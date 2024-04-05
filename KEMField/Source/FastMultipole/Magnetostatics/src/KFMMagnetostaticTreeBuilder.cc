#include "KFMMagnetostaticTreeBuilder.hh"

#include "KFMCompoundInspectingActor.hh"
#include "KFMLeafConditionActor.hh"
#include "KFMNodeChildToParentFlagValueInitializer.hh"
#include "KFMNodeFlagValueInitializer.hh"
#include "KFMNodeFlagValueInspector.hh"
#include "KFMNodeParentToChildFlagValueInspector.hh"
#include "KFMNonEmptyIdentitySetActor.hh"

namespace KEMField
{

//extracted electrode data
void KFMMagnetostaticTreeBuilder::SetMagnetostaticElementContainer(
    KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>* container)
{
    fContainer = container;
}


KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>*
KFMMagnetostaticTreeBuilder::GetMagnetostaticElementContainer()
{
    return fContainer;
}


void KFMMagnetostaticTreeBuilder::SetTree(KFMMagnetostaticTree* tree)
{
    fTree = tree;
    KFMMagnetostaticParameters params = tree->GetParameters();

    fDegree = params.degree;
    fNTerms = (fDegree + 1) * (fDegree + 1);
    fTopLevelDivisions = params.top_level_divisions;
    fDivisions = params.divisions;
    fZeroMaskSize = params.zeromask;
    fMaximumTreeDepth = params.maximum_tree_depth;
    fInsertionRatio = params.insertion_ratio;
    fRegionSizeFactor = std::fabs(params.region_expansion_factor);
    fVerbosity = params.verbosity;

    if (!(params.use_region_estimation)) {
        fUseRegionEstimation = false;
        fWorldCenter[0] = params.world_center_x;
        fWorldCenter[1] = params.world_center_y;
        fWorldCenter[2] = params.world_center_z;
        fWorldLength = params.world_length;
    }
    else {
        fUseRegionEstimation = true;
    }

    if (fVerbosity > 1) {
        kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: top level divisions set to "
               << params.top_level_divisions << kfmendl;
        kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: divisions set to " << params.divisions << kfmendl;
        kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: degree set to " << params.degree << kfmendl;
        kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: zero mask size set to " << params.zeromask << kfmendl;
        kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: max tree depth set to " << params.maximum_tree_depth
               << kfmendl;

        if (!(params.use_region_estimation)) {
            kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: using user defined world cube volume" << kfmendl;
            kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: world cube center set to (" << params.world_center_x
                   << ", " << params.world_center_y << ", " << params.world_center_z << ") " << kfmendl;
            kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: world cube side length set to ("
                   << params.world_length << kfmendl;
        }
        else {
            kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: using region size estimation" << kfmendl;
            kfmout << "KFMMagnetostaticTreeBuilder::SetParameters: region expansion factor set to "
                   << params.region_expansion_factor << kfmendl;
        }
    }
}

KFMMagnetostaticTree* KFMMagnetostaticTreeBuilder::GetTree()
{
    return fTree;
}

void KFMMagnetostaticTreeBuilder::ConstructRootNode()
{
    if (fUseRegionEstimation) {
        if (fVerbosity > 2) {
            kfmout << "KFMMagnetostaticTreeBuilder::Initialize: Region size estimator running. " << kfmendl;
        }

        //the region size estimator
        KFMMagnetostaticRegionSizeEstimator regionSizeEstimator;

        regionSizeEstimator.SetMagnetostaticElementContainer(fContainer);
        regionSizeEstimator.ComputeEstimate();
        KFMCube<3> estimate = regionSizeEstimator.GetCubeEstimate();

        fWorldCenter = estimate.GetCenter();
        fWorldLength = fRegionSizeFactor * (estimate.GetLength());

        if (fVerbosity > 2) {
            kfmout << "KFMMagnetostaticTreeBuilder::Initialize: Estimated world cube center is (" << fWorldCenter[0]
                   << ", " << fWorldCenter[1] << ", " << fWorldCenter[2] << ")" << kfmendl;
            kfmout << "KFMMagnetostaticTreeBuilder::Initialize: Estimated world cube size length is " << fWorldLength
                   << kfmendl;
        }
    }

    KFMCube<3>* world_volume;
    world_volume = new KFMCube<3>(fWorldCenter, fWorldLength);
    KFMPoint<3> center = world_volume->GetCenter();

    unsigned int n_elements = fContainer->GetNElements();

    if (fVerbosity > 2) {
        kfmout << "KFMMagnetostaticTreeBuilder::ConstructRootNode: Constructing root node with center at (" << center[0]
               << ", " << center[1] << ", " << center[2] << ")." << kfmendl;
        kfmout << "KFMMagnetostaticTreeBuilder::ConstructRootNode: Root node has side length of " << fWorldLength
               << " and contains " << n_elements << " boundary elements." << kfmendl;
    }

    KFMCubicSpaceTreeProperties<3>* tree_prop = fTree->GetTreeProperties();

    tree_prop->SetMaxTreeDepth(fMaximumTreeDepth);
    tree_prop->SetCubicNeighborOrder(fZeroMaskSize);
    unsigned int dim[3] = {(unsigned int) fDivisions, (unsigned int) fDivisions, (unsigned int) fDivisions};
    unsigned int top_level_dim[3] = {(unsigned int) fTopLevelDivisions,
                                     (unsigned int) fTopLevelDivisions,
                                     (unsigned int) fTopLevelDivisions};
    tree_prop->SetDimensions(dim);
    tree_prop->SetTopLevelDimensions(top_level_dim);

    KFMMagnetostaticNode* root = fTree->GetRootNode();

    //set the world volume
    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCube<3>>::SetNodeObject(world_volume, root);

    //set the tree properties
    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMCubicSpaceTreeProperties<3>>::SetNodeObject(tree_prop, root);

    //set the element container
    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMMagnetostaticElementContainerBase<3, 1>>::SetNodeObject(
        fContainer,
        root);

    //add the complete id set of all elements to the root node
    auto* root_list = new KFMIdentitySet();
    for (unsigned int i = 0; i < n_elements; i++) {
        root_list->AddID(i);
    }

    //set the id set
    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySet>::SetNodeObject(root_list, root);

    //set basis node properties
    root->SetID(tree_prop->RegisterNode());
    root->SetIndex(0);
    root->SetParent(nullptr);
}

void KFMMagnetostaticTreeBuilder::PerformSpatialSubdivision()
{
    //conditions for subdivision of a node
    KFMInsertionCondition<3> basic_insertion_condition;
    basic_insertion_condition.SetInsertionRatio(fInsertionRatio);

    if (fSubdivisionCondition == nullptr) {
        //subdivision condition was unset, so we default to aggressive
        //since it is the only one which takes no paramters
        fSubdivisionCondition =
            new KFMSubdivisionConditionAggressive<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>();
        fSubdivisionConditionIsOwned = true;
    }

    fSubdivisionCondition->SetInsertionCondition(&basic_insertion_condition);
    fTree->SetSubdivisionCondition(fSubdivisionCondition);

    //things to do on a node after it has been visited by the progenitor
    KFMCubicSpaceBallSorter<3, KFMMagnetostaticNodeObjects> bball_sorter;
    bball_sorter.SetInsertionCondition(&basic_insertion_condition);
    fTree->AddPostSubdivisionAction(&bball_sorter);

    KFMObjectContainer<KFMBall<3>>* bballs = fContainer->GetBoundingBallContainer();
    fSubdivisionCondition->SetBoundingBallContainer(bballs);
    bball_sorter.SetBoundingBallContainer(bballs);

    if (fVerbosity > 2) {
        kfmout << "KFMMagnetostaticTreeBuilder::PerformSpatialSubdivision: Subdividing region using the "
               << fSubdivisionCondition->Name() << " strategy " << kfmendl;
    }

    fTree->ConstructTree();

    if (fVerbosity > 2) {
        kfmout << "KFMMagnetostaticTreeBuilder::PerformSpatialSubdivision: Done performing spatial subdivision. "
               << kfmendl;
    }
}

void KFMMagnetostaticTreeBuilder::FlagNonZeroMultipoleNodes()
{
    //the condition (non-empty id set)
    KFMNonEmptyIdentitySetActor<KFMMagnetostaticNodeObjects> non_empty_condition;

    //the flag value initializer
    KFMNodeChildToParentFlagValueInitializer<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> flag_init;
    flag_init.SetFlagIndex(1);
    flag_init.SetFlagValue(1);

    KFMConditionalActor<KFMMagnetostaticNode> conditional_actor;

    conditional_actor.SetInspectingActor(&non_empty_condition);
    conditional_actor.SetOperationalActor(&flag_init);

    fTree->ApplyRecursiveAction(&conditional_actor);
}

void KFMMagnetostaticTreeBuilder::PerformAdjacencySubdivision()
{
    //adjacency progenation condition
    KFMMagnetostaticAdjacencyProgenitor adjacencyProgenitor;
    adjacencyProgenitor.SetZeroMaskSize(fZeroMaskSize);

    //the condition that we use is that the node's adjacent to a node which
    //has non-zero multipole moments, and is not a leaf node

    //leaf condition inspector
    KFMLeafConditionActor<KFMMagnetostaticNode> leaf_condition;
    leaf_condition.SetFalseOnLeafNodes();

    //the non-zero multipole flag inspector
    KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> multipole_flag_condition;
    multipole_flag_condition.SetFlagIndex(1);
    multipole_flag_condition.SetFlagValue(1);

    //non-zero multipole flag inspector for all of the node's children
    KFMNodeParentToChildFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS>
        child_multipole_flag_condition;
    child_multipole_flag_condition.SetFlagIndex(1);
    child_multipole_flag_condition.SetFlagValue(1);
    child_multipole_flag_condition.UseOrCondition();

    //compound condition
    KFMCompoundInspectingActor<KFMMagnetostaticNode> compound_inspector;
    compound_inspector.UseAndCondition();

    compound_inspector.AddInspectingActor(&leaf_condition);
    compound_inspector.AddInspectingActor(&multipole_flag_condition);
    compound_inspector.AddInspectingActor(&child_multipole_flag_condition);

    //now we constuct the conditional actor
    KFMConditionalActor<KFMMagnetostaticNode> conditional_actor;

    conditional_actor.SetInspectingActor(&compound_inspector);
    conditional_actor.SetOperationalActor(&adjacencyProgenitor);

    fTree->ApplyCorecursiveAction(&conditional_actor);

    if (fVerbosity > 3) {
        kfmout
            << "KFMMagnetostaticTreeBuilder::PerformAdjacencySubdivision: Done performing subdivision of nodes satisfying adjacency condition."
            << kfmendl;
    }
}

void KFMMagnetostaticTreeBuilder::FlagPrimaryNodes()
{
    //for charge density solving we need to flag nodes which contain element centroids
    //(these get the 'primary' status flag)

    KFMMagnetostaticTreeNavigator navigator;

    //the flag value initializer
    KFMNodeChildToParentFlagValueInitializer<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> flag_init;
    flag_init.SetFlagIndex(0);
    flag_init.SetFlagValue(1);

    unsigned int n_elem = fContainer->GetNElements();
    //loop over all elements of surface container
    for (unsigned int i = 0; i < n_elem; i++) {
        KFMPoint<3> centroid = *(fContainer->GetCentroid(i));
        navigator.SetPoint(&centroid);
        navigator.ApplyAction(fTree->GetRootNode());

        if (navigator.Found()) {
            KFMMagnetostaticNode* leaf_node = navigator.GetLeafNode();
            flag_init.ApplyAction(leaf_node);
        }
        else {
            kfmout
                << "KFMMagnetostaticBoundaryIntegrator::FlagPrimaryNodes: Error, element centroid not found in region."
                << kfmendl;
            kfmexit(1);
        }
    }

    if (fVerbosity > 2) {
        kfmout << "KFMMagnetostaticTreeBuilder::FlagPrimaryNodes: Done flagging primary nodes." << kfmendl;
    }
}

void KFMMagnetostaticTreeBuilder::CollectDirectCallIdentities()
{
    //sorter for id sets
    KFMMagnetostaticIdentitySetSorter IDSorter;
    fTree->ApplyRecursiveAction(&IDSorter);

    //create the lists of the external identity sets
    //(reduced memory alternative to explicitly creating the external id sets as above)
    KFMMagnetostaticIdentitySetListCreator IDListCreator;
    IDListCreator.SetZeroMaskSize(fZeroMaskSize);
    fTree->ApplyCorecursiveAction(&IDListCreator);

    if (fVerbosity > 3) {
        kfmout
            << "KFMMagnetostaticTreeBuilder::CollectDirectCallIdentities: Done collecting element identities of node direct calls. Max number of direct calls from any node is "
            << kfmendl;
    }
}

void KFMMagnetostaticTreeBuilder::CollectDirectCallIdentitiesForPrimaryNodes()
{
    //sort id sets
    KFMMagnetostaticIdentitySetSorter IDSorter;

    fTree->ApplyRecursiveAction(&IDSorter);

    //the primacy flag inspector
    KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> primary_flag_condition;
    primary_flag_condition.SetFlagIndex(0);
    primary_flag_condition.SetFlagValue(1);

    //we assume that the primary nodes have already been determined
    //create a conditional actor, which depends on node primacy
    //to construct the direct call lists
    KFMConditionalActor<KFMMagnetostaticNode> conditional_actor;
    conditional_actor.SetInspectingActor(&primary_flag_condition);

    //create the lists of the external identity sets
    //(reduced memory alternative to explicitly creating the external id sets as above)
    KFMMagnetostaticIdentitySetListCreator IDListCreator;
    IDListCreator.SetZeroMaskSize(fZeroMaskSize);
    conditional_actor.SetOperationalActor(&IDListCreator);
    //apply action
    fTree->ApplyCorecursiveAction(&conditional_actor);

    //now we create the lists of the collocation points
    //these are associated with the centroid of each electrostatic element
    //first we form a list of the centroids
    std::vector<const KFMPoint<KFMMAGNETOSTATICS_DIM>*> centroids;
    unsigned int n_elements = fContainer->GetNElements();
    for (unsigned int i = 0; i < n_elements; i++) {
        centroids.push_back(fContainer->GetCentroid(i));
    }

    KFMMagnetostaticCollocationPointIdentitySetCreator cpid_creator;
    cpid_creator.SetTree(fTree);
    cpid_creator.SortCollocationPoints(&centroids);

    if (fVerbosity > 3) {
        kfmout
            << "KFMMagnetostaticTreeBuilder::CollectDirectCallIdentitiesForPrimaryNodes: Done collecting element identities of primary node direct calls."
            << kfmendl;
    }
}


}  // namespace KEMField
