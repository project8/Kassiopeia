#ifndef KMAGNETOSTATICINTEGRATINGFIELDSOLVER_DEF
#define KMAGNETOSTATICINTEGRATINGFIELDSOLVER_DEF

#include "KIntegratingFieldSolverTemplate.hh"
#include "KSurfaceContainer.hh"

namespace KEMField
{
class MagnetostaticSingleThread;

template<class Integrator> class KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>
{
  public:
    typedef typename Integrator::Basis Basis;

    KIntegratingFieldSolver(const KSurfaceContainer& container, Integrator& integrator);
    virtual ~KIntegratingFieldSolver() = default;

    virtual void Initialize() {}

    double Potential(const KPosition& P) const;
    KFieldVector MagneticField(const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const KPosition& P) const;

    // functions without Kahan summation
    double PotentialNoKahanSum(const KPosition& P) const;
    KFieldVector MagneticFieldNoKahanSum(const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotentialNoKahanSum(const KPosition& P) const;

    double Potential(const unsigned int* SurfaceIndexSet, unsigned int SetSize, const KPosition& P) const;
    KFieldVector MagneticField(const unsigned int* SurfaceIndexSet, unsigned int SetSize, const KPosition& P) const;
    std::pair<KFieldVector, double> MagneticFieldAndPotential(const unsigned int* SurfaceIndexSet, unsigned int SetSize,
                                                              const KPosition& P) const;

  protected:
    const KSurfaceContainer& fContainer;
    Integrator& fIntegrator;

  private:
    class ShapeVisitorForPotential : public KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>
    {
      public:
        using KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>::Visit;

        ShapeVisitorForPotential(Integrator& integrator) : fIntegrator(integrator) {}

        void Visit(KTriangle& t) override
        {
            ComputePotential(t);
        }
        void Visit(KRectangle& r) override
        {
            ComputePotential(r);
        }
        void Visit(KLineSegment& l) override
        {
            ComputePotential(l);
        }
        void Visit(KConicSection& c) override
        {
            ComputePotential(c);
        }
        void Visit(KRing& r) override
        {
            ComputePotential(r);
        }
        void Visit(KTriangleGroup& t) override
        {
            ComputePotential(t);
        }
        void Visit(KRectangleGroup& r) override
        {
            ComputePotential(r);
        }
        void Visit(KLineSegmentGroup& l) override
        {
            ComputePotential(l);
        }
        void Visit(KConicSectionGroup& c) override
        {
            ComputePotential(c);
        }
        void Visit(KRingGroup& r) override
        {
            ComputePotential(r);
        }

        template<class ShapePolicy> void ComputePotential(ShapePolicy& s)
        {
            fPotential = fIntegrator.Potential(&s, fP);
        }

        void SetPosition(const KPosition& p) const
        {
            fP = p;
        }
        double GetNormalizedPotential() const
        {
            return fPotential;
        }

      private:
        mutable KPosition fP;
        double fPotential;
        Integrator& fIntegrator;
    };

    class ShapeVisitorForMagneticField : public KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>
    {
      public:
        using KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>::Visit;

        ShapeVisitorForMagneticField(Integrator& integrator) : fIntegrator(integrator) {}

        void Visit(KTriangle& t) override
        {
            ComputeMagneticField(t);
        }
        void Visit(KRectangle& r) override
        {
            ComputeMagneticField(r);
        }
        void Visit(KLineSegment& l) override
        {
            ComputeMagneticField(l);
        }
        void Visit(KConicSection& c) override
        {
            ComputeMagneticField(c);
        }
        void Visit(KRing& r) override
        {
            ComputeMagneticField(r);
        }
        void Visit(KTriangleGroup& t) override
        {
            ComputeMagneticField(t);
        }
        void Visit(KRectangleGroup& r) override
        {
            ComputeMagneticField(r);
        }
        void Visit(KLineSegmentGroup& l) override
        {
            ComputeMagneticField(l);
        }
        void Visit(KConicSectionGroup& c) override
        {
            ComputeMagneticField(c);
        }
        void Visit(KRingGroup& r) override
        {
            ComputeMagneticField(r);
        }

        template<class ShapePolicy> void ComputeMagneticField(ShapePolicy& s)
        {
            fMagneticField = fIntegrator.MagneticField(&s, fP);
        }

        void SetPosition(const KPosition& p) const
        {
            fP = p;
        }
        KFieldVector& GetNormalizedMagneticField() const
        {
            return fMagneticField;
        }

      private:
        mutable KPosition fP;
        mutable KFieldVector fMagneticField;
        Integrator& fIntegrator;
    };

    class ShapeVisitorForMagneticFieldAndPotential :
        public KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>
    {
      public:
        using KSelectiveVisitor<KShapeVisitor, typename Integrator::AcceptedShapes>::Visit;

        ShapeVisitorForMagneticFieldAndPotential(Integrator& integrator) : fIntegrator(integrator) {}

        void Visit(KTriangle& t) override
        {
            ComputeMagneticFieldAndPotential(t);
        }
        void Visit(KRectangle& r) override
        {
            ComputeMagneticFieldAndPotential(r);
        }
        void Visit(KLineSegment& l) override
        {
            ComputeMagneticFieldAndPotential(l);
        }
        void Visit(KConicSection& c) override
        {
            ComputeMagneticFieldAndPotential(c);
        }
        void Visit(KRing& r) override
        {
            ComputeMagneticFieldAndPotential(r);
        }
        void Visit(KTriangleGroup& t) override
        {
            ComputeMagneticFieldAndPotential(t);
        }
        void Visit(KRectangleGroup& r) override
        {
            ComputeMagneticFieldAndPotential(r);
        }
        void Visit(KLineSegmentGroup& l) override
        {
            ComputeMagneticFieldAndPotential(l);
        }
        void Visit(KConicSectionGroup& c) override
        {
            ComputeMagneticFieldAndPotential(c);
        }
        void Visit(KRingGroup& r) override
        {
            ComputeMagneticFieldAndPotential(r);
        }

        template<class ShapePolicy> void ComputeMagneticFieldAndPotential(ShapePolicy& s)
        {
            fMagneticFieldAndPotential = fIntegrator.MagneticFieldAndPotential(&s, fP);
        }

        void SetPosition(const KPosition& p) const
        {
            fP = p;
        }
        std::pair<KFieldVector, double>& GetNormalizedMagneticFieldAndPotential() const
        {
            return fMagneticFieldAndPotential;
        }

      private:
        mutable KPosition fP;
        mutable std::pair<KFieldVector, double> fMagneticFieldAndPotential;
        Integrator& fIntegrator;
    };

    mutable ShapeVisitorForPotential fShapeVisitorForPotential;
    mutable ShapeVisitorForMagneticField fShapeVisitorForMagneticField;
    mutable ShapeVisitorForMagneticFieldAndPotential fShapeVisitorForMagneticFieldAndPotential;
};


template<class Integrator>
KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::KIntegratingFieldSolver(
    const KSurfaceContainer& container, Integrator& integrator) :
    fContainer(container),
    fIntegrator(integrator),
    fShapeVisitorForPotential(integrator),
    fShapeVisitorForMagneticField(integrator),
    fShapeVisitorForMagneticFieldAndPotential(integrator)
{}

template<class Integrator>
double KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::Potential(const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForPotential.SetPosition(P);
    double sum = 0.;
    double c = 0.;
    double y = 0.;
    double t = 0.;
    KSurfaceContainer::iterator it;
    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForPotential);
        y = fShapeVisitorForPotential.GetNormalizedPotential() * fIntegrator.BasisValue(*it, 0) - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

template<class Integrator>
KFieldVector KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticField(const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticField.SetPosition(P);
    KFieldVector sum(0., 0., 0.);
    KFieldVector c(0., 0., 0.);
    KFieldVector y(0., 0., 0.);
    KFieldVector t(0., 0., 0.);
    KSurfaceContainer::iterator it;
    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForMagneticField);
        y = fShapeVisitorForMagneticField.GetNormalizedMagneticField() * fIntegrator.BasisValue(*it, 0) - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

template<class Integrator>
std::pair<KFieldVector, double>
KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticFieldAndPotential(const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticFieldAndPotential.SetPosition(P);

    KFieldVector sumField(0., 0., 0.);
    KFieldVector cField(0., 0., 0.);
    KFieldVector yField(0., 0., 0.);
    KFieldVector tField(0., 0., 0.);

    double sumPot = 0.;
    double cPot = 0.;
    double yPot = 0.;
    double tPot = 0.;

    KSurfaceContainer::iterator it;
    std::pair<KFieldVector, double> itFieldAndPot;
    double itBasisValue = 0.;

    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForMagneticFieldAndPotential);

        itFieldAndPot = fShapeVisitorForMagneticFieldAndPotential.GetNormalizedMagneticFieldAndPotential();
        itBasisValue = fIntegrator.BasisValue(*it, 0);

        yField = itFieldAndPot.first * itBasisValue - cField;
        tField = sumField + yField;
        cField = (tField - sumField) - yField;
        sumField = tField;

        yPot = itFieldAndPot.second * itBasisValue - cPot;
        tPot = sumPot + yPot;
        cPot = (tPot - sumPot) - yPot;
        sumPot = tPot;
    }
    return std::make_pair(sumField, sumPot);
}

template<class Integrator>
double KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::PotentialNoKahanSum(const KPosition& P) const
{
    fShapeVisitorForPotential.SetPosition(P);
    double sum = 0.;
    KSurfaceContainer::iterator it;
    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForPotential);
        sum += (fShapeVisitorForPotential.GetNormalizedPotential() * fIntegrator.BasisValue(*it, 0));
    }
    return sum;
}

template<class Integrator>
KFieldVector
KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticFieldNoKahanSum(const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticField.SetPosition(P);
    KFieldVector sum(0., 0., 0.);
    KSurfaceContainer::iterator it;
    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForMagneticField);
        sum += (fShapeVisitorForMagneticField.GetNormalizedMagneticField() * fIntegrator.BasisValue(*it, 0));
    }
    return sum;
}

template<class Integrator>
std::pair<KFieldVector, double>
KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticFieldAndPotentialNoKahanSum(
    const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticFieldAndPotential.SetPosition(P);

    KFieldVector sumField(0., 0., 0.);
    double sumPot = 0.;

    KSurfaceContainer::iterator it;
    std::pair<KFieldVector, double> itFieldAndPot;
    double itBasisValue = 0.;

    for (it = fContainer.begin<Basis>(); it != fContainer.end<Basis>(); ++it) {
        (*it)->Accept(fShapeVisitorForMagneticFieldAndPotential);

        itFieldAndPot = fShapeVisitorForMagneticFieldAndPotential.GetNormalizedMagneticFieldAndPotential();
        itBasisValue = fIntegrator.BasisValue(*it, 0);

        sumField += (itFieldAndPot.first * itBasisValue);
        sumPot += (itFieldAndPot.second * itBasisValue);
    }
    return std::make_pair(sumField, sumPot);
}

template<class Integrator>
double KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::Potential(const unsigned int* SurfaceIndexSet,
                                                                                 unsigned int SetSize,
                                                                                 const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForPotential.SetPosition(P);
    double sum = 0.;
    double c = 0.;
    double y = 0.;
    double t = 0.;
    unsigned int id;
    for (unsigned int i = 0; i < SetSize; ++i) {
        id = SurfaceIndexSet[i];
        fContainer[id]->Accept(fShapeVisitorForPotential);
        y = fShapeVisitorForPotential.GetNormalizedPotential() * fIntegrator.BasisValue(fContainer[id], 0) - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

template<class Integrator>
KFieldVector KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticField(
    const unsigned int* SurfaceIndexSet, unsigned int SetSize, const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticField.SetPosition(P);
    KFieldVector sum(0., 0., 0.);
    KFieldVector c(0., 0., 0.);
    KFieldVector y(0., 0., 0.);
    KFieldVector t(0., 0., 0.);
    unsigned int id;
    for (unsigned int i = 0; i < SetSize; ++i) {
        id = SurfaceIndexSet[i];
        fContainer[id]->Accept(fShapeVisitorForMagneticField);
        y = fShapeVisitorForMagneticField.GetNormalizedMagneticField() * fIntegrator.BasisValue(fContainer[id], 0) - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

template<class Integrator>
std::pair<KFieldVector, double>
KIntegratingFieldSolver<Integrator, MagnetostaticSingleThread>::MagneticFieldAndPotential(
    const unsigned int* SurfaceIndexSet, unsigned int SetSize, const KPosition& P) const
{
    // Kahan Sum to mitigate rounding error
    fShapeVisitorForMagneticFieldAndPotential.SetPosition(P);

    KFieldVector sumField(0., 0., 0.);
    KFieldVector cField(0., 0., 0.);
    KFieldVector yField(0., 0., 0.);
    KFieldVector tField(0., 0., 0.);

    double sumPot = 0.;
    double cPot = 0.;
    double yPot = 0.;
    double tPot = 0.;

    KSurfaceContainer::iterator it;
    std::pair<KFieldVector, double> itFieldAndPot;
    double itBasisValue = 0.;

    unsigned int id;

    for (unsigned int i = 0; i < SetSize; ++i) {
        id = SurfaceIndexSet[i];
        fContainer[id]->Accept(fShapeVisitorForMagneticFieldAndPotential);

        itFieldAndPot = fShapeVisitorForMagneticFieldAndPotential.GetNormalizedMagneticFieldAndPotential();
        itBasisValue = fIntegrator.BasisValue(*it, 0);

        yField = itFieldAndPot.first * itBasisValue - cField;
        tField = sumField + yField;
        cField = (tField - sumField) - yField;
        sumField = tField;

        yPot = itFieldAndPot.second * itBasisValue - cPot;
        tPot = sumPot + yPot;
        cPot = (tPot - sumPot) - yPot;
        sumPot = tPot;
    }
    return std::make_pair(sumField, sumPot);
}

}  // namespace KEMField

#endif /* KMAGNETOSTATICINTEGRATINGFIELDSOLVER_DEF */
