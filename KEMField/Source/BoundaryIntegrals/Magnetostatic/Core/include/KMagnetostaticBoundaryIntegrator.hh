#ifndef KMAGNETOSTATICBOUNDARYINTEGRATOR_DEF
#define KMAGNETOSTATICBOUNDARYINTEGRATOR_DEF

#include "KMagnetostaticElementIntegrator.hh"
#include "KSurfacePrimitive.hh"
#include "KSurfaceVisitors.hh"

#include <memory>

namespace KEMField
{
class MagnetostaticSingleThread;

class KMagnetostaticBoundaryIntegrator
{
  public:
    using Basis = KMagnetostaticBasis;
    using ValueType = Basis::ValueType;
    using DirichletBoundary = KBoundaryType<Basis, KDirichletBoundary>;
    using NeumannBoundary = KBoundaryType<Basis, KNeumannBoundary>;
    using AcceptedBasis = KEMField::KTypelist<KMagnetostaticBasis, KEMField::KNullType>;
    using AcceptedBoundaries =
        KEMField::KTypelist<KDirichletBoundary, KEMField::KTypelist<KNeumannBoundary, KEMField::KNullType>>;
    using AcceptedShapes = KEMField::KTypelist<
        KTriangle,
        KEMField::KTypelist<
            KRectangle,
            KEMField::KTypelist<
                KLineSegment,
                KEMField::KTypelist<
                    KConicSection,
                    KEMField::KTypelist<
                        KRing,
                        KEMField::KTypelist<
                            KRectangleGroup,
                            KEMField::KTypelist<
                                KLineSegmentGroup,
                                KEMField::KTypelist<
                                    KTriangleGroup,
                                    KEMField::KTypelist<KConicSectionGroup,
                                                        KEMField::KTypelist<KRingGroup, KEMField::KNullType>>>>>>>>>>;

    // for field solver template selection, states what kind of boundary integrator this is.
    using Kind = MagnetostaticSingleThread;

    KMagnetostaticBoundaryIntegrator(
//        const std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>>& triangleIntegrator,
//        const std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>>& rectangleIntegrator,
        const std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>>& lineSegmentIntegrator);
//        const std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>>& conicSectionIntegrator,
//        const std::shared_ptr<KMagnetostaticElementIntegrator<KRing>>& ringIntegrator);

    KMagnetostaticBoundaryIntegrator(const KMagnetostaticBoundaryIntegrator& integrator);
    KMagnetostaticBoundaryIntegrator& operator=(const KMagnetostaticBoundaryIntegrator& integrator);
    virtual ~KMagnetostaticBoundaryIntegrator() = default;

    virtual ValueType BoundaryIntegral(KSurfacePrimitive* source, unsigned int sourceIndex, KSurfacePrimitive* target,
                                       unsigned int targetIndex);

    ValueType BoundaryValue(KSurfacePrimitive* surface, unsigned int);
    ValueType& BasisValue(KSurfacePrimitive* surface, unsigned int);

    //triangle integrator getter and setter and evaluation functions
    std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>> GetTriangleIntegrator();

    void SetTriangleIntegrator(const std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>>& triangleIntegrator);

    double Potential(const KTriangle* source, const KPosition& P) const;
    KFieldVector MagneticField(const KTriangle* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KTriangle* source, const KPosition& P) const;

    double Potential(const KTriangleGroup* source, const KPosition& P) const;
    KFieldVector MagneticField(const KTriangleGroup* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KTriangleGroup* source, const KPosition& P) const;

  private:
    std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>> fTriangleIntegrator;

  public:
    //Rectangle integrator getter and setter and evaluation functions
    std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>> GetRectangleIntegrator();

    void SetRectangleIntegrator(const std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>>& RectangleIntegrator);

    double Potential(const KRectangle* source, const KPosition& P) const;
    KFieldVector MagneticField(const KRectangle* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KRectangle* source, const KPosition& P) const;

    double Potential(const KRectangleGroup* source, const KPosition& P) const;
    KFieldVector MagneticField(const KRectangleGroup* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KRectangleGroup* source, const KPosition& P) const;

  private:
    std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>> fRectangleIntegrator;

  public:
    //LineSegment integrator getter and setter and evaluation functions
    std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>> GetLineSegmentIntegrator();

    void
    SetLineSegmentIntegrator(const std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>>& LineSegmentIntegrator);

    double Potential(const KLineSegment* source, const KPosition& P) const;
    KFieldVector MagneticField(const KLineSegment* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KLineSegment* source, const KPosition& P) const;

    double Potential(const KLineSegmentGroup* source, const KPosition& P) const;
    KFieldVector MagneticField(const KLineSegmentGroup* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KLineSegmentGroup* source,
                                                              const KPosition& P) const;

  private:
    std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>> fLineSegmentIntegrator;

  public:
    //ConicSection integrator getter and setter and evaluation functions
    std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>> GetConicSectionIntegrator();

    void SetConicSectionIntegrator(
        const std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>>& ConicSectionIntegrator);

    double Potential(const KConicSection* source, const KPosition& P) const;
    KFieldVector MagneticField(const KConicSection* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KConicSection* source, const KPosition& P) const;

    double Potential(const KConicSectionGroup* source, const KPosition& P) const;
    KFieldVector MagneticField(const KConicSectionGroup* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KConicSectionGroup* source,
                                                              const KPosition& P) const;

  private:
    std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>> fConicSectionIntegrator;

  public:
    //Ring integrator getter and setter and evaluation functions
    std::shared_ptr<KMagnetostaticElementIntegrator<KRing>> GetRingIntegrator();

    void SetRingIntegrator(const std::shared_ptr<KMagnetostaticElementIntegrator<KRing>>& ringIntegrator);

    double Potential(const KRing* source, const KPosition& P) const;
    KFieldVector MagneticField(const KRing* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KRing* source, const KPosition& P) const;

    double Potential(const KRingGroup* source, const KPosition& P) const;
    KFieldVector MagneticField(const KRingGroup* source, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KRingGroup* source, const KPosition& P) const;

  private:
    std::shared_ptr<KMagnetostaticElementIntegrator<KRing>> fRingIntegrator;

  protected:
    class ShapeVisitor : public KSelectiveVisitor<KShapeVisitor, AcceptedShapes>
    {
      public:
        using KSelectiveVisitor<KShapeVisitor, AcceptedShapes>::Visit;

        ShapeVisitor(KMagnetostaticBoundaryIntegrator& integrator) : fIntegrator(integrator) {}

        void Visit(KTriangle& t) override
        {
            fIntegrator.ComputeBoundaryIntegral(t);
        }
        void Visit(KRectangle& r) override
        {
            fIntegrator.ComputeBoundaryIntegral(r);
        }
        void Visit(KLineSegment& l) override
        {
            fIntegrator.ComputeBoundaryIntegral(l);
        }
        void Visit(KConicSection& c) override
        {
            fIntegrator.ComputeBoundaryIntegral(c);
        }
        void Visit(KRing& r) override
        {
            fIntegrator.ComputeBoundaryIntegral(r);
        }
        void Visit(KTriangleGroup& t) override
        {
            fIntegrator.ComputeBoundaryIntegral(t);
        }
        void Visit(KRectangleGroup& r) override
        {
            fIntegrator.ComputeBoundaryIntegral(r);
        }
        void Visit(KLineSegmentGroup& l) override
        {
            fIntegrator.ComputeBoundaryIntegral(l);
        }
        void Visit(KConicSectionGroup& c) override
        {
            fIntegrator.ComputeBoundaryIntegral(c);
        }
        void Visit(KRingGroup& r) override
        {
            fIntegrator.ComputeBoundaryIntegral(r);
        }

      protected:
        KMagnetostaticBoundaryIntegrator& fIntegrator;
    };

    class BoundaryVisitor : public KSelectiveVisitor<KBoundaryVisitor, AcceptedBoundaries>
    {
      public:
        using KSelectiveVisitor<KBoundaryVisitor, AcceptedBoundaries>::Visit;

        BoundaryVisitor() = default;

        void Visit(KDirichletBoundary&) override;
        void Visit(KNeumannBoundary&) override;

        bool IsDirichlet() const
        {
            return fIsDirichlet;
        }
        ValueType Prefactor() const
        {
            return fPrefactor;
        }
        ValueType GetBoundaryValue() const
        {
            return fBoundaryValue;
        }

      protected:
        bool fIsDirichlet;
        ValueType fPrefactor;
        ValueType fBoundaryValue;
    };

    class BasisVisitor : public KSelectiveVisitor<KBasisVisitor, AcceptedBasis>
    {
      public:
        using KSelectiveVisitor<KBasisVisitor, AcceptedBasis>::Visit;

        BasisVisitor() : fBasisValue(nullptr) {}

        void Visit(KMagnetostaticBasis&) override;

        ValueType& GetBasisValue() const
        {
            return *fBasisValue;
        }

      protected:
        ValueType* fBasisValue;
    };

    template<class SourceShape> void ComputeBoundaryIntegral(SourceShape& source);

    ShapeVisitor fShapeVisitor;
    BoundaryVisitor fBoundaryVisitor;
    BasisVisitor fBasisVisitor;
    KSurfacePrimitive* fTarget;
    ValueType fValue;
};

template<class SourceShape> void KMagnetostaticBoundaryIntegrator::ComputeBoundaryIntegral(SourceShape& source)
{
    if (fBoundaryVisitor.IsDirichlet()) {
        fValue = this->Potential(&source, fTarget->GetShape()->Centroid());
    }
    else {
        double dist = (source.Centroid() - fTarget->GetShape()->Centroid()).Magnitude();

        if (dist >= 1.e-12) {
            KFieldVector field = this->MagneticField(&source, fTarget->GetShape()->Centroid());
            fValue = field.Dot(fTarget->GetShape()->Normal());
        }
        else {
            // For planar Neumann elements (here: triangles and rectangles) the following formula
            // is valid and incorporates already the Magnetic field 1./(2.*Eps0).
            // In case of conical (axialsymmetric) Neumann elements this formula has to be modified.
            // Ferenc Glueck and Daniel Hilk, March 27th 2018
            fValue = fBoundaryVisitor.Prefactor() / (2. * KEMConstants::Eps0);
        }
    }
}
}  // namespace KEMField

#endif /* KMAGNETOSTATICBOUNDARYINTEGRATOR_DEF */
