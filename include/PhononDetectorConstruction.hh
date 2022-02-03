/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/include/PhononDetectorConstruction.hh
/// \brief Definition of the PhononDetectorConstruction class
//
// $Id: 4c06153e9ea08f2a90b22c53e5c39bde4b847c07 $
//

#ifndef PhononDetectorConstruction_h
#define PhononDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
//class ChargeElectrodeSensitivity;
class G4Material;
class G4VPhysicalVolume;
class G4CMPSurfaceProperty;
class G4CMPElectrodeSensitivity;
class G4ElectricField;
class PhononDetectorConstruction : public G4VUserDetectorConstruction {
public:
  PhononDetectorConstruction();
  virtual ~PhononDetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();

private:
  void DefineMaterials();
  void SetupGeometry();
  void AttachField(G4LogicalVolume* lv);

  void AttachSensitivity(G4LogicalVolume* lv);


private:
  //ChargeElectrodeSensitivity *sensitivity;
  G4Material* fLiquidHelium;
  G4Material* fGermanium;
  G4Material* fSilicon;
  G4Material* fAluminum;
  G4Material*fNiobium;
  G4Material* fTungsten;
  G4VPhysicalVolume* fWorldPhys;
  G4CMPSurfaceProperty* topSurfProp;
  G4CMPSurfaceProperty *topSurfPropNb;
  G4CMPSurfaceProperty* botSurfProp;
  G4CMPSurfaceProperty* wallSurfProp;
  G4CMPElectrodeSensitivity* electrodeSensitivity;
  //  G4CMPElectrodeSensitivity* sensitivity;
   G4bool fConstructed;
   G4bool fIfField;
  // G4double zipThickness; // Useful for geom. and field
  // G4double epotScale;
  // G4double voltage;
  // G4bool constructed;
  // G4String epotFileName;
  // G4String outputFileName;
  // G4ElectricField* fEMField;

public:
  inline void Field(G4bool bl) { fIfField = bl; }
};

#endif
