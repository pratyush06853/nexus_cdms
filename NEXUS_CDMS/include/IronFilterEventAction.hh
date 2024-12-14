// $Id: IronFilterEventAction.hh $
//
/// \file IronFilterEventAction.hh
/// \brief Definition of the IronFilterEventAction class

#ifndef IronFilterEventAction_h
#define IronFilterEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "StepInfo.hh"
#include "IronFilterRunAction.hh"

class IronFilterEventAction : public G4UserEventAction{

public:

    IronFilterEventAction( IronFilterRunAction* input_run_action );
    virtual ~IronFilterEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    vector<StepInfo>& GetStepCollection();

private:

    IronFilterRunAction* run_action;

    TTree* data_tree;

    // methods
    void PrintEventStatistics() const;

    vector<StepInfo> stepCollection;

    // flags used to check whether a track passes both LHe and backing detector.
    int if_crytsal = 0;
    int if_zeroth = 0;
    int if_first = 0;
    int if_second = 0;
    int if_third = 0;
    int if_fourth  = 0;
    int if_fifth = 0;
    int if_sixth = 0;
    int if_seventh = 0;
    int if_eighth = 0;
    int if_ninth = 0;
    int if_tenth = 0;
    int if_eleventh = 0;
    int if_twelveth = 0;
    int if_thirteenth = 0;
    int if_LS_1 = 0;
    int if_LS_2 = 0;
    int if_LS_3 = 0;


    int eventID;
    int trackID;
    int stepID;
    int parentID;

    int max_char_len;
    char particle_name[70];
    char volume_name[70];
    char process_name[70];

    G4String tmp_particle_name;
    G4String tmp_volume_name;
    G4String tmp_process_name;

    int volume_copy_number;
    double Eki;
    double Ekf;
    double edep;

    G4ThreeVector position;
    G4ThreeVector momentum;

    double x;
    double y;
    double z;

    double px;
    double py;
    double pz;

    double global_time;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
