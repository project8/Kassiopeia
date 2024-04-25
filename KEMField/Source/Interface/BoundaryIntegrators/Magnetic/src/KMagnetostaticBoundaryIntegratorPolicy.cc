/*
 * KMagnetostaticBoundaryIntegratorPolicy.cc
 *
 *  Created on: 30.08.2016
 *      Author: gosda
 */

#include "KMagnetostaticBoundaryIntegratorPolicy.hh"

#include "KMagnetostaticBoundaryIntegratorFactory.hh"

#ifdef KEMFIELD_USE_OPENCL
#include "KOpenCLMagnetostaticBoundaryIntegratorFactory.hh"
#endif

#include "KEMCoreMessage.hh"

namespace KEMField
{

KMagnetostaticBoundaryIntegratorPolicy::KMagnetostaticBoundaryIntegratorPolicy() :
    fIntegratorCPU(KEBIFactory::MakeDefault())
#ifdef KEMFIELD_USE_OPENCL
    ,
    fOpenCLIntegratorConfig(KOpenCLMagnetostaticBoundaryIntegratorFactory::MakeDefaultConfig())
#endif
{}

KMagnetostaticBoundaryIntegratorPolicy::KMagnetostaticBoundaryIntegratorPolicy(const std::string& name) :
    fIntegratorCPU(KEBIFactory::Make(name))
#ifdef KEMFIELD_USE_OPENCL
    ,
    fOpenCLIntegratorConfig(KOpenCLMagnetostaticBoundaryIntegratorFactory::MakeConfig(name))
#endif
{
    kem_cout() << "Using boundary integrator policy: " << name << eom;
}

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorPolicy::CreateIntegrator()
{
    return fIntegratorCPU;
}

#ifdef KEMFIELD_USE_OPENCL
KOpenCLMagnetostaticBoundaryIntegrator
KMagnetostaticBoundaryIntegratorPolicy::CreateOpenCLIntegrator(KOpenCLSurfaceContainer& container)
{
    return KOpenCLMagnetostaticBoundaryIntegrator(fOpenCLIntegratorConfig, container);
}

KoclEBIConfig KMagnetostaticBoundaryIntegratorPolicy::CreateOpenCLConfig()
{
    return fOpenCLIntegratorConfig;
}
#endif

} /* namespace KEMField */
