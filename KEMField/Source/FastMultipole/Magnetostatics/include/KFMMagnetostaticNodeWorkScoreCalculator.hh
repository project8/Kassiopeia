#ifndef KFMMagnetostaticNodeWorkScoreCalculator_HH__
#define KFMMagnetostaticNodeWorkScoreCalculator_HH__

#include "KFMMagnetostaticNode.hh"
#include "KFMMagnetostaticTree.hh"
#include "KFMNodeActor.hh"
#include "KFMNodeFlagValueInspector.hh"
#include "KFMObjectRetriever.hh"
#include "KFMRecursiveActor.hh"

namespace KEMField
{

/*
*
*@file KFMMagnetostaticNodeWorkScoreCalculator.hh
*@class KFMMagnetostaticNodeWorkScoreCalculator
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Fri Feb 2 13:54:55 EST 2015 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KFMMagnetostaticNodeWorkScoreCalculator : public KFMNodeActor<KFMNode<KFMMagnetostaticNodeObjects>>
{
  public:
    KFMMagnetostaticNodeWorkScoreCalculator();
    ~KFMMagnetostaticNodeWorkScoreCalculator() override;

    void SetNTerms(unsigned int n_terms)
    {
        fNTerms = n_terms;
    };
    void SetDivisions(unsigned int div)
    {
        fDivisions = div;
    };
    void SetZeroMaskSize(unsigned int zmask)
    {
        fZeroMaskSize = zmask;
    };

    void SetFFTWeight(double fft_weight)
    {
        fGamma = fft_weight;
    };
    void SetSparseMatrixWeight(double mx_weight)
    {
        fTheta = mx_weight;
    };

    void ApplyAction(KFMNode<KFMMagnetostaticNodeObjects>* node) override;

    double GetNodeScore() const
    {
        return fNodeScore;
    };

  private:
    //internal class which does the actual work and accumulates the necessary data
    class SingleNodeActor : public KFMNodeActor<KFMNode<KFMMagnetostaticNodeObjects>>
    {
      public:
        SingleNodeActor()
        {
            fNMultipoleNodes = 0;
            fNonLeafMultipoleNodes = 0;
            fNPrimaryNodes = 0;
            fNSources = 0;
            fNCollocationPoints = 0;
            fNSparseMatrixElements = 0;

            fMultipoleFlagCondition.SetFlagIndex(1);
            fMultipoleFlagCondition.SetFlagValue(1);

            fLocalCoeffFlagCondition.SetFlagIndex(0);
            fLocalCoeffFlagCondition.SetFlagValue(1);
        };
        ~SingleNodeActor() override
        {
            ;
        };

        void Reset()
        {
            fNMultipoleNodes = 0;
            fNonLeafMultipoleNodes = 0;
            fNPrimaryNodes = 0;
            fNSources = 0;
            fNCollocationPoints = 0;
            fNSparseMatrixElements = 0;
        }

        void ApplyAction(KFMNode<KFMMagnetostaticNodeObjects>* node) override
        {
            if (node != nullptr) {

                if (fMultipoleFlagCondition.ConditionIsSatisfied(node)) {
                    fNMultipoleNodes += 1;
                    if (!(node->HasChildren())) {
                        fNonLeafMultipoleNodes += 1;
                    }
                }

                if (fLocalCoeffFlagCondition.ConditionIsSatisfied(node)) {
                    fNPrimaryNodes += 1;
                }

                KFMIdentitySet* id_set =
                    KFMObjectRetriever<KFMMagnetostaticNodeObjects, KFMIdentitySet>::GetNodeObject(node);
                if (id_set != nullptr) {
                    fNSources += id_set->GetSize();
                    //collocation point id lists have not yet been filled, but this is a reasonable proxy
                    fNSparseMatrixElements += (id_set->GetSize()) * (id_set->GetSize());
                    fNCollocationPoints += id_set->GetSize();
                }
            }
        }

        double GetNMultipoleNodes()
        {
            return fNMultipoleNodes;
        };
        double GetNonLeafMultipoleNodes()
        {
            return fNonLeafMultipoleNodes;
        };
        double GetNPrimaryNodes()
        {
            return fNPrimaryNodes;
        };
        double GetNSources()
        {
            return fNSources;
        };
        double GetNCollocationPoints()
        {
            return fNCollocationPoints;
        };
        double GetNSparseMatrixElements()
        {
            return fNSparseMatrixElements;
        };

      private:
        double fNMultipoleNodes;
        double fNonLeafMultipoleNodes;
        double fNPrimaryNodes;
        double fNSources;
        double fNCollocationPoints;
        double fNSparseMatrixElements;

        //condition for a node to have a multipole/local coeff expansion
        KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> fMultipoleFlagCondition;
        KFMNodeFlagValueInspector<KFMMagnetostaticNodeObjects, KFMMAGNETOSTATICS_FLAGS> fLocalCoeffFlagCondition;
    };

    void CalculateFinalScore();

    //utility
    KFMRecursiveActor<KFMNode<KFMMagnetostaticNodeObjects>> fRecursiveActor;
    SingleNodeActor fSingleNodeActor;

    //data used to calculate the score
    unsigned int fNTerms;
    unsigned int fDivisions;
    unsigned int fZeroMaskSize;

    double fNMultipoleNodes;
    double fNonLeafMultipoleNodes;
    double fNPrimaryNodes;
    double fNSources;
    double fNCollocationPoints;
    double fNSparseMatrixElements;
    double fNodeScore;


    //weights for scoring
    double fAlpha;    //weight for source multipole calcution (unused)
    double fBeta;     //weight for m2m transform (unused)
    double fGamma;    //weight for m2l transform
    double fDelta;    //weight for l2l transform (unused)
    double fEpsilon;  //weight for local coeff to field evaluation (unused)
    double fTheta;    //weight for sparse matrix evalution
};


}  // namespace KEMField


#endif /* KFMMagnetostaticNodeWorkScoreCalculator_H__ */
