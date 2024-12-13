
/// \file IronFilterRunAction.hh
/// \brief Definition of the IronFilterRunAction class

#ifndef IronFilterRunAction_h
#define IronFilterRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TMacro.h"

#include <vector>
#include <sstream>

class G4Run;
class IronFilterRunActionMessenger;

class IronFilterRunAction : public G4UserRunAction {

public:

    IronFilterRunAction();
    virtual ~IronFilterRunAction();

    virtual void setOutputFileName(G4String newname);

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddMacro( G4String s){
        macros.push_back( s );
        /*
        if( output_file!=0 ){
            TMacro m( s.c_str());
            m.Write();
        }
        else{
            G4cout << "Warning: no output file is created yet. Macro not added." << G4endl;
        }
        */
    }
    void AddRandomSeeds( long seeds[], int len){
        for( int i=0; i<len; i++)
            random_seeds.push_back( seeds[i]);
        /*
        if( output_file!=0 ){
            std::stringstream ss;
            for( int i=0; i<len; i++)
                ss << seeds[i] << '\t';
            TMacro m( "rand_seed_array");
            m.AddLine( ss.str().c_str());
        }
        else{
            G4cout << "Warning: no output file is created yet. Macro not added." << G4endl;
        }
        */
    }

    TTree* GetDataTree();

private:

    G4String output_name = "";

    TFile* output_file;
    TTree* data_tree;

    std::vector< G4String > macros;
    std::vector< long > random_seeds;

    IronFilterRunActionMessenger* fRunActionMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
