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
//
// $Id: DetectorConstruction.cc,v 1.18 2010-10-23 19:27:38 gum Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "MyMaterials.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "math.h"
#include <cmath>



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(const string& configFileName)
{
  readConfigFile(configFileName);

//   G4LogicalSkinSurface::CleanSurfaceTable();
//   G4LogicalBorderSurface::CleanSurfaceTable();
  
  //---------------------------------------
  //------------- Parameters --------------
  //---------------------------------------
  
  initializeMaterials();
  
  expHall_x = expHall_y = expHall_z = 10*m;
  
  crystal_length = 220*mm;
  front_face_size = 28.62*mm;
  rear_face_size = 30.00*mm;

  matrix_pos = 6015 + crystal_length/2;
  hodo_1 = 5;
  hodo_2 = 2525;
  
  startAngle = 0.*deg;
  spanningAngle = 360.*deg;
    
  
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4cout << ">>>>>> DetectorConstruction::Construct()::begin <<<<<<" << G4endl;
  

  // initialize surfaces
    G4LogicalBorderSurface *CrystalSurfaceSkin   	= NULL;
    G4LogicalBorderSurface *CrystalFrontSkin   	= NULL;
    G4OpticalSurface *OpCrystalSurface       		= NULL;
    
  //------------------------------------
  //------------- Volumes --------------
  //------------------------------------
  
  // The experimental Hall
  G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);
  G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box, MyMaterials::Air(), "World", 0, 0, 0);
  G4VPhysicalVolume* expHall_phys = new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World", 0, false, 0);
  
  double alveola_thickness = 0.2*mm;
  
  // solids
  G4Trd* EE_solid = new G4Trd("EE_solid",0.5*front_face_size, 0.5*rear_face_size, 0.5*front_face_size , 0.5*rear_face_size, 0.5*crystal_length);

  G4Trd* EE_solid_big = new G4Trd("EE_solid_big",0.5*(front_face_size + alveola_thickness/2), 0.5*(rear_face_size + alveola_thickness/2), 0.5*(front_face_size + alveola_thickness/2) , 0.5*(rear_face_size+ alveola_thickness/2), 0.5*(crystal_length - 0.5*mm));
  G4SubtractionSolid* EE_solid_alveolar = new G4SubtractionSolid ("EE_solid_alveolar", EE_solid_big, EE_solid);
  
  G4Tubs* Grease_solid = new G4Tubs("Grease_solid", 0, win_r, 0.5*win_l, startAngle, spanningAngle);
  G4Tubs* Win_solid = new G4Tubs("Win_solid", 0, win_r, 0.5*win_l, startAngle, spanningAngle);
 
  G4Tubs* Det_layer_solid = new G4Tubs("Det_layer_solid", 0, win_r, depth*0.5, startAngle, spanningAngle);
  G4Tubs* Det_solid = new G4Tubs("Det_solid", 0, win_r, det_d*0.5, startAngle, spanningAngle);
  
  G4Box* Front_al = new G4Box("Front_al", 0.5*front_face_size, 0.5*front_face_size, 0.5*win_l);
  G4Box* Dead_material = new G4Box("Dead_material", 0.5*front_face_size, 0.5*front_face_size, 3*mm);		// dead material in front of crystal
  
  //plastic scintillator tagging
  G4Box* Plastic_tag = new G4Box("Plastic_tag", 10*mm, 1*mm, 10*mm);
  
  // logical
  G4LogicalVolume* EE_log = new G4LogicalVolume(EE_solid, ScMaterial, "EE_log", 0, 0, 0);
//  G4LogicalVolume* EE_log_alveolar = new G4LogicalVolume(EE_solid_alveolar, MyMaterials::Aluminum(), "EE_log_alveolar", 0, 0, 0);
   G4LogicalVolume* EE_log_alveolar = new G4LogicalVolume(EE_solid_alveolar, MyMaterials::Air(), "EE_log_alveolar", 0, 0, 0);
  
  G4LogicalVolume* Grease_log = new G4LogicalVolume(Grease_solid, MyMaterials::OpticalGrease(), "Grease_log", 0, 0, 0);
  G4LogicalVolume* Win_log = new G4LogicalVolume(Win_solid, WiMaterial, "Win_log", 0, 0, 0);
  
  G4LogicalVolume* Det_layer_log = new G4LogicalVolume(Det_layer_solid, DeMaterial, "Det_layer_log", 0, 0, 0);
  G4LogicalVolume* Det_log = new G4LogicalVolume(Det_solid, DeMaterial, "Det_log", 0, 0, 0);
  
  G4LogicalVolume* Front_al_log = new G4LogicalVolume(Front_al, MyMaterials::Aluminum(), "Front_log", 0, 0, 0);
  G4LogicalVolume* Dead_material_log = new G4LogicalVolume(Dead_material, MyMaterials::Aluminum(), "Dead_material_log", 0, 0, 0);
  
  G4LogicalVolume* Plastic_tag_log = new G4LogicalVolume(Plastic_tag, MyMaterials::Air(), "Plastic_tag_log", 0, 0, 0);

  
      // physical: placement
      G4VPhysicalVolume* EE_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), EE_log, "EE_phys", expHall_log, false, 0);
      G4VPhysicalVolume* EE_alveolar_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), EE_log_alveolar, "EE_alveolar_phys", expHall_log, false, 0);

      G4VPhysicalVolume* Grease_rear_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (crystal_length + win_l)/2) , Grease_log, "Grease_rear_phys", expHall_log, false, 0);
      G4VPhysicalVolume* Win_rear_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (crystal_length + win_l)/2 + win_l), Win_log, "Win_rear_phys", expHall_log, false, 0);

      G4VPhysicalVolume* Det_layer_rear_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (crystal_length + depth)/2 + 2*win_l) , Det_layer_log, "Det_layer_rear_phys", expHall_log, false, 0);
      G4VPhysicalVolume* Det_rear_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (crystal_length  + det_d)/2 + 2*win_l + depth) , Det_log, "Det_rear_phys", expHall_log, false, 0);
      
      //reflective layer on front face and dead material in front of crystal
//       G4VPhysicalVolume* Front_al_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -(crystal_length + win_l)/2) , Front_al_log, "Front_al_phys", expHall_log, false, 0);
//      G4VPhysicalVolume* Dead_material_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -0.15*m) , Dead_material_log, "Dead_material_phys", expHall_log, false, 0);

      // double readout: place photodetector also in front
      G4VPhysicalVolume* Grease_front_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -(crystal_length + win_l)/2) , Grease_log, "Grease_front_phys", expHall_log, false, 0);
      G4VPhysicalVolume* Win_front_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -(crystal_length + win_l)/2 - win_l), Win_log, "Win_front_phys", expHall_log, false, 0);

      G4VPhysicalVolume* Det_layer_front_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -(crystal_length + depth)/2 - 2*win_l) , Det_layer_log, "Det_layer_front_phys", expHall_log, false, 0);
      G4VPhysicalVolume* Det_front_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, -(crystal_length  + det_d)/2 - 2*win_l - depth) , Det_log, "Det_front_phys", expHall_log, false, 0);

      // adding 4 plastic detectors on top of the crystal to tag muons
      double distance = 45*mm;
      G4VPhysicalVolume* Plastic_tag_phys1 = new G4PVPlacement(0, G4ThreeVector(0, distance, -90*mm) , Plastic_tag_log, "Plastic_tag_phys1", expHall_log, false, 0);
      G4VPhysicalVolume* Plastic_tag_phys2 = new G4PVPlacement(0, G4ThreeVector(0, distance, -30*mm) , Plastic_tag_log, "Plastic_tag_phys2", expHall_log, false, 0);
      G4VPhysicalVolume* Plastic_tag_phys3 = new G4PVPlacement(0, G4ThreeVector(0, distance,  30*mm) , Plastic_tag_log, "Plastic_tag_phys3", expHall_log, false, 0);
      G4VPhysicalVolume* Plastic_tag_phys4 = new G4PVPlacement(0, G4ThreeVector(0, distance,  90*mm) , Plastic_tag_log, "Plastic_tag_phys4", expHall_log, false, 0);
    //
    // S U R F A C E S   C O N F I G U R A T I O N
    //

    //CASE 0: CRYSTAL ONLY
    
    if (surConfig == 0) {
        //Nothing - Crystal completely polished
    }

    else if (surConfig == 1) {
        cout << "Configuring a naked crystal, with only wrapping" << endl;
	
        /*-------CRYSTAL SURFACE-------*/
        OpCrystalSurface = new G4OpticalSurface("crystal");

        initializeSurface(OpCrystalSurface, "crystal");
        initializeReflectivitySurface(OpCrystalSurface, "crystal");

        //----INTERNAL WRAPPING----//
	    	    
	    CrystalSurfaceSkin   = new G4LogicalBorderSurface("Lateral", EE_phys, EE_alveolar_phys, OpCrystalSurface);
//    	    CrystalFrontSkin   = new G4LogicalBorderSurface("Front", EE_phys, Front_al_phys, OpCrystalSurface);
    }
      
  //-----------------------------------------------------
  //------------- Visualization attributes --------------
  //-----------------------------------------------------
  
  G4Colour  white   (1.0, 1.0, 1.0) ;  // white
  G4Colour  gray    (0.5, 0.5, 0.5) ;  // gray
  G4Colour  black   (0.0, 0.0, 0.0) ;  // black
  G4Colour  red     (1.0, 0.0, 0.0) ;  // red
  G4Colour  green   (0.0, 1.0, 0.0) ;  // green
  G4Colour  blue    (0.0, 0.0, 1.0) ;  // blue
  G4Colour  cyan    (0.0, 1.0, 1.0) ;  // cyan
  G4Colour  magenta (1.0, 0.0, 1.0) ;  // magenta 
  G4Colour  yellow  (1.0, 1.0, 0.0) ;  // yellow
  G4Colour  brass   (0.8, 0.6, 0.4) ;  // brass
  G4Colour  brown   (0.7, 0.4, 0.1) ;  // brass
  
  G4VisAttributes* VisAttWorld = new G4VisAttributes(white);
  VisAttWorld->SetVisibility(true);
  VisAttWorld->SetForceWireframe(true);
  expHall_log->SetVisAttributes(VisAttWorld);
  
  G4VisAttributes* VisAttAbs = new G4VisAttributes(brass);
  VisAttAbs->SetVisibility(true);
  VisAttAbs->SetForceWireframe(true);
  EE_log->SetVisAttributes(VisAttAbs);
  
  G4VisAttributes* VisAttCrystal = new G4VisAttributes(green);
  VisAttCrystal->SetVisibility(true);
  VisAttCrystal->SetForceWireframe(true);
  EE_log->SetVisAttributes(VisAttCrystal);
  
  G4VisAttributes* VisAttWindow = new G4VisAttributes(blue);
  VisAttWindow->SetVisibility(true);
  VisAttWindow->SetForceWireframe(true);
  Win_log->SetVisAttributes(VisAttWindow);
  
  G4VisAttributes* VisAttDetLayer = new G4VisAttributes(red);
  VisAttDetLayer->SetVisibility(true);
  VisAttDetLayer->SetForceWireframe(false);
  Det_layer_log->SetVisAttributes(VisAttDetLayer);
 
  G4VisAttributes* VisAttDetector = new G4VisAttributes(gray);
  VisAttDetector->SetVisibility(true);
  VisAttDetector->SetForceWireframe(false);
  Det_log->SetVisAttributes(VisAttDetector);

  G4VisAttributes* VisAttAlveolar = new G4VisAttributes(yellow);
  VisAttAlveolar->SetVisibility(true);
  VisAttAlveolar->SetForceWireframe(true);
  EE_log_alveolar->SetVisAttributes(VisAttAlveolar);
  

//   G4VisAttributes* VisAttAlveolar = new G4VisAttributes(yellow);
//   VisAttAlveolar->SetVisibility(true);
//   VisAttAlveolar->SetForceWireframe(true);
//   EE_log_alveolar->SetVisAttributes(VisAttAlveolar);
  
  
  G4cout << ">>>>>> DetectorConstruction::Construct()::end <<< " << G4endl;
  return expHall_phys;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::readConfigFile(string configFileName)
{	
  ConfigFile config(configFileName);
  
  config.readInto(crystal_material,"crystal_material");
  config.readInto(crystal_risetime,"crystal_risetime");
  config.readInto(crystal_abslength,"crystal_abslength");
  config.readInto(crystal_lightyield,"crystal_lightyield");
  
  config.readInto(crystal_length,"crystal_length");
  config.readInto(front_face_size,"front_face_size");
  config.readInto(rear_face_size,"rear_face_size");
  config.readInto(abs_material,"abs_material");
  config.readInto(surConfig, "surConfig");
  config.readInto(cReffile, "cReffile");
  config.readInto(crystal_reflectivity, "cReflectivity");
  config.readInto(cSurrefind, "cSurrefind");
  config.readInto(cSurtype, "cSurtype");
  config.readInto(cSpecularspike, "cSpecularspike");
  config.readInto(cSpecularlobe, "cSpecularlobe");
  config.readInto(cSigmaalpha, "cSigmaalpha");
  config.readInto(cSpecularspike, "cSpecularspike");
  config.readInto(cSpecularlobe, "cSpecularlobe");
  config.readInto(cSigmaalpha, "cSigmaalpha");
  config.readInto(cBackscatter, "cBackscatter");
  config.readInto(cLambertian, "cLambertian");
  config.readInto(crystalSurfinish, "crystalSurfinish");
  
  config.readInto(win_r,"win_r");
  config.readInto(win_l,"win_l");
  config.readInto(win_material,"win_material");
  
  config.readInto(det_d,"det_d");
  config.readInto(det_distance,"det_distance");
  config.readInto(det_material,"det_material");
  
  config.readInto(depth,"depth");
  config.readInto(mu_ind,"mu_ind");
  
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::initializeMaterials()
{
  // define materials
  
  AbMaterial = NULL;
  if( abs_material == 1 ) AbMaterial = MyMaterials::Brass();
  else if( abs_material == 2 ) AbMaterial = MyMaterials::Tungsten();
  else
  {
    G4cerr << "<DetectorConstructioninitializeMaterials>: Invalid absorber material specifier " << abs_material << G4endl;
    exit(-1);
  }
  G4cout << "Ab. material: "<< AbMaterial << G4endl;
  
  ScMaterial = NULL;
  if     ( crystal_material == 1 ) ScMaterial = MyMaterials::LSO();
  else if( crystal_material == 2 ) ScMaterial = MyMaterials::LYSO();
  else if( crystal_material == 3 ) ScMaterial = MyMaterials::LuAG_Ce();  
  else if( crystal_material == 4 ) ScMaterial = MyMaterials::LuAG_Pr();
  else if( crystal_material == 5 ) ScMaterial = MyMaterials::PWO(mu_ind);
  else if( crystal_material == 6 ) ScMaterial = MyMaterials::Air();
  else if( crystal_material == 7 ) ScMaterial = MyMaterials::Quartz();
  else if( crystal_material == 8 ) ScMaterial = MyMaterials::DSBCe();
  else if( crystal_material == 9 ) ScMaterial = MyMaterials::SiO2Ce();
  else
  {
    G4cerr << "<DetectorConstructioninitializeMaterials>: Invalid crystal material specifier " << crystal_material << G4endl;
    exit(-1);
  }
  G4cout << "Sc. material: "<< ScMaterial << G4endl;
  
  
  WiMaterial = NULL;
  if( win_material == 1 ) WiMaterial = MyMaterials::Quartz();
  else
  {
    G4cerr << "<DetectorConstructioninitializeMaterials>: Invalid window material specifier " << win_material << G4endl;
    exit(-1);
  }
  G4cout << "Window material: " << win_material << G4endl;
  
  
  DeMaterial = NULL;
  if( det_material == 1 ) DeMaterial = MyMaterials::Silicon();
  else
  {
    G4cerr << "<DetectorConstructioninitializeMaterials>: Invalid detector material specifier " << det_material << G4endl;
    exit(-1);
  }
  G4cout << "Detector material: " << det_material << G4endl;	
  
  
  
  // modify default properties of the scintillator
  if( crystal_lightyield >= 0 )
  {
    ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("SCINTILLATIONYIELD");
    ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("SCINTILLATIONYIELD",crystal_lightyield/MeV);  
  } 
  
  if( crystal_risetime >= 0 )
  {
    ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("FASTSCINTILLATIONRISETIME");
    ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("FASTSCINTILLATIONRISETIME",crystal_risetime/ns);  
  } 
  
  if( crystal_abslength >= 0 ) 
  {
    ScMaterial->GetMaterialPropertiesTable()->RemoveProperty("ABSLENGTH");
    ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("ABSLENGTH",crystal_abslength);  
  } 
  else 
  {
    for(unsigned int j = 0; j < ScMaterial->GetMaterialPropertiesTable()->GetProperty("ABSLENGTH")->GetVectorLength();++j)
    {
      ScMaterial->GetMaterialPropertiesTable()->GetProperty("ABSLENGTH")->Energy(j);
    }
  }
}


// Initialization classes
//
void DetectorConstruction::initializeSurface(G4OpticalSurface *mySurface, string surfaceType)
{
    if(surfaceType == "crystal") {
//         cout << "CRISTALLO " << crystalSurfinish << endl;
        surfinish   = crystalSurfinish;
        RefFile     = cReffile;
        reflectivity    = cReflectivity;
        surrefind   = cSurrefind;
        surtype     = cSurtype;
        specularspike   = cSpecularspike;
        specularlobe    = cSpecularlobe;
        sigmaalpha  = cSigmaalpha;
        backscatter     = cBackscatter;
        lambertian  = cLambertian;
    }



    if(this->surfinish <= 5)
    {
        G4cout << "Using unified model." << G4endl;
        mySurface -> SetModel(unified);
        switch(this->surtype) {
        case 0:
            mySurface -> SetType(dielectric_metal);
            G4cout << "Surface type: dielectric_metal" << G4endl;
            break;
        case 1:
            mySurface -> SetType(dielectric_dielectric);
            G4cout << "Surface type: dielectric_dielectric" << G4endl;
            break;
        }
    }

    else if(this->surfinish > 5 && surfaceType == "wrapping") G4cout << "Value not allowed" << G4endl;

    else {
        G4cout << "Using LUT for surface treatment." << G4endl;
        mySurface -> SetModel(LUT);
        mySurface -> SetType(dielectric_LUT);
    }

    switch(this->surfinish) {
    case 0:
        mySurface -> SetFinish(polished);
        G4cout << "Surface finish: polished" << G4endl;
        break;
    case 1:
        mySurface -> SetFinish(polishedfrontpainted);
        G4cout << "Surface finish: polishedfrontpainted" << G4endl;
        break;
    case 2:
        mySurface -> SetFinish(polishedbackpainted);
        G4cout << "Surface finish: polishedbackpainted" << G4endl;
        break;
    case 3:
        mySurface -> SetFinish(ground);
        G4cout << "Surface finish: ground" << G4endl;
        break;
    case 4:
        mySurface -> SetFinish(groundfrontpainted);
        G4cout << "Surface finish: groundfrontpainted" << G4endl;
        break;
    case 5:
        mySurface -> SetFinish(groundbackpainted);
        G4cout << "Surface finish: groundbackpainted" << G4endl;
        break;
    case 17:
        mySurface -> SetFinish(polishedteflonair);
        G4cout << "Surface finish: polishedteflonair" << G4endl;
        break;
    case 18:
        mySurface -> SetFinish(polishedtioair);
        G4cout << "Surface finish: polishedtioair" << G4endl;
        break;
    case 26:
        mySurface -> SetFinish(etchedtioair);
        G4cout << "Surface finish: etchedtioair" << G4endl;
        break;
    case 34:
        mySurface -> SetFinish(groundtioair);
        G4cout << "Surface finish: groundtioair" << G4endl;
        break;
    case 36:
        mySurface -> SetFinish(polishedtyvekair);
        G4cout << "Surface finish: polishedtyvekair" << G4endl;
        break;
    default:
        G4cout << "Surface finish unkown!" << G4endl;
        exit(0);
    }
}


//
// reflectivity
//
void DetectorConstruction::initializeReflectivitySurface(G4OpticalSurface *surface, string surfaceType)
{

    int NumRefl = 0;
    G4double EphotonRefl[1000];
    G4double Refl[1000];
    
//     if(this->RefFile != 0) {
//         ifstream myReadFile;
//         myReadFile.open(this->RefFile);
// 
//         G4cout << "Reflectivities read from file:" << G4endl;
//         if(myReadFile.is_open()) {
//             while(!myReadFile.eof()) {
//                 myReadFile >> EphotonRefl[NumRefl];
//                 if(EphotonRefl[NumRefl] == -1) break;
//                 myReadFile >> Refl[NumRefl];
//                 // convert to energy (1eV corresponds to 1239.8 nm: energy [eV]= 1239.8nmeV/lambda[nm])
//                 EphotonRefl[NumRefl] = 1239.8 / EphotonRefl[NumRefl] * eV;
//                 NumRefl++;
//             }
//         }
// 
//         else {
//             G4cerr << "<DetectorConstruction> : Could not read file with reflectivities!" << G4endl;
//             exit(0);
//         }
//         myReadFile.close();
//     }

//     else {
        EphotonRefl[0] = 0.0001 * eV;
        EphotonRefl[1] = 1.0 * eV;
        EphotonRefl[2] = 4.08 * eV;
        Refl[0] = 0.0; // suppress photons with energy < 1eV (will not be detected)
        Refl[1] = this->crystal_reflectivity;
        Refl[2] = this->crystal_reflectivity;
        NumRefl = 100;


//     }
    G4cout << "Reflectivities as a function of the photon energy:" << G4endl;
    for(int i = 0; i < NumRefl; i++) {
        G4cout << i << "   " << EphotonRefl[i] << "   " << Refl[i] << G4endl;
    }




    Ephoton[0] = 0.0001 * eV;
    Ephoton[1] = 1.0 * eV;
    Ephoton[2] = 4.08 * eV;
    G4double RefractiveIndex[3] = {this->surrefind, this->surrefind, this->surrefind};
    G4double SpecularLobe[3]    = {this->specularlobe, this->specularlobe, this->specularlobe};
    G4double SpecularSpike[3]   = {this->specularspike, this->specularspike, this->specularspike};
    G4double Backscatter[3]     = {this->backscatter, this->backscatter, this->backscatter};
    G4double Lambertian[3]      = {this->lambertian, this->lambertian, this->lambertian};
    G4MaterialPropertiesTable *myST = new G4MaterialPropertiesTable();
    G4cout << "Read from config-file: " << G4endl;
    G4cout << "Read SPECULARLOBECONSTANT  : " << SpecularLobe[0] << G4endl;
    G4cout << "Read SPECULARSPIKECONSTANT : " << SpecularSpike[0] << G4endl;
    G4cout << "Read BACKSCATTERCONSTANT   : " << Backscatter[0] << G4endl;
    G4cout << "Read LAMBERTIAN            : " << Lambertian[0] << G4endl;
    G4cout << "Read ref. index            : " << RefractiveIndex[0] << G4endl;

    myST->AddProperty("RINDEX", Ephoton, RefractiveIndex, 3);
    if(this->specularlobe >= 0) {
        G4cout << "Setting SPECULARLOBECONSTANT to : " << SpecularLobe[0] << G4endl;
        myST->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    3);
    }
    if(this->specularspike >= 0) {
        G4cout << "Setting SPECULARSPIKECONSTANT to : " << SpecularSpike[0] << G4endl;
        myST->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   3);
    }
    if(this->backscatter >= 0) {
        G4cout << "Setting BACKSCATTERCONSTANT to : " << Backscatter[0] << G4endl;
        myST->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     3);
    }
    if(this->lambertian >= 0) {
        G4cout << "Setting LAMBERTIAN to : " << Lambertian[0] << G4endl;
        myST->AddProperty("LAMBERTIAN",            Ephoton, Lambertian,      3);
    }

//     setWrappingIndices(myST,1.82,"teflon");

    surface->SetMaterialPropertiesTable(myST);
    if(this->sigmaalpha >= 0) surface->SetSigmaAlpha(this->sigmaalpha);


}
