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
/// \file IronFilterPrimaryMessenger.hh
/// \brief Definition of the IronFilterPrimaryMessenger class

#ifndef IronFilterPrimaryMessenger_h
#define IronFilterPrimaryMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class IronFilterPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Messenger class that defines commands for IronFilterPrimaryGeneratorAction.
///

class IronFilterPrimaryMessenger: public G4UImessenger
{
  public:
    IronFilterPrimaryMessenger(IronFilterPrimaryGeneratorAction*);
    virtual ~IronFilterPrimaryMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    IronFilterPrimaryGeneratorAction* fPrimaryGeneratorAction;

    G4UIdirectory*           fIronFilterDirectory;
    G4UIdirectory*           fDetDirectory;

    G4UIcmdWithAnInteger* fSetVerbosityCmd;
    G4UIcmdWithADouble* fSetCosThetaMinCmd;
    G4UIcmdWithADouble* fSetCosThetaMaxCmd;
    G4UIcmdWithADouble* fSetPhiMinCmd;
    G4UIcmdWithADouble* fSetPhiMaxCmd;
    G4UIcmdWithADoubleAndUnit* fSourceSizeCmd;
    G4UIcmdWith3VectorAndUnit* fSetMisalignmentCmd;
    G4UIcmdWithAString*        fParticleNameCmd;
    G4UIcmdWithADoubleAndUnit* fParticleEnergyCmd;
    G4UIcmdWithABool* fUseLineBeamCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
