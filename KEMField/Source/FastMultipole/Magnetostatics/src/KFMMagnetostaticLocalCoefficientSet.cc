#include "KFMMagnetostaticLocalCoefficientSet.hh"


namespace KEMField
{

KFMMagnetostaticLocalCoefficientSet::KFMMagnetostaticLocalCoefficientSet() = default;

KFMMagnetostaticLocalCoefficientSet::~KFMMagnetostaticLocalCoefficientSet() = default;

std::string KFMMagnetostaticLocalCoefficientSet::ClassName() const
{
    return std::string("KFMMagnetostaticLocalCoefficientSet");
}

void KFMMagnetostaticLocalCoefficientSet::DefineOutputNode(KSAOutputNode* node) const
{
    KFMScalarMultipoleExpansion::DefineOutputNode(node);
}

void KFMMagnetostaticLocalCoefficientSet::DefineInputNode(KSAInputNode* node)
{
    KFMScalarMultipoleExpansion::DefineInputNode(node);
}


}  // namespace KEMField
