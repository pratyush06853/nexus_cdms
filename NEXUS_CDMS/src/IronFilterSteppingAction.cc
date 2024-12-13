/// \file IronFilterSteppingAction.cc
/// \brief Implementation of the IronFilterSteppingAction class

#include "IronFilterSteppingAction.hh"
#include "IronFilterEventAction.hh"
#include "IronFilterDetectorConstruction.hh"
#include "IronFilterAnalysis.hh"

#include "G4Neutron.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "StepInfo.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::IronFilterSteppingAction(
                      const IronFilterDetectorConstruction* detectorConstruction,
                      IronFilterEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterSteppingAction::~IronFilterSteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterSteppingAction::UserSteppingAction(const G4Step* step){
    /*
    G4cout << "User stepping: \n";
    G4cout << "   Track ID: " << step->GetTrack()->GetTrackID()<<"\n";
    G4cout << "   Step ID : " << step->GetTrack()->GetCurrentStepNumber()<<"\n";
    G4cout << "   Name    : " << step->GetTrack()->GetParticleDefinition()->GetParticleName() << "\n";
    G4cout << "   Process : " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
    */

  // Collect energy and number of scatters step by step
  // Don't save the out of world step
  if(!step->GetPostStepPoint()->GetPhysicalVolume()) return;

  if( step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()!="Transportation" )
      fEventAction->GetStepCollection().push_back(StepInfo(step));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
