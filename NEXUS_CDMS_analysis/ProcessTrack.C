#include "TSystem.h"
#include <vector>
#include "TMath.h"
#include <map>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<string.h>

class MacroInfo{
  public:
    double NoOfParticle;
    void GetNoOfParticle(TMacro* h1, string Xphrase);

};

void MacroInfo::GetNoOfParticle(TMacro* h1, string phrase) {

  string str;
  std::string length(h1->GetLineWith((phrase).c_str())->GetString());
  stringstream ssx(length.c_str());
  ssx>>str>>NoOfParticle;
  cout<<NoOfParticle<<endl;

}

MacroInfo GetMacroInfo(TFile* file, TString Filename){
  MacroInfo m;
  TIter next(file->GetListOfKeys());
  TString T2HF_name;
  TKey *key;
  while ((key=(TKey*)next())) {
   T2HF_name=key->GetName();

    if (T2HF_name.EqualTo(Filename)) {

        TMacro* h1 = (TMacro*)file->Get(T2HF_name);
        m.GetNoOfParticle(h1,"/run/beamOn");
    }

  }
 return m;
}


void ProcessTrack(const char* ext = ".root"){


  string base_root_folder = "Three_LS_1cm_dia";
  //string base_root_folder = "GammaTh232";

  //create a new root file that will have the information about angle and Energy
  string output_file = "Combined"+base_root_folder+".root";
  TFile *g = new TFile(output_file.c_str(),"RECREATE");
  TTree *Event = new TTree("Event","simple tree");

  Double_t E_Dep_LS1carbon, E_Dep_LS1electron, E_Dep_LS1gamma, E_Dep_LS1proton, E_Dep_LS1deutrium;
  Double_t E_Dep_LS2carbon, E_Dep_LS2electron, E_Dep_LS2gamma, E_Dep_LS2proton, E_Dep_LS2deutrium;
  Double_t E_Dep_LS3carbon, E_Dep_LS3electron, E_Dep_LS3gamma, E_Dep_LS3proton, E_Dep_LS3deutrium;

  Int_t EventID;


  Event->Branch("E_Dep_LS1carbon",&E_Dep_LS1carbon,"E_Dep_LS1carbon/D");
  Event->Branch("E_Dep_LS1electron",&E_Dep_LS1electron,"E_Dep_LS1electron/D");
  Event->Branch("E_Dep_LS1gamma",&E_Dep_LS1gamma,"E_Dep_LS1gamma/D");
  Event->Branch("E_Dep_LS1proton",&E_Dep_LS1proton,"E_Dep_LS1proton/D");
  Event->Branch("E_Dep_LS1deutrium",&E_Dep_LS1deutrium,"E_Dep_LS1deutrium/D");

  Event->Branch("E_Dep_LS2carbon",&E_Dep_LS2carbon,"E_Dep_LS2carbon/D");
  Event->Branch("E_Dep_LS2electron",&E_Dep_LS2electron,"E_Dep_LS2electron/D");
  Event->Branch("E_Dep_LS2gamma",&E_Dep_LS2gamma,"E_Dep_LS2gamma/D");
  Event->Branch("E_Dep_LS2proton",&E_Dep_LS2proton,"E_Dep_LS2proton/D");
  Event->Branch("E_Dep_LS2deutrium",&E_Dep_LS2deutrium,"E_Dep_LS2deutrium/D");

  Event->Branch("E_Dep_LS3carbon",&E_Dep_LS3carbon,"E_Dep_LS3carbon/D");
  Event->Branch("E_Dep_LS3electron",&E_Dep_LS3electron,"E_Dep_LS3electron/D");
  Event->Branch("E_Dep_LS3gamma",&E_Dep_LS3gamma,"E_Dep_LS3gamma/D");
  Event->Branch("E_Dep_LS3proton",&E_Dep_LS3proton,"E_Dep_LS3proton/D");
  Event->Branch("E_Dep_LS3deutrium",&E_Dep_LS3deutrium,"E_Dep_LS3deutrium/D");

  Event->Branch("EventID",&EventID,"EventID/I");




    const char* inDir = "/Users/pratyushpatel/NEXUS_DD/NEXUS_CDMS/NEXUS_CDMS_analysis/";
    //const char* inDir = "/Volumes/GoogleDrive/My Drive/GraduateWork/HeRALD/raw_geant_outputdir/Backgrounds_Copper/GammaTh232";
    char* dir = gSystem->ExpandPathName(inDir);
    Printf("%s", dir);
    void* dirp = gSystem->OpenDirectory(dir);
    cout<<gSystem->OpenDirectory(dir)<<endl;
    const char* entry;
    const char* filename[10000];
    Int_t n = 0;
    TString str;
    long double TotalParticles=0.0;

    while((entry = (char*)gSystem->GetDirEntry(dirp))) {
      str = entry;
      if(str.EndsWith(ext))
        filename[n++] = gSystem->ConcatFileName(dir, entry);
    }


    //looping over the files
    for (Int_t i = 0; i < n; i++){


      TFile* file = new TFile(filename[i]);

      if( !file->IsOpen() ){
             cout<< "Error opening " << filename[i] <<endl;
             continue;
      }
      //first else
      else {
          if(file->IsZombie()) {
            cout<<"The file "<<filename[i]<<"is corrupted"<<endl;
            continue;
          }
      //2nd else
          else{
      //Printf("%d file -> %s",i, filename[i]);
      MacroInfo m=GetMacroInfo(file, "DTIronFilter");
      //MacroInfo m=GetMacroInfo(file, "DTGpsInMaterial_Cu_Th232");//_Cu_Co60
      //cout<<name.substr(96,17)<<"   "<<m.SurfaceArea<<endl;
      TotalParticles = m.NoOfParticle + TotalParticles;


      TTree *t1 = (TTree*)file->Get("IronFilter");
      if (!t1) {
          std::cerr << "Warning: TTree 'IronFilter' not found in file " << filename[i] << std::endl;
          file->Close();
          continue;  // Skip this file and move to the next
      }
      Int_t nentries = (Int_t)t1->GetEntries();

      Double_t time,X_pos,Y_pos,Z_pos,X_mom,Y_mom,Z_mom, Intial_E, Final_E, Dep_E;
      Int_t event_ID,track_ID, step_ID;
      char Vol_ID[28], Particle_ID[28], Process_Name[28];

      t1->SetBranchAddress("eventID",&event_ID);
      t1->SetBranchAddress("trackID",&track_ID);
      t1->SetBranchAddress("stepID",&step_ID);
      t1->SetBranchAddress("particle",Particle_ID);
      t1->SetBranchAddress("volume",Vol_ID);
      t1->SetBranchAddress("Eki",&Intial_E);
      t1->SetBranchAddress("Ekf",&Final_E);
      t1->SetBranchAddress("Edep",&Dep_E);
      t1->SetBranchAddress("x",&X_pos);
      t1->SetBranchAddress("y",&Y_pos);
      t1->SetBranchAddress("z",&Z_pos);
      t1->SetBranchAddress("px",&X_mom);
      t1->SetBranchAddress("py",&Y_mom);
      t1->SetBranchAddress("pz",&Z_mom);
      t1->SetBranchAddress("t",&time);
      t1->SetBranchAddress("process",Process_Name);


      Double_t ELS1carbon=0,ELS1electron=0, ELS1gamma=0, ELS1proton=0,ELS1deutrium=0;
      Double_t ELS2carbon=0,ELS2electron=0, ELS2gamma=0, ELS2proton=0,ELS2deutrium=0;
      Double_t ELS3carbon=0,ELS3electron=0, ELS3gamma=0, ELS3proton=0,ELS3deutrium=0;




      for (Int_t i=0;i<nentries;i++){

            t1->GetEntry(i);
            std::string Volume(Vol_ID);
            std::string Particle(Particle_ID);
            std::string Process(Process_Name);


            if( (Process != "newEvent") && (Process != "neutronInelastic") ){

             cout<<event_ID<<"  "<<Particle<<"   "<<Volume<<"   "<<Process<<"     "<<(Intial_E-Final_E)*1000<<"   "<<endl;

             if ( (Particle == "C12" ||Particle == "C13") && Volume == "LiquidScintillator_1") {
               ELS1carbon = ELS1carbon+ Dep_E;

             } else if (Particle == "gamma" && Volume == "LiquidScintillator_1") {
               ELS1gamma = ELS1gamma + Dep_E;

             }else if ((Particle == "proton") && Volume == "LiquidScintillator_1") {
               ELS1proton = ELS1proton + Dep_E;

             } else if ((Particle == "e-" ||Particle == "e+") && Volume == "LiquidScintillator_1") {
               ELS1electron = ELS1electron+ Dep_E;

             } else if ((Particle == "deuteron") && Volume == "LiquidScintillator_1") {
               ELS1deutrium = ELS1deutrium + Dep_E;


             } else if ((Particle == "C12" ||Particle == "C13") && Volume == "LiquidScintillator_2") {
               ELS2carbon = ELS2carbon+ Dep_E;

             } else if (Particle == "gamma" && Volume == "LiquidScintillator_2") {
               ELS2gamma = ELS2gamma + Dep_E;

             } else if ((Particle == "proton") && Volume == "LiquidScintillator_2") {
               ELS2proton = ELS2proton + Dep_E;

             } else if ((Particle == "e-" ||Particle == "e+") && Volume == "LiquidScintillator_2") {
               ELS2electron = ELS2electron+ Dep_E;

             } else if ((Particle == "deuteron") && Volume == "LiquidScintillator_2") {
               ELS2deutrium = ELS2deutrium + Dep_E;



             } else if ((Particle == "C12" ||Particle == "C13") && Volume == "LiquidScintillator_3") {
               ELS3carbon = ELS3carbon+ Dep_E;

             } else if (Particle == "gamma" && Volume == "LiquidScintillator_3") {
               ELS3gamma = ELS3gamma + Dep_E;

             } else if ((Particle == "proton") && Volume == "LiquidScintillator_3") {
               ELS3proton = ELS3proton + Dep_E;

             } else if ((Particle == "e-" ||Particle == "e+") && Volume == "LiquidScintillator_3") {
               ELS3electron = ELS3electron+ Dep_E;

             } else if ((Particle == "deuteron") && Volume == "LiquidScintillator_3") {
               ELS3deutrium = ELS3deutrium + Dep_E;

             }

             else{
               cout<<"Topology is different; need to include new forms of events"<<endl;
               cout<<"******************"<<endl;
               cout<<event_ID<<"  "<<Particle<<"   "<<Volume<<"    "<<(Intial_E-Final_E)*1000<<"   "<<endl;
               cout<<"******************"<<endl;
             }

            }
            //cout<<Particle<<"   "<<Volume<<"   "<<Dep_E*1000<<"   "<<EHegamma*1000<<"   "<<EHeelectron*1000<<"  "<<ECPDgamma*1000<<"   "<<ECPDelectron*1000<<endl;


            if (Process=="newEvent") {
              //cout<<"New Event:  electron:"<<EGeelectron*1000<<"   carbon:"<<EGeneutron*1000<<endl;


              E_Dep_LS1carbon = ELS1carbon*1000;
              E_Dep_LS1electron = ELS1electron*1000;
              E_Dep_LS1gamma = ELS1gamma*1000;
              E_Dep_LS1proton = ELS1proton*1000;
              E_Dep_LS1deutrium = ELS1deutrium*1000;

              E_Dep_LS2carbon = ELS2carbon*1000;
              E_Dep_LS2electron = ELS2electron*1000;
              E_Dep_LS2gamma = ELS2gamma*1000;
              E_Dep_LS2proton = ELS2proton*1000;
              E_Dep_LS2deutrium = ELS2deutrium*1000;

              E_Dep_LS3carbon = ELS3carbon*1000;
              E_Dep_LS3electron = ELS3electron*1000;
              E_Dep_LS3gamma = ELS3gamma*1000;
              E_Dep_LS3proton = ELS3proton*1000;
              E_Dep_LS3deutrium = ELS3deutrium*1000;

              EventID = event_ID;


              Event->Fill();

              ELS1carbon=0; ELS1electron=0; ELS1gamma=0; ELS1proton=0; ELS1deutrium=0;
              ELS2carbon=0; ELS2electron=0; ELS2gamma=0; ELS2proton=0; ELS2deutrium=0;
              ELS3carbon=0; ELS3electron=0; ELS3gamma=0; ELS3proton=0; ELS3deutrium=0;

              }
       }//end for looping over the entries

       file->Close();

     }//2nd else
   }//first else

}//end for looping over the files

cout<<"Total Particles Simulate "<<TotalParticles<<endl;


g->cd();

//g->Write("",TObject::kOverwrite);
g->Write("Event",TObject::kOverwrite);


TTree *Information = new TTree("Information","simple tree");
Double_t NoOfParticleSimulated;
Information->Branch("NoOfParticleSimulated",&NoOfParticleSimulated,"NoOfParticleSimulated/D");
NoOfParticleSimulated = TotalParticles;
Information->Fill();
g->Write("Information",TObject::kOverwrite);

g->Close();


}
