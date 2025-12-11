#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4SystemOfUnits.hh>
#include "G4ParticleTable.hh"
#include "MyPrimaryGeneratorAction.hh"

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    if (isPiDecay) {

       
        std::vector<Particle> particles = piDecay->decayPi();

        // ---- Распад π0 → γγ ----
        if (particles.size() == 2) {
            double theta1 = std::acos(particles[0].momentum.z() / particles[0].momentum.mag());

            // Проверяем только первый фотон
            if (theta1 <= 0.1 || theta1 >= (CLHEP::pi - 0.1)) {
                return; // событие не подходит
            }

            // Генерация фотонов
            for (int i = 0; i < 2; ++i) {
                fParticleGun->SetParticleMomentumDirection(particles[i].momentum);
                fParticleGun->SetParticleEnergy(particles[i].energy);

                G4ParticleDefinition *particleDefinition =
                    particleTable->FindParticle(particles[i].pdgID);

                fParticleGun->SetParticleDefinition(particleDefinition);
                fParticleGun->GeneratePrimaryVertex(anEvent);
            }
        }

        // ---- Распад π0 → e⁺ e⁻ γ ----
        else if (particles.size() == 3) {
            double th_e = std::acos(particles[0].momentum.z() / particles[0].momentum.mag());
            double th_p = std::acos(particles[1].momentum.z() / particles[1].momentum.mag());
            double th_g = std::acos(particles[2].momentum.z() / particles[2].momentum.mag());

            // Проверяем все три частицы
            if (th_e <= 0.1 || th_e >= (CLHEP::pi - 0.1) ||
                th_p <= 0.1 || th_p >= (CLHEP::pi - 0.1) ||
                th_g <= 0.1 || th_g >= (CLHEP::pi - 0.1)) {
                return; // хотя бы одна частица не проходит
            }

            // Генерация всех трёх частиц
            for (int i = 0; i < 3; ++i) {
                fParticleGun->SetParticleMomentumDirection(particles[i].momentum);
                fParticleGun->SetParticleEnergy(particles[i].energy);

                G4ParticleDefinition *particleDefinition =
                    particleTable->FindParticle(particles[i].pdgID);

                fParticleGun->SetParticleDefinition(particleDefinition);
                fParticleGun->GeneratePrimaryVertex(anEvent);
            }
        }
    }
    else {
        // --- обычный вариант без распада ---
        G4ThreeVector mom(0., 0., 1.);
        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleEnergy(60.0 * MeV);

        fParticleGun->SetParticleDefinition(G4Electron::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);

        fParticleGun->SetParticleDefinition(G4Gamma::Definition());
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(bool isPiDecay)
    : G4VUserPrimaryGeneratorAction(),
      isPiDecay(isPiDecay)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    piDecay = new PiDecayGenerator();
    particleTable = G4ParticleTable::GetParticleTable();
}
