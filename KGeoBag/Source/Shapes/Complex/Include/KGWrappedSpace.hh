#ifndef KGWRAPPEDSPACE_HH_
#define KGWRAPPEDSPACE_HH_

#include "KGCore.hh"
#include "KGWrappedSurface.hh"

#include <limits>

namespace KGeoBag
{
template<class XObject> class KGWrappedSpace : public KGVolume
{
  public:
    class Visitor
    {
      public:
        Visitor() = default;
        virtual ~Visitor() = default;

        virtual void VisitWrappedSpace(KGWrappedSpace<XObject>* aWrappedSpace) = 0;
    };

  public:
    KGWrappedSpace();
    KGWrappedSpace(XObject* anObject);
    KGWrappedSpace(const std::shared_ptr<XObject>& anObject);
    KGWrappedSpace(const KGWrappedSpace& aCopy);
    ~KGWrappedSpace() override;

    static std::string Name()
    {
        return "wrapped_" + XObject::Name() + "_space";
    }

  public:
    void SetObject(std::shared_ptr<XObject> anObject);
    std::shared_ptr<XObject> GetObject() const;

  public:
    void VolumeInitialize(BoundaryContainer& aBoundaryContainer) const override;
    void VolumeAccept(KGVisitor* aVisitor) override;
    bool VolumeOutside(const katrin::KThreeVector& aPoint) const override;
    katrin::KThreeVector VolumePoint(const katrin::KThreeVector& aPoint) const override;
    katrin::KThreeVector VolumeNormal(const katrin::KThreeVector& aPoint) const override;

  protected:
    std::shared_ptr<XObject> fObject;
};

template<class XObject> KGWrappedSpace<XObject>::KGWrappedSpace() : KGVolume(), fObject(new XObject) {}

template<class XObject> KGWrappedSpace<XObject>::KGWrappedSpace(XObject* anObject) : KGVolume(), fObject(anObject) {}

template<class XObject> KGWrappedSpace<XObject>::KGWrappedSpace(const std::shared_ptr<XObject>& anObject) : KGVolume()
{
    fObject = anObject;
}

template<class XObject> KGWrappedSpace<XObject>::KGWrappedSpace(const KGWrappedSpace& aCopy) : KGVolume(aCopy)
{
    fObject = aCopy.fObject;
}

template<class XObject> KGWrappedSpace<XObject>::~KGWrappedSpace() = default;

template<class XObject> void KGWrappedSpace<XObject>::SetObject(std::shared_ptr<XObject> anObject)
{
    fObject = anObject;
    return;
}

template<class XObject> std::shared_ptr<XObject> KGWrappedSpace<XObject>::GetObject() const
{
    return fObject;
}

template<class XObject> void KGWrappedSpace<XObject>::VolumeInitialize(BoundaryContainer& aBoundaryContainer) const
{
    fObject->Initialize();
    auto tSurface = std::shared_ptr<KGBoundary>(fObject);
    aBoundaryContainer.push_back(tSurface);
    return;
}

template<class XObject> void KGWrappedSpace<XObject>::VolumeAccept(KGVisitor* aVisitor)
{
    auto* tWrappedSpaceVisitor = dynamic_cast<typename KGWrappedSpace<XObject>::Visitor*>(aVisitor);
    if (tWrappedSpaceVisitor != nullptr) {
        tWrappedSpaceVisitor->VisitWrappedSpace(this);
        return;
    }
    KGVolume::VolumeAccept(aVisitor);
    return;
}

template<class XObject> bool KGWrappedSpace<XObject>::VolumeOutside(const katrin::KThreeVector& aQuery) const
{
    if (fObject->ContainsPoint((const double*) (aQuery)) == true) {
        return false;
    }
    return true;
}

template<class XObject>
katrin::KThreeVector KGWrappedSpace<XObject>::VolumePoint(const katrin::KThreeVector& aQuery) const
{
    katrin::KThreeVector tPoint;
    fObject->DistanceTo((const double*) (aQuery), (double*) (tPoint));

    return tPoint;
}

template<class XObject>
katrin::KThreeVector KGWrappedSpace<XObject>::VolumeNormal(const katrin::KThreeVector& aQuery) const
{
    katrin::KThreeVector tNormal;
    fObject->DistanceTo((const double*) (aQuery), nullptr, (double*) (tNormal));

    return tNormal;
}
}  // namespace KGeoBag

#endif
