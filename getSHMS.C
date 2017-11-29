#include "SHMSMagnets.h"

////////////////////
// global variables:
////////////////////
const double tol = 1E-5;
int debug = 1;

//////////////////////////////////////
// input the desired momentum in [GeV]
//////////////////////////////////////
int main(int argc, char *argv[]){

  double P = atof(argv[1]);


  double eta[5] = {10000, 10000, 10000, 10000, 10000};
  int ii[5] = {0, 0, 0, 0, 0};
  double I_iter[5] = {calcLinearHB(P), calcLinearQ1(P), calcLinearQ2(P), calcLinearQ3(P), calcLinearDip(P)};
  double I_linear[5] = {calcLinearHB(P), calcLinearQ1(P), calcLinearQ2(P), calcLinearQ3(P), calcLinearDip(P)};

  char const *magnets[5] = {"HB","Q1","Q2","Q3","Dipole"};

  static double (*cpratio[5])(double a, double b) = {calcPratioHB,calcPratioQ1,calcPratioQ2,calcPratioQ3,calcPratioDip};
  static double (*bratio[5])(double a) = {calcBetaRatioHB,calcBetaRatioQ1,calcBetaRatioQ2,calcBetaRatioQ3,calcBetaRatioDip};
  static double (*lratio[5])(double a) = {calcLeffRatioHB,calcLeffRatioQ1,calcLeffRatioQ2,calcLeffRatioQ3,calcLeffRatioDip};

    static double (*error[5])(double a) = {calcErrorHB,calcErrorQ1,calcErrorQ2,calcErrorQ3,calcErrorDip};
  
  for (int kk=0; kk<5; kk++){
  
    while (abs(eta[kk])>tol){
      eta[kk] = cpratio[kk](P, I_iter[kk]);
      //cout<<"\t"<<ii<<"\t"<<eta<<"\t"<<Iiter<<"\t"<<beta(Iiter)<<endl;
      if (eta[kk] > 0) {I_iter[kk] = I_iter[kk]*(1-abs(eta[kk])/2.0);}
      else {I_iter[kk] = I_iter[kk]*(1+abs(eta[kk])/2.0);}
      
      ii[kk]++;
      if (abs(ii[kk]) > 100) {break;}
    }

    cout<<"Magnet:\t"<<magnets[kk]<<"\tVersion:\t"<<getVersion(kk)<<endl;

    if (debug == 1){
      cout<<"\tRequested energy:\t"<<P<<" [GeV]"<<endl;
      cout<<"\tRecommended Iset: "<<I_iter[kk]<<" [A], from initial guess: "<<I_linear[kk]<<" [A]."<<endl;
      cout<<"\tbeta ratio: "<<bratio[kk](I_iter[kk])<<" leff ratio: "<<lratio[kk](I_iter[kk])<<endl;
      cout<<"\tResulting difference from nominal: "<<eta[kk]<<endl;
      cout<<"\tUncertainty: +/-"<<error[kk](I_iter[kk])<<"[%]"<<endl;
    }
    else{
      cout<<"\tRecommended Iset: "<<I_iter[kk]<<" [A], from initial guess: "<<I_linear[kk]<<" [A]."<<endl;
    }
  }

  return 0;

}
