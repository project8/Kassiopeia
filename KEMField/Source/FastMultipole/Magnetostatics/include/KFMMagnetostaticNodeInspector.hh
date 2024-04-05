#ifndef KFMMagnetostaticNodeInspector_H
#define KFMMagnetostaticNodeInspector_H


#include "KFMMagnetostaticNode.hh"
#include "KFMNodeActor.hh"
#include "KFMObjectRetriever.hh"

#include <sstream>
#include <string>
#include <vector>


namespace KEMField
{

/**
*
*@file KFMMagnetostaticNodeInspector.hh
*@class KFMMagnetostaticNodeInspector
*@brief
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Thu Aug 23 22:35:12 EDT 2012 J. Barrett (barrettj@mit.edu) First Version
*
*/

class KFMMagnetostaticNodeInspector : public KFMNodeActor<KFMMagnetostaticNode>
{
  public:
    KFMMagnetostaticNodeInspector();
    ~KFMMagnetostaticNodeInspector() override;

    void ApplyAction(KFMMagnetostaticNode* node) override;
    void Print();

  private:
    double fNumberOfNodes;

    std::vector<double> fNumberOfNodesAtLevel;

    std::vector<double> fNumberOfElementsAtLevel;

    std::vector<std::vector<double>> fElementSizeAtLevel;

    std::vector<std::vector<double>> fDirectCallDistribution;
};

}  // namespace KEMField

#endif /* KFMMagnetostaticNodeInspector_H */
