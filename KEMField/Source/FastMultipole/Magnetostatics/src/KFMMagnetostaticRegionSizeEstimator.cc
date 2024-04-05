#include "KFMMagnetostaticRegionSizeEstimator.hh"

namespace KEMField
{


KFMMagnetostaticRegionSizeEstimator::KFMMagnetostaticRegionSizeEstimator() : fElementContainer(nullptr)
{
    fEstimator = new KFMBoundaryCalculator<3>();
}

KFMMagnetostaticRegionSizeEstimator::~KFMMagnetostaticRegionSizeEstimator()
{
    delete fEstimator;
}

void KFMMagnetostaticRegionSizeEstimator::ComputeEstimate()
{
    unsigned int n_elem = fElementContainer->GetNElements();
    for (unsigned int i = 0; i < n_elem; i++) {
        fEstimator->AddBall(fElementContainer->GetBoundingBall(i));
    }
}

KFMCube<3> KFMMagnetostaticRegionSizeEstimator::GetCubeEstimate() const
{
    return fEstimator->GetMinimalBoundingCube();
}

KFMBall<3> KFMMagnetostaticRegionSizeEstimator::GetBallEstimate() const
{
    return fEstimator->GetMinimalBoundingBall();
}

KFMBox<3> KFMMagnetostaticRegionSizeEstimator::GetBoxEstimate() const
{
    return fEstimator->GetMinimalBoundingBox();
}


}  // namespace KEMField
