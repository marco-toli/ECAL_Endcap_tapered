// Martin Goettlich @ DESY
//

#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"
#include <iostream>

#include "TFile.h"
#include "TF1.h"
#include "TTree.h"
#include "TString.h"
#include <vector>



  const int nATT = 13;
  double par0[nATT], par1[nATT], par2[nATT], par3[nATT], par4[nATT];
  double par0_r[nATT], par1_r[nATT], par2_r[nATT];
  double par0_f[nATT], par1_f[nATT], par2_f[nATT];

  //class SteppingMessenger;
  
class SteppingAction : public G4UserSteppingAction
{
public:

  SteppingAction();
  ~SteppingAction();
  virtual void UserSteppingAction(const G4Step*);
  

  

  double fAtt (double par0, double par1, double par2, double par3, double par4, double z)
  {
    
    double att = par0*exp((z-220)/par1) + par2 + par3*exp((-z)/par4);
    return att;
    
  }

  double fAttRear (double par0, double par1, double par2, double z)
  {

    double att = par0*exp((z-220)/par1) + par2;
    return att;

  }

  double fAttFront (double par0, double par1, double par2, double z)
  {

    double att = par0*exp((-z)/par1) + par2;
    return att;

  }
  
     
  //void SetOneStepPrimaries(G4bool b){oneStepPrimaries=b;}
  //G4bool GetOneStepPrimaries(){return oneStepPrimaries;}
  
// private:

//   G4bool oneStepPrimaries;
//   SteppingMessenger* steppingMessenger;
};

#endif
