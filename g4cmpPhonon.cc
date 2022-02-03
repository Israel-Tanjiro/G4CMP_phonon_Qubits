/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file phonon/g4cmpPhonon.cc
/// \brief Main program of the G4CMP/phonon example
//
// $Id$
//
// 20140509  Add conditional code for Geant4 10.0 vs. earlier
// 20150112  Remove RM->Initialize() call to allow macro configuration
// 20160111  Remove Geant4 version check since we now hard depend on 10.2+
// 20170816  Add example-specific configuration manager

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include "G4UIExecutive.hh"
#include "G4CMPPhysicsList.hh"
#include "G4CMPConfigManager.hh"
#include "PhononConfigManager.hh"
#include "PhononActionInitialization.hh"
#include "PhononDetectorConstruction.hh"
#include "G4VisExecutive.hh"
int main(int argc,char** argv)
{
 // Construct the run manager
 //
 G4RunManager * runManager = new G4RunManager;

 // Set mandatory initialization classes
 //
 PhononDetectorConstruction* detector = new PhononDetectorConstruction();
 runManager->SetUserInitialization(detector);

 G4VUserPhysicsList* physics = new G4CMPPhysicsList();
 physics->SetCuts();
 runManager->SetUserInitialization(physics);

 // Set user action classes (different for Geant4 10.0)
 //
 runManager->SetUserInitialization(new PhononActionInitialization);

 // Create configuration managers to ensure macro commands exist
 G4CMPConfigManager::Instance();
 PhononConfigManager::Instance();


G4VisManager* visManager = new G4VisExecutive;
visManager->Initialize();
 // Get the pointer to the User Interface manager
 //
 G4UImanager* UImanager = G4UImanager::GetUIpointer();
 G4UIExecutive * ui = new G4UIExecutive(argc,argv);
 UImanager->ApplyCommand("/control/execute vis.mac");
ui->SessionStart();


// UImanager->ApplyCommand("/run/initialize");
// UImanager->ApplyCommand("/run/beamOn 1");
// UImanager->ApplyCommand("/vis/open OGL ");
// UImanager->ApplyCommand("/vis/viewer/set/upVector 0 1 0");
// UImanager->ApplyCommand("/vis/viewer/set/viewpointerVector 0 0 1");
// UImanager->ApplyCommand("/vis/viewer/zoom 1.4");
// UImanager->ApplyCommand("/vis/drawVolume");
// UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true ");
// UImanager->ApplyCommand("/tracking/storeTrajectory 1");
// UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
// UImanager->ApplyCommand("/vis/scene/add/trajectories");
// UImanager->ApplyCommand("/vis/scene/add/hits");



//  if (argc==1)   // Define UI session for interactive mode
//  {
// #ifdef G4UI_USE
//       G4UIExecutive * ui = new G4UIExecutive(argc,argv);
//       ui->SessionStart();
//       delete ui;
// #endif
//  }
//  else           // Batch mode
//  {
//    G4String command = "/control/execute ";
//    G4String fileName = argv[1];
//    UImanager->ApplyCommand(command+fileName);
//  }
//
// #ifdef G4VIS_USE
//  delete visManager;
// #endif
//  delete runManager;
//
 return 0;
}
