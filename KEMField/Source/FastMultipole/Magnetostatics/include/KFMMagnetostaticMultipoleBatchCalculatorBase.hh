#ifndef KFMMagnetostaticMultipoleBatchCalculatorBase_HH__
#define KFMMagnetostaticMultipoleBatchCalculatorBase_HH__

#include "KFMMagnetostaticElementContainer.hh"
#include "KFMElementMomentBatchCalculator.hh"

#define KFM_MAX_ASPECT_RATIO 50


namespace KEMField
{

/*
*
*@file KFMMagnetostaticMultipoleBatchCalculatorBase.hh
*@class KFMMagnetostaticMultipoleBatchCalculatorBase
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Sun Feb  9 11:30:51 EST 2014 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticMultipoleBatchCalculatorBase : public KFMElementMomentBatchCalculator
{
  public:
    KFMMagnetostaticMultipoleBatchCalculatorBase() : KFMElementMomentBatchCalculator()
    {
        fContainer = nullptr;
    }

    ~KFMMagnetostaticMultipoleBatchCalculatorBase() override
    {
        ;
    };

    void SetMagnetostaticElementContainer(const KFMMagnetostaticElementContainerBase<3, 1>* container)
    {
        fContainer = container;
    }

  protected:
    const KFMMagnetostaticElementContainerBase<3, 1>* fContainer;
};


}  // namespace KEMField


#endif /* KFMMagnetostaticMultipoleBatchCalculatorBase_H__ */
