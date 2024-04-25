#ifndef KFMMagnetostaticNearFieldToLocalCoefficientCalculator_HH__
#define KFMMagnetostaticNearFieldToLocalCoefficientCalculator_HH__

#include "KFMMagnetostaticElementContainerBase.hh"
#include "KFMMagnetostaticLocalCoefficientCalculatorNumeric.hh"
#include "KFMMagnetostaticLocalCoefficientSet.hh"
#include "KFMMagnetostaticNode.hh"
#include "KFMNodeActor.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticNearFieldToLocalCoefficientCalculator.hh
*@class KFMMagnetostaticNearFieldToLocalCoefficientCalculator
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Fri Apr 18 14:25:05 EDT 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMMagnetostaticNearFieldToLocalCoefficientCalculator : public KFMNodeActor<KFMMagnetostaticNode>
{
  public:
    KFMMagnetostaticNearFieldToLocalCoefficientCalculator();
    ~KFMMagnetostaticNearFieldToLocalCoefficientCalculator() override;

    void SetDegree(int l_max);
    void SetNumberOfQuadratureTerms(unsigned int n);

    void Initialize();

    void SetMagnetostaticElementContainer(KFMMagnetostaticElementContainerBase<3, 1>* elementContainer)
    {
        fElementContainer = elementContainer;
    }

    void ApplyAction(KFMMagnetostaticNode* node) override;

  private:
    unsigned int fDegree;
    unsigned int fNQuadrature;

    double fConversionFactor;

    KFMMagnetostaticLocalCoefficientCalculatorNumeric* fLocalCoeffCalc;
    KFMMagnetostaticElementContainerBase<3, 1>* fElementContainer;
    mutable KFMMagnetostaticLocalCoefficientSet fTempMoments;
    std::vector<unsigned int> fElementsToRemove;
    std::vector<unsigned int> fElementsToKeep;
};


}  // namespace KEMField

#endif /* KFMMagnetostaticNearFieldToLocalCoefficientCalculator_H__ */
