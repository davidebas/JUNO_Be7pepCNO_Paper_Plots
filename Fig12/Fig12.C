#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig12() {	

	ifstream Read;
	Read.open("N13-O15.txt",ios::in);

	int N = 7;
	
	double *Time = new double[N];
	double *Exposure = new double[N];

	//N13 free
	//
	double *RelError_IBD_N13_free = new double[N];
	double *RelError_Baseline_N13_free  = new double[N];
	double *RelError_Ideal_N13_free  = new double[N];
	double *RelError_BorexinoLike_N13_free  = new double[N];

	double *Bx_left_N13_free = new double[N];
        double *Bx_right_N13_free = new double[N];
        double *Ideal_left_N13_free = new double[N];
        double *Ideal_right_N13_free = new double[N];
        double *Baseline_left_N13_free = new double[N];
        double *Baseline_right_N13_free = new double[N];
        double *IBD_left_N13_free = new double[N];
        double *IBD_right_N13_free = new double[N];

	//O15 free
	//
	double *RelError_IBD_O15_free = new double[N];
        double *RelError_Baseline_O15_free  = new double[N];
        double *RelError_Ideal_O15_free  = new double[N];
        double *RelError_BorexinoLike_O15_free  = new double[N];

        double *Bx_left_O15_free = new double[N];
        double *Bx_right_O15_free = new double[N];
        double *Ideal_left_O15_free = new double[N];
        double *Ideal_right_O15_free = new double[N];
        double *Baseline_left_O15_free = new double[N];
        double *Baseline_right_O15_free = new double[N];
        double *IBD_left_O15_free = new double[N];
        double *IBD_right_O15_free = new double[N];

	//N13 fixed
	//
	double *RelError_IBD_N13_fixed = new double[N];
        double *RelError_Baseline_N13_fixed  = new double[N];
        double *RelError_Ideal_N13_fixed  = new double[N];
        double *RelError_BorexinoLike_N13_fixed  = new double[N];

        double *Bx_left_N13_fixed = new double[N];
        double *Bx_right_N13_fixed = new double[N];
        double *Ideal_left_N13_fixed = new double[N];
        double *Ideal_right_N13_fixed = new double[N];
        double *Baseline_left_N13_fixed = new double[N];
        double *Baseline_right_N13_fixed = new double[N];
        double *IBD_left_N13_fixed = new double[N];
        double *IBD_right_N13_fixed = new double[N];

	//O15 fixed
	//
	double *RelError_IBD_O15_fixed = new double[N];
        double *RelError_Baseline_O15_fixed  = new double[N];
        double *RelError_Ideal_O15_fixed  = new double[N];
        double *RelError_BorexinoLike_O15_fixed  = new double[N];

        double *Bx_left_O15_fixed = new double[N];
        double *Bx_right_O15_fixed = new double[N];
        double *Ideal_left_O15_fixed = new double[N];
        double *Ideal_right_O15_fixed = new double[N];
        double *Baseline_left_O15_fixed = new double[N];
        double *Baseline_right_O15_fixed = new double[N];
        double *IBD_left_O15_fixed = new double[N];
        double *IBD_right_O15_fixed = new double[N];

	double radius = 14.;
	double DC = 1.0;
	double mass = 4./3.*3.14*pow(radius,3)*860*DC/pow(10,5);
	
	cout << mass << endl;


	for(int i=0; i<N; i++){

		Read >> Time[i];

		Read >> RelError_BorexinoLike_N13_free[i];
		Read >> Bx_left_N13_free[i];
		Read >> Bx_right_N13_free[i];
		Read >> RelError_Ideal_N13_free[i];
                Read >> Ideal_left_N13_free[i];
                Read >> Ideal_right_N13_free[i];
		Read >> RelError_Baseline_N13_free[i];
                Read >> Baseline_left_N13_free[i];
                Read >> Baseline_right_N13_free[i];
		Read >> RelError_IBD_N13_free[i];
                Read >> IBD_left_N13_free[i];
                Read >> IBD_right_N13_free[i];

		Read >> RelError_BorexinoLike_O15_free[i];
                Read >> Bx_left_O15_free[i];
                Read >> Bx_right_O15_free[i];
                Read >> RelError_Ideal_O15_free[i];
                Read >> Ideal_left_O15_free[i];
                Read >> Ideal_right_O15_free[i];
                Read >> RelError_Baseline_O15_free[i];
                Read >> Baseline_left_O15_free[i];
                Read >> Baseline_right_O15_free[i];
                Read >> RelError_IBD_O15_free[i];
                Read >> IBD_left_O15_free[i];
                Read >> IBD_right_O15_free[i];

		Read >> RelError_BorexinoLike_N13_fixed[i];
                Read >> Bx_left_N13_fixed[i];
                Read >> Bx_right_N13_fixed[i];
                Read >> RelError_Ideal_N13_fixed[i];
                Read >> Ideal_left_N13_fixed[i];
                Read >> Ideal_right_N13_fixed[i];
                Read >> RelError_Baseline_N13_fixed[i];
                Read >> Baseline_left_N13_fixed[i];
                Read >> Baseline_right_N13_fixed[i];
                Read >> RelError_IBD_N13_fixed[i];
                Read >> IBD_left_N13_fixed[i];
                Read >> IBD_right_N13_fixed[i];

		Read >> RelError_BorexinoLike_O15_fixed[i];
                Read >> Bx_left_O15_fixed[i];
                Read >> Bx_right_O15_fixed[i];
                Read >> RelError_Ideal_O15_fixed[i];
                Read >> Ideal_left_O15_fixed[i];
                Read >> Ideal_right_O15_fixed[i];
                Read >> RelError_Baseline_O15_fixed[i];
                Read >> Baseline_left_O15_fixed[i];
                Read >> Baseline_right_O15_fixed[i];
                Read >> RelError_IBD_O15_fixed[i];
                Read >> IBD_left_O15_fixed[i];
                Read >> IBD_right_O15_fixed[i];				
	}

	double *RelError_IBD_N13_free_appo = new double[N];
	double *Time_IBD_N13_free_appo = new double[N];
        double *RelError_Baseline_N13_free_appo  = new double[N-4];
	double *Time_Baseline_N13_free_appo  = new double[N-4];
        double *RelError_Ideal_N13_free_appo  = new double[N-3];
	double *Time_Ideal_N13_free_appo  = new double[N-3];
        double *RelError_BorexinoLike_N13_free_appo  = new double[N-2];
	double *Time_BorexinoLike_N13_free_appo  = new double[N-2];

        double *Bx_left_N13_free_appo = new double[N-2];
        double *Bx_right_N13_free_appo = new double[N-2];
        double *Ideal_left_N13_free_appo = new double[N-3];
        double *Ideal_right_N13_free_appo = new double[N-3];
        double *Baseline_left_N13_free_appo = new double[N-4];
        double *Baseline_right_N13_free_appo = new double[N-4];
        double *IBD_left_N13_free_appo = new double[N];
        double *IBD_right_N13_free_appo = new double[N];

	double *RelError_IBD_O15_free_appo = new double[N];
        double *RelError_Baseline_O15_free_appo  = new double[N-4];
        double *RelError_Ideal_O15_free_appo  = new double[N-3];
        double *RelError_BorexinoLike_O15_free_appo  = new double[N-2];
	double *Time_IBD_O15_free_appo = new double[N];
        double *Time_Baseline_O15_free_appo  = new double[N-4];
        double *Time_Ideal_O15_free_appo  = new double[N-3];
        double *Time_BorexinoLike_O15_free_appo  = new double[N-2];

        double *Bx_left_O15_free_appo = new double[N-2];
        double *Bx_right_O15_free_appo = new double[N-2];
        double *Ideal_left_O15_free_appo = new double[N-3];
        double *Ideal_right_O15_free_appo = new double[N-3];
        double *Baseline_left_O15_free_appo = new double[N-4];
        double *Baseline_right_O15_free_appo = new double[N-4];
        double *IBD_left_O15_free_appo = new double[N];
        double *IBD_right_O15_free_appo = new double[N];

	double *RelError_IBD_N13_fixed_appo = new double[N];
        double *RelError_Baseline_N13_fixed_appo  = new double[N-4];
        double *RelError_Ideal_N13_fixed_appo  = new double[N-2];
        double *RelError_BorexinoLike_N13_fixed_appo  = new double[N-2];
	double *Time_IBD_N13_fixed_appo = new double[N];
        double *Time_Baseline_N13_fixed_appo  = new double[N-4];
        double *Time_Ideal_N13_fixed_appo  = new double[N-2];
        double *Time_BorexinoLike_N13_fixed_appo  = new double[N-2];

        double *Bx_left_N13_fixed_appo = new double[N-2];
        double *Bx_right_N13_fixed_appo = new double[N-2];
        double *Ideal_left_N13_fixed_appo = new double[N-2];
        double *Ideal_right_N13_fixed_appo = new double[N-2];
        double *Baseline_left_N13_fixed_appo = new double[N-4];
        double *Baseline_right_N13_fixed_appo = new double[N-4];
        double *IBD_left_N13_fixed_appo = new double[N];
        double *IBD_right_N13_fixed_appo = new double[N];

	double *RelError_IBD_O15_fixed_appo = new double[N-3];
        double *RelError_Baseline_O15_fixed_appo  = new double[N-1];
        double *RelError_Ideal_O15_fixed_appo  = new double[N];
        double *RelError_BorexinoLike_O15_fixed_appo  = new double[N];

	double *Time_IBD_O15_fixed_appo = new double[N-3];
        double *Time_Baseline_O15_fixed_appo  = new double[N-1];
        double *Time_Ideal_O15_fixed_appo  = new double[N];
        double *Time_BorexinoLike_O15_fixed_appo  = new double[N];

        double *Bx_left_O15_fixed_appo = new double[N];
        double *Bx_right_O15_fixed_appo = new double[N];
        double *Ideal_left_O15_fixed_appo = new double[N];
        double *Ideal_right_O15_fixed_appo = new double[N];
        double *Baseline_left_O15_fixed_appo = new double[N-1];
        double *Baseline_right_O15_fixed_appo = new double[N-1];
        double *IBD_left_O15_fixed_appo = new double[N-3];
        double *IBD_right_O15_fixed_appo = new double[N-3];

	double appo_N13_free = 0.;
        int k_IBD_N13_free = 0;
        int k_Baseline_N13_free = 0;
        int k_Ideal_N13_free = 0;
        int k_BorexinoLike_N13_free = 0;

        for(int i=0; i<N; i++){
                if(RelError_IBD_N13_free[i]==9999){
                        appo_N13_free = RelError_IBD_N13_free[i];
                }else{
                        RelError_IBD_N13_free_appo[k_IBD_N13_free] = RelError_IBD_N13_free[i];
                        IBD_left_N13_free_appo[k_IBD_N13_free] = IBD_left_N13_free[i];
                        IBD_right_N13_free_appo[k_IBD_N13_free] = IBD_right_N13_free[i];
                        Time_IBD_N13_free_appo[k_IBD_N13_free] = Time[i];
                        k_IBD_N13_free++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Baseline_N13_free[i]==9999){
                        appo_N13_free = RelError_Baseline_N13_free[i];
                }else{
                        RelError_Baseline_N13_free_appo[k_Baseline_N13_free] = RelError_Baseline_N13_free[i];
                        Baseline_left_N13_free_appo[k_Baseline_N13_free] = Baseline_left_N13_free[i];
                        Baseline_right_N13_free_appo[k_Baseline_N13_free] = Baseline_right_N13_free[i];
                        Time_Baseline_N13_free_appo[k_Baseline_N13_free] = Time[i];
                        k_Baseline_N13_free++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Ideal_N13_free[i]==9999){
                        appo_N13_free = RelError_Ideal_N13_free[i];
                }else{
                        RelError_Ideal_N13_free_appo[k_Ideal_N13_free] = RelError_Ideal_N13_free[i];
                        Ideal_left_N13_free_appo[k_Ideal_N13_free] = Ideal_left_N13_free[i];
                        Ideal_right_N13_free_appo[k_Ideal_N13_free] = Ideal_right_N13_free[i];
                        Time_Ideal_N13_free_appo[k_Ideal_N13_free] = Time[i];
                        k_Ideal_N13_free++;
                }
        }

         for(int i=0; i<N; i++){
                if(RelError_BorexinoLike_N13_free[i]==9999){
                        appo_N13_free = RelError_BorexinoLike_N13_free[i];
                }else{
                        RelError_BorexinoLike_N13_free_appo[k_BorexinoLike_N13_free] = RelError_BorexinoLike_N13_free[i];
                        Bx_left_N13_free_appo[k_BorexinoLike_N13_free] = Bx_left_N13_free[i];
                        Bx_right_N13_free_appo[k_BorexinoLike_N13_free] = Bx_right_N13_free[i];
                        Time_BorexinoLike_N13_free_appo[k_BorexinoLike_N13_free] = Time[i];
                        k_BorexinoLike_N13_free++;
                }
        }

	double appo_O15_free = 0.;
        int k_IBD_O15_free = 0;
        int k_Baseline_O15_free = 0;
        int k_Ideal_O15_free = 0;
        int k_BorexinoLike_O15_free = 0;

        for(int i=0; i<N; i++){
                if(RelError_IBD_O15_free[i]==9999){
                        appo_O15_free = RelError_IBD_O15_free[i];
                }else{
                        RelError_IBD_O15_free_appo[k_IBD_O15_free] = RelError_IBD_O15_free[i];
                        IBD_left_O15_free_appo[k_IBD_O15_free] = IBD_left_O15_free[i];
                        IBD_right_O15_free_appo[k_IBD_O15_free] = IBD_right_O15_free[i];
                        Time_IBD_O15_free_appo[k_IBD_O15_free] = Time[i];
                        k_IBD_O15_free++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Baseline_O15_free[i]==9999){
                        appo_O15_free = RelError_Baseline_O15_free[i];
                }else{
                        RelError_Baseline_O15_free_appo[k_Baseline_O15_free] = RelError_Baseline_O15_free[i];
                        Baseline_left_O15_free_appo[k_Baseline_O15_free] = Baseline_left_O15_free[i];
                        Baseline_right_O15_free_appo[k_Baseline_O15_free] = Baseline_right_O15_free[i];
                        Time_Baseline_O15_free_appo[k_Baseline_O15_free] = Time[i];
                        k_Baseline_O15_free++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Ideal_O15_free[i]==9999){
                        appo_O15_free = RelError_Ideal_O15_free[i];
                }else{
                        RelError_Ideal_O15_free_appo[k_Ideal_O15_free] = RelError_Ideal_O15_free[i];
                        Ideal_left_O15_free_appo[k_Ideal_O15_free] = Ideal_left_O15_free[i];
                        Ideal_right_O15_free_appo[k_Ideal_O15_free] = Ideal_right_O15_free[i];
                        Time_Ideal_O15_free_appo[k_Ideal_O15_free] = Time[i];
                        k_Ideal_O15_free++;
                }
        }

         for(int i=0; i<N; i++){
                if(RelError_BorexinoLike_O15_free[i]==9999){
                        appo_O15_free = RelError_BorexinoLike_O15_free[i];
                }else{
                        RelError_BorexinoLike_O15_free_appo[k_BorexinoLike_O15_free] = RelError_BorexinoLike_O15_free[i];
                        Bx_left_O15_free_appo[k_BorexinoLike_O15_free] = Bx_left_O15_free[i];
                        Bx_right_O15_free_appo[k_BorexinoLike_O15_free] = Bx_right_O15_free[i];
                        Time_BorexinoLike_O15_free_appo[k_BorexinoLike_O15_free] = Time[i];
                        k_BorexinoLike_O15_free++;
                }
        }


	double appo_N13_fixed = 0.;
        int k_IBD_N13_fixed = 0;
        int k_Baseline_N13_fixed = 0;
        int k_Ideal_N13_fixed = 0;
        int k_BorexinoLike_N13_fixed = 0;

        for(int i=0; i<N; i++){
                if(RelError_IBD_N13_fixed[i]==9999){
                        appo_N13_fixed = RelError_IBD_N13_fixed[i];
                }else{
                        RelError_IBD_N13_fixed_appo[k_IBD_N13_fixed] = RelError_IBD_N13_fixed[i];
                        IBD_left_N13_fixed_appo[k_IBD_N13_fixed] = IBD_left_N13_fixed[i];
                        IBD_right_N13_fixed_appo[k_IBD_N13_fixed] = IBD_right_N13_fixed[i];
                        Time_IBD_N13_fixed_appo[k_IBD_N13_fixed] = Time[i];
                        k_IBD_N13_fixed++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Baseline_N13_fixed[i]==9999){
                        appo_N13_fixed = RelError_Baseline_N13_fixed[i];
                }else{
                        RelError_Baseline_N13_fixed_appo[k_Baseline_N13_fixed] = RelError_Baseline_N13_fixed[i];
                        Baseline_left_N13_fixed_appo[k_Baseline_N13_fixed] = Baseline_left_N13_fixed[i];
                        Baseline_right_N13_fixed_appo[k_Baseline_N13_fixed] = Baseline_right_N13_fixed[i];
                        Time_Baseline_N13_fixed_appo[k_Baseline_N13_fixed] = Time[i];
                        k_Baseline_N13_fixed++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Ideal_N13_fixed[i]==9999){
                        appo_N13_fixed = RelError_Ideal_N13_fixed[i];
                }else{
                        RelError_Ideal_N13_fixed_appo[k_Ideal_N13_fixed] = RelError_Ideal_N13_fixed[i];
                        Ideal_left_N13_fixed_appo[k_Ideal_N13_fixed] = Ideal_left_N13_fixed[i];
                        Ideal_right_N13_fixed_appo[k_Ideal_N13_fixed] = Ideal_right_N13_fixed[i];
                        Time_Ideal_N13_fixed_appo[k_Ideal_N13_fixed] = Time[i];
                        k_Ideal_N13_fixed++;
                }
        }

         for(int i=0; i<N; i++){
                if(RelError_BorexinoLike_N13_fixed[i]==9999){
                        appo_N13_fixed = RelError_BorexinoLike_N13_fixed[i];
                }else{
                        RelError_BorexinoLike_N13_fixed_appo[k_BorexinoLike_N13_fixed] = RelError_BorexinoLike_N13_fixed[i];
                        Bx_left_N13_fixed_appo[k_BorexinoLike_N13_fixed] = Bx_left_N13_fixed[i];
                        Bx_right_N13_fixed_appo[k_BorexinoLike_N13_fixed] = Bx_right_N13_fixed[i];
                        Time_BorexinoLike_N13_fixed_appo[k_BorexinoLike_N13_fixed] = Time[i];
                        k_BorexinoLike_N13_fixed++;
                }
        }

	double appo_O15_fixed = 0.;
        int k_IBD_O15_fixed = 0;
        int k_Baseline_O15_fixed = 0;
        int k_Ideal_O15_fixed = 0;
        int k_BorexinoLike_O15_fixed = 0;

        for(int i=0; i<N; i++){
                if(RelError_IBD_O15_fixed[i]==9999){
                        appo_O15_fixed = RelError_IBD_O15_fixed[i];
                }else{
                        RelError_IBD_O15_fixed_appo[k_IBD_O15_fixed] = RelError_IBD_O15_fixed[i];
                        IBD_left_O15_fixed_appo[k_IBD_O15_fixed] = IBD_left_O15_fixed[i];
                        IBD_right_O15_fixed_appo[k_IBD_O15_fixed] = IBD_right_O15_fixed[i];
                        Time_IBD_O15_fixed_appo[k_IBD_O15_fixed] = Time[i];
                        k_IBD_O15_fixed++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Baseline_O15_fixed[i]==9999){
                        appo_O15_fixed = RelError_Baseline_O15_fixed[i];
                }else{
                        RelError_Baseline_O15_fixed_appo[k_Baseline_O15_fixed] = RelError_Baseline_O15_fixed[i];
                        Baseline_left_O15_fixed_appo[k_Baseline_O15_fixed] = Baseline_left_O15_fixed[i];
                        Baseline_right_O15_fixed_appo[k_Baseline_O15_fixed] = Baseline_right_O15_fixed[i];
                        Time_Baseline_O15_fixed_appo[k_Baseline_O15_fixed] = Time[i];
                        k_Baseline_O15_fixed++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Ideal_O15_fixed[i]==9999){
                        appo_O15_fixed = RelError_Ideal_O15_fixed[i];
                }else{
                        RelError_Ideal_O15_fixed_appo[k_Ideal_O15_fixed] = RelError_Ideal_O15_fixed[i];
                        Ideal_left_O15_fixed_appo[k_Ideal_O15_fixed] = Ideal_left_O15_fixed[i];
                        Ideal_right_O15_fixed_appo[k_Ideal_O15_fixed] = Ideal_right_O15_fixed[i];
                        Time_Ideal_O15_fixed_appo[k_Ideal_O15_fixed] = Time[i];
                        k_Ideal_O15_fixed++;
                }
        }

         for(int i=0; i<N; i++){
                if(RelError_BorexinoLike_O15_fixed[i]==9999){
                        appo_O15_fixed = RelError_BorexinoLike_O15_fixed[i];
                }else{
                        RelError_BorexinoLike_O15_fixed_appo[k_BorexinoLike_O15_fixed] = RelError_BorexinoLike_O15_fixed[i];
                        Bx_left_O15_fixed_appo[k_BorexinoLike_O15_fixed] = Bx_left_O15_fixed[i];
                        Bx_right_O15_fixed_appo[k_BorexinoLike_O15_fixed] = Bx_right_O15_fixed[i];
                        Time_BorexinoLike_O15_fixed_appo[k_BorexinoLike_O15_fixed] = Time[i];
                        k_BorexinoLike_O15_fixed++;
                }
        }

	double Ymin = 5.;
	double Ymax = 100.;
	double Xmin = 0.0;
	double Xmax = 11.0;
	
	TF1 *f_IBD_N13_free = new TF1("f_IBD_N13_free","[0]+[1]*pow(x,-0.5)",Xmin,Xmax);
	TF1 *f_Baseline_N13_free = new TF1("f_Baseline_N13_free","[0]+[1]*pow(x,-0.5)",6,Xmax);	
	TF1 *f_Ideal_N13_free = new TF1("f_Ideal_N13_free","[0]+[1]*pow(x,-0.5)",4,Xmax);	
	TF1 *f_BorexinoLike_N13_free = new TF1("f_BorexinoLike_N13_free","[0]+[1]*pow(x,-0.5)",2,Xmax);	
	
	f_IBD_N13_free->SetParameter(2,-0.5);
        f_Baseline_N13_free->SetParameter(2,-0.5);
        f_Ideal_N13_free->SetParameter(2,-0.5);
        f_BorexinoLike_N13_free->SetParameter(2,-0.5);

	TF1 *f_IBD_O15_free = new TF1("f_IBD_O15_free","[0]+[1]*pow(x,-0.5)",Xmin,Xmax);
        TF1 *f_Baseline_O15_free = new TF1("f_Baseline_O15_free","[0]+[1]*pow(x,-0.5)",6,Xmax);
        TF1 *f_Ideal_O15_free = new TF1("f_Ideal_O15_free","[0]+[1]*pow(x,-0.5)",4,Xmax);
        TF1 *f_BorexinoLike_O15_free = new TF1("f_BorexinoLike_O15_free","[0]+[1]*pow(x,-0.5)",2,Xmax);

        f_IBD_O15_free->SetParameter(2,-0.5);
        f_Baseline_O15_free->SetParameter(2,-0.5);
        f_Ideal_O15_free->SetParameter(2,-0.5);
        f_BorexinoLike_O15_free->SetParameter(2,-0.5);

	TF1 *f_IBD_N13_fixed = new TF1("f_IBD_N13_fixed","[0]+[1]*pow(x,-0.5)",Xmin,Xmax);
        TF1 *f_Baseline_N13_fixed = new TF1("f_Baseline_N13_fixed","[0]+[1]*pow(x,-0.5)",6,Xmax);
        TF1 *f_Ideal_N13_fixed = new TF1("f_Ideal_N13_fixed","[0]+[1]*pow(x,-0.5)",2,Xmax);
        TF1 *f_BorexinoLike_N13_fixed = new TF1("f_BorexinoLike_N13_fixed","[0]+[1]*pow(x,-0.5)",2,Xmax);

        f_IBD_N13_fixed->SetParameter(2,-0.5);
        f_Baseline_N13_fixed->SetParameter(2,-0.5);
        f_Ideal_N13_fixed->SetParameter(2,-0.5);
        f_BorexinoLike_N13_fixed->SetParameter(2,-0.5);
	
	TF1 *f_IBD_O15_fixed = new TF1("f_IBD_O15_fixed","[0]+[1]*pow(x,-0.5)",4,Xmax);
        TF1 *f_Baseline_O15_fixed = new TF1("f_Baseline_O15_fixed","[0]+[1]*pow(x,-0.5)",1,Xmax);
        TF1 *f_Ideal_O15_fixed = new TF1("f_Ideal_O15_fixed","[0]+[1]*pow(x,-0.5)",0.5,Xmax);
        TF1 *f_BorexinoLike_O15_fixed = new TF1("f_BorexinoLike_O15_fixed","[0]+[1]*pow(x,-0.5)",0.5,Xmax);

        f_IBD_O15_fixed->SetParameter(2,-0.5);
        f_Baseline_O15_fixed->SetParameter(2,-0.5);
        f_Ideal_O15_fixed->SetParameter(2,-0.5);
        f_BorexinoLike_O15_fixed->SetParameter(2,-0.5);

	
	//TFile *f = new TFile ("f.root", "RECREATE");
	//f->cd();
	double NNN = 600;
        double Width = NNN;
        double Height = Width*0.7;

	TCanvas *c = new TCanvas("c","c",Width,Height);
	gStyle->SetOptTitle(0);
	
	double A = 1.;
	double Border = 0.00;
	double T = 0.3*Height;
	double T1 = 0.1*Height;
	double T2 = T - T1;
        double HHH = (Height-T+T1)/Height;	
	
	TPad *pad_Left = new TPad("pad_Left","",0,0,0.5,HHH);
	TPad *pad_Right = new TPad("pad_Right","",0.5,0,1,HHH);
	TPad *U=new TPad("newpad","a transparent pad",0,0,1,1);	
		
	cout << "HHH   " << HHH << endl;
	cout << 1-T2/Height << endl;


	pad_Left->Draw();
	pad_Left->cd();

	pad_Left->SetLogy();
	pad_Left->SetFillStyle(4000);	
	pad_Left->SetBorderSize(3);
	pad_Left->SetTopMargin(0.12);
	pad_Left->SetLeftMargin(0.15);
	pad_Left->SetRightMargin(0.03);
	pad_Left->SetBottomMargin(0.14);
	
	//N13 free

	TGraphAsymmErrors *Graph_RelError_BorexinoLike_N13_free = new TGraphAsymmErrors(N-2,Time_BorexinoLike_N13_free_appo,RelError_BorexinoLike_N13_free_appo,0,0,Bx_left_N13_free_appo,Bx_right_N13_free_appo);
        Graph_RelError_BorexinoLike_N13_free->GetYaxis()->SetTitle("^{13}N-#nu rate relative uncertainty [%]");
        Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_N13_free->GetYaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_N13_free->GetYaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_N13_free->GetYaxis()->SetRangeUser(Ymin,Ymax);
        Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetTitleOffset(1.200);
        Graph_RelError_BorexinoLike_N13_free->GetYaxis()->SetTitleOffset(1.29);
        Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetRangeUser(Xmin,Xmax);
        Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetTitle("Time [y]");

        Graph_RelError_BorexinoLike_N13_free->Fit("f_BorexinoLike_N13_free","0");
        Graph_RelError_BorexinoLike_N13_free->Draw("AP");
        Graph_RelError_BorexinoLike_N13_free->SetMarkerStyle(20);
        Graph_RelError_BorexinoLike_N13_free->SetMarkerSize(1);
        Graph_RelError_BorexinoLike_N13_free->SetLineWidth(0);
        Graph_RelError_BorexinoLike_N13_free->SetMarkerColor(kSpring-5);
        Graph_RelError_BorexinoLike_N13_free->SetLineColor(kSpring-5);

        f_BorexinoLike_N13_free->SetLineColor(kSpring-5);
        f_BorexinoLike_N13_free->SetLineWidth(2);
        f_BorexinoLike_N13_free->SetLineStyle(1);
        f_BorexinoLike_N13_free->Draw("same");

	Graph_RelError_BorexinoLike_N13_free->GetXaxis()->SetLimits(Xmin,Xmax);
	c->Update();


        TGraphAsymmErrors *Graph_RelError_Ideal_N13_free = new TGraphAsymmErrors(N-3,Time_Ideal_N13_free_appo,RelError_Ideal_N13_free_appo,0,0,Bx_left_N13_free_appo,Bx_right_N13_free_appo);
        Graph_RelError_Ideal_N13_free->Fit("f_Ideal_N13_free","0");
        Graph_RelError_Ideal_N13_free->Draw("Psame");
        Graph_RelError_Ideal_N13_free->SetMarkerStyle(21);
        Graph_RelError_Ideal_N13_free->SetMarkerSize(1);
        Graph_RelError_Ideal_N13_free->SetLineWidth(0);
        Graph_RelError_Ideal_N13_free->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal_N13_free->SetLineColor(kAzure+8);

        f_Ideal_N13_free->SetLineColor(kAzure+8);
        f_Ideal_N13_free->SetLineWidth(2);
        f_Ideal_N13_free->SetLineStyle(1);
        f_Ideal_N13_free->Draw("same");

        TGraphAsymmErrors *Graph_RelError_Baseline_N13_free = new TGraphAsymmErrors(N-4,Time_Baseline_N13_free_appo,RelError_Baseline_N13_free_appo,0,0,Bx_left_N13_free_appo,Bx_right_N13_free_appo);
        Graph_RelError_Baseline_N13_free->Fit("f_Baseline_N13_free","0");
        Graph_RelError_Baseline_N13_free->Draw("Psame");
        Graph_RelError_Baseline_N13_free->SetMarkerStyle(22);
        Graph_RelError_Baseline_N13_free->SetMarkerSize(1);
        Graph_RelError_Baseline_N13_free->SetLineWidth(1);
        Graph_RelError_Baseline_N13_free->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline_N13_free->SetLineColor(kBlue+1);

        f_Baseline_N13_free->SetLineColor(kBlue+1);
        f_Baseline_N13_free->SetLineWidth(2);
        f_Baseline_N13_free->SetLineStyle(1);
        f_Baseline_N13_free->Draw("same");


	//N13 fixed

	TGraphAsymmErrors *Graph_RelError_BorexinoLike_N13_fixed = new TGraphAsymmErrors(N-2,Time_BorexinoLike_N13_fixed_appo,RelError_BorexinoLike_N13_fixed_appo,0,0,Bx_left_N13_fixed_appo,Bx_right_N13_fixed_appo);
        Graph_RelError_BorexinoLike_N13_fixed->Fit("f_BorexinoLike_N13_fixed","0");
        Graph_RelError_BorexinoLike_N13_fixed->Draw("Psame");
        Graph_RelError_BorexinoLike_N13_fixed->SetMarkerStyle(20);
        Graph_RelError_BorexinoLike_N13_fixed->SetMarkerSize(1);
        Graph_RelError_BorexinoLike_N13_fixed->SetLineWidth(1);
        Graph_RelError_BorexinoLike_N13_fixed->SetMarkerColor(kSpring-5);
        Graph_RelError_BorexinoLike_N13_fixed->SetLineColor(kSpring-5);

        f_BorexinoLike_N13_fixed->SetLineColor(kSpring-5);
        f_BorexinoLike_N13_fixed->SetLineWidth(2);
        f_BorexinoLike_N13_fixed->SetLineStyle(2);
        f_BorexinoLike_N13_fixed->Draw("same");


	TGraphAsymmErrors *Graph_RelError_Ideal_N13_fixed = new TGraphAsymmErrors(N-2,Time_Ideal_N13_fixed_appo,RelError_Ideal_N13_fixed_appo,0,0,Bx_left_N13_fixed_appo,Bx_right_N13_fixed_appo);
        Graph_RelError_Ideal_N13_fixed->Fit("f_Ideal_N13_fixed","0");
        Graph_RelError_Ideal_N13_fixed->Draw("Psame");
        Graph_RelError_Ideal_N13_fixed->SetMarkerStyle(21);
        Graph_RelError_Ideal_N13_fixed->SetMarkerSize(1);
        Graph_RelError_Ideal_N13_fixed->SetLineWidth(1);
        Graph_RelError_Ideal_N13_fixed->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal_N13_fixed->SetLineColor(kAzure+8);

        f_Ideal_N13_fixed->SetLineColor(kAzure+8);
        f_Ideal_N13_fixed->SetLineWidth(2);
        f_Ideal_N13_fixed->SetLineStyle(2);
        f_Ideal_N13_fixed->Draw("same");


        TGraphAsymmErrors *Graph_RelError_Baseline_N13_fixed = new TGraphAsymmErrors(N-4,Time_Baseline_N13_fixed_appo,RelError_Baseline_N13_fixed_appo,0,0,Bx_left_N13_fixed_appo,Bx_right_N13_fixed_appo);
        Graph_RelError_Baseline_N13_fixed->Fit("f_Baseline_N13_fixed","0");
        Graph_RelError_Baseline_N13_fixed->Draw("Psame");
        Graph_RelError_Baseline_N13_fixed->SetMarkerStyle(22);
        Graph_RelError_Baseline_N13_fixed->SetMarkerSize(1);
        Graph_RelError_Baseline_N13_fixed->SetLineWidth(1);
        Graph_RelError_Baseline_N13_fixed->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline_N13_fixed->SetLineColor(kBlue+1);

        f_Baseline_N13_fixed->SetLineColor(kBlue+1);
        f_Baseline_N13_fixed->SetLineWidth(2);
        f_Baseline_N13_fixed->SetLineStyle(2);
        f_Baseline_N13_fixed->Draw("same");


	TGaxis *A31 = new TGaxis(Xmin,Ymax,Xmax,Ymax,Xmin, Xmax*9.87,310,"-");
	A31->SetTitle("Exposure [kt y]");
	A31->SetTitleSize(0.055);
	A31->SetTitleOffset(0.9);
	A31->SetLabelSize(0.055);
	A31->SetTextFont(42);
	A31->SetLabelFont(42);
	A31->CenterTitle(kTRUE);
	A31->Draw("SAME");
	c->Update();	

	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);


	c->cd();

	pad_Right->Draw("same");
	pad_Right->cd();

	pad_Right->SetLogy();
	pad_Right->SetFillStyle(4000);	
	pad_Right->SetBorderSize(3);
	pad_Right->SetTopMargin(0.12);
	pad_Right->SetLeftMargin(0.15);
	pad_Right->SetRightMargin(0.03);
	pad_Right->SetBottomMargin(0.14);
	
	
	//O15 free
	
	TGraphAsymmErrors *Graph_RelError_BorexinoLike_O15_free = new TGraphAsymmErrors(N-2,Time_BorexinoLike_O15_free_appo,RelError_BorexinoLike_O15_free_appo,0,0,Bx_left_O15_free_appo,Bx_right_O15_free_appo);
        Graph_RelError_BorexinoLike_O15_free->GetYaxis()->SetTitle("^{15}O-#nu rate relative uncertainty [%]");
        Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_O15_free->GetYaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_O15_free->GetYaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_O15_free->GetYaxis()->SetRangeUser(Ymin,Ymax);
        Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetTitleOffset(1.200);
        Graph_RelError_BorexinoLike_O15_free->GetYaxis()->SetTitleOffset(1.29);
        Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetRangeUser(Xmin,Xmax);
        Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetTitle("Time [y]");

        Graph_RelError_BorexinoLike_O15_free->Fit("f_BorexinoLike_O15_free","0");
        Graph_RelError_BorexinoLike_O15_free->Draw("AP");
        Graph_RelError_BorexinoLike_O15_free->SetMarkerStyle(20);
        Graph_RelError_BorexinoLike_O15_free->SetMarkerSize(1);
        Graph_RelError_BorexinoLike_O15_free->SetLineWidth(1);
        Graph_RelError_BorexinoLike_O15_free->SetMarkerColor(kSpring-5);
        Graph_RelError_BorexinoLike_O15_free->SetLineColor(kSpring-5);

        f_BorexinoLike_O15_free->SetLineColor(kSpring-5);
        f_BorexinoLike_O15_free->SetLineWidth(2);
        f_BorexinoLike_O15_free->SetLineStyle(1);
        f_BorexinoLike_O15_free->Draw("same");

	Graph_RelError_BorexinoLike_O15_free->GetXaxis()->SetLimits(Xmin,Xmax);
        c->Update();

        TGraphAsymmErrors *Graph_RelError_Ideal_O15_free = new TGraphAsymmErrors(N-3,Time_Ideal_O15_free_appo,RelError_Ideal_O15_free_appo,0,0,Bx_left_O15_free_appo,Bx_right_O15_free_appo);
        Graph_RelError_Ideal_O15_free->Fit("f_Ideal_O15_free","0");
        Graph_RelError_Ideal_O15_free->Draw("Psame");
        Graph_RelError_Ideal_O15_free->SetMarkerStyle(21);
        Graph_RelError_Ideal_O15_free->SetMarkerSize(1);
        Graph_RelError_Ideal_O15_free->SetLineWidth(1);
        Graph_RelError_Ideal_O15_free->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal_O15_free->SetLineColor(kAzure+8);

        f_Ideal_O15_free->SetLineColor(kAzure+8);
        f_Ideal_O15_free->SetLineWidth(2);
        f_Ideal_O15_free->SetLineStyle(1);
        f_Ideal_O15_free->Draw("same");


        TGraphAsymmErrors *Graph_RelError_Baseline_O15_free = new TGraphAsymmErrors(N-4,Time_Baseline_O15_free_appo,RelError_Baseline_O15_free_appo,0,0,Bx_left_O15_free_appo,Bx_right_O15_free_appo);
        Graph_RelError_Baseline_O15_free->Fit("f_Baseline_O15_free","0");
        Graph_RelError_Baseline_O15_free->Draw("Psame");
        Graph_RelError_Baseline_O15_free->SetMarkerStyle(22);
        Graph_RelError_Baseline_O15_free->SetMarkerSize(1);
        Graph_RelError_Baseline_O15_free->SetLineWidth(1);
        Graph_RelError_Baseline_O15_free->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline_O15_free->SetLineColor(kBlue+1);

        f_Baseline_O15_free->SetLineColor(kBlue+1);
        f_Baseline_O15_free->SetLineWidth(2);
        f_Baseline_O15_free->SetLineStyle(1);
        f_Baseline_O15_free->Draw("same");
	
	//O15 fixed

	TGraphAsymmErrors *Graph_RelError_BorexinoLike_O15_fixed = new TGraphAsymmErrors(N,Time_BorexinoLike_O15_fixed_appo,RelError_BorexinoLike_O15_fixed_appo,0,0,Bx_left_O15_fixed_appo,Bx_right_O15_fixed_appo);
        Graph_RelError_BorexinoLike_O15_fixed->Fit("f_BorexinoLike_O15_fixed","0");
        Graph_RelError_BorexinoLike_O15_fixed->Draw("Psame");
        Graph_RelError_BorexinoLike_O15_fixed->SetMarkerStyle(20);
        Graph_RelError_BorexinoLike_O15_fixed->SetMarkerSize(1);
        Graph_RelError_BorexinoLike_O15_fixed->SetLineWidth(1);
        Graph_RelError_BorexinoLike_O15_fixed->SetMarkerColor(kSpring-5);
        Graph_RelError_BorexinoLike_O15_fixed->SetLineColor(kSpring-5);

        f_BorexinoLike_O15_fixed->SetLineColor(kSpring-5);
        f_BorexinoLike_O15_fixed->SetLineWidth(2);
        f_BorexinoLike_O15_fixed->SetLineStyle(2);
        f_BorexinoLike_O15_fixed->Draw("same");


        TGraphAsymmErrors *Graph_RelError_Ideal_O15_fixed = new TGraphAsymmErrors(N,Time_Ideal_O15_fixed_appo,RelError_Ideal_O15_fixed_appo,0,0,Bx_left_O15_fixed_appo,Bx_right_O15_fixed_appo);
        Graph_RelError_Ideal_O15_fixed->Fit("f_Ideal_O15_fixed","0");
        Graph_RelError_Ideal_O15_fixed->Draw("Psame");
        Graph_RelError_Ideal_O15_fixed->SetMarkerStyle(21);
        Graph_RelError_Ideal_O15_fixed->SetMarkerSize(1);
        Graph_RelError_Ideal_O15_fixed->SetLineWidth(1);
        Graph_RelError_Ideal_O15_fixed->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal_O15_fixed->SetLineColor(kAzure+8);

        f_Ideal_O15_fixed->SetLineColor(kAzure+8);
        f_Ideal_O15_fixed->SetLineWidth(2);
        f_Ideal_O15_fixed->SetLineStyle(2);
        f_Ideal_O15_fixed->Draw("same");


        TGraphAsymmErrors *Graph_RelError_Baseline_O15_fixed = new TGraphAsymmErrors(N-1,Time_Baseline_O15_fixed_appo,RelError_Baseline_O15_fixed_appo,0,0,Bx_left_O15_fixed_appo,Bx_right_O15_fixed_appo);
        Graph_RelError_Baseline_O15_fixed->Fit("f_Baseline_O15_fixed","0");
        Graph_RelError_Baseline_O15_fixed->Draw("Psame");
        Graph_RelError_Baseline_O15_fixed->SetMarkerStyle(22);
        Graph_RelError_Baseline_O15_fixed->SetMarkerSize(1);
        Graph_RelError_Baseline_O15_fixed->SetLineWidth(1);
        Graph_RelError_Baseline_O15_fixed->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline_O15_fixed->SetLineColor(kBlue+1);

        f_Baseline_O15_fixed->SetLineColor(kBlue+1);
        f_Baseline_O15_fixed->SetLineWidth(2);
        f_Baseline_O15_fixed->SetLineStyle(2);
        f_Baseline_O15_fixed->Draw("same");

	TGraphAsymmErrors *Graph_RelError_IBD_O15_fixed = new TGraphAsymmErrors(N-3,Time_IBD_O15_fixed_appo,RelError_IBD_O15_fixed_appo,0,0,Bx_left_O15_fixed_appo,Bx_right_O15_fixed_appo);
        Graph_RelError_IBD_O15_fixed->Fit("f_IBD_O15_fixed","0");
        Graph_RelError_IBD_O15_fixed->Draw("Psame");
        Graph_RelError_IBD_O15_fixed->SetMarkerStyle(23);
        Graph_RelError_IBD_O15_fixed->SetMarkerSize(1);
        Graph_RelError_IBD_O15_fixed->SetLineWidth(1);
        Graph_RelError_IBD_O15_fixed->SetMarkerColor(kViolet-7);
        Graph_RelError_IBD_O15_fixed->SetLineColor(kViolet-7);

        f_IBD_O15_fixed->SetLineColor(kViolet-7);
        f_IBD_O15_fixed->SetLineWidth(2);
        f_IBD_O15_fixed->SetLineStyle(2);
        f_IBD_O15_fixed->Draw("same");

	TF1 *f_allfree = new TF1("f_allfree","[0]+[1]*pow(x,[2])",2,2);
        f_allfree->SetLineColor(1);
        f_allfree->SetLineWidth(3);
        f_allfree->SetLineStyle(1);
        f_allfree->Draw("same");

        TF1 *f_pepc = new TF1("f_pepc","[0]+[1]*pow(x,[2])",2,2);
        f_pepc->SetLineColor(1);
        f_pepc->SetLineWidth(3);
        f_pepc->SetLineStyle(2);
        f_pepc->Draw("same");

	TGaxis *A32 = new TGaxis(Xmin,Ymax,Xmax,Ymax,Xmin, Xmax*9.87,310,"-");
        A32->SetTitle("Exposure [kt y]");
        A32->SetTitleSize(0.055);
        A32->SetTitleOffset(0.9);
        A32->SetLabelSize(0.055);
        A32->SetTextFont(42);
        A32->SetLabelFont(42);
        A32->CenterTitle(kTRUE);
        A32->Draw("SAME");
        c->Update();
	
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);

	c->Update();	
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);
	gStyle->SetLegendTextSize(0.045);

	c->cd();

	double LegendStep = 1.00/4. ;

	TLegend *legend_01 = new TLegend(Border,HHH,LegendStep,HHH+T1/Height);
	legend_01->AddEntry("f_BorexinoLike_O15_fixed","BX-like","l");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(LegendStep,HHH,2.*LegendStep,HHH+T1/Height);
	legend_02->AddEntry("f_Ideal_O15_fixed","Ideal","l");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(2.*LegendStep,HHH,3.*LegendStep,HHH+T1/Height);
	legend_03->AddEntry("f_Baseline_O15_fixed","Baseline","l");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(3.*LegendStep,HHH,4.*LegendStep,HHH+T1/Height);
	legend_04->AddEntry("f_IBD_O15_fixed","IBD","l");
	legend_04->Draw("same");


	U->SetFillStyle(4000);
	U->Draw("same");
	U->cd();
	
	TPaveLabel *titleU = new TPaveLabel(0,0.9,1,0.95,"Radiopurity scenario");
	titleU->SetFillColor(4000);
	titleU->SetTextFont(42);
	titleU->Draw("same");
	
	c->cd();
	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig12.pdf","pdf");
	
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig12();
  return 0;
}
#endif

