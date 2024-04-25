#ifndef KFMMagnetostaticElementContainerBase_HH__
#define KFMMagnetostaticElementContainerBase_HH__

#include "KFMBall.hh"
#include "KFMBasisData.hh"
#include "KFMMagnetostaticElement.hh"
#include "KFMObjectContainer.hh"
#include "KFMPointCloud.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticElementContainerBase.hh
*@class KFMMagnetostaticElementContainerBase
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Aug 28 19:01:39 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/

template<unsigned int SpatialDimension, unsigned int BasisDimension> class KFMMagnetostaticElementContainerBase
{
  public:
    KFMMagnetostaticElementContainerBase()
    {
        ;
    };
    virtual ~KFMMagnetostaticElementContainerBase()
    {
        ;
    };

    virtual unsigned int GetNElements() const = 0;

    virtual void AddMagnetostaticElement(const KFMMagnetostaticElement<SpatialDimension, BasisDimension>& elem) = 0;
    virtual KFMMagnetostaticElement<SpatialDimension, BasisDimension> GetMagnetostaticElement(unsigned int id) = 0;

    virtual KFMPointCloud<SpatialDimension>* GetPointCloud(unsigned int id) = 0;
    virtual KFMBall<SpatialDimension>* GetBoundingBall(unsigned int id) = 0;
    virtual KFMBasisData<BasisDimension>* GetBasisData(unsigned int id) = 0;
    virtual KFMPoint<SpatialDimension>* GetCentroid(unsigned int id) = 0;

    virtual const KFMPointCloud<SpatialDimension>* GetPointCloud(unsigned int id) const = 0;
    virtual const KFMBall<SpatialDimension>* GetBoundingBall(unsigned int id) const = 0;
    virtual const KFMBasisData<BasisDimension>* GetBasisData(unsigned int id) const = 0;
    virtual const KFMPoint<SpatialDimension>* GetCentroid(unsigned int id) const = 0;
    virtual double GetAspectRatio(unsigned int id) const = 0;

    virtual void ClearBoundingBalls()
    {
        ;
    };
    virtual void Clear()
    {
        ;
    };

    virtual KFMObjectContainer<KFMPointCloud<SpatialDimension>>* GetPointCloudContainer() = 0;
    virtual KFMObjectContainer<KFMBall<SpatialDimension>>* GetBoundingBallContainer() = 0;
    virtual KFMObjectContainer<KFMBasisData<BasisDimension>>* GetChargeDensityContainer() = 0;
    virtual KFMObjectContainer<KFMPoint<SpatialDimension>>* GetCentroidContainer() = 0;

    virtual const KFMObjectContainer<KFMPointCloud<SpatialDimension>>* GetPointCloudContainer() const = 0;
    virtual const KFMObjectContainer<KFMBall<SpatialDimension>>* GetBoundingBallContainer() const = 0;
    virtual const KFMObjectContainer<KFMBasisData<BasisDimension>>* GetChargeDensityContainer() const = 0;
    virtual const KFMObjectContainer<KFMPoint<SpatialDimension>>* GetCentroidContainer() const = 0;

  private:
};

}  // namespace KEMField

#endif /* KFMMagnetostaticElementContainerBase_H__ */
