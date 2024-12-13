
/// \file IronFilterRunActionMessenger.hh
/// \brief Definition of the IronFilterRunActionMessenger class

#ifndef IronFilterRunActionMessenger_h
#define IronFilterRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class IronFilterRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class IronFilterRunActionMessenger: public G4UImessenger
{
    public:
        IronFilterRunActionMessenger(IronFilterRunAction* );
        virtual ~IronFilterRunActionMessenger();

        virtual void SetNewValue(G4UIcommand*, G4String);

      private:
        IronFilterRunAction* SetFileName;

        G4UIdirectory* SetFileNameDir;
        G4UIcmdWithAString* FileNameCmd;

};

#endif
