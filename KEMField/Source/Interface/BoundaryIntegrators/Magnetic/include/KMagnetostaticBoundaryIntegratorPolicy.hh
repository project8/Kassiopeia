/*
 * KMagnetostaticBoundaryIntegratorPolicy.hh
 *
 *  Created on: 30.08.2016
 *      Author: gosda
 */

#ifndef KMAGNETOSTATICBOUNDARYINTEGRATORPOLICY_HH_
#define KMAGNETOSTATICBOUNDARYINTEGRATORPOLICY_HH_

#include "KMagnetostaticBoundaryIntegrator.hh"

#include <string>

#ifdef KEMFIELD_USE_OPENCL
#include "KOpenCLMagnetostaticBoundaryIntegrator.hh"
#endif

namespace KEMField
{

/**
 * This class mirrors the Interfaces way of having or not having the
 * OpenCL part in them depending on the compilation flag.
 * It should be not much more (some addition selection gathering might happen)
 * than the combination of both electrostatic boundary integrator factories.
 *
 * Leave the factories in the constructors to detect the errors early (unknown
 * names, etc.) where the bindings can process them and create sensible error
 * messages.
 */
class KMagnetostaticBoundaryIntegratorPolicy
{
  public:
    KMagnetostaticBoundaryIntegratorPolicy();
    KMagnetostaticBoundaryIntegratorPolicy(const std::string& name);

    KMagnetostaticBoundaryIntegrator CreateIntegrator();
#ifdef KEMFIELD_USE_OPENCL
    KOpenCLMagnetostaticBoundaryIntegrator CreateOpenCLIntegrator(KOpenCLSurfaceContainer& container);

    KoclEBIConfig CreateOpenCLConfig();
#endif

  private:
    KMagnetostaticBoundaryIntegrator fIntegratorCPU;
#ifdef KEMFIELD_USE_OPENCL
    KOpenCLMagnetostaticBoundaryIntegratorConfig fOpenCLIntegratorConfig;
#endif
};

// a short alias for lazy people
using KEBIPolicy = KMagnetostaticBoundaryIntegratorPolicy;

} /* namespace KEMField */

#endif /* KMAGNETOSTATICBOUNDARYINTEGRATORPOLICY_HH_ */
