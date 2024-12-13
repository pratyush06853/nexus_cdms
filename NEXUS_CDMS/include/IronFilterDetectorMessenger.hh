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
/// \file IronFilterDetectorMessenger.hh
/// \brief Definition of the IronFilterDetectorMessenger class

#ifndef IronFilterDetectorMessenger_h
#define IronFilterDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class IronFilterDetectorConstruction;
class B1PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Messenger class that defines commands for IronFilterDetectorConstruction.
///
/// It implements commands:
/// - /B2/det/setTargetMaterial name
/// - /B2/det/setChamberMaterial name
/// - /B2/det/stepMax value unit

class IronFilterDetectorMessenger: public G4UImessenger
{
  public:
    IronFilterDetectorMessenger(IronFilterDetectorConstruction*);
    virtual ~IronFilterDetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    IronFilterDetectorConstruction*  fDetectorConstruction;
    B1PrimaryGeneratorAction* fB1PrimaryGeneratorAction;

    G4UIdirectory*           fB1Directory;
    G4UIdirectory*           fDetDirectory;

    G4UIcmdWithAString*      fChamMatCmd;

//    G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
    G4UIcmdWithAnInteger*      fSetVerbosityCmd;
    G4UIcmdWithADoubleAndUnit* fPolyGapCmd;
    G4UIcmdWithADoubleAndUnit* fLeadGapCmd;
    G4UIcmdWithADoubleAndUnit* fLeadHorizGapCmd;
    G4UIcmdWithAString*        fWallMaterialCmd;
    G4UIcmdWithADoubleAndUnit* fDumpDepthCmd;
    G4UIcmdWithADoubleAndUnit* fDumpRadiusCmd;
    G4UIcmdWithAString*        fDumpMaterialCmd;
    G4UIcmdWithAString*        fTargetMaterialCmd;
    G4UIcmdWithADoubleAndUnit* fCryostatHeightCmd;
    G4UIcmdWithADoubleAndUnit* fCollRadiusCmd;
    G4UIcmdWithADoubleAndUnit* fShieldHoleRadiusCmd;
    G4UIcmdWithADoubleAndUnit* fBeamPipeClearCmd;
    G4UIcmdWithADoubleAndUnit* fBeamPipeWallCmd;
    G4UIcmdWithADoubleAndUnit* fCartZOffsetCmd;
    G4UIcmdWithADoubleAndUnit* fBackingZPositionCmd;
    G4UIcmdWithADoubleAndUnit* fTableLegWidthCmd;
    G4UIcmdWithAString*        fEnvironmentMaterialCmd;
    G4UIcmdWithABool*          fUseFloorCmd;
    G4UIcmdWithABool*          fUseFloorBlockCmd;
    G4UIcmdWithADoubleAndUnit* fFloorBlockHeightCmd;
    G4UIcmdWithABool*          fUseAltTargetCmd;
    G4UIcmdWith3VectorAndUnit* fAltTargetSizeCmd;
    G4UIcmdWith3VectorAndUnit* fAltTargetPositionCmd;
    G4UIcmdWithADoubleAndUnit* fTargetTemperatureCmd;
    G4UIcmdWith3VectorAndUnit* fGeneratorSizeCmd;
    G4UIcmdWith3VectorAndUnit* fGenerShiftCmd;
    G4UIcmdWith3VectorAndUnit* fLayerThickness0Cmd;
    G4UIcmdWith3Vector*        fLayerAspect0Cmd;
    G4UIcmdWithAString*        fLayerMaterial0Cmd;
    G4UIcmdWithAnInteger*      fLayerGap0Cmd;
    G4UIcmdWith3VectorAndUnit* fLayerThickness1Cmd;
    G4UIcmdWith3Vector*        fLayerAspect1Cmd;
    G4UIcmdWithAString*        fLayerMaterial1Cmd;
    G4UIcmdWithAnInteger*      fLayerGap1Cmd;
    G4UIcmdWith3VectorAndUnit* fLayerThickness2Cmd;
    G4UIcmdWith3Vector*        fLayerAspect2Cmd;
    G4UIcmdWithAString*        fLayerMaterial2Cmd;
    G4UIcmdWithAnInteger*      fLayerGap2Cmd;
    G4UIcmdWithABool*          fUseParametrizationCmd;
    G4UIcmdWithABool*          fUseNotchCmd;
    G4UIcmdWithABool*          fUseCartShieldCmd;
    G4UIcmdWithABool*          fUseCartBeamholeCmd;
    G4UIcmdWithABool*          fUseCryostatCmd;
    G4UIcmdWithAString*        fCryoOVCMaterialCmd;
    G4UIcmdWithAString*        fCryoShieldMaterialCmd;
    G4UIcmdWithABool*          fUseCannonCmd;
    G4UIcmdWithAString*        fCannonMaterialCmd;
    G4UIcmdWithAString*        fBeamPipeMaterialCmd;
    G4UIcmdWithABool*          fUseSouthWallCmd;
    G4UIcmdWithABool*          fUseSouthWallPlugCmd;
    G4UIcmdWithABool*          fUseBackingWallCmd;
    G4UIcmdWithABool*          fUseDumpDetectorCmd;
    G4UIcmdWithABool*          fUseBackingFaceCmd;
    G4UIcmdWithADoubleAndUnit* fBackingFaceThickCmd;
    G4UIcmdWithAString*        fBackingFaceMaterialCmd;
    G4UIcmdWithAnInteger*      fBackingTypeCmd;
    G4UIcmdWith3VectorAndUnit* fBackingMisalignCmd;
    G4UIcmdWith3VectorAndUnit* fBeamScintDimCmd;
    G4UIcmdWithAnInteger*      fScatScintNumCmd;
    G4UIcmdWith3VectorAndUnit* fScatScintDimCmd;
    G4UIcmdWithADoubleAndUnit* fScatScintGapCmd;
    G4UIcmdWithADoubleAndUnit* fScatMinRadiusCmd;
    G4UIcmdWithABool*          fUseTableLegCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
