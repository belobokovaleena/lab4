#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4SystemOfUnits.hh>
#include "G4ParticleTable.hh"
#include "MyPrimaryGeneratorAction.hh"

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    if (isPiDecay) {
        std::vector<Particle> particles = piDecay->decayPi();

        for (int iParticle = 0; iParticle < particles.size(); ++iParticle) {
            fParticleGun->SetParticleMomentumDirection(particles[iParticle].momentum);
            fParticleGun->SetParticleEnergy(particles[iParticle].energy);
            G4ParticleDefinition *particleDefinition = particleTable->FindParticle(particles[iParticle].pdgID);
            fParticleGun->SetParticleDefinition(particleDefinition);
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
    } else {
        G4ThreeVector mom(0., 0., 1.);

        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleEnergy(60.0 * MeV);

        // Генерируем первую первичную частицы для события
        fParticleGun->SetParticleDefinition(G4Electron::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);

        // Генерируем вторую первичную частицу для события
        fParticleGun->SetParticleDefinition(G4Gamma::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(bool isPiDecay) : G4VUserPrimaryGeneratorAction(), isPiDecay(isPiDecay) {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    piDecay = new PiDecayGenerator();
    particleTable = G4ParticleTable::GetParticleTable();
}
