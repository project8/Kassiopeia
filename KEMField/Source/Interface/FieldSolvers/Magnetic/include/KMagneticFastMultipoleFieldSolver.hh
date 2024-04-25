/*
 * KMagneticFastMultipoleFieldSolver.hh
 *
 *  Created on: 23.07.2015
 *      Author: gosda
 */

#ifndef KMAGNETICFASTMULTIPOLEFIELDSOLVER_HH_
#define KMAGNETICFASTMULTIPOLEFIELDSOLVER_HH_

#include "KMagneticFieldSolver.hh"
#include "KMagnetostaticBoundaryIntegratorPolicy.hh"
#include "KFMMagnetostaticFastMultipoleFieldSolver.hh"
#include "KFMMagnetostaticParameters.hh"
#include "KFMMagnetostaticTree.hh"

#ifdef KEMFIELD_USE_OPENCL
//#include "KFMMagnetostaticFieldMapper_OpenCL.hh"
#include "KFMMagnetostaticFastMultipoleFieldSolver_OpenCL.hh"
#endif

namespace KEMField
{

class KMagneticFastMultipoleFieldSolver : public KMagneticFieldSolver
{
  public:
    KMagneticFastMultipoleFieldSolver();
    ~KMagneticFastMultipoleFieldSolver() override;

    void InitializeCore(KSurfaceContainer& container) override;
    void DeinitializeCore() override {}

    double PotentialCore(const KPosition& P) const override;
    KFieldVector MagneticFieldCore(const KPosition& P) const override;

    void SetIntegratorPolicy(const KEBIPolicy& policy)
    {
        fIntegratorPolicy = policy;
    }

    KFMMagnetostaticParameters* GetParameters()
    {
        return &fParameters;
    }

    std::string GetParameterInformation();

    KFMMagnetostaticTree* GetTree()
    {
        return fTree;
    }

    void UseOpenCL(bool choice);
    void SetSplitMode(bool choice);

  private:
    KEBIPolicy fIntegratorPolicy;
    KFMMagnetostaticParameters fParameters;
    KFMMagnetostaticTree* fTree;
    KFMMagnetostaticFastMultipoleFieldSolver* fFastMultipoleFieldSolver;
#ifdef KEMFIELD_USE_OPENCL
    KFMMagnetostaticFastMultipoleFieldSolver_OpenCL* fFastMultipoleFieldSolverOpenCL;
#endif
    bool fUseOpenCL;
};

} /* namespace KEMField */

#endif /* KMAGNETICFASTMULTIPOLEFIELDSOLVER_HH_ */
