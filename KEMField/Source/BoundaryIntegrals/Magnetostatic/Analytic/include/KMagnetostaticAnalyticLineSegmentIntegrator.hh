#ifndef KMAGNETOSTATICLINESEGMENTINTEGRATOR_DEF
#define KMAGNETOSTATICLINESEGMENTINTEGRATOR_DEF

#include "KEMConstants.hh"
#include "KMagnetostaticElementIntegrator.hh"
#include "KSurface.hh"

namespace KEMField
{
class KMagnetostaticAnalyticLineSegmentIntegrator : public KMagnetostaticElementIntegrator<KLineSegment>
{
  public:
    using Shape = KLineSegment;
    using ValueType = KMagnetostaticBasis::ValueType;

    KMagnetostaticAnalyticLineSegmentIntegrator() = default;
    ~KMagnetostaticAnalyticLineSegmentIntegrator() override = default;

    double Potential(const KLineSegment* source, const KPosition& P) const override;
    KFieldVector MagneticField(const KLineSegment* source, const KPosition& P) const override;
    using KMagnetostaticElementIntegrator<KLineSegment>::Potential;
    using KMagnetostaticElementIntegrator<KLineSegment>::MagneticField;
};

}  // namespace KEMField

#endif /* KMAGNETOSTATICLINESEGMENTINTEGRATOR_DEF */
