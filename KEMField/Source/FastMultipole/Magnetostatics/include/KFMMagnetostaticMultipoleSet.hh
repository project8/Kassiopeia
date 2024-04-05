#ifndef KFMMagnetostaticMultipoleSet_HH__
#define KFMMagnetostaticMultipoleSet_HH__

#include "KFMScalarMultipoleExpansion.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticMultipoleSet.hh
*@class KFMMagnetostaticMultipoleSet
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Sep  4 10:06:47 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticMultipoleSet : public KFMScalarMultipoleExpansion
{
  public:
    KFMMagnetostaticMultipoleSet();
    ~KFMMagnetostaticMultipoleSet() override;
    KFMMagnetostaticMultipoleSet(const KFMMagnetostaticMultipoleSet& copyObject) :
        KFMScalarMultipoleExpansion(copyObject)
    {
        ;
    };
    KFMMagnetostaticMultipoleSet& operator=(const KFMMagnetostaticMultipoleSet& copyObject) = default;
    ;

    std::string ClassName() const override;

    void DefineOutputNode(KSAOutputNode* node) const override;
    void DefineInputNode(KSAInputNode* node) override;

  private:
};

DefineKSAClassName(KFMMagnetostaticMultipoleSet)

}  // namespace KEMField


#endif /* KFMMagnetostaticMultipoleSet_H__ */
