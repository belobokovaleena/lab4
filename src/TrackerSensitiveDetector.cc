#include <G4Gamma.hh>
#include "TrackerSensitiveDetector.hh"

TrackerSensitiveDetector::TrackerSensitiveDetector(G4String name,
                                                   TupleID *tupleID) : G4VSensitiveDetector(name) {
    this->tupleID = tupleID;
}

TrackerSensitiveDetector::~TrackerSensitiveDetector() {}

G4bool TrackerSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *history) {
    auto aTrack = aStep->GetTrack();
    //Как мы видели в трековый детектор летит много разных частиц, но самих электронов первичных,
    //которых мы хотим увидеть довольно мало => наш трековый детектор будет довольно зашумлен
    //На практике производят различные методы, чтобы определить, где был шум,
    //создают пороги срабатывания всякие, например, ячейка сработала, если в ней выделилось достаточно энергии
    //Но нам тут просто, так как это симуляция и мы можем указать для убирания шума 2 вещи:
    bool isThisParticlePrimary = aTrack->GetParentID() == 0;
    bool isThisParticleNotGamma = aTrack->GetDefinition() != G4Gamma::Definition();
    if (isThisParticlePrimary && isThisParticleNotGamma) {
//        std::cout << aTrack->GetVolume()->GetCopyNo() << " ";
//        std::cout << aTrack->GetTouchable()->GetVolume(1)->GetName() << " ";
//        std::cout << aTrack->GetTouchable()->GetVolume(2)->GetName() << " ";
//        std::cout << aTrack->GetTouchable()->GetVolume(3)->GetName() << "\n";

        int detectorNumber = aTrack->GetTouchable()->GetVolume(3)->GetCopyNo();

        TrackerData trackerData;
        trackerData.detector = detectorNumber;
        trackerData.position = aTrack->GetPosition();
        trackerData.time = aTrack->GetGlobalTime();
        trackerData.energyDeposit = aStep->GetTotalEnergyDeposit();

        data.push_back(trackerData);
    }
    
    return true;

}

void TrackerSensitiveDetector::Initialize(G4HCofThisEvent *event) {
//    std::cout << "This is start of " << event << "\n";
    G4VSensitiveDetector::Initialize(event);

    data.clear();
}

void TrackerSensitiveDetector::EndOfEvent(G4HCofThisEvent *event) {
//    std::cout << "This is end of " << event << "\n";
    G4VSensitiveDetector::EndOfEvent(event);
//    for (int i = 0; i < data.size(); ++i) {
//        std::cout << "========== " << i << " ==========\n";
//        std::cout << "address: det=" << data[i].address.detector
//                  << " segment=" << data[i].address.segment
//                  << " layer=" << data[i].address.layer
//                  << " cell=" << data[i].address.cell
//                  << "\n";
//        std::cout << "time=" << data[i].time << "\tenergy=" << data[i].energyDeposit << "\n";
//
//    }

    auto analysisManager = tupleID->analysisManager;
    for (int i = 0; i < data.size(); i++){
        auto currentData = data[i];
        int ID;
        if (currentData.detector == 0){
            ID = tupleID->rightTrackID;
        }
        else{
            ID = tupleID->leftTrackID;
        }
//        std::cout << "_________" << ID << "_________\n";
        analysisManager->FillNtupleDColumn(ID, 0, currentData.position.getX());
        analysisManager->FillNtupleDColumn(ID, 1, currentData.position.getY());
        analysisManager->FillNtupleDColumn(ID, 2, currentData.position.getZ());
        analysisManager->FillNtupleDColumn(ID, 3, currentData.time);
        analysisManager->AddNtupleRow(ID);

    }

    analysisManager->AddNtupleRow(tupleID->leftTrackID);
    analysisManager->AddNtupleRow(tupleID->rightTrackID);
}




