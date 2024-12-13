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
/// \file IronFilterDetectorConstruction.hh
/// \brief Definition of the IronFilterDetectorConstruction class

#ifndef IronFilterDetectorConstruction_h
#define IronFilterDetectorConstruction_h 1

#include "G4Color.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

//class G4RotationMatrix;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4VSolid;
class G4FieldManager;
class G4UserLimits;

class IronFilterDetectorMessenger;
//const char * DD_SHIELD_NAME = "DDShield";
const int N_DETECTORS = 6;
//const int N_DETECTORS = 1;
const int N_SHIELD_LAYERS = 4;
const int N_WALL_LAYERS = 10;
//const int N_SCATTER_LAYERS = 10;
const int NUM_BEAM_LAYERS = 2;
const int NUM_SCATTER_LAYERS = 2;
const int MAX_BEAM_COUNTERS = 16;
const int MAX_SCATTER_COUNTERS = 32;
const int NUM_DUMP_BEAM_LAYERS = 2;
const int NUM_DUMP_SCATTER_LAYERS = 2;
const int MAX_DUMP_BEAM_COUNTERS = 8;
const int MAX_DUMP_RINGS = 8;
const int MAX_BOTTOM_COUNTERS = 16;
const int MAX_TOTAL_COUNTERS = NUM_BEAM_LAYERS * MAX_BEAM_COUNTERS +
                               NUM_SCATTER_LAYERS * MAX_SCATTER_COUNTERS +
			       NUM_BEAM_LAYERS * MAX_DUMP_BEAM_COUNTERS +
                               NUM_DUMP_SCATTER_LAYERS * MAX_DUMP_RINGS +
			       MAX_BOTTOM_COUNTERS;
/// Detector construction class to define materials and geometry.

class IronFilterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    IronFilterDetectorConstruction();
    virtual ~IronFilterDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    //virtual void ConstructSDandField();

    G4LogicalVolume* ConstructCleanRoom();
    G4LogicalVolume* ConstructLeanShield();
    G4LogicalVolume* ConstructDDGenerator();
    G4LogicalVolume* ConstructDDShield();
    G4LogicalVolume* ConstructBeamDump();
    G4LogicalVolume* ConstructFloorBlock();
    G4LogicalVolume* ConstructF10161306();
    G4LogicalVolume* ConstructLeadBrick();
    G4LogicalVolume* ConstructSWallSections(G4ThreeVector &,G4ThreeVector &);
    G4LogicalVolume* ConstructSWallPlug();//to be built in real
    G4LogicalVolume* ConstructCart();
    G4LogicalVolume* ConstructPosts();
    G4LogicalVolume* ConstructBasePlate();
    G4LogicalVolume* ConstructStepPlate();
    G4LogicalVolume* ConstructSWallPlate();
    G4LogicalVolume* ConstructCryostat();
    G4LogicalVolume* ConstructBackingArray();
    G4LogicalVolume* ConstructBackingWall();
    G4LogicalVolume* ConstructBackingFace();
    G4LogicalVolume* ConstructBeamDetector();
    G4LogicalVolume* ConstructScatDetector();
    G4LogicalVolume* ConstructScatBarDetector();
    G4LogicalVolume* ConstructDumpDetector();
    G4LogicalVolume* ConstructDumpScatDetector();
    G4LogicalVolume* ConstructBottomDetector();
    G4LogicalVolume* ConstructUnistrut(const double);
    G4Material* GetMaterial(G4String);
    int ConstructTableLeg();
    int ConstructNotch();
    G4VPhysicalVolume *  PositionLeanShield();
    G4VPhysicalVolume *  PositionCart();
    G4VPhysicalVolume * PositionSWallPlug();
    G4VPhysicalVolume * PositionCryostat();
    G4VPhysicalVolume * PositionBackingArray();
    G4VPhysicalVolume * PositionBottomArray();
    void PositionSWallSections(G4LogicalVolume *, G4ThreeVector &);
    void CustomMaterials();
    void SetVerbosity(G4int newValue = 0) { fVerbosity = newValue;};
    void SetPolyGap(double newValue) {fPolyGap = newValue; }
    void SetLeadGap(double newValue) {fLeadGap = newValue; }
    void SetLeadHorizGap(double newValue) {fLeadHorizGap = newValue; }
    void SetFloorBlockHeight(double newValue) {fFloorBlockHeight = newValue; }
    void SetDumpDepth(double newValue) {fDumpDepth = newValue; }
    void SetDumpRadius(double newValue) {fDumpRadius = newValue; }
    void SetCollRadius(double newValue) {fCollRadius = newValue; }
    void SetShieldHoleRadius(double newValue) {fShieldHoleRadius = newValue; }
    void SetBeamPipeWall(double newValue) {fBeamPipeWall = newValue; }
    void SetBeamPipeClear(double newValue) {fBeamPipeClear = newValue; }
    void SetWallMaterial(G4String);
    void SetDumpMaterial(G4String);
    void SetTargetMaterial(G4String);
    void SetCryostatHeight(double newValue) {fCryostatHeight = newValue; }
    void SetCannonMaterial(G4String);
    void SetBeamPipeMaterial(G4String);
    void SetEnvironmentMaterial(G4String);
    void UseFloor(G4bool newValue = false) {fUseFloor = newValue; };
    void UseFloorBlock(G4bool newValue = false) {fUseFloorBlock = newValue; };
    void UseAltTarget(G4bool newValue = false) {fUseAltTarget = newValue; };
    void SetAltTargetSize(G4ThreeVector newValue) {fAltTargetSize = newValue; }
    void SetAltTargetPosition(G4ThreeVector newValue)
         {fAltTargetPosition = newValue; }
    void SetTargetTemperature(G4double newValue) {fTargetTemperature = newValue; }
    void SetGeneratorSize(G4ThreeVector newValue) {fGeneratorSize = newValue; }
    void SetGeneratorShift(G4ThreeVector newValue) {fGeneratorShift = newValue; }
    void UseParametrization(G4bool newValue = false)
      {fParametrization = newValue; };
    void UseNotch(G4bool newValue = false) {fUseNotch = newValue; };
    void UseCartShield(G4bool newValue = false) {fUseCartShield = newValue; };
    void UseCartBeamhole(G4bool newValue = false) {fUseCartBeamhole = newValue; };
    void UseCryostat(G4bool newValue = false) {fUseCryostat = newValue; };
    void SetCryoOVCMaterial(G4String newValue) {fCryoOVCMater = newValue; };
    void SetCryoShieldMaterial(G4String newValue) {fCryoShieldMater = newValue; };
    void UseCannon(G4bool newValue = false) {fUseCannon = newValue; };
    void UseSouthWall(G4bool newValue = true) {fUseSouthWall = newValue; };
    void UseSouthWallPlug(G4bool newValue = true) {fUseSouthWallPlug = newValue; };
    void UseBackingWall(G4bool newValue = true) {fUseBackingWall = newValue; };
    void UseDumpDetector(G4bool newValue = true) {fUseDumpDetector = newValue; };
    void UseBackingFace(G4bool newValue = true) {fUseBackingFace = newValue; };
    void SetBackingFaceThick(double newValue) {fBackingFaceThick = newValue; };
    void SetBackingFaceMater(G4String newValue) {fBackingFaceMater = newValue; };
    void SetBackingType(G4int newValue) {fBackingType = newValue; };
    void SetBackingMisalign(G4ThreeVector newValue) {fBackingMisalign = newValue; }
    void SetBeamScintDim(G4ThreeVector newValue) {fBeamScintDim = newValue; }
    void SetScatScintNum(int newValue) {fNumScatScint = newValue; }
    void SetScatScintDim(G4ThreeVector newValue) {fScatScintDim = newValue; }
    void SetScatMinRadius(G4double newValue) {fScatMinRadius = newValue; }
    void SetScatScintGap(G4double newValue) {fScatScintGap = newValue; }
    void UseTableLeg(G4bool newValue = true) {fUseTableLeg = newValue; };
    void SetBackingZPosition(double newValue) {fBackingZposition = newValue; };
    void SetCartZOffset(double newValue) {fCartZOffset = newValue; };
    void SetTableLegWidth(double newValue) {fTableLegWidth = newValue; };
    void SetLayerThickness(int layer, G4ThreeVector newValue)
      {fLayerThickness[layer] = newValue; }
    void SetLayerAspect(int layer, G4ThreeVector newValue)
      {fLayerAspect[layer] = newValue; }
    void SetLayerGaps(int layer, G4int newValue)
      {fLayerGaps[layer] = newValue; }
    void SetLayerMaterial(int layer, G4String);
    void DumpParameters();
    void DumpFamily(G4LogicalVolume*, int nGener = 99 );
    void DumpDaughters(G4LogicalVolume*, int nGener = 99,
                       G4String indent = "  ");
    G4ThreeVector LocateDaughter(G4LogicalVolume *, G4VPhysicalVolume *);
    void WhereDaughters(G4LogicalVolume*, G4VPhysicalVolume *,
                        G4ThreeVector &, bool &);

  protected:
    G4int        fVerbosity;
    G4Material* fEnvironmentMaterial;

    G4ThreeVector fGeneratorSize;
    G4ThreeVector fGeneratorShift;

    G4double fPolyGap;
    G4bool    fUseSouthWall;
    G4bool    fUseSouthWallPlug;
    G4bool    fUseCannon;
    G4Material* fCannonMaterial;
    G4double fLeadGap;
    G4double fLeadHorizGap;
    G4Material* fWallMaterial;

    G4double fDumpDepth;
    G4double fDumpRadius;
    G4Material* fDumpMaterial;
    G4double fCollRadius;
    G4double fShieldHoleRadius;
    G4double fBeamPipeWall;
    G4double fBeamPipeClear;
    G4Material* fBeamPipeMaterial;
    G4bool    fUseCryostat;
    G4String  fCryoOVCMater;
    G4String  fCryoShieldMater;
    G4Material* fTargetMaterial;
    G4double fCryostatHeight;
    G4bool    fUseAltTarget;
    G4ThreeVector fAltTargetSize;
    G4ThreeVector fAltTargetPosition;
    G4double  fTargetTemperature;
    G4bool    fUseFloor;
    G4bool    fUseFloorBlock;
    G4double  fFloorBlockHeight;
    G4bool    fUseNotch;
    G4bool    fUseTableLeg;
    G4double  fTableLegWidth;
    G4bool    fUseCartShield;
    G4bool    fUseCartBeamhole;
    G4double  fCartZOffset;
    G4bool    fUseBackingWall;
    G4bool    fUseDumpDetector;
    G4double  fBackingZposition;
    G4bool    fUseBackingFace;
    G4double  fBackingFaceThick;
    G4String  fBackingFaceMater;
    G4int     fBackingType;
    G4ThreeVector fBackingMisalign;
    G4ThreeVector fBeamScintDim;
    G4ThreeVector fScatScintDim;
    G4double  fScatScintGap;
    G4double  fScatMinRadius;
    G4int     fNumScatScint;
    G4bool    fParametrization;
    G4Material* fLayerMaterial[N_SHIELD_LAYERS];
    G4ThreeVector fLayerThickness[N_SHIELD_LAYERS];
    G4ThreeVector fLayerAspect[N_SHIELD_LAYERS];
    G4int fLayerGaps[N_SHIELD_LAYERS];
    G4LogicalVolume * fBeamScintillator;
    G4LogicalVolume * fScatScintillator[MAX_SCATTER_COUNTERS];
    G4LogicalVolume * fDumpScintillator[MAX_DUMP_RINGS];
    G4LogicalVolume * fBottomScintillator;

    char name[80];
    char lineOutput[132];
    char formPosOut[132];
    char formDimOut[132];
    char formTubsOut[132];
    IronFilterDetectorMessenger*  fMessenger;   // messenger
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
