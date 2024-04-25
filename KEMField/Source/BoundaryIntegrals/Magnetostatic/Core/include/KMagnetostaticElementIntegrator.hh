/*
 * KMagnetostaticElementIntegrator.hh
 *
 *  Created on: 25 Aug 2016
 *      Author: wolfgang
 */

#ifndef KMAGNETOSTATICELEMENTINTEGRATOR_HH_
#define KMAGNETOSTATICELEMENTINTEGRATOR_HH_

#include "KSymmetryGroup.hh"
#include "KThreeVector_KEMField.hh"

namespace KEMField
{

template<class Shape> class KMagnetostaticElementIntegrator
{
  public:
    virtual ~KMagnetostaticElementIntegrator() = default;
    ;
    virtual double Potential(const Shape* source, const KPosition& P) const = 0;
    virtual KFieldVector MagneticField(const Shape* source, const KPosition& P) const = 0;
    virtual std::pair<KFieldVector, double> MagneticFieldAndPotential(const Shape* source, const KPosition& P) const;

    virtual double Potential(const KSymmetryGroup<Shape>* source, const KPosition& P) const;
    virtual KFieldVector MagneticField(const KSymmetryGroup<Shape>* source, const KPosition& P) const;
    virtual std::pair<KFieldVector, double> MagneticFieldAndPotential(const KSymmetryGroup<Shape>* source,
                                                                      const KPosition& P) const;

  private:
    typedef typename KSymmetryGroup<Shape>::ShapeCIt ShapeGroupCIt;
};


template<class Shape>
inline std::pair<KFieldVector, double>
KMagnetostaticElementIntegrator<Shape>::MagneticFieldAndPotential(const Shape* source, const KPosition& P) const
{
    return std::make_pair(MagneticField(source, P), Potential(source, P));
}

template<class Shape>
inline double KMagnetostaticElementIntegrator<Shape>::Potential(const KSymmetryGroup<Shape>* source,
                                                                const KPosition& P) const
{
    double potential = 0.;
    for (auto it = source->begin(); it != source->end(); ++it)
        potential += Potential(*it, P);
    return potential;
}

template<class Shape>
inline KFieldVector KMagnetostaticElementIntegrator<Shape>::MagneticField(const KSymmetryGroup<Shape>* source,
                                                                          const KPosition& P) const
{
    KFieldVector electricField(0., 0., 0.);
    for (auto it = source->begin(); it != source->end(); ++it)
        electricField += MagneticField(*it, P);
    return electricField;
}

template<class Shape>
inline std::pair<KFieldVector, double>
KMagnetostaticElementIntegrator<Shape>::MagneticFieldAndPotential(const KSymmetryGroup<Shape>* source,
                                                                  const KPosition& P) const
{
    std::pair<KFieldVector, double> fieldAndPotential;
    double potential(0.);
    KFieldVector electricField(0., 0., 0.);

    for (auto it = source->begin(); it != source->end(); ++it) {
        fieldAndPotential = MagneticFieldAndPotential(*it, P);
        electricField += fieldAndPotential.first;
        potential += fieldAndPotential.second;
    }

    return std::make_pair(electricField, potential);
}

} /* namespace KEMField */

#endif /* KMAGNETOSTATICELEMENTINTEGRATOR_HH_ */
