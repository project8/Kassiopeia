#include "KSReadObjectROOT.h"

using namespace std;

namespace Kassiopeia
{

KSReadObjectROOT::KSReadObjectROOT(TTree* aStructureTree, TTree* aPresenceTree, TTree* aDataTree) :
    fPresences(),
    fValid(false),
    fIndex(0),
    fStructure(aStructureTree),
    fPresence(aPresenceTree),
    fData(aDataTree)
{
    string tLabel;
    string* tLabelPointer = &tLabel;
    string** tLabelHandle = &tLabelPointer;
    fStructure->SetBranchAddress("LABEL", tLabelHandle);

    string tType;
    string* tTypePointer = &tType;
    string** tTypeHandle = &tTypePointer;
    fStructure->SetBranchAddress("TYPE", tTypeHandle);

    for (Long64_t tStructureIndex = 0; tStructureIndex < fStructure->GetEntries(); tStructureIndex++) {
        fStructure->GetEntry(tStructureIndex);

        readermsg_debug("analyzing structure with label <" << tLabel << "> and type <" << tType << ">" << eom);

        if (tType == string("bool")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSBool>(tLabel).Pointer());
            continue;
        }

        if (tType == string("unsigned_char")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSUChar>(tLabel).Pointer());
            continue;
        }
        if (tType == string("char")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSChar>(tLabel).Pointer());
            continue;
        }

        if (tType == string("unsigned_short")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSUShort>(tLabel).Pointer());
            continue;
        }
        if (tType == string("short")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSShort>(tLabel).Pointer());
            continue;
        }

        if (tType == string("unsigned_int")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSUInt>(tLabel).Pointer());
            continue;
        }
        if (tType == string("int")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSInt>(tLabel).Pointer());
            continue;
        }

        if (tType == string("unsigned_long")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSULong>(tLabel).Pointer());
            continue;
        }
        if (tType == string("long")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSLong>(tLabel).Pointer());
            continue;
        }
        if (tType == string("long long") || tType == string("long_long")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSLongLong>(tLabel).Pointer());
            continue;
        }

        if (tType == string("float")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSFloat>(tLabel).Pointer());
            continue;
        }
        if (tType == string("double")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSDouble>(tLabel).Pointer());
            continue;
        }

        if (tType == string("string")) {
            fData->SetBranchAddress(tLabel.c_str(), Add<KSString>(tLabel).Handle());
            continue;
        }

        if (tType == string("two_vector")) {
            auto& tTwoVector = Add<KSTwoVector>(tLabel);
            fData->SetBranchAddress((tLabel + string("_x")).c_str(), &(tTwoVector.Value().X()));
            fData->SetBranchAddress((tLabel + string("_y")).c_str(), &(tTwoVector.Value().Y()));
            continue;
        }
        if (tType == string("three_vector")) {
            auto& tThreeVector = Add<KSThreeVector>(tLabel);
            fData->SetBranchAddress((tLabel + string("_x")).c_str(), &(tThreeVector.Value().X()));
            fData->SetBranchAddress((tLabel + string("_y")).c_str(), &(tThreeVector.Value().Y()));
            fData->SetBranchAddress((tLabel + string("_z")).c_str(), &(tThreeVector.Value().Z()));
            continue;
        }

        if (tType == string("two_matrix")) {
            auto& tTwoMatrix = Add<KSTwoMatrix>(tLabel);
            fData->SetBranchAddress((tLabel + string("_xx")).c_str(), &(tTwoMatrix.Value().At(0,0)));
            fData->SetBranchAddress((tLabel + string("_xy")).c_str(), &(tTwoMatrix.Value().At(0,1)));
            fData->SetBranchAddress((tLabel + string("_yx")).c_str(), &(tTwoMatrix.Value().At(1,0)));
            fData->SetBranchAddress((tLabel + string("_yy")).c_str(), &(tTwoMatrix.Value().At(1,1)));
            continue;
        }
        if (tType == string("three_matrix")) {
            auto& tThreeMatrix = Add<KSThreeMatrix>(tLabel);
            fData->SetBranchAddress((tLabel + string("_xx")).c_str(), &(tThreeMatrix.Value().At(0,0)));
            fData->SetBranchAddress((tLabel + string("_xy")).c_str(), &(tThreeMatrix.Value().At(0,1)));
            fData->SetBranchAddress((tLabel + string("_xz")).c_str(), &(tThreeMatrix.Value().At(0,2)));
            fData->SetBranchAddress((tLabel + string("_yx")).c_str(), &(tThreeMatrix.Value().At(1,0)));
            fData->SetBranchAddress((tLabel + string("_yy")).c_str(), &(tThreeMatrix.Value().At(1,1)));
            fData->SetBranchAddress((tLabel + string("_yz")).c_str(), &(tThreeMatrix.Value().At(1,2)));
            fData->SetBranchAddress((tLabel + string("_zx")).c_str(), &(tThreeMatrix.Value().At(2,0)));
            fData->SetBranchAddress((tLabel + string("_zy")).c_str(), &(tThreeMatrix.Value().At(2,1)));
            fData->SetBranchAddress((tLabel + string("_zz")).c_str(), &(tThreeMatrix.Value().At(2,2)));
            continue;
        }

        readermsg(eError) << "could not analyze branch with label <" << tLabel << "> and type <" << tType << ">" << eom;
    }

    unsigned int tIndex;
    unsigned int* tIndexPointer = &tIndex;
    fPresence->SetBranchAddress("INDEX", tIndexPointer);

    unsigned int tLength;
    unsigned int* tLengthPointer = &tLength;
    fPresence->SetBranchAddress("LENGTH", tLengthPointer);

    vector<Presence> tPresences;
    unsigned int tEntry = 0;
    for (Long64_t tPresenceIndex = 0; tPresenceIndex < fPresence->GetEntries(); tPresenceIndex++) {
        fPresence->GetEntry(tPresenceIndex);

        readermsg_debug("analyzing presence with index <" << tIndex << "> and length <" << tLength << ">" << eom);

        tPresences.emplace_back(tIndex, tLength, tEntry);
        tEntry += tLength;
    }

    //rearrange presence data to avoid exponential grow of analysis time
    unsigned int tFirstIndex = 0;
    unsigned int tLastIndex = 0;
    unsigned int tFirstEntry = 0;
    unsigned int tTotalLength = 0;
    for (auto tIt = tPresences.begin(); tIt != tPresences.end(); tIt++) {
        tIndex = tIt->fIndex;
        tLength = tIt->fLength;
        tEntry = tIt->fEntry;

        if (tIt == tPresences.begin()) {
            tFirstIndex = tIndex;
            tLastIndex = tIndex;
            tFirstEntry = tEntry;
            tTotalLength = tLength;
            continue;
        }

        if (tIndex == tLastIndex + 1) {
            tTotalLength += tLength;
        }
        else {
            fPresences.emplace_back(tFirstIndex, tTotalLength, tFirstEntry);
            tFirstIndex = tIndex;
            tFirstEntry = tEntry;
            tTotalLength = tLength;
        }
        tLastIndex = tIndex;
    }
    fPresences.emplace_back(tFirstIndex, tTotalLength, tFirstEntry);
}

KSReadObjectROOT::~KSReadObjectROOT() = default;

void KSReadObjectROOT::operator++(int)
{
    fIndex++;
    for (auto& presence : fPresences) {
        if (presence.fIndex > fIndex) {
            fValid = false;
            return;
        }
        if (presence.fIndex + presence.fLength > fIndex) {
            fValid = true;
            fData->GetEntry(presence.fEntry + (fIndex - presence.fIndex));
            return;
        }
    }
    fValid = false;
    return;
}
void KSReadObjectROOT::operator--(int)
{
    fIndex--;
    for (auto& presence : fPresences) {
        if (presence.fIndex > fIndex) {
            fValid = false;
            return;
        }
        if (presence.fIndex + presence.fLength > fIndex) {
            fValid = true;
            fData->GetEntry(presence.fEntry + (fIndex - presence.fIndex));
            return;
        }
    }
    fValid = false;
    return;
}
void KSReadObjectROOT::operator<<(const unsigned int& aValue)
{
    fIndex = aValue;
    for (auto& presence : fPresences) {
        if (presence.fIndex > fIndex) {
            fValid = false;
            return;
        }
        if (presence.fIndex + presence.fLength > fIndex) {
            fValid = true;
            fData->GetEntry(presence.fEntry + (fIndex - presence.fIndex));
            return;
        }
    }
    fValid = false;
    return;
}

bool KSReadObjectROOT::Valid() const
{
    return fValid;
}
unsigned int KSReadObjectROOT::Index() const
{
    return fIndex;
}
bool KSReadObjectROOT::operator<(const unsigned int& aValue) const
{
    return (fIndex < aValue);
}
bool KSReadObjectROOT::operator<=(const unsigned int& aValue) const
{
    return (fIndex <= aValue);
}
bool KSReadObjectROOT::operator>(const unsigned int& aValue) const
{
    return (fIndex > aValue);
}
bool KSReadObjectROOT::operator>=(const unsigned int& aValue) const
{
    return (fIndex >= aValue);
}
bool KSReadObjectROOT::operator==(const unsigned int& aValue) const
{
    return (fIndex == aValue);
}
bool KSReadObjectROOT::operator!=(const unsigned int& aValue) const
{
    return (fIndex != aValue);
}

}  // namespace Kassiopeia
