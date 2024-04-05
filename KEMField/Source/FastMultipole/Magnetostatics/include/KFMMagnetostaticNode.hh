#ifndef KFMMagnetostaticNode_HH__
#define KFMMagnetostaticNode_HH__


#include "KFMBall.hh"
#include "KFMCollocationPointIdentitySet.hh"
#include "KFMCube.hh"
#include "KFMCubicSpaceTreeProperties.hh"
#include "KFMMagnetostaticElementContainerBase.hh"
#include "KFMMagnetostaticLocalCoefficientSet.hh"
#include "KFMMagnetostaticMultipoleSet.hh"
#include "KFMElementLocalInfluenceRange.hh"
#include "KFMExternalIdentitySet.hh"
#include "KFMIdentitySet.hh"
#include "KFMIdentitySetList.hh"
#include "KFMNode.hh"
#include "KFMNodeFlags.hh"
#include "KFMNodeIdentityListRange.hh"

#define KFMMAGNETOSTATICS_DIM   3
#define KFMMAGNETOSTATICS_BASIS 1
#define KFMMAGNETOSTATICS_FLAGS 2


namespace KEMField
{

/*
*
*@file KFMMagnetostaticNode.hh
*@class KFMMagnetostaticNode
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Sep  4 10:01:33 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/


//some typedefs...needed for picky compilers
typedef KFMCubicSpaceTreeProperties<KFMMAGNETOSTATICS_DIM> three_dimensional_tree_properties;

using three_dimensional_constant_charge_density_element_container =
    KFMMagnetostaticElementContainerBase<KFMMAGNETOSTATICS_DIM, KFMMAGNETOSTATICS_BASIS>;

using three_dimensional_cube = KFMCube<KFMMAGNETOSTATICS_DIM>;

using electrostatic_node_flags = KFMNodeFlags<KFMMAGNETOSTATICS_FLAGS>;

using KFMMagnetostaticNodeObjects =
    KEMField::KTypelist<three_dimensional_tree_properties,
        KEMField::KTypelist<three_dimensional_constant_charge_density_element_container,
            KEMField::KTypelist<KFMIdentitySet,
                KEMField::KTypelist<KFMIdentitySetList,
                    KEMField::KTypelist<KFMCollocationPointIdentitySet,
                        KEMField::KTypelist<three_dimensional_cube,
                            KEMField::KTypelist<electrostatic_node_flags,
                                KEMField::KTypelist<KFMMagnetostaticMultipoleSet,
                                    KEMField::KTypelist<KFMMagnetostaticLocalCoefficientSet,
                                        KEMField::KNullType>>>>>>>>>;

using KFMMagnetostaticNode = KFMNode<KFMMagnetostaticNodeObjects>;

}  // namespace KEMField

#endif /* KFMMagnetostaticNode_H__ */
