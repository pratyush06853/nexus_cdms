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
/// \file IronFilterPrimaryMessenger.cc
/// \brief Implementation of the IronFilterPrimaryMessenger class

#include "IronFilterPrimaryMessenger.hh"
#include "IronFilterPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterPrimaryMessenger::IronFilterPrimaryMessenger(IronFilterPrimaryGeneratorAction* Det)
 : G4UImessenger(),
   fPrimaryGeneratorAction(Det)
{
  fIronFilterDirectory = new G4UIdirectory("/IronFilter/");
  fIronFilterDirectory->SetGuidance("UI commands specific to this example.");

  fSetVerbosityCmd = new G4UIcmdWithAnInteger("/IronFilter/prim/verbose",this);
  fSetVerbosityCmd->SetGuidance("Set the verbosity level");
  fSetVerbosityCmd->SetParameterName("verbose",false);
  fSetVerbosityCmd->AvailableForStates(G4State_Idle);

  fDetDirectory = new G4UIdirectory("/IronFilter/prim/");
  fDetDirectory->SetGuidance("Particle generation control");

  fSetCosThetaMinCmd = new G4UIcmdWithADouble("/IronFilter/prim/SetCosThetaMin",this);
  fSetCosThetaMinCmd->SetGuidance("Set the minimum cos(theta)");
  fSetCosThetaMinCmd->SetParameterName("SetCosThetaMin",false);
  fSetCosThetaMinCmd->AvailableForStates(G4State_Idle);

  fSetCosThetaMaxCmd = new G4UIcmdWithADouble("/IronFilter/prim/SetCosThetaMax",this);
  fSetCosThetaMaxCmd->SetGuidance("Set the Maximum cos(theta)");
  fSetCosThetaMaxCmd->SetParameterName("SetCosThetaMax",false);
  fSetCosThetaMaxCmd->AvailableForStates(G4State_Idle);

  fSetPhiMinCmd = new G4UIcmdWithADouble("/IronFilter/prim/SetPhiMin",this);
  fSetPhiMinCmd->SetGuidance("Set the minimum phi");
  fSetPhiMinCmd->SetParameterName("SetPhiMin",false);
  fSetPhiMinCmd->AvailableForStates(G4State_Idle);

  fSetPhiMaxCmd = new G4UIcmdWithADouble("/IronFilter/prim/SetPhiMax",this);
  fSetPhiMaxCmd->SetGuidance("Set the Maximum phi");
  fSetPhiMaxCmd->SetParameterName("SetPhiMax",false);
  fSetPhiMaxCmd->AvailableForStates(G4State_Idle);

  fSourceSizeCmd = new G4UIcmdWithADoubleAndUnit("/IronFilter/prim/SourceSize",this);
  fSourceSizeCmd->SetGuidance("Set the source size");
  fSourceSizeCmd->SetParameterName("SourceSize",false);
  fSourceSizeCmd->AvailableForStates(G4State_Idle);

  fSetMisalignmentCmd =
    new G4UIcmdWith3VectorAndUnit("/IronFilter/prim/SetMisalignment",this);
  fSetMisalignmentCmd->SetGuidance("Set Misalignment(X,Y,Z)");
  fSetMisalignmentCmd->SetParameterName("Delta X","Delta Y",
                                      "Delta Z",false);
  fSetMisalignmentCmd->SetUnitCategory("Length");
  fSetMisalignmentCmd->AvailableForStates(G4State_Idle);

  fParticleEnergyCmd = new G4UIcmdWithADoubleAndUnit("/IronFilter/prim/ParticleEnergy",this);
  fParticleEnergyCmd->SetGuidance("Set the particle energy");
  fParticleEnergyCmd->SetParameterName("ParticleEnergy",false);
  fParticleEnergyCmd->AvailableForStates(G4State_Idle);

  fParticleNameCmd =
    new G4UIcmdWithAString("/IronFilter/prim/ParticleName",this);
  fParticleNameCmd->SetGuidance("Set particle name");
  fParticleNameCmd->SetParameterName("ParticleName",false);
  fParticleNameCmd->AvailableForStates(G4State_Idle);

  fUseLineBeamCmd =
    new G4UIcmdWithABool("/IronFilter/prim/UseLineBeam",this);
  fUseLineBeamCmd->SetGuidance("Use a line beam");
  fUseLineBeamCmd->SetParameterName("UseLineBeam",false);
  fUseLineBeamCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterPrimaryMessenger::~IronFilterPrimaryMessenger()
{
  delete fSetCosThetaMinCmd;
  delete fSetCosThetaMaxCmd;
  delete fIronFilterDirectory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterPrimaryMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fSetVerbosityCmd ){
    int newVerbose = fSetVerbosityCmd->GetNewIntValue(newValue);
    fPrimaryGeneratorAction->SetVerbosity(newVerbose);
  }
  if( command == fSetCosThetaMinCmd ){
    double newCosth = fSetCosThetaMinCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetCosThetaMin(newCosth);
  }
  if( command == fSetCosThetaMaxCmd ){
    double newCosth = fSetCosThetaMaxCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetCosThetaMax(newCosth);
  }
  if( command == fSetPhiMinCmd ){
    double newPhi = fSetPhiMinCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetPhiMin(newPhi);
  }
  if( command == fSetPhiMaxCmd ){
    double newPhi = fSetPhiMaxCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetPhiMax(newPhi);
  }
  if( command == fSourceSizeCmd ){
    double newSize = fSourceSizeCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetSourceSize(newSize);
  }
  if( command == fSetMisalignmentCmd ){
    G4ThreeVector newOffset =
      fSetMisalignmentCmd->GetNew3VectorValue(newValue);
    fPrimaryGeneratorAction->SetMisalignment(newOffset);
  }
  if( command == fParticleEnergyCmd ){
    double newSize = fParticleEnergyCmd->GetNewDoubleValue(newValue);
    fPrimaryGeneratorAction->SetParticleEnergy(newSize);
  }
  if( command == fParticleNameCmd ){
    fPrimaryGeneratorAction->SetParticleName(newValue);
  }
  if( command == fUseLineBeamCmd ){
    fPrimaryGeneratorAction->UseLineBeam(newValue);
  }
  if((command == fSetCosThetaMinCmd) || (command == fSetCosThetaMaxCmd) ||
     (command == fSetPhiMinCmd)      || (command == fSetPhiMaxCmd)){
    char title[80];
    double cosMin = fPrimaryGeneratorAction->GetCosThetaMin();
    double cosMax = fPrimaryGeneratorAction->GetCosThetaMax();
    double phiMin = fPrimaryGeneratorAction->GetPhiMin();
    double phiMax = fPrimaryGeneratorAction->GetPhiMax();
//
    std::string strOutput = "\n********** Primary Generator ************\n" ;
    char * env_NumEvents = getenv("NUM_EVENTS");
    double equivScale = 2.0/(cosMax - cosMin);
    equivScale *=  CLHEP::twopi /(phiMax - phiMin);
    if(env_NumEvents){
      int numEvents = atoi(getenv("NUM_EVENTS"));
      sprintf(title,"*      Generating %10.2e primaries  *\n",double(numEvents));
      strOutput += title;
      double equiv = numEvents * equivScale;
      sprintf(title,"*   Equivalent to %10.2e primaries  *\n",equiv);
      strOutput += title;
    }
    else{
      sprintf(title,"Environment variable NUM_EVENTS was not found \n");
      strOutput += title;
      sprintf(title,"*   Equivalent scale is %10.2e      *\n",equivScale);
      strOutput += title;
    }
    sprintf(title,"***************************************** \n");
    strOutput += title;
    G4cout << strOutput << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
