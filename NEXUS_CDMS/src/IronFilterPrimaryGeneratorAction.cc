//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file IronFilterPrimaryGeneratorAction.cc
/// \brief Implementation of the IronFilterPrimaryGeneratorAction class

#include "IronFilterPrimaryGeneratorAction.hh"
#include "IronFilterPrimaryMessenger.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisExtent.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterPrimaryGeneratorAction::IronFilterPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fVerbosity(0),
  fParticleGun(0),
  fEnvelopeBox(0),
  fGeneratorPosition(0),
  fParticleName("neutron"),
  fParticleEnergy(2.45*MeV),
  fCosThetaMin(-1.0),
  fCosThetaMax( 1.0),
  fPhiMin(-CLHEP::pi*rad),
  fPhiMax( CLHEP::pi*rad),
  fSourceSize( 0.2*cm),
  fMisalignment(0.0,0.0,0.0),
  fUseLineBeam(FALSE)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
//  fParticleName = G4String("neutron");
  G4ParticleDefinition* particle
    = particleTable->FindParticle(fParticleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(fParticleEnergy);
//
  fGeneratorPosition = new G4ThreeVector(0.,0.,0.);
  fMessenger = new IronFilterPrimaryMessenger(this);
//
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterPrimaryGeneratorAction::~IronFilterPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

//  G4double envSizeXY = 0;
//  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());

  }

  bool debug = (fVerbosity >= 2) ;
  if ( fEnvelopeBox ) {
//    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
//    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("IronFilterPrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }
//
//  Climb the ancestry to get the D-D generator position in the
//  world coordinate system.
//
  G4ThreeVector sourcePos(0.0,0.0,0.);
  G4VPhysicalVolume * thisVolume = 0;
//  if(thisVolume = G4PhysicalVolumeStore::GetInstance()->GetVolume("DDGener")){
  if(thisVolume = G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource")){
    sourcePos = thisVolume->GetTranslation();
    if(debug){
      G4cout << "Current volume: " << thisVolume->GetName()
             << ", translation: "  << thisVolume->GetTranslation() << G4endl;
    }
    while(thisVolume->GetName() != "CleanRoom"){
      if(debug){
        G4cout << "Current volume: " << thisVolume->GetName() << G4endl;
      }
      G4LogicalVolume * motherVolume = thisVolume->GetMotherLogical();
      G4String motherName = motherVolume->GetName();
      thisVolume =
         G4PhysicalVolumeStore::GetInstance()->GetVolume(motherName);
      if(debug){
        G4cout << "Current volume: " << thisVolume->GetName()
            << ", translation: "  << thisVolume->GetTranslation() << G4endl;
      }
      G4ThreeVector thisPosition = thisVolume->GetTranslation();
      sourcePos += thisPosition;
    }
  }
  *fGeneratorPosition = sourcePos;
  if(debug){
    G4cout << "Generator position: " << *fGeneratorPosition << G4endl;
  }
//
//   Smear the location uniformly over a transverse circle with a
//   characteristic radius.
//
  G4double radius = fSourceSize * sqrt(G4UniformRand());
  G4double ranPhi = CLHEP::twopi * G4UniformRand();
  sourcePos.setX(fGeneratorPosition->x() + radius * cos(ranPhi));
  sourcePos.setY(fGeneratorPosition->y() + radius * sin(ranPhi));
//  sourcePos.setX(fGeneratorPosition->x() + fSourceSize * (G4UniformRand()-0.5));
//  sourcePos.setY(fGeneratorPosition->y() + fSourceSize * (G4UniformRand()-0.5));
  sourcePos.setZ(fGeneratorPosition->z());
//
//  Finally move it by a misalignment location
//
  sourcePos += fMisalignment;
//
  G4double costh = -1.0;
  G4double phi   =  0.0;
  if(!fUseLineBeam){
    costh = fCosThetaMin +
                    (fCosThetaMax - fCosThetaMin) * G4UniformRand();
    phi   =  fPhiMin + (fPhiMax - fPhiMin) * G4UniformRand();
  }
  G4double sinth = sqrt(1.0 - costh * costh);
  G4double px = cos(phi) * sinth;
  G4double py = sin(phi) * sinth;
  G4double pz = costh;

  if(debug){
    G4cout << "    Event position: " << sourcePos << G4endl;
  }
  fParticleGun->SetParticlePosition(sourcePos);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  fParticleGun->SetParticleEnergy(fParticleEnergy);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
    = particleTable->FindParticle(fParticleName);
  fParticleGun->SetParticleDefinition(particle);
  // get analysis manager
  //auto analysisManager = G4AnalysisManager::Instance();
  // fill histogram
  //analysisManager->FillH3(0,px,py,pz);
  //analysisManager->FillH3(1,sourcePos.x(),sourcePos.y(),sourcePos.z());

  fParticleGun->GeneratePrimaryVertex(anEvent);
//  if(debug){
//     G4cout << ddGen->GetName() << "  " << ddGen->GetTranslation()
//            << G4endl;
//     G4cout << shield->GetName() << "  " << shield->GetTranslation()
//            << G4endl;
//     G4cout << interior->GetName() << "  " << interior->GetTranslation()
//            << G4endl;
//     G4cout << cleanroom->GetName() << "  " << cleanroom->GetTranslation()
//            << G4endl;
//     G4cout << "Source position: " << sourcePos << G4endl;
//  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterPrimaryGeneratorAction::SetParticleName(G4String particleName)
{
  //this function is called at the begining the run
  //
   fParticleName = particleName;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
