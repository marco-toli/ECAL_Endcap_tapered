#include "SteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "EventAction.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"
#include "CreateTree.hh"
#include "MyMaterials.hh"

#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TF1.h"


SteppingAction::SteppingAction()
{}



SteppingAction::~SteppingAction()
{}



void SteppingAction::UserSteppingAction(const G4Step * theStep)
{
  G4Track* theTrack = theStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  
//   cout << " step " << endl;
  
  
  G4StepPoint* thePrePoint  = theStep->GetPreStepPoint();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePrePV  = thePrePoint ->GetPhysicalVolume();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
  G4String thePrePVName  = ""; if( thePrePV )  thePrePVName  = thePrePV  -> GetName();
  G4String thePostPVName = ""; if( thePostPV ) thePostPVName = thePostPV -> GetName();

   G4LogicalVolume* thePreLV  = thePrePV ->GetLogicalVolume();
   G4LogicalVolume* thePostLV = thePostPV->GetLogicalVolume();
   G4String thePreLVName  = ""; thePreLVName  = thePreLV  -> GetName();
//    G4String thePostLVName = ""; if( thePostLV ) thePostLVName = thePostLV -> GetName();


//    cout << "defining step volumes ... " << endl;
    

  // optical photon
  if( particleType == G4OpticalPhoton::OpticalPhotonDefinition() )
  {
//      cout << "optical photon ! " << endl;
    G4String processName = " "; if (theTrack->GetCreatorProcess())  processName = theTrack->GetCreatorProcess()->GetProcessName();
//     if (processName == "Cerenkov") CreateTree::Instance()->Tot_phot_cer += 1;
//     if (processName == "Scintillation") CreateTree::Instance()->Tot_phot_scint += 1;
    if( !CreateTree::Instance()->Timing() || processName == "Cerenkov")
      theTrack->SetTrackStatus(fKillTrackAndSecondaries);
    
    // do this cycle only IF info on optical photons is needed
    if (CreateTree::Instance()->OpPhotons() && processName != "Cerenkov")
    {
      //---------------------------------------------------------
      // storing time, energy and position of all optical photons

//       cout << " tracing optical photons ... " << endl;
      
      G4int nStep = theTrack -> GetCurrentStepNumber();
      
      // produced photons
      // 	  if (thePostPVName == name2 ) cout << "pre PV name = " << thePrePVName << " :: the post PV = " << thePostPVName  << endl;
      if (theTrack->GetVolume()->GetName() == "EE_phys" && (nStep == 1)) {// 
	CreateTree::Instance()->opPhoton_n ++;
	if (processName == "Cerenkov") CreateTree::Instance()->opPhoton_n_type.push_back(0);
	if (processName == "Scintillation") CreateTree::Instance()->opPhoton_n_type.push_back(1);
	CreateTree::Instance()->opPhoton_time.push_back(theTrack->GetGlobalTime()/nanosecond);
      }
      /*
      // extracted photons
      if ((thePrePVName == "EE_phys" && thePostPVName == "Grease_rear_phys")	||
	  (thePrePVName == "EE_phys" && thePostPVName == "Grease_front_phys")     ) {
	
	CreateTree::Instance()->opPhoton_n_ext ++;
	//tag for photon type
	if (processName == "Cherenkov") CreateTree::Instance()->opPhoton_n_ext_type.push_back(0);
	if (processName == "Scintillation") CreateTree::Instance()->opPhoton_n_ext_type.push_back(1);
	
	//tag for detector type: front or rear
	if (thePostPVName == "Grease_rear_phys") CreateTree::Instance()->opPhoton_n_ext_end.push_back(0);
	if (thePostPVName == "Grease_front_phys") CreateTree::Instance()->opPhoton_n_ext_end.push_back(1);
      }*/

      
      //----------------------------------------------
      // detected photons
/*
      if ((thePrePVName == "Det_layer_rear_phys" && thePostPVName == "Det_rear_phys") ||
	  (thePrePVName == "Det_layer_front_phys" && thePostPVName == "Det_front_phys")      ) {	// detected at photodetector iCrystal

	CreateTree::Instance()->opPhoton_n_det++;
	//tag for photon type
	if (processName == "Cherenkov") CreateTree::Instance()->opPhoton_n_det_type.push_back(0);
	if (processName == "Scintillation") CreateTree::Instance()->opPhoton_n_det_type.push_back(1);
	//tag for detector type: front or rear
	if (thePrePVName == "Det_layer_rear_phys") CreateTree::Instance()->opPhoton_n_det_end.push_back(0);
	if (thePrePVName == "Det_layer_front_phys") CreateTree::Instance()->opPhoton_n_det_end.push_back(1);
	
	CreateTree::Instance()->opPhoton_waveLength_det.push_back(MyMaterials::fromEvToNm(theTrack->GetTotalEnergy()/eV) );
	CreateTree::Instance()->opPhoton_time_det.push_back( theTrack->GetGlobalTime()/nanosecond );
	CreateTree::Instance()->opPhoton_trackLength_det.push_back( theTrack->GetTrackLength()/m );
	
      }//definition of detected photon
*/
	//new looser definition of detected photons
      if ((thePrePVName == "Grease_rear_phys" && thePostPVName != "EE_phys") ||
          (thePrePVName == "Grease_front_phys" && thePostPVName != "EE_phys")      ) {        // detected at photodetector iCrystal

        CreateTree::Instance()->opPhoton_n_det++;
        //tag for photon type
//        if (processName == "Cherenkov") CreateTree::Instance()->opPhoton_n_det_type.push_back(0);
//        if (processName == "Scintillation") CreateTree::Instance()->opPhoton_n_det_type.push_back(1);
        //tag for detector type: front or rear
        if (thePrePVName == "Grease_rear_phys") CreateTree::Instance()->opPhoton_n_det_end.push_back(0);
        if (thePrePVName == "Grease_front_phys") CreateTree::Instance()->opPhoton_n_det_end.push_back(1);

//        CreateTree::Instance()->opPhoton_waveLength_det.push_back(MyMaterials::fromEvToNm(theTrack->GetTotalEnergy()/eV) );
//        CreateTree::Instance()->opPhoton_time_det.push_back( theTrack->GetGlobalTime()/nanosecond );
//        CreateTree::Instance()->opPhoton_trackLength_det.push_back( theTrack->GetTrackLength()/m );
	theTrack->SetTrackStatus(fKillTrackAndSecondaries);
      }//definition of detected photon

      
    } // do this cycle only IF info on optical photons is needed
  } // optical photon
  
  
  // non optical photon
  else
  {
    G4TouchableHandle thePreTouch = thePrePoint -> GetTouchableHandle();
    G4VPhysicalVolume* thePreVolume = thePreTouch -> GetVolume();
    G4LogicalVolume* thePrePVLog = thePreVolume -> GetLogicalVolume();
    G4String thePrePVLogName = thePrePVLog -> GetName();
    
    /*
    G4TouchableHandle thePostTouch = thePostPoint -> GetTouchableHandle();
    G4VPhysicalVolume* thePostVolume = thePostTouch -> GetVolume();
    G4LogicalVolume* thePostPVLog = thePostVolume -> GetLogicalVolume();
    G4String thePosPVLogName;  if (thePostPVLog) thePosPVLogName = thePostPVLog -> GetName();*/
    
    
    float delta = thePrePoint->GetTotalEnergy()/GeV - thePostPoint->GetTotalEnergy()/GeV;
    float energy = theStep->GetTotalEnergyDeposit()/GeV;
    float time_dep =  theTrack->GetGlobalTime()/nanosecond ;
    float ion_energy = theStep->GetTotalEnergyDeposit()/GeV - theStep->GetNonIonizingEnergyDeposit()/GeV;

    if( delta > 0  && thePrePVLogName == "Dead_material_log")    CreateTree::Instance()->Total_energy_dead_material += energy;
   
    // tag using "plastic" scintillator
    if( thePrePVLogName == "Plastic_tag_log")   
    {
      if (thePrePVName == "Plastic_tag_phys1")       CreateTree::Instance()->Plastic_tag_ID = 1;
      if (thePrePVName == "Plastic_tag_phys2")       CreateTree::Instance()->Plastic_tag_ID = 2;
      if (thePrePVName == "Plastic_tag_phys3")       CreateTree::Instance()->Plastic_tag_ID = 3;
      if (thePrePVName == "Plastic_tag_phys4")       CreateTree::Instance()->Plastic_tag_ID = 4;
    }
    
    if( delta > 0  && thePrePVLogName == "EE_log")
    {	   

      G4ThreeVector pos = thePostPoint -> GetPosition();
      CreateTree::Instance()->Total_energy      += energy;
      CreateTree::Instance()->Total_ion_energy    += ion_energy;
      
     // define parameter for effective attenuation curve along z (crystal length)
     
     
//      cout << " att coeff = " <<  fAtt(par0, par1, par2, pos[2])/par0 << endl;
     for (int iAtt = 0; iAtt < nATT; iAtt++) {
	 CreateTree::Instance()->Total_ion_energy_att[iAtt]    	+= ion_energy* fAtt(par0[iAtt], par1[iAtt], par2[iAtt], par3[iAtt], par4[iAtt], pos[2] + 110);	// if normalization / fAtt(par0[iAtt], par1[iAtt], par2[iAtt], 220);
	 CreateTree::Instance()->Total_ion_energy_att_rear[iAtt]    	+= ion_energy* fAttRear(par0_r[iAtt], par1_r[iAtt], par2_r[iAtt], pos[2] + 110);			// if normalization / fAtt(par0[iAtt], par1[iAtt], par2[iAtt], 220);
	 CreateTree::Instance()->Total_ion_energy_att_front[iAtt]    	+= ion_energy* fAttFront(par0_f[iAtt], par1_f[iAtt], par2_f[iAtt], pos[2] + 110);			// if normalization / fAtt(par0[iAtt], par1[iAtt], par2[iAtt], 220);
     }
     

      
      if( CreateTree::Instance()->Pos_fiber() )
      {
        	
        CreateTree::Instance() -> depositionX.push_back(pos[0]);		
        CreateTree::Instance() -> depositionY.push_back(pos[1]);
        CreateTree::Instance() -> depositionZ.push_back(pos[2]);
        CreateTree::Instance() -> Energy_deposited.push_back(energy);
	CreateTree::Instance() -> Time_deposit.push_back(time_dep);
// 	cout << " depositing ... ("  << pos[0] << "," << pos[1] << "," << pos[2] << ") :: energy = " << energy << endl;
      }
    }  //inside crystal
  } // non optical photon
  
}
