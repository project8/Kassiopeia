#ifndef __KFMMagnetostaticBoundaryIntegratorEngine_SingleThread_H__
#define __KFMMagnetostaticBoundaryIntegratorEngine_SingleThread_H__

#include "KFMMagnetostaticElementContainer.hh"
#include "KFMMagnetostaticMultipoleBatchCalculatorBase.hh"
#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticParameters.hh"
#include "KFMMagnetostaticTree.hh"
#include "KFMNodeObjectRemover.hh"
#include "KFMObjectRetriever.hh"

namespace KEMField
{

/**
*
*@file KFMMagnetostaticBoundaryIntegratorEngine_SingleThread.hh
*@class KFMMagnetostaticBoundaryIntegratorEngine_SingleThread
*@brief
*@details
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Jul 16 13:26:56 EDT 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMMagnetostaticBoundaryIntegratorEngine_SingleThread
{
  public:
    KFMMagnetostaticBoundaryIntegratorEngine_SingleThread();
    virtual ~KFMMagnetostaticBoundaryIntegratorEngine_SingleThread();

    //for evaluating work load weights
    void EvaluateWorkLoads(unsigned int divisions, unsigned int zeromask);
    double GetDiskWeight() const
    {
        return fDiskWeight;
    };
    double GetRamWeight() const
    {
        return fRamWeight;
    };
    double GetFFTWeight() const
    {
        return fFFTWeight;
    };

    //extracted electrode data
    void SetMagnetostaticElementContainer(KFMMagnetostaticElementContainerBase<3, 1>* container)
    {
        fContainer = container;
    };

    void SetParameters(const KFMMagnetostaticParameters& params);
    void SetTree(KFMMagnetostaticTree* tree);
    void InitializeMultipoleMoments();
    void InitializeLocalCoefficientsForPrimaryNodes();

    //dummy functions (used by mpi)
    void RecieveTopLevelLocalCoefficients(){};
    void SendTopLevelLocalCoefficients(){};

    void Initialize();

    void MapField();

    //individual operations, only to be used when the tree needs
    //to be modified in between steps (i.e. MPI)
    void ResetMultipoleMoments();
    void ComputeMultipoleMoments();
    void ResetLocalCoefficients();
    void ComputeMultipoleToLocal();
    void ComputeLocalToLocal();
    void ComputeLocalCoefficients();

  protected:
    void AssociateElementsAndNodes();

    static double ComputeDiskMatrixVectorProductWeight();
    static double ComputeRamMatrixVectorProductWeight();
    static double ComputeFFTWeight(unsigned int divisions, unsigned int zeromask);

#ifdef KEMFIELD_USE_REALTIME_CLOCK
    timespec diff(timespec start, timespec end)
    {
        timespec temp;
        if ((end.tv_nsec - start.tv_nsec) < 0) {
            temp.tv_sec = end.tv_sec - start.tv_sec - 1;
            temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
        }
        else {
            temp.tv_sec = end.tv_sec - start.tv_sec;
            temp.tv_nsec = end.tv_nsec - start.tv_nsec;
        }
        return temp;
    }
#endif

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

    double fDiskWeight;
    double fRamWeight;
    double fFFTWeight;
    static const std::string fWeightFilePrefix;

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


    //local coefficient resetter
    KFMMagnetostaticLocalCoefficientResetter* fLocalCoeffResetter;
    //multipole resetter
    KFMMagnetostaticMultipoleResetter* fMultipoleResetter;


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

#endif /* __KFMMagnetostaticBoundaryIntegratorEngine_SingleThread_H__ */
