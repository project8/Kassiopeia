#ifndef KFMMagnetostaticTreeInformationExtractor_HH__
#define KFMMagnetostaticTreeInformationExtractor_HH__

#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticTree.hh"
#include "KFMNodeActor.hh"
#include "KFMNodeFlagValueInspector.hh"


namespace KEMField
{


/*
*
*@file KFMMagnetostaticTreeInformationExtractor.hh
*@class KFMMagnetostaticTreeInformationExtractor
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Thu Feb 13 16:07:31 EST 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticTreeInformationExtractor : public KFMNodeActor<KFMMagnetostaticNode>
{
  public:
    KFMMagnetostaticTreeInformationExtractor()
    {
        fInitialized = false;
        fMaxDepth = 0;
        fMaxDirectCalls = 0;
        fDegree = 0;
        fZeroMaskSize = 0;

        fMultipoleFlagCondition.SetFlagIndex(1);
        fMultipoleFlagCondition.SetFlagValue(1);

        fLocalCoeffFlagCondition.SetFlagIndex(0);
        fLocalCoeffFlagCondition.SetFlagValue(1);
    };

    ~KFMMagnetostaticTreeInformationExtractor() override = default;
    ;

    void SetDegree(unsigned int degree)
    {
        fDegree = degree;
    };

    void ApplyAction(KFMMagnetostaticNode* node) override
    {
        if (!fInitialized) {
            KFMCubicSpaceTreeProperties<3>* prop =
                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCubicSpaceTreeProperties<3>>::GetNodeObject(node);

            fZeroMaskSize = prop->GetCubicNeighborOrder();
            fMaxDepth = prop->GetMaxTreeDepth();
            fNLevelNodes.resize(fMaxDepth + 1);
            fNLevelNodesWithNonZeroMultipole.resize(fMaxDepth + 1);
            fNLevelElements.resize(fMaxDepth + 1);
            fLevelElementSet.resize(fMaxDepth + 1);
            fLevelNodeSize.resize(fMaxDepth + 1);
            fNLevelPrimaryNodes.resize(fMaxDepth + 1);
            fNLevelDirectCalls.resize(fMaxDepth + 1);

            fLocalCoeffMem = 0;
            fMultipoleCoeffMem = 0;
            fIDSetMem = 0;
            fNodeMem = 0;
            fExternalIDSetMem = 0;

            for (unsigned int i = 0; i < fMaxDepth; i++) {
                fNLevelNodes[i] = 0;
                fNLevelElements[i] = 0;
                fNLevelNodesWithNonZeroMultipole[i] = 0;
                fLevelNodeSize[i] = 0;
                fNLevelPrimaryNodes[i] = 0;
                fNLevelDirectCalls[i] = 0;
            }

            fNNodes = 0;

            fInitialized = true;
        }

        if (node != nullptr) {
            fNNodes++;

            fNodeMem +=
                sizeof(KFMMagnetostaticNode) + sizeof(electrostatic_node_flags) + sizeof(three_dimensional_cube);

            int level = node->GetLevel();

            fNLevelNodes[level] += 1;

            double length =
                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCube<3>>::GetNodeObject(node)->GetLength();

            fLevelNodeSize[level] = length;

            if (node->GetID() == 0)  //root node
            {
                KFMCube<3>* world_cube =
                    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCube<3>>::GetNodeObject(node);

                fWorldCenter = world_cube->GetCenter();
                fWorldLength = world_cube->GetLength();
            }

            if (fMultipoleFlagCondition.ConditionIsSatisfied(node)) {
                fNLevelNodesWithNonZeroMultipole[level] += 1;
                fMultipoleCoeffMem += 2 * (((fDegree + 1) * (fDegree + 2)) / 2) * sizeof(double);
            }

            if (fLocalCoeffFlagCondition.ConditionIsSatisfied(node)) {
                fNLevelPrimaryNodes[level] += 1;
                fLocalCoeffMem += 2 * (((fDegree + 1) * (fDegree + 2)) / 2) * sizeof(double);
            }

            KFMIdentitySet* id_set =
                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySet>::GetNodeObject(node);
            if (id_set != nullptr) {
                fIDSetMem += (id_set->GetSize()) * sizeof(unsigned int);
                fNLevelElements[level] += id_set->GetSize();
                fLevelElementSet[level].Merge(id_set);
            }

            KFMCollocationPointIdentitySet* coll_id_set =
                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCollocationPointIdentitySet>::GetNodeObject(node);
            if (coll_id_set != nullptr) {
                fIDSetMem += (coll_id_set->GetSize()) * sizeof(unsigned int);
            }

            KFMIdentitySetList* id_set_list =
                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySetList>::GetNodeObject(node);
            if (id_set_list != nullptr) {
                if (node->GetParent() != nullptr) {
                    KFMIdentitySetList* parent_id_set_list =
                        KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySetList>::GetNodeObject(
                            node->GetParent());
                    if (id_set_list != parent_id_set_list) {
                        //std::cout<<"n sets = "<<id_set_list->GetNumberOfSets()<<std::endl;
                        fExternalIDSetMem +=
                            (id_set_list->GetNumberOfSets()) * sizeof(const std::vector<unsigned int>*);
                    }
                }
            }

            unsigned int direct_calls = CountDirectCalls(node);

            if (direct_calls > fMaxDirectCalls) {
                fMaxDirectCalls = direct_calls;
            };
        }
    }

    void PrintStatistics()
    {
        kfmout << "Tree summary is as follows: " << kfmendl;
        kfmout << "Tree has " << fNNodes << " nodes. Center at (" << fWorldCenter[0] << ", " << fWorldCenter[1] << ", "
               << fWorldCenter[2] << ") and side length: " << fWorldLength << kfmendl;
        kfmout << "Level / Total Nodes / Source Nodes / Target Nodes / Elements Owned / Direct Calls " << kfmendl;
        for (unsigned int i = 0; i < fNLevelNodes.size(); i++) {
            std::stringstream ss;
            ss << i << " / " << fNLevelNodes[i] << " / " << fNLevelNodesWithNonZeroMultipole[i] << " / "
               << fNLevelPrimaryNodes[i] << " / ";
            ss << fNLevelElements[i] << " / " << fNLevelDirectCalls[i];
            kfmout << ss.str() << kfmendl;
        }

        kfmout << "Max number of direct calls from any one node is: " << fMaxDirectCalls << kfmendl;
        kfmout << "Total memory required by id-sets (MB) = " << fIDSetMem / (1024. * 1024.) << kfmendl;
        kfmout << "Total memory required by external id-sets (MB) = " << fExternalIDSetMem / (1024. * 1024.) << kfmendl;
        kfmout << "Total memory required by multipole expansions (MB) = " << fMultipoleCoeffMem / (1024. * 1024.)
               << kfmendl;
        kfmout << "Total memory required by local coefficient expansions (MB) = " << fLocalCoeffMem / (1024. * 1024.)
               << kfmendl;
        kfmout << "Total memory required by nodes (MB) = " << fNodeMem / (1024. * 1024.) << kfmendl;
    }

    std::string GetStatistics()
    {
        std::stringstream ss;
        ss << "Tree summary is as follows: " << std::endl;
        ss << "Tree has " << fNNodes << " nodes. Center at (" << fWorldCenter[0] << ", " << fWorldCenter[1] << ", "
           << fWorldCenter[2] << ") and side length: " << fWorldLength << std::endl;
        ss << "Level / Total Nodes / Source Nodes / Target Nodes / Elements Owned / Direct Calls " << std::endl;

        for (unsigned int i = 0; i < fNLevelNodes.size(); i++) {
            ss << i << " / " << fNLevelNodes[i] << " / " << fNLevelNodesWithNonZeroMultipole[i] << " / "
               << fNLevelPrimaryNodes[i] << " / ";
            ss << fNLevelElements[i] << " / " << fNLevelDirectCalls[i];
            ss << std::endl;
        }

        ss << "Max number of direct calls from any one node is: " << fMaxDirectCalls << std::endl;
        ss << "Total memory required by id-sets (MB) = " << fIDSetMem / (1024. * 1024.) << std::endl;
        ss << "Total memory required by external id-sets (MB) = " << fExternalIDSetMem / (1024. * 1024.) << std::endl;
        ss << "Total memory required by multipole expansions (MB) = " << fMultipoleCoeffMem / (1024. * 1024.)
           << std::endl;
        ss << "Total memory required by local coefficient expansions (MB) = " << fLocalCoeffMem / (1024. * 1024.)
           << std::endl;
        ss << "Total memory required by nodes (MB) = " << fNodeMem / (1024. * 1024.) << std::endl;

        return ss.str();
    }

    std::vector<KFMIdentitySet>* GetLevelIDSets()
    {
        return &fLevelElementSet;
    };

    unsigned int GetMaxDirectCalls() const
    {
        return fMaxDirectCalls;
    };

  protected:
    bool fInitialized;
    unsigned int fMaxDepth;
    unsigned int fMaxDirectCalls;
    unsigned int fDegree;
    unsigned int fZeroMaskSize;

    KFMPoint<3> fWorldCenter;
    double fWorldLength;

    unsigned int fNNodes;
    std::vector<double> fNLevelNodes;
    std::vector<double> fLevelNodeSize;
    std::vector<double> fNLevelNodesWithNonZeroMultipole;
    std::vector<double> fNLevelElements;
    std::vector<double> fNLevelPrimaryNodes;
    std::vector<double> fNLevelDirectCalls;  //which level the direct calls come from
    std::vector<KFMIdentitySet> fLevelElementSet;

    double fLocalCoeffMem;
    double fMultipoleCoeffMem;
    double fIDSetMem;
    double fNodeMem;
    double fExternalIDSetMem;

    std::vector<KFMMagnetostaticNode*> fNodeList;
    std::vector<KFMMagnetostaticNode*> fNodeNeighborList;

    //condition for a node to have a multipole/local coeff expansion
    KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> fMultipoleFlagCondition;
    KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> fLocalCoeffFlagCondition;

    //count number of direct calls in this node
    unsigned int CountDirectCalls(KFMMagnetostaticNode* node)
    {
        unsigned int count = 0;
        unsigned int level_count = 0;

        KFMMagnetostaticNode* temp_node;
        if (!(node->HasChildren())) {

            temp_node = node;
            fNodeList.clear();
            fNodeNeighborList.clear();
            fNodeList.push_back(temp_node);
            //collect all of the parents in the node list
            while (temp_node->GetParent() != nullptr) {
                fNodeList.push_back(temp_node->GetParent());
                temp_node = temp_node->GetParent();
            }


            for (unsigned int i = 0; i < fNodeList.size(); i++) {
                level_count = 0;
                KFMCubicSpaceNodeNeighborFinder<3, KFMMagnetostaticNodeObjects>::GetAllNeighbors(fNodeList[i],
                                                                                                 fZeroMaskSize,
                                                                                                 &fNodeNeighborList);
                for (auto& j : fNodeNeighborList) {
                    if (j != nullptr) {
                        if (KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySet>::GetNodeObject(j) !=
                            nullptr) {
                            level_count +=
                                KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySet>::GetNodeObject(j)
                                    ->GetSize();
                        }
                    }
                }

                fNLevelDirectCalls[(fNodeList.size() - 1) - i] += level_count;
                count += level_count;
            }
        }

        return count;
    }
};


}  // namespace KEMField

#endif /* KFMMagnetostaticTreeInformationExtractor_H__ */
