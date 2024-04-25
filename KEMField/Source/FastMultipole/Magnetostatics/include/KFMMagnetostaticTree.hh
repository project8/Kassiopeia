#ifndef KFMMagnetostaticTree_HH__
#define KFMMagnetostaticTree_HH__

#include "KFMCubicSpaceTree.hh"
#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticParameters.hh"
#include "KFMExternalIdentitySetSorter.hh"
#include "KFMIdentitySetSorter.hh"


//from kernel
#include "KFMResponseKernel_3DLaplaceL2L.hh"
#include "KFMResponseKernel_3DLaplaceM2L.hh"
#include "KFMResponseKernel_3DLaplaceM2M.hh"

//from tree
#include "KFMCollocationPointIdentitySetCreator.hh"
#include "KFMCubicSpaceNodeAdjacencyProgenitor.hh"
#include "KFMCubicSpaceTreeNavigator.hh"
#include "KFMElementLocalInfluenceRangeCollector.hh"
#include "KFMElementLocator.hh"
#include "KFMElementNodeAssociator.hh"
#include "KFMElementScalarMomentDistributor.hh"
#include "KFMIdentitySetCollector.hh"
#include "KFMIdentitySetListCreator.hh"
#include "KFMIdentitySetMerger.hh"
#include "KFMNearbyElementCounter.hh"
#include "KFMNodeFlagInitializer.hh"
#include "KFMNodeIdentityListCreator.hh"
#include "KFMNodeIdentityListRange.hh"
#include "KFMNodeIdentityListRangeAssociator.hh"
#include "KFMReducedScalarMomentRemoteToLocalConverter.hh"
#include "KFMRemoteToLocalConverterInterface.hh"
#include "KFMScalarMomentDistributor.hh"
#include "KFMScalarMomentInitializer.hh"
#include "KFMScalarMomentLocalToLocalConverter.hh"
#include "KFMScalarMomentRemoteToLocalConverter.hh"
#include "KFMScalarMomentRemoteToRemoteConverter.hh"
#include "KFMScalarMomentResetter.hh"

#include <string>

#define USE_REDUCED_M2L


namespace KEMField
{


//we operate on the tree with the following visitors
typedef KFMNearbyElementCounter<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM>
    KFMMagnetostaticNearbyElementCounter;

using KFMMagnetostaticElementNodeAssociator = KFMElementNodeAssociator<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM>;

using KFMMagnetostaticIdentitySetListCreator = KFMIdentitySetListCreator<KFMMagnetostaticNodeObjects>;

//distributor of element moments
using KFMMagnetostaticElementMultipoleDistributor =
    KFMElementScalarMomentDistributor<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet, KFMMAGNETOSTATICS_DIM>;


//initializers
using KFMMagnetostaticMultipoleInitializer =
    KFMScalarMomentInitializer<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet>;

using KFMMagnetostaticLocalCoefficientInitializer =
    KFMScalarMomentInitializer<KFMMagnetostaticNodeObjects, KFMMagnetostaticLocalCoefficientSet>;

//resetters
using KFMMagnetostaticMultipoleResetter =
    KFMScalarMomentResetter<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet>;

using KFMMagnetostaticLocalCoefficientResetter =
    KFMScalarMomentResetter<KFMMagnetostaticNodeObjects, KFMMagnetostaticLocalCoefficientSet>;

//moment converters
using KFMMagnetostaticRemoteToRemoteConverter =
    KFMScalarMomentRemoteToRemoteConverter<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet,
                                           KFMResponseKernel_3DLaplaceM2M, KFMMAGNETOSTATICS_DIM>;

using KFMMagnetostaticLocalToLocalConverter =
    KFMScalarMomentLocalToLocalConverter<KFMMagnetostaticNodeObjects, KFMMagnetostaticLocalCoefficientSet,
                                         KFMResponseKernel_3DLaplaceL2L, KFMMAGNETOSTATICS_DIM>;

#ifdef USE_REDUCED_M2L
using KFMMagnetostaticRemoteToLocalConverter =
    KFMReducedScalarMomentRemoteToLocalConverter<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet,
                                                 KFMMagnetostaticLocalCoefficientSet, KFMResponseKernel_3DLaplaceM2L,
                                                 KFMMAGNETOSTATICS_DIM>;
#else
typedef KFMScalarMomentRemoteToLocalConverter<KFMMagnetostaticNodeObjects, KFMMagnetostaticMultipoleSet,
                                              KFMMagnetostaticLocalCoefficientSet, KFMResponseKernel_3DLaplaceM2L,
                                              KFMMAGNETOSTATICS_DIM>
    KFMMagnetostaticRemoteToLocalConverter;
#endif

//interface to m2l converters to handle different divisions on top level
using KFMMagnetostaticRemoteToLocalConverterInterface =
    KFMRemoteToLocalConverterInterface<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM, KFMMagnetostaticRemoteToLocalConverter>;

//navigator
using KFMMagnetostaticTreeNavigator = KFMCubicSpaceTreeNavigator<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM>;

//id set collector
using KFMMagnetostaticNodeIdentitySetMerger = KFMIdentitySetMerger<KFMMagnetostaticNodeObjects>;

//inspector to determine node primacy
using KFMMagnetostaticAdjacencyProgenitor = KFMCubicSpaceNodeAdjacencyProgenitor<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM>;


//sorters for the identity set, and external identity set
using KFMMagnetostaticIdentitySetSorter = KFMIdentitySetSorter<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticExternalIdentitySetSorter = KFMExternalIdentitySetSorter<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticElementLocator = KFMElementLocator<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticNodeIdentityListCreator = KFMNodeIdentityListCreator<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticNodeIdentityListRangeAssociator = KFMNodeIdentityListRangeAssociator<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticElementInfluenceRangeCollector =
    KFMElementInfluenceRangeCollector<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticNodeIdentitySetCollector = KFMIdentitySetCollector<KFMMagnetostaticNodeObjects>;

using KFMMagnetostaticCollocationPointIdentitySetCreator =
    KFMCollocationPointIdentitySetCreator<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_DIM>;

//the local coefficient calculator
//KFMLocalCoefficientCalculator* fLocalCoeffCalculator;


/*
*
*@file KFMMagnetostaticTree.hh
*@class KFMMagnetostaticTree
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Tue Sep 24 15:00:38 EDT 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/

//this is the type of tree we operate on
class KFMMagnetostaticTree : public KFMCubicSpaceTree<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>
{
  public:
    KFMMagnetostaticTree() : KFMCubicSpaceTree<KFMMAGNETOSTATICS_DIM, KFMMagnetostaticNodeObjects>()
    {
        ;
    }
    ~KFMMagnetostaticTree() override = default;
    ;

    void SetParameters(const KFMMagnetostaticParameters& params)
    {
        fParameters = params;
    }

    KFMMagnetostaticParameters GetParameters()
    {
        return fParameters;
    };

    std::string GetUniqueID() const
    {
        return fUniqueID;
    };
    void SetUniqueID(const std::string& unique_id)
    {
        fUniqueID = unique_id;
    };

  private:
    KFMMagnetostaticParameters fParameters;
    std::string fUniqueID;
};


}  // namespace KEMField

#endif /* KFMMagnetostaticTree_H__ */
