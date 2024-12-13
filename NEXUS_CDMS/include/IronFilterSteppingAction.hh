//
/// \file IronFilterSteppingAction.hh
/// \brief Definition of the IronFilterSteppingAction class

#ifndef IronFilterSteppingAction_h
#define IronFilterSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class IronFilterDetectorConstruction;
class IronFilterEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track
/// lengths of charged particles in Absober and Gap layers and
/// updated in IronFilterEventAction.

class IronFilterSteppingAction : public G4UserSteppingAction
{
public:
  IronFilterSteppingAction(const IronFilterDetectorConstruction* detectorConstruction,
                    IronFilterEventAction* eventAction);
  virtual ~IronFilterSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);

private:
  const IronFilterDetectorConstruction* fDetConstruction;
  IronFilterEventAction* fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
