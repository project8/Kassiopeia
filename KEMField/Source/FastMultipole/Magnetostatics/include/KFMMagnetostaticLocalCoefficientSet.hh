#ifndef KFMMagnetostaticLocalCoefficientSet_HH__
#define KFMMagnetostaticLocalCoefficientSet_HH__

#include "KFMScalarMultipoleExpansion.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticLocalCoefficientSet.hh
*@class KFMMagnetostaticLocalCoefficientSet
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Wed Sep  4 10:06:47 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticLocalCoefficientSet : public KFMScalarMultipoleExpansion
{
  public:
    KFMMagnetostaticLocalCoefficientSet();
    ~KFMMagnetostaticLocalCoefficientSet() override;
    KFMMagnetostaticLocalCoefficientSet(const KFMMagnetostaticLocalCoefficientSet& copyObject) :
        KFMScalarMultipoleExpansion(copyObject)
    {
        ;
    };
    KFMMagnetostaticLocalCoefficientSet& operator=(const KFMMagnetostaticLocalCoefficientSet& copyObject) = default;
    ;

    std::string ClassName() const override;

    void DefineOutputNode(KSAOutputNode* node) const override;
    void DefineInputNode(KSAInputNode* node) override;

  private:
};

template<typename Stream> Stream& operator>>(Stream& s, KFMMagnetostaticLocalCoefficientSet& aData)
{
    s.PreStreamInAction(aData);

    unsigned int size;
    s >> size;

    std::vector<double>* r_mom = aData.GetRealMoments();
    std::vector<double>* i_mom = aData.GetImaginaryMoments();

    r_mom->resize(size);
    i_mom->resize(size);

    for (unsigned int i = 0; i < size; i++) {
        s >> (*r_mom)[i];
        s >> (*i_mom)[i];
    }

    s.PostStreamInAction(aData);
    return s;
}

template<typename Stream> Stream& operator<<(Stream& s, const KFMMagnetostaticLocalCoefficientSet& aData)
{
    s.PreStreamOutAction(aData);

    const std::vector<double>* r_mom = aData.GetRealMoments();
    const std::vector<double>* i_mom = aData.GetImaginaryMoments();

    unsigned int size = r_mom->size();
    s << size;

    for (unsigned int i = 0; i < size; i++) {
        s << (*r_mom)[i];
        s << (*i_mom)[i];
    }

    s.PostStreamOutAction(aData);

    return s;
}


DefineKSAClassName(KFMMagnetostaticLocalCoefficientSet)

}  // namespace KEMField


#endif /* KFMMagnetostaticLocalCoefficientSet_H__ */
