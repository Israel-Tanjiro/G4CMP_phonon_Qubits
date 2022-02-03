#ifndef PHONONPHYSICSLIST_HH
#define PHONONPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class PhononPhysicslist : public G4VModularPhysicsList
{
public:
    PhononPhysicslist();
    ~PhononPhysicslist();
};

#endif
