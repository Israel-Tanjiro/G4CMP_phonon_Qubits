/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/src/PhononDetectorConstruction.cc \brief
/// Implementation of the PhononDetectorConstruction class
//
// $Id: a2016d29cc7d1e75482bfc623a533d20b60390da $
//
// 20140321  Drop passing placement transform to G4LatticePhysical

#include "PhononDetectorConstruction.hh"
#include "PhononSensitivity.hh"
#include "G4CMPElectrodeSensitivity.hh"
//#include "G4CMPElectrodeSensitivity.hh"
//#include "ChargeElectrodePattern.hh"
#include "G4CMPSurfaceProperty.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4FieldManager.hh"
#include "G4GeometryManager.hh"
#include "G4LatticeLogical.hh"
#include "G4LatticeManager.hh"
#include "G4LatticePhysical.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SolidStore.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Tubs.hh"
#include "G4UniformMagField.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
//#include "ChargeConfigMessenger.hh"
//#include "ChargeConfigManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhononDetectorConstruction::PhononDetectorConstruction()
  :   fLiquidHelium(0), fGermanium(0),fSilicon (0) ,fAluminum(0),  fNiobium(0) ,fTungsten(0),
    fWorldPhys(0), topSurfProp(0),topSurfPropNb(0) ,botSurfProp(0), wallSurfProp(0),
    electrodeSensitivity(0),fConstructed(false), fIfField(true){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhononDetectorConstruction::~PhononDetectorConstruction() {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* PhononDetectorConstruction::Construct()
{
  if (fConstructed) {
    if (!G4RunManager::IfGeometryHasBeenDestroyed()) {
      // Run manager hasn't cleaned volume stores. This code shouldn't execute
      G4GeometryManager::GetInstance()->OpenGeometry();
      G4PhysicalVolumeStore::GetInstance()->Clean();
      G4LogicalVolumeStore::GetInstance()->Clean();
      G4SolidStore::GetInstance()->Clean();
    }
    // Have to completely remove all lattices to avoid warning on reconstruction
    G4LatticeManager::GetLatticeManager()->Reset();
    // Clear all LogicalSurfaces
    // NOTE: No need to redefine the G4CMPSurfaceProperties
    G4LogicalBorderSurface::CleanSurfaceTable();
  }


  // // Only regenerate E field if it has changed since last construction.
  //   if (epotFileName != ChargeConfigManager::GetEPotFile() ||
  //       epotScale != ChargeConfigManager::GetEPotScale() ||
  //       voltage != ChargeConfigManager::GetVoltage()) {
  //      delete fEMField; fEMField = nullptr;
  //   }






  DefineMaterials();
  SetupGeometry();
  fConstructed = true;

  return fWorldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhononDetectorConstruction::DefineMaterials()
{
  G4NistManager* nistManager = G4NistManager::Instance();

  fLiquidHelium = nistManager->FindOrBuildMaterial("G4_AIR"); // to be corrected
  fGermanium = nistManager->FindOrBuildMaterial("G4_Ge");
  fAluminum = nistManager->FindOrBuildMaterial("G4_Al");
  fTungsten = nistManager->FindOrBuildMaterial("G4_W");
  fNiobium = nistManager->FindOrBuildMaterial("G4_Nb");
  fSilicon = nistManager->FindOrBuildMaterial("G4_Si");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhononDetectorConstruction::SetupGeometry()
{
  //
  // World
  //
  G4VSolid* worldSolid = new G4Box("World",16.*cm,16.*cm,16.*cm);
  G4LogicalVolume* worldLogical =
    new G4LogicalVolume(worldSolid,fLiquidHelium,"World");
  worldLogical->SetUserLimits(new G4UserLimits(10*mm, DBL_MAX, DBL_MAX, 0, 0));
  fWorldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"World",0,
                                 false,0);

  //
  // Silicon  cube - this is the volume in which we will propagate phonons
  //

  ////////////Silicon
  G4VSolid *fSiliconSolid  = new G4Box("World",6.25*cm,6.25*cm,.036*cm);//The thickness is 375 micron
  G4LogicalVolume* fSiliconLogical = new G4LogicalVolume(fSiliconSolid,fSilicon,"fSiliconLogical");
  G4VPhysicalVolume* SiPhys =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.0*cm),fSiliconLogical,"fSiliconPhysical",worldLogical,false,0);



  G4double Gap= 0.015*cm;
//  G4VSolid *fGap = new G4Tubs("FGap",0.*cm,0.001*cm+Gap,0.0011*cm,0.*deg, 360.*deg);
  //G4VSolid *fboundary = new G4Box("Fboundary",0.625*cm,0.625*cm,0.001*cm);
  G4ThreeVector T(0.*cm,0.,0.);
  // New Geometry Nb ground plane circles.
   G4VSolid* fNiobiumSolid = new G4Tubs("fNiobiumSolid ",0.075*cm,0.081*cm,0.01*cm, 0.*deg, 360.*deg);//
  //G4VSolid *fNiobiumSolid = new G4SubtractionSolid("Fboundary-FGap",fboundary,fGap,0,T);// This must be 100 microns
  G4LogicalVolume *logicfNiobiumSolid = new G4LogicalVolume(fNiobiumSolid,fNiobium,"logicfNiobiumSolid ");
  G4VPhysicalVolume *physfNiobium = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.076*cm),logicfNiobiumSolid,"physfNiobium",  worldLogical,false,0 );







  // G4VSolid* fGermaniumSolid = new G4Tubs("fGermaniumSolid",0.*cm,0.81*cm,
  //                                        0.27*cm, 0.*deg, 360.*deg);
  // G4LogicalVolume* fGermaniumLogical =
  //   new G4LogicalVolume(fGermaniumSolid,fGermanium,"fGermaniumLogical");
  // G4VPhysicalVolume* GePhys =
  //   new G4PVPlacement(0,G4ThreeVector(),fGermaniumLogical,"fGermaniumPhysical",
  //                     worldLogical,false,0);

  //
  //Germanium lattice information
  //

  // G4LatticeManager gives physics processes access to lattices by volume
  G4LatticeManager* LM = G4LatticeManager::GetLatticeManager();
  G4LatticeLogical* SiLogical = LM->LoadLattice(fSilicon, "Si");

  // G4LatticePhysical assigns G4LatticeLogical a physical orientation
  G4LatticePhysical* SiPhysical = new G4LatticePhysical(SiLogical);
  SiPhysical->SetMillerOrientation(1,0,0);
  LM->RegisterLattice(SiPhys, SiPhysical);

  // NOTE:  Above registration can also be done in single step:
  // G4LatticlePhysical* GePhysical = LM->LoadLattice(GePhys, "Ge");

  //
  // Aluminum - crystal end caps. This is where phonon hits are registered
  //
  G4VSolid* fAluminumSolid = new G4Tubs("aluminiumSolid",0.*cm,0.07*cm,0.01*cm,
                                        0.*deg, 360.*deg);

  G4LogicalVolume* fAluminumLogical =
    new G4LogicalVolume(fAluminumSolid,fAluminum,"fAluminumLogical");
  G4VPhysicalVolume* aluminumTopPhysical = new G4PVPlacement(0,
    G4ThreeVector(0.,0.,0.046*cm), fAluminumLogical, "fAluminumPhysical",
    worldLogical,false,0);
  //G4VPhysicalVolume* aluminumBotPhysical = new G4PVPlacement(0,
  //  G4ThreeVector(0.,0.,-0.09*cm), fAluminumLogical, "fAluminumPhysical",
  //  worldLogical,false,1);

  // G4VisAttributes *visattR;
  // visattR = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  // visattR->SetVisibility(true);
  // fAluminumLogical->SetVisAttributes(visattR);

  // //G4VPhysicalVolume* aluminumTopPhysical = new G4PVPlacement(0,
  //   G4ThreeVector(0.,0.,1.28*cm), fAluminumLogical, "fAluminumPhysical",
  //   worldLogical,false,0);
  // G4VPhysicalVolume* aluminumBotPhysical = new G4PVPlacement(0,
  //   G4ThreeVector(0.,0.,-1.28*cm), fAluminumLogical, "fAluminumPhysical",
  //   worldLogical,false,1);

  //
  // detector -- Note : Aluminum electrode sensitivity is attached to Germanium
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if (!electrodeSensitivity)
    electrodeSensitivity = new PhononSensitivity("PhononElectrode");
      //sensitivity = new ChargeElectrodeSensitivity("ChargeElectrode");
  SDman->AddNewDetector(electrodeSensitivity);
fSiliconLogical->SetSensitiveDetector(electrodeSensitivity);
//fSiliconLogical->SetSensitiveDetector(electrodeSensitivity);

  // Trying to attach Charge Sensitivity





  //
  // surface between Al and Ge determines phonon reflection/absorption

  if (!fConstructed) {
    topSurfProp =new G4CMPSurfaceProperty("TopAlSurf", 1.0, 0.0, 0., 0.,
    1.0, 0.0, 0., 0.);
    // botSurfProp = new G4CMPSurfaceProperty("BotAlSurf", 1., 1., 0., 0.,
    // 0.22, 1., 0., 0.);
   topSurfPropNb = new G4CMPSurfaceProperty("BotNbSurf", 1.0, 1.0, 0.0, 0.0, 0.33, 1.0, 0.0, 0.0);

    wallSurfProp = new G4CMPSurfaceProperty("WallAlSurf", 1.0, 0.0, 0.0, 0.0,
                                                          1.0, 0.0, 0.0, 0.0);
  }

  new G4LogicalBorderSurface("iZIPTop", SiPhys, aluminumTopPhysical,
                                        topSurfProp);
//  new G4LogicalBorderSurface("iZIPBot", SiPhys, aluminumBotPhysical,
                                  //      botSurfProp);
new G4LogicalBorderSurface("iZIPBotNb", SiPhys, physfNiobium ,topSurfPropNb);
  new G4LogicalBorderSurface("iZIPWall", SiPhys, fWorldPhys,
                                        wallSurfProp);

  //
  // Visualization attributes
  //
  worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  fSiliconLogical->SetVisAttributes(simpleBoxVisAtt);
  fAluminumLogical->SetVisAttributes(simpleBoxVisAtt);
}

////////////////////////////////////?Including the Electical Field and ChargeDetectorConstruction////////////////////////////////////
// void PhononDetectorConstruction::AttachField(G4LogicalVolume* lv)
// {
//   if (!fEMField) { // Only create field if one doesn't exist.
//     if (!epotFileName.empty()) {
//       fEMField = new G4CMPMeshElectricField(epotFileName, epotScale);
//     } else {
//       G4double fieldMag = -voltage/zipThickness;
//       fEMField = new G4UniformElectricField(fieldMag*G4ThreeVector(0., 0., 1.));
//     }
//   }
//
//
//
//   // Ensure that logical volume has a field manager attached
//   if (!lv->GetFieldManager()) { // Should always run
//     G4FieldManager* fFieldMgr = new G4CMPFieldManager(fEMField);
//     lv->SetFieldManager(fFieldMgr, true);
//   }
//
//   lv->GetFieldManager()->SetDetectorField(fEMField);
// }
//
//
//
// void PhononDetectorConstruction::AttachSensitivity(G4LogicalVolume *lv)
// {
//   if (!sensitivity) { // Only create detector if one doesn't exist.
//     // NOTE: ChargeElectrodeSensitivity's ctor will call SetOutputFile()
//     sensitivity = new ChargeElectrodeSensitivity("ChargeElectrode");
//   }
//   G4SDManager* SDman = G4SDManager::GetSDMpointer();
//   SDman->AddNewDetector(sensitivity);
//   lv->SetSensitiveDetector(sensitivity);
// }
