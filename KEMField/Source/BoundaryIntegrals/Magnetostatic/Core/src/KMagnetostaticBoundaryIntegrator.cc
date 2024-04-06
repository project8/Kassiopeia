#include "KMagnetostaticBoundaryIntegrator.hh"

//#include "KMagnetostaticAnalyticConicSectionIntegrator.hh"
#include "KMagnetostaticAnalyticLineSegmentIntegrator.hh"
//#include "KMagnetostaticAnalyticRectangleIntegrator.hh"
//#include "KMagnetostaticAnalyticRingIntegrator.hh"
//#include "KMagnetostaticAnalyticTriangleIntegrator.hh"


namespace KEMField
{
KMagnetostaticBoundaryIntegrator::KMagnetostaticBoundaryIntegrator(
//    const std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>>& triangleIntegrator,
//    const std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>>& rectangleIntegrator,
    const std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>>& lineSegmentIntegrator :
//    const std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>>& conicSectionIntegrator,
//    const std::shared_ptr<KMagnetostaticElementIntegrator<KRing>>& ringIntegrator) :
//    fTriangleIntegrator(triangleIntegrator),
//    fRectangleIntegrator(rectangleIntegrator),
    fLineSegmentIntegrator(lineSegmentIntegrator),
//    fConicSectionIntegrator(conicSectionIntegrator),
//    fRingIntegrator(ringIntegrator),
    fShapeVisitor(*this)

{}


KEMField::KMagnetostaticBoundaryIntegrator::KMagnetostaticBoundaryIntegrator(
    const KMagnetostaticBoundaryIntegrator& integrator) :
//    KMagnetostaticBoundaryIntegrator(integrator.fTriangleIntegrator, integrator.fRectangleIntegrator,
//                                     integrator.fLineSegmentIntegrator, integrator.fConicSectionIntegrator,
//                                     integrator.fRingIntegrator)
    KMagnetostaticBoundaryIntegrator(integrator.fLineSegmentIntegrator)
{}

KMagnetostaticBoundaryIntegrator&
KEMField::KMagnetostaticBoundaryIntegrator::operator=(const KMagnetostaticBoundaryIntegrator& integrator)
{
    if (this == &integrator)
        return *this;

//    fTriangleIntegrator = integrator.fTriangleIntegrator;
//    fRectangleIntegrator = integrator.fRectangleIntegrator;
    fLineSegmentIntegrator = integrator.fLineSegmentIntegrator;
//    fConicSectionIntegrator = integrator.fConicSectionIntegrator;
//    fRingIntegrator = integrator.fRingIntegrator;
    return *this;
}

void KMagnetostaticBoundaryIntegrator::BoundaryVisitor::Visit(KDirichletBoundary& boundary)
{
    fIsDirichlet = true;
    fPrefactor = 1.;
    fBoundaryValue = static_cast<DirichletBoundary&>(boundary).GetBoundaryValue();
}

void KMagnetostaticBoundaryIntegrator::BoundaryVisitor::Visit(KNeumannBoundary& boundary)
{
    fIsDirichlet = false;
    fPrefactor = ((1. + static_cast<NeumannBoundary&>(boundary).GetNormalBoundaryFlux()) /
                  (1. - static_cast<NeumannBoundary&>(boundary).GetNormalBoundaryFlux()));
    fBoundaryValue = 0.;
}

void KMagnetostaticBoundaryIntegrator::BasisVisitor::Visit(KMagnetostaticBasis& basis)
{
    fBasisValue = &(basis.GetSolution());
}

KMagnetostaticBasis::ValueType KMagnetostaticBoundaryIntegrator::BoundaryIntegral(KSurfacePrimitive* source,
                                                                                  unsigned int /*unused*/,
                                                                                  KSurfacePrimitive* target,
                                                                                  unsigned int /*unused*/)
{
    fTarget = target;
    target->Accept(fBoundaryVisitor);
    source->Accept(fShapeVisitor);
    return fValue;
}

KMagnetostaticBasis::ValueType KMagnetostaticBoundaryIntegrator::BoundaryValue(KSurfacePrimitive* surface,
                                                                               unsigned int /*unused*/)
{
    surface->Accept(fBoundaryVisitor);
    return fBoundaryVisitor.GetBoundaryValue();
}

KMagnetostaticBasis::ValueType& KMagnetostaticBoundaryIntegrator::BasisValue(KSurfacePrimitive* surface,
                                                                             unsigned int /*unused*/)
{
    surface->Accept(fBasisVisitor);
    return fBasisVisitor.GetBasisValue();
}

std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>> KMagnetostaticBoundaryIntegrator::GetTriangleIntegrator()
{
    return fTriangleIntegrator;
}

void KMagnetostaticBoundaryIntegrator::SetTriangleIntegrator(
    const std::shared_ptr<KMagnetostaticElementIntegrator<KTriangle>>& triangleIntegrator)
{
    fTriangleIntegrator = triangleIntegrator;
}

double KMagnetostaticBoundaryIntegrator::Potential(const KTriangle* source, const KPosition& P) const
{
    return fTriangleIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KTriangle* source, const KPosition& P) const
{
    return fTriangleIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KTriangle* source,
                                                                                            const KPosition& P) const
{
    return fTriangleIntegrator->MagneticFieldAndPotential(source, P);
}

double KMagnetostaticBoundaryIntegrator::Potential(const KTriangleGroup* source, const KPosition& P) const
{
    return fTriangleIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KTriangleGroup* source, const KPosition& P) const
{
    return fTriangleIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double>
KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KTriangleGroup* source, const KPosition& P) const
{
    return fTriangleIntegrator->MagneticFieldAndPotential(source, P);
}

std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>> KMagnetostaticBoundaryIntegrator::GetRectangleIntegrator()
{
    return fRectangleIntegrator;
}

void KMagnetostaticBoundaryIntegrator::SetRectangleIntegrator(
    const std::shared_ptr<KMagnetostaticElementIntegrator<KRectangle>>& RectangleIntegrator)
{
    fRectangleIntegrator = RectangleIntegrator;
}

double KMagnetostaticBoundaryIntegrator::Potential(const KRectangle* source, const KPosition& P) const
{
    return fRectangleIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KRectangle* source, const KPosition& P) const
{
    return fRectangleIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KRectangle* source,
                                                                                            const KPosition& P) const
{
    return fRectangleIntegrator->MagneticFieldAndPotential(source, P);
}

double KMagnetostaticBoundaryIntegrator::Potential(const KRectangleGroup* source, const KPosition& P) const
{
    return fRectangleIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KRectangleGroup* source, const KPosition& P) const
{
    return fRectangleIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double>
KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KRectangleGroup* source, const KPosition& P) const
{
    return fRectangleIntegrator->MagneticFieldAndPotential(source, P);
}

std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>>
KMagnetostaticBoundaryIntegrator::GetLineSegmentIntegrator()
{
    return fLineSegmentIntegrator;
}

void KMagnetostaticBoundaryIntegrator::SetLineSegmentIntegrator(
    const std::shared_ptr<KMagnetostaticElementIntegrator<KLineSegment>>& LineSegmentIntegrator)
{
    fLineSegmentIntegrator = LineSegmentIntegrator;
}

double KMagnetostaticBoundaryIntegrator::Potential(const KLineSegment* source, const KPosition& P) const
{
    return fLineSegmentIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KLineSegment* source, const KPosition& P) const
{
    return fLineSegmentIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KLineSegment* source,
                                                                                            const KPosition& P) const
{
    return fLineSegmentIntegrator->MagneticFieldAndPotential(source, P);
}

double KMagnetostaticBoundaryIntegrator::Potential(const KLineSegmentGroup* source, const KPosition& P) const
{
    return fLineSegmentIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KLineSegmentGroup* source, const KPosition& P) const
{
    return fLineSegmentIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double>
KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KLineSegmentGroup* source, const KPosition& P) const
{
    return fLineSegmentIntegrator->MagneticFieldAndPotential(source, P);
}

std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>>
KMagnetostaticBoundaryIntegrator::GetConicSectionIntegrator()
{
    return fConicSectionIntegrator;
}

void KMagnetostaticBoundaryIntegrator::SetConicSectionIntegrator(
    const std::shared_ptr<KMagnetostaticElementIntegrator<KConicSection>>& ConicSectionIntegrator)
{
    fConicSectionIntegrator = ConicSectionIntegrator;
}

double KMagnetostaticBoundaryIntegrator::Potential(const KConicSection* source, const KPosition& P) const
{
    return fConicSectionIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KConicSection* source, const KPosition& P) const
{
    return fConicSectionIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KConicSection* source,
                                                                                            const KPosition& P) const
{
    return fConicSectionIntegrator->MagneticFieldAndPotential(source, P);
}

double KMagnetostaticBoundaryIntegrator::Potential(const KConicSectionGroup* source, const KPosition& P) const
{
    return fConicSectionIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KConicSectionGroup* source, const KPosition& P) const
{
    return fConicSectionIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double>
KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KConicSectionGroup* source, const KPosition& P) const
{
    return fConicSectionIntegrator->MagneticFieldAndPotential(source, P);
}


std::shared_ptr<KMagnetostaticElementIntegrator<KRing>> KMagnetostaticBoundaryIntegrator::GetRingIntegrator()
{
    return fRingIntegrator;
}

void KMagnetostaticBoundaryIntegrator::SetRingIntegrator(
    const std::shared_ptr<KMagnetostaticElementIntegrator<KRing>>& RingIntegrator)
{
    fRingIntegrator = RingIntegrator;
}

double KMagnetostaticBoundaryIntegrator::Potential(const KRing* source, const KPosition& P) const
{
    return fRingIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KRing* source, const KPosition& P) const
{
    return fRingIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KRing* source,
                                                                                            const KPosition& P) const
{
    return fRingIntegrator->MagneticFieldAndPotential(source, P);
}

double KMagnetostaticBoundaryIntegrator::Potential(const KRingGroup* source, const KPosition& P) const
{
    return fRingIntegrator->Potential(source, P);
}

KFieldVector KMagnetostaticBoundaryIntegrator::MagneticField(const KRingGroup* source, const KPosition& P) const
{
    return fRingIntegrator->MagneticField(source, P);
}

std::pair<KFieldVector, double> KMagnetostaticBoundaryIntegrator::MagneticFieldAndPotential(const KRingGroup* source,
                                                                                            const KPosition& P) const
{
    return fRingIntegrator->MagneticFieldAndPotential(source, P);
}

}  // namespace KEMField
