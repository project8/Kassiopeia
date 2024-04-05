#ifndef KFMMagnetostaticRegionSizeEstimator_HH__
#define KFMMagnetostaticRegionSizeEstimator_HH__

#include "KFMBoundaryCalculator.hh"
#include "KFMCube.hh"
#include "KFMMagnetostaticElementContainerBase.hh"

#include <cstddef>

namespace KEMField
{

/*
*
*@file KFMMagnetostaticRegionSizeEstimator.hh
*@class KFMMagnetostaticRegionSizeEstimator
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Sep  4 18:16:42 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMMagnetostaticRegionSizeEstimator
{
  public:
    KFMMagnetostaticRegionSizeEstimator();
    virtual ~KFMMagnetostaticRegionSizeEstimator();

    void SetMagnetostaticElementContainer(const KFMMagnetostaticElementContainerBase<3, 1>* container)
    {
        fElementContainer = container;
    }

    void ComputeEstimate();

    KFMCube<3> GetCubeEstimate() const;
    KFMBall<3> GetBallEstimate() const;
    KFMBox<3> GetBoxEstimate() const;

  private:
    const KFMMagnetostaticElementContainerBase<3, 1>* fElementContainer;

    KFMBoundaryCalculator<3>* fEstimator;
};

}  // namespace KEMField

#endif /* KFMMagnetostaticRegionSizeEstimator_H__ */
