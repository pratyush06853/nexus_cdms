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
/// \file IronFilterDetectorMessenger.cc
/// \brief Implementation of the IronFilterDetectorMessenger class

#include "IronFilterDetectorMessenger.hh"
#include "IronFilterDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorMessenger::IronFilterDetectorMessenger(IronFilterDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fB1Directory = new G4UIdirectory("/B1/");
  fB1Directory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/B1/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fSetVerbosityCmd =
    new G4UIcmdWithAnInteger("/B1/det/verbose",this);
  fSetVerbosityCmd->SetGuidance("Set verbosity level");
  fSetVerbosityCmd->SetParameterName("SetVerbosity",false);
  fSetVerbosityCmd->AvailableForStates(G4State_Idle);

  fPolyGapCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/PolyGap",this);
  fPolyGapCmd->SetGuidance("Set lead Wall thickness");
  fPolyGapCmd->SetParameterName("PolyGap",false);
  fPolyGapCmd->SetUnitCategory("Length");
  fPolyGapCmd->AvailableForStates(G4State_Idle);

  fLeadGapCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/LeadGap",this);
  fLeadGapCmd->SetGuidance("Set crack width");
  fLeadGapCmd->SetParameterName("LeadGap",false);
  fLeadGapCmd->SetUnitCategory("Length");
  fLeadGapCmd->AvailableForStates(G4State_Idle);

  fLeadHorizGapCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/LeadHorizGap",this);
  fLeadHorizGapCmd->SetGuidance("Set crack width");
  fLeadHorizGapCmd->SetParameterName("LeadHorizGap",false);
  fLeadHorizGapCmd->SetUnitCategory("Length");
  fLeadHorizGapCmd->AvailableForStates(G4State_Idle);

  fWallMaterialCmd =
    new G4UIcmdWithAString("/B1/det/WallMaterial",this);
  fWallMaterialCmd->SetGuidance("Set material for south wall");
  fWallMaterialCmd->SetParameterName("WallMaterial",false);
  fWallMaterialCmd->AvailableForStates(G4State_Idle);

  fDumpDepthCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/DumpDepth",this);
  fDumpDepthCmd->SetGuidance("Set beam dump depth");
  fDumpDepthCmd->SetParameterName("DumpDepth",false);
  fDumpDepthCmd->SetUnitCategory("Length");
  fDumpDepthCmd->AvailableForStates(G4State_Idle);

  fDumpRadiusCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/DumpRadius",this);
  fDumpRadiusCmd->SetGuidance("Set beam dump radius");
  fDumpRadiusCmd->SetParameterName("DumpRadius",false);
  fDumpRadiusCmd->SetUnitCategory("Length");
  fDumpRadiusCmd->AvailableForStates(G4State_Idle);

  fCollRadiusCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/CollRadius",this);
  fCollRadiusCmd->SetGuidance("Set beam collimator radius");
  fCollRadiusCmd->SetParameterName("CollRadius",false);
  fCollRadiusCmd->SetUnitCategory("Length");
  fCollRadiusCmd->AvailableForStates(G4State_Idle);

  fShieldHoleRadiusCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/ShieldHoleRadius",this);
  fShieldHoleRadiusCmd->SetGuidance("Set Shield Hole radius");
  fShieldHoleRadiusCmd->SetParameterName("ShieldHoleRadius",false);
  fShieldHoleRadiusCmd->SetUnitCategory("Length");
  fShieldHoleRadiusCmd->AvailableForStates(G4State_Idle);

  fBeamPipeClearCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/BeamPipeClear",this);
  fBeamPipeClearCmd->SetGuidance("Set Beam pipe Clearance");
  fBeamPipeClearCmd->SetParameterName("BeamPipeClear",false);
  fBeamPipeClearCmd->SetUnitCategory("Length");
  fBeamPipeClearCmd->AvailableForStates(G4State_Idle);

  fBeamPipeWallCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/BeamPipeWall",this);
  fBeamPipeWallCmd->SetGuidance("Set Beam pipe wall");
  fBeamPipeWallCmd->SetParameterName("BeamPipeWall",false);
  fBeamPipeWallCmd->SetUnitCategory("Length");
  fBeamPipeWallCmd->AvailableForStates(G4State_Idle);

  fCartZOffsetCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/CartZOffset",this);
  fCartZOffsetCmd->SetGuidance("Set Cart Offset");
  fCartZOffsetCmd->SetParameterName("CartZOffset",false);
  fCartZOffsetCmd->SetUnitCategory("Length");
  fCartZOffsetCmd->AvailableForStates(G4State_Idle);

  fBackingZPositionCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/BackingZPosition",this);
  fBackingZPositionCmd->SetGuidance("Set Backing Array Z Position");
  fBackingZPositionCmd->SetParameterName("BackingZPosition",false);
  fBackingZPositionCmd->SetUnitCategory("Length");
  fBackingZPositionCmd->AvailableForStates(G4State_Idle);

  fBackingTypeCmd =
    new G4UIcmdWithAnInteger("/B1/det/BackingType",this);
  fBackingTypeCmd->SetGuidance("Set Backing Array Type");
  fBackingTypeCmd->SetParameterName("BackingType",false);
  fBackingTypeCmd->AvailableForStates(G4State_Idle);

  fBackingMisalignCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/BackingMisalign",this);
  fBackingMisalignCmd->SetGuidance("Set beam scintillator dimensions(X,Y,Z)");
  fBackingMisalignCmd->SetParameterName("Offset X","Offset Y",
                                     "Offset Z",false);
  fBackingMisalignCmd->SetUnitCategory("Length");
  fBackingMisalignCmd->AvailableForStates(G4State_Idle);

  fBeamScintDimCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/BeamScintDim",this);
  fBeamScintDimCmd->SetGuidance("Set beam scintillator dimensions(X,Y,Z)");
  fBeamScintDimCmd->SetParameterName("Thickness X","Thickness Y",
                                     "Thickness Z",false);
  fBeamScintDimCmd->SetUnitCategory("Length");
  fBeamScintDimCmd->AvailableForStates(G4State_Idle);

  fScatScintDimCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/ScatScintDim",this);
  fScatScintDimCmd->SetGuidance("Set scatter scintillator dimensions(X,Y,Z)");
  fScatScintDimCmd->SetParameterName("Thickness X","Thickness Y",
                                     "Thickness Z",false);
  fScatScintDimCmd->SetUnitCategory("Length");
  fScatScintDimCmd->AvailableForStates(G4State_Idle);

  fScatScintNumCmd =
    new G4UIcmdWithAnInteger("/B1/det/ScatScintNum",this);
  fScatScintNumCmd->SetGuidance("Set number of scatter scintillators");
  fScatScintNumCmd->SetParameterName("NumScatScint",false);
  fScatScintNumCmd->AvailableForStates(G4State_Idle);

  fScatScintGapCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/ScatScintGap",this);
  fScatScintGapCmd->SetGuidance("Set scatter scintillator Gap");
  fScatScintGapCmd->SetParameterName("Thickness",false);
  fScatScintGapCmd->SetUnitCategory("Length");
  fScatScintGapCmd->AvailableForStates(G4State_Idle);

  fScatMinRadiusCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/ScatMinRadius",this);
  fScatMinRadiusCmd->SetGuidance("Set scatter scintillator min. radius");
  fScatMinRadiusCmd->SetParameterName("Radius",false);
  fScatMinRadiusCmd->SetUnitCategory("Length");
  fScatMinRadiusCmd->AvailableForStates(G4State_Idle);

  fTableLegWidthCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/TableLegWidth",this);
  fTableLegWidthCmd->SetGuidance("Set Table Leg Width");
  fTableLegWidthCmd->SetParameterName("TableLegWidth",false);
  fTableLegWidthCmd->SetUnitCategory("Length");
  fTableLegWidthCmd->AvailableForStates(G4State_Idle);

  fDumpMaterialCmd =
    new G4UIcmdWithAString("/B1/det/DumpMaterial",this);
  fDumpMaterialCmd->SetGuidance("Set material for beam dump");
  fDumpMaterialCmd->SetParameterName("DumpMaterial",false);
  fDumpMaterialCmd->AvailableForStates(G4State_Idle);

  fTargetMaterialCmd =
    new G4UIcmdWithAString("/B1/det/TargetMaterial",this);
  fTargetMaterialCmd->SetGuidance("Set material for target");
  fTargetMaterialCmd->SetParameterName("TargetMaterial",false);
  fTargetMaterialCmd->AvailableForStates(G4State_Idle);

  fEnvironmentMaterialCmd =
    new G4UIcmdWithAString("/B1/det/EnvironmentMaterial",this);
  fEnvironmentMaterialCmd->SetGuidance("Set material for Environment");
  fEnvironmentMaterialCmd->SetParameterName("EnvironmentMaterial",false);
  fEnvironmentMaterialCmd->AvailableForStates(G4State_Idle);

  fUseFloorCmd =
    new G4UIcmdWithABool("/B1/det/UseFloor",this);
  fUseFloorCmd->SetGuidance("Use the concrete floor");
  fUseFloorCmd->SetParameterName("UseFloor",false);
  fUseFloorCmd->AvailableForStates(G4State_Idle);

  fUseFloorBlockCmd =
    new G4UIcmdWithABool("/B1/det/UseFloorBlock",this);
  fUseFloorBlockCmd->SetGuidance("Use the floor block");
  fUseFloorBlockCmd->SetParameterName("UseFloorBlock",false);
  fUseFloorBlockCmd->AvailableForStates(G4State_Idle);

  fFloorBlockHeightCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/FloorBlockHeight",this);
  fFloorBlockHeightCmd->SetGuidance("Set Drain Radius");
  fFloorBlockHeightCmd->SetParameterName("FloorBlockHeight",false);
  fFloorBlockHeightCmd->SetUnitCategory("Length");
  fFloorBlockHeightCmd->AvailableForStates(G4State_Idle);

  fCryostatHeightCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/CryostatHeight",this);
  fCryostatHeightCmd->SetGuidance("Set Cryostat Height");
  fCryostatHeightCmd->SetParameterName("CryostatHeight",false);
  fCryostatHeightCmd->SetUnitCategory("Length");
  fCryostatHeightCmd->AvailableForStates(G4State_Idle);

  fUseAltTargetCmd =
    new G4UIcmdWithABool("/B1/det/UseAltTarget",this);
  fUseAltTargetCmd->SetGuidance("Use the concrete AltTarget");
  fUseAltTargetCmd->SetParameterName("UseAltTarget",false);
  fUseAltTargetCmd->AvailableForStates(G4State_Idle);

  fAltTargetSizeCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/AltTargetSize",this);
  fAltTargetSizeCmd->SetGuidance("Set Target Size(X,Y,Z)");
  fAltTargetSizeCmd->SetParameterName("AltTarget X","AltTarget Y",
                                      "AltTarget Z",false);
  fAltTargetSizeCmd->SetUnitCategory("Length");
  fAltTargetSizeCmd->AvailableForStates(G4State_Idle);

  fAltTargetPositionCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/AltTargetPosition",this);
  fAltTargetPositionCmd->SetGuidance("Set Target Position(X,Y,Z)");
  fAltTargetPositionCmd->SetParameterName("AltTarget X","AltTarget Y",
                                      "AltTarget Z",false);
  fAltTargetPositionCmd->SetUnitCategory("Length");
  fAltTargetPositionCmd->AvailableForStates(G4State_Idle);

  fTargetTemperatureCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/SetTargetTemp",this);
  fTargetTemperatureCmd->SetGuidance("Set Drain Radius");
  fTargetTemperatureCmd->SetParameterName("TargetTemperature",false);
  fTargetTemperatureCmd->SetUnitCategory("Temperature");
  fTargetTemperatureCmd->AvailableForStates(G4State_Idle);

  fGeneratorSizeCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/GeneratorSize",this);
  fGeneratorSizeCmd->SetGuidance("Set Generator Size(X,Y,Z)");
  fGeneratorSizeCmd->SetParameterName("Generator X","Generator Y",
                                      "Generator Z",false);
  fGeneratorSizeCmd->SetUnitCategory("Length");
  fGeneratorSizeCmd->AvailableForStates(G4State_Idle);

  fGenerShiftCmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/GeneratorShift",this);
  fGenerShiftCmd->SetGuidance("Set Drain Radius");
  fGenerShiftCmd->SetParameterName("GenerShift X","GenerShift Y",
                                   "GenerShift Z",false);
  fGenerShiftCmd->SetUnitCategory("Length");
  fGenerShiftCmd->AvailableForStates(G4State_Idle);


  fUseParametrizationCmd =
    new G4UIcmdWithABool("/B1/det/UseParametrization",this);
  fUseParametrizationCmd->SetGuidance("Use the shield Parametrization");
  fUseParametrizationCmd->SetParameterName("UseParametrization",false);
  fUseParametrizationCmd->AvailableForStates(G4State_Idle);

  fUseNotchCmd =
    new G4UIcmdWithABool("/B1/det/UseNotch",this);
  fUseNotchCmd->SetGuidance("Use the shield Notch");
  fUseNotchCmd->SetParameterName("UseNotch",false);
  fUseNotchCmd->AvailableForStates(G4State_Idle);

  fUseCartShieldCmd =
    new G4UIcmdWithABool("/B1/det/UseCartShield",this);
  fUseCartShieldCmd->SetGuidance("Use the cart shield");
  fUseCartShieldCmd->SetParameterName("UseCartShield",false);
  fUseCartShieldCmd->AvailableForStates(G4State_Idle);

  fUseCartBeamholeCmd =
    new G4UIcmdWithABool("/B1/det/UseCartBeamhole",this);
  fUseCartBeamholeCmd->SetGuidance("Use the cart shield");
  fUseCartBeamholeCmd->SetParameterName("UseCartBeamhole",false);
  fUseCartBeamholeCmd->AvailableForStates(G4State_Idle);

  fUseCryostatCmd =
    new G4UIcmdWithABool("/B1/det/UseCryostat",this);
  fUseCryostatCmd->SetGuidance("Use the cryostat");
  fUseCryostatCmd->SetParameterName("UseCryostat",false);
  fUseCryostatCmd->AvailableForStates(G4State_Idle);

  fCryoOVCMaterialCmd =
    new G4UIcmdWithAString("/B1/det/SetCryoOVCMaterial",this);
  fCryoOVCMaterialCmd->SetGuidance("Set material for CryoOVC");
  fCryoOVCMaterialCmd->SetParameterName("CryoOVCMaterial",false);
  fCryoOVCMaterialCmd->AvailableForStates(G4State_Idle);

  fCryoShieldMaterialCmd =
    new G4UIcmdWithAString("/B1/det/SetCryoShieldMaterial",this);
  fCryoShieldMaterialCmd->SetGuidance("Set material for CryoShield");
  fCryoShieldMaterialCmd->SetParameterName("CryoShieldMaterial",false);
  fCryoShieldMaterialCmd->AvailableForStates(G4State_Idle);

  fUseCannonCmd =
    new G4UIcmdWithABool("/B1/det/UseCannon",this);
  fUseCannonCmd->SetGuidance("Use the Cannon");
  fUseCannonCmd->SetParameterName("UseCannon",false);
  fUseCannonCmd->AvailableForStates(G4State_Idle);

  fCannonMaterialCmd =
    new G4UIcmdWithAString("/B1/det/CannonMaterial",this);
  fCannonMaterialCmd->SetGuidance("Set material for Cannon");
  fCannonMaterialCmd->SetParameterName("CannonMaterial",false);
  fCannonMaterialCmd->AvailableForStates(G4State_Idle);

  fBeamPipeMaterialCmd =
    new G4UIcmdWithAString("/B1/det/BeamPipeMaterial",this);
  fBeamPipeMaterialCmd->SetGuidance("Set material for BeamPipe");
  fBeamPipeMaterialCmd->SetParameterName("BeamPipeMaterial",false);
  fBeamPipeMaterialCmd->AvailableForStates(G4State_Idle);

  fUseSouthWallCmd =
    new G4UIcmdWithABool("/B1/det/UseSouthWall",this);
  fUseSouthWallCmd->SetGuidance("Use the SouthWall");
  fUseSouthWallCmd->SetParameterName("UseSouthWall",false);
  fUseSouthWallCmd->AvailableForStates(G4State_Idle);

  fUseSouthWallPlugCmd =
    new G4UIcmdWithABool("/B1/det/UseSouthWallPlug",this);
  fUseSouthWallPlugCmd->SetGuidance("Use the SouthWallPlug");
  fUseSouthWallPlugCmd->SetParameterName("UseSouthWallPlug",false);
  fUseSouthWallPlugCmd->AvailableForStates(G4State_Idle);

  fUseBackingWallCmd =
    new G4UIcmdWithABool("/B1/det/UseBackingWall",this);
  fUseBackingWallCmd->SetGuidance("Use the BackingWall");
  fUseBackingWallCmd->SetParameterName("UseBackingWall",false);
  fUseBackingWallCmd->AvailableForStates(G4State_Idle);

  fUseDumpDetectorCmd =
    new G4UIcmdWithABool("/B1/det/UseDumpDetector",this);
  fUseDumpDetectorCmd->SetGuidance("Use the DumpDetector");
  fUseDumpDetectorCmd->SetParameterName("UseDumpDetector",false);
  fUseDumpDetectorCmd->AvailableForStates(G4State_Idle);

  fUseBackingFaceCmd =
    new G4UIcmdWithABool("/B1/det/UseBackingFace",this);
  fUseBackingFaceCmd->SetGuidance("Use the BackingFace");
  fUseBackingFaceCmd->SetParameterName("UseBackingFace",false);
  fUseBackingFaceCmd->AvailableForStates(G4State_Idle);

  fBackingFaceThickCmd =
    new G4UIcmdWithADoubleAndUnit("/B1/det/BackingFaceThickness",this);
  fBackingFaceThickCmd->SetGuidance("Set backing face thickness");
  fBackingFaceThickCmd->SetParameterName("BackingFaceThick",false);
  fBackingFaceThickCmd->SetUnitCategory("Length");
  fBackingFaceThickCmd->AvailableForStates(G4State_Idle);

  fBackingFaceMaterialCmd =
    new G4UIcmdWithAString("/B1/det/BackingFaceMaterial",this);
  fBackingFaceMaterialCmd->SetGuidance("Set material for Layer 0");
  fBackingFaceMaterialCmd->SetParameterName("BackingFaceMaterial",false);
  fBackingFaceMaterialCmd->AvailableForStates(G4State_Idle);

  fUseTableLegCmd =
    new G4UIcmdWithABool("/B1/det/UseTableLeg",this);
  fUseTableLegCmd->SetGuidance("Use the TableLeg");
  fUseTableLegCmd->SetParameterName("UseTableLeg",false);
  fUseTableLegCmd->AvailableForStates(G4State_Idle);

  fLayerMaterial0Cmd =
    new G4UIcmdWithAString("/B1/det/LayerMaterial0",this);
  fLayerMaterial0Cmd->SetGuidance("Set material for Layer 0");
  fLayerMaterial0Cmd->SetParameterName("LayerMaterial0",false);
  fLayerMaterial0Cmd->AvailableForStates(G4State_Idle);

  fLayerThickness0Cmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/LayerThickness0",this);
  fLayerThickness0Cmd->SetGuidance("Set Layer 0 thickness(X,Y,Z)");
  fLayerThickness0Cmd->SetParameterName("Thickness X","Thickness Y",
                                      "Thickness Z",false);
  fLayerThickness0Cmd->SetUnitCategory("Length");
  fLayerThickness0Cmd->AvailableForStates(G4State_Idle);

  fLayerAspect0Cmd =
    new G4UIcmdWith3Vector("/B1/det/LayerAspect0",this);
  fLayerAspect0Cmd->SetGuidance("Set Layer Aspect(X,Y,Z)");
  fLayerAspect0Cmd->SetParameterName("Aspect X","Aspect Y",
                                      "Aspect Z",false);
  fLayerAspect0Cmd->AvailableForStates(G4State_Idle);

  fLayerGap0Cmd =
    new G4UIcmdWithAnInteger("/B1/det/LayerGap0",this);
  fLayerGap0Cmd->SetGuidance("Set number of gaps");
  fLayerGap0Cmd->SetParameterName("Gaps",false);
  fLayerGap0Cmd->AvailableForStates(G4State_Idle);

  fLayerMaterial1Cmd =
    new G4UIcmdWithAString("/B1/det/LayerMaterial1",this);
  fLayerMaterial1Cmd->SetGuidance("Set material for Layer 1");
  fLayerMaterial1Cmd->SetParameterName("LayerMaterial1",false);
  fLayerMaterial1Cmd->AvailableForStates(G4State_Idle);

  fLayerThickness1Cmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/LayerThickness1",this);
  fLayerThickness1Cmd->SetGuidance("Set Layer 1 thickness(X,Y,Z)");
  fLayerThickness1Cmd->SetParameterName("Thickness X","Thickness Y",
                                      "Thickness Z",false);
  fLayerThickness1Cmd->SetUnitCategory("Length");
  fLayerThickness1Cmd->AvailableForStates(G4State_Idle);

  fLayerAspect1Cmd =
    new G4UIcmdWith3Vector("/B1/det/LayerAspect1",this);
  fLayerAspect1Cmd->SetGuidance("Set Layer Aspect(X,Y,Z)");
  fLayerAspect1Cmd->SetParameterName("Aspect X","Aspect Y",
                                      "Aspect Z",false);
  fLayerAspect1Cmd->AvailableForStates(G4State_Idle);

  fLayerGap1Cmd =
    new G4UIcmdWithAnInteger("/B1/det/LayerGap1",this);
  fLayerGap1Cmd->SetGuidance("Set number of gaps");
  fLayerGap1Cmd->SetParameterName("Gaps",false);
  fLayerGap1Cmd->AvailableForStates(G4State_Idle);

  fLayerMaterial2Cmd =
    new G4UIcmdWithAString("/B1/det/LayerMaterial2",this);
  fLayerMaterial2Cmd->SetGuidance("Set material for Layer 2");
  fLayerMaterial2Cmd->SetParameterName("LayerMaterial2",false);
  fLayerMaterial2Cmd->AvailableForStates(G4State_Idle);

  fLayerThickness2Cmd =
    new G4UIcmdWith3VectorAndUnit("/B1/det/LayerThickness2",this);
  fLayerThickness2Cmd->SetGuidance("Set Layer 2 thickness(X,Y,Z)");
  fLayerThickness2Cmd->SetParameterName("Thickness X","Thickness Y",
                                      "Thickness Z",false);
  fLayerThickness2Cmd->SetUnitCategory("Length");
  fLayerThickness2Cmd->AvailableForStates(G4State_Idle);

  fLayerAspect2Cmd =
    new G4UIcmdWith3Vector("/B1/det/LayerAspect2",this);
  fLayerAspect2Cmd->SetGuidance("Set Layer Aspect(X,Y,Z)");
  fLayerAspect2Cmd->SetParameterName("Aspect X","Aspect Y",
                                      "Aspect Z",false);
  fLayerAspect2Cmd->AvailableForStates(G4State_Idle);

  fLayerGap2Cmd =
    new G4UIcmdWithAnInteger("/B1/det/LayerGap2",this);
  fLayerGap2Cmd->SetGuidance("Set number of gaps");
  fLayerGap2Cmd->SetParameterName("Gaps",false);
  fLayerGap2Cmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorMessenger::~IronFilterDetectorMessenger()
{
  delete fPolyGapCmd;
  delete fLeadGapCmd;
  delete fWallMaterialCmd;
  delete fDumpRadiusCmd;
  delete fCollRadiusCmd;
  delete fB1Directory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fSetVerbosityCmd ){
    int newVerbose = fSetVerbosityCmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetVerbosity(newVerbose);
  }
  if( command == fPolyGapCmd ){
    double newThickness = fPolyGapCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetPolyGap(newThickness);
  }
  if( command == fLeadGapCmd ){
    double newThickness = fLeadGapCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetLeadGap(newThickness);
  }
  if( command == fLeadHorizGapCmd ){
    double newThickness = fLeadHorizGapCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetLeadHorizGap(newThickness);
  }
  if( command == fWallMaterialCmd ){
    fDetectorConstruction->SetWallMaterial(newValue);
  }
  if( command == fDumpMaterialCmd ){
    fDetectorConstruction->SetDumpMaterial(newValue);
  }
  if( command == fDumpRadiusCmd ){
    double newRadius = fDumpRadiusCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetDumpRadius(newRadius);
  }
  if( command == fCollRadiusCmd ){
    double newRadius = fCollRadiusCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetCollRadius(newRadius);
  }
  if( command == fShieldHoleRadiusCmd ){
    double newRadius = fShieldHoleRadiusCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetShieldHoleRadius(newRadius);
  }
  if( command == fBeamPipeClearCmd ){
    double newRadius = fBeamPipeClearCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetBeamPipeClear(newRadius);
  }
  if( command == fBeamPipeWallCmd ){
    double newRadius = fBeamPipeWallCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetBeamPipeWall(newRadius);
  }
  if( command == fCartZOffsetCmd ){
    double newOffset = fCartZOffsetCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetCartZOffset(newOffset);
  }
  if( command == fBackingZPositionCmd ){
    double newOffset = fBackingZPositionCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetBackingZPosition(newOffset);
  }
  if( command == fBackingTypeCmd ){
    double newType = fBackingTypeCmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetBackingType(newType);
  }
  if( command == fBackingMisalignCmd ){
    G4ThreeVector BackingMisalign =
      fBackingMisalignCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetBackingMisalign(BackingMisalign);
  }
  if( command == fBeamScintDimCmd ){
    G4ThreeVector BeamScintDim =
      fBeamScintDimCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetBeamScintDim(BeamScintDim);
  }
  if( command == fScatScintNumCmd ){
    int ScatScintNum =
      fScatScintNumCmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetScatScintNum(ScatScintNum);
  }
  if( command == fScatScintDimCmd ){
    G4ThreeVector ScatScintDim =
      fScatScintDimCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetScatScintDim(ScatScintDim);
  }
  if( command == fScatScintGapCmd ){
    double newGap = fScatScintGapCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetScatScintGap(newGap);
  }
  if( command == fScatMinRadiusCmd ){
    double newRadius = fScatMinRadiusCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetScatMinRadius(newRadius);
  }
  if( command == fTableLegWidthCmd ){
    double newOffset = fTableLegWidthCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetTableLegWidth(newOffset);
  }
  if( command == fDumpDepthCmd ){
    double newDepth = fDumpDepthCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetDumpDepth(newDepth);
  }
  if( command == fTargetMaterialCmd ){
    fDetectorConstruction->SetTargetMaterial(newValue);
  }
  if( command == fEnvironmentMaterialCmd ){
    fDetectorConstruction->SetEnvironmentMaterial(newValue);
  }
  if( command == fUseFloorCmd ){
    bool useConcrete = fUseFloorCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseFloor(useConcrete);
  }
  if( command == fUseFloorBlockCmd ){
    bool useBlock = fUseFloorBlockCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseFloorBlock(useBlock);
  }
  if( command == fFloorBlockHeightCmd ){
    double newElevation = fFloorBlockHeightCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetFloorBlockHeight(newElevation);
  }
  if( command == fCryostatHeightCmd ){
    double newCryostatHeight = fCryostatHeightCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetCryostatHeight(newCryostatHeight);
  }
  if( command == fUseAltTargetCmd ){
    bool useAltTarget = fUseAltTargetCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseAltTarget(useAltTarget);
  }
  if( command == fAltTargetSizeCmd ){
    G4ThreeVector newTargetSize =
      fAltTargetSizeCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetAltTargetSize(newTargetSize);
  }
  if( command == fAltTargetPositionCmd ){
    G4ThreeVector newTargetPosition =
      fAltTargetPositionCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetAltTargetPosition(newTargetPosition);
  }
  if( command == fTargetTemperatureCmd ){
    double newTemp = fTargetTemperatureCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetTargetTemperature(newTemp);
  }
  if( command == fGeneratorSizeCmd ){
    G4ThreeVector newGeneratorSize =
      fGeneratorSizeCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetGeneratorSize(newGeneratorSize);
  }
  if( command == fGenerShiftCmd ){
    G4ThreeVector newGeneratorShift =
      fGeneratorSizeCmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetGeneratorShift(newGeneratorShift);
  }
  if( command == fUseParametrizationCmd ){
    bool usePara = fUseParametrizationCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseParametrization(usePara);
  }
  if( command == fUseNotchCmd ){
    bool useNotch = fUseNotchCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseNotch(useNotch);
  }
  if( command == fUseCartShieldCmd ){
    bool useCartShield = fUseCartShieldCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseCartShield(useCartShield);
  }
  if( command == fUseCartBeamholeCmd ){
    bool useCartBeamhole = fUseCartBeamholeCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseCartBeamhole(useCartBeamhole);
  }
  if( command == fUseCryostatCmd ){
    bool useCryostat = fUseCryostatCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseCryostat(useCryostat);
  }
  if( command == fCryoOVCMaterialCmd ){
    fDetectorConstruction->SetCryoOVCMaterial(newValue);
  }
  if( command == fCryoShieldMaterialCmd ){
    fDetectorConstruction->SetCryoShieldMaterial(newValue);
  }
  if( command == fUseCannonCmd ){
    bool useCannon = fUseCannonCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseCannon(useCannon);
  }
  if( command == fCannonMaterialCmd ){
    fDetectorConstruction->SetCannonMaterial(newValue);
  }
  if( command == fBeamPipeMaterialCmd ){
    fDetectorConstruction->SetBeamPipeMaterial(newValue);
  }
  if( command == fUseSouthWallCmd ){
    bool useSouthWall = fUseSouthWallCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseSouthWall(useSouthWall);
  }
  if( command == fUseSouthWallPlugCmd ){
    bool useSouthWallPlug = fUseSouthWallPlugCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseSouthWallPlug(useSouthWallPlug);
  }
  if( command == fUseBackingWallCmd ){
    bool useBackingWall = fUseBackingWallCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseBackingWall(useBackingWall);
  }
  if( command == fUseDumpDetectorCmd ){
    bool useDumpDetector = fUseDumpDetectorCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseDumpDetector(useDumpDetector);
  }
  if( command == fUseBackingFaceCmd ){
    bool useBackingFace = fUseBackingFaceCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseBackingFace(useBackingFace);
  }
  if( command == fBackingFaceThickCmd ){
    double BackingFaceThickness =
      fBackingFaceThickCmd->GetNewDoubleValue(newValue);
    fDetectorConstruction->SetBackingFaceThick(BackingFaceThickness);
  }
  if( command == fBackingFaceMaterialCmd ){
    fDetectorConstruction->SetBackingFaceMater(newValue);
  }
  if( command == fUseTableLegCmd ){
    bool useTableLeg = fUseTableLegCmd->GetNewBoolValue(newValue);
    fDetectorConstruction->UseTableLeg(useTableLeg);
  }
  if( command == fLayerMaterial0Cmd ){
    fDetectorConstruction->SetLayerMaterial(0,newValue);
  }
  if( command == fLayerThickness0Cmd ){
    G4ThreeVector LayerThickness =
      fLayerThickness0Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerThickness(0,LayerThickness);
  }
  if( command == fLayerAspect0Cmd ){
    G4ThreeVector LayerAspect =
      fLayerAspect0Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerAspect(0,LayerAspect);
  }
  if( command == fLayerGap0Cmd ){
    G4int LayerGaps =
      fLayerGap0Cmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetLayerGaps(0,LayerGaps);
  }
  if( command == fLayerMaterial1Cmd ){
    fDetectorConstruction->SetLayerMaterial(1,newValue);
  }
  if( command == fLayerThickness1Cmd ){
    G4ThreeVector LayerThickness =
      fLayerThickness1Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerThickness(1,LayerThickness);
  }
  if( command == fLayerAspect1Cmd ){
    G4ThreeVector LayerAspect =
      fLayerAspect1Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerAspect(1,LayerAspect);
  }
  if( command == fLayerGap1Cmd ){
    G4int LayerGaps =
      fLayerGap1Cmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetLayerGaps(1,LayerGaps);
  }
  if( command == fLayerMaterial2Cmd ){
    fDetectorConstruction->SetLayerMaterial(2,newValue);
  }
  if( command == fLayerThickness2Cmd ){
    G4ThreeVector LayerThickness =
      fLayerThickness2Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerThickness(2,LayerThickness);
  }
  if( command == fLayerAspect2Cmd ){
    G4ThreeVector LayerAspect =
      fLayerAspect2Cmd->GetNew3VectorValue(newValue);
    fDetectorConstruction->SetLayerAspect(2,LayerAspect);
  }
  if( command == fLayerGap2Cmd ){
    G4int LayerGaps =
      fLayerGap2Cmd->GetNewIntValue(newValue);
    fDetectorConstruction->SetLayerGaps(2,LayerGaps);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
