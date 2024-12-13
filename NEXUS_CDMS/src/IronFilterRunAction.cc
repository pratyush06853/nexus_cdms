
// $Id: IronFilterRunAction.cc $
//
/// \file IronFilterRunAction.cc
/// \brief Implementation of the IronFilterRunAction class


#include "IronFilterRunAction.hh"
#include "IronFilterRunActionMessenger.hh"
//#include "IronFilterAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "TFile.h"
#include "TTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterRunAction::IronFilterRunAction() : G4UserRunAction(),
    output_file( 0 ),
    data_tree( 0 ),
    output_name (""), fRunActionMessenger(0)
{
    // set printing event number per each event
     fRunActionMessenger = new IronFilterRunActionMessenger(this);
    G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterRunAction::~IronFilterRunAction(){
     delete fRunActionMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterRunAction::setOutputFileName(G4String newname){
    output_name = newname;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterRunAction::BeginOfRunAction(const G4Run* /*run*/){
    if( output_name!="" ){
        output_file = new TFile(output_name, "NEW");
        G4cout << "Output ROOT file " << output_name << " created." << G4endl;

        if( output_file ){
            data_tree = new TTree("IronFilter", "Track-level info for the run");
            G4cout << "Output TTree object created." << G4endl;
        }
    }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterRunAction::EndOfRunAction(const G4Run* /*run*/){

    if( output_file!=0 ) {
        for( unsigned int i=0; i<macros.size(); i++){
            TMacro mac( macros[i] );
            mac.Write();
        }

        std::stringstream ss;
        for( unsigned int i=0; i<random_seeds.size(); i++)
            ss << random_seeds[i] << '\t';

        TMacro randm( "rand_seeds");
        randm.AddLine( ss.str().c_str());
        randm.Write();

        output_file->Write();
        output_file->Close();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TTree* IronFilterRunAction::GetDataTree(){
    return data_tree;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
