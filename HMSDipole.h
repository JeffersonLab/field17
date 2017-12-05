#include "TMath.h"
#include "TROOT.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

/**************************************************
 * If anything is changed, increase version number 
 * and commit to github. 
 * Experts only!
 * Errors are estimated from data!
 ***************************************************/

// version number per magnet:
const int version_dip = 0;


double getVersion(){
  return version_dip;
}

/////////////////////////////
// variables for dipole:
/////////////////////////////
const double betaG_dip = 8.94363583242782471E-03; //units of [kG/A]
const double P0_dip = 3.26687082629409332E-03; //units of [GeV/A]
const double leffG_dip = 5.28744767; //units of [m]

//////////////////
//Dipole parameters:
//////////////////

// input units [GeV], output units [A] 
double calcLinearDip(double P){
  
  return P/P0_dip;
}

//outputs [kG/A]
double getBetaGoldenDip(){
  return betaG_dip;
}

// input units [A], output units [unitless]
double calcBetaRatioDip(double I_iter){

  double beta = (7.76495E-29*pow(I_iter,8) - 9.59365E-25*pow(I_iter,7) +4.80895E-21*pow(I_iter,6) -1.25206E-17*pow(I_iter,5) +1.81193E-14*pow(I_iter,4) - 1.48202E-11*pow(I_iter,3) +6.77632E-9 *pow(I_iter,2) -1.71809E-6*I_iter + 0.00916971 );
  
  return beta/betaG_dip;
}

// input units [A], output units [unitless]
double calcLeffRatioDip(double I_iter){

  double leff = leffG_dip*  (1 + (I_iter>1220)*(2.5173E-12*pow(I_iter-1220,3)-1.17767E-8*pow(I_iter-1220,2)-3.60694E-6*(I_iter-1220)));

  return leff/leffG_dip;
}

// input units [GeV], [A], output units [unitless]
double calcPratioDip(double P, double I_iter){

  double I_linear = calcLinearDip(P);

  double betaRatio = calcBetaRatioDip(I_iter);

  double leffRatio = calcLeffRatioDip(I_iter); 
  
  double ratio = (I_iter/I_linear)*(betaRatio)*(leffRatio);
  
  return ratio-1;
}

//input units [A], return units [%]
double calcErrorDip(double I_iter){
  return 1.0-calcLeffRatioDip(I_iter) + 0.15;
}
