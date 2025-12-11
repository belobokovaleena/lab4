#ifndef TRACKERSENSDET_HH
#define TRACKERSENSDET_HH

#include <G4VSensitiveDetector.hh>
#include "TupleID.hh"
#include "MyDetectorConstruction.hh"

struct TrackerData {
    int detector;
    G4ThreeVector position;
    double time;
    double energyDeposit;
};

class TrackerSensitiveDetector : public G4VSensitiveDetector {
public:
    TrackerSensitiveDetector(G4String name, TupleID *tupleID);

    ~TrackerSensitiveDetector();

    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *history);

    virtual void Initialize(G4HCofThisEvent *event);

    virtual void EndOfEvent(G4HCofThisEvent *event);
private:
    TupleID *tupleID;
    std::vector<TrackerData> data;
};

#endif
