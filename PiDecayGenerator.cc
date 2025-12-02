//
// Created by bannikovev on 14.11.23.
//

#include "PiDecayGenerator.hh"


PiDecayGenerator::PiDecayGenerator() {
    rand = G4Random::getTheEngine();
}

PiDecayGenerator::~PiDecayGenerator() {}

std::vector<Particle> PiDecayGenerator::decayPi() {
    double sample = rand->flat();// Should return a pseudo random number between 0 and 1

    if (sample < PROBABILITY_OF_GG_DECAY) {
        return decayPiOnTwoPhotons();
    } else {
        return decayPiOnElectrPositrAndPhoton();
    }
}

std::vector<Particle> PiDecayGenerator::decayPiOnTwoPhotons() {
    double p = PI0_MASS / 2;//modulo of momentum

    Particle firstPhoton;
    Particle secondPhoton;

    //Разыграем угол вылета фотона
    double phi = 2 * M_PI * rand->flat();//0 < phi < 2*Pi
    double theta = acos(2 * rand->flat() - 1);//y = sin(theta), reverse function: theta = arccos(y)

    firstPhoton.energy = p;
    firstPhoton.pdgID = 22;//from PDG
    firstPhoton.momentum = G4ThreeVector(p * sin(theta) * cos(phi),
                                         p * sin(theta) * sin(phi),
                                         p * cos(theta));//spherical system

    secondPhoton.energy = p;
    secondPhoton.pdgID = 22;
    secondPhoton.momentum = -1 * firstPhoton.momentum;//ЗСИ, reverse

    return std::vector<Particle>({firstPhoton, secondPhoton});
}

std::vector<Particle> PiDecayGenerator::decayPiOnElectrPositrAndPhoton() {
    Particle photon;
    Particle electron;
    Particle positron;

    //Create a phase space where we will generate event
    //event is generated in the center-of-mass frame
    TGenPhaseSpace *event = new TGenPhaseSpace();//generator of phase space
    //Create the lorentz vector of our decay particle
    TLorentzVector W(0., 0., 0., PI0_MASS);
    //Create the array of decay product masses
    double masses[3] = {electron_mass_c2,//electron
                        electron_mass_c2,//positron
                        0};//photon
    //make the decay
    event->SetDecay(W, 3, masses);

    while (true) {
        //generate a random final state and return the weight of
        //the current event
        //!!!TLorentzVector of each decay product can be obtained
        ///using GetDecay(number of particle) (1 - e-, 2 - e+, 3 - gamma)
        double weight = event->Generate();

        if (rand->flat() < weight) {
            TLorentzVector *particleFromDecay = event->GetDecay(0);
            electron = Particle::fromDecay(11, particleFromDecay);
            particleFromDecay = event->GetDecay(1);
            positron = Particle::fromDecay(-11, particleFromDecay);
            particleFromDecay = event->GetDecay(2);
            photon = Particle::fromDecay(22, particleFromDecay);
            break;
        }
    }

    return std::vector<Particle>({photon, electron, positron});
}

