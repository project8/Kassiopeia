#include "KFMMagnetostaticTreeData.hh"

namespace KEMField
{

void KFMMagnetostaticTreeData::GetFlattenedTree(std::vector<KFMNodeData>* node_data) const
{
    *node_data = fFlattenedTree;
}

void KFMMagnetostaticTreeData::SetFlattenedTree(const std::vector<KFMNodeData>* node_data)
{
    fFlattenedTree = *node_data;
}

void KFMMagnetostaticTreeData::GetLocalCoefficientNodeIDs(std::vector<int>* node_ids) const
{
    *node_ids = fLocalCoefficientsNodeIDs;
}

void KFMMagnetostaticTreeData::SetLocalCoefficientNodeIDs(const std::vector<int>* node_ids)
{
    fLocalCoefficientsNodeIDs = *node_ids;
}

void KFMMagnetostaticTreeData::GetLocalCoefficients(
    std::vector<KFMMagnetostaticLocalCoefficientSet*>* local_coeff) const
{
    *local_coeff = fLocalCoefficients;
}

void KFMMagnetostaticTreeData::SetLocalCoefficients(
    const std::vector<KFMMagnetostaticLocalCoefficientSet*>* local_coeff)
{
    fLocalCoefficients = *local_coeff;
}

void KFMMagnetostaticTreeData::GetIdentitySetNodeIDs(std::vector<int>* node_ids) const
{
    *node_ids = fIdentitySetNodeIDs;
}

void KFMMagnetostaticTreeData::SetIdentitySetNodeIDs(const std::vector<int>* node_ids)
{
    fIdentitySetNodeIDs = *node_ids;
}

void KFMMagnetostaticTreeData::GetIdentitySets(std::vector<KFMIdentitySet*>* id_sets) const
{
    *id_sets = fIdentitySets;
}

void KFMMagnetostaticTreeData::SetIdentitySets(const std::vector<KFMIdentitySet*>* id_sets)
{
    fIdentitySets = *id_sets;
}

void KFMMagnetostaticTreeData::GetCubeNodeIDs(std::vector<int>* node_ids) const
{
    *node_ids = fCubeNodeIDs;
}

void KFMMagnetostaticTreeData::SetCubeNodeIDs(const std::vector<int>* node_ids)
{
    fCubeNodeIDs = *node_ids;
}


void KFMMagnetostaticTreeData::GetCubes(std::vector<KFMCube<3>*>* cubes) const
{
    *cubes = fCubes;
}

void KFMMagnetostaticTreeData::SetCubes(const std::vector<KFMCube<3>*>* cubes)
{
    fCubes = *cubes;
}

void KFMMagnetostaticTreeData::DefineOutputNode(KSAOutputNode* node) const
{
    if (node != nullptr) {
        node->AddChild(
            new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                std::string,
                                                &KFMMagnetostaticTreeData::GetTreeID>(std::string("tree_id"), this));
        node->AddChild(new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                           unsigned int,
                                                           &KFMMagnetostaticTreeData::GetNumberOfTreeNodes>(
            std::string("n_tree_nodes"),
            this));
        node->AddChild(
            new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                unsigned int,
                                                &KFMMagnetostaticTreeData::GetDivisions>(std::string("divisions"),
                                                                                         this));
        node->AddChild(new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                           unsigned int,
                                                           &KFMMagnetostaticTreeData::GetTopLevelDivisions>(
            std::string("top_level_divisions"),
            this));
        node->AddChild(
            new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                unsigned int,
                                                &KFMMagnetostaticTreeData::GetDegree>(std::string("degree"), this));
        node->AddChild(new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                           unsigned int,
                                                           &KFMMagnetostaticTreeData::GetZeroMaskSize>(
            std::string("zero_mask_size"),
            this));
        node->AddChild(new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                           unsigned int,
                                                           &KFMMagnetostaticTreeData::GetMaximumTreeDepth>(
            std::string("maximum_tree_depth"),
            this));
        node->AddChild(new KSAAssociatedValuePODOutputNode<KFMMagnetostaticTreeData,
                                                           double,
                                                           &KFMMagnetostaticTreeData::GetInsertionRatio>(
            std::string("insertion_ratio"),
            this));

        node->AddChild(
            new KSAAssociatedPassedPointerPODOutputNode<KFMMagnetostaticTreeData,
                                                        std::vector<int>,
                                                        &KFMMagnetostaticTreeData::GetLocalCoefficientNodeIDs>(
                std::string("LocalCoefficientNodeIDVector"),
                this));
        node->AddChild(new KSAAssociatedPassedPointerPODOutputNode<KFMMagnetostaticTreeData,
                                                                   std::vector<int>,
                                                                   &KFMMagnetostaticTreeData::GetIdentitySetNodeIDs>(
            std::string("IdentitySetNodeIDVector"),
            this));
        node->AddChild(new KSAAssociatedPassedPointerPODOutputNode<KFMMagnetostaticTreeData,
                                                                   std::vector<int>,
                                                                   &KFMMagnetostaticTreeData::GetCubeNodeIDs>(
            std::string("CubeNodeIDVector"),
            this));


        node->AddChild(
            new KSAObjectOutputNode<std::vector<KFMNodeData>>(std::string("NodeDataVector"), &fFlattenedTree));
        node->AddChild(
            new KSAObjectOutputNode<std::vector<KFMIdentitySet*>>(std::string("IdentitySetVector"), &fIdentitySets));
        node->AddChild(new KSAObjectOutputNode<std::vector<KFMCube<3>*>>(std::string("CubeVector"), &fCubes));
        node->AddChild(new KSAObjectOutputNode<std::vector<KFMMagnetostaticLocalCoefficientSet*>>(
            std::string("LocalCoefficientVector"),
            &fLocalCoefficients));
    }
}

void KFMMagnetostaticTreeData::DefineInputNode(KSAInputNode* node)
{
    if (node != nullptr) {
        node->AddChild(
            new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                   std::string,
                                                   &KFMMagnetostaticTreeData::SetTreeID>(std::string("tree_id"), this));
        node->AddChild(new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                              unsigned int,
                                                              &KFMMagnetostaticTreeData::SetNumberOfTreeNodes>(
            std::string("n_tree_nodes"),
            this));
        node->AddChild(
            new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                   unsigned int,
                                                   &KFMMagnetostaticTreeData::SetDivisions>(std::string("divisions"),
                                                                                            this));
        node->AddChild(new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                              unsigned int,
                                                              &KFMMagnetostaticTreeData::SetTopLevelDivisions>(
            std::string("top_level_divisions"),
            this));
        node->AddChild(
            new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                   unsigned int,
                                                   &KFMMagnetostaticTreeData::SetDegree>(std::string("degree"), this));
        node->AddChild(new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                              unsigned int,
                                                              &KFMMagnetostaticTreeData::SetZeroMaskSize>(
            std::string("zero_mask_size"),
            this));
        node->AddChild(new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                              unsigned int,
                                                              &KFMMagnetostaticTreeData::SetMaximumTreeDepth>(
            std::string("maximum_tree_depth"),
            this));
        node->AddChild(new KSAAssociatedReferencePODInputNode<KFMMagnetostaticTreeData,
                                                              double,
                                                              &KFMMagnetostaticTreeData::SetInsertionRatio>(
            std::string("insertion_ratio"),
            this));

        node->AddChild(new KSAAssociatedPointerPODInputNode<KFMMagnetostaticTreeData,
                                                            std::vector<int>,
                                                            &KFMMagnetostaticTreeData::SetLocalCoefficientNodeIDs>(
            std::string("LocalCoefficientNodeIDVector"),
            this));
        node->AddChild(new KSAAssociatedPointerPODInputNode<KFMMagnetostaticTreeData,
                                                            std::vector<int>,
                                                            &KFMMagnetostaticTreeData::SetIdentitySetNodeIDs>(
            std::string("IdentitySetNodeIDVector"),
            this));
        node->AddChild(new KSAAssociatedPointerPODInputNode<KFMMagnetostaticTreeData,
                                                            std::vector<int>,
                                                            &KFMMagnetostaticTreeData::SetCubeNodeIDs>(
            std::string("CubeNodeIDVector"),
            this));

        node->AddChild(
            new KSAObjectInputNode<std::vector<KFMNodeData>>(std::string("NodeDataVector"), &fFlattenedTree));
        node->AddChild(
            new KSAObjectInputNode<std::vector<KFMIdentitySet*>>(std::string("IdentitySetVector"), &fIdentitySets));
        node->AddChild(new KSAObjectInputNode<std::vector<KFMCube<3>*>>(std::string("CubeVector"), &fCubes));
        node->AddChild(new KSAObjectInputNode<std::vector<KFMMagnetostaticLocalCoefficientSet*>>(
            std::string("LocalCoefficientVector"),
            &fLocalCoefficients));
    }
}


}  // namespace KEMField
