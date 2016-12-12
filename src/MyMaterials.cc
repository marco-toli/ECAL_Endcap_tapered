

#include "MyMaterials.hh"
#include "G4NistManager.hh"
#include "TF1.h"
#include "TH1F.h"



MyMaterials::MyMaterials()
{}



MyMaterials::~MyMaterials()
{}



G4Material* MyMaterials::Air()
{
  G4double a, z, density;
  G4int nelements;
  
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  
  G4Material* mat = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  mat->AddElement(N, 70.*perCent);
  mat->AddElement(O, 30.*perCent);
  
  const G4int nEntries = 34;
  G4double PhotonEnergy[nEntries] =
    { 0.0001*eV, 1.0000*eV, 2.0340*eV, 2.0680*eV,
      2.1030*eV, 2.1390*eV, 2.1770*eV, 2.2160*eV,
      2.2560*eV, 2.2980*eV, 2.3410*eV, 2.3860*eV,
      2.4330*eV, 2.4810*eV, 2.5320*eV, 2.5850*eV,
      2.6400*eV, 2.6970*eV, 2.7570*eV, 2.8200*eV,
      2.8850*eV, 2.9540*eV, 3.0260*eV, 3.1020*eV,
      3.1810*eV, 3.2650*eV, 3.3530*eV, 3.4460*eV,
      3.5450*eV, 3.6490*eV, 3.7600*eV, 3.8770*eV,
      4.0020*eV, 4.1360*eV };
  G4double RefractiveIndex[nEntries] =
    { 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00 };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX",PhotonEnergy,RefractiveIndex,nEntries);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::Water()
{
  G4double a, z, density;
  G4int nelements;
  
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  
  G4Material* mat = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  mat->AddElement(H, 2);
  mat->AddElement(O, 1);
  
  const G4int nEntries = 33;
  G4double PhotonEnergy[nEntries] =
    { 0.100*eV, 2.034*eV, 2.068*eV, 2.103*eV,
      2.139*eV, 2.177*eV, 2.216*eV, 2.256*eV,
      2.298*eV, 2.341*eV, 2.386*eV, 2.433*eV,
      2.481*eV, 2.532*eV, 2.585*eV, 2.640*eV,
      2.697*eV, 2.757*eV, 2.820*eV, 2.885*eV,
      2.954*eV, 3.026*eV, 3.102*eV, 3.181*eV,
      3.265*eV, 3.353*eV, 3.446*eV, 3.545*eV,
      3.649*eV, 3.760*eV, 3.877*eV, 4.002*eV,
      4.136*eV };
  G4double RefractiveIndex[nEntries] =
    { 1.3435, 1.3435, 1.3440, 1.3445,
      1.3450, 1.3455, 1.3460, 1.3465,
      1.3470, 1.3475, 1.3480, 1.3485,
      1.3492, 1.3500, 1.3505, 1.3510,
      1.3518, 1.3522, 1.3530, 1.3535,
      1.3540, 1.3545, 1.3550, 1.3555,
      1.3560, 1.3568, 1.3572, 1.3580,
      1.3585, 1.3590, 1.3595, 1.3600,
      1.3608};
  G4double Absorption[nEntries] =
    {  3.448*m,  3.448*m,  4.082*m,  6.329*m,
       9.174*m, 12.346*m, 13.889*m, 15.152*m,
      17.241*m, 18.868*m, 20.000*m, 26.316*m,
      35.714*m, 45.455*m, 47.619*m, 52.632*m,
      52.632*m, 55.556*m, 52.632*m, 52.632*m,
      47.619*m, 45.455*m, 41.667*m, 37.037*m,
      33.333*m, 30.000*m, 28.500*m, 27.000*m,
      24.500*m, 22.000*m, 19.500*m, 17.500*m,
      14.500*m };
  G4double FastComponent[nEntries] =
    { 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00 };
  G4double SlowComponent[nEntries] =
    { 0.01, 0.01, 1.00, 2.00,
      3.00, 4.00, 5.00, 6.00,
      7.00, 8.00, 9.00, 8.00,
      7.00, 6.00, 4.00, 3.00,
      2.00, 1.00, 0.01, 1.00,
      2.00, 3.00, 4.00, 5.00,
      6.00, 7.00, 8.00, 9.00,
      8.00, 7.00, 6.00, 5.00,
      4.00 };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX",        PhotonEnergy, RefractiveIndex, nEntries);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy, Absorption,      nEntries);
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy, FastComponent,   nEntries);
  myMPT->AddProperty("SLOWCOMPONENT", PhotonEnergy, SlowComponent,   nEntries);
  
  myMPT->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  //myMPT->AddConstProperty("ELECTRONSCINTILLATIONYIELD",50./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT->AddConstProperty("YIELDRATIO",0.8);
  
  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}



G4Material* MyMaterials::Vacuum()
{
  G4double a, z, density;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  
  G4Material* mat = new G4Material("Vacuum", density=0.001*mg/cm3, nelements=2);
  mat->AddElement(N, 70.*perCent);
  mat->AddElement(O, 30.*perCent);
  
  const G4int nEntries = 3;
  G4double PhotonEnergy[nEntries] =
    { 0.0001*eV, 1.00*eV,100.00*eV };
  G4double RefractiveIndex[nEntries] =
    { 1.00, 1.00, 1.00 };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}

G4Material* MyMaterials::Aluminum () 
{
  G4double a, z, density;
  density = 2.700*g/cm3;
  a = 26.98*g/mole;
  
  G4Material* mat = new G4Material("Aluminum", z=13., a, density);
  return mat;
}



G4Material* MyMaterials::Silicon()
{
  G4double a, z, density;
  
  G4Element* Si = new G4Element("Silicon", "Si", z=14., a=28.09*g/mole);
  
  G4Material* mat = new G4Material("Silicon", density=2.33*g/cm3,1);
  mat->AddElement(Si,1);
  
  const G4int nEntries = 4;
  G4double PhotonEnergy[nEntries] =
    { 0.0001*eV, 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries] =
    { 4.0, 4.0, 4.0, 4.0 };
  G4double Absorption[nEntries] =
    { 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm};
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX",    PhotonEnergy,  RefractiveIndex, nEntries);
  myMPT->AddProperty("ABSLENGTH", PhotonEnergy,  Absorption,      nEntries);
  
  mat->SetMaterialPropertiesTable(myMPT);

  return mat;
}



G4Material* MyMaterials::Quartz()
{
  G4double a, z, density;
  
  G4Element* Si = new G4Element("Silicon", "Si", z = 14., a = 28.09* g/mole);
  G4Element* O  = new G4Element("Oxygen",  "O",  z =  8., a = 16.00* g/mole);
  
  G4Material* mat = new G4Material ("Quartz", density = 2.2*g/cm3,2);
  mat->AddElement(Si,1);
  mat->AddElement(O,2);
  
  const G4int nEntries_RI = 11;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV,
      3.5 * eV, 4.0 * eV, 4.5 * eV, 5.0 * eV,
      5.5 * eV, 6.0 * eV, 6.26 * eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.53, 1.54, 1.55, 1.56,
      1.56, 1.57, 1.59, 1.60,
      1.62, 1.64, 1.65 };
  
  const G4int nEntries_ABS = 4;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV };
  G4double Absorption[nEntries_ABS] =
    { 138.*mm, 138.*mm, 138.*mm, 138. *mm };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty ("RINDEX",    PhotonEnergy_RI,  RefractiveIndex, nEntries_RI);
  myMPT->AddProperty ("ABSLENGTH", PhotonEnergy_ABS, Absorption,      nEntries_ABS);
  
  mat->SetMaterialPropertiesTable (myMPT);
  
  return mat;
}

G4Material* MyMaterials::SiO2Ce()
{
  G4double a, z, density;

  G4Element* Si = new G4Element("Silicon", "Si", z = 14., a = 28.09* g/mole);
  G4Element* O  = new G4Element("Oxygen",  "O",  z =  8., a = 16.00* g/mole);

  G4Material* mat = new G4Material ("SiO2Ce", density = 2.65*g/cm3,2);
  mat->AddElement(Si,1);
  mat->AddElement(O,2);

  const G4int nEntries_RI = 11;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0 * eV, 2.0 * eV, 2.5 * eV, 3.0 * eV,
      3.5 * eV, 4.0 * eV, 4.5 * eV, 5.0 * eV,
      5.5 * eV, 6.0 * eV, 6.26 * eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.53, 1.54, 1.55, 1.56,
      1.56, 1.57, 1.59, 1.60,
      1.62, 1.64, 1.65 };

  const G4int nEntries_ABS = 4;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.0 * eV, 1.84 * eV, 4.08 * eV, 6.26 * eV };
  G4double Absorption[nEntries_ABS] =
    { 138.*mm, 138.*mm, 138.*mm, 138. *mm };

  const G4int NUMENTRIES_1 = 5;
  G4double FAST_Energy[NUMENTRIES_1]    = {1.8*eV,1.90*eV,2.7*eV,2.88*eV,4.08*eV};
  G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00,1.00,2.0,1.0,0.00};

  G4MaterialPropertiesTable* mt = new G4MaterialPropertiesTable();
  mt->AddProperty ("RINDEX",    PhotonEnergy_RI,  RefractiveIndex, nEntries_RI);
  mt->AddProperty ("ABSLENGTH", PhotonEnergy_ABS, Absorption,      nEntries_ABS);
  mt->AddProperty("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);

  mt->AddConstProperty("SCINTILLATIONYIELD",1800/MeV);
  mt->AddConstProperty("RESOLUTIONSCALE",8.5);
  mt->AddConstProperty("FASTTIMECONSTANT",55.*ns);
  mt->AddConstProperty("YIELDRATIO",1.0);
  mt->AddConstProperty("FASTSCINTILLATIONRISETIME",0.5*ns);

  mat->SetMaterialPropertiesTable(mt);
  return mat;
}



G4Material* MyMaterials::Brass()
{
  G4double a, z, density;

  G4Element* Cu = new G4Element("Copper", "Cu", z=29., a=63.546*g/mole);
  G4Element* Zn = new G4Element("Zinc",   "Zn", z=30., a=65.409*g/mole);
  
  G4Material* mat = new G4Material("Brass", density=8.73*g/cm3,2);
  mat->AddElement(Cu,0.75);
  mat->AddElement(Zn,0.25);
  
  return mat;
}


G4Material* MyMaterials::Tungsten()
{
  //   G4Element* Cu = new G4Element("Copper", "Cu", z=29., a=63.546*g/mole);
  G4NistManager* man = G4NistManager::Instance();
  G4Element* W = man->FindOrBuildElement("W");
  G4Element* Ni = man->FindOrBuildElement("Ni");
  G4Element* Cu = man->FindOrBuildElement("Cu");

  G4Material* mat = new G4Material("Tungsten", 17.*g/cm3,3);
  mat->AddElement(W,90.*perCent);
  mat->AddElement(Ni,5.*perCent);
  mat->AddElement(Cu,5.*perCent);
  return mat;
}

  


G4Material* MyMaterials::OpticalGrease()
{
  G4double a, z, density;
  G4Element* H = new G4Element("Hydrogen", "H", z=1., a= 1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a=16.00*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6., a=12.01*g/mole);

  G4Material* mat = new G4Material("Grease", density=1.0*g/cm3,3);
  mat->AddElement(C,1);
  mat->AddElement(H,1);
  mat->AddElement(O,1);

  const G4int nEntries = 34;
  G4double PhotonEnergy[nEntries] =
    { 0.0001*eV, 1.000*eV, 2.034*eV, 2.068*eV,
       2.103*eV, 2.139*eV, 2.177*eV, 2.216*eV,
       2.256*eV, 2.298*eV, 2.341*eV, 2.386*eV,
       2.433*eV, 2.481*eV, 2.532*eV, 2.585*eV,
       2.640*eV, 2.697*eV, 2.757*eV, 2.820*eV,
       2.885*eV, 2.954*eV, 3.026*eV, 3.102*eV,
       3.181*eV, 3.265*eV, 3.353*eV, 3.446*eV,
       3.545*eV, 3.649*eV, 3.760*eV, 3.877*eV,
       4.002*eV, 4.136*eV };
  G4double RefractiveIndex[nEntries] =
    { 1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45, 1.45, 1.45,
      1.45, 1.45 };

  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX",    PhotonEnergy, RefractiveIndex, nEntries);
  //myMPT->AddProperty("ABSLENGTH", PhotonEnergy, Absorption,      nEntries);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}

G4Material* MyMaterials::DSBCe()  // Nanostructured glass ceramics scintillator DSB:Ce
{
  G4double a, z, density;
  G4Element*  DSB_glass = new G4Element("DSB_glass",    "DSB",   z=51,  a=124.00*g/mole);

  G4Material* mat = new G4Material("DSB", density=4*g/cm3,1);
  mat->AddElement(DSB_glass,1);

  // large band between 470 (2.64 eV) and 630 nm (1.97 eV) (mean 535 nm, 2.32)
  const G4int NUMENTRIES_1 = 5;
  G4double FAST_Energy[NUMENTRIES_1]    = {1.8*eV,1.90*eV,2.7*eV,2.88*eV,4.08*eV};
  G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00,1.00,2.0,1.0,0.00};


  const G4int NUMENTRIES_2 = 3;
  G4double RIND_Energy[NUMENTRIES_2]    = { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RIND_INDEX[NUMENTRIES_2]     = { 1.5, 1.5, 1.5 };
  G4double ABS_Energy[NUMENTRIES_2]     = { 1.0*eV, 1.84*eV, 4.08*eV };
  //G4double ABS_LENGTH[NUMENTRIES_2]     = { 50.*m, 50.*m, 50.*m};
  G4double ABS_LENGTH[NUMENTRIES_2]       = { 500.*mm, 500.*mm, 500.*mm };	//138 original
//   G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

  G4MaterialPropertiesTable* mt = new G4MaterialPropertiesTable();
  mt->AddProperty("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
  mt->AddProperty("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
  mt->AddProperty("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
//   mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);

  mt->AddConstProperty("SCINTILLATIONYIELD",1800/MeV);
  mt->AddConstProperty("RESOLUTIONSCALE",8.5);
  mt->AddConstProperty("FASTTIMECONSTANT",50.*ns);
  mt->AddConstProperty("YIELDRATIO",1.0);
  mt->AddConstProperty("FASTSCINTILLATIONRISETIME",0.5*ns);

  mat->SetMaterialPropertiesTable(mt);
  return mat;
}



G4Material* MyMaterials::LuAG_Ce() // Lutetium Aluminum Garnet - Ce-doped
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z=8.,  a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Al = new G4Element("Aluminum", "Al", z=27., a= 28.09*g/mole);
  
  G4Material* mat = new G4Material("LuAG_Ce", density=6.7*g/cm3,3);
  mat->AddElement(Lu,3);
  mat->AddElement(Al,12);
  mat->AddElement(O,5);
  
  const G4int nEntries_FAST = 458;
  G4double PhotonEnergy_FAST[nEntries_FAST] =
    { 1.82487*eV, 1.82622*eV, 1.82756*eV, 1.82891*eV, 1.83026*eV, 1.83161*eV, 1.83296*eV, 1.83432*eV, 1.83568*eV, 1.83704*eV,
      1.8384*eV, 1.83976*eV, 1.84113*eV, 1.8425*eV, 1.84387*eV, 1.84524*eV, 1.84661*eV, 1.84799*eV, 1.84937*eV, 1.85075*eV,
      1.85213*eV, 1.85351*eV, 1.8549*eV, 1.85629*eV, 1.85768*eV, 1.85907*eV, 1.86047*eV, 1.86186*eV, 1.86326*eV, 1.86466*eV,
      1.86606*eV, 1.86747*eV, 1.86888*eV, 1.87029*eV, 1.8717*eV, 1.87311*eV, 1.87453*eV, 1.87595*eV, 1.87737*eV, 1.87879*eV,
      1.88021*eV, 1.88164*eV, 1.88307*eV, 1.8845*eV, 1.88593*eV, 1.88737*eV, 1.8888*eV, 1.89024*eV, 1.89169*eV, 1.89313*eV,
      1.89458*eV, 1.89602*eV, 1.89748*eV, 1.89893*eV, 1.90038*eV, 1.90184*eV, 1.9033*eV, 1.90476*eV, 1.90623*eV, 1.90769*eV,
      1.90916*eV, 1.91063*eV, 1.9121*eV, 1.91358*eV, 1.91506*eV, 1.91654*eV, 1.91802*eV, 1.9195*eV, 1.92099*eV, 1.92248*eV,
      1.92397*eV, 1.92547*eV, 1.92696*eV, 1.92846*eV, 1.92996*eV, 1.93146*eV, 1.93297*eV, 1.93448*eV, 1.93599*eV, 1.9375*eV,
      1.93901*eV, 1.94053*eV, 1.94205*eV, 1.94357*eV, 1.9451*eV, 1.94662*eV, 1.94815*eV, 1.94969*eV, 1.95122*eV, 1.95276*eV,
      1.95429*eV, 1.95584*eV, 1.95738*eV, 1.95893*eV, 1.96047*eV, 1.96203*eV, 1.96358*eV, 1.96513*eV, 1.96669*eV, 1.96825*eV,
      1.96982*eV, 1.97138*eV, 1.97295*eV, 1.97452*eV, 1.9761*eV, 1.97767*eV, 1.97925*eV, 1.98083*eV, 1.98241*eV, 1.984*eV,
      1.98559*eV, 1.98718*eV, 1.98877*eV, 1.99037*eV, 1.99197*eV, 1.99357*eV, 1.99517*eV, 1.99678*eV, 1.99839*eV, 2*eV,
      2.00161*eV, 2.00323*eV, 2.00485*eV, 2.00647*eV, 2.0081*eV, 2.00972*eV, 2.01135*eV, 2.01299*eV, 2.01462*eV, 2.01626*eV,
      2.0179*eV, 2.01954*eV, 2.02119*eV, 2.02284*eV, 2.02449*eV, 2.02614*eV, 2.0278*eV, 2.02946*eV, 2.03112*eV, 2.03279*eV,
      2.03445*eV, 2.03612*eV, 2.0378*eV, 2.03947*eV, 2.04115*eV, 2.04283*eV, 2.04452*eV, 2.0462*eV, 2.04789*eV, 2.04959*eV,
      2.05128*eV, 2.05298*eV, 2.05468*eV, 2.05638*eV, 2.05809*eV, 2.0598*eV, 2.06151*eV, 2.06323*eV, 2.06495*eV, 2.06667*eV,
      2.06839*eV, 2.07012*eV, 2.07185*eV, 2.07358*eV, 2.07531*eV, 2.07705*eV, 2.07879*eV, 2.08054*eV, 2.08228*eV, 2.08403*eV,
      2.08579*eV, 2.08754*eV, 2.0893*eV, 2.09106*eV, 2.09283*eV, 2.09459*eV, 2.09637*eV, 2.09814*eV, 2.09992*eV, 2.10169*eV,
      2.10348*eV, 2.10526*eV, 2.10705*eV, 2.10884*eV, 2.11064*eV, 2.11244*eV, 2.11424*eV, 2.11604*eV, 2.11785*eV, 2.11966*eV,
      2.12147*eV, 2.12329*eV, 2.12511*eV, 2.12693*eV, 2.12876*eV, 2.13058*eV, 2.13242*eV, 2.13425*eV, 2.13609*eV, 2.13793*eV,
      2.13978*eV, 2.14162*eV, 2.14347*eV, 2.14533*eV, 2.14719*eV, 2.14905*eV, 2.15091*eV, 2.15278*eV, 2.15465*eV, 2.15652*eV,
      2.1584*eV, 2.16028*eV, 2.16216*eV, 2.16405*eV, 2.16594*eV, 2.16783*eV, 2.16973*eV, 2.17163*eV, 2.17353*eV, 2.17544*eV,
      2.17735*eV, 2.17926*eV, 2.18118*eV, 2.1831*eV, 2.18502*eV, 2.18695*eV, 2.18888*eV, 2.19081*eV, 2.19275*eV, 2.19469*eV,
      2.19663*eV, 2.19858*eV, 2.20053*eV, 2.20249*eV, 2.20444*eV, 2.20641*eV, 2.20837*eV, 2.21034*eV, 2.21231*eV, 2.21429*eV,
      2.21626*eV, 2.21825*eV, 2.22023*eV, 2.22222*eV, 2.22422*eV, 2.22621*eV, 2.22821*eV, 2.23022*eV, 2.23222*eV, 2.23423*eV,
      2.23625*eV, 2.23827*eV, 2.24029*eV, 2.24231*eV, 2.24434*eV, 2.24638*eV, 2.24841*eV, 2.25045*eV, 2.2525*eV, 2.25455*eV,
      2.2566*eV, 2.25865*eV, 2.26071*eV, 2.26277*eV, 2.26484*eV, 2.26691*eV, 2.26898*eV, 2.27106*eV, 2.27314*eV, 2.27523*eV,
      2.27732*eV, 2.27941*eV, 2.28151*eV, 2.28361*eV, 2.28571*eV, 2.28782*eV, 2.28994*eV, 2.29205*eV, 2.29417*eV, 2.2963*eV,
      2.29842*eV, 2.30056*eV, 2.30269*eV, 2.30483*eV, 2.30698*eV, 2.30912*eV, 2.31128*eV, 2.31343*eV, 2.31559*eV, 2.31776*eV,
      2.31993*eV, 2.3221*eV, 2.32427*eV, 2.32645*eV, 2.32864*eV, 2.33083*eV, 2.33302*eV, 2.33522*eV, 2.33742*eV, 2.33962*eV,
      2.34183*eV, 2.34405*eV, 2.34626*eV, 2.34848*eV, 2.35071*eV, 2.35294*eV, 2.35518*eV, 2.35741*eV, 2.35966*eV, 2.3619*eV,
      2.36416*eV, 2.36641*eV, 2.36867*eV, 2.37094*eV, 2.37321*eV, 2.37548*eV, 2.37776*eV, 2.38004*eV, 2.38232*eV, 2.38462*eV,
      2.38691*eV, 2.38921*eV, 2.39151*eV, 2.39382*eV, 2.39614*eV, 2.39845*eV, 2.40077*eV, 2.4031*eV, 2.40543*eV, 2.40777*eV,
      2.41011*eV, 2.41245*eV, 2.4148*eV, 2.41715*eV, 2.41951*eV, 2.42188*eV, 2.42424*eV, 2.42661*eV, 2.42899*eV, 2.43137*eV,
      2.43376*eV, 2.43615*eV, 2.43854*eV, 2.44094*eV, 2.44335*eV, 2.44576*eV, 2.44817*eV, 2.45059*eV, 2.45302*eV, 2.45545*eV,
      2.45788*eV, 2.46032*eV, 2.46276*eV, 2.46521*eV, 2.46766*eV, 2.47012*eV, 2.47258*eV, 2.47505*eV, 2.47752*eV, 2.48*eV,
      2.48248*eV, 2.48497*eV, 2.48746*eV, 2.48996*eV, 2.49246*eV, 2.49497*eV, 2.49748*eV, 2.5*eV, 2.50252*eV, 2.50505*eV,
      2.50758*eV, 2.51012*eV, 2.51266*eV, 2.51521*eV, 2.51777*eV, 2.52033*eV, 2.52289*eV, 2.52546*eV, 2.52803*eV, 2.53061*eV,
      2.5332*eV, 2.53579*eV, 2.53838*eV, 2.54098*eV, 2.54359*eV, 2.5462*eV, 2.54882*eV, 2.55144*eV, 2.55407*eV, 2.5567*eV,
      2.55934*eV, 2.56198*eV, 2.56463*eV, 2.56729*eV, 2.56995*eV, 2.57261*eV, 2.57529*eV, 2.57796*eV, 2.58065*eV, 2.58333*eV,
      2.58603*eV, 2.58873*eV, 2.59143*eV, 2.59414*eV, 2.59686*eV, 2.59958*eV, 2.60231*eV, 2.60504*eV, 2.60778*eV, 2.61053*eV,
      2.61328*eV, 2.61603*eV, 2.6188*eV, 2.62156*eV, 2.62434*eV, 2.62712*eV, 2.6299*eV, 2.6327*eV, 2.63549*eV, 2.6383*eV,
      2.64111*eV, 2.64392*eV, 2.64674*eV, 2.64957*eV, 2.65241*eV, 2.65525*eV, 2.65809*eV, 2.66094*eV, 2.6638*eV, 2.66667*eV,
      2.66954*eV, 2.67241*eV, 2.6753*eV, 2.67819*eV, 2.68108*eV, 2.68398*eV, 2.68689*eV, 2.6898*eV, 2.69273*eV, 2.69565*eV,
      2.69859*eV, 2.70153*eV, 2.70447*eV, 2.70742*eV, 2.71038*eV, 2.71335*eV, 2.71632*eV, 2.7193*eV, 2.72228*eV, 2.72527*eV,
      2.72827*eV, 2.73128*eV, 2.73429*eV, 2.73731*eV, 2.74033*eV, 2.74336*eV, 2.7464*eV, 2.74945*eV };
  G4double FastComponent[nEntries_FAST] =
    { 5.81332e-05, 6.44431e-05, 5.14981e-05, 5.53578e-05, 7.63256e-05, 7.53282e-05, 7.58269e-05, 8.97693e-05, 7.76917e-05, 7.38103e-05,
      7.78435e-05, 7.09481e-05, 7.49162e-05, 8.77528e-05, 8.86852e-05, 9.01596e-05, 7.3355e-05, 8.61916e-05, 8.31125e-05, 9.63177e-05,
      9.64045e-05, 8.96609e-05, 0.000118934, 0.000122446, 0.000112017, 8.10092e-05, 9.10487e-05, 9.54287e-05, 0.000102975, 0.000102996,
      0.00010833, 9.44529e-05, 9.82259e-05, 0.000117372, 0.000121601, 0.00011206, 0.000123183, 0.000126371, 0.000114987, 0.000121687,
      0.00011065, 0.000131879, 0.000124766, 0.000119606, 0.000146146, 0.000145279, 0.000141441, 0.000148553, 0.000156012, 0.000149746,
      0.000163168, 0.000161043, 0.000174898, 0.000182661, 0.000175918, 0.000175939, 0.000171169, 0.000159807, 0.0001726, 0.000178866,
      0.000175028, 0.000190836, 0.000208768, 0.000179539, 0.000198165, 0.000197644, 0.000199509, 0.000202545, 0.000218005, 0.000208031,
      0.000212584, 0.000219848, 0.000234961, 0.000249945, 0.000232078, 0.000224814, 0.000229476, 0.000248232, 0.000290948, 0.000269568,
      0.000289062, 0.000288346, 0.000276572, 0.000287999, 0.000306235, 0.000306452, 0.000293724, 0.000325186, 0.000335356, 0.000332277,
      0.000323885, 0.000335464, 0.000335724, 0.000372413, 0.000366406, 0.000352919, 0.000341297, 0.000400384, 0.00038796, 0.000373518,
      0.000396785, 0.000419986, 0.00042712, 0.000413654, 0.000429158, 0.000443621, 0.000482629, 0.000489546, 0.00047736, 0.000457151,
      0.000534973, 0.000505028, 0.000518277, 0.000507934, 0.000520879, 0.000552884, 0.00054859, 0.00057396, 0.000561015, 0.000557329,
      0.000603645, 0.000608111, 0.000628646, 0.000624894, 0.000634196, 0.000647055, 0.000670148, 0.000680122, 0.000679211, 0.000696731,
      0.000703887, 0.000728888, 0.000708722, 0.000749509, 0.000780863, 0.000772819, 0.000771908, 0.000782294, 0.000797256, 0.000792767,
      0.000837197, 0.00086081, 0.000856668, 0.000894267, 0.000905629, 0.000906323, 0.00097068, 0.00095175, 0.000955696, 0.000969986,
      0.000980069, 0.00103508, 0.00108445, 0.00109566, 0.00108985, 0.00108554, 0.00116115, 0.00116232, 0.00123272, 0.00118337,
      0.0012059, 0.00121104, 0.00122034, 0.00134806, 0.00132759, 0.00131655, 0.00134255, 0.0014004, 0.00139422, 0.00140613,
      0.00148002, 0.00146782, 0.00151511, 0.00152601, 0.00156979, 0.00156765, 0.00161945, 0.00161797, 0.00164276, 0.00167585,
      0.00163298, 0.00169692, 0.00173064, 0.00185434, 0.0018602, 0.00183116, 0.00184591, 0.00187262, 0.00185005, 0.00187863,
      0.00193908, 0.00196593, 0.00204381, 0.00207335, 0.00214098, 0.00216439, 0.00214946, 0.00215717, 0.00218378, 0.00220102,
      0.00226733, 0.00225952, 0.00232741, 0.0023407, 0.00237913, 0.0023986, 0.00246035, 0.00246658, 0.00256504, 0.00255051,
      0.00260585, 0.00261381, 0.00263094, 0.00263575, 0.00272168, 0.00272411, 0.00270891, 0.00276706, 0.00281004, 0.00290874,
      0.00298958, 0.00287925, 0.00292917, 0.00294574, 0.00308388, 0.00300632, 0.00300664, 0.00304351, 0.00310511, 0.00314704,
      0.00307382, 0.0031967, 0.00324223, 0.0032804, 0.00328582, 0.00328493, 0.00322873, 0.00335108, 0.00344131, 0.00348589,
      0.00347806, 0.00350257, 0.00354257, 0.00361777, 0.00364609, 0.00357236, 0.00361374, 0.0036504, 0.00367545, 0.00370214,
      0.00372157, 0.00380769, 0.00386073, 0.00378243, 0.0038225, 0.00388172, 0.00388896, 0.0039206, 0.00382433, 0.0039355,
      0.00394595, 0.00403936, 0.00412466, 0.00398097, 0.00412995, 0.00410556, 0.00412607, 0.00409762, 0.00417612, 0.00419223,
      0.00418902, 0.00420858, 0.00418737, 0.00438864, 0.00428859, 0.00424058, 0.00428341, 0.00434349, 0.00426255, 0.00425739,
      0.00426099, 0.00435654, 0.00430615, 0.0043434, 0.00436442, 0.00443317, 0.00453702, 0.00458465, 0.00451718, 0.00454829,
      0.004526, 0.00444941, 0.00459784, 0.00461657, 0.00464116, 0.00463936, 0.00462128, 0.00464869, 0.00472074, 0.00464255,
      0.00463531, 0.00464357, 0.00472312, 0.00471226, 0.00472876, 0.00475929, 0.00477558, 0.00477493, 0.00476745, 0.00480513,
      0.00488634, 0.00489984, 0.00491695, 0.0049675, 0.00488809, 0.00492643, 0.0048836, 0.00497446, 0.00506449, 0.00503294,
      0.00507216, 0.00511015, 0.00528854, 0.00508509, 0.00508214, 0.00515293, 0.00521213, 0.00535207, 0.00521807, 0.00530294,
      0.00523004, 0.00531701, 0.00543113, 0.00540544, 0.00534221, 0.00529414, 0.00536786, 0.00530663, 0.00540221, 0.0054366,
      0.00546841, 0.00534307, 0.0053802, 0.00543647, 0.00542493, 0.00540019, 0.0054354, 0.00542636, 0.00540218, 0.00539761,
      0.00546834, 0.00538748, 0.0054119, 0.00524333, 0.0052661, 0.00528475, 0.00527178, 0.00527688, 0.00527451, 0.0051803,
      0.00532525, 0.00516377, 0.00502179, 0.00498588, 0.00493792, 0.00504124, 0.00497812, 0.00480997, 0.00484698, 0.00475996,
      0.00467631, 0.0046375, 0.00452982, 0.00445893, 0.00443842, 0.00431203, 0.004365, 0.00422527, 0.00416564, 0.00407752,
      0.00394289, 0.00401572, 0.00385061, 0.00368295, 0.00359867, 0.00356532, 0.00350603, 0.00343337, 0.00328738, 0.00314308,
      0.00308744, 0.00307742, 0.00298919, 0.00291293, 0.00276594, 0.00274861, 0.00263172, 0.00244029, 0.00243841, 0.0023837,
      0.00222602, 0.00220015, 0.00206933, 0.0019725, 0.00198421, 0.00188412, 0.00176243, 0.00169384, 0.00163604, 0.00154739,
      0.00148061, 0.00135909, 0.00128767, 0.00121056, 0.00116466, 0.00113142, 0.00102363, 0.000933341, 0.000903136, 0.00086764,
      0.000834096, 0.000722275, 0.000704733, 0.000665919, 0.000615007, 0.00057151, 0.000541261, 0.000484668, 0.000465868, 0.000435923,
      0.000406347, 0.000362091, 0.000334272, 0.000302766, 0.000280562, 0.000268874, 0.000248102, 0.000231557, 0.0002133, 0.0001981,
      0.000193611, 0.000166442, 0.000154017, 0.000139056, 0.0001301, 0.00011928, 0.000122511, 0.000106704, 8.5411e-05, 8.49339e-05,
      8.20717e-05, 6.96905e-05, 6.09304e-05, 5.20402e-05, 5.76345e-05, 5.77646e-05, 4.39089e-05, 6.16243e-05 };
  
  const G4int nEntries_RI = 3;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.842, 1.842, 1.842 };
  //G4double Rayleigh[nEntries_RI] =
  //  { 138.*mm, 138.*mm, 138.*mm };
  
  const G4int nEntries_ABS = 89;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.78417*eV, 1.7971*eV, 1.81022*eV, 1.82353*eV, 1.83704*eV, 1.85075*eV, 1.86466*eV, 1.87879*eV, 1.89313*eV, 1.90769*eV,
      1.92248*eV, 1.9375*eV, 1.95276*eV, 1.96825*eV, 1.984*eV, 2*eV, 2.01626*eV, 2.03279*eV, 2.04959*eV, 2.06667*eV,
      2.08403*eV, 2.10169*eV, 2.11966*eV, 2.13793*eV, 2.15652*eV, 2.17544*eV, 2.19469*eV, 2.21429*eV, 2.23423*eV, 2.25455*eV,
      2.27523*eV, 2.2963*eV, 2.31776*eV, 2.33962*eV, 2.3619*eV, 2.38462*eV, 2.40777*eV, 2.43137*eV, 2.45545*eV, 2.48*eV,
      2.50505*eV, 2.53061*eV, 2.5567*eV, 2.58333*eV, 2.61053*eV, 2.6383*eV, 2.66667*eV, 2.69565*eV, 2.72527*eV, 2.75556*eV,
      2.78652*eV, 2.81818*eV, 2.85057*eV, 2.88372*eV, 2.91765*eV, 2.95238*eV, 2.98795*eV, 3.02439*eV, 3.06173*eV, 3.1*eV,
      3.13924*eV, 3.17949*eV, 3.22078*eV, 3.26316*eV, 3.30667*eV, 3.35135*eV, 3.39726*eV, 3.44444*eV, 3.49296*eV, 3.54286*eV,
      3.5942*eV, 3.64706*eV, 3.70149*eV, 3.75758*eV, 3.81538*eV, 3.875*eV, 3.93651*eV, 4*eV, 4.06557*eV, 4.13333*eV,
      4.20339*eV, 4.27586*eV, 4.35088*eV, 4.42857*eV, 4.50909*eV, 4.59259*eV, 4.67925*eV, 4.76923*eV, 4.86275*eV };
  G4double Absorption[nEntries_ABS] =
    { 1.66482*m, 1.0584*m, 1.90233*m, 0.958758*m, 1.16913*m, 1.05368*m, 0.881739*m, 2.74593*m, 0.969113*m, 1.30342*m,
      1.11065*m, 1.14053*m, 0.926481*m, 0.835474*m, 0.814388*m, 0.702776*m, 1.01264*m, 0.749002*m, 0.691299*m, 0.791851*m,
      0.708582*m, 0.609636*m, 0.625308*m, 0.59058*m, 0.522642*m, 0.599727*m, 0.595345*m, 0.594927*m, 0.574464*m, 0.541271*m,
      0.531547*m, 0.581632*m, 0.57251*m, 0.560577*m, 0.493902*m, 0.422165*m, 0.354962*m, 0.255139*m, 0.151762*m, 0.0827965*m,
      0.0409174*m, 0.02007*m, 0.0100463*m, 0.00588694*m, 0.00636339*m, 0.0084497*m, 0.0224574*m, 0.0509883*m, 0.262914*m, 0.0571499*m,
      0.0830375*m, 0.378696*m, 0.0528428*m, 0.0661874*m, 0.0930821*m, 0.0672707*m, 0.0152385*m, 0.00676752*m, 0.00538106*m, 0.00799596*m,
      0.0177025*m, 0.0411282*m, 0.0919861*m, 0.149875*m, 0.132761*m, 0.068419*m, 0.0246548*m, 0.00922619*m, 0.00902168*m, 0.0264256*m,
      0.0839517*m, 0.0796384*m, 0.0552649*m, 0.0197203*m, 0.00872616*m, 0.00764327*m, 0.0153009*m, 0.0299903*m, 0.0403526*m, 0.0377371*m,
      0.0322887*m, 0.0251734*m, 0.0194992*m, 0.0145645*m, 0.0112908*m, 0.0100775*m, 0.0112081*m, 0.0158907*m, 0.019793*m };
  
  // for now, using the LSO scintillation properties
  const G4int nEntries_SCY = 12;
  G4double ElectronEnergy_SCY[nEntries_SCY] =
    { 0.000*MeV, 0.015*MeV, 0.020*MeV, 0.030*MeV,
      0.040*MeV, 0.060*MeV, 0.080*MeV, 0.090*MeV,
      0.105*MeV, 0.300*MeV, 0.500*MeV, 1.000*MeV };
  G4double ScintilYield[nEntries_SCY] =
    { 0.10, 0.46, 0.60, 0.68,
      0.74, 0.80, 0.82, 0.84,
      0.87, 0.96, 0.98, 1.00 };
  for(int i = 0; i < nEntries_SCY; i++)
    ScintilYield[i] = 15000.0*MeV*ScintilYield[i]*ElectronEnergy_SCY[i];
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,   nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  //myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
  //myMPT->AddProperty("ELECTRONSCINTILLATIONYIELD", ElectronEnergy_SCY, ScintilYield, nEntries_SCY);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",15000/MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",8.5);
  myMPT->AddConstProperty("FASTTIMECONSTANT",60.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.5*ns);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::LuAG_Pr() // Lutetium Aluminum Garnet - 
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z= 8., a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Al = new G4Element("Aluminum", "Al", z=27., a= 28.09*g/mole);
  
  G4Material* mat = new G4Material("LuAG_Pr", density=6.7*g/cm3,3);
  mat->AddElement(Lu,3);
  mat->AddElement(Al,12);
  mat->AddElement(O,5);
  
  //  2 bands at 290nm (4.28eV) and 350nm (3.54eV) about 50% of the light in each.
  const G4int nEntries_FAST = 8;
  G4double PhotonEnergy_FAST[nEntries_FAST] =
    { 1.00*eV, 3.40*eV, 3.50*eV, 3.60*eV,
      3.90*eV, 3.91*eV, 4.07*eV, 4.08*eV};
  G4double FastComponent[nEntries_FAST] =
    {0.00, 0.00, 1.00, 0.00,
     0.00, 1.00, 0.00, 0.00 }; 
 
  const G4int nEntries_RI = 3;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.842, 1.842, 1.842 };
  //G4double Rayleigh[nEntries_RI] =
  //  { 138.*mm, 138.*mm, 138.*mm};
  
  const G4int nEntries_ABS = 3;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double Absorption[nEntries_ABS] =
    { 138.*mm, 138.*mm, 138.*mm };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,   nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  //myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_RI);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",7000/MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",6.4);
  myMPT->AddConstProperty("FASTTIMECONSTANT",20.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.5*ns);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::LYSO()
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z= 8., a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Si = new G4Element("Silicon",  "Si", z=14., a= 28.09*g/mole);
  
  G4Material* mat = new G4Material("LYSO", density=7.1*g/cm3,3,kStateSolid);
  mat->AddElement(Lu,2);
  mat->AddElement(Si,1);
  mat->AddElement(O,5);
  
  const G4int nEntries_FAST = 261;
  G4double PhotonEnergy_FAST[nEntries_FAST] = 
    { 1.77169*eV, 1.77266*eV, 1.77558*eV, 1.77851*eV, 1.78145*eV, 1.78539*eV, 1.79033*eV, 1.7963*eV, 1.80231*eV, 1.80836*eV,
      1.81445*eV, 1.82058*eV, 1.82882*eV, 1.83401*eV, 1.84553*eV, 1.85293*eV, 1.86147*eV, 1.869*eV, 1.87769*eV, 1.89308*eV,
      1.90536*eV, 1.92007*eV, 1.93039*eV, 1.94901*eV, 1.95846*eV, 1.9668*eV, 1.97884*eV, 1.99102*eV, 2.00088*eV, 2.01209*eV,
      2.02596*eV, 2.03617*eV, 2.04519*eV, 2.0569*eV, 2.06611*eV, 2.0794*eV, 2.09151*eV, 2.10239*eV, 2.112*eV, 2.1231*eV,
      2.13431*eV, 2.14565*eV, 2.15566*eV, 2.16868*eV, 2.18038*eV, 2.19519*eV, 2.21171*eV, 2.2193*eV, 2.23619*eV, 2.23464*eV,
      2.24395*eV, 2.25806*eV, 2.27234*eV, 2.28358*eV, 2.29493*eV, 2.30475*eV, 2.31631*eV, 2.32463*eV, 2.33134*eV, 2.33809*eV,
      2.34487*eV, 2.35856*eV, 2.36719*eV, 2.37939*eV, 2.38642*eV, 2.40238*eV, 2.41134*eV, 2.424*eV, 2.43312*eV, 2.44047*eV,
      2.44786*eV, 2.46278*eV, 2.47788*eV, 2.48741*eV, 2.49317*eV, 2.49702*eV, 2.50282*eV, 2.50865*eV, 2.5145*eV, 2.52038*eV,
      2.52432*eV, 2.53223*eV, 2.5362*eV, 2.54619*eV, 2.55424*eV, 2.56031*eV, 2.56437*eV, 2.57049*eV, 2.57663*eV, 2.58487*eV,
      2.59317*eV, 2.59734*eV, 2.60571*eV, 2.61414*eV, 2.61414*eV, 2.61837*eV, 2.62262*eV, 2.62475*eV, 2.62902*eV, 2.63331*eV,
      2.63545*eV, 2.63976*eV, 2.64191*eV, 2.64841*eV, 2.65493*eV, 2.6593*eV, 2.66149*eV, 2.66588*eV, 2.67914*eV, 2.67914*eV,
      2.68136*eV, 2.68136*eV, 2.68359*eV, 2.68805*eV, 2.68805*eV, 2.68805*eV, 2.69477*eV, 2.69477*eV, 2.69702*eV, 2.70153*eV,
      2.70605*eV, 2.71286*eV, 2.71742*eV, 2.71971*eV, 2.722*eV, 2.722*eV, 2.72429*eV, 2.72889*eV, 2.72889*eV, 2.73351*eV,
      2.73814*eV, 2.74279*eV, 2.74512*eV, 2.74979*eV, 2.75213*eV, 2.75447*eV, 2.75917*eV, 2.75682*eV, 2.76389*eV, 2.76626*eV,
      2.76389*eV, 2.76626*eV, 2.77338*eV, 2.77576*eV, 2.78533*eV, 2.79255*eV, 2.79738*eV, 2.80223*eV, 2.80466*eV, 2.80709*eV,
      2.80953*eV, 2.80953*eV, 2.81934*eV, 2.8218*eV, 2.82673*eV, 2.83168*eV, 2.84164*eV, 2.84916*eV, 2.85419*eV, 2.8643*eV,
      2.86684*eV, 2.87449*eV, 2.87705*eV, 2.87961*eV, 2.88475*eV, 2.88733*eV, 2.8925*eV, 2.89509*eV, 2.90028*eV, 2.90549*eV,
      2.90811*eV, 2.91073*eV, 2.91335*eV, 2.91335*eV, 2.91335*eV, 2.91861*eV, 2.92125*eV, 2.92125*eV, 2.92389*eV, 2.92654*eV,
      2.92654*eV, 2.92919*eV, 2.92919*eV, 2.93185*eV, 2.93451*eV, 2.93717*eV, 2.93985*eV, 2.94252*eV, 2.9452*eV, 2.94789*eV,
      2.94789*eV, 2.94789*eV, 2.95058*eV, 2.95868*eV, 2.96411*eV, 2.96955*eV, 2.97228*eV, 2.97228*eV, 2.96955*eV, 2.97228*eV,
      2.97502*eV, 2.97776*eV, 2.97502*eV, 2.9805*eV, 2.9805*eV, 2.9805*eV, 2.98601*eV, 2.99154*eV, 2.99431*eV, 2.99431*eV,
      2.99708*eV, 2.99431*eV, 2.99708*eV, 3.00544*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.01385*eV, 3.0223*eV,
      3.02797*eV, 3.03081*eV, 3.02797*eV, 3.03365*eV, 3.03081*eV, 3.03081*eV, 3.0365*eV, 3.03935*eV, 3.04221*eV, 3.04795*eV,
      3.04795*eV, 3.05083*eV, 3.05371*eV, 3.05949*eV, 3.06239*eV, 3.06529*eV, 3.0682*eV, 3.06529*eV, 3.07112*eV, 3.0682*eV,
      3.07696*eV, 3.08283*eV, 3.0976*eV, 3.09464*eV, 3.09464*eV, 3.10653*eV, 3.11252*eV, 3.11852*eV, 3.12757*eV, 3.13668*eV,
      3.14583*eV, 3.15813*eV, 3.16741*eV, 3.17675*eV, 3.20828*eV, 3.23719*eV, 3.26664*eV, 3.28656*eV, 3.31351*eV, 3.34783*eV,
      3.38287*eV };
  G4double FastComponent[nEntries_FAST] = 
    { 0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
      0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
      0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
      0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
      0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
      0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
      0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
      0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
      0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
      0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
      1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
      1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
      1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
      1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
      1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
      2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
      2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
      1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
      1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
      1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
      1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
      1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
      0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
      0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
      0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
      0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
      0.011691 };
  
  const G4int nEntries_RI = 3;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.82, 1.82, 1.82 };
  //G4double Rayleigh[nEntries_RI] =
  //  { 138.*mm, 138.*mm, 138.*mm};
  
  const G4int nEntries_ABS = 9;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.00*eV , 2.82*eV , 2.88*eV , 2.95*eV , 3.02*eV  , 3.10*eV  , 3.18*eV  , 3.26*eV , 4.08*eV };
  G4double Absorption[nEntries_ABS] =
    { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5*mm  , 11.5*mm  , 1.0*mm  , 1.0*mm  };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,  nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  //myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_ABS,  Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",40000./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",3.4);
  myMPT->AddConstProperty("FASTTIMECONSTANT",40.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.1*ns);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::LYSO_lowLY()
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z=8.,  a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Si = new G4Element("Silicon",  "Si", z=14., a= 28.09*g/mole);
  
  G4Material* mat = new G4Material("LYSO_lowLY", density=7.1*g/cm3,3,kStateSolid);
  mat->AddElement(Lu,2);
  mat->AddElement(Si,1);
  mat->AddElement(O,5);
  
  const G4int nEntries_FAST = 261;
  G4double PhotonEnergy_FAST[nEntries_FAST] = 
    { 1.77169*eV, 1.77266*eV, 1.77558*eV, 1.77851*eV, 1.78145*eV, 1.78539*eV, 1.79033*eV, 1.7963*eV, 1.80231*eV, 1.80836*eV,
      1.81445*eV, 1.82058*eV, 1.82882*eV, 1.83401*eV, 1.84553*eV, 1.85293*eV, 1.86147*eV, 1.869*eV, 1.87769*eV, 1.89308*eV,
      1.90536*eV, 1.92007*eV, 1.93039*eV, 1.94901*eV, 1.95846*eV, 1.9668*eV, 1.97884*eV, 1.99102*eV, 2.00088*eV, 2.01209*eV,
      2.02596*eV, 2.03617*eV, 2.04519*eV, 2.0569*eV, 2.06611*eV, 2.0794*eV, 2.09151*eV, 2.10239*eV, 2.112*eV, 2.1231*eV,
      2.13431*eV, 2.14565*eV, 2.15566*eV, 2.16868*eV, 2.18038*eV, 2.19519*eV, 2.21171*eV, 2.2193*eV, 2.23619*eV, 2.23464*eV,
      2.24395*eV, 2.25806*eV, 2.27234*eV, 2.28358*eV, 2.29493*eV, 2.30475*eV, 2.31631*eV, 2.32463*eV, 2.33134*eV, 2.33809*eV,
      2.34487*eV, 2.35856*eV, 2.36719*eV, 2.37939*eV, 2.38642*eV, 2.40238*eV, 2.41134*eV, 2.424*eV, 2.43312*eV, 2.44047*eV,
      2.44786*eV, 2.46278*eV, 2.47788*eV, 2.48741*eV, 2.49317*eV, 2.49702*eV, 2.50282*eV, 2.50865*eV, 2.5145*eV, 2.52038*eV,
      2.52432*eV, 2.53223*eV, 2.5362*eV, 2.54619*eV, 2.55424*eV, 2.56031*eV, 2.56437*eV, 2.57049*eV, 2.57663*eV, 2.58487*eV,
      2.59317*eV, 2.59734*eV, 2.60571*eV, 2.61414*eV, 2.61414*eV, 2.61837*eV, 2.62262*eV, 2.62475*eV, 2.62902*eV, 2.63331*eV,
      2.63545*eV, 2.63976*eV, 2.64191*eV, 2.64841*eV, 2.65493*eV, 2.6593*eV, 2.66149*eV, 2.66588*eV, 2.67914*eV, 2.67914*eV,
      2.68136*eV, 2.68136*eV, 2.68359*eV, 2.68805*eV, 2.68805*eV, 2.68805*eV, 2.69477*eV, 2.69477*eV, 2.69702*eV, 2.70153*eV,
      2.70605*eV, 2.71286*eV, 2.71742*eV, 2.71971*eV, 2.722*eV, 2.722*eV, 2.72429*eV, 2.72889*eV, 2.72889*eV, 2.73351*eV,
      2.73814*eV, 2.74279*eV, 2.74512*eV, 2.74979*eV, 2.75213*eV, 2.75447*eV, 2.75917*eV, 2.75682*eV, 2.76389*eV, 2.76626*eV,
      2.76389*eV, 2.76626*eV, 2.77338*eV, 2.77576*eV, 2.78533*eV, 2.79255*eV, 2.79738*eV, 2.80223*eV, 2.80466*eV, 2.80709*eV,
      2.80953*eV, 2.80953*eV, 2.81934*eV, 2.8218*eV, 2.82673*eV, 2.83168*eV, 2.84164*eV, 2.84916*eV, 2.85419*eV, 2.8643*eV,
      2.86684*eV, 2.87449*eV, 2.87705*eV, 2.87961*eV, 2.88475*eV, 2.88733*eV, 2.8925*eV, 2.89509*eV, 2.90028*eV, 2.90549*eV,
      2.90811*eV, 2.91073*eV, 2.91335*eV, 2.91335*eV, 2.91335*eV, 2.91861*eV, 2.92125*eV, 2.92125*eV, 2.92389*eV, 2.92654*eV,
      2.92654*eV, 2.92919*eV, 2.92919*eV, 2.93185*eV, 2.93451*eV, 2.93717*eV, 2.93985*eV, 2.94252*eV, 2.9452*eV, 2.94789*eV,
      2.94789*eV, 2.94789*eV, 2.95058*eV, 2.95868*eV, 2.96411*eV, 2.96955*eV, 2.97228*eV, 2.97228*eV, 2.96955*eV, 2.97228*eV,
      2.97502*eV, 2.97776*eV, 2.97502*eV, 2.9805*eV, 2.9805*eV, 2.9805*eV, 2.98601*eV, 2.99154*eV, 2.99431*eV, 2.99431*eV,
      2.99708*eV, 2.99431*eV, 2.99708*eV, 3.00544*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.01385*eV, 3.0223*eV,
      3.02797*eV, 3.03081*eV, 3.02797*eV, 3.03365*eV, 3.03081*eV, 3.03081*eV, 3.0365*eV, 3.03935*eV, 3.04221*eV, 3.04795*eV,
      3.04795*eV, 3.05083*eV, 3.05371*eV, 3.05949*eV, 3.06239*eV, 3.06529*eV, 3.0682*eV, 3.06529*eV, 3.07112*eV, 3.0682*eV,
      3.07696*eV, 3.08283*eV, 3.0976*eV, 3.09464*eV, 3.09464*eV, 3.10653*eV, 3.11252*eV, 3.11852*eV, 3.12757*eV, 3.13668*eV,
      3.14583*eV, 3.15813*eV, 3.16741*eV, 3.17675*eV, 3.20828*eV, 3.23719*eV, 3.26664*eV, 3.28656*eV, 3.31351*eV, 3.34783*eV,
      3.38287*eV };
  G4double FastComponent[nEntries_FAST] = 
    { 0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
      0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
      0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
      0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
      0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
      0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
      0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
      0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
      0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
      0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
      1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
      1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
      1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
      1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
      1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
      2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
      2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
      1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
      1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
      1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
      1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
      1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
      0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
      0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
      0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
      0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
      0.011691 };
  
  const G4int nEntries_RI = 3;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.82, 1.82, 1.82 };
  //G4double Rayleigh[nEntries_RI]
  //  = { 138.*mm, 138.*mm, 138.*mm};
  
  const G4int nEntries_ABS = 9;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.00*eV , 2.82*eV , 2.88*eV , 2.95*eV , 3.02*eV  , 3.10*eV  , 3.18*eV  , 3.26*eV , 4.08*eV };
  G4double Absorption[nEntries_ABS] =
    { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5*mm  , 11.5*mm  , 1.0*mm  , 1.0*mm  };
  
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,  nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  //myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",10./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",3.4);
  myMPT->AddConstProperty("FASTTIMECONSTANT",40.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.1*ns);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::LSO()
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z= 8., a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Si = new G4Element("Silicon",  "Si", z=14., a= 28.09*g/mole);
  
  G4Material* mat = new G4Material("LSO", density=7.4*g/cm3,3);
  mat->AddElement(Lu,2);
  mat->AddElement(Si,1);
  mat->AddElement(O,5);
  
  const G4int nEntries_FAST = 192;
  G4double PhotonEnergy_FAST[nEntries_FAST] = 
    { 1.83966*eV, 1.84948*eV, 1.86274*eV, 1.87507*eV, 1.88413*eV, 1.90369*eV, 1.91187*eV, 1.92129*eV, 1.92962*eV, 1.93922*eV,
      1.95258*eV, 1.96365*eV, 1.97986*eV, 1.99124*eV, 2.00533*eV, 2.02618*eV, 2.04747*eV, 2.06101*eV, 2.07472*eV, 2.09424*eV,
      2.11269*eV, 2.12565*eV, 2.14466*eV, 2.16251*eV, 2.17914*eV, 2.19602*eV, 2.21317*eV, 2.22422*eV, 2.24021*eV, 2.25479*eV,
      2.26462*eV, 2.27785*eV, 2.29462*eV, 2.30821*eV, 2.32024*eV, 2.33588*eV, 2.34643*eV, 2.35529*eV, 2.37322*eV, 2.38594*eV,
      2.3896*eV, 2.39879*eV, 2.40805*eV, 2.41365*eV, 2.4268*eV, 2.44009*eV, 2.45161*eV, 2.46518*eV, 2.47693*eV, 2.48483*eV,
      2.49477*eV, 2.50479*eV, 2.51692*eV, 2.53123*eV, 2.5457*eV, 2.54986*eV, 2.55613*eV, 2.56033*eV, 2.56665*eV, 2.58796*eV,
      2.59658*eV, 2.60091*eV, 2.60309*eV, 2.60744*eV, 2.614*eV, 2.62059*eV, 2.62943*eV, 2.6361*eV, 2.64057*eV, 2.64729*eV,
      2.65632*eV, 2.66085*eV, 2.6654*eV, 2.66997*eV, 2.67684*eV, 2.67684*eV, 2.68839*eV, 2.69303*eV, 2.70237*eV, 2.70471*eV,
      2.71177*eV, 2.72124*eV, 2.72362*eV, 2.73077*eV, 2.73077*eV, 2.73317*eV, 2.73797*eV, 2.74279*eV, 2.74762*eV, 2.7549*eV,
      2.7549*eV, 2.75978*eV, 2.75978*eV, 2.76468*eV, 2.76713*eV, 2.77205*eV, 2.77699*eV, 2.77699*eV, 2.77947*eV, 2.78941*eV,
      2.79692*eV, 2.80195*eV, 2.80699*eV, 2.8146*eV, 2.81714*eV, 2.8248*eV, 2.8325*eV, 2.83507*eV, 2.85063*eV, 2.85847*eV,
      2.86635*eV, 2.86899*eV, 2.87428*eV, 2.87959*eV, 2.88225*eV, 2.89027*eV, 2.89295*eV, 2.89833*eV, 2.90103*eV, 2.90915*eV,
      2.91186*eV, 2.91731*eV, 2.92278*eV, 2.92278*eV, 2.92553*eV, 2.93103*eV, 2.93103*eV, 2.93103*eV, 2.94487*eV, 2.94487*eV,
      2.94766*eV, 2.95324*eV, 2.95604*eV, 2.95885*eV, 2.95604*eV, 2.96166*eV, 2.96447*eV, 2.97012*eV, 2.96166*eV, 2.97295*eV,
      2.98434*eV, 2.98434*eV, 2.98148*eV, 2.98434*eV, 2.99006*eV, 2.9872*eV, 2.99006*eV, 2.9872*eV, 2.99006*eV, 2.99869*eV,
      3.00447*eV, 3.00737*eV, 3.0161*eV, 3.01902*eV, 3.0161*eV, 3.0161*eV, 3.01318*eV, 3.01318*eV, 3.02194*eV, 3.02781*eV,
      3.03666*eV, 3.03666*eV, 3.03666*eV, 3.04556*eV, 3.05152*eV, 3.05152*eV, 3.05451*eV, 3.05451*eV, 3.05451*eV, 3.06051*eV,
      3.05751*eV, 3.07258*eV, 3.07258*eV, 3.07561*eV, 3.08169*eV, 3.09085*eV, 3.08779*eV, 3.09085*eV, 3.09699*eV, 3.10935*eV,
      3.10625*eV, 3.1218*eV, 3.12807*eV, 3.13121*eV, 3.14067*eV, 3.15657*eV, 3.16941*eV, 3.19213*eV, 3.21849*eV, 3.24529*eV,
      3.27255*eV, 3.28981*eV };
  G4double FastComponent[nEntries_FAST] = 
    { 0.0121475, 0.0121475, 0.0151844, 0.0151844, 0.0151844, 0.0182213, 0.0182213, 0.0182213, 0.024295, 0.024295,
      0.0212581, 0.0212581, 0.0303688, 0.0303688, 0.0303688, 0.0425163, 0.0516269, 0.0607375, 0.0698482, 0.072885,
      0.0850325, 0.0941432, 0.106291, 0.127549, 0.130586, 0.142733, 0.163991, 0.179176, 0.19436, 0.212581,
      0.224729, 0.239913, 0.252061, 0.273319, 0.297614, 0.318872, 0.34013, 0.355315, 0.376573, 0.38872,
      0.413015, 0.4282, 0.440347, 0.458568, 0.47679, 0.507158, 0.531453, 0.567896, 0.595228, 0.628633,
      0.652928, 0.68026, 0.71974, 0.759219, 0.77744, 0.813883, 0.835141, 0.859436, 0.886768, 0.920174,
      0.956616, 0.990022, 1.00521, 1.01735, 1.04165, 1.06898, 1.09328, 1.11757, 1.15098, 1.17223,
      1.2026, 1.23297, 1.26334, 1.29067, 1.32104, 1.37874, 1.40304, 1.43341, 1.46074, 1.49414,
      1.52451, 1.56095, 1.60043, 1.63991, 1.67028, 1.69761, 1.72191, 1.7462, 1.77354, 1.81605,
      1.84946, 1.88286, 1.88286, 1.88894, 1.9102, 1.94056, 1.98308, 2.00434, 2.03167, 2.07419,
      2.10759, 2.13189, 2.15315, 2.16833, 2.17744, 2.19566, 2.20781, 2.20781, 2.21996, 2.21692,
      2.20477, 2.18959, 2.16833, 2.14403, 2.11367, 2.08026, 2.04685, 2.01649, 1.98308, 1.94056,
      1.90716, 1.87679, 1.84642, 1.80998, 1.77354, 1.73406, 1.70369, 1.66421, 1.60651, 1.53362,
      1.5154, 1.49111, 1.46985, 1.44252, 1.4243, 1.39696, 1.36356, 1.318, 1.26941, 1.21171,
      1.16616, 1.13275, 1.09935, 1.12972, 1.11453, 1.08416, 1.05683, 1.02343, 0.993059, 0.956616,
      0.929284, 0.895879, 0.87462, 0.835141, 0.801735, 0.77744, 0.747072, 0.704555, 0.67115, 0.640781,
      0.595228, 0.570933, 0.540564, 0.510195, 0.473753, 0.443384, 0.419089, 0.394794, 0.373536, 0.34013,
      0.318872, 0.276356, 0.252061, 0.203471, 0.185249, 0.163991, 0.142733, 0.127549, 0.112364, 0.0911063,
      0.072885, 0.0577007, 0.0425163, 0.0303688, 0.024295, 0.00911063, 0.00607375, 0.00607375, 0.00303688, 0.00303688,
      0.00911063, 0.00911063 };
  
  const G4int nEntries_RI = 4;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 0.0001*eV, 1.0*eV, 1.84*eV, 4.08*eV };
  G4double RefractiveIndex[nEntries_RI] =
    { 1.82, 1.82, 1.82, 1.82 };
  //G4double Rayleigh[nEntries_RI] =
  //  { 138.*mm, 138.*mm, 138.*mm};
  
  const G4int nEntries_ABS = 4;  
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 0.0001*eV, 1.0*eV, 1.84*eV, 4.08*eV };
  G4double Absorption[nEntries_ABS] =
    { 1*mm,138.*mm, 138.*mm, 138.*mm };
  
  const G4int nEntries_SCY = 12;
  G4double ElectronEnergy_SCY[nEntries_SCY] =
    { 0.000*MeV, 0.015*MeV, 0.020*MeV, 0.030*MeV,
      0.040*MeV, 0.060*MeV, 0.080*MeV, 0.090*MeV,
      0.105*MeV, 0.300*MeV, 0.500*MeV, 1.000*MeV };
  G4double ScintilYield[nEntries_SCY] =
    { 0.10, 0.46, 0.60, 0.68,
      0.74, 0.80, 0.82, 0.84,
      0.87,  0.96,  0.98,  1.00 };
  for(int i=0; i < nEntries_SCY; i++)
    ScintilYield[i] = 60000.0*MeV*ScintilYield[i]*ElectronEnergy_SCY[i];
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,   nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  //myMPT->AddProperty("RAYLEIGH",      PhotonEnergy_RI,   Rayleigh,        nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
  myMPT->AddProperty("ELECTRONSCINTILLATIONYIELD", ElectronEnergy_SCY, ScintilYield, nEntries_SCY);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",60000./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",3.2);
  myMPT->AddConstProperty("FASTTIMECONSTANT",40.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.1*ns);
  
  mat->SetMaterialPropertiesTable(myMPT);
  
  return mat;
}



G4Material* MyMaterials::PWO(double mu_ind)
{
  G4double a, z, density;
  G4Element* Pb = new G4Element("Lead",     "Pb", z = 82., a = 207.21*g/mole);
  G4Element* W  = new G4Element("Tungsten", "W",  z = 74., a = 183.85*g/mole);
  G4Element* O  = new G4Element("Oxygen",   "O",  z =  8., a =  16.00*g/mole);
  
  G4Material* mat = new G4Material ("PWO", density = 8.28*g/cm3,3);
  mat->AddElement (Pb, 1);
  mat->AddElement (W, 1);
  mat->AddElement (O, 4);
      
      //my latest lab measurement
      const int nEntries_FAST = 507;
      G4double PhotonEnergy_FAST[nEntries_FAST] = { 1.90769*eV, 2.06667*eV, 2.16783*eV, 2.16973*eV, 2.17163*eV, 2.17353*eV, 2.17544*eV, 2.17735*eV, 2.17926*eV, 2.18118*eV, 2.1831*eV, 2.18502*eV,
       2.18695*eV, 2.18888*eV, 2.19081*eV, 2.19275*eV, 2.19469*eV, 2.19663*eV, 2.19858*eV, 2.20053*eV, 2.20249*eV, 2.20444*eV, 2.20641*eV, 2.20837*eV, 2.21034*eV, 2.21231*eV, 2.21429*eV,
        2.21626*eV, 2.21825*eV, 2.22023*eV, 2.22222*eV, 2.22422*eV, 2.22621*eV, 2.22821*eV, 2.23022*eV, 2.23222*eV, 2.23423*eV, 2.23625*eV, 2.23827*eV, 2.24029*eV, 2.24231*eV, 2.24434*eV,
         2.24638*eV, 2.24841*eV, 2.25045*eV, 2.2525*eV, 2.25455*eV, 2.2566*eV, 2.25865*eV, 2.26071*eV, 2.26277*eV, 2.26484*eV, 2.26691*eV, 2.26898*eV, 2.27106*eV, 2.27314*eV, 2.27523*eV,
          2.27732*eV, 2.27941*eV, 2.28151*eV, 2.28361*eV, 2.28571*eV, 2.28782*eV, 2.28994*eV, 2.29205*eV, 2.29417*eV, 2.2963*eV, 2.29842*eV, 2.30056*eV, 2.30269*eV, 2.30483*eV, 2.30698*eV,
           2.30912*eV, 2.31128*eV, 2.31343*eV, 2.31559*eV, 2.31776*eV, 2.31993*eV, 2.3221*eV, 2.32427*eV, 2.32645*eV, 2.32864*eV, 2.33083*eV, 2.33302*eV, 2.33522*eV, 2.33742*eV, 2.33962*eV,
            2.34183*eV, 2.34405*eV, 2.34626*eV, 2.34848*eV, 2.35071*eV, 2.35294*eV, 2.35518*eV, 2.35741*eV, 2.35966*eV, 2.3619*eV, 2.36416*eV, 2.36641*eV, 2.36867*eV, 2.37094*eV, 2.37321*eV,
             2.37548*eV, 2.37776*eV, 2.38004*eV, 2.38232*eV, 2.38462*eV, 2.38691*eV, 2.38921*eV, 2.39151*eV, 2.39382*eV, 2.39614*eV, 2.39845*eV, 2.40077*eV, 2.4031*eV, 2.40543*eV, 2.40777*eV,
              2.41011*eV, 2.41245*eV, 2.4148*eV, 2.41715*eV, 2.41951*eV, 2.42188*eV, 2.42424*eV, 2.42661*eV, 2.42899*eV, 2.43137*eV, 2.43376*eV, 2.43615*eV, 2.43854*eV, 2.44094*eV, 2.44335*eV,
               2.44576*eV, 2.44817*eV, 2.45059*eV, 2.45302*eV, 2.45545*eV, 2.45788*eV, 2.46032*eV, 2.46276*eV, 2.46521*eV, 2.46766*eV, 2.47012*eV, 2.47258*eV, 2.47505*eV, 2.47752*eV, 2.48*eV,
                2.48248*eV, 2.48497*eV, 2.48746*eV, 2.48996*eV, 2.49246*eV, 2.49497*eV, 2.49748*eV, 2.5*eV, 2.50252*eV, 2.50505*eV, 2.50758*eV, 2.51012*eV, 2.51266*eV, 2.51521*eV, 2.51777*eV,
                 2.52033*eV, 2.52289*eV, 2.52546*eV, 2.52803*eV, 2.53061*eV, 2.5332*eV, 2.53579*eV, 2.53838*eV, 2.54098*eV, 2.54359*eV, 2.5462*eV, 2.54882*eV, 2.55144*eV, 2.55407*eV, 2.5567*eV,
                  2.55934*eV, 2.56198*eV, 2.56463*eV, 2.56729*eV, 2.56995*eV, 2.57261*eV, 2.57529*eV, 2.57796*eV, 2.58065*eV, 2.58333*eV, 2.58603*eV, 2.58873*eV, 2.59143*eV, 2.59414*eV,
                  2.59686*eV,2.59958*eV,          2.60231*eV, 2.60504*eV, 2.60778*eV, 2.61053*eV, 2.61328*eV, 2.61603*eV, 2.6188*eV, 2.62156*eV, 2.62434*eV, 2.62712*eV, 2.6299*eV, 2.6327*eV, 2.63549*eV, 2.6383*eV, 2.64111*eV, 2.64392*eV,                   2.64674*eV, 2.64957*eV, 2.65241*eV, 2.65525*eV, 2.65809*eV, 2.66094*eV, 2.6638*eV, 2.66667*eV, 2.66954*eV, 2.67241*eV, 2.6753*eV, 2.67819*eV, 2.68108*eV, 2.68398*eV, 2.68689*eV, 2.6898*eV, 2.69273*eV, 2.69565*eV, 2.69859*eV, 2.70153*eV, 2.70447*eV, 2.70742*eV, 2.71038*eV, 2.71335*eV, 2.71632*eV, 2.7193*eV, 2.72228*eV, 2.72527*eV, 2.72827*eV, 2.73128*eV, 2.73429*eV, 2.73731*eV, 2.74033*eV, 2.74336*eV, 2.7464*eV, 2.74945*eV, 2.7525*eV, 2.75556*eV, 2.75862*eV, 2.76169*eV, 2.76477*eV, 2.76786*eV, 2.77095*eV, 2.77405*eV, 2.77716*eV, 2.78027*eV, 2.78339*eV, 2.78652*eV, 2.78965*eV, 2.79279*eV, 2.79594*eV, 2.7991*eV, 2.80226*eV, 2.80543*eV, 2.80861*eV, 2.81179*eV, 2.81498*eV, 2.81818*eV, 2.82139*eV, 2.8246*eV, 2.82782*eV, 2.83105*eV, 2.83429*eV, 2.83753*eV, 2.84078*eV, 2.84404*eV, 2.8473*eV, 2.85057*eV, 2.85386*eV, 2.85714*eV, 2.86044*eV, 2.86374*eV, 2.86705*eV, 2.87037*eV, 2.8737*eV, 2.87703*eV, 2.88037*eV, 2.88372*eV, 2.88708*eV, 2.89044*eV, 2.89382*eV, 2.8972*eV, 2.90058*eV, 2.90398*eV, 2.90739*eV, 2.9108*eV, 2.91422*eV, 2.91765*eV, 2.92108*eV, 2.92453*eV, 2.92798*eV, 2.93144*eV, 2.93491*eV, 2.93839*eV, 2.94187*eV, 2.94537*eV, 2.94887*eV, 2.95238*eV, 2.9559*eV, 2.95943*eV, 2.96296*eV, 2.96651*eV, 2.97006*eV, 2.97362*eV, 2.97719*eV, 2.98077*eV, 2.98436*eV, 2.98795*eV, 2.99156*eV, 2.99517*eV, 2.99879*eV, 3.00242*eV, 3.00606*eV, 3.00971*eV, 3.01337*eV, 3.01703*eV, 3.02071*eV, 3.02439*eV, 3.02808*eV, 3.03178*eV, 3.0355*eV, 3.03922*eV, 3.04294*eV, 3.04668*eV, 3.05043*eV, 3.05419*eV, 3.05795*eV, 3.06173*eV, 3.06551*eV, 3.06931*eV, 3.07311*eV, 3.07692*eV, 3.08075*eV, 3.08458*eV, 3.08842*eV, 3.09227*eV, 3.09613*eV, 3.1*eV, 3.10388*eV, 3.10777*eV, 3.11167*eV, 3.11558*eV, 3.1195*eV, 3.12343*eV, 3.12736*eV, 3.13131*eV, 3.13527*eV, 3.13924*eV, 3.14322*eV, 3.14721*eV, 3.15121*eV, 3.15522*eV, 3.15924*eV, 3.16327*eV, 3.16731*eV, 3.17136*eV, 3.17542*eV, 3.17949*eV, 3.18357*eV, 3.18766*eV, 3.19176*eV, 3.19588*eV, 3.2*eV, 3.20413*eV, 3.20828*eV, 3.21244*eV, 3.2166*eV, 3.22078*eV, 3.22497*eV, 3.22917*eV, 3.23338*eV, 3.2376*eV, 3.24183*eV, 3.24607*eV, 3.25033*eV, 3.25459*eV, 3.25887*eV, 3.26316*eV, 3.26746*eV, 3.27177*eV, 3.27609*eV, 3.28042*eV, 3.28477*eV, 3.28912*eV, 3.29349*eV, 3.29787*eV, 3.30226*eV, 3.30667*eV, 3.31108*eV, 3.31551*eV, 3.31995*eV, 3.3244*eV, 3.32886*eV, 3.33333*eV, 3.33782*eV, 3.34232*eV, 3.34683*eV, 3.35135*eV, 3.35589*eV, 3.36043*eV, 3.36499*eV, 3.36957*eV, 3.37415*eV, 3.37875*eV, 3.38336*eV, 3.38798*eV, 3.39261*eV, 3.39726*eV, 3.40192*eV, 3.40659*eV, 3.41128*eV, 3.41598*eV, 3.42069*eV, 3.42541*eV, 3.43015*eV, 3.4349*eV, 3.43967*eV, 3.44444*eV, 3.44924*eV, 3.45404*eV, 3.45886*eV, 3.46369*eV, 3.46853*eV, 3.47339*eV, 3.47826*eV, 3.48315*eV, 3.48805*eV, 3.49296*eV, 3.49788*eV, 3.50282*eV, 3.50778*eV, 3.51275*eV, 3.51773*eV, 3.52273*eV, 3.52774*eV, 3.53276*eV, 3.5378*eV, 3.54286*eV, 3.54793*eV, 3.55301*eV, 3.55811*eV, 3.56322*eV, 3.56835*eV, 3.57349*eV, 3.57864*eV, 3.58382*eV, 3.589*eV, 3.5942*eV, 3.59942*eV, 3.60465*eV, 3.6099*eV, 3.61516*eV, 3.62044*eV, 3.62573*eV, 3.63104*eV, 3.63636*eV, 3.6417*eV, 3.64706*eV, 3.65243*eV, 3.65782*eV, 3.66322*eV, 3.66864*eV, 3.67407*eV, 3.67953*eV, 3.68499*eV, 3.69048*eV, 3.69598*eV, 3.70149*eV, 3.70703*eV, 3.71257*eV, 3.71814*eV, 3.72372*eV, 3.72932*eV, 3.73494*eV, 3.74057*eV, 3.74622*eV, 3.75189*eV, 3.75758*eV, 3.76328*eV, 3.769*eV, 3.77473*eV, 3.78049*eV, 3.78626*eV, 3.79205*eV, 3.79786*eV, 3.80368*eV, 3.80952*eV, 3.81538*eV, 3.82126*eV, 3.82716*eV, 3.83308*eV, 3.83901*eV, 3.84496*eV, 3.85093*eV, 3.85692*eV, 3.86293*eV, 3.86895*eV};
      
      G4double FastComponent[nEntries_FAST] ={ 0.00052381, 0.0152381, 0.0293924, 0.0269467, 0.0256848, 0.0254981, 0.0260076, 0.0268133, 0.0273648, 0.0280457, 0.0287067, 0.0289924, 0.029, 0.0288914, 0.0289476, 0.0291505, 0.0292914, 0.0290752, 0.0287514, 0.0286714, 0.0288343, 0.0293133, 0.0302143, 0.031561, 0.0330762, 0.034459, 0.0351705, 0.03478, 0.0340324, 0.0329552, 0.0314514, 0.0300962, 0.0292152, 0.028841, 0.0289524, 0.0294419, 0.0297876, 0.0303133, 0.0310962, 0.0317743, 0.0322238, 0.0325276, 0.0329733, 0.03336, 0.0337895, 0.0342257, 0.0347362, 0.0354695, 0.0363, 0.0369238, 0.036979, 0.036579, 0.0356076, 0.0343095, 0.032999, 0.0316876, 0.0306171, 0.0302533, 0.0308752, 0.0322067, 0.0339943, 0.0360067, 0.0384286, 0.0411333, 0.04334, 0.0450924, 0.0462695, 0.0472533, 0.0481019, 0.0483352, 0.0482181, 0.04864, 0.0499019, 0.0517543, 0.0543505, 0.0575267, 0.0607876, 0.0641314, 0.0667838, 0.0683514, 0.0693419, 0.0702543, 0.0710981, 0.0720552, 0.0736676, 0.0752762, 0.0773286, 0.0791752, 0.0807333, 0.082079, 0.0833629, 0.0845933, 0.0859524, 0.0877581, 0.0892943, 0.0910914, 0.0929019, 0.0952905, 0.0978371, 0.100682, 0.103224, 0.105718, 0.107852, 0.109241, 0.109795, 0.109354, 0.109503, 0.110292, 0.112409, 0.115256, 0.11961, 0.124909, 0.130732, 0.13613, 0.140314, 0.144119, 0.14665, 0.148469, 0.149407, 0.150265, 0.151147, 0.152253, 0.154354, 0.15737, 0.161138, 0.164838, 0.168873, 0.172971, 0.177416, 0.181659, 0.185039, 0.18823, 0.191871, 0.195512, 0.198159, 0.20033, 0.202124, 0.203936, 0.205858, 0.207766, 0.20994, 0.212648, 0.216484, 0.22057, 0.22497, 0.229337, 0.232884, 0.23596, 0.239326, 0.242921, 0.245595, 0.248666, 0.2521, 0.255899, 0.260253, 0.264172, 0.268089, 0.27221, 0.27688, 0.280961, 0.284639, 0.28845, 0.291873, 0.294659, 0.29668, 0.298346, 0.300048, 0.302431, 0.305583, 0.309162, 0.313943, 0.319651, 0.324986, 0.329565, 0.333289, 0.336565, 0.33924, 0.341681, 0.343442, 0.345074, 0.347293, 0.349824, 0.352279, 0.354626, 0.357285, 0.360091, 0.363057, 0.366477, 0.37011, 0.373876, 0.377648, 0.380938, 0.384106, 0.387288, 0.390137, 0.39199, 0.393832, 0.39634, 0.399255, 0.402285, 0.405265, 0.408943, 0.412963, 0.417683, 0.42203, 0.425902, 0.430032, 0.434444, 0.438648, 0.442674, 0.445648, 0.44771, 0.450105, 0.452818, 0.455475, 0.459257, 0.46497, 0.471776, 0.4804, 0.489469, 0.497992, 0.507131, 0.516506, 0.525018, 0.532744, 0.540899, 0.548129, 0.555484, 0.562471, 0.568386, 0.574721, 0.581799, 0.58892, 0.595488, 0.603247, 0.611145, 0.619414, 0.628492, 0.637634, 0.646924, 0.656813, 0.66681, 0.675362, 0.683059, 0.689791, 0.69601, 0.702039, 0.708148, 0.714768, 0.722988, 0.732344, 0.74167, 0.75073, 0.759785, 0.768961, 0.777719, 0.78556, 0.792373, 0.79914, 0.80549, 0.81113, 0.815989, 0.821, 0.826681, 0.832696, 0.838765, 0.844266, 0.850464, 0.85645, 0.862316, 0.86791, 0.873631, 0.879935, 0.887078, 0.895343, 0.903276, 0.910896, 0.917349, 0.922744, 0.927535, 0.931457, 0.93481, 0.938199, 0.942202, 0.946601, 0.950905, 0.954545, 0.957467, 0.96089, 0.964401, 0.967275, 0.968981, 0.97016, 0.971976, 0.973287, 0.973908, 0.973841, 0.97475, 0.977297, 0.981698, 0.986047, 0.990052, 0.994456, 0.998224, 1.0007, 1.00106, 1.00068, 1.00017, 1.00024, 1.00012, 0.99895, 0.997525, 0.995587, 0.994011, 0.991989, 0.990154, 0.988663, 0.987812, 0.988681, 0.990095, 0.990958, 0.990571, 0.990366, 0.989786, 0.988225, 0.985411, 0.981308, 0.977582, 0.973715, 0.96889, 0.963269, 0.958067, 0.954727, 0.952326, 0.95059, 0.949261, 0.949456, 0.949965, 0.948949, 0.946274, 0.94231, 0.937687, 0.93214, 0.926558, 0.920441, 0.915683, 0.912037, 0.908574, 0.904968, 0.901723, 0.898805, 0.895016, 0.891226, 0.886231, 0.880648, 0.874508, 0.867607, 0.859656, 0.851617, 0.844196, 0.83623, 0.828706, 0.822149, 0.817083, 0.812778, 0.808321, 0.803222, 0.798333, 0.793735, 0.787804, 0.780487, 0.772463, 0.764901, 0.75783, 0.750741, 0.743238, 0.737445, 0.73221, 0.725617, 0.717075, 0.707011, 0.696076, 0.684175, 0.670404, 0.65462, 0.640174, 0.627405, 0.6152, 0.603558, 0.592237, 0.58155, 0.57139, 0.559997, 0.546431, 0.532181, 0.517833, 0.503294, 0.488553, 0.474083, 0.460749, 0.449591, 0.439908, 0.431058, 0.42282, 0.414699, 0.406633, 0.398634, 0.39069, 0.382162, 0.373201, 0.364355, 0.355435, 0.346777, 0.337376, 0.32759, 0.31762, 0.307741, 0.29736, 0.286301, 0.274514, 0.262031, 0.249232, 0.235434, 0.220187, 0.204732, 0.18955, 0.174084, 0.158599, 0.143255, 0.128051, 0.113468, 0.0996657, 0.0862448, 0.0741762, 0.0637238, 0.054501, 0.0470933, 0.0412562, 0.0365495, 0.0324981, 0.0291943, 0.0259467, 0.0229876, 0.0201476, 0.0172495, 0.0144133, 0.0121181, 0.010861, 0.0100343, 0.00974476, 0.0103733, 0.0119886, 0.01364, 0.0151286, 0.0161257, 0.0168276, 0.0176267, 0.0177667, 0.0169867, 0.01598, 0.015241, 0.0144143, 0.0135886, 0.0125457, 0.0115524, 0.0113305, 0.0114295, 0.0114038, 0.0114352, 0.01208, 0.0132114, 0.0141905, 0.0147667, 0.0149648, 0.0148695, 0.0140505, 0.0127952, 0.0109514, 0.00864667, 0.00670762, 0.00527143, 0.0046019, 0.00473524, 0.00552476, 0.0065, 0.00768667, 0.0084381, 0.00831333, 0.00752286, 0.0062181, 0.00454952, 0.00287905, 0.00136476, 0.000487619, 0.000487619, 0.000514286, 0.000467619, 0.000337143, 0.00047619, 0.00104, 0.00124, 0.000652381, 0.0015, 0.00581905, 0.0120495, 0.0200286};
      
	  
	
  G4double PbWO_indexZero = 1.5861;
  G4double PbWO_nVec[1]   = { 1.1062 };
  G4double PbWO_lVec[1]   = { 270.63 };
  int sizeVect = sizeof(PbWO_nVec)/sizeof(*PbWO_nVec);
  
  const G4int nEntries_RI = 5;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 2.952 * eV, 4.08 * eV };
  G4double RefractiveIndex[nEntries_RI] =
    { CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(PhotonEnergy_RI[0])),
      CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(PhotonEnergy_RI[1])),
      CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(PhotonEnergy_RI[2])),
      CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(PhotonEnergy_RI[3])),
      CalculateSellmeier(sizeVect,PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(PhotonEnergy_RI[4]))       
    };
  
  const G4int nEntries_ABS = 70;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.25237 * eV, 1.26514 * eV, 1.27819 * eV, 1.2915 * eV, 1.3051 * eV, 1.31898 * eV, 1.33316 * eV, 1.34765 * eV, 1.36246 * eV, 1.3776 * eV,
      1.39308 * eV, 1.40891 * eV, 1.42511 * eV, 1.44168 * eV, 1.45864 * eV, 1.476 * eV, 1.49379 * eV, 1.512 * eV, 1.53067 * eV, 1.5498 * eV,
      1.56942 * eV, 1.58954 * eV, 1.61018 * eV, 1.63137 * eV, 1.65312 * eV, 1.67546 * eV, 1.69841 * eV, 1.722 * eV, 1.74626 * eV, 1.7712 * eV,
      1.79687 * eV, 1.8233 * eV, 1.85051 * eV, 1.87855 * eV, 1.90745 * eV, 1.93725 * eV, 1.968 * eV, 1.99974 * eV, 2.03253 * eV, 2.0664 * eV,
      2.10143 * eV, 2.13766 * eV, 2.17516 * eV, 2.214 * eV, 2.25426 * eV, 2.296 * eV, 2.33932 * eV, 2.38431 * eV, 2.43106 * eV, 2.47968 * eV,
      2.53029 * eV, 2.583 * eV, 2.63796 * eV, 2.69531 * eV, 2.7552 * eV, 2.81782 * eV, 2.88335 * eV, 2.952 * eV, 3.024 * eV, 3.0996 * eV,
      3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 3.64659 * eV, 3.7571 * eV, 3.87451 * eV, 3.99949 * eV, 4.13281 * eV };

      double att0 = 25;
      G4double Absorption[nEntries_ABS] =
    { 3110 *att0*mm, 3110 *att0*mm, 3110 *att0*mm, 3110 *att0*mm, 3110 *att0*mm, 3105 *att0*mm, 3105 *att0*mm, 3105 *att0*mm, 3105 *att0*mm, 3105 *att0*mm,
      3105 *att0*mm, 2745 *att0*mm, 2460 *att0*mm, 2230 *att0*mm, 2039 *att0*mm, 1877 *att0*mm, 1859 *att0*mm, 1826 *att0*mm, 1764 *att0*mm, 1760 *att0*mm,
      1664 *att0*mm, 1585 *att0*mm, 1471 *att0*mm, 1376 *att0*mm, 1272 *att0*mm, 1187 *att0*mm, 1114 *att0*mm, 1046 *att0*mm, 993.2 *att0*mm, 942.9 *att0*mm,
      898.8 *att0*mm, 856.9 *att0*mm, 821.7 *att0*mm, 794.2 *att0*mm, 767.7 *att0*mm, 746.5 *att0*mm, 725.6 *att0*mm, 710.7 *att0*mm, 695.3 *att0*mm, 686.2 *att0*mm,
      674.8 *att0*mm, 663.5 *att0*mm, 648.3 *att0*mm, 633.4 *att0*mm, 622.3 *att0*mm, 607.8 *att0*mm, 590.9 *att0*mm, 568.9 *att0*mm, 541.4 *att0*mm, 502.9 *att0*mm,
      467 *att0*mm, 430.2 *att0*mm, 390.1 *att0*mm, 345.3 *att0*mm, 298.9 *att0*mm, 256.7 *att0*mm, 219.8 *att0*mm, 185.4 *att0*mm, 150.9 *att0*mm, 116.4 *att0*mm,
      84.8 *att0*mm, 59.4 *att0*mm, 41.1 *att0*mm, 0 *att0*mm, 0 *att0*mm, 0 *att0*mm, 0 *att0*mm, 0 *att0*mm, 0 *att0*mm, 0 *att0*mm };
      

      TF1 * fLambdaMu = new TF1 ("fLambdaMu", "[0]/x/x/x/x + [1]*exp(-pow(x-[2],2)/2/[3]/[3] )");
      fLambdaMu->SetParameter(0, 3.11093e+10);
      fLambdaMu->SetParameter(1, 4.33418);
      fLambdaMu->SetParameter(2, 362.606);
      fLambdaMu->SetParameter(3, 14.991);
      
      
      TH1F * hAttenuation = new TH1F ("hAttenuation", "hAttenuation", nEntries_ABS, 1239.84/PhotonEnergy_ABS[nEntries_ABS-1], 1239.84/PhotonEnergy_ABS[0]);
      
      for (int iAbs = 0; iAbs < nEntries_ABS; iAbs++){
// 	Absorption[iAbs] = Absorption[iAbs]*10;
// 	Absorption[iAbs] = 1./(1/Absorption[iAbs] + mu_ind/1000*mm);

  	Absorption[iAbs] = 1./(1/Absorption[iAbs] + mu_ind*fLambdaMu->Eval(1239.84/PhotonEnergy_ABS[iAbs]*nm)/1000*mm);
	hAttenuation->Fill (1239.84/PhotonEnergy_ABS[iAbs] , Absorption[iAbs]);
// 	cout << " Absorption[" << 1239.84/PhotonEnergy_ABS[iAbs]*nm << "]  = " << Absorption[iAbs] << "correction : " << mu_ind*fLambdaMu->Eval(1239.84/PhotonEnergy_ABS[iAbs]*nm)/1000*mm << endl;
      }
      
      hAttenuation->Write();
      
      
      
  
  const G4int nEntries_SCY = 12;
  G4double ElectronEnergy_SCY[nEntries_SCY] =
    { 0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV,
      0.040 * MeV, 0.060 * MeV, 0.080 * MeV, 0.090 * MeV,
      0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV };
      
  G4double ScintilYield[nEntries_SCY] =
    { 0.10, 0.46, 0.60, 0.68,
      0.74, 0.80, 0.82, 0.84,
      0.87,  0.96,  0.98,  1.00 };
      
  for(int i = 0; i < nEntries_SCY; i++)    ScintilYield[i] = 0.3 * MeV * ScintilYield[i] * ElectronEnergy_SCY[i];
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty ("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,   nEntries_FAST);
  myMPT->AddProperty ("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  myMPT->AddProperty ("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
//   myMPT->AddProperty ("ELECTRONSCINTILLATIONYIELD", ElectronEnergy_SCY, ScintilYield, nEntries_SCY);
  myMPT->AddConstProperty ("SCINTILLATIONYIELD", 40/MeV );
  myMPT->AddConstProperty ("RESOLUTIONSCALE", 1.0); //3.2 default value
  myMPT->AddConstProperty ("FASTTIMECONSTANT", 5.*ns);
  myMPT->AddConstProperty ("SLOWTIMECONSTANT", 15.*ns);
  myMPT->AddConstProperty ("YIELDRATIO", 0.3);
  myMPT->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);
  
  mat->SetMaterialPropertiesTable (myMPT);
  
  return mat;
}



G4double MyMaterials::CalculateSellmeier (int size, G4double indexZero, G4double *nVec, G4double *lVec, G4double wavelength)
{
  /*------http://gentitfx.fr/SLitrani/code/SLitraniCode/TLitSellmeier.html----*/
  
  float partial = indexZero * indexZero;
  float sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += nVec[i] * nVec[i] / (1 - lVec[i] * lVec[i] / (wavelength*wavelength));
  }
  
  partial += sum;
  partial += 1;
  
  //G4cout << "Wavelength: " << wavelength << " -> rifr. index: " << sqrt(partial) << G4endl;
  
  return sqrt(partial);
}



G4double MyMaterials::fromEvToNm (G4double energy)
{
  return 1239.84187 / energy;
}

G4double MyMaterials::fromNmToEv (G4double wavelength)
{
  return 1239.84187 / wavelength;
}
