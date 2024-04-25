#ifndef KFMMagnetostaticFastMultipoleFieldSolver_HH__
#define KFMMagnetostaticFastMultipoleFieldSolver_HH__

#include "KMagnetostaticBoundaryIntegrator.hh"
#include "KMagnetostaticIntegratingFieldSolver.hh"
#include "KFMMagnetostaticLocalCoefficientFieldCalculator.hh"
#include "KFMMagnetostaticTree.hh"
#include "KSurfaceContainer.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticFastMultipoleFieldSolver.hh
*@class KFMMagnetostaticFastMultipoleFieldSolver
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Thu Jan 23 16:56:53 EST 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticFastMultipoleFieldSolver
{
  public:
    KFMMagnetostaticFastMultipoleFieldSolver(const KSurfaceContainer& container, KFMMagnetostaticTree& tree);

    virtual ~KFMMagnetostaticFastMultipoleFieldSolver();

    //computes the potential and field at a given point
    double Potential(const KPosition& P) const;
    KFieldVector MagneticField(const KPosition& P) const;

    //for debugging and information purposes
    int GetSubsetSize(const KPosition& P) const
    {
        SetPoint(P);
        return fSubsetSize;
    };
    int GetTreeLevel(const KPosition& P) const
    {
        SetPoint(P);
        return fNodeList->size() - 1;
    };

  protected:
    void SetPoint(const double* p) const;


    ////////////////////////////////////////////////////////////////////////////

    const KSurfaceContainer& fSurfaceContainer;

    KFMMagnetostaticTree& fTree;
    KFMMagnetostaticNode* fRootNode;
    KFMMagnetostaticParameters fParameters;
    bool fUseCaching;

    //direct field evaluation
    mutable KMagnetostaticBoundaryIntegrator fDirectIntegrator;
//    KIntegratingFieldSolver<KMagnetostaticBoundaryIntegrator> fDirectFieldSolver;

    //needed for field evaluation
    mutable KFMMagnetostaticLocalCoefficientFieldCalculator fFastFieldSolver;

    mutable KFMMagnetostaticTreeNavigator fNavigator;
    mutable KFMPoint<3> fEvaluationPoint;
    mutable KFMMagnetostaticNode* fLeafNode;
    mutable KFMCube<3>* fCube;
    mutable KFMPoint<3> fExpansionOrigin;
    mutable KFMMagnetostaticLocalCoefficientSet* fLocalCoeff;

    mutable std::vector<KFMMagnetostaticNode*>* fNodeList;
    mutable unsigned int fSubsetSize;
    mutable unsigned int* fDirectCallIDs;

    mutable bool fFallback;
};


}  // namespace KEMField


#endif /* KFMMagnetostaticFastMultipoleFieldSolver_H__ */
