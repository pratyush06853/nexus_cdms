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
// $Id: IronFilterParticleGunAction.cc $
//
/// \file IronFilterParticleGunAction.cc
/// \brief Implementation of the IronFilterParticleGunAction class

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

#include "IronFilterParticleGunAction.hh"
#include "G4RunManager.hh"
//#include "G4Navigator.hh"
//#include "G4PhysicalVolumeStore.hh"
//#include "G4VPhysicalVolume.hh"
//#include "G4SolidStore.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
//#include "G4Neutron.hh"
//#include "G4TransportationManager.hh"
//#include "G4Navigator.hh"
//#include "G4GenericIon.hh"
//#include "G4IonTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterParticleGunAction::IronFilterParticleGunAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleSource(0)
{
  fParticleSource = new G4ParticleGun();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterParticleGunAction::~IronFilterParticleGunAction()
{
  delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterParticleGunAction::GeneratePrimaries(G4Event* anEvent)
{

/*
//G4ThreeVector neutronDirection = G4RandomDirection();
double a;
ifstream f("/Users/pratyushpatel/TestFilter/a.out");
ofstream outfile;
outfile.open("/Users/pratyushpatel/TestFilter/o.out");
string line;
int flag=0;
while (getline(f, line)) {
    istringstream ss(line);
    if(flag){
      outfile<<line<<endl;
      flag =1;
    }
    else{
      //ss >> a >> b >> c>> d>> e>> f>> g;
      ss >> a;
      //fParticleSource->SetParticleEnergy(a/1000*MeV);
      //cout<<a<<"  "<<b<<"  "<<c<<"  "<<d<<"  "<<e<<"  "<<f<<"  "<<g<<endl;
      //cout<<a<<endl;
      flag =1;
    }
  }
outfile.close();
f.close();
remove("/Users/pratyushpatel/TestFilter/a.out");
rename("/Users/pratyushpatel/TestFilter/o.out","/Users/pratyushpatel/TestFilter/a.out");
*/
//ifstream input("/Users/pratyushpatel/TestFilter/a.out");

//if (!input) std::cerr << "Could not open the file!" << std::endl;
//if (input.is_open()) {
    //std::string line;
    //while (getline(input, line)) {
      //  printf("%s", line.c_str());
    //}
  //  input.close();
//}


//string base_root_file_name ="a";
//string base_root_folder = "Filter_Cap_2_FeI_41_files";
//string data_path ="/Users/pratyushpatel/24kevFilter/ROOT_Files";
//string data_path ="/Users/pratyushpatel/TestFilter";
//string search_command = data_path+ base_root_folder+ "/"+ base_root_file_name + "*.root";
//string search_command = data_path+"/"+ base_root_file_name + "*.out";
//system("rm -rf listOfFiles.txt");
//system(Form("ls %s > listOfFiles.txt", search_command.c_str()));
//ifstream listOfFiles("listOfFiles.txt");
//string filename;

// default particle kinematic
 G4ParticleDefinition* particleDefinition
  = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
 fParticleSource->SetParticleDefinition(particleDefinition);
 //fParticleSource->SetParticleEnergy(0.024*MeV);
 //fParticleSource->SetParticleEnergy(a/1000*MeV);

// Set source position
 fParticleSource->SetParticleMomentumDirection(G4ThreeVector(0., 1., 0.0));
 //G4cout<<"The Energy of the Primary Particle is "<<a/1000<<G4endl;
 //fParticleSource->SetParticlePosition(G4ThreeVector(0., 0., 3.025*cm));//45.0cm
 fParticleSource->SetParticlePosition(G4ThreeVector(0., 0., 0));
 fParticleSource->GeneratePrimaryVertex(anEvent);

}
