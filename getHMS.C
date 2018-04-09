#include "HMSDipole.h"

////////////////////
// global variables:
////////////////////
const double tol = 1E-5;
int debug = 0;

//////////////////////////////////////
// input the desired momentum in [GeV]
//////////////////////////////////////
int main(int argc, char *argv[]){

  double P = atof(argv[1]);
  P = abs(P);
  double eta = 10000;
  int ii = 0;
  double I_iter = calcLinearDip(P);
  double I_linear = I_iter;
  double betaG = getBetaGoldenDip();
  double Blin = betaG*I_linear;
  double Biter = Blin;
  double bratio;
  double lratio;

  char const *magnet = "HMS_Dipole";
  
  while (fabs(eta)>tol){
      eta = calcPratioDip(P, I_iter);

      if (eta > 0) {I_iter = I_iter*(1-fabs(eta)/2.0);}
      else {I_iter = I_iter*(1+fabs(eta)/2.0);}

      lratio = calcLeffRatioDip(I_iter);
      bratio = calcBetaRatioDip(I_iter)*betaG;
      Biter = (lratio * bratio * I_iter)/10.0;

      ii++;
      if (ii > 100) {break;}
    }

  //includes results from Mark's saturation study
  double satFactor = 1.0;
  if (P>=5.3){
    satFactor = 0.01*P+0.948;
  }

  Biter = Biter*satFactor;
  I_iter = I_iter*satFactor;

  cout<<"Magnet:\t"<<magnet<<"\tVersion:\t"<<getVersion()<<endl;
  cout<<"Set the HMS Dipole by NMR"<<endl;
    if (debug == 1){
      cout<<"\tRequested energy:\t"<<P<<" [GeV]"<<endl;
      cout<<"\tSaturation:\t"<<satFactor<<endl;
      cout<<"\tbeta ratio: "<<calcBetaRatioDip(I_iter)<<" leff ratio: "<<calcLeffRatioDip(I_iter)<<endl;
      cout<<"\tResulting difference from nominal: "<<eta<<endl;
      cout<<"\tUncertainty: +/-"<<calcErrorDip(I_iter)<<"[%]"<<endl;
    }
    if (P<0.01){
      cout<<"\tRecommended NMR B: "<<0.0<<" [T]"<<endl;
      cout<<"\tCorresponds to approx Iset: "<<0.0<<" [A]."<<endl;
    }
    else{
      cout<<"\tRecommended NMR B: "<<Biter<<" [T]"<<endl;
      cout<<"\tCorresponds to approx Iset: "<<I_iter<<" [A]."<<endl;
    }

  return 0;

}
