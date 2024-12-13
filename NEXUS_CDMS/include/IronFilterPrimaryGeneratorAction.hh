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
/// \file IronFilterPrimaryGeneratorAction.hh
/// \brief Definition of the IronFilterPrimaryGeneratorAction class

#ifndef IronFilterPrimaryGeneratorAction_h
#define IronFilterPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
//#include "G4AnalysisManager.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class IronFilterPrimaryMessenger;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class IronFilterPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    IronFilterPrimaryGeneratorAction();
    virtual ~IronFilterPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    void SetBeamHeight(double newValue) {fGeneratorPosition->setZ(newValue); }
    void SetCosThetaMin(double newValue = -1.0) {fCosThetaMin = newValue; }
    void SetCosThetaMax(double newValue =  1.0) {fCosThetaMax = newValue; }
    void SetPhiMin(double newValue = -CLHEP::pi*rad) {fPhiMin = newValue; }
    void SetPhiMax(double newValue =  CLHEP::pi*rad) {fPhiMax = newValue; }
    void SetSourceSize(double newValue =  0.8*cm) {fSourceSize = newValue; }
    void SetMisalignment(G4ThreeVector newValue) {fMisalignment = newValue; }
    void SetParticleEnergy(double newValue =  2.45*MeV) {fParticleEnergy = newValue; }
    void SetParticleName(G4String);
    double GetCosThetaMin() {return fCosThetaMin;}
    double GetCosThetaMax() {return fCosThetaMax;}
    double GetPhiMin() {return fPhiMin;}
    double GetPhiMax() {return fPhiMax;}
    void UseLineBeam(bool newValue = false){fUseLineBeam = newValue;};
    void SetVerbosity(G4int newValue = 0) { fVerbosity = newValue;};

  private:
    IronFilterPrimaryMessenger * fMessenger;
    G4int        fVerbosity;
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
    G4ThreeVector * fGeneratorPosition;
    G4String fParticleName;
    G4double fParticleEnergy;
    double fCosThetaMin;
    double fCosThetaMax;
    double fPhiMin;
    double fPhiMax;
    double fSourceSize;
    G4ThreeVector fMisalignment;
    bool fUseLineBeam;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
