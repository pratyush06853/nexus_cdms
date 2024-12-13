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
// $Id: IronFilterGPSGeneratorAction.cc $
//
/// \file IronFilterGPSGeneratorAction.cc
/// \brief Implementation of the IronFilterGPSGeneratorAction class

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

#include "IronFilterGPSGeneratorAction.hh"
#include "G4RunManager.hh"
//#include "G4Navigator.hh"
//#include "G4PhysicalVolumeStore.hh"
//#include "G4VPhysicalVolume.hh"
//#include "G4SolidStore.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
//#include "G4Neutron.hh"
//#include "G4TransportationManager.hh"
//#include "G4Navigator.hh"
//#include "G4GenericIon.hh"
//#include "G4IonTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterGPSGeneratorAction::IronFilterGPSGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleSource(0)
{
  fParticleSource = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterGPSGeneratorAction::~IronFilterGPSGeneratorAction()
{
  delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterGPSGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
//G4ThreeVector neutronDirection = G4RandomDirection();
//G4ThreeVector neutronDirection = G4ThreeVector(0., 1.0, 0.0);


  // default particle kinematic
 //G4ParticleDefinition* particleDefinition
//  = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
 //fParticleSource->SetParticleDefinition(particleDefinition);
 //fParticleSource->SetParticleEnergy(14.1*MeV);

// Set source position
// fParticleSource->SetParticleMomentumDirection(neutronDirection);
// fParticleSource->SetParticlePosition(G4ThreeVector(0., 100*cm, 0.0*cm));//45.0cm
 //cout<<a<<endl;
 fParticleSource->GeneratePrimaryVertex(anEvent);

}
