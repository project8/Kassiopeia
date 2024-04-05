#ifndef KFMMagnetostaticFieldMapper_SingleThread_HH__
#define KFMMagnetostaticFieldMapper_SingleThread_HH__

#include "KFMMagnetostaticElementContainer.hh"
#include "KFMMagnetostaticMultipoleBatchCalculatorBase.hh"
#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticParameters.hh"
#include "KFMMagnetostaticRegionSizeEstimator.hh"
#include "KFMMagnetostaticTree.hh"
#include "KFMNodeObjectRemover.hh"
#include "KFMObjectRetriever.hh"


/*
*
*@file KFMMagnetostaticFieldMapper_SingleThread.hh
*@class KFMMagnetostaticFieldMapper_SingleThread
*@brief helper class to apply actions to a tree
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Tue Sep 24 15:05:27 EDT 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/

namespace KEMField
{


class KFMMagnetostaticFieldMapper_SingleThread
{
  public:
    KFMMagnetostaticFieldMapper_SingleThread();
    virtual ~KFMMagnetostaticFieldMapper_SingleThread();

    //extracted electrode data
    void SetMagnetostaticElementContainer(KFMMagnetostaticElementContainerBase<3, 1>* container)
    {
        fContainer = container;
    };

    //access to the region tree
    void SetTree(KFMMagnetostaticTree* tree);

    void Initialize();

    void MapField();

  protected:
    //operations
    void SetParameters(const KFMMagnetostaticParameters& params);
    void AssociateElementsAndNodes();
    void InitializeMultipoleMoments();
    void ComputeMultipoleMoments();
    void InitializeLocalCoefficients();
    void ComputeLocalCoefficients();
    void CleanUp();

    ////////////////////////////////////////////////////////////////////////

    //data
    int fDegree;
    unsigned int fNTerms;
    int fTopLevelDivisions;
    int fDivisions;
    int fZeroMaskSize;
    int fMaximumTreeDepth;
    unsigned int fVerbosity;
    double fWorldLength;

    //the tree object that the manager is to construct
    KFMMagnetostaticTree* fTree;

    //element node associator
    KFMMagnetostaticElementNodeAssociator* fElementNodeAssociator;
    //the multipole calculator
    KFMMagnetostaticMultipoleBatchCalculatorBase* fBatchCalc;
    //the element's multipole distributor
    KFMMagnetostaticElementMultipoleDistributor* fMultipoleDistributor;

    //the local coefficient initializer
    KFMMagnetostaticLocalCoefficientInitializer* fLocalCoeffInitializer;

    //the multipole coefficient initializer
    KFMMagnetostaticMultipoleInitializer* fMultipoleInitializer;

    //the multipole up converter
    KFMMagnetostaticRemoteToRemoteConverter* fM2MConverter;

    //the local coefficient calculator
    //        KFMMagnetostaticRemoteToLocalConverter* fM2LConverter;
    KFMMagnetostaticRemoteToLocalConverterInterface* fM2LConverterInterface;

    //the local coefficient down converter
    KFMMagnetostaticLocalToLocalConverter* fL2LConverter;

    //container to the eletrostatic elements
    KFMMagnetostaticElementContainerBase<3, 1>* fContainer;
};


}  // namespace KEMField


#endif /* KFMMagnetostaticFieldMapper_SingleThread_H__ */
