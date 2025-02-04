//
// ********************************************************************
// * License and Disclaimer                                           *o
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
/// \file IronFilterDetectorConstruction.cc
/// \brief Implementation of the IronFilterDetectorConstruction class

#include "IronFilterDetectorConstruction.hh"
#include "IronFilterDetectorMessenger.hh"
//#include "B1TrackerSD.hh"
//#include "B1TargetSD.hh"
//#include "B1BackingSD.hh"
//#include "B1ScintillatorSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Para.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4AssemblyVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisExtent.hh"
#include "G4SubtractionSolid.hh"

#include "G4Material.hh"
#include "G4VSolid.hh"
#include "G4SolidStore.hh"
#include "G4GeometryManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::IronFilterDetectorConstruction()
: G4VUserDetectorConstruction(),
  fVerbosity(0),
  fEnvironmentMaterial(NULL),
  fGeneratorSize(345.9,1041.4,508.0),
  fGeneratorShift(0.0,0.0,-63.5),
  fPolyGap(0.0*cm),
  fUseSouthWall(TRUE),
  //fUseSouthWall(FALSE),
  fUseSouthWallPlug(TRUE),
  //fUseSouthWallPlug(FALSE),
  fUseCannon(TRUE),
  //fUseCannon(FALSE),
  fCannonMaterial(NULL),
  fLeadGap(0.03048*cm),
  fLeadHorizGap(0.3*cm),
  fWallMaterial(NULL),
  fDumpDepth(30.0*cm),
  fDumpRadius(30.0*cm),
  fDumpMaterial(NULL),
  fCollRadius(0.5*cm),
  fShieldHoleRadius(1.4*cm),
  fBeamPipeWall(0.29*cm),
  fBeamPipeClear(0.1*cm),
  fBeamPipeMaterial(NULL),
  fUseCryostat(TRUE),
  //fUseCryostat(FALSE),
  fCryoOVCMater("G4_Fe"),
  fCryoShieldMater("G4_Cu"),
  fTargetMaterial(NULL),
  fCryostatHeight(93.19*cm),
  //fUseAltTarget(FALSE),
  fUseAltTarget(TRUE),
  //fAltTargetSize(10.0,10.0,4.0),
  fAltTargetSize(1.963*cm,1.957*cm,1.555*cm),
  fAltTargetPosition(0.0,0.0,-66.0),
  fTargetTemperature(0.05 * kelvin),
  fUseFloor(TRUE),
  //fUseFloor(FALSE),
  fUseFloorBlock(FALSE),
  fFloorBlockHeight(0.0),
  fUseNotch(TRUE),
  fUseTableLeg(TRUE),
  fTableLegWidth(1.25 * 2.54 * cm),
  fUseCartShield(TRUE),
  fUseCartBeamhole(TRUE),
  fCartZOffset(0.0*cm),
  //fCartZOffset(-300.0*cm),
  fUseBackingWall(TRUE),
  //fUseBackingWall(FALSE),
  //fUseDumpDetector(TRUE),
  fUseDumpDetector(FALSE),
  //fBackingZposition(-75*cm),
  //fBackingZposition(-330*cm),
  fBackingZposition(-270*cm),
  fUseBackingFace(TRUE),
  //fUseBackingFace(FALSE),
  fBackingFaceThick(0.5 * mm),
  fBackingFaceMater("G4_AIR"),
  fBackingType(1),
  fBackingMisalign(0.0 * cm, 0.0 * cm, 0.0 * cm),
  fBeamScintDim(0.4 * cm, 5.0 * cm, 0.4 * cm),
  //fScatScintDim(30.0 * cm, 2.0 * cm, 2.0 * cm),
  fScatScintDim(200.0 * cm, 1.7 * cm, 4.0 * cm),
  //fScatScintGap(1.0 * cm),
  fScatScintGap(0.5 * cm),
  //fScatMinRadius(10.0 * cm),
  fScatMinRadius(15.0 * cm),
  //fNumScatScint(10),
  fNumScatScint(1),
  fParametrization(TRUE)
{
   fMessenger = new IronFilterDetectorMessenger(this);
   CustomMaterials();
   SetWallMaterial("G4_Pb");
   SetDumpMaterial("POLY_LUMBER");
   //SetTargetMaterial("G4_Ge_cryo");
   SetTargetMaterial("G4_Sn_cryo");
   //SetTargetMaterial("G4_Galactic");
   //SetCannonMaterial("Borated_Poly");
   SetCannonMaterial("EJ_301_Material");
   SetBeamPipeMaterial("G4_POLYVINYL_CHLORIDE");
   SetEnvironmentMaterial("G4_AIR");
//
//  Default parameterization set to nominal shield:
//
   G4ThreeVector innerDefaultAspect(0.4,0.5,0.6);
   G4ThreeVector middleDefaultAspect(0.5,0.5,0.46154);
   G4ThreeVector outerDefaultAspect(0.5,0.5,0.5);
   G4ThreeVector skinDefaultAspect(0.5,0.5,0.5);
   G4ThreeVector innerDefaultThick(254.0,203.2,508.0);
   G4ThreeVector middleDefaultThick(457.2,457.2,495.3);
   G4ThreeVector outerDefaultThick(0.1,0.1,0.1);
   G4ThreeVector skinDefaultThick(1.0,1.0,1.0);
   G4String defaultMaterials[N_SHIELD_LAYERS] =
     {"Borated_Poly","POLY_LUMBER","G4_AIR","G4_AIR"};
   G4ThreeVector defaultThick[N_SHIELD_LAYERS] =
    {innerDefaultThick,middleDefaultThick,outerDefaultThick,
     skinDefaultThick };
   G4ThreeVector defaultAspect[N_SHIELD_LAYERS] =
    {innerDefaultAspect,middleDefaultAspect,outerDefaultAspect,
     skinDefaultAspect};
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     SetLayerMaterial(layer,defaultMaterials[layer]);
     fLayerThickness[layer] = defaultThick[layer];
     fLayerAspect[layer]    = defaultAspect[layer];
     fLayerGaps[layer]      = 0;
   }
   fBeamScintillator = 0;
   for(int counter = 0; counter < MAX_SCATTER_COUNTERS; counter++){
     fScatScintillator[counter] = 0;
   }
   strcpy(formPosOut,"  %15s position: %8.2f  %8.2f  %8.2f \n");
   strcpy(formDimOut,"%15s dimensions: %8.2f  %8.2f  %8.2f \n");
   strcpy(formTubsOut,"%15s dimensions: %8.2f  %8.2f  %8.2f  %8.2f  %8.2f \n");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::~IronFilterDetectorConstruction()
{
   delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::Construct()
{
  DumpParameters();
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  CustomMaterials();

  // Envelope parameters
  //
  const G4double env_sizeXY = 365.76*cm, env_sizeZ = 731.52*cm;
//
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = fEnvironmentMaterial;
  //
  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Envelope
  //
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//
//  Build clean room walls
//
  G4LogicalVolume* cleanRoomEnv = ConstructCleanRoom();
  G4ThreeVector cleanRoomPos = G4ThreeVector(0.0, 0.0, 0.0);
  new G4PVPlacement(0,cleanRoomPos,cleanRoomEnv,cleanRoomEnv->GetName(),
    logicEnv,false,0,checkOverlaps);
  G4VPhysicalVolume * interiorPhys = cleanRoomEnv->GetDaughter(0);
  G4LogicalVolume * interiorEnv = interiorPhys->GetLogicalVolume();
//
  G4LogicalVolume* shieldEnv;
  if(fParametrization){
    shieldEnv = ConstructLeanShield();
  }
  else{
    shieldEnv = ConstructDDShield();
  }
  G4VPhysicalVolume * shieldPhys = PositionLeanShield();
  G4ThreeVector shieldDDPos  = LocateDaughter(interiorEnv,shieldPhys);

  G4LogicalVolume* beamDumpEnv    = ConstructBeamDump();
  G4LogicalVolume* cryostat       = ConstructCryostat();

//
  G4VPhysicalVolume * ddGen = 0;
  G4LogicalVolume   * ddGenEnv = 0;
  G4VPhysicalVolume * sourcePhys = 0;
  if((ddGen = G4PhysicalVolumeStore::GetInstance()->GetVolume("DDGener"))){
    ddGenEnv = ddGen->GetLogicalVolume();
    if(ddGenEnv->GetNoDaughters() == 1){
      sourcePhys = ddGenEnv->GetDaughter(0);
    }
    else{
      G4cout << "  Generator has no daughters" << G4endl;
    }
  }

  G4ThreeVector cryostatPlugPos;
  G4ThreeVector cryostatPlugBottomPos;
  G4VPhysicalVolume * det[N_DETECTORS];
  if(fUseCryostat){
    PositionCryostat();
    for(int idet = 0; idet < N_DETECTORS ; idet++){
      sprintf(name,"Det_%i",idet);
      if((det[idet] = G4PhysicalVolumeStore::GetInstance()->GetVolume(name))){
      }
      else{
        G4cout << name << " not found" << G4endl;
	det[idet] = 0;
      }
    }
    sprintf(name,"PlugCu");
    G4VPhysicalVolume * plugCu =
      G4PhysicalVolumeStore::GetInstance()->GetVolume(name);
    cryostatPlugPos = LocateDaughter(interiorEnv,plugCu);
    G4LogicalVolume * plugCuVol = plugCu ->GetLogicalVolume();
    cryostatPlugBottomPos = cryostatPlugPos;
    cryostatPlugBottomPos.setY(cryostatPlugPos.y() +
        plugCuVol->GetSolid()->GetExtent().GetZmin());
  }
  G4ThreeVector brickHolePos;
  G4VPhysicalVolume * beamHolePhys[N_SHIELD_LAYERS];
  G4VPhysicalVolume * layerPhys[N_SHIELD_LAYERS];
  if(fParametrization){
    G4ThreeVector layerPos[N_SHIELD_LAYERS];
    for(int layer = N_SHIELD_LAYERS - 1; layer >= 0; layer--){
      sprintf(name,"Layer_%i",layer);
      layerPhys[layer] =
        G4PhysicalVolumeStore::GetInstance()->GetVolume(name);
      if(layerPhys[layer]){
        G4ThreeVector localPos = layerPhys[layer]->GetTranslation();
        G4LogicalVolume * mother = layerPhys[layer]->GetMotherLogical();
	if(mother){
          G4cout << name << " position: " << localPos
	         << " in " << mother->GetName() << G4endl;
          G4cout << " Mother: " << mother->GetName() << G4endl;
          for(int l = 0; l <= layer; l++){
            layerPos[l] += localPos;
          }
        }
        else{
           G4cout << name << " was not found " << G4endl;
        }
      }
      else{
        G4cout << name << " was not found " << G4endl;
      }
    }
    for(int layer = 0; layer < N_SHIELD_LAYERS - 1; layer++){
      sprintf(name,"BeamClear_%i",layer);
      beamHolePhys[layer] =
        G4PhysicalVolumeStore::GetInstance()->GetVolume(name);
    }
  }
//
  G4ThreeVector shieldExtentMin(shieldEnv->GetSolid()->GetExtent().GetXmin(),
                                shieldEnv->GetSolid()->GetExtent().GetYmin(),
                                shieldEnv->GetSolid()->GetExtent().GetZmin());
  G4ThreeVector shieldExtentMax(shieldEnv->GetSolid()->GetExtent().GetXmax(),
                                shieldEnv->GetSolid()->GetExtent().GetYmax(),
                                shieldEnv->GetSolid()->GetExtent().GetZmax());
  shieldExtentMin += shieldDDPos;
  shieldExtentMax += shieldDDPos;
//
//  Place the cart
//
  G4LogicalVolume* cartShieldEnv = 0;
  G4ThreeVector cartPlatePos(0.,0.,0.);
  G4ThreeVector cartShieldPos(0.,0.,0.);
  G4VPhysicalVolume * cartShield = 0;
  G4VPhysicalVolume * cartPlate = 0;
  if(fUseCartShield){
    cartShieldEnv  = ConstructCart();
    cartShield = PositionCart();
    cartShieldPos = cartShield->GetTranslation();
    cartPlate = G4PhysicalVolumeStore::GetInstance()->GetVolume("CartPlate");
    cartPlatePos = cartPlate->GetTranslation();
  }
//
//   Figure out the beam holes
//
  G4ThreeVector intExtentMin(interiorEnv->GetSolid()->GetExtent().GetXmin(),
                             interiorEnv->GetSolid()->GetExtent().GetYmin(),
                             interiorEnv->GetSolid()->GetExtent().GetZmin());
  G4ThreeVector intExtentMax(interiorEnv->GetSolid()->GetExtent().GetXmax(),
                             interiorEnv->GetSolid()->GetExtent().GetYmax(),
                             interiorEnv->GetSolid()->GetExtent().GetZmax());

  G4ThreeVector beamDumpPos = LocateDaughter(interiorEnv,sourcePhys);
  beamDumpPos.setZ(intExtentMin.z() -
                   beamDumpEnv->GetSolid()->GetExtent().GetZmin());
//
  G4VPhysicalVolume * beamDumpPhys =
    new G4PVPlacement(0,beamDumpPos,beamDumpEnv,beamDumpEnv->GetName(),
      interiorEnv,false,0,checkOverlaps);

      // Define cylinder dimensions
      G4double innerRadius = 0.0 * cm;
      G4double outerRadius = 7.6/2.0 * cm;
      G4double halfHeight = 7.6/2.0 * cm;
      G4double startAngle = 0.0 * deg;
      G4double spanningAngle = 360.0 * deg;



      // Create a rotation matrix to rotate by 90 degrees around the y-axis
      G4RotationMatrix* rotation = new G4RotationMatrix();
      rotation->rotateX(90 * deg);  // 90 degrees in radians

      G4Color red(1.0,0.0,0.0);
      G4VisAttributes *att_red = new G4VisAttributes(red);


      // Create the cylinder geometry (as G4Tubs or G4Box, depending on your design)
      G4Tubs* cylinderSolid = new G4Tubs("Cylinder", innerRadius, outerRadius, halfHeight, startAngle, spanningAngle);

         // Place the cylinder at the new position (same x, y as barrel, custom z)
         //cylinder's z-coordinate (you choose this value)
         G4double customZ = 460.0*cm;
         G4ThreeVector cylinderPos2(beamDumpPos.x(), beamDumpPos.y(), beamDumpPos.z()+customZ);
         // Create the logical volume for the cylinder
         G4LogicalVolume* cylinderLog2 = new G4LogicalVolume(cylinderSolid, fCannonMaterial, "Cylinder2");

         new G4PVPlacement(rotation,                   // No rotation
                        cylinderPos2,          // Cylinder's position
                        cylinderLog2,          // Logical volume
                        "LiquidScintillator_2",           // Name
                        interiorEnv,         // Parent volume (same as barrel)
                        false,                // No boolean operation
                        0,                    // Copy number
                        checkOverlaps);       // Overlap check
         cylinderLog2->SetVisAttributes(att_red);


         // Place the cylinder at the new position (same x, y as barrel, custom z)

         //cylinder's z-coordinate (you choose this value)
          customZ = 350.0*cm;
          G4ThreeVector cylinderPos3(beamDumpPos.x(), beamDumpPos.y(), beamDumpPos.z()+customZ);
          // Create the logical volume for the cylinder
          G4LogicalVolume* cylinderLog3 = new G4LogicalVolume(cylinderSolid, fCannonMaterial, "Cylinder3");

          new G4PVPlacement(rotation,                   // No rotation
                            cylinderPos3,          // Cylinder's position
                            cylinderLog3,          // Logical volume
                            "LiquidScintillator_3",           // Name
                            interiorEnv,         // Parent volume (same as barrel)
                            false,                // No boolean operation
                            0,                    // Copy number
                            checkOverlaps);       // Overlap check
          cylinderLog3->SetVisAttributes(att_red);


  LocateDaughter(interiorEnv,beamDumpPhys);
//
//  Construct and place the south wall plug:
//
  G4LogicalVolume * wallPlug = ConstructSWallPlug();
  G4VPhysicalVolume * wallPlugPhys = PositionSWallPlug();
//
//  Set the backing wall:
//
  G4LogicalVolume * backingWall  = ConstructBackingArray();
  if(fUseBackingFace && cartShieldEnv){
    ConstructBackingFace();
  }
  G4VPhysicalVolume * backingWallPhys = PositionBackingArray();
//
//   Place the dump detector:
//
  G4LogicalVolume * dumpDetVol = ConstructDumpDetector();
  //G4LogicalVolume * dumpDetVol = 0;
  G4VPhysicalVolume * dumpDetPhys = 0;
  if(dumpDetVol){
    G4ThreeVector dumpDetPos  = beamDumpPos;
    dumpDetPos.setZ(beamDumpPos.z() +
                   beamDumpEnv->GetSolid()->GetExtent().GetZmax() +
                   dumpDetVol->GetSolid()->GetExtent().GetZmax());
    sprintf(lineOutput,formPosOut,dumpDetVol->GetName().c_str(),
         dumpDetPos.x(),dumpDetPos.y(),dumpDetPos.z());
    G4cout << lineOutput;
    //dumpDetPhys = new G4PVPlacement(0,dumpDetPos,dumpDetVol,
      //dumpDetVol->GetName(),interiorEnv,false,2,checkOverlaps);
  }
  else{
    G4cout << "No dump detector returned" << G4endl;
  }
//
//  Place the "bottom" detectors into the cart shield.
//
  if(cartShieldEnv){
    G4LogicalVolume * cartBottomDetector  = ConstructBottomDetector();
    PositionBottomArray();
  }
//
  G4VPhysicalVolume * barrel =
    G4PhysicalVolumeStore::GetInstance()->GetVolume("Barrel");
  G4ThreeVector barrelPos;
  double barrelLength = 0.0;
  if(barrel){
     barrelPos = barrel->GetTranslation();
     G4LogicalVolume * barrelVol = barrel->GetLogicalVolume();
     barrelLength = barrelVol->GetSolid()->GetExtent().GetZmax();
  }
//
  printf("\n*************************************************************\n \n");
  G4cout << "            Final Dimensions and Positions "  << G4endl << G4endl;
  LocateDaughter(logicWorld,interiorPhys);
  G4cout << "Extent of the interior: "  << G4endl;
  G4cout << "   X range: " << intExtentMin.x() << " - " <<
                              intExtentMax.x() << G4endl;
  G4cout << "   Y range: " << intExtentMin.y() << " - " <<
                              intExtentMax.y() << G4endl;
  G4cout << "   Z range: " << intExtentMin.z() << " - " <<
                              intExtentMax.z() << G4endl;
  G4cout << "Extent of " << shieldEnv->GetName() << ": "  << G4endl;
  G4cout << "   X range: " << shieldEnv->GetSolid()->GetExtent().GetXmin()
                  << " - " << shieldEnv->GetSolid()->GetExtent().GetXmax()
	          << G4endl;
  G4cout << "   Y range: " << shieldEnv->GetSolid()->GetExtent().GetYmin()
                  << " - " << shieldEnv->GetSolid()->GetExtent().GetYmax()
		  << G4endl;
  G4cout << "   Z range: " << shieldEnv->GetSolid()->GetExtent().GetZmin()
                  << " - " << shieldEnv->GetSolid()->GetExtent().GetZmax()
		  << G4endl;
  G4cout << shieldEnv->GetName() << " has "
             << shieldEnv->GetNoDaughters() << " daughters" << G4endl;
  for(int daugh = 0; daugh < int(shieldEnv->GetNoDaughters()); daugh++){
    G4VPhysicalVolume * daughter = shieldEnv->GetDaughter(daugh);
    sprintf(name,"  %i   %s    Position: ",daugh,daughter->GetName().c_str());
    G4cout << name << daughter->GetTranslation() << G4endl;
  }
  for(int daugh = 0; daugh < int(shieldEnv->GetNoDaughters()); daugh++){
    G4VPhysicalVolume * daughter = shieldEnv->GetDaughter(daugh);
    LocateDaughter(interiorEnv,daughter);
  }
  LocateDaughter(interiorEnv,shieldPhys);
  G4cout << "Extent of " << shieldEnv->GetName() << " in "
         << interiorEnv->GetName() << ": " << G4endl;
  G4cout << "   X range: " << shieldExtentMin.x() << " - " <<
                              shieldExtentMax.x() << G4endl;
  G4cout << "   Y range: " << shieldExtentMin.y() << " - " <<
                              shieldExtentMax.y() << G4endl;
  G4cout << "   Z range: " << shieldExtentMin.z() << " - " <<
                              shieldExtentMax.z() << G4endl;
  G4cout << "                    Generator size: " << fGeneratorSize << G4endl;
  G4cout << "             Neutron source offset: " << fGeneratorShift << G4endl;
  LocateDaughter(shieldEnv,ddGen);
  LocateDaughter(interiorEnv,ddGen);
  LocateDaughter(interiorEnv,sourcePhys);
  for(int layer = 0; layer < N_SHIELD_LAYERS - 1; layer++){
    G4LogicalVolume * layerVol = layerPhys[layer]->GetLogicalVolume();
    LocateDaughter(layerVol,beamHolePhys[layer]);
  }
  for(int layer = 0; layer < N_SHIELD_LAYERS - 1; layer++){
    LocateDaughter(interiorEnv,beamHolePhys[layer]);
  }
  G4ThreeVector barrelPosInt = LocateDaughter(interiorEnv,barrel);
  LocateDaughter(interiorEnv,wallPlugPhys);
  G4cout << "    Barrel range(Z) in the interior: "
         << barrelPosInt.z() - barrelLength << " - "
	 << barrelPosInt.z() + barrelLength << G4endl;
  if(fUseCryostat){
    DumpFamily(interiorEnv,1);
    G4VPhysicalVolume * cryostatPhys =
      G4PhysicalVolumeStore::GetInstance()->GetVolume(cryostat->GetName());
    LocateDaughter(interiorEnv,cryostatPhys);
    for(int idet = 0; idet < N_DETECTORS ; idet++){
      LocateDaughter(interiorEnv,det[idet]);
    }
  }
//  G4cout << "     Cart position in the interior: " << cartShieldPos << G4endl;
//  G4cout << "  Backing position in the interior: " << backingPosInt << G4endl;
//  G4cout << "Beam dump position in the interior: " << beamDumpPos << G4endl;
  if(cartShieldEnv){
    LocateDaughter(interiorEnv,cartShield);
    for(int idet = 0; idet < int(cartShieldEnv->GetNoDaughters()) ; idet++){
      LocateDaughter(interiorEnv,cartShieldEnv->GetDaughter(idet));
    }
  }
  //LocateDaughter(interiorEnv,dumpDetPhys);

  G4cout << G4endl << "  Alignment checks " << G4endl;

  G4VPhysicalVolume * basePlate =
    G4PhysicalVolumeStore::GetInstance()->GetVolume("Base Plate");
  G4LogicalVolume * basePlateEnv = basePlate->GetLogicalVolume();
  G4ThreeVector basePosInt =LocateDaughter(interiorEnv,basePlate);
  G4ThreeVector beamWRTFloor = beamDumpPos  - intExtentMin;
  G4ThreeVector cartWRTFloor = cartShieldPos + cartPlatePos - intExtentMin;
  G4ThreeVector baseWRTFloor = basePosInt   - intExtentMin;
  G4ThreeVector plugCuWRTFloor = cryostatPlugPos   - intExtentMin;
  G4ThreeVector plugCuBottomWRTFloor = cryostatPlugBottomPos - intExtentMin;
  if(cartPlate){
    G4LogicalVolume * cartPlateEnv = cartPlate->GetLogicalVolume();
    cartWRTFloor.setY(cartWRTFloor.y() +
                      cartPlateEnv->GetSolid()->GetExtent().GetYmax());
  }
  baseWRTFloor.setY(baseWRTFloor.y() +
                    basePlateEnv->GetSolid()->GetExtent().GetYmax());
  double beamHoleBotWRTFloor = 0.0;
  if(fUseSouthWall){
    G4VPhysicalVolume * sWallCenter =
      G4PhysicalVolumeStore::GetInstance()->GetVolume("CenterLWall");
    G4ThreeVector sWallWRTShield = sWallCenter->GetTranslation();
    G4ThreeVector sWallWRTFloor = sWallWRTShield + shieldDDPos - intExtentMin;
    G4LogicalVolume * sWallCenterVol =
      sWallCenter->GetLogicalVolume();
    double sWallHeight = sWallCenterVol->GetSolid()->GetExtent().GetYmax();
    beamHoleBotWRTFloor = sWallWRTFloor.y() + sWallHeight;
  }

  printf("     Beam height from floor %6.1f \n",beamWRTFloor.y());
  printf("     Cart height from floor %6.1f \n",cartWRTFloor.y());
  printf("     Base height from floor %6.1f \n",baseWRTFloor.y());
  printf("       Cryo plug from floor %6.1f \n",plugCuWRTFloor.y());
  printf("Cryo plug bottom from floor %6.1f \n",plugCuBottomWRTFloor.y());
  printf("Wall hole bottom from floor %6.1f \n",beamHoleBotWRTFloor);

  DumpFamily(cartShieldEnv,0);

  if(backingWall){
    G4cout << G4endl<< backingWall->GetName() << " positions " << G4endl;
    LocateDaughter(interiorEnv,backingWallPhys);
    int nDaugh0 = backingWall->GetNoDaughters();
    for(int daugh = 0; daugh < nDaugh0 ; daugh++){
      G4VPhysicalVolume * daughPhys0 = backingWall->GetDaughter(daugh);
      G4ThreeVector daughTrans0 = daughPhys0->GetTranslation();
      G4cout << daughPhys0->GetName() << " position: "
             << daughPhys0->GetTranslation() << G4endl;
      G4LogicalVolume * daughVol0 = daughPhys0->GetLogicalVolume();
      int nDaugh1 = daughVol0->GetNoDaughters();
      for(int daugh1 = 0; daugh1 < nDaugh1 ; daugh1++){
        G4VPhysicalVolume * daughPhys1 = daughVol0->GetDaughter(daugh1);
        G4ThreeVector daughTrans1 = daughPhys1->GetTranslation();
        G4cout << "  " << daughPhys1->GetName() << " position: "
               << daughPhys1->GetTranslation() << G4endl;
        G4LogicalVolume * daughVol1 = daughPhys1->GetLogicalVolume();
        int nDaugh2 = daughVol1->GetNoDaughters();
        for(int daugh2 = 0; daugh2 < nDaugh2 ; daugh2++){
          G4VPhysicalVolume * daughPhys2 = daughVol1->GetDaughter(daugh2);
          LocateDaughter(interiorEnv,daughPhys2);
        }
      }
    }
  }

  printf("\n*************************************************************\n \n");
//
// **********************************************************************
//
//   always return the physical World
//

//G4PhysicalVolumeStore* pVolumeStore = G4PhysicalVolumeStore::GetInstance();

//for (auto pVolume : *pVolumeStore) {
//  G4cout << "Physical Volume: " << pVolume->GetName()
//         << ", Mother Volume: "
//         << (pVolume->GetMotherLogical() ? pVolume->GetMotherLogical()->GetName() : "None")
//         << G4endl;
//}

// Access the logical volume store
//G4LogicalVolumeStore* lVolumeStore = G4LogicalVolumeStore::GetInstance();

// Iterate over all logical volumes
//for (auto lVolume : *lVolumeStore) {
//    // Get the associated solid and material
//    G4VSolid* solid = lVolume->GetSolid();
//    G4Material* material = lVolume->GetMaterial();

    // Print the solid name and material name
//    if (solid && material) {
//        G4cout << "Solid: " << solid->GetName()
//               << ", Material: " << material->GetName() << G4endl;
//    }
//}


  return physWorld;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void IronFilterDetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors
  const int NumTrackingDets = 4;

  G4String cleanRoomName  = "CleanRoom";
  G4String targetName     = "DetVol";
  G4String targetIncName  = "DetVolInc";
  G4String backingName    = "BackingLayer";
  G4String backingIncName = "BackingFace";
  G4String shieldSkinName = "Layer_3";
  G4String beamDetName    = "Scintillator";

  G4String cleanRoomSDName  = "B1/CleanRoomSD";
  G4String targetSDname     = "B1/TargetSD";
  G4String targetIncSDName  = "B1/TargetIncSD";
  G4String backingSDName    = "B1/BackingWallSD";
  G4String backingIncSDName = "B1/BackingWallIncSD";
  G4String shieldSkinSDName = "B1/ShieldSkinSD";
  G4String beamDetSDName    = "B1/ScintillatorSD";

  G4String cleanRoomCollName  = "CleanRoomHitsCollection";
  G4String targetCollName     = "TargetHitsCollection";
  G4String targetIncCollName  = "TargetIncidentCollection";
  G4String backingCollName    = "BackingWallHitsCollection";
  G4String backingIncCollName = "BackingWallIncidentCollection";
  G4String shieldSkinCollName = "ShieldSkinCollection";
  G4String beamDetCollName    = "ScintillatorCollection";

  G4String volTrackingName[NumTrackingDets] =
   {cleanRoomName,targetIncName,backingIncName,shieldSkinName};
  G4String detTrackingName[NumTrackingDets] =
   {cleanRoomSDName,targetIncSDName,backingIncSDName,shieldSkinSDName};
  G4String hitTrackingName[NumTrackingDets] =
   {cleanRoomCollName,targetIncCollName,backingIncCollName,shieldSkinCollName};
  G4String volName;
  G4String detName;
  G4String hitName;
  G4VSensitiveDetector * thisDetector;
  const char * make_message = " does not exist as a sensitive volume";
  const char * skip_message = " already exists as a sensitive volume";
//
  G4cout << G4endl << "In ConstructSDandField..." << G4endl;
//
//  If the sensitive detector already exists, don't create it again.
//
  for(int det = 0; det < NumTrackingDets; det++){
    volName = volTrackingName[det];
    detName = detTrackingName[det];
    hitName = hitTrackingName[det];
    G4LogicalVolume * volumeLogic =
      G4LogicalVolumeStore::GetInstance()->GetVolume(volName);
    if(volumeLogic){
      thisDetector = G4SDManager::GetSDMpointer()->
        G4SDManager::FindSensitiveDetector(detName,true);
      if(thisDetector){
        G4cout << detName << skip_message << G4endl;
      }
      else{
        G4cout << detName << make_message << G4endl;
        B1TrackerSD* aTrackerSD = new B1TrackerSD(detName,hitName);
        G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
        thisDetector = G4SDManager::GetSDMpointer()->
          G4SDManager::FindSensitiveDetector(detName,true);
      }
      SetSensitiveDetector(volName, thisDetector, true);
    }
//    G4LogicalVolume * volumeLogic =
//      G4LogicalVolumeStore::GetInstance()->GetVolume(volName);
//    if(volumeLogic) SetSensitiveDetector(volName, thisDetector, true);
  }
  printf("   Sensitive tracking volumes: \n");
  for(int det = 0; det < NumTrackingDets; det++){
    printf("Det: %i  Vol.: %s  DetName: %s  Hit: %s \n",det,
    volTrackingName[det].c_str(),detTrackingName[det].c_str(),
    hitTrackingName[det].c_str());
  }
//
  volName = targetName;
  detName = targetSDname;
  hitName = targetCollName;
  G4LogicalVolume * volumeLogic =
    G4LogicalVolumeStore::GetInstance()->GetVolume(volName);
  if(volumeLogic){
    thisDetector = G4SDManager::GetSDMpointer()->
      G4SDManager::FindSensitiveDetector(detName,true);
    if(thisDetector){
      G4cout << detName << skip_message << G4endl;
    }
    else{
      G4cout << detName << make_message << G4endl;
      if(G4LogicalVolumeStore::GetInstance()->GetVolume(volName)){
        B1TargetSD* aTargetSD = new B1TargetSD(detName,hitName);
        G4SDManager::GetSDMpointer()->AddNewDetector(aTargetSD);
        thisDetector = G4SDManager::GetSDMpointer()->
          G4SDManager::FindSensitiveDetector(detName,true);
      }
    }
    SetSensitiveDetector(volName, thisDetector, true);
  }
//  G4LogicalVolume * volumeLogic =
//    G4LogicalVolumeStore::GetInstance()->GetVolume(volName);
//  if(volumeLogic)  SetSensitiveDetector(volName, thisDetector, true);
//
//  volName = backingName;
//  detName = backingSDName;
//  hitName = backingCollName;
//  thisDetector = G4SDManager::GetSDMpointer()->
//    G4SDManager::FindSensitiveDetector(detName,true);
//  if(thisDetector){
//    G4cout << detName << skip_message << G4endl;
//  }
//  else{
//    G4cout << detName << make_message << G4endl;
//    if(G4LogicalVolumeStore::GetInstance()->GetVolume(volName)){
//      B1BackingSD* aBackingSD = new B1BackingSD(detName,hitName);
//      G4SDManager::GetSDMpointer()->AddNewDetector(aBackingSD);
//      thisDetector = G4SDManager::GetSDMpointer()->
//        G4SDManager::FindSensitiveDetector(detName,true);
//    }
//  }
//  if(thisDetector) SetSensitiveDetector(volName, thisDetector, true);
//
  if(fBackingType != 0){
    volName = beamDetName;
    detName = beamDetSDName;
    hitName = beamDetCollName;
    thisDetector = G4SDManager::GetSDMpointer()->
      G4SDManager::FindSensitiveDetector(detName,true);
//    if(thisDetector){
//      G4cout << detName << skip_message << G4endl;
//    }
//    else{
      G4cout << detName << make_message << G4endl;
      if(G4LogicalVolumeStore::GetInstance()->GetVolume(volName)){
        B1ScintillatorSD* aScintillatorSD = new B1ScintillatorSD(detName,hitName);
        G4SDManager::GetSDMpointer()->AddNewDetector(aScintillatorSD);
//        thisDetector = G4SDManager::GetSDMpointer()->
//          G4SDManager::FindSensitiveDetector(detName,true);
        fBeamScintillator->SetSensitiveDetector(aScintillatorSD);
        for(int ring = 0; ring < fNumScatScint; ring++){
          fScatScintillator[ring]->SetSensitiveDetector(aScintillatorSD);
        }
        for(int lsize = 0; lsize < MAX_DUMP_RINGS; lsize++){
          fDumpScintillator[lsize]->SetSensitiveDetector(aScintillatorSD);
        }
        fBottomScintillator->SetSensitiveDetector(aScintillatorSD);
        G4VPhysicalVolume * sourcePhys = 0;
        G4ThreeVector sourcePos;
        if((sourcePhys =
	  G4PhysicalVolumeStore::GetInstance()->GetVolume("BeamDump"))){
          sourcePos = sourcePhys->GetTranslation();
	  G4cout << sourcePhys->GetName()
	         << " position: " << sourcePos << G4endl;
          aScintillatorSD->SetBeamPosition(sourcePos);
        }
      }
//    }
//    SetSensitiveDetector(volName, thisDetector, true);
  }
//
  G4SDManager::GetSDMpointer()->G4SDManager::ListTree();
//
  G4cout << G4endl << "Completed ConstructSDandField..." << G4endl;
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructCleanRoom(){
//
//  Make the clean room volume:
//
     G4cout << G4endl << "In ConstructCleanRoom..." << G4endl;

    G4bool checkOverlaps = true;
    G4NistManager* nist = G4NistManager::Instance();
    G4LogicalVolume* worldVolume =
         G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    G4ThreeVector worldVolDim =
      G4ThreeVector(worldVolume->GetSolid()->GetExtent().GetXmax(),
                    worldVolume->GetSolid()->GetExtent().GetYmax(),
                    worldVolume->GetSolid()->GetExtent().GetZmax());
    sprintf(lineOutput,formDimOut,(worldVolume->GetName()).c_str(),
         worldVolDim.x(),worldVolDim.y(),worldVolDim.z());
    G4cout << lineOutput;
    G4ThreeVector cleanRoomDim = (5.0/6.0) * worldVolDim;
//
//  Build clean room walls
//
//    G4double wallThickness = 8*cm;
//  Make this thin, to avoid confusion with the positions of things
//  with respect to the hits.
//
    G4double wallThickness = 0.01*mm;
//    G4Material* wall_mat  = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Box * cleanRoom = new G4Box("CleanRoom",cleanRoomDim.x(),
                            cleanRoomDim.y(),cleanRoomDim.z());
    sprintf(lineOutput,formDimOut,(cleanRoom->GetName()).c_str(),
         cleanRoomDim.x(),cleanRoomDim.y(),cleanRoomDim.z());
    G4cout << lineOutput;
    G4Box * interior = new G4Box("Interior",
                                cleanRoom->GetXHalfLength() - wallThickness,
                                cleanRoom->GetYHalfLength() - wallThickness,
                                cleanRoom->GetZHalfLength() - wallThickness);
    sprintf(lineOutput,formDimOut,(interior->GetName()).c_str(),
         interior->GetXHalfLength(),
	 interior->GetYHalfLength(),interior->GetZHalfLength());
    G4cout << lineOutput;
    G4LogicalVolume* cleanRoomEnv =
      new G4LogicalVolume(cleanRoom,fEnvironmentMaterial,cleanRoom->GetName());
    G4LogicalVolume* interiorEnv =
      new G4LogicalVolume(interior,fEnvironmentMaterial,interior->GetName());
    G4VisAttributes *clear = new G4VisAttributes(false);
    interiorEnv->SetVisAttributes(clear);
    G4Color white(1.0,1.0,1.0);
    G4VisAttributes *att_white = new G4VisAttributes(white);
    interiorEnv->SetVisAttributes(att_white);
    cleanRoomEnv->SetVisAttributes(att_white);
    G4ThreeVector cleanRoomPos = G4ThreeVector(0.0, 0.0, 0.0);
    G4ThreeVector interiorPos  = G4ThreeVector(0.0, 0.0, 0.0);
//    interiorPos.setY(interior->GetYHalfLength() - cleanRoom->GetYHalfLength());
    sprintf(lineOutput,formPosOut,(interior->GetName()).c_str(),
         interiorPos.x(),interiorPos.y(),interiorPos.z());
    G4cout << lineOutput;
    new G4PVPlacement(0,interiorPos,interiorEnv,interiorEnv->GetName(),
      cleanRoomEnv,false,0,checkOverlaps);
  if(fUseFloor){
    G4Material* floor_mat = nist->FindOrBuildMaterial("G4_CONCRETE");
    G4double floorThickness = worldVolume->GetSolid()->GetExtent().GetYmax() -
                              cleanRoom->GetYHalfLength();
    G4Box * floor = new G4Box("Floor",cleanRoom->GetXHalfLength(),
                              0.5 * floorThickness,cleanRoom->GetZHalfLength());
    sprintf(lineOutput,formDimOut,(floor->GetName()).c_str(),
         floor->GetXHalfLength(),
	 floor->GetYHalfLength(),floor->GetZHalfLength());
    G4cout << lineOutput;
    G4LogicalVolume* floorEnv =
      new G4LogicalVolume(floor,floor_mat,"Floor");
    G4Color mud(0.3,0.3,0.3);
    G4VisAttributes *att_mud = new G4VisAttributes(mud);
    floorEnv->SetVisAttributes(att_mud);
    G4ThreeVector floorPos     = G4ThreeVector(0.0,
      -(worldVolDim.y() - 0.5 * floorThickness), 0.0);
    sprintf(lineOutput,formPosOut,(floor->GetName()).c_str(),
         floorPos.x(),floorPos.y(),floorPos.z());
    G4cout << lineOutput;
    new G4PVPlacement(0,floorPos,floorEnv,floorEnv->GetName(),worldVolume,
       false,0,checkOverlaps);
  }
    return cleanRoomEnv;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructDDGenerator(){
//
//  Make the generator volume:
//
   G4cout << G4endl << "In ConstructDDGenerator..." << G4endl;
//
   G4bool checkOverlaps = true;
// Open volume for the generator from drawing F10162176,
// 13.62 x 41 x 20 inches.
   const G4ThreeVector generVolDim = 0.5 * fGeneratorSize;
   G4Box * gener = new G4Box("DDGener",generVolDim.x(),
                              generVolDim.y(),generVolDim.z());
   G4LogicalVolume* generVol =
     new G4LogicalVolume(gener,fEnvironmentMaterial,gener->GetName());
//
   G4Color white(1.0,1.0,1.0);
   G4VisAttributes *att_white = new G4VisAttributes(white);
   generVol->SetVisAttributes(att_white);
//
//  Position the neutron source within the volume.
//  It is located 19.4 cm above the top of the bottom flange (docdb 3780).
//  That flange is 2.5 cm thick, and sits on the generator stand (field
//  measurement).
//  That stand is 55.3 cm tall (nominal, drawing F10160884).
//  Adjusted to 55.8 cm (field measurements of 7 Jan. 2022).
//  The generator is centered 2.5 inches south of center (F10161100)
//
   const double sourceHeight = (19.4 + 2.5 + 55.8) * cm;
   double bottomThickness = 0.0;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
      bottomThickness += fLayerThickness[layer].y() * fLayerAspect[layer].y();
   }
   printf("  Bottom thickness: %6.2f \n",bottomThickness);
   G4ThreeVector sourceDim(5.0,5.0,5.0);
   G4ThreeVector sourcePos(0.0,0.0,0.0);
   sourcePos.setY(sourceHeight - bottomThickness - generVolDim.y());
   sourcePos += fGeneratorShift;
   G4Box * sourceBox = new G4Box("NSource",sourceDim.x(),
                                  sourceDim.y(),sourceDim.z());
   G4LogicalVolume* sourceVol =
     new G4LogicalVolume(sourceBox,fEnvironmentMaterial,sourceBox->GetName());
   sprintf(lineOutput,formDimOut,generVol->GetName().c_str(),
           generVolDim.x(),generVolDim.y(),generVolDim.z());
   G4cout << lineOutput;
   sprintf(lineOutput,formDimOut,sourceBox->GetName().c_str(),
           sourceDim.x(),sourceDim.y(),sourceDim.z());
   G4cout << lineOutput;
   sprintf(lineOutput,formPosOut,sourceBox->GetName().c_str(),
           sourcePos.x(),sourcePos.y(),sourcePos.z());
   G4cout << lineOutput;
   new G4PVPlacement(0,sourcePos,sourceVol,
         sourceBox->GetName(),generVol,false,0,checkOverlaps);

   return generVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int IronFilterDetectorConstruction::ConstructNotch(){
//
//    Create a notch in the bottom for cables and hoses.
//    This needs to know the source position in each layer frame.
//    Dimensions originate from F10162876 and references.
//
   G4cout << G4endl << "In ConstructNotch..." << G4endl;
//
   G4bool checkOverlaps = true;

   char layerName[N_SHIELD_LAYERS][80];
   G4LogicalVolume* layerVolume[N_SHIELD_LAYERS];
   G4ThreeVector layerVolDim[N_SHIELD_LAYERS];
   G4ThreeVector sourcePos[N_SHIELD_LAYERS];
//   G4ThreeVector generPos[N_SHIELD_LAYERS];

   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(layerName[layer],"Layer_%i",layer);
     layerVolume[layer] =
         G4LogicalVolumeStore::GetInstance()->GetVolume(layerName[layer]);
     layerVolDim[layer] =
     G4ThreeVector(layerVolume[layer]->GetSolid()->GetExtent().GetXmax(),
                   layerVolume[layer]->GetSolid()->GetExtent().GetYmax(),
                   layerVolume[layer]->GetSolid()->GetExtent().GetZmax());
   }

   G4VPhysicalVolume * generPhysVol = layerVolume[0]->GetDaughter(0);
   if(!generPhysVol){
     G4cout << "Could not locate generator physical volume" << G4endl;
     return 0;
   }

   G4LogicalVolume * generVol = generPhysVol->GetLogicalVolume();
   if(!generVol){
     G4cout << "Could not locate generator logical volume" << G4endl;
     return 0;
   }

   G4VPhysicalVolume * sourcePhysVol = generVol->GetDaughter(0);
   if(!sourcePhysVol){
     G4cout << "Could not locate source physical volume" << G4endl;
     return 0;
   }
//
//  Obtain the source position in the frame of each layer
//
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     G4VPhysicalVolume * daughVol = layerVolume[layer]->GetDaughter(0);
     G4ThreeVector daughPos = daughVol->GetTranslation();
     sprintf(lineOutput,formPosOut,daughVol->GetName().c_str(),
       daughPos.x(),daughPos.y(),daughPos.z());
     G4cout << lineOutput;
     if(layer == 0){
       sourcePos[layer] = sourcePhysVol->GetTranslation();
       sourcePos[layer] += daughPos;
     }
     else{
       sourcePos[layer] = sourcePos[layer - 1] + daughPos;
     }
   }
   sprintf(lineOutput,"Source position in each layer \n");
   G4cout << lineOutput;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(lineOutput,formPosOut,layerVolume[layer]->GetName().c_str(),
       sourcePos[layer].x(),sourcePos[layer].y(),sourcePos[layer].z());
     G4cout << lineOutput;
   }
//
//   Each layer has a "drain".  Dimensions from the drawings.
//    Layer 1 has a "notch".  This is horizontal, with a cross section from
//   the drawings and N-S length to fill the layer
//
   G4ThreeVector layer1NotchDim(1.25 * 2.54 * cm,
                                1.5 * 2.54 * cm, 0.0);
   G4ThreeVector notchPos;
   G4ThreeVector drainDim[N_SHIELD_LAYERS] =
     {G4ThreeVector(layer1NotchDim.x(),
                    0.5 * fLayerAspect[0].y() * fLayerThickness[0].y(),
		    1.75 * 2.54 * cm),
      G4ThreeVector(layer1NotchDim.x(),
                    3.3125 * 2.54 * cm, 1.75 * 2.54 * cm),
      layer1NotchDim,layer1NotchDim};
   G4Box * drainBox[N_SHIELD_LAYERS];
   G4LogicalVolume * drainVol[N_SHIELD_LAYERS];
   G4ThreeVector drainPos[N_SHIELD_LAYERS];
   for(int layer = 2; layer < N_SHIELD_LAYERS; layer++){
     drainDim[layer].setZ(0.5 * (1.0 - fLayerAspect[layer].z()) *
                                fLayerThickness[layer].z());
   }
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(name,"Drain_%i",layer);
     sprintf(lineOutput,formDimOut,name,
       drainDim[layer].x(),drainDim[layer].y(),drainDim[layer].z());
     G4cout << lineOutput;
     drainBox[layer] = new G4Box(name,
       drainDim[layer].x(),drainDim[layer].y(),drainDim[layer].z());
     drainVol[layer] = new G4LogicalVolume(drainBox[layer],
       fEnvironmentMaterial,drainBox[layer]->GetName());
   }
//
//   Drain[0,1] are positioned directly beneath the source
//
   for(int layer = 0; layer < 2; layer++){
     drainPos[layer] = sourcePos[layer];
     double upperEdgeY =
       fLayerAspect[layer].y() * fLayerThickness[layer].y() -
         layerVolDim[layer].y();
     drainPos[layer].setY(upperEdgeY - drainDim[layer].y());
     sprintf(lineOutput,formPosOut,drainVol[layer]->GetName().c_str(),
       drainPos[layer].x(),drainPos[layer].y(),drainPos[layer].z());
     G4cout << lineOutput;
     new G4PVPlacement(0,drainPos[layer],drainVol[layer],
       drainVol[layer]->GetName(),layerVolume[layer],false,0,checkOverlaps);
     if(layer == 1){
       layer1NotchDim.setZ(0.5 * (layerVolDim[layer].z() -
         drainPos[layer].z() - drainDim[layer].z()));
       sprintf(name,"Layer1Notch");
       G4Box * notchBox = new G4Box(name,layer1NotchDim.x(),
	 layer1NotchDim.y(),layer1NotchDim.z());
       sprintf(lineOutput,formDimOut,notchBox->GetName().c_str(),
         layer1NotchDim.x(),layer1NotchDim.y(),layer1NotchDim.z());
       G4cout << G4endl << lineOutput;
       notchPos.setX(sourcePos[layer].x());
       notchPos.setY(upperEdgeY - 2.0 * drainDim[layer].y() +
         layer1NotchDim.y());
       notchPos.setZ(layerVolDim[layer].z() - layer1NotchDim.z());
       sprintf(lineOutput,formPosOut,notchBox->GetName().c_str(),
         notchPos.x(),notchPos.y(),notchPos.z());
       G4cout << lineOutput;
       G4LogicalVolume * notchVol = new G4LogicalVolume(notchBox,
         fEnvironmentMaterial,notchBox->GetName());
       new G4PVPlacement(0,notchPos,notchVol,notchVol->GetName(),
	 layerVolume[layer],false,0,checkOverlaps);
     }
   }
   for(int layer = 2; layer < N_SHIELD_LAYERS; layer++){
     drainPos[layer] = sourcePos[layer];
     drainPos[layer].setY(sourcePos[layer].y() -
                          (sourcePos[1].y() - notchPos.y()));
     drainPos[layer].setZ(layerVolDim[layer].z() - drainDim[layer].z());
     sprintf(lineOutput,formPosOut,drainBox[layer]->GetName().c_str(),
       drainPos[layer].x(),drainPos[layer].y(),drainPos[layer].z());
     G4cout << lineOutput;
     new G4PVPlacement(0,drainPos[layer],drainVol[layer],
       drainVol[layer]->GetName(),layerVolume[layer],false,0,checkOverlaps);
   }

   return 1;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int IronFilterDetectorConstruction::ConstructTableLeg(){
//
//    Create leg holes for the bottom.
//    These need to be positioned elsewhere,
//    where generator position is known.
//
//   char name[80];
   const double hairBreadth = 1e-6;
   G4cout << G4endl << "In ConstructTableLeg..." << G4endl;
   G4Color white(1.0,1.0,1.0);
   G4VisAttributes *att_white = new G4VisAttributes(white);
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(name,"TableLeg_%i",layer);
     double legLength =
       fLayerThickness[layer].y() * fLayerAspect[layer].y();
     G4cout << name << " leg length: " << legLength << G4endl;
     if(legLength > hairBreadth){
       G4Box * legBox = new G4Box(name,
         0.5 * fTableLegWidth,0.5 * legLength,0.5 * fTableLegWidth);
       legBox->DumpInfo();
       G4LogicalVolume * drainVolume =
         new G4LogicalVolume(legBox,fEnvironmentMaterial,name);
       drainVolume->SetVisAttributes(att_white);
     }
     else{
       G4cout << "No leg created for layer " << layer << G4endl;
     }
   }
   return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructLeanShield(){
//
//   This treats the shield layers as three independent boxes.
//   More could be added.
//
   G4bool checkOverlaps = true;
   const G4ThreeVector origin(0.0,0.0,0.0);

   printf("\n******************************************************** \n \n");
   printf("                 D-D generator shield construction \n\n");
//
   G4cout << G4endl << "In ConstructLeanShield..." << G4endl;
   G4LogicalVolume * generVolume = ConstructDDGenerator();
   G4LogicalVolume * brick = ConstructLeadBrick();
   G4LogicalVolume * postVol = ConstructPosts();
   G4LogicalVolume * basePlateVolume = ConstructBasePlate();
   G4LogicalVolume * stepPlateVolume = ConstructStepPlate();
   G4LogicalVolume * wallPlate = ConstructSWallPlate();
//
   G4ThreeVector generVolDim =
     G4ThreeVector(generVolume->GetSolid()->GetExtent().GetXmax(),
                   generVolume->GetSolid()->GetExtent().GetYmax(),
                   generVolume->GetSolid()->GetExtent().GetZmax());
   G4ThreeVector brickDim =
     G4ThreeVector(brick->GetSolid()->GetExtent().GetXmax(),
                   brick->GetSolid()->GetExtent().GetYmax(),
                   brick->GetSolid()->GetExtent().GetZmax());
   G4ThreeVector postVolDim =
     G4ThreeVector(postVol->GetSolid()->GetExtent().GetXmax(),
                   postVol->GetSolid()->GetExtent().GetYmax(),
                   postVol->GetSolid()->GetExtent().GetZmax());
   G4ThreeVector wallPlateDim =
     G4ThreeVector(wallPlate->GetSolid()->GetExtent().GetXmax(),
                   wallPlate->GetSolid()->GetExtent().GetYmax(),
                   wallPlate->GetSolid()->GetExtent().GetZmax());
//
   const G4ThreeVector aspectShift(0.5,0.5,0.5);
   const G4Color whiteColor(1.0,1.0,1.0);
   const G4VisAttributes *att_white = new G4VisAttributes(whiteColor);
   const G4Color orangeColor(1.0,0.3,0.0);
   const G4VisAttributes *att_orange = new G4VisAttributes(orangeColor);
   const G4Color purple(1.0,0.0,1.0);
   const G4Color green(0.0,0.95,0.0);
   const G4Color lightGray(0.75,0.75,0.75);
   const G4Color layerColor[N_SHIELD_LAYERS] = {green,lightGray,purple};
   G4VisAttributes *att_layer[N_SHIELD_LAYERS];
   char layerName[N_SHIELD_LAYERS][80];
   char beamClearName[N_SHIELD_LAYERS][80];
   char beamPipeName[N_SHIELD_LAYERS][80];
   char beamTubeName[N_SHIELD_LAYERS][80];
   G4ThreeVector layerVolDim[N_SHIELD_LAYERS];
   G4Box * layerBox[N_SHIELD_LAYERS];
   G4Tubs * beamClear[N_SHIELD_LAYERS];
   G4Tubs * beamPipe[N_SHIELD_LAYERS];
   G4Tubs * beamTube[N_SHIELD_LAYERS];
   G4LogicalVolume* layerVolume[N_SHIELD_LAYERS];
   G4LogicalVolume*  beamClearVolume[N_SHIELD_LAYERS];
   G4LogicalVolume*  beamPipeVolume[N_SHIELD_LAYERS];
   G4LogicalVolume*  beamVolume[N_SHIELD_LAYERS];
   G4ThreeVector beamClearPos[N_SHIELD_LAYERS];
   G4ThreeVector sourcePos[N_SHIELD_LAYERS];
   G4ThreeVector generPos[N_SHIELD_LAYERS];
   G4ThreeVector layerPos[N_SHIELD_LAYERS];

   sprintf(lineOutput,formDimOut,generVolume->GetName().c_str(),
       generVolDim.x(),generVolDim.y(),generVolDim.z());
   G4cout << G4endl << lineOutput;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(layerName[layer],"Layer_%i",layer);
     sprintf(beamPipeName[layer],"BeamPipe_%i",layer);
     sprintf(beamClearName[layer],"BeamClear_%i",layer);
     sprintf(beamTubeName[layer],"BeamHole_%i",layer);
     if(layer == 0){
       layerVolDim[layer] = generVolDim + 0.5 * fLayerThickness[layer];
     }
     else{
       layerVolDim[layer] =
         layerVolDim[layer - 1] + 0.5 * fLayerThickness[layer];
     }
     layerBox[layer] = new G4Box(layerName[layer],layerVolDim[layer].x(),
                       layerVolDim[layer].y(),layerVolDim[layer].z());
     layerVolume[layer] = new G4LogicalVolume(layerBox[layer],
                               fLayerMaterial[layer],layerName[layer]);
     att_layer[layer] = new G4VisAttributes(layerColor[layer]);
     layerVolume[layer]->SetVisAttributes(att_layer[layer]);
     const double seeThrough = 2.0*mm;
     if((layer > 0) && (fLayerThickness[layer].mag() < seeThrough)){
       const G4VisAttributes * lastAtt =
         layerVolume[layer - 1]->GetVisAttributes();
       layerVolume[layer]->SetVisAttributes(lastAtt);
     }
   }
//
//  Place each layer into its mother
//  Place generator into layer 0
//
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     G4cout << G4endl << "Build " << layerName[layer] << G4endl;
     sprintf(lineOutput,formDimOut,
       layerName[layer],layerVolDim[layer].x(),
       layerVolDim[layer].y(),layerVolDim[layer].z());
     G4cout << G4endl << lineOutput;
     G4ThreeVector aspectOff = fLayerAspect[layer] - aspectShift;
     layerPos[layer].setX(fLayerThickness[layer].x() * aspectOff.x());
     layerPos[layer].setY(fLayerThickness[layer].y() * aspectOff.y());
     layerPos[layer].setZ(fLayerThickness[layer].z() * aspectOff.z());
     G4LogicalVolume * storedVolume;
     G4ThreeVector prevVolDim;
     if(layer == 0){
       generPos[layer] = layerPos[layer];
       storedVolume = generVolume;
       prevVolDim = generVolDim;
       G4VPhysicalVolume * sourcePhys = 0;
       if((sourcePhys =
           G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource"))){
         sourcePos[layer] = sourcePhys->GetTranslation();
         sourcePos[layer] += generPos[layer];
       }
     }
     else{
       generPos[layer]  = generPos[layer - 1] + layerPos[layer];
       sourcePos[layer] = sourcePos[layer - 1] + layerPos[layer];
       storedVolume = layerVolume[layer - 1];
       prevVolDim = layerVolDim[layer - 1];
     }
     sprintf(lineOutput,formPosOut,
       storedVolume->GetName().c_str(),layerPos[layer].x(),
       layerPos[layer].y(),layerPos[layer].z());
     G4cout << lineOutput;
     G4ThreeVector thickness[2] =
       {layerVolDim[layer] - prevVolDim + layerPos[layer],
        layerVolDim[layer] - prevVolDim - layerPos[layer]};
     G4cout << "     Low side thickness: " << thickness[0] << G4endl;
     G4cout << "    High side thickness: " << thickness[1] << G4endl;
     new G4PVPlacement(0,layerPos[layer],storedVolume,
         storedVolume->GetName(),layerVolume[layer],false,0,checkOverlaps);

     double tubeLength =
       0.5 *(layerVolDim[layer].z() - prevVolDim.z() + layerPos[layer].z());
     sprintf(lineOutput,"TubeLength: %8.3e \n", tubeLength);
     G4cout << lineOutput;
//
//    The three layer beam pipe.
//    The mother is BeamClear, full of air
//    Daughter is BeamPipe, smaller than mother by a clearance, some material.
//    Grandaughter is BeamVolume, smaller than BeamPipe by a wall thickness.
//    Beam hole is omitted for the outermost, skin layer.
//
     if((tubeLength > 0.0) && (fShieldHoleRadius > 1e-3 * mm) &&
        (layer < N_SHIELD_LAYERS - 1)){
       beamClear[layer] = new G4Tubs(beamPipeName[layer],0.0,
                                    fShieldHoleRadius + fBeamPipeWall + fBeamPipeClear,
                                    tubeLength,0.0,CLHEP::twopi);
       beamPipe[layer] = new G4Tubs(beamPipeName[layer],0.0,
                                    fShieldHoleRadius + fBeamPipeWall,
                                    tubeLength,0.0,CLHEP::twopi);
       beamTube[layer] = new G4Tubs(beamTubeName[layer],0.0,fShieldHoleRadius,
                                    tubeLength,0.0,CLHEP::twopi);
       beamClearVolume[layer] =  new G4LogicalVolume(beamClear[layer],
                                   fEnvironmentMaterial,beamClearName[layer]);
       beamPipeVolume[layer] =  new G4LogicalVolume(beamPipe[layer],
                                   fBeamPipeMaterial,beamPipeName[layer]);
       beamVolume[layer] =  new G4LogicalVolume(beamTube[layer],
                                   fEnvironmentMaterial,beamTubeName[layer]);
       beamClearVolume[layer]->SetVisAttributes(att_white);
       beamPipeVolume[layer]->SetVisAttributes(att_orange);
       beamVolume[layer]->SetVisAttributes(att_white);
//
       new G4PVPlacement(0,origin,beamVolume[layer],
         beamVolume[layer]->GetName(),beamPipeVolume[layer],
	 false,0,checkOverlaps);
       new G4PVPlacement(0,origin,beamPipeVolume[layer],
         beamPipeVolume[layer]->GetName(),beamClearVolume[layer],
	 false,0,checkOverlaps);
       beamClearPos[layer] = sourcePos[layer];
       beamClearPos[layer].setZ(tubeLength - layerVolDim[layer].z());
       G4cout << "beamClearPos[" << layer << "]: " << beamClearPos[layer] << G4endl;
       new G4PVPlacement(0,beamClearPos[layer],beamClearVolume[layer],
         beamClearVolume[layer]->GetName(),layerVolume[layer],
	 false,0,checkOverlaps);
     }
     else{
       G4cout << beamTubeName[layer] << " omitted" << G4endl;
     }
   }
   sprintf(lineOutput,"Generator position in each layer \n");
   G4cout << lineOutput;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(lineOutput,formPosOut,layerVolume[layer]->GetName().c_str(),
       generPos[layer].x(),generPos[layer].y(),generPos[layer].z());
     G4cout << lineOutput;
   }
   sprintf(lineOutput,"Source position in each layer \n");
   G4cout << lineOutput;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     sprintf(lineOutput,formPosOut,layerVolume[layer]->GetName().c_str(),
       sourcePos[layer].x(),sourcePos[layer].y(),sourcePos[layer].z());
     G4cout << lineOutput;
   }
//
   ConstructNotch();
//
//   Now construct the table legs and position them
//   directly under the corners of the generator.
//
   if(fUseTableLeg && ConstructTableLeg()){
     for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
       sprintf(name,"TableLeg_%i",layer);
       G4LogicalVolume * legVolume =
         G4LogicalVolumeStore::GetInstance()->GetVolume(name);
       if(legVolume){
         G4ThreeVector legDim =
	   G4ThreeVector(legVolume->GetSolid()->GetExtent().GetXmax(),
	                 legVolume->GetSolid()->GetExtent().GetYmax(),
	                 legVolume->GetSolid()->GetExtent().GetZmax());
         for(int xSide = 0; xSide < 2; xSide++){
           double deltaX = -(2 * xSide - 1) * (generVolDim.x() - legDim.x());
           for(int zSide = 0; zSide < 2; zSide++){
             double deltaZ = -(2 * zSide - 1) * (generVolDim.z() - legDim.z());
             G4ThreeVector legPos = generPos[layer];
             legPos.setX(generPos[layer].x() + deltaX);
             legPos.setZ(generPos[layer].z() + deltaZ);
             if(layer == 0){
               legPos.setY(generPos[layer].y() - generVolDim.y() - legDim.y());
	     }
	     else{
               legPos.setY(legDim.y() - layerVolDim[layer].y());
	     }
             G4cout << "Leg position for " << zSide << ", " << xSide
	            << ": " << legPos << G4endl;
             sprintf(name,"%s_%ix_%iz",
	       legVolume->GetName().c_str(),xSide,zSide);
             new G4PVPlacement(0,legPos,legVolume,
               name,layerVolume[layer],false,0,checkOverlaps);
           }
         }
       }
     }
   }
//
//   Segment the north and west sides with gaps in Y if indicated.
//
   G4ThreeVector nsLayerGapDim[N_SHIELD_LAYERS][2];
   G4ThreeVector ewLayerGapDim[N_SHIELD_LAYERS][2];
   G4Box * nsLayerGapBox[N_SHIELD_LAYERS][2];
   G4Box * ewLayerGapBox[N_SHIELD_LAYERS][2];
   G4LogicalVolume * nsLayerGapVol[N_SHIELD_LAYERS][2];
   G4LogicalVolume * ewLayerGapVol[N_SHIELD_LAYERS][2];
   G4cout << G4endl;
   G4cout << "Generator dimensions: " << generVolDim << G4endl;
   G4cout << "  Generator position: " << generPos[0] << G4endl;
   for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
     for(int side = 0; side < 2; side++){
       nsLayerGapDim[layer][side].setX(layerVolDim[layer].x());
       nsLayerGapDim[layer][side].setY(0.5 * fPolyGap);
       ewLayerGapDim[layer][side].setY(0.5 * fPolyGap);
     }
     if(layer == 0){
       nsLayerGapDim[layer][0].setZ(0.5 * (layerVolDim[layer].z() -
         generVolDim.z() + generPos[layer].z()));
       nsLayerGapDim[layer][1].setZ(0.5 * (layerVolDim[layer].z() -
         generVolDim.z() - generPos[layer].z()));
       ewLayerGapDim[layer][0].setX(0.5 * (layerVolDim[layer].x() -
         generVolDim.x() + generPos[layer].x()));
       ewLayerGapDim[layer][1].setX(0.5 * (layerVolDim[layer].x() -
         generVolDim.x() - generPos[layer].x()));
       ewLayerGapDim[layer][0].setZ(generVolDim.z());
       ewLayerGapDim[layer][1].setZ(generVolDim.z());
     }
     else{
       nsLayerGapDim[layer][0].setZ(0.5 * (layerVolDim[layer].z() -
         layerVolDim[layer - 1].z() + layerPos[layer].z()));
       nsLayerGapDim[layer][1].setZ(0.5 * (layerVolDim[layer].z() -
         layerVolDim[layer - 1].z() - layerPos[layer].z()));
       ewLayerGapDim[layer][0].setX(0.5 * (layerVolDim[layer].x() -
         layerVolDim[layer - 1].x() + layerPos[layer].x()));
       ewLayerGapDim[layer][1].setX(0.5 * (layerVolDim[layer].x() -
         layerVolDim[layer - 1].x() - layerPos[layer].x()));
       ewLayerGapDim[layer][0].setZ(layerVolDim[layer - 1].z());
       ewLayerGapDim[layer][1].setZ(layerVolDim[layer - 1].z());
     }
     ewLayerGapDim[layer][1].setZ(ewLayerGapDim[layer][0].z());
     G4cout << layerVolume[layer]->GetName() << " dimensions, "
            << layerVolDim[layer] << G4endl;
     G4cout << layerVolume[layer]->GetName() << " gaps, "
            << fLayerGaps[layer] << G4endl;
     G4cout << layerVolume[layer]->GetName() << " position, "
            << layerPos[layer] << G4endl;
     G4cout << "  South side gap for layer " << layer << ", "
            << nsLayerGapDim[layer][0] << G4endl;
     G4cout << "  North side gap for layer " << layer << ", "
            << nsLayerGapDim[layer][1] << G4endl;
     G4cout << "   East side gap for layer " << layer << ", "
            << ewLayerGapDim[layer][0] << G4endl;
     G4cout << "   West side gap for layer " << layer << ", "
            << ewLayerGapDim[layer][1] << G4endl;
     if((fPolyGap > 1e-3) && (fLayerGaps[layer] > 0)){
       double deltaY = 2.0 * layerVolDim[layer].y()/(fLayerGaps[layer] + 1);
       for(int side = 0; side < 2; side++){
         sprintf(name,"NSGapLayer_%i_%i",layer,side);
         nsLayerGapBox[layer][side] = new G4Box(name,
           nsLayerGapDim[layer][side].x(),
           nsLayerGapDim[layer][side].y(),nsLayerGapDim[layer][side].z());
         sprintf(name,"EWGapLayer_%i_%i",layer,side);
         ewLayerGapBox[layer][side] = new G4Box(name,ewLayerGapDim[layer][side].x(),
           ewLayerGapDim[layer][side].y(),ewLayerGapDim[layer][side].z());
//
         nsLayerGapVol[layer][side] =
           new G4LogicalVolume(nsLayerGapBox[layer][side],
           fEnvironmentMaterial,nsLayerGapBox[layer][side]->GetName());
         ewLayerGapVol[layer][side] =
           new G4LogicalVolume(ewLayerGapBox[layer][side],
           fEnvironmentMaterial,ewLayerGapBox[layer][side]->GetName());
         const double beamAvoid = 5 * cm;
         for(int gap = 0; gap < fLayerGaps[layer]; gap++){
           sprintf(name,"%s_%i",
	     nsLayerGapVol[layer][side]->GetName().c_str(),gap);
           G4ThreeVector gapPos(0.0,0.0,0.0);
	   gapPos.setY((gap + 1) * deltaY - layerVolDim[layer].y());
           if(side == 0){
	     gapPos.setZ(nsLayerGapDim[layer][side].z() - layerVolDim[layer].z());
	   }
	   else{
	     gapPos.setZ(-nsLayerGapDim[layer][side].z() + layerVolDim[layer].z());
	   }
           G4cout << "    gap: " << name  << ", " << gapPos<< G4endl;
           if((side != 0) ||
	      (fabs(gapPos.y() - beamClearPos[layer].y()) > beamAvoid)){
             new G4PVPlacement(0,gapPos,nsLayerGapVol[layer][side],name,
               layerVolume[layer],false,0,checkOverlaps);
           }
           sprintf(name,"%s_%i",
	     ewLayerGapVol[layer][side]->GetName().c_str(),gap);
           if(side == 0){
	     gapPos.setX(ewLayerGapDim[layer][side].x() - layerVolDim[layer].x());
	   }
	   else{
	     gapPos.setX(-ewLayerGapDim[layer][side].x() + layerVolDim[layer].x());
	   }
	   gapPos.setZ(layerPos[layer].z());
           G4cout << "    gap: " << name  << ", " << gapPos<< G4endl;
           new G4PVPlacement(0,gapPos,ewLayerGapVol[layer][side],name,
             layerVolume[layer],false,0,checkOverlaps);
         }
       }
     }
   }
//
//   Create the steel baseplate the shield sits on.
//   This plate will run under the posts and lead wall (not accurate there).
//
   const double postSpacing = 50 * 2.54*cm;
   G4ThreeVector basePlateDim =
     G4ThreeVector(basePlateVolume->GetSolid()->GetExtent().GetXmax(),
                   basePlateVolume->GetSolid()->GetExtent().GetYmax(),
                   basePlateVolume->GetSolid()->GetExtent().GetZmax());
   G4ThreeVector stepPlateDim =
     G4ThreeVector(stepPlateVolume->GetSolid()->GetExtent().GetXmax(),
                   stepPlateVolume->GetSolid()->GetExtent().GetYmax(),
                   stepPlateVolume->GetSolid()->GetExtent().GetZmax());
//
//  Now define the overall shield volume.  This gets returned.
//  There is a 50 inch opening between the red posts
//
   const char * DD_SHIELD_NAME = "DDShield";
   double shieldWidth = 0.5 * postSpacing + 2.0 * postVolDim.x();
   double shieldDepth = basePlateDim.z() + postVolDim.z() + wallPlateDim.z();
   double shieldHeight = postVolDim.y();


   G4ThreeVector shieldVolumeDim =
     G4ThreeVector(shieldWidth,shieldHeight,shieldDepth);
   G4Box * shield = new G4Box(DD_SHIELD_NAME,shieldVolumeDim.x(),
                              shieldVolumeDim.y(),shieldVolumeDim.z());
   G4LogicalVolume* shieldVolume =
     new G4LogicalVolume(shield,fEnvironmentMaterial,shield->GetName());
   G4VisAttributes *att_invis = new G4VisAttributes(false);
   shieldVolume->SetVisAttributes(att_invis);
   sprintf(lineOutput,formDimOut,shieldVolume->GetName().c_str(),
       shieldVolumeDim.x(),shieldVolumeDim.y(),shieldVolumeDim.z());
   G4cout << lineOutput;
//
//  Place the red posts.
//
   G4ThreeVector postLoc = postVolDim - shieldVolumeDim;
   postLoc.setZ(postLoc.z() + 2.0 * wallPlateDim.z());
   for(int post = 0; post < 2; post++){
     sprintf(name,"Post_%i",post);
     sprintf(lineOutput,formPosOut,name,
       postLoc.x(),postLoc.y(),postLoc.z());
     G4cout << lineOutput;
     new G4PVPlacement(0,postLoc,postVol,name,
       shieldVolume,false,post,checkOverlaps);
     postLoc.setX(-1.0 * postLoc.x());
   }
//
//  Place the red base plate.
//
   G4ThreeVector basePlatePos(0.0,0.0,0.0);
   const double basePlateHeight = 65.4*cm;
   basePlatePos.setY(basePlateHeight - shieldVolumeDim.y() -
                     basePlateDim.y());
   basePlatePos.setZ(shieldVolumeDim.z() - basePlateDim.z());
   sprintf(lineOutput,formPosOut,basePlateVolume->GetName().c_str(),
       basePlatePos.x(),basePlatePos.y(),basePlatePos.z());
   G4cout << lineOutput;
   new G4PVPlacement(0,basePlatePos,basePlateVolume,basePlateVolume->GetName(),
     shieldVolume,false,0,checkOverlaps);
//
//  Place the red step plate, the plate under the lead wall.
//  Elevation below base plate is a measurement.
//
   G4ThreeVector stepPlatePos(0.0,0.0,0.0);
   const double stepPlateHeight = basePlateHeight - 18.5*cm;
   stepPlatePos.setY(stepPlateHeight - shieldVolumeDim.y() -
                     stepPlateDim.y());
   stepPlatePos.setZ(stepPlateDim.z() - shieldVolumeDim.z() +
                     2.0 * wallPlateDim.z());
   sprintf(lineOutput,formPosOut,stepPlateVolume->GetName().c_str(),
       stepPlatePos.x(),stepPlatePos.y(),stepPlatePos.z());
   G4cout << lineOutput;
   new G4PVPlacement(0,stepPlatePos,stepPlateVolume,stepPlateVolume->GetName(),
     shieldVolume,false,0,checkOverlaps);
//
//  Place the steel plate south of the lead wall.
//  Its bottom edge is about 3 inches below the red step plate.
//
   G4ThreeVector wallPlatePos(0.0,0.0,
                              wallPlateDim.z() - shieldVolumeDim.z());
   wallPlatePos.setY(stepPlatePos.y() + wallPlateDim.y() - 3 * 2.54 * cm);
   sprintf(lineOutput,formPosOut,wallPlate->GetName().c_str(),
       wallPlatePos.x(),wallPlatePos.y(),wallPlatePos.z());
   G4cout << lineOutput;
     new G4PVPlacement(0,wallPlatePos,wallPlate,wallPlate->GetName(),
       shieldVolume,false,0,checkOverlaps);
//
//   Place the outermost layer into the overall shield volume:
//   Center (E-W) the beamtube on the shield volume.
//   Push the shield to the downstream edge of the baseplate
//
   G4ThreeVector shieldPos(0.0,0.0,0.0);
   shieldPos.setX(-beamClearPos[2].x());
   shieldPos.setY(layerVolDim[N_SHIELD_LAYERS - 1].y() + basePlatePos.y() +
                  basePlateDim.y());
   shieldPos.setZ(shieldVolumeDim.z() - layerVolDim[N_SHIELD_LAYERS - 1].z());
   sprintf(lineOutput,formPosOut,
     layerName[N_SHIELD_LAYERS - 1],shieldPos.x(),shieldPos.y(),shieldPos.z());
   G4cout << lineOutput;

   G4ThreeVector shieldClearPos =
     shieldVolumeDim - layerVolDim[N_SHIELD_LAYERS - 1] - shieldPos;
   G4ThreeVector shieldClearNeg =
     shieldVolumeDim - layerVolDim[N_SHIELD_LAYERS - 1] + shieldPos;
   sprintf(lineOutput," Positive clearance: %6.2f,  %6.2f,  %6.2f \n",
       shieldClearPos.x(),shieldClearPos.y(),shieldClearPos.z());
   G4cout << lineOutput;
   sprintf(lineOutput," Negative clearance: %6.2f,  %6.2f,  %6.2f \n",
       shieldClearNeg.x(),shieldClearNeg.y(),shieldClearNeg.z());
   G4cout << lineOutput;
//
   new G4PVPlacement(0,shieldPos,layerVolume[N_SHIELD_LAYERS - 1],
     layerVolume[N_SHIELD_LAYERS - 1]->GetName(),
     shieldVolume,false,0,checkOverlaps);
//
//  Get the generator position in the shield frame, and in the wall frame:
//
   G4ThreeVector generPosShield = generPos[N_SHIELD_LAYERS - 1] + shieldPos;
   G4ThreeVector sourcePosShield = sourcePos[N_SHIELD_LAYERS - 1] + shieldPos;
//
//    The alternative wall, so a cannon could pass through:
//
   G4ThreeVector sWallPos(0.0,0.0,0.0);
   sWallPos.setY(stepPlatePos.y() + stepPlateDim.y());
   sWallPos.setZ(2 * brickDim.x() + fLeadHorizGap
                 - shieldVolumeDim.z() + 2.0 * wallPlateDim.z());
   ConstructSWallSections(sourcePosShield,sWallPos);
   PositionSWallSections(shieldVolume,sWallPos);
//
   if(fUseCannon){
     G4ThreeVector barrelDim(3.0 * 2.54 * cm,1.0 * 2.54 * cm, 25.0 * cm);
     barrelDim.setZ((shieldVolumeDim.z() - 2.0 * wallPlateDim.z() -
                     layerVolDim[N_SHIELD_LAYERS - 1].z()));
     G4Box * barrelBox = new G4Box("Barrel",
       barrelDim.x(),barrelDim.y(),barrelDim.z());
     G4LogicalVolume * barrelVol = new G4LogicalVolume(barrelBox,
       fCannonMaterial,barrelBox->GetName());
     barrelVol->SetVisAttributes(att_layer[0]);
     G4cout << "    Material for " << barrelVol->GetName()
            << ": " << barrelVol->GetMaterial()->GetName() << G4endl;
     sprintf(lineOutput,formDimOut,barrelVol->GetName().c_str(),
       barrelDim.x(),barrelDim.y(),barrelDim.z());
     G4cout << lineOutput;
     if(fCollRadius > 1e-3 * mm){
       G4Tubs * boreTube =
         new G4Tubs("Bore",0.0,fCollRadius,barrelDim.z(),0.0,CLHEP::twopi);
       G4LogicalVolume * boreVol = new G4LogicalVolume(boreTube,
         fEnvironmentMaterial,boreTube->GetName());
       boreVol->SetVisAttributes(att_white);
//
       G4ThreeVector borePos(0.0,0.0,0.0);
       //new G4PVPlacement(0,borePos,boreVol,boreVol->GetName(),
       //  barrelVol,false,0,checkOverlaps);
     }
//
//     G4ThreeVector barrelPos = generPosShield;
     G4ThreeVector barrelPos = sourcePosShield;
     barrelPos.setZ(barrelDim.z() - shieldVolumeDim.z() +
                    2.0 * wallPlateDim.z());
     sprintf(lineOutput,formPosOut,barrelVol->GetName().c_str(),
       barrelPos.x(),barrelPos.y(),barrelPos.z());
     G4cout << lineOutput;
     //new G4PVPlacement(0,barrelPos,barrelVol,barrelVol->GetName(),
     //     shieldVolume,false,0,checkOverlaps);


     // Define cylinder dimensions
     G4double innerRadius = 0.0 * cm;
     G4double outerRadius = 7.6/2.0 * cm;
     G4double halfHeight = 7.6/2.0 * cm;
     G4double startAngle = 0.0 * deg;
     G4double spanningAngle = 360.0 * deg;

     // Create a rotation matrix to rotate by 90 degrees around the y-axis
     G4RotationMatrix* rotation = new G4RotationMatrix();
     rotation->rotateX(90 * deg);  // 90 degrees in radians

     G4Color red(1.0,0.0,0.0);
     G4VisAttributes *att_red = new G4VisAttributes(red);


     // Create the cylinder geometry (as G4Tubs or G4Box, depending on your design)
     G4Tubs* cylinderSolid = new G4Tubs("Cylinder", innerRadius, outerRadius, halfHeight, startAngle, spanningAngle);

     // Create a new position for the cylinder (same x, y as barrel, custom z)
     G4double customZ = 5.0*cm;
     G4ThreeVector cylinderPos1(barrelPos.x(),barrelPos.y(),barrelPos.z()+customZ);
     // Create the logical volume for the cylinder
     G4LogicalVolume* cylinderLog1 = new G4LogicalVolume(cylinderSolid, fCannonMaterial, "Cylinder1");

     // Place the cylinder at the new position (same x, y as barrel, custom z)
     new G4PVPlacement(rotation,                   // No rotation
                     cylinderPos1,          // Cylinder's position
                     cylinderLog1,          // Logical volume
                     "LiquidScintillator_1",           // Name
                     shieldVolume,         // Parent volume (same as barrel)
                     false,                // No boolean operation
                     0,                    // Copy number
                     checkOverlaps);       // Overlap check

      cylinderLog1->SetVisAttributes(att_red);

   }



//
   if(fUseFloorBlock){
     G4LogicalVolume* floorBlockEnv  = ConstructFloorBlock();
     G4ThreeVector floorBlockPos = sourcePosShield;
     floorBlockPos.setY(shieldVolume->GetSolid()->GetExtent().GetYmin() -
                        floorBlockEnv->GetSolid()->GetExtent().GetYmin() +
			fFloorBlockHeight);
     floorBlockPos.setZ(shieldVolume->GetSolid()->GetExtent().GetZmax() -
                        floorBlockEnv->GetSolid()->GetExtent().GetZmax());
     new G4PVPlacement(0,floorBlockPos,floorBlockEnv,floorBlockEnv->GetName(),
       shieldVolume,false,0,checkOverlaps);
   }

   return shieldVolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::CustomMaterials(){
//
//  Define the custom materials we need:
//
   G4NistManager* nist = G4NistManager::Instance();
   G4Material* poly  = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
//
//  Borated polyethylene from the ePlastics web site
//  It lists 5% borated material having a 1.04 density.
//
   const char * lumberName = "POLY_LUMBER";
   const double polyLumberDensity = 0.84*g/cm3;
   if(!GetMaterial(lumberName)){
     G4Material * polyLumber = new G4Material(lumberName,polyLumberDensity,1);
     polyLumber->AddMaterial(poly,1.0);
     G4cout << polyLumber;
   }


   const char * borPolyName = "Borated_Poly";
   const double polyDensity = 0.94*g/cm3;
   const double fBoronFraction = 0.05;
   if(!GetMaterial(borPolyName)){
     double boratedPolyDensity = polyDensity + 2.0 * fBoronFraction*g/cm3;
     G4Material* polyB = new G4Material(borPolyName,boratedPolyDensity,2);
     G4Material* el_B  = nist->FindOrBuildMaterial("G4_B");
     polyB->AddMaterial(el_B,fBoronFraction);
     polyB->AddMaterial(poly,1.0 - fBoronFraction);
     G4cout << polyB;
   }

   // Define EJ_301 material
   const char* EJ_301Name = "EJ_301_Material";
   const double EJ_301Density = 0.874 * g/cm3;  // Replace with actual density if known

   if (!GetMaterial(EJ_301Name)) {
     // Create a new material with 2 elements (C and H)
     G4Material* EJ_301 = new G4Material(EJ_301Name, EJ_301Density, 2);

     // Get carbon and hydrogen from NIST database
     G4Element* el_C = G4NistManager::Instance()->FindOrBuildElement("C");  // Carbon
     G4Element* el_H = G4NistManager::Instance()->FindOrBuildElement("H");  // Hydrogen

     // Add the number of atoms for each element in the material
     EJ_301->AddElement(el_C, 398);  // 398 carbon atoms
     EJ_301->AddElement(el_H, 482);  // 482 hydrogen atoms

     // Output the material properties to the console
     G4cout << EJ_301;
   }
//
//  Make cryogenic materials for targets
//
   const int numCryoMat = 3;
   const char * cryoNames[numCryoMat] = {"G4_Ge","G4_Si","G4_Sn"};
   for(int mat = 0; mat < numCryoMat; mat++){
     strcpy(name,cryoNames[mat]);
     strcat(name,"_cryo");
     G4Material* baseMaterial = GetMaterial(cryoNames[mat]);
     G4Material* cryoMaterial = 0;
     if(!GetMaterial(name)){
       if(baseMaterial){
         cryoMaterial =
           new G4Material(name,baseMaterial->GetDensity(),
                          baseMaterial,kStateUndefined,fTargetTemperature);
         G4cout << "   New cryogenic material: " << G4endl;
       }
       else{
         G4cout << cryoNames[mat] << " was not found. " << G4endl;
       }
     }
     else{
       G4cout << name << " already exists. " << G4endl;
       cryoMaterial = GetMaterial(name);
     }
     if(cryoMaterial) G4cout << cryoMaterial << G4endl;
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructDDShield(){
//
//  Return the pointer to the shield around the D-D generator
//  This version is built off of the engineering drawings.
//
   printf("\n******************************************************** \n \n");
   printf("                 D-D generator shield construction \n\n");
//
   G4cout << G4endl << "In ConstructDDShield..." << G4endl;
   G4bool checkOverlaps = true;
//
   G4Color green(0.0,1.0,0.0);
   G4VisAttributes *att_green = new G4VisAttributes(green);
   G4VisAttributes *att_invis = new G4VisAttributes(false);
//
   const G4ThreeVector origin(0.0,0.0,0.0);
//
//  Build the lead walls and posts
//
   const double postSpacing = 50 * 2.54*cm;
   G4LogicalVolume * postVol = ConstructPosts();
   G4ThreeVector postVolDim =
     G4ThreeVector(postVol->GetSolid()->GetExtent().GetXmax(),
                   postVol->GetSolid()->GetExtent().GetYmax(),
                   postVol->GetSolid()->GetExtent().GetZmax());
//
//   Create the steel baseplate the shield sits on.
//   This plate will run under the posts and lead wall (not accurate there).
//
   G4LogicalVolume* basePlateVolume = ConstructBasePlate();
   G4ThreeVector basePlateDim =
     G4ThreeVector(basePlateVolume->GetSolid()->GetExtent().GetXmax(),
                   basePlateVolume->GetSolid()->GetExtent().GetYmax(),
                   basePlateVolume->GetSolid()->GetExtent().GetZmax());
//
//  Now define the overall shield volume.  This gets returned.
//  There is a 50 inch opening between the red posts
//
   const char * DD_SHIELD_NAME = "DDShield";
   double shieldWidth = 0.5 * postSpacing + 2.0 * postVolDim.x();
//   double shieldDepth = sBrickWallDim.z() +
//                        layerVolDim[N_SHIELD_LAYERS - 1].z();
   double shieldDepth = basePlateDim.z();
   double shieldHeight = postVolDim.y() + basePlateDim.y();

   G4ThreeVector shieldVolumeDim =
     G4ThreeVector(shieldWidth,shieldHeight,shieldDepth);
   G4Box * shield = new G4Box(DD_SHIELD_NAME,shieldVolumeDim.x(),
                              shieldVolumeDim.y(),shieldVolumeDim.z());
   G4LogicalVolume* shieldVolume =
     new G4LogicalVolume(shield,fEnvironmentMaterial,shield->GetName());
   shieldVolume->SetVisAttributes(att_green);
   sprintf(lineOutput,formDimOut,shieldVolume->GetName().c_str(),
       shieldVolumeDim.x(),shieldVolumeDim.y(),shieldVolumeDim.z());
   G4cout << lineOutput;
//
//  Place the red posts
//
   G4ThreeVector postLoc(postVolDim.x() - shieldVolumeDim.x(),
                     0.0,postVolDim.z() - shieldVolumeDim.z());
   postLoc.setY(postLoc.y() + basePlateDim.y());
   for(int post = 0; post < 2; post++){
     sprintf(name,"        Post_%i",post);
     sprintf(lineOutput,formPosOut,name,
        postLoc.x(),postLoc.y(),postLoc.z());
     G4cout << lineOutput;
     new G4PVPlacement(0,postLoc,postVol,name,
       shieldVolume,false,post,checkOverlaps);
     postLoc.setX(-1.0 * postLoc.x());
   }
//
//  Place the red base plate.
//
   G4ThreeVector basePlatePos = origin;
   basePlatePos.setY(-shieldVolumeDim.y() + basePlateDim.y());
   sprintf(lineOutput,formPosOut,basePlateVolume->GetName().c_str(),
      basePlatePos.x(),basePlatePos.y(),basePlatePos.z());
   G4cout << lineOutput;
   new G4PVPlacement(0,basePlatePos,basePlateVolume,basePlateVolume->GetName(),
     shieldVolume,false,0,checkOverlaps);
//
//  The frame from drawings F1015849:
//
   const double uniLength_7  = 62.25 * 2.54 * cm;
   const double uniLength_8  = 59.0  * 2.54 * cm;
   const double uniLength_9  = 31.0  * 2.54 * cm;
   const double uniLength_10 = 59.5  * 2.54 * cm;
   G4LogicalVolume* unistrutVol_7  = ConstructUnistrut(uniLength_7);
   G4LogicalVolume* unistrutVol_8  = ConstructUnistrut(uniLength_8);
   G4LogicalVolume* unistrutVol_9  = ConstructUnistrut(uniLength_9);
   G4LogicalVolume* unistrutVol_10 = ConstructUnistrut(uniLength_10);
   G4ThreeVector unistrutVolDim(unistrutVol_7->GetSolid()->GetExtent().GetXmax(),
                                unistrutVol_7->GetSolid()->GetExtent().GetYmax(),
                                unistrutVol_7->GetSolid()->GetExtent().GetZmax());
//
//  Define a ghost volume that holds the frame
//
   G4ThreeVector frameDim = origin;
   frameDim.setX(2 * unistrutVolDim.x() + 0.5 * uniLength_9);
   frameDim.setY(0.5 * uniLength_7);
   frameDim.setZ(unistrutVolDim.x() + 0.5 * uniLength_10);
   G4Box * frameBox = new G4Box("Shield Frame",frameDim.x(),
                              frameDim.y(),frameDim.z());
   G4LogicalVolume* frameVolume =
     new G4LogicalVolume(frameBox,fEnvironmentMaterial,frameBox->GetName());
   frameVolume->SetVisAttributes(att_invis);
   sprintf(lineOutput,formDimOut,frameVolume->GetName().c_str(),
       frameDim.x(),frameDim.y(),frameDim.z());
   G4cout << lineOutput;
//
// Place part 10:
//
   G4ThreeVector unistrutPos = origin;
   double xOffset = unistrutVolDim.x() - frameDim.x();
   double yOffset = unistrutVolDim.y() - frameDim.y();
   double zOffset = 0.0;
   unistrutPos.setZ(zOffset);
   for(int layer = 0; layer < 2; layer++){
     unistrutPos.setY(yOffset);
     for(int row = 0; row < 2; row++){
       sprintf(name,"FrameUni_10_%i",row + 2 * layer);
       unistrutPos.setX(xOffset);
       xOffset *= -1.0;
       sprintf(lineOutput,formPosOut,name,
         unistrutPos.x(),unistrutPos.y(),unistrutPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(0,unistrutPos,unistrutVol_10,name,
         frameVolume,false,0,checkOverlaps);
     }
     yOffset *= -1.0;
   }
//
// Place part 9:
//
   xOffset = 0.0;
   yOffset = unistrutVolDim.y() - frameDim.y();
   zOffset = unistrutVolDim.y() - frameDim.z();
   unistrutPos.setX(xOffset);
   G4RotationMatrix * yRot = new G4RotationMatrix;
   yRot->rotateY(CLHEP::halfpi*rad);
   sprintf(lineOutput,formDimOut,unistrutVol_9->GetName().c_str(),
     unistrutVol_9->GetSolid()->GetExtent().GetXmax(),
     unistrutVol_9->GetSolid()->GetExtent().GetYmax(),
     unistrutVol_9->GetSolid()->GetExtent().GetZmax());
   G4cout << lineOutput;
   for(int layer = 0; layer < 2; layer++){
     unistrutPos.setY(yOffset);
     for(int row = 0; row < 2; row++){
       sprintf(name,"FrameUni_9_%i",row + 2 * layer);
       unistrutPos.setZ(zOffset);
       zOffset *= -1.0;
       sprintf(lineOutput,formPosOut,name,
         unistrutPos.x(),unistrutPos.y(),unistrutPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(yRot,unistrutPos,unistrutVol_9,name,
         frameVolume,false,0,checkOverlaps);
     }
     yOffset *= -1.0;
   }
//
// Place part 8:
//
   xOffset = 0.0;
   yOffset = 0.0;
   zOffset = unistrutVolDim.y() - frameDim.z();
   unistrutPos.setY(yOffset);
   G4RotationMatrix * xRot = new G4RotationMatrix;
   xRot->rotateX(CLHEP::halfpi*rad);
   G4RotationMatrix * xzRot = new G4RotationMatrix;
   xzRot->rotateX(CLHEP::halfpi*rad);
   xzRot->rotateZ(CLHEP::halfpi*rad);
   sprintf(lineOutput,formDimOut,unistrutVol_8->GetName().c_str(),
     unistrutVol_8->GetSolid()->GetExtent().GetXmax(),
     unistrutVol_8->GetSolid()->GetExtent().GetYmax(),
     unistrutVol_8->GetSolid()->GetExtent().GetZmax());
   G4cout << lineOutput;
   for(int row = 0; row < 2; row++){
     unistrutPos.setZ(zOffset);
     for(int column = 0; column < 3; column++){
       sprintf(name,"FrameUni_8_%i_%i",row,column);
       xOffset = 0.25 * uniLength_9 * (column - 1);
       unistrutPos.setX(xOffset);
       sprintf(lineOutput,formPosOut,name,
         unistrutPos.x(),unistrutPos.y(),unistrutPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xzRot,unistrutPos,unistrutVol_8,name,
         frameVolume,false,0,checkOverlaps);
     }
     zOffset *= -1.0;
   }
   for(int row = 0; row < 1; row++){
     xOffset = unistrutVolDim.y() - frameDim.x();
     unistrutPos.setX(xOffset);
     for(int column = 0; column < 4; column++){
       sprintf(name,"FrameUni_8_%i_%i",row + 2,column);
       zOffset = 0.2 * uniLength_9 * (column - 1.5);
       unistrutPos.setZ(zOffset);
       sprintf(lineOutput,formPosOut,name,
         unistrutPos.x(),unistrutPos.y(),unistrutPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xRot,unistrutPos,unistrutVol_8,name,
         frameVolume,false,0,checkOverlaps);
     }
     xOffset *= -1.0;
   }
//
// Place part 7:
//
   xOffset = unistrutVolDim.x() - frameDim.x();
   yOffset = 0.0;
   zOffset = unistrutVolDim.y() - frameDim.z();
   for(int row = 0; row < 2; row++){
     unistrutPos.setX(xOffset);
     for(int column = 0; column < 2; column++){
       sprintf(name,"FrameUni_7_%i_%i",row,column);
       unistrutPos.setZ(zOffset);
       zOffset *= -1.0;
       sprintf(lineOutput,formPosOut,name,
         unistrutPos.x(),unistrutPos.y(),unistrutPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xRot,unistrutPos,unistrutVol_8,name,
         frameVolume,false,0,checkOverlaps);
     }
     xOffset *= -1.0;
   }
//
   G4ThreeVector framePos = origin;
   framePos.setX(0.0);
   framePos.setY(basePlatePos.y() + basePlateDim.y() + frameDim.y());
   framePos.setZ(basePlatePos.z() + basePlateDim.z() - frameDim.z());
   sprintf(lineOutput,formPosOut,frameVolume->GetName().c_str(),
       framePos.x(),framePos.y(),framePos.z());
   G4cout << lineOutput;
   new G4PVPlacement(0,framePos,frameVolume,frameVolume->GetName(),
     shieldVolume,false,0,checkOverlaps);
//
   return shieldVolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBeamDump(){
//
//
   G4cout << G4endl << "In ConstructBeamDump..." << G4endl;
//
    const char * dumpName = "BeamDump";
   G4cout << " Material: " << fDumpMaterial->GetName() << G4endl;
//
   const G4Color lightGray(0.75,0.75,0.75);
//
   G4ThreeVector dumpDim(0.5 * fDumpRadius,0.5 * fDumpRadius,0.5 * fDumpDepth);
   G4Box * beamDumpShape = new G4Box("BeamDumpBox",dumpDim.x(),
     dumpDim.y(),dumpDim.z());
//   G4Tubs * beamDumpShape = new G4Tubs("BeamDumpTube",0.0,fDumpRadius,
//     0.5 * fDumpDepth,0.0,CLHEP::twopi);
   beamDumpShape->DumpInfo();
   G4LogicalVolume * beamDumpVol =
        new G4LogicalVolume(beamDumpShape,fDumpMaterial,dumpName);
   G4VisAttributes * att_dump = new G4VisAttributes(lightGray);
   beamDumpVol->SetVisAttributes(att_dump);

   return beamDumpVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructFloorBlock(){
//
//   Put a block of standard polyethylene lumber on the floor
//
   G4cout << G4endl << "In ConstructFloorBlock..." << G4endl;
//
   const char * blockName = "FloorBlock";
   const G4ThreeVector lumberDim(9.0 * 2.54 * cm, 5.25 * 2.54 * cm, 100.0 * cm);
   G4cout << " Block Material: " << fDumpMaterial->GetName() << G4endl;
   const G4Color lightGray(0.75,0.75,0.75);
   G4VisAttributes *att_block = new G4VisAttributes(lightGray);
//
   G4ThreeVector blockDim = 0.5 * lumberDim;
   G4Box * floorBlockShape = new G4Box(blockName,
     blockDim.x(),blockDim.y(),blockDim.z());
   floorBlockShape->DumpInfo();
   G4LogicalVolume * floorBlockVol =
        new G4LogicalVolume(floorBlockShape,fDumpMaterial,blockName);
   floorBlockVol->SetVisAttributes(att_block);

   return floorBlockVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructF10161306(){
//
//   Put a block of standard polyethylene lumber on the floor
//
   G4cout << G4endl << "In ConstructF10161306..." << G4endl;
//
   const char * blockName = "F10161306";
   const G4ThreeVector lumberDim(7.0 * 2.54 * cm, 2.375 * 2.54 * cm,
                                 16.0 * 2.54 * cm);
   G4cout << "F10161306  Material: " << fLayerMaterial[0]->GetName() << G4endl;
   const G4Color green(0.0,0.95,0.0);
   G4VisAttributes *att_block = new G4VisAttributes(green);
//
   G4ThreeVector blockDim = 0.5 * lumberDim;
   G4Box * floorBlockShape = new G4Box(blockName,
     blockDim.x(),blockDim.y(),blockDim.z());
   floorBlockShape->DumpInfo();
   G4LogicalVolume * floorBlockVol =
        new G4LogicalVolume(floorBlockShape,fLayerMaterial[0],blockName);
   floorBlockVol->SetVisAttributes(att_block);

   return floorBlockVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Material*  IronFilterDetectorConstruction::GetMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();
//
  G4Material* thisMaterial =
              nistManager->FindOrBuildMaterial(materialName);
  if(!thisMaterial){
    G4cout << G4endl
           << "-->  WARNING from GetMaterial : "
           << materialName << " not found" << G4endl;
  }
  return thisMaterial;
//
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetWallMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fWallMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fWallMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The walls are made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetDumpMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fDumpMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fDumpMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The beam dump is made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetTargetMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fTargetMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fTargetMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The target is made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetCannonMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fCannonMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fCannonMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The Beam Collimator is made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetBeamPipeMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fBeamPipeMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fBeamPipeMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The Beam pipe through the shield is made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetEnvironmentMaterial(G4String materialName)
{
  G4Material* pttoMaterial = GetMaterial(materialName);
//
  if (fEnvironmentMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fEnvironmentMaterial = pttoMaterial;
        G4cout
          << G4endl
          << "----> The Environment is made of " << materialName << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::SetLayerMaterial(int layer, G4String materialName)
{
  G4cout << "SetLayerMaterial called for layer " << layer
         << ", material " << materialName << G4endl;
  if((layer < 0) || (layer > N_SHIELD_LAYERS - 1)) return;
//
  G4Material* pttoMaterial = GetMaterial(materialName);
  if (fLayerMaterial[layer] != pttoMaterial) {
     if ( pttoMaterial ) {
        fLayerMaterial[layer] = pttoMaterial;
        G4cout
          << G4endl
          << "----> Shield layer " << layer << " is made of "
	  << fLayerMaterial[layer]->GetName() << G4endl;
     }
  }

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructLeadBrick(){
//
//   Make and return a standard lead brick
//
   G4cout << G4endl << "In ConstructLeadBrick..." << G4endl;
   G4bool checkOverlaps = true;
//
   const char * brickName = "LeadBrick";
   const char * fillName  = "LeadBrickFiller";

   const G4Color grayColor(0.5,0.5,0.5);
   const G4VisAttributes *att_gray = new G4VisAttributes(grayColor);
   const G4VisAttributes *att_invis = new G4VisAttributes(false);
//
//   Build a brick by assuming that the lead filler is 2 x 4 x 8 inches
//   The brick is larger by the gap parameter,
//   meant to account for wrapping material.
//   Default gap is 2 x 0.006", the bag thickness.
//
   const G4ThreeVector origin(0.0,0.0,0.0);
   const G4ThreeVector brickPbExtent(5.08*cm,10.16*cm,20.32*cm);
//   Dimensions of the lead volume:
   const G4ThreeVector brickPbDim = 0.5 * brickPbExtent;
//   Dimensions of the brick  volume:
   G4ThreeVector brickVolDim(brickPbDim.x() + 0.5 * fLeadGap,
                             brickPbDim.y() + 0.5 * fLeadGap,
		             brickPbDim.z() + 0.5 * fLeadGap);
   G4cout << "   Brick dimensions: " << brickVolDim << G4endl;
   G4cout << "    Lead dimensions: " << brickPbDim << G4endl;
   G4cout << "     Brick material: " << fWallMaterial->GetName() << G4endl;
//
   G4Box * brickVolBox = new G4Box(brickName,brickVolDim.x(),
     brickVolDim.y(),brickVolDim.z());
   G4Box * brickPbBox = new G4Box(fillName,brickPbDim.x(),
     brickPbDim.y(),brickPbDim.z());
   G4LogicalVolume * brickVol =
     new G4LogicalVolume(brickVolBox,fEnvironmentMaterial,brickName);
   G4LogicalVolume * brickFill =
     new G4LogicalVolume(brickPbBox,fWallMaterial,fillName);
   new G4PVPlacement(0,origin,brickFill,fillName,
       brickVol,false,0,checkOverlaps);
   brickVol->SetVisAttributes(att_invis);
   brickFill->SetVisAttributes(att_gray);
//
   return brickVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::PositionSWallSections(G4LogicalVolume* mother,
                                            G4ThreeVector & basePos){
//
//   Position the south wall from individual sections made in
//   ConstructSWallSections.  The mother volume is passed in as
//   well as the position for the base of the wall.
//
//
     G4cout << G4endl << "In PositionSWallSections..." << G4endl;
     if(!fUseSouthWall){
       G4cout << " The south wall is not being placed" << G4endl << G4endl;
       return;
     }
     G4cout << "    Mother: " << mother->GetName() << G4endl;

     G4bool checkOverlaps = true;
//
     G4LogicalVolume * lowerWall =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CenterLWall");
     G4LogicalVolume * upperWall =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CenterUWall");
     G4LogicalVolume * sideWall =
       G4LogicalVolumeStore::GetInstance()->GetVolume("SideWall");
//
     G4ThreeVector lowerWallPos = basePos;
     G4ThreeVector upperWallPos = basePos;
     const int nSides = 2;
     G4ThreeVector sideWallPos[nSides] = {basePos, basePos};
     G4RotationMatrix * yRot[nSides] = {0,0};
     yRot[1] = new G4RotationMatrix;
     yRot[1]->rotateY(CLHEP::pi*rad);
//
     G4ThreeVector lowerWallDim =
       G4ThreeVector(lowerWall->GetSolid()->GetExtent().GetXmax(),
                     lowerWall->GetSolid()->GetExtent().GetYmax(),
                     lowerWall->GetSolid()->GetExtent().GetZmax());
     G4ThreeVector upperWallDim =
       G4ThreeVector(upperWall->GetSolid()->GetExtent().GetXmax(),
                     upperWall->GetSolid()->GetExtent().GetYmax(),
                     upperWall->GetSolid()->GetExtent().GetZmax());
     G4ThreeVector sideWallDim =
       G4ThreeVector(sideWall->GetSolid()->GetExtent().GetXmax(),
                     sideWall->GetSolid()->GetExtent().GetYmax(),
                     sideWall->GetSolid()->GetExtent().GetZmax());
     sprintf(lineOutput,formDimOut,(lowerWall->GetName()).c_str(),
       lowerWallDim.x(),lowerWallDim.y(),lowerWallDim.z());
     G4cout << lineOutput;
//
     lowerWallPos.setY(basePos.y() + lowerWallDim.y());
     upperWallPos.setY(basePos.y() + 2 * sideWallDim.y() - upperWallDim.y());
     sprintf(lineOutput,formPosOut,(lowerWall->GetName()).c_str(),
       lowerWallPos.x(),lowerWallPos.y(),lowerWallPos.z());
     G4cout << lineOutput;
     sprintf(lineOutput,formPosOut,(upperWall->GetName()).c_str(),
       upperWallPos.x(),upperWallPos.y(),upperWallPos.z());
     G4cout << lineOutput;
     double leftRight = -1.0;
     for(int side = 0; side < nSides ; side++){
       double deltaX = leftRight * (sideWallDim.x() + lowerWallDim.x());
       sideWallPos[side].setX(basePos.x() + deltaX);
       sideWallPos[side].setY(basePos.y() + sideWallDim.y());
       sprintf(lineOutput,formPosOut,(sideWall->GetName()).c_str(),
         sideWallPos[side].x(),sideWallPos[side].y(),sideWallPos[side].z());
       G4cout << lineOutput;
       leftRight *= -1.0;
     }
     new G4PVPlacement(0,lowerWallPos,lowerWall,lowerWall->GetName(),
             mother,false,0,checkOverlaps);
     new G4PVPlacement(0,upperWallPos,upperWall,upperWall->GetName(),
             mother,false,0,checkOverlaps);
     for(int side = 0; side < nSides ; side++){
       sprintf(name,"%s_%i",sideWall->GetName().c_str(),side);
       new G4PVPlacement(yRot[side],sideWallPos[side],sideWall,name,
             mother,false,0,checkOverlaps);
     }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructSWallSections
      (G4ThreeVector & beamPos, G4ThreeVector & basePos){
//
//   Construct south wall.  The generic lead brick must exist first.
//   This is the narrow version, 5.5 bricks wide, centered.
//   This version creates sections that must be positioned independently.
//   This allows a cannon to poke through the beam hole.
//   Revised for the 2022 stacking configuration.
//
//
     G4cout << G4endl << "In ConstructSWallSections..." << G4endl;
     if(!fUseSouthWall){
       G4cout << " The south wall is not being made" << G4endl << G4endl;
       return 0;
     }
     G4cout << "   Beam position in shield frame: " << beamPos << G4endl;
     G4cout << "   Wall position in shield frame: " << basePos << G4endl;
     G4LogicalVolume * brick =
       G4LogicalVolumeStore::GetInstance()->GetVolume("LeadBrick");
     if(!brick){
       G4cout << "  Lead brick for south wall is not yet made" << G4endl;
       return 0;
     }
     else{
       G4cout << "  Found brick " << brick->GetName() << G4endl;
     }
//
//     char name[80];
     G4RotationMatrix * xRot = new G4RotationMatrix;
     xRot->rotateX(CLHEP::halfpi*rad);
     G4RotationMatrix * yRot = new G4RotationMatrix;
     yRot->rotateY(CLHEP::halfpi*rad);
     G4RotationMatrix * xyRot = new G4RotationMatrix;
     xyRot->rotateX(CLHEP::halfpi*rad);
     xyRot->rotateY(CLHEP::halfpi*rad);
     G4RotationMatrix * yzRot = new G4RotationMatrix;
     yzRot->rotateY(CLHEP::halfpi*rad);
     yzRot->rotateZ(CLHEP::halfpi*rad);
     G4RotationMatrix * xzRot = new G4RotationMatrix;
     xzRot->rotateX(CLHEP::halfpi*rad);
     xzRot->rotateZ(CLHEP::halfpi*rad);
//
//   Set the wall size, based on a 48" width, centered.
//   Wall will be built as actual (2022).
//   Two sections 20 inches wide on sides, one center column 8 inches wide.
//
     const int nRows   = 18;
     const int nCols   =  3;
     const int nLayers =  2;
     G4ThreeVector brickDim =
       G4ThreeVector(brick->GetSolid()->GetExtent().GetXmax(),
                     brick->GetSolid()->GetExtent().GetYmax(),
                     brick->GetSolid()->GetExtent().GetZmax());
     sprintf(lineOutput,formDimOut,brick->GetName().c_str(),
       brickDim.x(),brickDim.y(),brickDim.z());
     G4cout << lineOutput;
     G4bool checkOverlaps = true;
//
//   Build the side section, consisting of two columns of bricks
//   on their edge and one of bricks on their end.
//
     G4ThreeVector sideWallDim(brickDim.y() + (nCols - 1) * brickDim.z() +
                         nCols * 0.5 * fLeadHorizGap,
                         nRows * brickDim.y(),
			 nLayers * (brickDim.x() + 0.5 * fLeadHorizGap));
     G4Box * sideWallBox = new G4Box("SideWall",
       sideWallDim.x(),sideWallDim.y(),sideWallDim.z());
     sprintf(lineOutput,formDimOut,sideWallBox->GetName().c_str(),
       sideWallDim.x(),sideWallDim.y(),sideWallDim.z());
     G4cout << lineOutput;
     G4LogicalVolume * sideWall = new G4LogicalVolume(sideWallBox,
       fEnvironmentMaterial,sideWallBox->GetName());
     G4VisAttributes *att_invis = new G4VisAttributes(false);
     sideWall->SetVisAttributes(att_invis);
//
//  The long edge columns:
//
     for(int row = 0; row < nRows; row++){
       double ypos = (2 * row + 1) * brickDim.y() - sideWallDim.y();
       for(int col = 0; col < nCols; col++){
         if(col != 1){
           double xpos = (col + 1) * (brickDim.z() + 0.5 * fLeadHorizGap) -
	                   sideWallDim.x();
           xpos += col * (brickDim.y() + 0.5 * fLeadHorizGap);
           for(int layer = 0; layer < nLayers; layer++){
             sprintf(name,"Brick_%i_%i_%i",layer,row,col);
             double zpos =
	       (2 * layer + 1) * (brickDim.x() + 0.5 * fLeadHorizGap) -
	       sideWallDim.z();
             G4ThreeVector brickPos(xpos,ypos,zpos);
             sprintf(lineOutput,formPosOut,name,
               brickPos.x(),brickPos.y(),brickPos.z());
             G4cout << lineOutput;
             new G4PVPlacement(yRot,brickPos,brick,name,
               sideWall,false,0,checkOverlaps);
           }
         }
       }
     }
//
//   The short edge columns:
//
     G4cout << G4endl << "Short edge columns" << G4endl;
     for(int row = 0; row < nRows/2; row++){
       int col = 1;
       for(int layer = 0; layer < nLayers; layer++){
         sprintf(name,"Brick_%i_%i_%i",layer,row,col);
         double xpos = 2 * (brickDim.z() + 0.75 * fLeadHorizGap) +
           brickDim.y() - sideWallDim.x();
//         xpos += brickDim.x() + 0.5 * fLeadHorizGap;
         double ypos = (2 * row + 1) * brickDim.z() - sideWallDim.y();
         double zpos =
           (2 * layer + 1) * (brickDim.x() + 0.5 * fLeadHorizGap) -
	    sideWallDim.z();
         G4ThreeVector brickPos(xpos,ypos,zpos);
         sprintf(lineOutput,formPosOut,name,
           brickPos.x(),brickPos.y(),brickPos.z());
         G4cout << lineOutput;
         new G4PVPlacement(xzRot,brickPos,brick,name,
           sideWall,false,0,checkOverlaps);
       }
     }
     G4cout << G4endl;
//
//   The center column
//   Scan through a full center column to determine the highest row in the
//   lower section.
//
     const int nCCols   =  1;
     int highRow  =  0;
     G4ThreeVector centerWallDim(nCCols * (brickDim.z() + 0.5 * fLeadHorizGap),
                         nRows * brickDim.y(),
			 nLayers * (brickDim.x() + 0.5 * fLeadHorizGap));
     G4cout << "   South Brick center wall dimensions: "
            << centerWallDim << G4endl;
     for(int row = 0; row < nRows; row++){
       int layer = 0;
       int col = 0;
       sprintf(name,"Brick_%i_%i_%i",layer,row,col);
       double xpos = 0.0;
       double ypos = (2 * row + 1) * brickDim.y() - centerWallDim.y();
       double zpos = 0.0;
       G4ThreeVector brickPos(xpos,ypos,zpos);
       G4ThreeVector brickPosShield = brickPos + centerWallDim + basePos;
       G4ThreeVector deltaBeamPos = beamPos - brickPosShield;
       G4cout << name << ",  position: " << brickPos
              << "   delta beam: " << deltaBeamPos << G4endl;
       if(deltaBeamPos.y() > 2.0 * brickDim.x()){
         highRow = row;
       }
     }
     G4cout << "   Highest row for lower section: " << highRow << G4endl;
     G4cout << G4endl;
//
//   The center column is composed of an upper and lower section,
//   separated by a beam gap of some number of bricks.
//   The lower center column:
//
     const int nLRows   = highRow + 1;
     const int beamGap  = 1;
     const int nURows   = nRows - nLRows - beamGap;
//
     G4ThreeVector centerLWallDim(nCCols * (brickDim.z() + 0.5 * fLeadHorizGap),
                         nLRows * brickDim.y(),
			 nLayers * (brickDim.x() + 0.5 * fLeadHorizGap));
     G4Box * centerLWallBox = new G4Box("CenterLWall",
       centerLWallDim.x(),centerLWallDim.y(),centerLWallDim.z());
     G4LogicalVolume * centerLWall = new G4LogicalVolume(centerLWallBox,
       fEnvironmentMaterial,centerLWallBox->GetName());
     centerLWall->SetVisAttributes(att_invis);
     sprintf(lineOutput,formDimOut,centerLWallBox->GetName().c_str(),
       centerLWallDim.x(),centerLWallDim.y(),centerLWallDim.z());
     G4cout << lineOutput;
     G4cout << G4endl << "Lower center column" << G4endl;
     for(int row = 0; row < nLRows; row++){
       int col = 0;
       for(int layer = 0; layer < nLayers; layer++){
         sprintf(name,"Brick_%i_%i_%i",layer,row,col);
         double xpos = 0.0;
         double ypos = (2 * row + 1) * brickDim.y() - centerLWallDim.y();
         double zpos =
           (2 * layer + 1) * (brickDim.x() + 0.5 * fLeadHorizGap) -
	    centerLWallDim.z();
         G4ThreeVector brickPos(xpos,ypos,zpos);
         G4ThreeVector brickPosShield = brickPos - basePos;
         G4ThreeVector deltaBeamPos = brickPosShield - beamPos;
         sprintf(lineOutput,formPosOut,name,
           brickPos.x(),brickPos.y(),brickPos.z());
         G4cout << lineOutput;
         new G4PVPlacement(yRot,brickPos,brick,name,
            centerLWall,false,0,checkOverlaps);
       }
     }
     G4cout << G4endl;
//
//   The upper center column:
//
     G4ThreeVector centerUWallDim(nCCols * (brickDim.z() + 0.5 * fLeadHorizGap),
                         nURows * brickDim.y(),
			 nLayers * (brickDim.x() + 0.5 * fLeadHorizGap));
     G4Box * centerUWallBox = new G4Box("CenterUWall",
       centerUWallDim.x(),centerUWallDim.y(),centerUWallDim.z());
     G4LogicalVolume * centerUWall =
       new G4LogicalVolume(centerUWallBox,fEnvironmentMaterial,
         centerUWallBox->GetName());
     centerUWall->SetVisAttributes(att_invis);
     sprintf(lineOutput,formDimOut,centerUWallBox->GetName().c_str(),
       centerUWallDim.x(),centerUWallDim.y(),centerUWallDim.z());
     G4cout << lineOutput;
     G4cout << G4endl << "Upper center column" << G4endl;
     for(int row = 0; row < nURows; row++){
       int col = 0;
       for(int layer = 0; layer < nLayers; layer++){
         sprintf(name,"Brick_%i_%i_%i",layer,row,col);
         double xpos = 0.0;
         double ypos = (2 * row + 1) * brickDim.y() - centerUWallDim.y();
         double zpos =
           (2 * layer + 1) * (brickDim.x() + 0.5 * fLeadHorizGap) -
	    centerUWallDim.z();
         G4ThreeVector brickPos(xpos,ypos,zpos);
         sprintf(lineOutput,formPosOut,name,
           brickPos.x(),brickPos.y(),brickPos.z());
         G4cout << lineOutput;
         new G4PVPlacement(yRot,brickPos,brick,name,
            centerUWall,false,0,checkOverlaps);
       }
     }
     G4cout << G4endl;
//
     return sideWall;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructSWallPlug(){
//
//   Construct the beam hole plug for the south wall.
//   This will be built so that the beam is expected to pass through
//    x = 0, y = 0.
//   This is hard-coded for a beam gap of two bricks spacing.
//
     G4cout << G4endl << "In ConstructSWallPlug..." << G4endl;
     G4bool checkOverlaps = true;
//
     if(!fUseSouthWall || !fUseSouthWallPlug){
       G4cout << " The south wall plug is not being made" << G4endl << G4endl;
       return 0;
     }
//
//   Interrupt the plug construction to install the steel on the
//   south side of the lead.
//   Dimensions are approximate.
//
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* steel  = nist->FindOrBuildMaterial("G4_Fe");
     G4VisAttributes *att_invis = new G4VisAttributes(false);
//
//   The generic lead brick must exist first.
//
     G4LogicalVolume * brick =
       G4LogicalVolumeStore::GetInstance()->GetVolume("LeadBrick");
     if(!brick){
       G4cout << "  Lead brick for south wall is not yet made" << G4endl;
       return 0;
     }
     else{
       G4cout << "  Found brick " << brick->GetName() << G4endl;
     }
     G4ThreeVector brickDim(brick->GetSolid()->GetExtent().GetXmax(),
                            brick->GetSolid()->GetExtent().GetYmax(),
                            brick->GetSolid()->GetExtent().GetZmax());
//
//   Several physical volumes must exist for this to work
//
     const int nRequired = 2;
     const char * requiredNames[nRequired] =
       {"Barrel","CenterLWall"};
     G4VPhysicalVolume * requiredPhysVol[nRequired];
     G4ThreeVector requiredPos[nRequired];
     for(int vol = 0; vol < nRequired; vol++){
       requiredPhysVol[vol] =
         G4PhysicalVolumeStore::GetInstance()->GetVolume(requiredNames[vol]);
       if(!requiredPhysVol[vol]){
         G4cout << "    " << requiredNames[vol] << " not found" << G4endl;
         return 0;
       }
       else{
         requiredPos[vol] = requiredPhysVol[vol]->GetTranslation();
       }
     }
//
//   Sources of information exist, so continue to build the plug.
//
//   Build the plug volume.  It is oversize to accomodate options
//
     const double halfSpacerThickness = 0.5 * 2.54 * cm;
     const double halfSpacerWidth = 2.0 * 2.54 * cm;
     const double halfSpacerDepth = 2.0 * 2.54 * cm;
     G4Color clear(0.0,0.0,0.0);
     const G4ThreeVector plugDim(brickDim.z() + 2.0 * brickDim.x() +
                                 1.5 * fLeadHorizGap,
                      brickDim.x() + halfSpacerThickness + brickDim.z(),
				 brickDim.y() + 0.5 * fLeadHorizGap);
     G4Box * plugBox = new G4Box("WallPlug",plugDim.x(),
       plugDim.y(),plugDim.z());
     G4LogicalVolume * plugVol =
       new G4LogicalVolume(plugBox,fEnvironmentMaterial,plugBox->GetName());
     plugVol->SetVisAttributes(att_invis);
     sprintf(lineOutput,formDimOut,plugBox->GetName().c_str(),plugDim.x(),
       plugDim.y(),plugDim.z());
     G4cout << lineOutput;
//
//   Build the spacer that opens the beam hole through the plug
//
     G4Color blue(0.0,0.0,1.0);
     G4VisAttributes *att_blue = new G4VisAttributes(blue);
     const G4ThreeVector spacerDim(halfSpacerWidth - fCollRadius,
                                   halfSpacerThickness,halfSpacerDepth);
     G4Box * spacerBox = new G4Box("PlugSpacer",spacerDim.x(),
       spacerDim.y(),spacerDim.z());
     G4LogicalVolume * spacerVol =
       new G4LogicalVolume(spacerBox,steel,spacerBox->GetName());
     spacerVol->SetVisAttributes(att_blue);
     sprintf(lineOutput,formDimOut,spacerBox->GetName().c_str(),spacerDim.x(),
       spacerDim.y(),spacerDim.z());
     G4cout << lineOutput;
//
//   We have to figure out where the beam line is within the hole in the wall.
//   Top half or bottom?
//
     G4ThreeVector lowHoleEdge = requiredPos[1];
     G4LogicalVolume * centerLWallVol = requiredPhysVol[1]->GetLogicalVolume();
     lowHoleEdge.setY(requiredPos[1].y() +
       centerLWallVol->GetSolid()->GetExtent().GetYmax());
     G4cout << "      Beam position: " << requiredPos[0] << G4endl;
     G4cout << "     Beam hole edge: " << lowHoleEdge << G4endl;
     const int totalHBricks = 3;
     int nLowSideBricks = 1;
     double deltaBeamEdge = requiredPos[0].y() - lowHoleEdge.y();
     if(deltaBeamEdge > 2.0 * brickDim.x()) nLowSideBricks = 2;
//
     G4ThreeVector spacerPos[2];
     spacerPos[0].setX(-fCollRadius - spacerDim.x());
     spacerPos[1].setX(-spacerPos[0].x());
//
     G4RotationMatrix * xRot = new G4RotationMatrix;
     xRot->rotateX(CLHEP::halfpi*rad);
     G4RotationMatrix * xyRot = new G4RotationMatrix;
     xyRot->rotateX(CLHEP::halfpi*rad);
     xyRot->rotateY(CLHEP::halfpi*rad);
//
//   Position the spacers:
//
     for(int vol = 0; vol < 2; vol++){
       sprintf(name,"%s_%i",spacerBox->GetName().c_str(),vol);
       sprintf(lineOutput,formPosOut,name,spacerPos[vol].x(),
         spacerPos[vol].y(),spacerPos[vol].z());
       G4cout << lineOutput;
       new G4PVPlacement(0,spacerPos[vol],spacerVol,name,
         plugVol,false,0,checkOverlaps);
     }
//
//   Position the horizontal bricks:
//
     G4ThreeVector brickPos;
     for(int vol = 0; vol < nLowSideBricks; vol++){
       double yPos = -halfSpacerThickness + brickDim.x() -
        (nLowSideBricks - vol) * 2.0 * brickDim.x();
       brickPos.setY(yPos);
       sprintf(name,"%s_%i",brick->GetName().c_str(),vol);
       sprintf(lineOutput,formPosOut,name,brickPos.x(),
         brickPos.y(),brickPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xyRot,brickPos,brick,name,
         plugVol,false,0,checkOverlaps);
     }
     for(int vol = nLowSideBricks; vol < totalHBricks; vol++){
       double yPos =  halfSpacerThickness + brickDim.x() -
        (nLowSideBricks - vol) * 2.0 * brickDim.x();
       brickPos.setY(yPos);
       sprintf(name,"%s_%i",brick->GetName().c_str(),vol);
       sprintf(lineOutput,formPosOut,name,brickPos.x(),
         brickPos.y(),brickPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xyRot,brickPos,brick,name,
         plugVol,false,0,checkOverlaps);
     }
//
//  Install 2 side bricks to close it off
//
     brickPos.setX(brickDim.x() - plugDim.x() + 0.5 * fLeadHorizGap);
     brickPos.setY(brickDim.z() -
                   halfSpacerThickness -
                   nLowSideBricks * 2.0 * brickDim.x());
     brickPos.setZ(0.0);
     for(int vol = totalHBricks; vol < totalHBricks + 2; vol++){
       sprintf(name,"%s_%i",brick->GetName().c_str(),vol);
       sprintf(lineOutput,formPosOut,name,brickPos.x(),
         brickPos.y(),brickPos.z());
       G4cout << lineOutput;
       new G4PVPlacement(xRot,brickPos,brick,name,
         plugVol,false,0,checkOverlaps);
       brickPos.setX(-brickPos.x());
     }
     G4cout << G4endl;

     return plugVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructPosts(){
//
//  The red posts
//  Dimensions from F10082000.
//
     G4cout << G4endl << "In ConstructPosts..." << G4endl;
     G4bool checkOverlaps = true;
     G4Material* postMaterial = 0;
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* steel  = nist->FindOrBuildMaterial("G4_Fe");
     postMaterial = steel;
//
     G4Color red(1.0,0.0,0.0);
     G4VisAttributes *att_red = new G4VisAttributes(red);
     G4Color dull_red(0.8,0.0,0.0);
     G4VisAttributes *att_dull_red = new G4VisAttributes(dull_red);
//
     const G4ThreeVector origin(0.0,0.0,0.0);
     double postHeight = 131.8 * 2.54*cm;
     G4ThreeVector postVolDim(4.0 * 2.54*cm,0.5 * postHeight,6.0 * 2.54*cm);
     G4ThreeVector postIntDim = postVolDim;
     postIntDim.setX(postVolDim.x() - 0.25 * 2.54*cm);
     postIntDim.setZ(postVolDim.z() - 0.25 * 2.54*cm);
     G4cout << "   Red post dimensions: " << postVolDim << G4endl;
     G4cout << "   Red post   material: " << postMaterial->GetName() << G4endl;
//
     G4Box * postVolBox = new G4Box("RedPost",postVolDim.x(),
       postVolDim.y(),postVolDim.z());
     G4Box * postIntBox = new G4Box("RedPostFill",postIntDim.x(),
       postIntDim.y(),postIntDim.z());
     G4LogicalVolume * postVol =
       new G4LogicalVolume(postVolBox,postMaterial,"RedPost");
     G4LogicalVolume * postIntVol =
       new G4LogicalVolume(postIntBox,fEnvironmentMaterial,"RedPostAir");
     postVol->SetVisAttributes(att_red);
     postIntVol->SetVisAttributes(att_dull_red);
     new G4PVPlacement(0,origin,postIntVol,"PostFiller",
       postVol,false,0,checkOverlaps);

   return postVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructSWallPlate(){
//
//   Create the steel plate south of the stationary lead wall.
//   Dimensions from F10143484.
//
     G4cout << G4endl << "In ConstructSWallPlate..." << G4endl;
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* steel  = nist->FindOrBuildMaterial("G4_Fe");
//
     G4Color green(0.0,0.8,0.4);
     G4VisAttributes *att_green = new G4VisAttributes(green);
     const G4ThreeVector plateDim(29*2.54*cm, 40.5*2.54*cm, 1.5*mm);
     const G4ThreeVector  holeDim( 4*2.54*cm,  3*2.54*cm, 1.5*mm);
     G4ThreeVector  holePos(0.,0.0,0.0);
     G4Box * plateBox = new G4Box("WallPlate",plateDim.x(),
       plateDim.y(),plateDim.z());
     G4Box *  holeBox = new G4Box("WallHole",holeDim.x(),
       holeDim.y(),holeDim.z());
     G4SubtractionSolid * hollowPlate =
       new G4SubtractionSolid("HollowPlate",plateBox,holeBox,0,holePos);
     G4LogicalVolume * plateVol =
       new G4LogicalVolume(hollowPlate,steel,plateBox->GetName());
     plateVol->SetVisAttributes(att_green);
//
     return plateVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBasePlate(){
//
//
//   Create the steel baseplate the shield sits on.
//
     G4cout << G4endl << "In ConstructBasePlate..." << G4endl;
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* steel  = nist->FindOrBuildMaterial("G4_Fe");
//
     G4Color red(1.0,0.0,0.0);
     G4VisAttributes *att_red = new G4VisAttributes(red);
//
//   Dimensions recreated from F10082000.
//   The cutouts for the north posts require some complexity here.
//
     G4ThreeVector basePlateDim =
       G4ThreeVector(30.0 * 2.54 * cm,
                     0.125 * 2.54 * cm, 37.75 * 2.54 * cm);
     G4ThreeVector cutoutDim =
       G4ThreeVector(3.0 * 2.54 * cm,
                     basePlateDim.y(), 2.0 * 2.54 * cm);
     G4Box * basePlate = new G4Box("Base Plate",basePlateDim.x(),
                                basePlateDim.y(),basePlateDim.z());
     G4Box * cutout = new G4Box("Cutout",cutoutDim.x(),
                                 cutoutDim.y(),cutoutDim.z());
     G4ThreeVector corner(basePlateDim.x(),0.0,basePlateDim.z());
     G4ThreeVector cutoutPos[2] = {corner, corner};
     cutoutPos[0].setX(cutoutDim.x() - corner.x());
     cutoutPos[0].setZ(corner.z() - cutoutDim.z());
     cutoutPos[1].setX(-cutoutPos[0].x());
     cutoutPos[1].setZ( cutoutPos[0].z());
//
     sprintf(lineOutput,formDimOut,basePlate->GetName().c_str(),
      basePlateDim.x(),basePlateDim.y(),basePlateDim.z());
     G4cout << lineOutput;
     sprintf(lineOutput,formDimOut,cutout->GetName().c_str(),
      cutoutDim.x(),cutoutDim.y(),cutoutDim.z());
     G4cout << lineOutput;
     sprintf(lineOutput,formPosOut,"cutoutPos[0]: ",
      cutoutPos[0].x(),cutoutPos[0].y(),cutoutPos[0].z());
     G4cout << lineOutput;
     sprintf(lineOutput,formPosOut,"cutoutPos[1]: ",
      cutoutPos[1].x(),cutoutPos[1].y(),cutoutPos[1].z());
     G4cout << lineOutput;
//
     G4SubtractionSolid * cutPlate0 =
       new G4SubtractionSolid("Cut plate 0",basePlate,cutout,0,cutoutPos[0]);
     G4SubtractionSolid * cutPlate1 =
       new G4SubtractionSolid("Cut plate 1",cutPlate0,cutout,0,cutoutPos[1]);
     cutPlate1->DumpInfo();
     G4LogicalVolume* basePlateVolume =
       new G4LogicalVolume(cutPlate1,steel,basePlate->GetName());
     basePlateVolume->SetVisAttributes(att_red);

     return basePlateVolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructStepPlate(){
//
//
//   Create the steel plate the lead wall sits on.
//
     G4cout << G4endl << "In ConstructStepPlate..." << G4endl;
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* steel  = nist->FindOrBuildMaterial("G4_Fe");
//
     G4Color red(1.0,0.0,0.0);
     G4VisAttributes *att_red = new G4VisAttributes(red);
     const double postSpacing = 50 * 2.54 * cm;
//
//   Dimensions recreated from F10082000.
//
     G4ThreeVector stepPlateDim =
       G4ThreeVector(0.5 * postSpacing,
                     0.125 * 2.54 * cm, 6.0 * 2.54 * cm);
     G4Box * stepPlate = new G4Box("Step Plate",stepPlateDim.x(),
                                stepPlateDim.y(),stepPlateDim.z());
//
     sprintf(lineOutput,formDimOut,stepPlate->GetName().c_str(),
      stepPlateDim.x(),stepPlateDim.y(),stepPlateDim.z());
     G4cout << lineOutput;
//
     G4LogicalVolume* stepPlateVolume =
       new G4LogicalVolume(stepPlate,steel,stepPlate->GetName());
     stepPlateVolume->SetVisAttributes(att_red);

     return stepPlateVolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructCryostat(){
//
//  As the name says
//
//  Dimensions estimated from the Cryoconcept drawing on docdb #430.
//
     G4cout << G4endl << "In ConstructCryostat..." << G4endl;
     if(!fUseCryostat){
       G4cout << "  The cryostat is not being used" << G4endl << G4endl;
       return 0;
     }
     G4bool checkOverlaps = true;
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* vacuum  = nist->FindOrBuildMaterial("G4_Galactic");
    const int nCylind = 4;
    const double flangeCuRad =  7*mm;  // estimated from the drawing
    const double flangeFeRad = 10*mm;  // estimated from the drawing
    const double cylRadius[nCylind] = {0.5 * 334*mm - flangeCuRad,
                                       0.5 * 367*mm - flangeCuRad,
                                       0.5 * 400*mm - flangeCuRad,
                                       0.5 * 456*mm - flangeFeRad};
    const double cylLength[nCylind] = {745*mm,854*mm,981.5*mm,1084*mm};
    const double cylThick[nCylind] = {1.5*mm,1.5*mm,2.5*mm,3.5*mm};
//  Staggers are distances from the tops of the cylinders to the
//  top of the OVC.
    const double topStagger[nCylind] = {149*mm,95*mm,39*mm,0.0};
    const char * nameTubs[nCylind] = {"MC","CP","Still","OVC"};
    G4Tubs * cylTubs[nCylind];
    G4Tubs * vacTubs;
    G4LogicalVolume * cylVol[nCylind];
    G4LogicalVolume * vacVol;
//
     G4Material* cryostatMaterial = 0;
     G4Material* cylinderMaterial = 0;
     G4Material* steel  = nist->FindOrBuildMaterial(fCryoOVCMater);
     G4Material* copper = nist->FindOrBuildMaterial(fCryoShieldMater);
     G4Material* lead   = nist->FindOrBuildMaterial("G4_Pb");
     cryostatMaterial = steel;
     cylinderMaterial = copper;
     G4cout << "   Cryostat material: " << cryostatMaterial->GetName() << G4endl;
     G4cout << "   Cylinder material: " << cylinderMaterial->GetName() << G4endl;
     G4cout << "     Target material: " <<  fTargetMaterial->GetName() << G4endl;
//
    for(int cyl = 0; cyl < nCylind; cyl++){
      double rMin = 0.0;
      if(cyl < nCylind - 1){
        rMin = cylRadius[cyl] - cylThick[cyl];
      }
      double rMax = cylRadius[cyl];
      double dz = 0.5 * cylLength[cyl];
      cylTubs[cyl] = new G4Tubs(nameTubs[cyl],rMin,rMax,dz,0.0,CLHEP::twopi);
      cylTubs[cyl]->DumpInfo();
    }
    vacTubs = new G4Tubs("VacTubs",0.0,
      cylRadius[nCylind - 1] - cylThick[nCylind - 1],
      0.5 * cylLength[nCylind - 1],0.0,CLHEP::twopi);


    const G4Color red(1.0,0.3,0.0);
    const G4Color grayColor(0.5,0.5,0.5);
    const G4VisAttributes *att_invis = new G4VisAttributes(false);
    const G4VisAttributes *att_red = new G4VisAttributes(red);
    const G4VisAttributes *att_gray = new G4VisAttributes(grayColor);
    for(int cyl = 0; cyl < nCylind - 1; cyl++){
      cylVol[cyl] = new G4LogicalVolume(cylTubs[cyl],
                                        cylinderMaterial,nameTubs[cyl]);
      cylVol[cyl]->SetVisAttributes(att_red);
    }
    cylVol[nCylind - 1] =
      new G4LogicalVolume(cylTubs[nCylind - 1],
                          cryostatMaterial,nameTubs[nCylind - 1]);
    vacVol = new G4LogicalVolume(vacTubs,vacuum,"Vacuum");
    vacVol->SetVisAttributes(att_invis);
//
    G4ThreeVector origin(0.0,0.0,0.0);
    G4ThreeVector cylPos[nCylind];
    new G4PVPlacement(0,origin,vacVol,"Vacuum",
       cylVol[nCylind - 1],false,0,checkOverlaps);
    for(int cyl = 0; cyl < nCylind - 1; cyl++){
      cylPos[cyl] = origin;
      cylPos[cyl].setZ(0.5 * (cylLength[nCylind - 1] - cylLength[cyl]) -
                  topStagger[cyl]);
      G4cout << nameTubs[cyl] << ": " << cylPos[cyl] << G4endl;
      new G4PVPlacement(0,cylPos[cyl],cylVol[cyl],nameTubs[cyl],
         vacVol,false,0,checkOverlaps);
    }
//
//  Add the copper/lead shield plug at the top.
//  Dimensions are scaled from the drawing.
//  plugTop is distance from the plug top to the MC cylinder top.
//
    const double plugPbRadius = 120.4 * mm;
    const double plugCuRadius = plugPbRadius + 24.8 * mm;
    const double plugPbHalfHeight = 50.6 * mm;
    const double plugCuHalfHeight = plugPbHalfHeight + 14.6 * mm;
    const double plugTop = 67.5 * mm;
    const double plugDetGap = 105.8 * mm;
    G4ThreeVector plugPos = origin;
    plugPos.setZ(cylPos[0].z() + 0.5 * cylLength[0] - plugCuHalfHeight -
                 plugTop);
    G4Tubs * plugPbTube =
      new G4Tubs("PlugPb",0.0,plugPbRadius,plugPbHalfHeight,0.0,CLHEP::twopi);
    G4Tubs * plugCuTube =
      new G4Tubs("PlugCu",0.0,plugCuRadius,plugCuHalfHeight,0.0,CLHEP::twopi);
    plugCuTube->DumpInfo();
    G4LogicalVolume * plugPbVol =
        new G4LogicalVolume(plugPbTube,lead,plugPbTube->GetName());
    G4LogicalVolume * plugCuVol =
        new G4LogicalVolume(plugCuTube,copper,plugCuTube->GetName());
    plugPbVol->SetVisAttributes(att_gray);
    plugCuVol->SetVisAttributes(att_red);
    sprintf(lineOutput,formPosOut,plugCuTube->GetName().c_str(),
       plugPos.x(),plugPos.y(),plugPos.z());
    G4cout << lineOutput;
    new G4PVPlacement(0,origin,plugPbVol,plugPbVol->GetName(),
         plugCuVol,false,0,checkOverlaps);
    new G4PVPlacement(0,plugPos,plugCuVol,plugCuVol->GetName(),
         vacVol,false,0,checkOverlaps);

    if(fUseAltTarget){
      G4cout << "Implementing the alternative detector - " << G4endl;
           sprintf(lineOutput,formDimOut,"Alt Target",
     	fAltTargetSize.x(),fAltTargetSize.y(),fAltTargetSize.z());
           G4cout << lineOutput;
           sprintf(lineOutput,formPosOut,"Alt Target",
     	fAltTargetPosition.x(),fAltTargetPosition.y(),fAltTargetPosition.z());
           G4cout << lineOutput;
           //double detRad = 0.5 * sqrt(fAltTargetSize.x() * fAltTargetSize.x() +
           //                           fAltTargetSize.z() * fAltTargetSize.z());
           double detRad =  fAltTargetSize.x();
           //double detectorTubeIncLength = 0.5 * fAltTargetSize.y();
           double detectorTubeIncLength = 0.5 * fAltTargetSize.z();
           //double detectorZOffset = -5.0 * cm;
           double detectorZOffset = -6.0 * cm;
           G4Tubs * detectorTubsInc =
             new G4Tubs("DetTubsInc",0.0,detRad + 0.1*mm,
     	  detectorTubeIncLength + 0.1 * mm,0.0,CLHEP::twopi);
           detectorTubsInc->DumpInfo();
           G4LogicalVolume * detectorVolInc =
             new G4LogicalVolume(detectorTubsInc,vacuum,"DetVolInc");
           G4Box * detectorBox =
             new G4Box("DetBox",0.5 * fAltTargetSize.x(),
     	                   0.5 * fAltTargetSize.y(),0.5 * fAltTargetSize.z());
           //G4Tubs * detectorBox =
          //   new G4Tubs("DetBox",0.0,
          //                fAltTargetSize.y(),0.5 * fAltTargetSize.z(),0.0,CLHEP::twopi);
           G4LogicalVolume * detectorVol =
             new G4LogicalVolume(detectorBox,fTargetMaterial,"DetVol");
           G4ThreeVector detPos = origin;
           sprintf(lineOutput,formPosOut,detectorVol->GetName().c_str(),
             detPos.x(),detPos.y(),detPos.z());
           G4cout << lineOutput;
           G4RotationMatrix * xRot = new G4RotationMatrix;
           xRot->rotateX(CLHEP::halfpi*rad);
            //new G4PVPlacement(xRot,detPos,detectorVol,detectorVol->GetName(),
            //  detectorVolInc,false,0,checkOverlaps);
            new G4PVPlacement(0,detPos,detectorVol,detectorVol->GetName(),
                detectorVolInc,false,0,checkOverlaps);
           G4ThreeVector detIncPos = plugPos;
           detIncPos.setZ(plugPos.z() - plugCuHalfHeight - plugDetGap -
            detectorTubeIncLength + detectorZOffset);
           detIncPos += fAltTargetPosition;
           sprintf(lineOutput,formPosOut,detectorVolInc->GetName().c_str(),
            detIncPos.x(),detIncPos.y(),detIncPos.z());
           G4cout << lineOutput;
           sprintf(name,"Det_0");
           new G4PVPlacement(0,detIncPos,detectorVolInc,name,
              vacVol,false,0,checkOverlaps);
    }
    else{

        //    Build a target of Ge crystals
       if (N_DETECTORS) {
         const double detRad = 50*mm;
         const double detLength = 33*mm;
         const double detSpacing = 36.7*mm; // from scaling the drawing
         //const double detSpacing = 0*mm; // from scaling the drawing
         const double detectorTubeIncLength =
           0.5 * (detLength + (N_DETECTORS - 1) * detSpacing);
         G4Tubs * detectorTubsInc =
           new G4Tubs("DetTubsInc",0.0,detRad + 0.1*mm,
      detectorTubeIncLength,0.0,CLHEP::twopi);
         detectorTubsInc->DumpInfo();
         G4LogicalVolume * detectorVolInc =
           new G4LogicalVolume(detectorTubsInc,vacuum,"DetVolInc");
         detectorVolInc->SetVisAttributes(att_invis);
         G4Tubs * detectorTubs =
           new G4Tubs("DetTubs",0.0,detRad,0.5 * detLength,0.0,CLHEP::twopi);
         G4LogicalVolume * detectorVol =
           new G4LogicalVolume(detectorTubs,fTargetMaterial,"DetVol");
         G4ThreeVector detPos[N_DETECTORS];
         G4VPhysicalVolume * detPhys[N_DETECTORS];
         for(int det = 0; det < N_DETECTORS; det++){
           sprintf(name,"Det_%i",det);
           detPos[det] = origin;
           detPos[det].setZ(-0.5 * detLength + detectorTubeIncLength -
                       det * detSpacing);
           sprintf(lineOutput,formPosOut,name,
             detPos[det].x(),detPos[det].y(),detPos[det].z());
           G4cout << lineOutput;
           detPhys[det] = new G4PVPlacement(0,detPos[det],detectorVol,name,
              detectorVolInc,false,det,checkOverlaps);
         }
         G4ThreeVector detPosInc = plugPos;
         detPosInc.setZ(plugPos.z() - plugCuHalfHeight - plugDetGap -
          detectorTubeIncLength );
         sprintf(lineOutput,formPosOut,detectorVolInc->GetName().c_str(),
          detPosInc.x(),detPosInc.y(),detPosInc.z());
         G4cout << lineOutput;
         new G4PVPlacement(0,detPosInc,detectorVolInc,detectorVolInc->GetName(),
            vacVol,false,0,checkOverlaps);

         G4cout << "   Detector positions in the vacuum" << G4endl;
         G4ThreeVector detPosVac[N_DETECTORS];
         for(int det = 0; det < N_DETECTORS; det++){
           detPosVac[det] = detPosInc + detPos[det];
           sprintf(lineOutput,formPosOut,detPhys[det]->GetName().c_str(),
            detPosVac[det].x(),detPosVac[det].y(),detPosVac[det].z());
           G4cout << lineOutput;
         }
         G4cout << G4endl << "   Detector distances from the plug" << G4endl;
         double plugBottomY = plugPos.z() - plugCuHalfHeight;
         for(int det = 0; det < N_DETECTORS; det++){
           double dist = plugBottomY - detPosVac[det].z() - 0.5 * detLength;
           G4cout << "    " << detPhys[det]->GetName() << ": "
           << dist << G4endl;
         }
       }

    }

    return cylVol[nCylind - 1];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructCart(){
//
//  Makes the moveable shield.
//  This is revised for the 2022 reconfiguration of the lead.
//  Staggering is not implemented.
//  Definitions consistent with the south wall.
//  Columns - vary in x
//  Rows -    vary in y
//  Layers -  vary in z
//
     G4cout << G4endl << "In ConstructCart..." << G4endl;
     if(!fUseCartShield){
       G4cout << "    The cart shield is not being made" << G4endl << G4endl;
       return 0;
     }
     G4bool checkOverlaps = true;
     G4NistManager* nist = G4NistManager::Instance();
     const int nSect = 4;
     enum Surfacetype{PLATE, BOTTOM, SOUTH, SIDE};
     const char * sectName[nSect] =
       {"CartPlate","CartBottom","CartSouth","CartSide"};
     const int sectCol[nSect] = {0,4,5,5};
     const int sectRow[nSect] = {0,2,18,18};
     const int sectLayer[nSect] = {0,9,2,2};
     G4Material* sectMat[nSect] =
      {fEnvironmentMaterial,fEnvironmentMaterial,
       fEnvironmentMaterial,fEnvironmentMaterial};
     G4ThreeVector sectDim[nSect];
     G4Box * sectBox[nSect];
     G4LogicalVolume * sectVol[nSect];
     G4ThreeVector origin(0.0,0.0,0.0);
//
     G4LogicalVolume * brick =
       G4LogicalVolumeStore::GetInstance()->GetVolume("LeadBrick");
     if(!brick){
       G4cout << "  Lead brick for south wall is not yet made" << G4endl;
       return 0;
     }
     else{
       G4cout << "  Found brick " << brick->GetName() << G4endl;
     }
     G4ThreeVector brickDim =
       G4ThreeVector(brick->GetSolid()->GetExtent().GetXmax(),
                     brick->GetSolid()->GetExtent().GetYmax(),
                     brick->GetSolid()->GetExtent().GetZmax());
     sprintf(lineOutput,formDimOut,brick->GetName().c_str(),
       brickDim.x(),brickDim.y(),brickDim.z());
     G4cout << lineOutput;
//
//   The base plate:
//
     int sect = 0;
     const double plateWidth     = 48.0 * 2.54 * cm;
     const double plateLength    = 46.0 * 2.54 * cm;
     const double plateThickness = 0.25 * 2.54 * cm;
     sectDim[sect].setX(0.5 * plateWidth);
     sectDim[sect].setY(0.5 * plateThickness);
     sectDim[sect].setZ(0.5 * plateLength);
     sectMat[sect] = nist->FindOrBuildMaterial("G4_Al");
     sprintf(lineOutput,formDimOut,
       sectName[sect],sectDim[sect].x(),sectDim[sect].y(),sectDim[sect].z());
     G4cout << lineOutput;
//
//   The brick layers:
//
     for(int section = 1; section < nSect; section++){
       sectDim[section].setX(sectCol[section] *
                             (brickDim.z() + 0.5 * fLeadHorizGap));
//     Bottom layer
       if(section == 1){
         sectDim[section].setY(sectRow[section] * brickDim.x());
         sectDim[section].setZ(sectLayer[section] *
                               (brickDim.y() + 0.5 * fLeadHorizGap));
       }
//     Side layers have first row laying flat.
       else{
         sectDim[section].setY(sectRow[section] * brickDim.y() +
	                       brickDim.x());
         sectDim[section].setZ(sectLayer[section] *
                               (brickDim.x() + 0.5 * fLeadHorizGap));
         if(brickDim.y() > sectLayer[section] *
                               (brickDim.x() + 0.5 * fLeadHorizGap))
           sectDim[section].setZ(brickDim.y());
       }
       sprintf(lineOutput,formDimOut,sectName[section],sectDim[section].x(),
	       sectDim[section].y(),sectDim[section].z());
       G4cout << lineOutput;
     }
//
//   Add a 1/2 width column to the bottom
//
     sect++;
     sectDim[sect].setZ(sectDim[sect].z() + brickDim.x());

     G4Color white(1.0,1.0,1.0);
     G4VisAttributes *att_invis = new G4VisAttributes(false);
     G4VisAttributes *att_white = new G4VisAttributes(white);
     for(int section = 0; section < nSect; section++){
       sectBox[section] = new G4Box(sectName[section],sectDim[section].x(),
                                 sectDim[section].y(),sectDim[section].z());
       sectVol[section] = new G4LogicalVolume(sectBox[section],
                                 sectMat[section],sectName[section]);
       if(section == 0){
         sectVol[section]->SetVisAttributes(att_white);
       }
       else{
         sectVol[section]->SetVisAttributes(att_invis);
       }
     }
//
//   Load the boxes with bricks:
//
     G4RotationMatrix * xRot = new G4RotationMatrix;
     xRot->rotateX(CLHEP::halfpi*rad);
     G4RotationMatrix * yRot = new G4RotationMatrix;
     yRot->rotateY(CLHEP::halfpi*rad);
     G4RotationMatrix * zRot = new G4RotationMatrix;
     zRot->rotateZ(CLHEP::halfpi*rad);
     G4RotationMatrix * zxRot = new G4RotationMatrix;
     zxRot->rotateZ(CLHEP::halfpi*rad);
     zxRot->rotateX(CLHEP::halfpi*rad);
     G4RotationMatrix * brickRot[nSect] = {0,zxRot,yRot,yRot};
     for(int section = 0; section < nSect; section++){
       G4cout << "Loading bricks into " << sectName[section] << G4endl;
       for(int col = 0; col < sectCol[section]; col++){
         for(int row = 0; row < sectRow[section]; row++){
           double xpos = (2 * col + 1) * (brickDim.z() + 0.5 * fLeadHorizGap) -
                     sectDim[section].x() ;
           double ypos = 0.0;
           double zpos = 0.0;
           for(int layer = 0; layer < sectLayer[section]; layer++){
             sprintf(name,"%s_Brick_%i_%i_%i",sectName[section],layer,row,col);
             if(section == 1){
               zpos =
	         (2 * layer + 1) * (brickDim.y() + 0.5 * fLeadHorizGap) -
	                    sectDim[section].z();
               ypos = (2 * row + 1) * brickDim.x() - sectDim[section].y();
             }
             else{
               if(row == 0){
                 zpos = brickDim.y() - sectDim[section].z();
                 ypos = brickDim.x() - sectDim[section].y();
               }
	       else{
                 zpos =
	           (2 * layer + 1) * (brickDim.x() + 0.5 * fLeadHorizGap) -
	                      sectDim[section].z();
                 ypos = (2 * row - 1) * brickDim.y() - sectDim[section].y() +
		        2.0 * brickDim.x();
               }
             }
             G4ThreeVector brickPos(xpos,ypos,zpos);
             sprintf(lineOutput,formPosOut,
               sectName[section],brickPos.x(),brickPos.y(),brickPos.z());
//             G4cout << lineOutput;
             if(row == 0){
               if(layer == 0){
                 new G4PVPlacement(zxRot,brickPos,brick,
                   name,sectVol[section],false,0,checkOverlaps);
               }
	     }
	     else{
               new G4PVPlacement(brickRot[section],brickPos,brick,
                 name,sectVol[section],false,0,checkOverlaps);
             }
           }
         }
       }
     }
//
//   The extra 1/2 column for the bottom
//
     sect = 1;
     for(int col = 0; col < sectCol[sect]; col++){
       int row = sectRow[sect];
       int layer = 0;
       double xpos = (2 * col + 1) * (brickDim.z() + 0.5 * fLeadHorizGap) -
                      sectDim[sect].x();
       double ypos = 0.0;
       double zpos = sectDim[sect].z() - brickDim.x();
       sprintf(name,"%s_Brick_%i_%i_%i",sectName[sect],layer,row,col);
       G4ThreeVector brickPos(xpos,ypos,zpos);
       sprintf(lineOutput,formPosOut,
         name,brickPos.x(),brickPos.y(),brickPos.z());
//       G4cout << lineOutput;
       new G4PVPlacement(yRot,brickPos,brick,name,
          sectVol[sect],false,0,checkOverlaps);
     }
//
     for(int section = 0; section < nSect; section++){
       sprintf(lineOutput,formDimOut,sectName[section],
         sectDim[section].x(),sectDim[section].y(),sectDim[section].z());
       G4cout << lineOutput;
     }
//
     if(fUseCartBeamhole){
//
//     Now remove bricks from the south wall for the beam hole.
//
       const int southSect = 2;
       const int centCol = 2;
       const int lowRow = 8;
       const int highRow = lowRow + 4;
       for(int row = lowRow; row < highRow; row++){
         G4ThreeVector bottomBrickPos;
         G4ThreeVector brickPos;
         for(int layer = 0; layer < sectLayer[southSect]; layer++){
           sprintf(name,"%s_Brick_%i_%i_%i",sectName[southSect],layer,row,centCol);
           for(int brickNum = sectVol[southSect]->GetNoDaughters() - 1;
	       brickNum >= 0 ; brickNum--){
             G4VPhysicalVolume * brickPhysVol =
	       sectVol[southSect]->GetDaughter(brickNum);
	     if(name == brickPhysVol->GetName()){
               if(layer == lowRow)
	         bottomBrickPos = brickPhysVol->GetTranslation();
	       brickPos = brickPhysVol->GetTranslation();
	       G4cout << "Brick to remove for beam hole: " << name << G4endl;
               sprintf(lineOutput,formPosOut,(brickPhysVol->GetName()).c_str(),
	          brickPos.x(),brickPos.y(),brickPos.z());
               G4cout << lineOutput;
//
//     Remove this brick from the wall
//
               sectVol[southSect]->RemoveDaughter(brickPhysVol);
	     }
           }
         }
       }
     }
     else{
       G4cout << "No beam hole installed in the cart shield" << G4endl;
     }
//
//   Unistrut frames that hold the bricks
//
     G4cout << "   Unistrut frame assembly: " << G4endl;
     const double sideWidth  = 32.0 * 2.54 * cm;
     const double sideHeight = 72.0 * 2.54 * cm;
     G4LogicalVolume * sideBottom   = ConstructUnistrut(sideWidth);
     G4LogicalVolume * sideVertical = ConstructUnistrut(sideHeight);
     G4ThreeVector sideBottomDim(sideBottom->GetSolid()->GetExtent().GetXmax(),
                                 sideBottom->GetSolid()->GetExtent().GetYmax(),
                                 sideBottom->GetSolid()->GetExtent().GetZmax());
     sprintf(lineOutput,formDimOut,sideBottom->GetName().c_str(),
       sideBottom->GetSolid()->GetExtent().GetXmax(),
       sideBottom->GetSolid()->GetExtent().GetYmax(),
       sideBottom->GetSolid()->GetExtent().GetZmax());
     G4cout << lineOutput;
     sprintf(lineOutput,formDimOut,sideVertical->GetName().c_str(),
       sideVertical->GetSolid()->GetExtent().GetXmax(),
       sideVertical->GetSolid()->GetExtent().GetYmax(),
       sideVertical->GetSolid()->GetExtent().GetZmax());
     G4cout << lineOutput;
     G4ThreeVector frameDim(sideBottom->GetSolid()->GetExtent().GetZmax(),
                        2.0 * sideBottom->GetSolid()->GetExtent().GetYmax() +
                        sideVertical->GetSolid()->GetExtent().GetZmax(),
                        sideBottom->GetSolid()->GetExtent().GetXmax());
     G4Box * frameBox = new G4Box("UnistrutFrame",frameDim.x(),
                                   frameDim.y(),frameDim.z());
     G4LogicalVolume * frameVol = new G4LogicalVolume(frameBox,
                            fEnvironmentMaterial,frameBox->GetName());
     G4LogicalVolume * southFrameVol = new G4LogicalVolume(frameBox,
                            fEnvironmentMaterial,"SouthFrame");
     frameVol->SetVisAttributes(att_invis);
     southFrameVol->SetVisAttributes(att_invis);
//
//   Position unistruts inside the frame box
//
     G4ThreeVector strutPos(0.,0.,0.);
     G4RotationMatrix * yxRot = new G4RotationMatrix;
     yxRot->rotateY(CLHEP::halfpi*rad);
     yxRot->rotateX(CLHEP::halfpi*rad);
     strutPos.setY(sideBottomDim.y() - frameDim.y());
     for(int topBot = 0; topBot < 2; topBot++){
       sprintf(lineOutput,formPosOut,sideBottom->GetName().c_str(),
         strutPos.x(),strutPos.y(),strutPos.z());
       strutPos.setY(-strutPos.y());
       G4cout << lineOutput;
       new G4PVPlacement(yRot,strutPos,sideBottom,sideBottom->GetName(),
          frameVol,false,topBot,checkOverlaps);
       new G4PVPlacement(yRot,strutPos,sideBottom,sideBottom->GetName(),
          southFrameVol,false,topBot,checkOverlaps);
     }
     const int nVerts = 5;
     strutPos.setY(0.0);
     for(int leftRight = 0; leftRight < nVerts; leftRight++){
       double xLocal =
         (leftRight - 2) * 0.5 * (frameDim.x() - 2.0 * sideBottomDim.x());
       strutPos.setX(xLocal);
       sprintf(lineOutput,formPosOut,sideVertical->GetName().c_str(),
         strutPos.x(),strutPos.y(),strutPos.z());
       strutPos.setY(-strutPos.y());
       G4cout << lineOutput;
       new G4PVPlacement(yxRot,strutPos,sideVertical,sideVertical->GetName(),
          frameVol,false,leftRight,checkOverlaps);
       new G4PVPlacement(yxRot,strutPos,sideVertical,sideVertical->GetName(),
          southFrameVol,false,leftRight,checkOverlaps);
     }
     if(fUseCartBeamhole){
       const int midBar = 4;
       G4VPhysicalVolume * unistrutPhysVol = southFrameVol->GetDaughter(midBar);
       southFrameVol->RemoveDaughter(unistrutPhysVol);
     }
//
//   Create the cart volume
//   The length of the cart volume needs to be flexible with the brick
//   wrappings.  Actual cart has the side walls extend beyond the base plate.
//
     G4ThreeVector cartDim = sectDim[PLATE];
     cartDim.setY(2.0 * sectDim[PLATE].y() + sectDim[SIDE].y());
     if(frameDim.y() > sectDim[SIDE].y()){
       cartDim.setY(2.0 * sectDim[PLATE].y() + frameDim.y());
     }
     double cartLengthSide = sectDim[SOUTH].z() + sectDim[SIDE].x() +
       frameDim.z();
     double cartLengthBottom = sectDim[SOUTH].z() + sectDim[BOTTOM].z() +
       2.0 * frameDim.z();
     cartDim.setZ(cartLengthSide);
     if(cartLengthBottom > cartLengthSide) cartDim.setZ(cartLengthBottom);
     G4Box * cartBox = new G4Box("MoveableShield",cartDim.x(),
                               cartDim.y(),cartDim.z());
     sprintf(lineOutput,formDimOut,cartBox->GetName().c_str(),
         cartDim.x(),cartDim.y(),cartDim.z());
     G4cout << lineOutput;
//
//   Create the cart void - the space where the cryostat occupies
//
     G4ThreeVector voidDim = cartDim;
     const double collarDepth = 15.0 * cm;
     voidDim.setX(sectDim[BOTTOM].x() - collarDepth);
     voidDim.setY(voidDim.y() -
       2.0 * (sectDim[PLATE].y() + sectDim[BOTTOM].y()) - collarDepth);
     voidDim.setZ(sectDim[BOTTOM].z() - 0.5 * collarDepth);
     G4Box * voidBox = new G4Box("MoveableShieldVoid",voidDim.x(),
                               voidDim.y(),voidDim.z());
     sprintf(lineOutput,formDimOut,voidBox->GetName().c_str(),
         voidDim.x(),voidDim.y(),voidDim.z());
     G4cout << lineOutput;
//
//   Build the shield from the south edge, running north
//
     G4ThreeVector sectPos[nSect];
     sectPos[PLATE] = origin;
     sectPos[PLATE].setY(sectDim[PLATE].y() - cartDim.y());
     sectPos[PLATE].setZ(sectDim[PLATE].z() - cartDim.z());
     sprintf(lineOutput,formPosOut,sectVol[PLATE]->GetName().c_str(),
       sectPos[PLATE].x(),sectPos[PLATE].y(),sectPos[PLATE].z());
     G4cout << lineOutput;
//
     G4ThreeVector outerSouthFramePos = origin;
     outerSouthFramePos.setY(sectPos[PLATE].y() + sectDim[PLATE].y() +
       frameDim.y());
     outerSouthFramePos.setZ(frameDim.z() - cartDim.z());
     sprintf(lineOutput,formPosOut,frameVol->GetName().c_str(),
       outerSouthFramePos.x(),outerSouthFramePos.y(),outerSouthFramePos.z());
     G4cout << lineOutput;
//
     sectPos[SOUTH] = outerSouthFramePos;
     sectPos[SOUTH].setY(sectPos[PLATE].y() + sectDim[PLATE].y() +
       sectDim[SOUTH].y());
     sectPos[SOUTH].setZ(outerSouthFramePos.z() + frameDim.z() +
       sectDim[SOUTH].z());
     sprintf(lineOutput,formPosOut,sectVol[SOUTH]->GetName().c_str(),
       sectPos[SOUTH].x(),sectPos[SOUTH].y(),sectPos[SOUTH].z());
     G4cout << lineOutput;
//
     G4ThreeVector southFramePos = outerSouthFramePos;
     southFramePos.setZ(sectPos[SOUTH].z() + sectDim[SOUTH].z() +
       frameDim.z());
     sprintf(lineOutput,formPosOut,frameVol->GetName().c_str(),
       southFramePos.x(),southFramePos.y(),southFramePos.z());
     G4cout << lineOutput;
//
     sectPos[BOTTOM] = origin;
     sectPos[BOTTOM].setY(sectPos[PLATE].y() + sectDim[PLATE].y() +
       sectDim[BOTTOM].y());
     sectPos[BOTTOM].setZ(cartDim.z() - sectDim[BOTTOM].z());
       sprintf(lineOutput,formPosOut,sectVol[BOTTOM]->GetName().c_str(),
         sectPos[BOTTOM].x(),sectPos[BOTTOM].y(),sectPos[BOTTOM].z());
       G4cout << lineOutput;
//
     G4ThreeVector sideFramePos[2];
     G4ThreeVector sideWallPos[2];
     for(int side = 0; side < 2; side++){
       sideFramePos[side] = origin;
       sideFramePos[side].setX(sectPos[BOTTOM].x()
         + (2 * side - 1) * ( sectDim[BOTTOM].x() + frameDim.z()));
       sideFramePos[side].setY(sectPos[PLATE].y() + sectDim[PLATE].y() +
         frameDim.y());
       sideFramePos[side].setZ(cartDim.z() - sectDim[SIDE].x());
       sprintf(lineOutput,formPosOut,frameVol->GetName().c_str(),
         sideFramePos[side].x(),sideFramePos[side].y(),sideFramePos[side].z());
       G4cout << lineOutput;
       sideWallPos[side] = origin;
       sideWallPos[side].setX(sideFramePos[side].x()
         + (2 * side - 1) * ( frameDim.z() + sectDim[SIDE].z()));
       sideWallPos[side].setY(sectPos[PLATE].y() + sectDim[PLATE].y() +
         sectDim[SIDE].y());
       sideWallPos[side].setZ(cartDim.z() - sectDim[SIDE].x());
       sprintf(lineOutput,formPosOut,sectVol[SIDE]->GetName().c_str(),
         sideWallPos[side].x(),sideWallPos[side].y(),sideWallPos[side].z());
       G4cout << lineOutput;
     }
//
//   Eye candy.  Frames on the outside.
//
     G4ThreeVector outerSideFramePos[2];
     for(int side = 0; side < 2; side++){
       outerSideFramePos[side] = sideFramePos[side];
       outerSideFramePos[side].setX(sideWallPos[side].x()
         + (2 * side - 1) * (frameDim.z() + sectDim[SIDE].z()));
       sprintf(lineOutput,formPosOut,frameVol->GetName().c_str(),
         outerSideFramePos[side].x(),outerSideFramePos[side].y(),
	 outerSideFramePos[side].z());
       G4cout << lineOutput;
     }
//
     G4ThreeVector voidPos = origin;
     voidPos.setY(2.0 * (sectDim[PLATE].y() + sectDim[BOTTOM].y()) -
       cartDim.y() + voidDim.y() + collarDepth);
     voidPos.setZ(cartDim.z() - voidDim.z());
     sprintf(lineOutput,formPosOut,voidBox->GetName().c_str(),
       voidPos.x(),voidPos.y(),voidPos.z());
     G4cout << lineOutput;
//
//   Create the cart volume out of the void subtracted from the cartbox.
//
     G4SubtractionSolid * cartWithVoid =
      new G4SubtractionSolid("CartShield",cartBox,voidBox,0,voidPos);
     cartWithVoid->DumpInfo();
     G4LogicalVolume * cartVol = new G4LogicalVolume(cartWithVoid,
                            fEnvironmentMaterial,cartWithVoid->GetName());
     cartVol->SetVisAttributes(att_invis);
//
//   Now place all the walls and frames
//
     G4RotationMatrix * sectRot[nSect] = {0,0,0,yRot};
     for(int section = 0; section < nSect; section++){
       if(section != SIDE){
         new G4PVPlacement(sectRot[section],sectPos[section],sectVol[section],
           sectVol[section]->GetName(),cartVol,false,0,checkOverlaps);
       }
       else{
         for(int side = 0; side < 2; side++){
           new G4PVPlacement(sectRot[section],sideWallPos[side],
	     sectVol[section],
             sectVol[section]->GetName(),cartVol,false,side,checkOverlaps);
         }
       }
     }
     for(int side = 0; side < 2; side++){
       new G4PVPlacement(sectRot[SIDE],sideFramePos[side],
	 frameVol,frameVol->GetName(),cartVol,false,2 * side,checkOverlaps);
       new G4PVPlacement(sectRot[SIDE],outerSideFramePos[side],
	 frameVol,frameVol->GetName(),cartVol,false,2 * side + 1,
	 checkOverlaps);
     }
     new G4PVPlacement(sectRot[SOUTH],southFramePos,
       southFrameVol,southFrameVol->GetName(),cartVol,false,0,checkOverlaps);
     new G4PVPlacement(sectRot[SOUTH],outerSouthFramePos,
       southFrameVol,southFrameVol->GetName(),cartVol,false,1,checkOverlaps);
//
     G4cout << G4endl;
     return cartVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume * IronFilterDetectorConstruction::PositionCryostat(){
//
//  Positions the cryostat.
//
     G4cout << G4endl << "In PositionCryostat..." << G4endl;
     G4bool checkOverlaps = true;
     G4VPhysicalVolume * cryostatPhys = 0;
//
     G4LogicalVolume * cryostatVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("OVC");
     G4VPhysicalVolume * shieldPhys =
       G4PhysicalVolumeStore::GetInstance()->GetVolume("DDShield");
//
     if(cryostatVol && shieldPhys){
       G4LogicalVolume * interiorVol =
         G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
       G4LogicalVolume * shieldVol = shieldPhys->GetLogicalVolume();
       G4VPhysicalVolume * nSourcePhys =
         G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource");
       G4ThreeVector sourcePos = LocateDaughter(interiorVol,nSourcePhys);
       G4ThreeVector shieldPos = LocateDaughter(interiorVol,shieldPhys);
       G4ThreeVector cryostatPos = sourcePos;
       cryostatPos.setY(fCryostatHeight +
                     cryostatVol->GetSolid()->GetExtent().GetZmax() +
                     interiorVol->GetSolid()->GetExtent().GetYmin());
       cryostatPos.setZ(shieldPos.z() +
                        shieldVol->GetSolid()->GetExtent().GetZmin() - 50.8*cm);
       sprintf(lineOutput,formPosOut,cryostatVol->GetName().c_str(),
               cryostatPos.x(),cryostatPos.y(),cryostatPos.z());
       G4cout << lineOutput;
       G4RotationMatrix * xRot = new G4RotationMatrix;
       xRot->rotateX(CLHEP::halfpi*rad);
       cryostatPhys = new G4PVPlacement(xRot,cryostatPos,cryostatVol,
         cryostatVol->GetName(),interiorVol,false,0,checkOverlaps);
     }
     return cryostatPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume * IronFilterDetectorConstruction::PositionSWallPlug(){
//
//  Positions the base plate and walls of the moveable cart.
//
     G4cout << G4endl << "In PositionSWallPlug..." << G4endl;
     G4bool checkOverlaps = true;
     G4VPhysicalVolume * wallPlugPhys = 0;
//
     G4LogicalVolume * plugShieldVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("WallPlug");
     G4VPhysicalVolume * shieldPhys =
       G4PhysicalVolumeStore::GetInstance()->GetVolume("DDShield");
//
     if(plugShieldVol && shieldPhys){
       G4LogicalVolume * interiorVol =
         G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
       G4LogicalVolume * shieldVol = shieldPhys->GetLogicalVolume();
       G4VPhysicalVolume * nSourcePhys =
         G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource");
       G4ThreeVector plugDim(plugShieldVol->GetSolid()->GetExtent().GetXmax(),
                             plugShieldVol->GetSolid()->GetExtent().GetYmax(),
                             plugShieldVol->GetSolid()->GetExtent().GetZmax());
       G4ThreeVector shieldExtentMin(shieldVol->GetSolid()->GetExtent().GetXmin(),
                                     shieldVol->GetSolid()->GetExtent().GetYmin(),
                                     shieldVol->GetSolid()->GetExtent().GetZmin());
       G4ThreeVector sourcePos = LocateDaughter(interiorVol,nSourcePhys);
       G4ThreeVector shieldPos = LocateDaughter(interiorVol,shieldPhys);
       G4ThreeVector plugPos = sourcePos;
       plugPos.setZ(shieldPos.z() + shieldExtentMin.z() - plugDim.z());
       sprintf(lineOutput,formPosOut,plugShieldVol->GetName().c_str(),
               plugPos.x(),plugPos.y(),plugPos.z());
       G4cout << lineOutput;
       wallPlugPhys = new G4PVPlacement(0,plugPos,plugShieldVol,
         plugShieldVol->GetName(),interiorVol,false,0,checkOverlaps);
     }
     return wallPlugPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume * IronFilterDetectorConstruction::PositionLeanShield(){
//
//  Positions the full shield into the clean room.
//
     G4cout << G4endl << "In PositionLeanShield..." << G4endl;
     G4bool checkOverlaps = true;
     G4LogicalVolume * interiorVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
     G4LogicalVolume * shieldVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("DDShield");
     G4VPhysicalVolume * shieldPhys = 0;
//
     G4VPhysicalVolume * basePlate =
       G4PhysicalVolumeStore::GetInstance()->GetVolume("Base Plate");
     G4LogicalVolume * basePlateEnv = basePlate->GetLogicalVolume();
     G4ThreeVector baseExtentMax(basePlateEnv->GetSolid()->GetExtent().GetXmax(),
                                 basePlateEnv->GetSolid()->GetExtent().GetYmax(),
                                 basePlateEnv->GetSolid()->GetExtent().GetZmax());
     G4ThreeVector interiorExtent(interiorVol->GetSolid()->GetExtent().GetXmax(),
                                  interiorVol->GetSolid()->GetExtent().GetYmax(),
                                  interiorVol->GetSolid()->GetExtent().GetZmax());
     sprintf(lineOutput,formDimOut,basePlateEnv->GetName().c_str(),
       baseExtentMax.x(),baseExtentMax.y(),baseExtentMax.z());
     G4cout << lineOutput;
// From docdb 4374, actual measurement of the plate top:
//  const double basePlateHeight = 65.4*cm;
//  From my cleanroom installation sketch:
//     const double   southFace =  0.5 * env_sizeZ  - 240*cm;
//     const double frameCenter = -0.5 * env_sizeXY + 169*cm;
     double   southFace =  interiorExtent.z()  - 240*cm;
     double frameCenter = -interiorExtent.x() + 169*cm;
//  double shieldBottom =
//    basePlateHeight - 2.0 * basePlateEnv->GetSolid()->GetExtent().GetYmax();
     G4ThreeVector shieldDDPos  =
       G4ThreeVector(frameCenter,
       interiorVol->GetSolid()->GetExtent().GetYmin() +
       shieldVol->GetSolid()->GetExtent().GetYmax(),
       shieldVol->GetSolid()->GetExtent().GetZmax() + southFace);
//
     sprintf(lineOutput,formPosOut,shieldVol->GetName().c_str(),
       shieldDDPos.x(),shieldDDPos.y(),shieldDDPos.z());
     G4cout << lineOutput;
//
     shieldPhys =
       new G4PVPlacement(0,shieldDDPos,shieldVol,shieldVol->GetName(),
         interiorVol,false,0,checkOverlaps);

     return shieldPhys;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume * IronFilterDetectorConstruction::PositionCart(){
//
//  Positions the base plate and walls of the moveable cart.
//
     G4cout << G4endl << "In PositionCart..." << G4endl;
     G4bool checkOverlaps = true;
     G4VPhysicalVolume * cartShieldPhys = 0;
//     G4cout << "   South face of shield at z = "
//            << shieldPos.z() + shieldVol->GetSolid()->GetExtent().GetZmin()
//	    << G4endl;
//
     G4LogicalVolume * cartShieldVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CartShield");
     G4VPhysicalVolume * shieldPhys =
       G4PhysicalVolumeStore::GetInstance()->GetVolume("DDShield");
//
     if(cartShieldVol && shieldPhys){
       G4LogicalVolume * interiorVol =
         G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
       G4LogicalVolume * shieldVol = shieldPhys->GetLogicalVolume();
//
//   Offset the cart plate by the measured difference with the floor.
//
       const double cartOffsetY = 47.6 * cm;
       G4ThreeVector cartShieldPos;
       G4ThreeVector shieldPos = LocateDaughter(interiorVol,shieldPhys);
       cartShieldPos.setX(shieldPos.x());
       cartShieldPos.setY(cartOffsetY +
         interiorVol->GetSolid()->GetExtent().GetYmin() +
         cartShieldVol->GetSolid()->GetExtent().GetYmax());
       cartShieldPos.setZ(shieldPos.z() +
         shieldVol->GetSolid()->GetExtent().GetZmin() -
         cartShieldVol->GetSolid()->GetExtent().GetZmax());
//
//   Offset the cart:
//
       cartShieldPos.setZ(cartShieldPos.z()  + fCartZOffset);
//
       cartShieldPhys = new G4PVPlacement(0,cartShieldPos,cartShieldVol,
         cartShieldVol->GetName(),interiorVol,false,0,checkOverlaps);
//
//   Print the positions of everything
//
       sprintf(lineOutput,formDimOut,(cartShieldVol->GetName()).c_str(),
         cartShieldVol->GetSolid()->GetExtent().GetXmax(),
         cartShieldVol->GetSolid()->GetExtent().GetYmax(),
         cartShieldVol->GetSolid()->GetExtent().GetZmax());
       G4cout << lineOutput;
       sprintf(lineOutput,formPosOut,(cartShieldVol->GetName()).c_str(),
         cartShieldPos.x(),cartShieldPos.y(),cartShieldPos.z());
       G4cout << lineOutput;
       G4cout << G4endl;
     }
     return cartShieldPhys;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume * IronFilterDetectorConstruction::PositionBackingArray(){
//
//  Positions the backing array into the moveable cart.
//
     G4cout << G4endl << "In PositionBackingArray..." << G4endl;
     G4bool checkOverlaps = true;
     G4VPhysicalVolume * backingWallPhys = 0;

//     G4LogicalVolume * cartShieldVol =
//       G4LogicalVolumeStore::GetInstance()->GetVolume("CartShield");
     G4LogicalVolume * backingWallVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("BackingWall");
//     G4VPhysicalVolume * cartShieldPhys =
//         G4PhysicalVolumeStore::GetInstance()->GetVolume("CartShield");
//     if(!cartShieldPhys){
//       G4cout << "Cart must be positioned before backing array" << G4endl;
//       return 0;
//     }
//     if(cartShieldVol && backingWallVol){
     if(backingWallVol){
       G4LogicalVolume * interiorVol =
         G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
       G4VPhysicalVolume * sourcePhys =
         G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource");
//       G4VPhysicalVolume * southFrame =
//         G4PhysicalVolumeStore::GetInstance()->GetVolume("SouthFrame");
//       G4LogicalVolume * southFrameVol = southFrame->GetLogicalVolume();

//       G4ThreeVector backingPos(0.0,0.0,0.0);
       G4ThreeVector nsourcePos = LocateDaughter(interiorVol,sourcePhys);
       G4ThreeVector backingPos = nsourcePos;
       backingPos.setZ(fBackingZposition);
//       backingPos.setY(nsourcePos.y() - cartShieldPhys->GetTranslation().y());
//       backingPos.setZ(southFrame->GetTranslation().z() +
//         southFrameVol->GetSolid()->GetExtent().GetZmax() +
//         backingWallVol->GetSolid()->GetExtent().GetZmax());
       sprintf(lineOutput,formDimOut,"Backing wall misalignment",
            fBackingMisalign.x(),fBackingMisalign.y(),fBackingMisalign.z());
       G4cout << lineOutput;
       backingPos += fBackingMisalign;
//       G4cout << backingWallVol->GetName() << " position in "
//              << cartShieldVol->GetName() << ": " << backingPos << G4endl;
//       backingWallPhys = new G4PVPlacement(0,backingPos,backingWallVol,
//         backingWallVol->GetName(),cartShieldVol,false,0,checkOverlaps);
       backingWallPhys = new G4PVPlacement(0,backingPos,backingWallVol,
         backingWallVol->GetName(),interiorVol,false,0,checkOverlaps);
       LocateDaughter(interiorVol,backingWallPhys);

       G4LogicalVolume * backingFaceVol =
         G4LogicalVolumeStore::GetInstance()->GetVolume("BackingFace");
       if(backingFaceVol){
         G4ThreeVector backingFacePos  = backingPos;
         backingFacePos.setZ(backingPos.z() +
	   backingWallVol->GetSolid()->GetExtent().GetZmax() +
	   backingFaceVol->GetSolid()->GetExtent().GetZmax());
//         G4VPhysicalVolume * backingFacePhys =
//           new G4PVPlacement(0,backingFacePos,backingFaceVol,
//	     backingFaceVol->GetName(),cartShieldVol,false,0,checkOverlaps);
//         G4cout << backingFacePhys->GetName() << "  position in the "
//	        << cartShieldVol->GetName() << ": "
//		<< backingFacePhys->GetTranslation() << G4endl;
         G4VPhysicalVolume * backingFacePhys =
           new G4PVPlacement(0,backingFacePos,backingFaceVol,
	     backingFaceVol->GetName(),interiorVol,false,0,checkOverlaps);
         LocateDaughter(interiorVol,backingFacePhys);
       }
     }
     return backingWallPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume * IronFilterDetectorConstruction::PositionBottomArray(){
//
//  Positions the bottom array into the moveable cart.
//
     G4cout << G4endl << "In PositionBottomArray..." << G4endl;
     G4bool checkOverlaps = true;
     G4VPhysicalVolume * bottomPhys = 0;

     G4LogicalVolume * cartShieldVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CartShield");
     G4LogicalVolume * bottomVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CartBottomArray");
     G4VPhysicalVolume * cartShieldPhys =
         G4PhysicalVolumeStore::GetInstance()->GetVolume("CartShield");
     G4VPhysicalVolume * cartBottom =
       G4PhysicalVolumeStore::GetInstance()->GetVolume("CartBottom");
     if(!cartShieldPhys){
       G4cout << "Cart must be positioned before backing array" << G4endl;
       return 0;
     }
     if(cartShieldVol && bottomVol){
//       G4LogicalVolume * interiorVol =
//         G4LogicalVolumeStore::GetInstance()->GetVolume("Interior");
//       G4VPhysicalVolume * sourcePhys =
//         G4PhysicalVolumeStore::GetInstance()->GetVolume("NSource");
//       G4VPhysicalVolume * southFrame =
//         G4PhysicalVolumeStore::GetInstance()->GetVolume("SouthFrame");
//       G4LogicalVolume * southFrameVol = southFrame->GetLogicalVolume();

       G4ThreeVector cartBottomPos = cartBottom->GetTranslation();
       sprintf(lineOutput,formPosOut,bottomVol->GetName().c_str(),
               cartBottomPos.x(),cartBottomPos.y(),cartBottomPos.z());
       G4cout << lineOutput;
       G4LogicalVolume * cartBottomVol = cartBottom->GetLogicalVolume();
       cartBottomPos.setY(cartBottomPos.y() +
         bottomVol->GetSolid()->GetExtent().GetYmax() +
         cartBottomVol->GetSolid()->GetExtent().GetYmax());
       sprintf(lineOutput,formPosOut,bottomVol->GetName().c_str(),
               cartBottomPos.x(),cartBottomPos.y(),cartBottomPos.z());
       G4cout << lineOutput;
       const int arrayID = 4;
       bottomPhys = new G4PVPlacement(0,cartBottomPos,bottomVol,
         bottomVol->GetName(),cartShieldVol,false,arrayID,checkOverlaps);
     }
     return bottomPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructUnistrut(const double length){
//
//  Construct Unistrut of a given length.
//  Material will be scaled to contain the steel in P1000.
    G4cout << G4endl << "In ConstructUnistrut..." << G4endl;
//
//  Unistrut data from the catalogue:
//
//  Use  inches, because our designers do:
//    const double unistrutWidth    = 41.3 * mm;
    const double unistrutWidth    = 1.625 * 25.4 * mm;
    const double unistrutGauge    = 2.7 * mm;
    const double unistrutLipWidth = 9.5 * mm;
    const double unistrutLipDepth = 7.1 * mm;
    const double unistrutMaterialScale =
      (1.5 * unistrutWidth + unistrutLipWidth + unistrutLipDepth)/
      (1.5 * unistrutWidth);
    const double steelEffThickness = unistrutGauge * unistrutMaterialScale;
//
    G4bool checkOverlaps = true;
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* unistrutMaterial = nistManager->FindOrBuildMaterial("G4_Fe");
    const G4Color greenColor(0.1,1.0,0.1);
    const G4VisAttributes *att_green = new G4VisAttributes(greenColor);
    const G4VisAttributes *att_invis = new G4VisAttributes(false);
//
    G4ThreeVector unistrutDim(0.5 * unistrutWidth,0.5 * unistrutWidth,
                              0.5 * length);
    sprintf(name,"Unistrut_%6.2f",length);
    G4Box * unistrutBox = new G4Box(name,
       unistrutDim.x(),unistrutDim.y(),unistrutDim.z());
    G4LogicalVolume * unistrutVol = new G4LogicalVolume(unistrutBox,
       unistrutMaterial,unistrutBox->GetName());
//    sprintf(lineOutput,formOut,unistrutBox->GetName().c_str(),
//      unistrutDim.x(),unistrutDim.y(),unistrutDim.z());
//    G4cout << lineOutput;
    unistrutVol->SetVisAttributes(att_green);
//
//  The air volume:
//
    G4ThreeVector openingDim(0.5 *  unistrutWidth - steelEffThickness,
                             0.5 * (unistrutWidth - steelEffThickness),
                             0.5 * length);
    G4Box * openingBox = new G4Box("Opening",
       openingDim.x(),openingDim.y(),openingDim.z());
    G4LogicalVolume * openingVol = new G4LogicalVolume(openingBox,
       fEnvironmentMaterial,openingBox->GetName());
    openingVol->SetVisAttributes(att_invis);
//
    G4ThreeVector openingPos(0.0, 0.5 * steelEffThickness,0.0);
//    sprintf(lineOutput,formOut,openingBox->GetName().c_str(),
//      openingDim.x(),openingDim.y(),openingDim.z());
//    G4cout << lineOutput;
//    sprintf(lineOutput,formOut,openingBox->GetName().c_str(),
//      openingPos.x(),openingPos.y(),openingPos.z());
//    G4cout << lineOutput;
    new G4PVPlacement(0,openingPos,openingVol,openingBox->GetName(),
         unistrutVol,false,0,checkOverlaps);
//
    return unistrutVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBackingFace(){
//
//  Construct a slab detector as a sort of backing array.
//
     G4cout << G4endl << "In ConstructBackingFace..." << G4endl;
     G4LogicalVolume * backingWall =
       G4LogicalVolumeStore::GetInstance()->GetVolume("BackingWall");
     G4ThreeVector backingWallDim(backingWall->GetSolid()->GetExtent().GetXmax(),
                                  backingWall->GetSolid()->GetExtent().GetYmax(),
                                  backingWall->GetSolid()->GetExtent().GetZmax());
     G4NistManager* nistManager = G4NistManager::Instance();
     G4Material* faceMaterial =
       nistManager->FindOrBuildMaterial(fBackingFaceMater);

     G4Box * backingFaceBox = new G4Box("BackingFace",
       backingWallDim.x(),backingWallDim.y(),fBackingFaceThick);
     G4LogicalVolume * backingFaceVol = new G4LogicalVolume(backingFaceBox,
       faceMaterial,backingFaceBox->GetName());
     sprintf(lineOutput,formDimOut,backingFaceVol->GetName().c_str(),
        backingFaceBox->GetXHalfLength(),backingFaceBox->GetYHalfLength(),
	backingFaceBox->GetZHalfLength());
     G4cout << lineOutput;

     G4VisAttributes *att_backingFace = new G4VisAttributes(false);
     if(!(fBackingFaceMater == "G4_AIR")){
       G4Color green(0.0,1.0,0.0);
       *att_backingFace = new G4VisAttributes(green);
     }
     backingFaceVol->SetVisAttributes(att_backingFace);

     G4cout << backingFaceVol->GetName() << " is made of "
            << faceMaterial->GetName() << G4endl;

     return backingFaceVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBackingArray(){
//
//  Construct a backing arrays.  Different types are defined.
//
    G4bool checkOverlaps = true;
    G4cout << G4endl << "In ConstructBackingArray..." << G4endl;
    G4LogicalVolume * arrayVol = 0;
//    G4ThreeVector arrayVolDim(arrayVol->GetSolid()->GetExtent().GetXmax(),
//                              arrayVol->GetSolid()->GetExtent().GetYmax(),
//                              arrayVol->GetSolid()->GetExtent().GetZmax());
    if(fBackingType == 0){
      arrayVol = ConstructBackingWall();
    }
    else{
      int detectorNumber = 0;
      G4LogicalVolume * beamDetVol  = ConstructBeamDetector();
//      G4LogicalVolume * bottomDetVol  = ConstructBottomDetector();
      G4ThreeVector beamDetDim(beamDetVol->GetSolid()->GetExtent().GetXmax(),
                               beamDetVol->GetSolid()->GetExtent().GetYmax(),
                               beamDetVol->GetSolid()->GetExtent().GetZmax());
      G4LogicalVolume * scatDetVol = 0;
      if(fBackingType == 1){
        scatDetVol = ConstructScatDetector();
      }
      if(fBackingType == 2){
        scatDetVol = ConstructScatBarDetector();
//        scatDetVol = ConstructScatDetector();
      }
      G4ThreeVector beamDetPos(0.0,0.0,0.0);
      sprintf(lineOutput,formDimOut,beamDetVol->GetName().c_str(),
        beamDetDim.x(),beamDetDim.y(),beamDetDim.z());
      G4cout << lineOutput;
      G4ThreeVector scatDetDim(scatDetVol->GetSolid()->GetExtent().GetXmax(),
                               scatDetVol->GetSolid()->GetExtent().GetYmax(),
                               scatDetVol->GetSolid()->GetExtent().GetZmax());
      sprintf(lineOutput,formDimOut,scatDetVol->GetName().c_str(),
        scatDetDim.x(),scatDetDim.y(),scatDetDim.z());
      G4cout << lineOutput;
//
//    Create the "backing wall" with 5 cm in the back for Unistrut and brackets.
//
      G4ThreeVector backingWallDim = scatDetDim;
      backingWallDim.setZ(scatDetDim.z() + 2.5 * cm);
      G4Box * backingWallBox = new G4Box("BackingWall",
       backingWallDim.x(),backingWallDim.y(),backingWallDim.z());
      sprintf(lineOutput,formDimOut,backingWallBox->GetName().c_str(),
        backingWallDim.x(),backingWallDim.y(),backingWallDim.z());
      G4cout << lineOutput;
      arrayVol = new G4LogicalVolume(backingWallBox,fEnvironmentMaterial,
                                     backingWallBox->GetName());
      const G4VisAttributes *att_invis = new G4VisAttributes(false);
      arrayVol->SetVisAttributes(att_invis);
//
//    Position the full array into the "wall", towards the front.
//
      G4ThreeVector barrayDetPos(0.0,0.0,0.0);
      const double airGap = 0.1 * mm;
      double zLocal =   arrayVol->GetSolid()->GetExtent().GetZmax() +
                      scatDetVol->GetSolid()->GetExtent().GetZmin() -
                      airGap;
      barrayDetPos.setZ(zLocal);
      sprintf(lineOutput,formPosOut,beamDetVol->GetName().c_str(),
        beamDetPos.x(),beamDetPos.y(),beamDetPos.z());
      G4cout << lineOutput;
      sprintf(lineOutput,formPosOut,scatDetVol->GetName().c_str(),
        barrayDetPos.x(),barrayDetPos.y(),barrayDetPos.z());
      G4cout << lineOutput;
//
      new G4PVPlacement(0,beamDetPos,beamDetVol,beamDetVol->GetName(),
        scatDetVol,false,detectorNumber++,checkOverlaps);
      new G4PVPlacement(0,barrayDetPos,scatDetVol,scatDetVol->GetName(),
        arrayVol,false,detectorNumber++,checkOverlaps);
    }

    DumpFamily(arrayVol,2);
    return arrayVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBeamDetector(){
//
//  Construct a backing arrays.  Different types are defined.
//
     G4cout << G4endl << "In ConstructBeamDetector..." << G4endl;
//
//   Begin with some hard-coded dimensions that vary later
//
    G4bool checkOverlaps = true;
    const int DET_PER_LAYER = 8;
    const double wrappingHalfThick = 0.05 * cm;
    const double gapHalfThick = 0.05 * cm;
    const G4ThreeVector wrapDim(fBeamScintDim.x() + wrappingHalfThick,
                                fBeamScintDim.y() + wrappingHalfThick,
                                fBeamScintDim.z() + wrappingHalfThick);
    const G4ThreeVector detectorDim(wrapDim.x() + gapHalfThick,
                                    wrapDim.y() + gapHalfThick,
                                    wrapDim.z() + gapHalfThick);
    const G4ThreeVector origin(0.0,0.0,0.0);
//
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* detMaterial =
      nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Box * scintillatorBox = new G4Box("Scintillator",
       fBeamScintDim.x(),fBeamScintDim.y(),fBeamScintDim.z());
    G4Box * wrapBox = new G4Box("ScintillatorWrap",
       wrapDim.x(),wrapDim.y(),wrapDim.z());
    G4Box * detectorBox = new G4Box("BeamDetector",
       detectorDim.x(),detectorDim.y(),detectorDim.z());
//
    fBeamScintillator = new G4LogicalVolume(scintillatorBox,
       detMaterial,scintillatorBox->GetName());
    G4LogicalVolume * wrapVol = new G4LogicalVolume(wrapBox,
       detMaterial,wrapBox->GetName());
    G4LogicalVolume * detectorVol = new G4LogicalVolume(detectorBox,
       fEnvironmentMaterial,detectorBox->GetName());
//
    sprintf(lineOutput,formDimOut,fBeamScintillator->GetName().c_str(),
      fBeamScintDim.x(),fBeamScintDim.y(),fBeamScintDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,wrapVol->GetName().c_str(),
      wrapDim.x(),wrapDim.y(),wrapDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,detectorVol->GetName().c_str(),
      detectorDim.x(),detectorDim.y(),detectorDim.z());
    G4cout << lineOutput;

    new G4PVPlacement(0,origin,fBeamScintillator,"BeamScintillator",
      wrapVol,false,0,checkOverlaps);
    new G4PVPlacement(0,origin,wrapVol,wrapVol->GetName(),
      detectorVol,false,0,checkOverlaps);
//
    G4ThreeVector planeDim(DET_PER_LAYER * detectorDim.x(),
      detectorDim.y(),detectorDim.z());
    if(planeDim.x() < planeDim.y()) planeDim.setX(planeDim.y());
    G4Box * planeBox = new G4Box("DetectorPlane",
       planeDim.x(),planeDim.y(),planeDim.z());
    G4LogicalVolume * planeVol = new G4LogicalVolume(planeBox,
       fEnvironmentMaterial,planeBox->GetName());
    sprintf(lineOutput,formDimOut,planeVol->GetName().c_str(),
      planeDim.x(),planeDim.y(),planeDim.z());
    G4cout << lineOutput;
//
    const G4Color  blueColor(0.0,0.0,0.8);
    const G4Color blackColor(0.0,0.0,0.0);
    const G4VisAttributes  *att_blue = new G4VisAttributes(blueColor);
    const G4VisAttributes *att_black = new G4VisAttributes(blackColor);
    const G4VisAttributes *clear = new G4VisAttributes(false);
    fBeamScintillator->SetVisAttributes(att_blue);
    wrapVol->SetVisAttributes(att_black);
    detectorVol->SetVisAttributes(clear);

    G4ThreeVector detPos = origin;
    G4cout <<"**********************************************************************************"<<G4endl;
    for(int det = 0; det < DET_PER_LAYER; det++){
      double xLocal =
        (2 * det + 1 - DET_PER_LAYER) * detectorBox->GetXHalfLength();
      detPos.setX(xLocal);
      sprintf(name,"%s_%i",detectorVol->GetName().c_str(),det);
      sprintf(lineOutput,formPosOut,name,detPos.x(),detPos.y(),detPos.z());
      G4cout << lineOutput;
      new G4PVPlacement(0,detPos,detectorVol,name,
        planeVol,false,det,checkOverlaps);
    }
    G4cout <<"**********************************************************************************"<<G4endl;
//
    G4RotationMatrix * zRot = new G4RotationMatrix;
    zRot->rotateZ(-CLHEP::halfpi*rad);
    G4ThreeVector arrayDim(planeDim.x(),planeDim.y(),2.0 * planeDim.z());
    if(planeDim.x() > planeDim.y()) arrayDim.setY(planeDim.x());
    G4Box * arrayBox = new G4Box("BeamArray",
       arrayDim.x(),arrayDim.y(),arrayDim.z());
    G4LogicalVolume * arrayVol = new G4LogicalVolume(arrayBox,
       fEnvironmentMaterial,arrayBox->GetName());
    sprintf(lineOutput,formDimOut,arrayVol->GetName().c_str(),
      arrayDim.x(),arrayDim.y(),arrayDim.z());
    G4cout << lineOutput;
//
    G4ThreeVector planePos = origin;
    G4RotationMatrix * planeRot[NUM_BEAM_LAYERS] = {0,zRot};
    for(int layer = 0; layer < NUM_BEAM_LAYERS; layer++){
      double zLocal = (2 * layer + 1) * planeBox->GetZHalfLength() -
        arrayBox->GetZHalfLength();
      planePos.setZ(zLocal);
      sprintf(name,"%s_%i",planeVol->GetName().c_str(),layer);
      sprintf(lineOutput,formPosOut,name,
        planePos.x(),planePos.y(),planePos.z());
      G4cout << lineOutput;
//      new G4PVPlacement(planeRot[layer],planePos,planeVol,planeVol->GetName(),
//        arrayVol,false,plane,checkOverlaps);
      new G4PVPlacement(planeRot[layer],planePos,planeVol,name,
        arrayVol,false,layer,checkOverlaps);
    }
    planeVol->SetVisAttributes(clear);
    arrayVol->SetVisAttributes(clear);

    return arrayVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructDumpDetector(){
//
//  Construct a dump array.  Different types are defined.
//
    G4cout << G4endl << "In ConstructDumpDetector..." << G4endl;
    G4bool checkOverlaps = true;
    const G4VisAttributes *clear = new G4VisAttributes(false);
//
    G4LogicalVolume * beamDetVol =
      G4LogicalVolumeStore::GetInstance()->GetVolume("BeamArray");
    G4LogicalVolume * scatDetVol = ConstructDumpScatDetector();
    G4ThreeVector scatDetDim(scatDetVol->GetSolid()->GetExtent().GetXmax(),
                             scatDetVol->GetSolid()->GetExtent().GetYmax(),
                             scatDetVol->GetSolid()->GetExtent().GetZmax());
//
    int detectorNumber = 2;
    G4ThreeVector beamDetPos(0.0,0.0,0.0);
    G4String beamName = "Dump" + beamDetVol->GetName();
    new G4PVPlacement(0,beamDetPos,beamDetVol,beamName,
      scatDetVol,false,detectorNumber++,checkOverlaps);
//
    const double airGap = 0.1 * mm;
    G4ThreeVector arrayVolDim(scatDetDim.x() + airGap,
                              scatDetDim.y() + airGap,
			      scatDetDim.z() + airGap);
    G4Box * arrayBox = new G4Box("DumpArray",
      arrayVolDim.x(),arrayVolDim.y(),arrayVolDim.z());
    G4LogicalVolume * arrayVol = new G4LogicalVolume(arrayBox,
      fEnvironmentMaterial,arrayBox->GetName());
    arrayVol->SetVisAttributes(clear);
//    sprintf(lineOutput,formDimOut,arrayVol->GetName().c_str(),
//      arrayVolDim.x(),arrayVolDim.y(),arrayVolDim.z());
//    G4cout << lineOutput;
//
    double zLocal =   arrayVol->GetSolid()->GetExtent().GetZmax() +
                    scatDetVol->GetSolid()->GetExtent().GetZmin() -
                    airGap;
    beamDetPos.setZ(zLocal);
    sprintf(lineOutput,formPosOut,scatDetVol->GetName().c_str(),
      beamDetPos.x(),beamDetPos.y(),beamDetPos.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,scatDetVol->GetName().c_str(),
      scatDetDim.x(),scatDetDim.y(),scatDetDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,arrayVol->GetName().c_str(),
      arrayVolDim.x(),arrayVolDim.y(),arrayVolDim.z());
    G4cout << lineOutput;
    new G4PVPlacement(0,beamDetPos,scatDetVol,scatDetVol->GetName(),
      arrayVol,false,detectorNumber++,checkOverlaps);
    DumpFamily(arrayVol,2);
//
    return arrayVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructDumpScatDetector(){
//
//  Construct a dump array.  Different types are defined.
//
     G4cout << G4endl << "In ConstructDumpScatDetector..." << G4endl;
//
//   Begin with some hard-coded dimensions that vary later
//
    G4bool checkOverlaps = true;
//
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* detMaterial =
      nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
//
    const double wrappingHalfThick = 0.05 * cm;
    const double gapHalfThick = 0.05 * cm;
    const double endClearance = 2.0 * cm;
    const G4ThreeVector scintDim = {20.0 * cm, 1.0 * cm, 1.0 * cm};
    G4ThreeVector wrapDim = scintDim;
    wrapDim.setZ(0.5 * fScatScintDim.z() + wrappingHalfThick);
    G4ThreeVector detDim = wrapDim;
    detDim.setZ(wrapDim.z() + gapHalfThick);
    G4LogicalVolume * detectorVol[MAX_DUMP_RINGS];
    const G4Color  blueColor(0.0,0.0,0.8);
    const G4Color blackColor(0.0,0.0,0.0);
    const G4VisAttributes  *att_blue = new G4VisAttributes(blueColor);
    const G4VisAttributes *att_black = new G4VisAttributes(blackColor);
    const G4VisAttributes *clear = new G4VisAttributes(false);
//
//  Create several different counters
//
    const G4ThreeVector origin(0.0,0.0,0.0);
    G4Tubs * scintTubs[MAX_DUMP_RINGS];
    G4Tubs * wrapTubs[MAX_DUMP_RINGS];
    G4Tubs * detTubs[MAX_DUMP_RINGS];
    double innerRad = 12.6 * cm;
    for(int ring = 0; ring < MAX_DUMP_RINGS; ring++){
      double innerScint = innerRad;
      double outerScint = innerScint + scintDim.y();
      double avgRad = 0.5 * (innerScint + outerScint);
      double lowScintPhi = 2.0 * endClearance/(innerScint + outerScint);
      double minLowPhi =
        CLHEP::halfpi*rad - 0.5 * scintDim.x()/avgRad;
      if(minLowPhi > lowScintPhi) lowScintPhi = minLowPhi;
      double deltaPhi = CLHEP::pi*rad - 2.0 * lowScintPhi;
      sprintf(name,"DumpScatScintillator_%i",ring);
      scintTubs[ring] = new G4Tubs(name,
       innerScint,outerScint,0.5 * scintDim.z(),lowScintPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,scintTubs[ring]->GetName().c_str(),
	scintTubs[ring]->GetInnerRadius(),scintTubs[ring]->GetOuterRadius(),
	scintTubs[ring]->GetZHalfLength(),
	scintTubs[ring]->GetStartPhiAngle(),scintTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      double innerWrap = innerScint - wrappingHalfThick;
      double outerWrap = outerScint + wrappingHalfThick;
      double lowPhi = lowScintPhi - wrappingHalfThick/(innerWrap + outerWrap);
      deltaPhi = CLHEP::pi*rad - 2.0 * lowPhi;
      sprintf(name,"WrapRing_%i",ring);
      wrapTubs[ring] = new G4Tubs(name,innerWrap,outerWrap,
        wrapDim.z(),lowPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,wrapTubs[ring]->GetName().c_str(),
	wrapTubs[ring]->GetInnerRadius(),wrapTubs[ring]->GetOuterRadius(),
	wrapTubs[ring]->GetZHalfLength(),
	wrapTubs[ring]->GetStartPhiAngle(),wrapTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      double innerDet  = innerWrap - gapHalfThick;
      double outerDet  = outerWrap + gapHalfThick;
      lowPhi = lowScintPhi - gapHalfThick/(innerDet + outerDet);
      deltaPhi = CLHEP::pi*rad - 2.0 * lowPhi;
      sprintf(name,"DetRing_%i",ring);
      detTubs[ring] = new G4Tubs(name,innerDet,outerDet,
        detDim.z(),lowPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,detTubs[ring]->GetName().c_str(),
	detTubs[ring]->GetInnerRadius(),detTubs[ring]->GetOuterRadius(),
	detTubs[ring]->GetZHalfLength(),
	detTubs[ring]->GetStartPhiAngle(),detTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      fDumpScintillator[ring] =
        new G4LogicalVolume(scintTubs[ring],
         detMaterial,scintTubs[ring]->GetName());
      G4LogicalVolume * wrapVol = new G4LogicalVolume(wrapTubs[ring],
         detMaterial,wrapTubs[ring]->GetName());
      detectorVol[ring] = new G4LogicalVolume(detTubs[ring],
         fEnvironmentMaterial,detTubs[ring]->GetName());
      new G4PVPlacement(0,origin,fDumpScintillator[ring],
        scintTubs[ring]->GetName(),wrapVol,false,0,checkOverlaps);
      new G4PVPlacement(0,origin,wrapVol,wrapTubs[ring]->GetName(),
        detectorVol[ring],false,0,checkOverlaps);
//
      fDumpScintillator[ring]->SetVisAttributes(att_blue);
      wrapVol->SetVisAttributes(att_black);
      detectorVol[ring]->SetVisAttributes(clear);
//
      innerRad = outerDet + fScatScintGap + wrappingHalfThick +
                 gapHalfThick;
    }
//
//   Place the rings into a "plane" box.
//   Awkward, but allows the hits for the beam detector to be used.
//
    G4Tubs * scatPlaneTubs = new G4Tubs(*detTubs[0]);
    scatPlaneTubs->SetName("DumpScatterPlane");
    scatPlaneTubs->SetOuterRadius(detTubs[MAX_DUMP_RINGS - 1]->GetOuterRadius());
    scatPlaneTubs->DumpInfo();
    G4LogicalVolume * planeVol = new G4LogicalVolume(scatPlaneTubs,
         fEnvironmentMaterial,scatPlaneTubs->GetName());
    planeVol->SetVisAttributes(clear);
//
//  Position the rings into the plane box.
//
    G4ThreeVector planePos = origin;
    for(int ring = 0; ring < MAX_DUMP_RINGS; ring++){
      new G4PVPlacement(0,origin,detectorVol[ring],detectorVol[ring]->GetName(),
        planeVol,false,ring,checkOverlaps);
    }
//
//  Now create the overall volume of the backing array.
//
    G4ThreeVector scatArrayDim(detTubs[MAX_DUMP_RINGS - 1]->GetOuterRadius(),
     detTubs[MAX_DUMP_RINGS - 1]->GetOuterRadius(),
     detTubs[MAX_DUMP_RINGS - 1]->GetZHalfLength());
    G4Box * scatArrayBox = new G4Box("DumpScatterArray",
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    sprintf(lineOutput,formDimOut,scatArrayBox->GetName().c_str(),
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    G4cout << lineOutput;
    G4LogicalVolume * arrayVol = new G4LogicalVolume(scatArrayBox,
         fEnvironmentMaterial,scatArrayBox->GetName());
    arrayVol->SetVisAttributes(clear);
//
//  Place two planes of ring detectors into the overall volume.
//
    G4RotationMatrix * zRot = new G4RotationMatrix;
    zRot->rotateZ(CLHEP::pi*rad);
    G4RotationMatrix * planeRot[NUM_SCATTER_LAYERS] = {0,zRot};
    for(int plane = 0; plane < NUM_SCATTER_LAYERS; plane++){
      new G4PVPlacement(planeRot[plane],origin,planeVol,planeVol->GetName(),
        arrayVol,false,plane,checkOverlaps);
    }
//
    DumpFamily(arrayVol,2);
    return arrayVol;
//    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructScatDetector(){
//
//  Construct a backing arrays.  Different types are defined.
//
     G4cout << G4endl << "In ConstructScatDetector..." << G4endl;
//
//   Begin with some hard-coded dimensions that vary later
//   Geometry in G4ThreeVector fScatScintDim, passed by command
//   fScatScintDim.x() - maximum length of a counter
//   fScatScintDim.y() - radial thickness of a counter
//   fScatScintDim.z() - the absorption thickness of a counter
//
    G4bool checkOverlaps = true;
//
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* detMaterial =
      nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
//
    const double wrappingHalfThick = 0.05 * cm;
    const double gapHalfThick = 0.05 * cm; // Minimum gap between detectors
    const double endClearance = 2.0 * cm;
    G4ThreeVector wrapDim = fScatScintDim;
    wrapDim.setZ(0.5 * fScatScintDim.z() + wrappingHalfThick);
    G4ThreeVector detDim = wrapDim;
    detDim.setZ(wrapDim.z() + gapHalfThick);
    G4LogicalVolume * beamDetVol =
      G4LogicalVolumeStore::GetInstance()->GetVolume("BeamArray");
    if(beamDetVol){
      double zThick = beamDetVol->GetSolid()->GetExtent().GetZmax();
      if(zThick > detDim.z()) detDim.setZ(zThick);
    }
    const G4ThreeVector origin(0.0,0.0,0.0);

    G4LogicalVolume * detVol[MAX_SCATTER_COUNTERS];
    const G4Color  blueColor(0.0,0.0,0.8);
    const G4Color blackColor(0.0,0.0,0.0);
    const G4VisAttributes  *att_blue = new G4VisAttributes(blueColor);
    const G4VisAttributes *att_black = new G4VisAttributes(blackColor);
    const G4VisAttributes *clear = new G4VisAttributes(false);
//
    G4Tubs * scintTubs[MAX_SCATTER_COUNTERS];
    G4Tubs * wrapTubs[MAX_SCATTER_COUNTERS];
    G4Tubs * detTubs[MAX_SCATTER_COUNTERS];
    double innerRad = fScatMinRadius;
    double maxWidth = 0.0;
    for(int ring = 0; ring < fNumScatScint; ring++){
      double innerScint = innerRad;
      double outerScint = innerScint + fScatScintDim.y();
      double avgRad = 0.5 * (innerScint + outerScint);
      double lowScintPhi = 2.0 * endClearance/(innerScint + outerScint);
      double minLowPhi =
        CLHEP::halfpi*rad - 0.5 * fScatScintDim.x()/avgRad;
      if(minLowPhi > lowScintPhi) lowScintPhi = minLowPhi;
      double deltaPhi = CLHEP::pi*rad - 2.0 * lowScintPhi;
      sprintf(name,"ScatScintillator_%i",ring);
      scintTubs[ring] = new G4Tubs(name,
       innerScint,outerScint,0.5 * fScatScintDim.z(),lowScintPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,scintTubs[ring]->GetName().c_str(),
	scintTubs[ring]->GetInnerRadius(),scintTubs[ring]->GetOuterRadius(),
	scintTubs[ring]->GetZHalfLength(),
	scintTubs[ring]->GetStartPhiAngle(),scintTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      double innerWrap = innerScint - wrappingHalfThick;
      double outerWrap = outerScint + wrappingHalfThick;
      double lowPhi = lowScintPhi - wrappingHalfThick/(innerWrap + outerWrap);
      deltaPhi = CLHEP::pi*rad - 2.0 * lowPhi;
      sprintf(name,"WrapRing_%i",ring);
      wrapTubs[ring] = new G4Tubs(name,innerWrap,outerWrap,
        wrapDim.z(),lowPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,wrapTubs[ring]->GetName().c_str(),
	wrapTubs[ring]->GetInnerRadius(),wrapTubs[ring]->GetOuterRadius(),
	wrapTubs[ring]->GetZHalfLength(),
	wrapTubs[ring]->GetStartPhiAngle(),wrapTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      double innerDet  = innerWrap - gapHalfThick;
      double outerDet  = outerWrap + gapHalfThick;
      lowPhi = lowScintPhi - gapHalfThick/(innerDet + outerDet);
      deltaPhi = CLHEP::pi*rad - 2.0 * lowPhi;
      sprintf(name,"DetRing_%i",ring);
      detTubs[ring] = new G4Tubs(name,innerDet,outerDet,
        detDim.z(),lowPhi,deltaPhi);
      sprintf(lineOutput,formTubsOut,detTubs[ring]->GetName().c_str(),
	detTubs[ring]->GetInnerRadius(),detTubs[ring]->GetOuterRadius(),
	detTubs[ring]->GetZHalfLength(),
	detTubs[ring]->GetStartPhiAngle(),detTubs[ring]->GetDeltaPhiAngle());
      G4cout << lineOutput;
//
      fScatScintillator[ring] =
        new G4LogicalVolume(scintTubs[ring],
         detMaterial,scintTubs[ring]->GetName());
      G4LogicalVolume * wrapVol = new G4LogicalVolume(wrapTubs[ring],
         detMaterial,wrapTubs[ring]->GetName());
      detVol[ring] = new G4LogicalVolume(detTubs[ring],
         fEnvironmentMaterial,detTubs[ring]->GetName());
      new G4PVPlacement(0,origin,fScatScintillator[ring],
        scintTubs[ring]->GetName(),wrapVol,false,0,checkOverlaps);
      new G4PVPlacement(0,origin,wrapVol,wrapTubs[ring]->GetName(),
        detVol[ring],false,0,checkOverlaps);
//
      fScatScintillator[ring]->SetVisAttributes(att_blue);
      wrapVol->SetVisAttributes(att_black);
      detVol[ring]->SetVisAttributes(clear);
//
      double width = outerDet * sin(CLHEP::halfpi*rad - lowPhi);
      if(width > maxWidth) maxWidth = width;
      G4cout << "maxWidth: " << maxWidth << G4endl;
      innerRad = outerDet + fScatScintGap + wrappingHalfThick +
                 gapHalfThick;
    }
//
//   Place the rings into a "plane" box.
//   Awkward, but allows the hits for the beam detector to be used.
//
    G4ThreeVector scatPlaneDim;
    scatPlaneDim.setX(maxWidth);
    scatPlaneDim.setY(0.5 * detTubs[fNumScatScint - 1]->GetOuterRadius());
    scatPlaneDim.setZ(detTubs[fNumScatScint - 1]->GetZHalfLength());
    G4Box * scatPlaneBox = new G4Box("ScatterPlane",
      scatPlaneDim.x(),scatPlaneDim.y(),scatPlaneDim.z());
//
//  Create a cylinder to cut out of the box, for beam detector clearance:
//
    G4Tubs * beamDetSpace = new G4Tubs("BeamDetSpace",
       0.0,fScatMinRadius - 2.0 * mm,scatPlaneDim.z(),0.0,CLHEP::pi);
    sprintf(lineOutput,formTubsOut,beamDetSpace->GetName().c_str(),
	beamDetSpace->GetInnerRadius(),beamDetSpace->GetOuterRadius(),
	beamDetSpace->GetZHalfLength(),
	beamDetSpace->GetStartPhiAngle(),beamDetSpace->GetDeltaPhiAngle());
//
    G4cout << lineOutput;
    G4ThreeVector cutoutPos = origin;
    cutoutPos.setY(-scatPlaneDim.y());
    G4SubtractionSolid * arrayWithHole =
      new G4SubtractionSolid("BackingArrayWithHole",scatPlaneBox,
        beamDetSpace,0,cutoutPos);
    arrayWithHole->DumpInfo();
    G4LogicalVolume * planeVol = new G4LogicalVolume(arrayWithHole,
         fEnvironmentMaterial,scatPlaneBox->GetName());
    planeVol->SetVisAttributes(clear);
    sprintf(lineOutput,formDimOut,scatPlaneBox->GetName().c_str(),
      scatPlaneDim.x(),scatPlaneDim.y(),scatPlaneDim.z());
    G4cout << lineOutput;
//
//  Position the rings into the plane box.
//
    G4ThreeVector ringPos = origin;
    ringPos.setY(-scatPlaneDim.y());
    for(int ring = 0; ring < fNumScatScint; ring++){
      new G4PVPlacement(0,ringPos,detVol[ring],
        detVol[ring]->GetName(),planeVol,false,ring,checkOverlaps);
    }
//
//  Now create the overall volume of the backing array.
//
    G4ThreeVector scatArrayDim(scatPlaneDim.x(),
     detTubs[fNumScatScint - 1]->GetOuterRadius(),detDim.z());
    G4Box * scatArrayBox = new G4Box("ScatterArray",
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    sprintf(lineOutput,formDimOut,scatArrayBox->GetName().c_str(),
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    G4cout << lineOutput;
    G4LogicalVolume * arrayVol = new G4LogicalVolume(scatArrayBox,
         fEnvironmentMaterial,scatArrayBox->GetName());
    arrayVol->SetVisAttributes(clear);
//
//  Place two planes of ring detectors into the overall volume.
//
    G4ThreeVector planePos = origin;
    planePos.setY(scatPlaneDim.y());
    G4RotationMatrix * zRot = new G4RotationMatrix;
    zRot->rotateZ(CLHEP::pi*rad);
    G4RotationMatrix * planeRot[NUM_SCATTER_LAYERS] = {0,zRot};
    for(int plane = 0; plane < NUM_SCATTER_LAYERS; plane++){
      sprintf(lineOutput,formPosOut,planeVol->GetName().c_str(),
        planePos.x(),planePos.y(),planePos.z());
      G4cout << lineOutput;
      new G4PVPlacement(planeRot[plane],planePos,planeVol,planeVol->GetName(),
        arrayVol,false,plane,checkOverlaps);
      planePos.setY(-planePos.y());
    }
    DumpFamily(arrayVol);

    return arrayVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructScatBarDetector(){
//
//  Construct a backing arrays.  Different types are defined.
//
     G4cout << G4endl << "In ConstructScatBarDetector..." << G4endl;
//
//   Begin with some hard-coded dimensions that vary later
//   Geometry in G4ThreeVector fScatScintDim, passed by command
//   fScatScintDim.x() - maximum length of the inner counter
//   fScatScintDim.y() - radial width of a counter
//   fScatScintDim.z() - the absorption thickness of a counter
//
    G4bool checkOverlaps = true;
//
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* detMaterial =
      nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
//
    const double wrappingHalfThick = 0.05 * cm;
    const double gapHalfThick = 0.05 * cm; // Minimum gap between detectors
    G4ThreeVector wrapDim = fScatScintDim;
    wrapDim.setZ(fScatScintDim.z() + wrappingHalfThick);
    G4ThreeVector detDim = wrapDim;
    detDim.setZ(wrapDim.z() + gapHalfThick);
    G4LogicalVolume * beamDetVol =
      G4LogicalVolumeStore::GetInstance()->GetVolume("BeamArray");
    double beamDetThick = 0.0;
    if(beamDetVol){
      beamDetThick = beamDetVol->GetSolid()->GetExtent().GetZmax();
      if(beamDetThick > detDim.z()) detDim.setZ(beamDetThick);
    }
    const G4ThreeVector origin(0.0,0.0,0.0);

    G4LogicalVolume * detVol[MAX_SCATTER_COUNTERS];
    const G4Color  blueColor(0.0,0.0,0.8);
    const G4Color blackColor(0.0,0.0,0.0);
    const G4VisAttributes  *att_blue = new G4VisAttributes(blueColor);
    const G4VisAttributes *att_black = new G4VisAttributes(blackColor);
    const G4VisAttributes *clear = new G4VisAttributes(false);
//
    G4ThreeVector scintDim = 0.5 * fScatScintDim;
    G4Box * scintBox[MAX_SCATTER_COUNTERS];
    G4Box * wrapBox[MAX_SCATTER_COUNTERS];
    G4Box * detBox[MAX_SCATTER_COUNTERS];
    G4ThreeVector detPos[MAX_SCATTER_COUNTERS];
//    double tanPhi = 0.5 * fScatScintDim.x()/fScatMinRadius;
    double innerRad = fScatMinRadius;
    for(int cntr = 0; cntr < fNumScatScint; cntr++){
      double innerScint = innerRad + wrappingHalfThick;
      double outerScint = innerScint + fScatScintDim.y();
      double avgRad = 0.5 * (innerScint + outerScint);
      sprintf(name,"ScatScintillator_%i",cntr);
      sprintf(lineOutput,"%s avgRad: %6.2f \n",name,avgRad);
      G4cout << lineOutput;
      scintBox[cntr] = new G4Box(name,scintDim.x(),scintDim.y(),scintDim.z());
      sprintf(lineOutput,formDimOut,scintBox[cntr]->GetName().c_str(),
        scintDim.x(),scintDim.y(),scintDim.z());
      G4cout << lineOutput;
//
      double outerWrap = outerScint + wrappingHalfThick;
      wrapDim.setX(scintDim.x() + wrappingHalfThick);
      wrapDim.setY(scintDim.y() + wrappingHalfThick);
      wrapDim.setZ(scintDim.z() + wrappingHalfThick);
      sprintf(name,"WrapBar_%i",cntr);
      wrapBox[cntr] = new G4Box(name,wrapDim.x(),wrapDim.y(),
        wrapDim.z());
      sprintf(lineOutput,formDimOut,wrapBox[cntr]->GetName().c_str(),
        wrapDim.x(),wrapDim.y(),wrapDim.z());
      G4cout << lineOutput;
//
//      double innerDet  = innerWrap - gapHalfThick;
      double outerDet  = outerWrap + gapHalfThick;
      detDim = wrapDim;
      if(beamDetVol && (beamDetThick > detDim.z()))
        detDim.setZ(beamDetThick);
      sprintf(name,"DetBar_%i",cntr);
      detBox[cntr] = new G4Box(name,detDim.x(),detDim.y(),detDim.z());
      sprintf(lineOutput,formDimOut,detBox[cntr]->GetName().c_str(),
	detBox[cntr]->GetXHalfLength(),detBox[cntr]->GetYHalfLength(),
	detBox[cntr]->GetZHalfLength());
      G4cout << lineOutput;
//
      fScatScintillator[cntr] = new G4LogicalVolume(scintBox[cntr],
        detMaterial,scintBox[cntr]->GetName());
      G4LogicalVolume * wrapVol = new G4LogicalVolume(wrapBox[cntr],
        detMaterial,wrapBox[cntr]->GetName());
      detVol[cntr] = new G4LogicalVolume(detBox[cntr],
        fEnvironmentMaterial,detBox[cntr]->GetName());
      new G4PVPlacement(0,origin,fScatScintillator[cntr],
        scintBox[cntr]->GetName(),wrapVol,false,0,checkOverlaps);
      new G4PVPlacement(0,origin,wrapVol,wrapBox[cntr]->GetName(),
        detVol[cntr],false,0,checkOverlaps);
//
      fScatScintillator[cntr]->SetVisAttributes(att_blue);
      wrapVol->SetVisAttributes(att_black);
      detVol[cntr]->SetVisAttributes(clear);
//
      innerRad = outerDet + fScatScintGap + wrappingHalfThick +
                 gapHalfThick;
    }
//
//   Place the counters into a "plane" box.
//   Awkward, but allows the hits for the beam detector to be used.
//
    G4ThreeVector scatPlaneDim;
    scatPlaneDim.setX(detBox[fNumScatScint - 1]->GetXHalfLength());
    scatPlaneDim.setY(fNumScatScint *
      detBox[fNumScatScint - 1]->GetYHalfLength() +
      (fNumScatScint - 1) * (0.5 * fScatScintGap + gapHalfThick));
    scatPlaneDim.setZ(detBox[fNumScatScint - 1]->GetZHalfLength());
    G4Box * scatPlaneBox = new G4Box("ScatterPlane",
      scatPlaneDim.x(),scatPlaneDim.y(),scatPlaneDim.z());
    scatPlaneBox->DumpInfo();
    G4LogicalVolume * planeVol = new G4LogicalVolume(scatPlaneBox,
         fEnvironmentMaterial,scatPlaneBox->GetName());
    planeVol->SetVisAttributes(clear);
//
//  Position the counters into the plane box.
//
    for(int cntr = 0; cntr < fNumScatScint; cntr++){
      detPos[cntr].setY((2 * cntr + 1) * detBox[cntr]->GetYHalfLength() +
        cntr * (fScatScintGap + 2.0 * gapHalfThick) -
	scatPlaneBox->GetYHalfLength());
      sprintf(lineOutput,formPosOut,detBox[cntr]->GetName().c_str(),
        detPos[cntr].x(),detPos[cntr].y(),detPos[cntr].z());
      G4cout << lineOutput;
      new G4PVPlacement(0,detPos[cntr],detVol[cntr],detVol[cntr]->GetName(),
        planeVol,false,cntr,checkOverlaps);
    }
//
//  Now create the overall volume of the backing array.
//
    G4ThreeVector scatArrayDim = scatPlaneDim;
    scatArrayDim.setY(2.0 * scatPlaneBox->GetYHalfLength() +
      fScatMinRadius + wrappingHalfThick);
    G4Box * scatArrayBox = new G4Box("BackingArray",
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    sprintf(lineOutput,formDimOut,scatPlaneBox->GetName().c_str(),
      scatPlaneDim.x(),scatPlaneDim.y(),scatPlaneDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,scatArrayBox->GetName().c_str(),
      scatArrayDim.x(),scatArrayDim.y(),scatArrayDim.z());
    G4cout << lineOutput;
    G4LogicalVolume * arrayVol = new G4LogicalVolume(scatArrayBox,
         fEnvironmentMaterial,scatArrayBox->GetName());
    arrayVol->SetVisAttributes(clear);
//
//  Place two planes of bar detectors into the overall volume.
//
    G4RotationMatrix * zRot = new G4RotationMatrix;
    zRot->rotateZ(CLHEP::pi*rad);
    G4RotationMatrix * planeRot[NUM_SCATTER_LAYERS] = {0,zRot};
    G4ThreeVector planePos = origin;
    planePos.setY(scatArrayBox->GetYHalfLength() -
      scatPlaneBox->GetYHalfLength() - 2.0 * gapHalfThick);
    for(int plane = 0; plane < NUM_SCATTER_LAYERS; plane++){
      sprintf(name,"%s_%i",planeVol->GetName().c_str(),plane);
      sprintf(lineOutput,formPosOut,name,
        planePos.x(),planePos.y(),planePos.z());
      G4cout << lineOutput;
      new G4PVPlacement(planeRot[plane],planePos,planeVol,name,
        arrayVol,false,plane,checkOverlaps);
      planePos.setY(-planePos.y());
    }

    return arrayVol;
//    return 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBottomDetector(){
//
//  Construct a backing arrays.  Different types are defined.
//
     G4cout << G4endl << "In ConstructBottomDetector..." << G4endl;
     G4LogicalVolume * cartBottomVol =
       G4LogicalVolumeStore::GetInstance()->GetVolume("CartBottom");
     if(!cartBottomVol){
       G4cout << "Returning without making cart bottom detector" << G4endl;
       return 0;
     }
//
//   Begin with some hard-coded dimensions that vary later
//   Geometry in G4ThreeVector fScatScintDim, passed by command
//   fScatScintDim.x() - maximum length of the inner counter
//   fScatScintDim.y() - radial width of a counter
//   fScatScintDim.z() - the absorption thickness of a counter
//
    G4bool checkOverlaps = true;
    const int DET_PER_LAYER = 10;
    const double wrappingHalfThick = 0.05 * cm;
    const double gapHalfThick = 0.05 * cm;
//    const G4ThreeVector scintDim = 0.5 * fScatScintDim;
    const G4ThreeVector scintDim(15.0,1.0,1.0);
    const G4ThreeVector wrapDim(scintDim.x() + wrappingHalfThick,
                                scintDim.y() + wrappingHalfThick,
                                scintDim.z() + wrappingHalfThick);
    const G4ThreeVector detectorDim(wrapDim.x() + gapHalfThick,
                                    wrapDim.y() + gapHalfThick,
                                    wrapDim.z() + gapHalfThick);
    const G4ThreeVector origin(0.0,0.0,0.0);
//
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* detMaterial =
      nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Box * scintillatorBox = new G4Box("Scintillator",
       scintDim.x(),scintDim.y(),scintDim.z());
    G4Box * wrapBox = new G4Box("ScintillatorWrap",
       wrapDim.x(),wrapDim.y(),wrapDim.z());
    G4Box * detectorBox = new G4Box("BottomDetector",
       detectorDim.x(),detectorDim.y(),detectorDim.z());
//
    fBottomScintillator = new G4LogicalVolume(scintillatorBox,
       detMaterial,scintillatorBox->GetName());
    G4LogicalVolume * wrapVol = new G4LogicalVolume(wrapBox,
       detMaterial,wrapBox->GetName());
    G4LogicalVolume * detectorVol = new G4LogicalVolume(detectorBox,
       fEnvironmentMaterial,detectorBox->GetName());
//
    sprintf(lineOutput,formDimOut,fBottomScintillator->GetName().c_str(),
      scintDim.x(),scintDim.y(),scintDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,wrapVol->GetName().c_str(),
      wrapDim.x(),wrapDim.y(),wrapDim.z());
    G4cout << lineOutput;
    sprintf(lineOutput,formDimOut,detectorVol->GetName().c_str(),
      detectorDim.x(),detectorDim.y(),detectorDim.z());
    G4cout << lineOutput;
//
    new G4PVPlacement(0,origin,fBottomScintillator,"BottomScintillator",
      wrapVol,false,0,checkOverlaps);
    new G4PVPlacement(0,origin,wrapVol,wrapVol->GetName(),
      detectorVol,false,0,checkOverlaps);

    const G4Color  blueColor(0.0,0.0,0.8);
    const G4Color blackColor(0.0,0.0,0.0);
    const G4VisAttributes  *att_blue = new G4VisAttributes(blueColor);
    const G4VisAttributes *att_black = new G4VisAttributes(blackColor);
    const G4VisAttributes *clear = new G4VisAttributes(false);
    fBottomScintillator->SetVisAttributes(att_blue);
    wrapVol->SetVisAttributes(att_black);
    detectorVol->SetVisAttributes(clear);
//
//  Place the bars within a plane, the plane within the array.
//  This extra layer is for consistancy with the scattering array.
//
    G4ThreeVector bottomExtentMax(cartBottomVol->GetSolid()->GetExtent().GetXmax(),
                                  cartBottomVol->GetSolid()->GetExtent().GetYmax(),
                                  cartBottomVol->GetSolid()->GetExtent().GetZmax());
    sprintf(lineOutput,formDimOut,cartBottomVol->GetName().c_str(),
      bottomExtentMax.x(),bottomExtentMax.y(),bottomExtentMax.z());
    G4cout << lineOutput;
//
    G4ThreeVector planeBoxDim = bottomExtentMax;
    planeBoxDim.setX(bottomExtentMax.x() - 1.0 * mm);
    planeBoxDim.setY(detectorDim.y());
    planeBoxDim.setZ(bottomExtentMax.z() - 1.0 * mm);
    G4Box * planeBox = new G4Box("CartBottomPlane",
       planeBoxDim.x(),planeBoxDim.y(),planeBoxDim.z());
    sprintf(lineOutput,formDimOut,planeBox->GetName().c_str(),
      planeBoxDim.x(),planeBoxDim.y(),planeBoxDim.z());
    G4cout << lineOutput;
    G4LogicalVolume * planeVol = new G4LogicalVolume(planeBox,
       fEnvironmentMaterial,planeBox->GetName());
    planeVol->SetVisAttributes(clear);

    G4ThreeVector arrayBoxDim = planeBoxDim;
    arrayBoxDim.setX(planeBoxDim.x() + 0.5 * mm);
    arrayBoxDim.setY(planeBoxDim.y() + 0.5 * mm);
    arrayBoxDim.setZ(planeBoxDim.z() + 0.5 * mm);
    G4Box * arrayBox = new G4Box("CartBottomArray",
       arrayBoxDim.x(),arrayBoxDim.y(),arrayBoxDim.z());
    sprintf(lineOutput,formDimOut,arrayBox->GetName().c_str(),
      arrayBoxDim.x(),arrayBoxDim.y(),arrayBoxDim.z());
    G4cout << lineOutput;
    G4LogicalVolume * arrayVol = new G4LogicalVolume(arrayBox,
       fEnvironmentMaterial,arrayBox->GetName());
    arrayVol->SetVisAttributes(clear);

    G4ThreeVector detPos = origin;
    double zHalfSpacing = arrayBoxDim.z()/DET_PER_LAYER;
    for(int det = 0; det < DET_PER_LAYER; det++){
      double zLocal = (2 * det + 1) * zHalfSpacing -
        arrayBox->GetZHalfLength();
      detPos.setZ(zLocal);
//      sprintf(name,"%s_%i",detectorVol->GetName().c_str(),det);
      sprintf(lineOutput,formPosOut,detectorVol->GetName().c_str(),
        detPos.x(),detPos.y(),detPos.z());
      G4cout << lineOutput;
      new G4PVPlacement(0,detPos,detectorVol,detectorVol->GetName(),
        planeVol,false,det,checkOverlaps);
    }
    new G4PVPlacement(0,origin,planeVol,planeVol->GetName(),
      arrayVol,false,0,checkOverlaps);
    DumpFamily(arrayVol);

    return arrayVol;
//    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4LogicalVolume* IronFilterDetectorConstruction::ConstructBackingWall(){
//
//  Construct a slab detector as a sort of backing array.
//
     G4cout << G4endl << "In ConstructBackingWall..." << G4endl;
     G4bool checkOverlaps = true;
//
//   Detector volume will be a box of polyethylene, in layers.
//   If detector is not used, build it anyway from air.
//
     G4NistManager* nistManager = G4NistManager::Instance();
     G4Material* layerMaterial;
     if(fUseBackingWall){
       layerMaterial = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
     }
     else{
       layerMaterial = fEnvironmentMaterial;
     }
     G4cout << "   BackingWall is made of "
            << layerMaterial->GetName() << G4endl;
//
     G4LogicalVolume * brick =
       G4LogicalVolumeStore::GetInstance()->GetVolume("LeadBrick");
     if(!brick){
       G4cout << "  Lead brick for south wall is not yet made" << G4endl;
       return 0;
     }
     else{
       G4cout << "  Found brick " << brick->GetName() << G4endl;
     }
     G4ThreeVector brickDim =
       G4ThreeVector(brick->GetSolid()->GetExtent().GetXmax(),
                     brick->GetSolid()->GetExtent().GetYmax(),
                     brick->GetSolid()->GetExtent().GetZmax());
     G4ThreeVector backingLayerDim(4.0 * brickDim.z(),
       16.0 * brickDim.y(), 1 * cm);
     G4Box * backingLayerBox = new G4Box("BackingLayer",
       backingLayerDim.x(),backingLayerDim.y(),backingLayerDim.z());
     G4LogicalVolume * backingLayerVol = new G4LogicalVolume(backingLayerBox,
       layerMaterial,backingLayerBox->GetName());
     const G4Color blueColor(0.0,0.0,0.0);
     const G4VisAttributes *att_blue = new G4VisAttributes(blueColor);
     backingLayerVol->SetVisAttributes(att_blue);
//
     const double airGap = 1.0 * mm;
     G4ThreeVector backingDim = backingLayerDim;
     backingDim.setZ(N_WALL_LAYERS * backingLayerDim.z() + 0.5 * airGap);
     G4Box * backingBox = new G4Box("BackingWall",
       backingDim.x(),backingDim.y(),backingDim.z());
     G4LogicalVolume * backingVol =
       new G4LogicalVolume(backingBox,fEnvironmentMaterial,
                           backingBox->GetName());
     const G4VisAttributes *att_invis = new G4VisAttributes(false);
     backingVol->SetVisAttributes(att_invis);
     backingBox->DumpInfo();
//
     G4ThreeVector backingLayerPos(0.0,0.0,0.0);
     for(int layer = 0; layer < N_WALL_LAYERS; layer++){
       double zLayer = (1 + 2 * layer) * backingLayerDim.z() -
                        backingDim.z();
       backingLayerPos.setZ(zLayer);
       sprintf(name,"%s_%i",backingLayerVol->GetName().c_str(),layer);
       new G4PVPlacement(0,backingLayerPos,backingLayerVol,name,
         backingVol,false,layer,checkOverlaps);
     }
     return backingVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::DumpParameters(){
//
//  Print all of the variables defined in the header.
//
  printf("\n  *************************************************\n");
  printf("              NEXUS simulation input parameters \n\n ");
     const char * formVector = "%30s : %8.2f  %8.2f  %8.2f \n";
     const char * formDouble = "%30s : %8.2f \n";
     const char * formInteg  = "%30s : %8i \n";
     const char * formString = "%30s : %s \n";
     const char * formBool   = "%30s : %8i  (0 = FALSE) \n";
//
  printf(formString,"Environment material",fEnvironmentMaterial->GetName().c_str());
  printf(formVector,"Generator size",fGeneratorSize.x(),
    fGeneratorSize.y(),fGeneratorSize.z());
  printf(formVector,"Generator shift",fGeneratorShift.x(),
    fGeneratorShift.y(),fGeneratorShift.z());
  printf("  \n");
  printf(formDouble,"Poly Plate Gap",fPolyGap);
  printf(formBool,"Use the south wall",fUseSouthWall);
  printf(formBool,"Use the south wall plug",fUseSouthWallPlug);
  printf(formBool,"Use the cannon",fUseCannon);
  printf(formString,"Cannon material",fCannonMaterial->GetName().c_str());
  printf(formDouble,"Lead Brick Gap",fLeadGap);
  printf(formDouble,"Horizontal Lead Brick Gap",fLeadHorizGap);
  printf(formString,"Wall material",fWallMaterial->GetName().c_str());
  printf("  \n");
  printf(formDouble,"Dump depth",fDumpDepth);
  printf(formDouble,"Dump radius",fDumpRadius);
  printf(formString,"Dump material",fDumpMaterial->GetName().c_str());
  printf("  \n");
  printf(formDouble,"Collimator radius",fCollRadius);
  printf(formDouble,"Shield hole radius",fShieldHoleRadius);
  printf(formDouble,"Beam pipe clearance",fBeamPipeClear);
  printf(formDouble,"Beam pipe wall",fBeamPipeWall);
  printf(formString,"Beam pipe material",fBeamPipeMaterial->GetName().c_str());
  printf("  \n");
  printf(formBool,"Use the cryostat",fUseCryostat);
  printf(formString,"Target material",fTargetMaterial->GetName().c_str());
  printf(formDouble,"Cryostat height",fCryostatHeight);
  printf(formString,"Cryostat OVC material",fCryoOVCMater.c_str());
  printf(formString,"Cryostat Shield material",fCryoShieldMater.c_str());
  printf(formBool,"Use alternate target",fUseAltTarget);
  printf(formVector,"Alternate target size",fAltTargetSize.x(),
  fAltTargetSize.y(),fAltTargetSize.z());
  printf(formDouble,"Target temperature",fTargetTemperature);
  printf("  \n");
  printf(formBool,"Use of the floor",fUseFloor);
  printf(formBool,"Use of the floor block",fUseFloorBlock);
  printf(formDouble,"Floor block elevation",fFloorBlockHeight);
  printf(formBool,"Use the notch",fUseNotch);
  printf(formBool,"Use the table leg",fUseTableLeg);
  printf(formBool,"Use the cart shield",fUseCartShield);
  printf(formDouble,"Shield cart Z offset",fCartZOffset);
  printf(formBool,"Use the backing array",fUseBackingWall);
  printf(formDouble,"Backing array Z position",fBackingZposition);
  printf(formBool,"Use the backing face",fUseBackingFace);
  printf(formDouble,"Backing face thickness",fBackingFaceThick);
  printf(formString,"Backing face Material",fBackingFaceMater.c_str());
  printf(formInteg,"Backing array type",fBackingType);
  printf(formVector,"Backing array beam dimensions",fBeamScintDim.x(),
    fBeamScintDim.y(),fBeamScintDim.z());
  printf(formVector,"Backing array scatter dimensions",fScatScintDim.x(),
    fScatScintDim.y(),fScatScintDim.z());
  printf(formDouble,"Backing array scatter gap",fScatScintGap);
  printf("  \n");
  printf(formBool,"Use Shield parametrization",fParametrization);
  for(int layer = 0; layer < N_SHIELD_LAYERS; layer++){
    printf("Shield layer %i - \n",layer);
    printf(formString,"   Material",fLayerMaterial[layer]->GetName().c_str());
    printf(formVector,"   Thickness",fLayerThickness[layer].x(),
      fLayerThickness[layer].y(),fLayerThickness[layer].z());
    printf(formVector,"   Aspect",fLayerAspect[layer].x(),
      fLayerAspect[layer].y(),fLayerAspect[layer].z());
    printf(formInteg,"      Gaps",fLayerGaps[layer]);
  }
  printf("\n  *************************************************\n\n");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::DumpFamily(G4LogicalVolume * motherVol,
                                        int nGener){

  if(motherVol){
    G4String strOutput = "\nVolume arrangement for ";
    strOutput += motherVol->GetName();
    strOutput += ": \n";
    G4cout << strOutput << G4endl;
    DumpDaughters(motherVol,nGener);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::DumpDaughters(G4LogicalVolume * motherVol,
                                           int nGener, G4String indent){
    if(nGener < 0) return;
    G4String strOutput;
    G4String nextIndent = indent + "  ";
    int numDaugh = 0;
    while(numDaugh < int(motherVol->GetNoDaughters())){
      G4VPhysicalVolume * daughterPhys = motherVol->GetDaughter(numDaugh);
      G4LogicalVolume *   daughterVol  = daughterPhys->GetLogicalVolume();
      sprintf(name,"Daughter %i: %s [%i] \n",numDaugh,
	  daughterPhys->GetName().c_str(), int(daughterPhys->GetCopyNo()));
      strOutput += indent + name;
      G4cout << strOutput;
      strOutput = "";
      int nextGener = nGener - 1;
      DumpDaughters(daughterVol,nextGener,nextIndent);
      numDaugh++;
    }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreeVector IronFilterDetectorConstruction::LocateDaughter(G4LogicalVolume * motherVol,
                                        G4VPhysicalVolume * daughterVol){

    G4ThreeVector location(0.0,0.0,0.0);
    if( motherVol && daughterVol){
      sprintf(name,"%18s[%i]",daughterVol->GetName().c_str(),
        daughterVol->GetCopyNo());
      G4String strOutput = name;
      strOutput += " position in " + motherVol->GetName() + ": ";
      bool found = false;
      WhereDaughters(motherVol,daughterVol,location,found);
      if(found){
        G4cout << strOutput << location << G4endl;
      }
      else{
        strOutput += " was not found";
        G4cout << strOutput << G4endl;
      }
    }
    return location;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void IronFilterDetectorConstruction::WhereDaughters(G4LogicalVolume * motherVol,
                                           G4VPhysicalVolume * lostDaughterVol,
					   G4ThreeVector &location,
				 	   bool &found){
    int numDaugh = 0;
    G4String strOutput;
    while((numDaugh < int(motherVol->GetNoDaughters())) && !found){
      G4VPhysicalVolume  * daughterPhys = motherVol->GetDaughter(numDaugh);
      G4ThreeVector position = daughterPhys->GetTranslation();
      G4RotationMatrix * rotate = daughterPhys->GetRotation();
      if(daughterPhys != lostDaughterVol){
        G4LogicalVolume *   daughterVol  = daughterPhys->GetLogicalVolume();
        WhereDaughters(daughterVol,lostDaughterVol,location,found);
        if(found){
          if(rotate){
            location = position + (*rotate).inverse() * location;
          }
	  else{
	    location += position;
	  }
	}
      }
      else{
        found = true;
        if(rotate){
          location = position + (*rotate).inverse() * location;
        }
	else{
	  location += position;
	}
      }
      numDaugh++;
    }
}
