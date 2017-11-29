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
const int nmag = 5;
int version_hb = 0;
int version_q1 = 0;
int version_q2 = 0;
int version_q3 = 0;
int version_dip = 0;

const int version[nmag] = {version_hb, version_q1, version_q2, version_q3, version_dip};

double getVersion(int ii){
  return version[ii];
}

/////////////////////////////
// variables for each magnet:
/////////////////////////////

//HB:
double betaG_hb = 6.48514620500684636e-03; //units of [kG/A]
double P0_hb = 0.00307690156; //units of [GeV/A]
double leffG_hb = 80.209; //units of [cm]

//Q1:
double betaG_q1 = 7.10342873019000065e-03; //units of [kG/A]
double P0_q1 =  0.0049948; //units of [GeV/A]
double leffG_q1 = 1.863; //units of [m]

//Q2:
double betaG_q2 = 9.43647134013299999e-03; //units of [kG/A]
double P0_q2 = 0.00300464; //units of [GeV/A]
double leffG_q2 = 1; //assume linear

//Q3:
double betaG_q3 = 9.72834595398900000e-03; //units of [kG/A]
double P0_q3 = 0.004519309778; //units of [GeV/A]
double leffG_q3 = 1; //assume linear

//dipole:
double betaG_dip = 1.18479459998974725e-02; //units of [kG/A]
double P0_dip = 3.18840579710144957e-03; //units of [GeV/A]
double leffG_dip = 1; //assume linear


//ordering: HB,Q1,Q2,Q3,Dipole
double betaG[nmag] = {betaG_hb, betaG_q1, betaG_q2, betaG_q3, betaG_dip};
double P0[nmag] = {P0_hb, P0_q1, P0_q2, P0_q3, P0_dip};
double leffG[nmag] = {leffG_hb, leffG_q1, leffG_q2, leffG_q3, leffG_dip};

//////////////////
//HB parameters:
//////////////////

// input units [GeV], output units [A] 
double calcLinearHB(double P){
  
  return P/P0[0];
}

// input units [A], output units [unitless]
double calcBetaRatioHB(double I_iter){

  double beta = (6.77648E-25*pow(I_iter,6) - 8.43358E-21*pow(I_iter,5) + 3.60792E-17*pow(I_iter,4) - 6.38532E-14*pow(I_iter,3) + 3.14903E-11*pow(I_iter,2) - 3.06624E-08*I_iter + 0.00650637);

  return beta/betaG[0];
}

// input units [A], output units [unitless]
double calcLeffRatioHB(double I_iter){

  double leff = leffG[0]* (1 + (I_iter>1246)*(2.018E-12*pow(I_iter-1246,3)-9.44239E-9*pow(I_iter-1246,2)-2.36088E-7*(I_iter-1246)));

  return leff/leffG[0];
}

// input units [GeV], [A], output units [unitless]
double calcPratioHB(double P, double I_iter){

  double I_linear = calcLinearHB(P);

  double betaRatio = calcBetaRatioHB(I_iter);

  double leffRatio = calcLeffRatioHB(I_iter); 
  
  double ratio = (I_iter/I_linear)*(betaRatio)*(leffRatio);
  
  return ratio-1;
}

//input units [A], return units [%]
double calcErrorHB(double I_iter){
  return (10.0*(1.0-calcLeffRatioHB(I_iter))) + 0.1;
}

////////////////
//Q1 parameters:
////////////////

// input units [GeV], output units [A] 
double calcLinearQ1(double P){
  
  return P/P0[1];
}

// input units [A], output units [unitless]
double calcBetaRatioQ1(double I_iter){

  double beta = (2.24863E-23*pow(I_iter,6) - 1.56067E-19*pow(I_iter,5) + 3.72383E-16*pow(I_iter,4) - 4.12478E-13*pow(I_iter,3) + 2.29043E-10*pow(I_iter,2) - 6.2683E-08*I_iter + 0.00711028);

  return beta/betaG[1];
}

// input units [A], output units [unitless]
double calcLeffRatioQ1(double I_iter){

  double leff = leffG[1]* (1 + (I_iter>1220)*(4.60576E-12*pow(I_iter-1220,3)-1.00781E-8*pow(I_iter-1220,2)+7.17211E-7*(I_iter-1220)));

  return leff/leffG[1];
}

// input units [GeV], [A], output units [unitless]
double calcPratioQ1(double P, double I_iter){

  double I_linear = calcLinearQ1(P);

  double betaRatio = calcBetaRatioQ1(I_iter);

  double leffRatio = calcLeffRatioQ1(I_iter); 
  
  double ratio = (I_iter/I_linear)*(betaRatio)*(leffRatio);
  
  return ratio-1;
}

//input units [A], return units [%]
double calcErrorQ1(double I_iter){
  return (100.0*(1.0-calcLeffRatioQ1(I_iter))) + 0.1;
}

////////////////
//Q2 parameters:
////////////////

// input units [GeV], output units [A] 
double calcLinearQ2(double P){
  
  return P/P0[2];
}

// input units [A], output units [unitless]
double calcBetaRatioQ2(double I_iter){

  double beta = (-4.2749E-19*pow(I_iter,4) + 4.46166E-15*pow(I_iter,3) - 1.26893E-11*pow(I_iter,2) - 1.80224E-9*I_iter + 0.00944297);

  return beta/betaG[2];
}

// input units [A], output units [unitless]
double calcLeffRatioQ2(double I_iter){

  double leff = leffG[2];

  return leff/leffG[2];
}

// input units [GeV], [A], output units [unitless]
double calcPratioQ2(double P, double I_iter){

  double I_linear = calcLinearQ2(P);

  double betaRatio = calcBetaRatioQ2(I_iter);

  double leffRatio = calcLeffRatioQ2(I_iter); 
  
  double ratio = (I_iter/I_linear)*(betaRatio)*(leffRatio);
  
  return ratio-1;
}

//input units [A], return units [%]
double calcErrorQ2(double I_iter){
  return (100.0*(1.0-calcBetaRatioQ2(I_iter))) + 0.25;
}

////////////////
//Q3 parameters:
////////////////

// input units [GeV], output units [A] 
double calcLinearQ3(double P){
  
  return P/P0[3];
}

// input units [A], output units [unitless]
double calcBetaRatioQ3(double I_iter){

  double beta = (5.57412E-24*pow(I_iter,6) - 4.57913E-20*pow(I_iter,5) + 1.34093E-16*pow(I_iter,4) - 1.5001E-13*pow(I_iter,3) + 1.28572E-12*pow(I_iter,2) + 2.34223E-12*I_iter + 0.00973899);

  return beta/betaG[3];
}

// input units [A], output units [unitless]
double calcLeffRatioQ3(double I_iter){

  double leff = leffG[3];

  return leff/leffG[3];
}

// input units [GeV], [A], output units [unitless]
double calcPratioQ3(double P, double I_iter){

  double I_linear = calcLinearQ3(P);

  double betaRatio = calcBetaRatioQ3(I_iter);

  double leffRatio = calcLeffRatioQ3(I_iter); 
  
  double ratio = (I_iter/I_linear)*(betaRatio)*(leffRatio);
  
  return ratio-1;
}

//input units [A], return units [%]
double calcErrorQ3(double I_iter){
  return (10.0*(1.0-calcBetaRatioQ3(I_iter))) + 0.1;
}
////////////////////
//Dipole parameters:
////////////////////

// input units [GeV], output units [A] 
double calcLinearDip(double P){
  
  return P/P0[4];
}

// input units [A], output units [unitless]
double calcBetaRatioDip(double I_iter){

  double beta = (-9.72072E-25*pow(I_iter,6) + 9.79429E-21*pow(I_iter,5) - 3.80396E-17*pow(I_iter,4) + 7.02145E-14*pow(I_iter,3) - 5.80238E-11*pow(I_iter,2) + 1.88857E-9*I_iter + 0.0118584);

  return beta/betaG[4];
}

// input units [A], output units [unitless]
double calcLeffRatioDip(double I_iter){

  double leff = leffG[4];

  return leff/leffG[4];
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
  return (10.0*(1.0-calcBetaRatioDip(I_iter)))/2.0 + 0.01;
}
