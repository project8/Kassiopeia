/*
 * EBIFactory.cc
 *
 *  Created on: 26 Aug 2016
 *      Author: wolfgang
 */

#include "KMagnetostaticBoundaryIntegratorFactory.hh"
#include "KMagnetostaticAnalyticLineSegmentIntegrator.hh"

#include "KEMSimpleException.hh"


namespace KEMField
{


KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeDefault()
{
    return KMagnetostaticBoundaryIntegrator(std::make_shared<KMagnetostaticAnalyticLineSegmentIntegrator>());
}

/*
KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeDefaultForFFTM()
{
    return MakeNumeric();
}

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeAnalytic()
{
    return KMagnetostaticBoundaryIntegrator(std::make_shared<KMagnetostaticAnalyticTriangleIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticRectangleIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticLineSegmentIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticConicSectionIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticRingIntegrator>());
}

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeNumeric()
{
    return KMagnetostaticBoundaryIntegrator(std::make_shared<KMagnetostaticCubatureTriangleIntegrator>(),
                                            std::make_shared<KMagnetostaticCubatureRectangleIntegrator>(),
                                            std::make_shared<KMagnetostaticQuadratureLineSegmentIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticConicSectionIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticRingIntegrator>());
}

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeRWG()
{
    return KMagnetostaticBoundaryIntegrator(std::make_shared<KMagnetostaticRWGTriangleIntegrator>(),
                                            std::make_shared<KMagnetostaticRWGRectangleIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticLineSegmentIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticConicSectionIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticRingIntegrator>());
}

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::MakeReference()
{
    return KMagnetostaticBoundaryIntegrator(std::make_shared<KMagnetostaticBiQuadratureTriangleIntegrator>(),
                                            std::make_shared<KMagnetostaticBiQuadratureRectangleIntegrator>(),
                                            std::make_shared<KMagnetostatic256NodeQuadratureLineSegmentIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticConicSectionIntegrator>(),
                                            std::make_shared<KMagnetostaticAnalyticRingIntegrator>());
}

*/

KMagnetostaticBoundaryIntegrator KMagnetostaticBoundaryIntegratorFactory::Make(const std::string& name)
{
/*
    if (name == "numeric")
        return MakeNumeric();
    if (name == "analytic")
        return MakeAnalytic();
    if (name == "rwg")
        return MakeRWG();
    if (name == "reference")
        return MakeReference();
*/        
    if (name == "default")
        return MakeDefault();       
    throw KEMSimpleException("KMagnetostaticBoundaryIntegratorFactory has no integrator with name: " + name);
}

} /* namespace KEMField */
