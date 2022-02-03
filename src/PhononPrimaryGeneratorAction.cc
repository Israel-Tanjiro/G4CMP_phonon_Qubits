/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/src/PhononPrimaryGeneratorAction.cc
/// \brief Implementation of the PhononPrimaryGeneratorAction class
//
// $Id: e75f788b103aef810361fad30f75077829192c13 $
//
// 20140519  Allow the user to specify phonon type by name in macro; if
//	     "geantino" is set, use random generator to select.

#include "PhononPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4Geantino.hh"
#include "G4ParticleGun.hh"
#include "G4RandomDirection.hh"
#include "G4PhononTransFast.hh"
#include "G4PhononTransSlow.hh"
#include "G4PhononLong.hh"
#include "G4SystemOfUnits.hh"
#include "G4CMPDriftElectron.hh"
#include "G4CMPDriftHole.hh"
#include "G4Proton.hh"

using namespace std;

PhononPrimaryGeneratorAction::PhononPrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  //G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  //G4String particleName="muon";
  //G4ParticleDefinition *particle = particleTable->FindParticle("muonmnus");
  //fParticleGun->SetParticlePosition(pos);
  //fParticleGun->SetParticleMomentumDirection(mom);
  //
  //fParticleGun->SetParticleDefinition(proton::Definition());
  // default particle kinematics ("geantino" triggers random phonon choice)
//  fParticleGun->SetParticleDefinition(G4Geantino::Definition());
  //fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));

  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.*cm,0.035*cm));
  fParticleGun->SetParticleEnergy(10*eV);// The initial energy
  //fParticleGun->SetParticleMomentum(100.*GeV);
  //fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.0,0.0,0.0));
  //fParticleGun->SetParticleEnergy(0.0075*eV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


PhononPrimaryGeneratorAction::~PhononPrimaryGeneratorAction() {
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void PhononPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  fParticleGun->SetParticleDefinition(G4CMPDriftElectron::Definition());
  fParticleGun->GeneratePrimaryVertex(anEvent);

  //fParticleGun->GetParticleDefinition() ==G4Proton::Definition();
  //fParticleGun->SetParticleDefinition(G4Proton::Definition());
  //fParticleGun->GeneratePrimaryVertex(anEvent);

if (fParticleGun->GetParticleDefinition() == G4Geantino::Definition()) {
    fParticleGun->SetParticleDefinition(G4CMPDriftElectron::Definition());
    fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleGun->SetParticleDefinition(G4CMPDriftHole::Definition());
      fParticleGun->GeneratePrimaryVertex(anEvent);

    G4double selector = G4UniformRand();
  if (selector<0.53539) {
      fParticleGun->SetParticleDefinition(G4PhononTransSlow::Definition());
    } else if (selector<0.90217) {
      fParticleGun->SetParticleDefinition(G4PhononTransFast::Definition());
    } else {
      fParticleGun->SetParticleDefinition(G4PhononLong::Definition());
    }
  }

  fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
