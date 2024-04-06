/*
 * KMagnetostaticBoundaryIntegratorFactory.hh
 *
 *  Created on: 26 Aug 2016
 *      Author: wolfgang
 */

#ifndef KMAGNETOSTATICBOUNDARYINTEGRATORFACTORY_HH_
#define KMAGNETOSTATICBOUNDARYINTEGRATORFACTORY_HH_

#include "KMagnetostaticBoundaryIntegrator.hh"

#include <string>

namespace KEMField
{

class KMagnetostaticBoundaryIntegratorFactory
{
  public:

  
    static KMagnetostaticBoundaryIntegrator MakeDefault();


/*
    // FFTM might use different default because only
    // close by evaluations are normally used
    static KMagnetostaticBoundaryIntegrator MakeDefaultForFFTM();

    static KMagnetostaticBoundaryIntegrator MakeAnalytic();

    static KMagnetostaticBoundaryIntegrator MakeNumeric();

    static KMagnetostaticBoundaryIntegrator MakeRWG();

    static KMagnetostaticBoundaryIntegrator MakeReference();
    
*/
    static KMagnetostaticBoundaryIntegrator Make(const std::string& name);
    
};

using KEBIFactory = KMagnetostaticBoundaryIntegratorFactory;

} /* namespace KEMField */

#endif /* KMAGNETOSTATICBOUNDARYINTEGRATORFACTORY_HH_ */
