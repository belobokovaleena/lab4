#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include "PiDecayGenerator.hh"


class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
    explicit MyPrimaryGeneratorAction(bool isPiDecay);
    void GeneratePrimaries(G4Event *anEvent) override;

private:
    bool isPiDecay;
    G4ParticleGun *fParticleGun;
    PiDecayGenerator *piDecay;
    G4ParticleTable *particleTable;
};


#endif //PRIMARYGENERATORACTION_HH