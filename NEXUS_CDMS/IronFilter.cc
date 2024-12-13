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
// $Id: IronFilter.cc $
//
/// \file IronFilter.cc
/// \brief Main program of the IronFilter example

#include "IronFilterDetectorConstruction.hh"
#include "IronFilterActionInitialization.hh"
#include "IronFilterGPSGeneratorAction.hh"
#include "IronFilterParticleGunAction.hh"
#include "IronFilterDTGeneratorAction.hh"
#include "IronFilterPrimaryGeneratorAction.hh"
#include "IronFilterPhysicsList.hh"
#include "IronFilterRunAction.hh"
#include "IronFilterEventAction.hh"
#include "IronFilterTrackingAction.hh"
#include "IronFilterSteppingAction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif


#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "Shielding.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " IronFilter [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 7 ) {
    PrintUsage();
    return 1;
  }

  G4String macro;
  G4String session;

  G4String filename = "";
#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
    else if ( G4String(argv[i]) == "-f" ) filename = G4String(argv[i+1]);
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) {
      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  }

  // Detect interactive mode (if no macro provided) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( ! macro.size() ) {
    ui = new G4UIExecutive(argc, argv, session);
  }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seeds[2];
  time_t systime = time(NULL);
  seeds[0] = (long) systime;
  seeds[1] = (long) (systime*G4UniformRand());
  G4Random::setTheSeeds(seeds);

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  //G4MTRunManager * runManager = new G4MTRunManager;
  G4RunManager * runManager = new G4RunManager;
  if ( nThreads > 0 ) {
    G4cout<<"multithreading"<<G4endl;	  
    //runManager->SetNumberOfThreads(nThreads);
  }
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  IronFilterDetectorConstruction* detConstruction = new IronFilterDetectorConstruction();
  runManager->SetUserInitialization(detConstruction);

  //G4VModularPhysicsList* physicsList = new Shielding;
  //runManager->SetUserInitialization(physicsList);
  IronFilterPhysicsList* physicsList = new IronFilterPhysicsList;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // avoid using ActionInitialization for now
   /*
  IronFilterActionInitialization* actionInitialization
     = new IronFilterActionInitialization(detConstruction);
  runManager->SetUserInitialization(actionInitialization);
  */

  // Primary generator
runManager->SetUserAction( new IronFilterGPSGeneratorAction);
//runManager->SetUserAction( new IronFilterPrimaryGeneratorAction);
//runManager->SetUserAction( new IronFilterDTGeneratorAction);

// Run action
IronFilterRunAction* runAction = new IronFilterRunAction;
runAction->setOutputFileName( filename );
runAction->AddRandomSeeds( seeds, 2);
runManager->SetUserAction( runAction );

// Event action
IronFilterEventAction* eventAction = new IronFilterEventAction(runAction);
runManager->SetUserAction( eventAction );

// Tracking and stepping
runManager->SetUserAction(new IronFilterTrackingAction(eventAction));
runManager->SetUserAction(new IronFilterSteppingAction(detConstruction, eventAction));

// Get the pointer to the User Interface manager
G4UImanager* UImanager = G4UImanager::GetUIpointer();

// Process macro or start UI session

if ( macro.size() ) {
  // batch mode
  // actionInitialization
  runAction->AddMacro( macro );
  G4String command = "/control/execute ";
  UImanager->ApplyCommand(command+macro);
}
else  {
  // interactive mode : define UI session
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  UImanager->ApplyCommand("/control/execute init_vis.mac");
  if (ui->IsGUI()) {
    UImanager->ApplyCommand("/control/execute gui.mac");
  }
  ui->SessionStart();

  delete visManager;
  delete ui;
}

// Job termination
// Free the store: user actions, physics_list and detector_description are
// owned and deleted by the run manager, so they should not be deleted
// in the main() program !

delete runManager;
}
