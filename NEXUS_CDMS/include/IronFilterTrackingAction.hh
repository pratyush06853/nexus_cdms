//
/// \file IronFilter/include/IronFilterTrackingAction.hh
/// \brief Definition of the IronFilterTrackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef IronFilterTrackingAction_h
#define IronFilterTrackingAction_h 1

#include "G4UserTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class IronFilterEventAction;

class IronFilterTrackingAction : public G4UserTrackingAction {

public:
  IronFilterTrackingAction(IronFilterEventAction*);
  virtual ~IronFilterTrackingAction() {};

  virtual void PreUserTrackingAction(const G4Track*);

private:
  IronFilterEventAction* fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
