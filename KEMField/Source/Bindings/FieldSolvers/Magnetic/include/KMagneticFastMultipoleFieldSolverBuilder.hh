/*
 * KMagneticFastMultipoleFieldSolverBuilder.hh
 *
 *  Created on: 24 Jul 2015
 *      Author: wolfgang
 */

#ifndef KMAGNETICFASTMULTIPOLEFIELDSOLVERBUILDER_HH_
#define KMAGNETICFASTMULTIPOLEFIELDSOLVERBUILDER_HH_

#include "KComplexElement.hh"
#include "KMagneticFastMultipoleFieldSolver.hh"

namespace katrin
{

typedef KComplexElement<KEMField::KMagneticFastMultipoleFieldSolver> KMagneticFastMultipoleFieldSolverBuilder;

template<> inline bool KMagneticFastMultipoleFieldSolverBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "top_level_divisions") {
        fObject->GetParameters()->top_level_divisions = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "tree_level_divisions") {
        fObject->GetParameters()->divisions = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "expansion_degree") {
        fObject->GetParameters()->degree = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "neighbor_order") {
        fObject->GetParameters()->zeromask = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "maximum_tree_depth") {
        fObject->GetParameters()->maximum_tree_depth = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "region_expansion_factor") {
        fObject->GetParameters()->region_expansion_factor = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "use_region_size_estimation") {
        fObject->GetParameters()->use_region_estimation = aContainer->AsReference<bool>();
        return true;
    }
    if (aContainer->GetName() == "world_cube_center_x") {
        fObject->GetParameters()->world_center_x = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "world_cube_center_y") {
        fObject->GetParameters()->world_center_y = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "world_cube_center_z") {
        fObject->GetParameters()->world_center_z = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "world_cube_length") {
        fObject->GetParameters()->world_length = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "use_caching") {
        fObject->GetParameters()->use_caching = aContainer->AsReference<bool>();
        return true;
    }
    if (aContainer->GetName() == "verbosity") {
        fObject->GetParameters()->verbosity = aContainer->AsReference<unsigned int>();
        return true;
    }
    if (aContainer->GetName() == "insertion_ratio") {
        fObject->GetParameters()->insertion_ratio = aContainer->AsReference<double>();
        return true;
    }
    if (aContainer->GetName() == "use_opencl") {
        aContainer->CopyTo(fObject, &KEMField::KMagneticFastMultipoleFieldSolver::UseOpenCL);
        return true;
    }
    if (aContainer->GetName() == "split_mode") {
        aContainer->CopyTo(fObject, &KEMField::KMagneticFastMultipoleFieldSolver::SetSplitMode);
        return true;
    }
    return false;
}


} /* namespace katrin */
#endif /* KMAGNETICFASTMULTIPOLEFIELDSOLVERBUILDER_HH_ */
