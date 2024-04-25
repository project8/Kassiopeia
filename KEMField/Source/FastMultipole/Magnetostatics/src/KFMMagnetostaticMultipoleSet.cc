#include "KFMMagnetostaticMultipoleSet.hh"


namespace KEMField
{

KFMMagnetostaticMultipoleSet::KFMMagnetostaticMultipoleSet() = default;

KFMMagnetostaticMultipoleSet::~KFMMagnetostaticMultipoleSet() = default;

std::string KFMMagnetostaticMultipoleSet::ClassName() const
{
    return std::string("KFMMagnetostaticMultipoleSet");
}

void KFMMagnetostaticMultipoleSet::DefineOutputNode(KSAOutputNode* node) const
{
    KFMScalarMultipoleExpansion::DefineOutputNode(node);
}

void KFMMagnetostaticMultipoleSet::DefineInputNode(KSAInputNode* node)
{
    KFMScalarMultipoleExpansion::DefineInputNode(node);
}

}  // namespace KEMField
