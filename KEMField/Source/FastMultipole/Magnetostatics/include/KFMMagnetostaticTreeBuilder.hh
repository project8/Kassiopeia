#ifndef __KFMMagnetostaticTreeBuilder_H__
#define __KFMMagnetostaticTreeBuilder_H__


#include "KFMCubicSpaceBallSorter.hh"
#include "KFMCubicSpaceTree.hh"
#include "KFMCubicSpaceTreeProperties.hh"
#include "KFMMagnetostaticElementContainer.hh"
#include "KFMMagnetostaticElementContainerBase.hh"
#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticParameters.hh"
#include "KFMMagnetostaticRegionSizeEstimator.hh"
#include "KFMMagnetostaticTree.hh"
#include "KFMInsertionCondition.hh"
#include "KFMNodeObjectRemover.hh"
#include "KFMObjectRetriever.hh"
#include "KFMSubdivisionCondition.hh"
#include "KFMSubdivisionConditionAggressive.hh"
#include "KFMSubdivisionConditionBalanced.hh"
#include "KFMSubdivisionConditionGuided.hh"

namespace KEMField
{


/**
*
*@file KFMMagnetostaticTreeBuilder.hh
*@class KFMMagnetostaticTreeBuilder
*@brief class responsible for constructing the tree's 'skeleton' (nodes and their relations)
*Does not compute moments or provide visitors to do this
*@details
*<b>Revision History:<b>
*Date Name Brief Description
*Mon Jul  7 11:09:06 EDT 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMMagnetostaticTreeBuilder
{
  public:
    KFMMagnetostaticTreeBuilder()
    {
        fSubdivisionCondition = nullptr;
        fSubdivisionConditionIsOwned = false;
    };

    virtual ~KFMMagnetostaticTreeBuilder()
    {
        if (fSubdivisionConditionIsOwned) {
            delete fSubdivisionCondition;
        }
    };

    //extracted electrode data
    void SetMagnetostaticElementContainer(
        KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>* container);
    KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>*
    GetMagnetostaticElementContainer();

    //access to the region tree, tree builder does not own the tree!
    void SetTree(KFMMagnetostaticTree* tree);
    KFMMagnetostaticTree* GetTree();

    void SetSubdivisionCondition(KFMSubdivisionCondition<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>* subdiv)
    {
        if (subdiv != nullptr) {
            fSubdivisionCondition = subdiv;
            fSubdivisionConditionIsOwned = false;
        }
    }


    //build up the tree using these functions
    //typically these are applied in the same order as they are listed here
    void ConstructRootNode();
    void PerformSpatialSubdivision();
    void FlagNonZeroMultipoleNodes();
    void PerformAdjacencySubdivision();
    void FlagPrimaryNodes();
    void CollectDirectCallIdentities();
    void CollectDirectCallIdentitiesForPrimaryNodes();

  protected:
    /* data */
    int fDegree;
    unsigned int fNTerms;
    int fTopLevelDivisions;
    int fDivisions;
    int fZeroMaskSize;
    int fMaximumTreeDepth;
    double fInsertionRatio;
    unsigned int fVerbosity;
    double fRegionSizeFactor;

    bool fUseRegionEstimation;
    KFMPoint<3> fWorldCenter;
    double fWorldLength;

    //the tree object that the manager is to construct
    KFMMagnetostaticTree* fTree;

    //subdivision condition
    KFMSubdivisionCondition<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>* fSubdivisionCondition;
    bool fSubdivisionConditionIsOwned;

    //manager does not own this object!
    //container to the eletrostatic elements
    KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>* fContainer;
};


}  // namespace KEMField

#endif /* __KFMMagnetostaticTreeBuilder_H__ */
