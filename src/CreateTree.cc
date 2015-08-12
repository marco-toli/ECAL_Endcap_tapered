#include "CreateTree.hh"



CreateTree* CreateTree::fInstance = NULL;



CreateTree::CreateTree(TString name, bool energy_fiber, bool init_data, bool pos_fiber, bool opPhotons, bool timing, bool double_ro)
{
  if( fInstance )
  {
    return;
  }
  
  this -> ENERGY_FIBER 	= energy_fiber;
  this -> INIT_DATA    	= init_data;
  this -> POS_FIBER    	= pos_fiber;
  this -> OPPHOTONS     = opPhotons;
  this -> TIMING        = timing;
  this -> DOUBLE        = double_ro;
  
  this -> fInstance = this;
  this -> fname     = name;
  this -> ftree     = new TTree(name,name);
  
  this->GetTree()->Branch("Event",&this->Event,"Event/I");
  
//   this->GetTree()->Branch("Tot_phot_cer",		   &this->Tot_phot_cer,			 "Tot_phot_cer/F");
//   this->GetTree()->Branch("Tot_phot_scint",		   &this->Tot_phot_scint,			 "Tot_phot_scint/F");
  
//   this->GetTree()->Branch("Total_delta_world",        &this->Total_delta_world,        "Total_delta_world/F");
//   this->GetTree()->Branch("Total_energy_world",       &this->Total_energy_world,       "Total_energy_world/F");
//   this->GetTree()->Branch("Total_ion_energy_world",   &this->Total_ion_energy_world,   "Total_ion_energy_world/F");
//   this->GetTree()->Branch("Total_nonion_energy_world",&this->Total_nonion_energy_world,"Total_nonion_energy_world/F");
  
//   this->GetTree()->Branch("Total_em_energy",&this->Total_em_energy,"Total_em_energy/F");
  
  if( this -> INIT_DATA )
  {
 //   this->GetTree()->Branch("InitialEnergy",&this->InitialEnergy,"InitialEnergy/F");
    
    this->GetTree()->Branch("InitialPositionX",&this->InitialPositionX,"InitialPositionX/F");
    this->GetTree()->Branch("InitialPositionY",&this->InitialPositionY,"InitialPositionY/F");
    this->GetTree()->Branch("InitialPositionZ",&this->InitialPositionZ,"InitialPositionZ/F");
    
//    this->GetTree()->Branch("InitalMomentumDirectionX",&this->InitalMomentumDirectionX,"InitalMomentumDirectionX/F");
//    this->GetTree()->Branch("InitalMomentumDirectionY",&this->InitalMomentumDirectionY,"InitalMomentumDirectionY/F");
//    this->GetTree()->Branch("InitalMomentumDirectionZ",&this->InitalMomentumDirectionZ,"InitalMomentumDirectionZ/F");
  }
    
  if( this -> ENERGY_FIBER)
  {
    this->GetTree()->Branch("Total_energy_dead_material",&this->Total_energy_dead_material,"Total_energy_dead_material/F");
    this->GetTree()->Branch("Plastic_tag_ID",&this->Plastic_tag_ID,"Plastic_tag_ID/I");
    this->GetTree()->Branch("Total_energy",&this->Total_energy,"Total_energy/F");
    this->GetTree()->Branch("Total_ion_energy",&this->Total_ion_energy,"Total_ion_energy/F");	  
    this->GetTree()->Branch("Total_ion_energy_att",&this->Total_ion_energy_att,"Total_ion_energy_att[13]/F");
    this->GetTree()->Branch("Total_ion_energy_att_rear",&this->Total_ion_energy_att_rear,"Total_ion_energy_att_rear[13]/F");
    this->GetTree()->Branch("Total_ion_energy_att_front",&this->Total_ion_energy_att_front,"Total_ion_energy_att_front[13]/F");
  }
  
  if( this -> POS_FIBER)
  { 
    this->GetTree()->Branch("depositionX",&depositionX);
    this->GetTree()->Branch("depositionY",&depositionY);
    this->GetTree()->Branch("depositionZ",&depositionZ);  
    this->GetTree()->Branch("Energy_deposited",&Energy_deposited);
    this->GetTree()->Branch("Time_deposit",&Time_deposit);
  }
  
  if( this -> OPPHOTONS)
  {
    this->GetTree()->Branch("opPhoton_n",&this->opPhoton_n,"opPhoton_n/I");
//    this->GetTree()->Branch("opPhoton_n_type",&this->opPhoton_n_type);
    
//    this->GetTree()->Branch("opPhoton_n_ext",&this->opPhoton_n_ext,"opPhoton_n_ext/I");
//    this->GetTree()->Branch("opPhoton_n_ext_type",&this->opPhoton_n_ext_type);
//    this->GetTree()->Branch("opPhoton_n_ext_end",&this->opPhoton_n_ext_end);
    
    this->GetTree()->Branch("opPhoton_n_det",&this->opPhoton_n_det,"opPhoton_n_det/I");
//    this->GetTree()->Branch("opPhoton_n_det_type",&this->opPhoton_n_det_type);
    this->GetTree()->Branch("opPhoton_n_det_end",&this->opPhoton_n_det_end);
       
//    this->GetTree()->Branch("opPhoton_waveLength_det",&opPhoton_waveLength_det);
//    this->GetTree()->Branch("opPhoton_time_det",&opPhoton_time_det);
//    this->GetTree()->Branch("opPhoton_trackLength_det",&opPhoton_trackLength_det);
  }
  
  this->Clear();
}



CreateTree::~CreateTree()
{}



bool CreateTree::Write()
{
  TString filename = this->GetName();
  filename+=".root";
  TFile* file = new TFile(filename,"RECREATE");
  this->GetTree()->Write();
  file->Write();
  file->Close();
  return true;
}



void CreateTree::Clear()
{
  Event	= 0;
  /*
  Tot_phot_cer = 0;
  Tot_phot_scint = 0;*/
  /*
  Total_delta_world         = 0;
  Total_energy_world        = 0;
  Total_ion_energy_world    = 0;
  Total_nonion_energy_world = 0;*/
  
  if( this->INIT_DATA )
  {
    InitialEnergy = 0;
    
    InitialPositionX = 0;
    InitialPositionY = 0;
    InitialPositionZ = 0;
    
    InitalMomentumDirectionX = 0;
    InitalMomentumDirectionY = 0;
    InitalMomentumDirectionZ = 0;
  }
  
  if( this->ENERGY_FIBER )
  {

	Total_energy_dead_material = 0;
	Plastic_tag_ID = -1;
        Total_energy = 0;
        Total_ion_energy = 0;	  		    	  
	for (int j = 0; j< 13; j++)
	{
	  Total_ion_energy_att      [j] = 0;
	  Total_ion_energy_att_rear [j] = 0;
	  Total_ion_energy_att_front[j] = 0;
	}
  }
  
  if( this->POS_FIBER )
  {
    depositionX.clear();		
    depositionY.clear();		
    depositionZ.clear();
    Energy_deposited.clear();
    Time_deposit.clear();
  }
  
  if( this->OPPHOTONS )
  {

    opPhoton_n = 0;
    opPhoton_n_type.clear();
      
    opPhoton_n_ext = 0;
    opPhoton_n_ext_type.clear();
    opPhoton_n_ext_end.clear();
      
    opPhoton_n_det = 0;
    opPhoton_n_det_type.clear();
    opPhoton_n_det_end.clear();

    opPhoton_waveLength_det.clear();
    opPhoton_time_det.clear();
    opPhoton_trackLength_det.clear();
  }
}
