/*
 * KMagneticFastMultipoleFieldSolverBuilder.cc
 *
 *  Created on: 24 Jul 2015
 *      Author: wolfgang
 */

#include "KMagneticFastMultipoleFieldSolverBuilder.hh"

#include "KMagnetostaticBoundaryFieldBuilder.hh"

using namespace KEMField;

namespace katrin
{

template<> KMagneticFastMultipoleFieldSolverBuilder::~KComplexElement() = default;

STATICINT sKMagneticFastMultipoleFieldSolverStructure =
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("top_level_divisions") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("tree_level_divisions") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("expansion_degree") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("neighbor_order") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("maximum_tree_depth") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("region_expansion_factor") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<bool>("use_region_size_estimation") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("world_cube_center_x") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("world_cube_center_y") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("world_cube_center_z") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("world_cube_length") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<bool>("use_caching") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<unsigned int>("verbosity") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<double>("insertion_ratio") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<bool>("use_opencl") +
    KMagneticFastMultipoleFieldSolverBuilder::Attribute<bool>("split_mode");

STATICINT sKMagnetostaticBoundaryField =
    KMagnetostaticBoundaryFieldBuilder::ComplexElement<KMagneticFastMultipoleFieldSolver>(
        "fast_multipole_field_solver");

} /* namespace katrin */
