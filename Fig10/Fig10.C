#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig10() {	


	//CNO free
	ifstream Read;
        Read.open("CNOfree.txt",ios::in);

        int N = 7;

        double *Time = new double[N];
        double *Exposure = new double[N];
        double *RelError_IBD = new double[N];
        double *RelError_Baseline  = new double[N];
        double *RelError_Ideal  = new double[N];
        double *RelError_BorexinoLike  = new double[N];

        double *Bx_left = new double[N];
        double *Bx_right = new double[N];
        double *Ideal_left = new double[N];
        double *Ideal_right = new double[N];
        double *Baseline_left = new double[N];
        double *Baseline_right = new double[N];
        double *IBD_left = new double[N];
        double *IBD_right = new double[N];



        double radius = 14.;
        double DC = 1.0;
        double mass = 4./3.*3.14*pow(radius,3)*860*DC/pow(10,5);

        cout << "mass: " << mass << endl;


        for(int i=0; i<N; i++){
                Read >> Time[i];

                Read >> RelError_BorexinoLike[i];
                Read >> Bx_left[i];
                Read >> Bx_right[i];

                Read >> RelError_Ideal[i];
                Read >> Ideal_left[i];
                Read >> Ideal_right[i];

                Read >> RelError_Baseline[i];
                Read >> Baseline_left[i];
                Read >> Baseline_right[i];

        }

	double *RelError_Baseline_appo = new double[N-4];
        double *Time_Baseline_appo = new double[N-4];
        double *Baseline_left_appo = new double[N-4];
        double *Baseline_right_appo = new double[N-4];

        double *RelError_Ideal_appo = new double[N-2];
        double *Time_Ideal_appo = new double[N-2];
        double *Ideal_left_appo = new double[N-2];
        double *Ideal_right_appo = new double[N-2];

        double *RelError_BorexinoLike_appo = new double[N-2];
        double *Time_BorexinoLike_appo = new double[N-2];
        double *Bx_left_appo = new double[N-2];
        double *Bx_right_appo = new double[N-2];

        double appo = 0.;
        int k_IBD = 0;
        int k_Baseline = 0;
        int k_Ideal = 0;
        int k_BorexinoLike = 0;

	for(int i=0; i<N; i++){
                if(RelError_Baseline[i]==9999){
                        appo = RelError_Baseline[i];
                }else{
                        RelError_Baseline_appo[k_Baseline] = RelError_Baseline[i];
                        Baseline_left_appo[k_Baseline] = Baseline_left[i];
                        Baseline_right_appo[k_Baseline] = Baseline_right[i];
                        Time_Baseline_appo[k_Baseline] = Time[i];
                        k_Baseline++;
                }
        }

        for(int i=0; i<N; i++){
                if(RelError_Ideal[i]==9999){
                        appo = RelError_Ideal[i];
                }else{
                        RelError_Ideal_appo[k_Ideal] = RelError_Ideal[i];
                        Ideal_left_appo[k_Ideal] = Ideal_left[i];
                        Ideal_right_appo[k_Ideal] = Ideal_right[i];
                        Time_Ideal_appo[k_Ideal] = Time[i];
                        k_Ideal++;
                }
        }

         for(int i=0; i<N; i++){
                if(RelError_BorexinoLike[i]==9999){
                        appo = RelError_BorexinoLike[i];
                }else{
                        RelError_BorexinoLike_appo[k_BorexinoLike] = RelError_BorexinoLike[i];
                        Bx_left_appo[k_BorexinoLike] = Bx_left[i];
                        Bx_right_appo[k_BorexinoLike] = Bx_right[i];
                        Time_BorexinoLike_appo[k_BorexinoLike] = Time[i];
                        k_BorexinoLike++;
                }
        }

	
	double Ymin = 5.;
        double Ymax = 100.;
        double Xmin = 0.0;
        double Xmax = 11.0;

        TF1 *f_IBD = new TF1("f_IBD","[0]+[1]*pow(x,[2])",Xmin,Xmax);
        TF1 *f_Baseline = new TF1("f_Baseline","[0]+[1]*pow(x,[2])",6,Xmax);
        TF1 *f_Ideal = new TF1("f_Ideal","[0]+[1]*pow(x,[2])",2,Xmax);
        TF1 *f_BX = new TF1("f_BX","[0]+[1]*pow(x,[2])",2,Xmax);

        f_IBD->SetParameter(2,-0.5);
        f_Baseline->SetParameter(2,-0.5);
        f_Ideal->SetParameter(2,-0.5);
        f_BX->SetParameter(2,-0.5);

        TF1 *f_BX_L = new TF1("f_BX_L","[0]",0,Xmax);
        TF1 *f_BX_R = new TF1("f_BX_R","[0]",0,Xmax);
        f_BX_L->SetParameter(0,11.9);
        f_BX_R->SetParameter(0,29.8);
        
        
        //CNO fixed
        
        ifstream Read_f;
	Read_f.open("CNOpepfixed.txt",ios::in);

	int N_f = 7;
	
	double *Time_f = new double[N_f];
	double *Exposure_f = new double[N_f];
	double *RelError_IBD_f = new double[N_f];
	double *RelError_Baseline_f  = new double[N_f];
	double *RelError_Ideal_f  = new double[N_f];
	double *RelError_BorexinoLike_f  = new double[N_f];
	
	double *Bx_left_f = new double[N_f];
        double *Bx_right_f = new double[N_f];
	double *Ideal_left_f = new double[N_f];
        double *Ideal_right_f = new double[N_f];
	double *Baseline_left_f = new double[N_f];
        double *Baseline_right_f = new double[N_f];
	double *IBD_left_f = new double[N_f];
        double *IBD_right_f = new double[N_f];



	double radius_f = 14.;
	double DC_f = 1.0;
	double mass_f = 4./3.*3.14*pow(radius_f,3)*860*DC_f/pow(10,5);
	
	cout << "mass: " << mass_f << endl;


	for(int i=0; i<N_f; i++){
		Read_f >> Time_f[i];

		Read_f >> RelError_BorexinoLike_f[i];
		Read_f >> Bx_left_f[i];
                Read_f >> Bx_right_f[i];

		Read_f >> RelError_Ideal_f[i]; 
		Read_f >> Ideal_left_f[i];
                Read_f >> Ideal_right_f[i];

		Read_f >> RelError_Baseline_f[i]; 
		Read_f >> Baseline_left_f[i];
                Read_f >> Baseline_right_f[i];

		Read_f >> RelError_IBD_f[i]; 
		Read_f >> IBD_left_f[i];
                Read_f >> IBD_right_f[i];
	}

	double *RelError_IBD_appo_f = new double[N_f-3];
	double *Time_IBD_appo_f = new double[N_f-3];
	double *IBD_left_appo_f = new double[N_f-3];
        double *IBD_right_appo_f = new double[N_f-3];

	double *RelError_Baseline_appo_f = new double[N_f-1];
        double *Time_Baseline_appo_f = new double[N_f-1];
	double *Baseline_left_appo_f = new double[N_f-1];
        double *Baseline_right_appo_f = new double[N_f-1];

	double *RelError_Ideal_appo_f = new double[N_f];
        double *Time_Ideal_appo_f = new double[N_f];
	double *Ideal_left_appo_f = new double[N_f];
        double *Ideal_right_appo_f = new double[N_f];

	double *RelError_BorexinoLike_appo_f = new double[N_f];
        double *Time_BorexinoLike_appo_f = new double[N_f];
	double *Bx_left_appo_f = new double[N_f];
        double *Bx_right_appo_f = new double[N_f];

	double appo_f = 0.;
	int k_IBD_f = 0;
	int k_Baseline_f = 0;
	int k_Ideal_f = 0;
	int k_BorexinoLike_f = 0;

	for(int i=0; i<N_f; i++){
                if(RelError_IBD_f[i]==9999){
                        appo_f = RelError_IBD_f[i];
                }else{
                        RelError_IBD_appo_f[k_IBD_f] = RelError_IBD_f[i];
			IBD_left_appo_f[k_IBD_f] = IBD_left_f[i];
                        IBD_right_appo_f[k_IBD_f] = IBD_right_f[i];
                        Time_IBD_appo_f[k_IBD_f] = Time_f[i];
                        k_IBD_f++;
                }
        }

	for(int i=0; i<N_f; i++){
		if(RelError_Baseline_f[i]==9999){
			appo_f = RelError_Baseline_f[i];
		}else{
			RelError_Baseline_appo_f[k_Baseline_f] = RelError_Baseline_f[i];
			Baseline_left_appo_f[k_Baseline_f] = Baseline_left_f[i];
                        Baseline_right_appo_f[k_Baseline_f] = Baseline_right_f[i];
			Time_Baseline_appo_f[k_Baseline_f] = Time_f[i];
			k_Baseline_f++;
		}
	}

	for(int i=0; i<N_f; i++){
                if(RelError_Ideal_f[i]==9999){
                        appo_f = RelError_Ideal_f[i];
                }else{
                        RelError_Ideal_appo_f[k_Ideal_f] = RelError_Ideal_f[i];
			Ideal_left_appo_f[k_Ideal_f] = Ideal_left_f[i];
                        Ideal_right_appo_f[k_Ideal_f] = Ideal_right_f[i];
                        Time_Ideal_appo_f[k_Ideal_f] = Time_f[i];
                        k_Ideal_f++;
                }
                cout << RelError_Ideal_appo_f[i] << endl;
        }

	
	 for(int i=0; i<N_f; i++){
                if(RelError_BorexinoLike_f[i]==9999){
                        appo_f = RelError_BorexinoLike_f[i];
                }else{
                        RelError_BorexinoLike_appo_f[k_BorexinoLike_f] = RelError_BorexinoLike_f[i];
			Bx_left_appo_f[k_BorexinoLike_f] = Bx_left_f[i];
			Bx_right_appo_f[k_BorexinoLike_f] = Bx_right_f[i];
                        Time_BorexinoLike_appo_f[k_BorexinoLike_f] = Time_f[i];
                        k_BorexinoLike_f++;
                }
        }

	double Ymin_f = 5.;
	double Ymax_f = 100.;
	double Xmin_f = 0.0;
	double Xmax_f = 11.0;
	
	TF1 *f_IBD_f = new TF1("f_IBD_f","[0]+[1]*pow(x,[2])",4,Xmax_f);
	TF1 *f_Baseline_f = new TF1("f_Baseline_f","[0]+[1]*pow(x,[2])",1,Xmax_f);	
	TF1 *f_Ideal_f = new TF1("f_Ideal_f","[0]+[1]*pow(x,[2])",0.5,Xmax_f);	
	TF1 *f_BX_f = new TF1("f_BX_f","[0]+[1]*pow(x,[2])",0.5,Xmax_f);	

	f_IBD_f->SetParameter(2,-0.5);
	f_Baseline_f->SetParameter(2,-0.5);
	f_Ideal_f->SetParameter(2,-0.5);
	f_BX_f->SetParameter(2,-0.5);

	TF1 *f_BX_L_f = new TF1("f_BX_L_f","[0]",0,Xmax_f);
	TF1 *f_BX_R_f = new TF1("f_BX_R_f","[0]",0,Xmax_f);
	f_BX_L_f->SetParameter(0,11.9);	
	f_BX_R_f->SetParameter(0,29.8);


	
	//TFile *f = new TFile ("f.root", "RECREATE");
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
	
	//CNO free

	//Borexino-like scenario

	TGraphAsymmErrors *Graph_RelError_BorexinoLike = new TGraphAsymmErrors(N-2,Time_BorexinoLike_appo,RelError_BorexinoLike_appo,0,0,Bx_left_appo,Bx_right_appo);
	Graph_RelError_BorexinoLike->GetYaxis()->SetTitle("CNO-#nu rate relative uncertainty [%]");
        Graph_RelError_BorexinoLike->GetXaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike->GetYaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike->GetYaxis()->SetRangeUser(Ymin,Ymax);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleOffset(1.200);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleOffset(1.29);
        Graph_RelError_BorexinoLike->GetXaxis()->SetRangeUser(Xmin,Xmax);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitle("Time [y]");

	cout << "AAAA " << endl;
	cout << Bx_left_appo[0] << endl;
	cout << Bx_left_appo[1] << endl;
	cout << Bx_left_appo[2] << endl;
	cout << Bx_left_appo[3] << endl;
	
	
	Graph_RelError_BorexinoLike->Fit("f_BX","0");
	Graph_RelError_BorexinoLike->Draw("AP");
	Graph_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_RelError_BorexinoLike->SetMarkerSize(1);
	Graph_RelError_BorexinoLike->SetLineWidth(2);
	Graph_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_RelError_BorexinoLike->SetLineColor(kSpring-5);

	Graph_RelError_BorexinoLike->SetTitle("Time [y]");

	f_BX->SetLineColor(kSpring-5);
	f_BX->SetLineWidth(2);
	f_BX->SetLineStyle(1);	
	f_BX->Draw("same");

	Graph_RelError_BorexinoLike->GetXaxis()->SetLimits(Xmin,Xmax);
	c->Update();
	//Ideal scenario

        TGraphAsymmErrors *Graph_RelError_Ideal = new TGraphAsymmErrors(N-2,Time_Ideal_appo,RelError_Ideal_appo,0,0,Ideal_left_appo,Ideal_right_appo);
        Graph_RelError_Ideal->Fit("f_Ideal","0");
        Graph_RelError_Ideal->Draw("Psame");
        Graph_RelError_Ideal->SetMarkerStyle(21);
        Graph_RelError_Ideal->SetMarkerSize(1);
	Graph_RelError_Ideal->SetLineWidth(2);
        Graph_RelError_Ideal->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal->SetLineColor(kAzure+8);

        f_Ideal->SetLineColor(kAzure+8);
        f_Ideal->SetLineWidth(2);
        f_Ideal->SetLineStyle(1);
        f_Ideal->Draw("same");

        c->Update();
        
	//Baseline scenario

        TGraphAsymmErrors *Graph_RelError_Baseline = new TGraphAsymmErrors(N-4,Time_Baseline_appo,RelError_Baseline_appo,0,0,Baseline_left_appo,Baseline_right_appo);
       
        Graph_RelError_Baseline->Fit("f_Baseline","0");
        Graph_RelError_Baseline->Draw("Psame");
        Graph_RelError_Baseline->SetMarkerStyle(22);
        Graph_RelError_Baseline->SetMarkerSize(1);
	Graph_RelError_Baseline->SetLineWidth(2);
        Graph_RelError_Baseline->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline->SetLineColor(kBlue+1);

        f_Baseline->SetLineColor(kBlue+1);
        f_Baseline->SetLineWidth(2);
        f_Baseline->SetLineStyle(1);
        f_Baseline->Draw("same");

	
	f_BX_L->SetLineWidth(3);
	f_BX_L->SetLineStyle(2);
	f_BX_L->SetLineColor(kBlack);
	f_BX_L->Draw("same");

	f_BX_R->SetLineWidth(3);
        f_BX_R->SetLineStyle(2);
        f_BX_R->SetLineColor(kGray+1);
        f_BX_R->Draw("same");

	TGaxis *A3 = new TGaxis(Xmin,Ymax,Xmax,Ymax,0, Xmax*9.87,310,"-");
	A3->SetTitle("Exposure [kt y]");
	A3->SetTitleSize(0.045);
	A3->SetTitleOffset(1.4);
	A3->SetLabelSize(0.045);
	A3->SetTextFont(42);
	A3->SetLabelFont(42);
	A3->CenterTitle(kTRUE);
	A3->Draw("SAME");
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
	
	//CNO fixed
	
	TGraphAsymmErrors *Graph_RelError_BorexinoLike_f = new TGraphAsymmErrors(N_f,Time_BorexinoLike_appo_f,RelError_BorexinoLike_appo_f,0,0,Bx_left_appo_f,Bx_right_appo_f);
	Graph_RelError_BorexinoLike_f->GetYaxis()->SetTitle("CNO-#nu rate relative uncertainty [%]");
        Graph_RelError_BorexinoLike_f->GetXaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_f->GetYaxis()->SetLabelSize(0.055);
        Graph_RelError_BorexinoLike_f->GetXaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_f->GetYaxis()->SetTitleSize(0.055);
        Graph_RelError_BorexinoLike_f->GetYaxis()->SetRangeUser(Ymin_f,Ymax_f);
        Graph_RelError_BorexinoLike_f->GetXaxis()->SetTitleOffset(1.200);
        Graph_RelError_BorexinoLike_f->GetYaxis()->SetTitleOffset(1.29);
        Graph_RelError_BorexinoLike_f->GetXaxis()->SetRangeUser(Xmin_f,Xmax_f);
        Graph_RelError_BorexinoLike_f->GetXaxis()->SetTitle("Time [y]");

	Graph_RelError_BorexinoLike_f->Fit("f_BX_f","0");
	Graph_RelError_BorexinoLike_f->Draw("AP");
	Graph_RelError_BorexinoLike_f->SetMarkerStyle(20);
	Graph_RelError_BorexinoLike_f->SetMarkerSize(1);
	Graph_RelError_BorexinoLike_f->SetLineWidth(2);
	Graph_RelError_BorexinoLike_f->SetMarkerColor(kSpring-5);
	Graph_RelError_BorexinoLike_f->SetLineColor(kSpring-5);

	Graph_RelError_BorexinoLike_f->SetTitle("Time [y]");

	f_BX_f->SetLineColor(kSpring-5);
	f_BX_f->SetLineWidth(2);
	f_BX_f->SetLineStyle(1);	
	f_BX_f->Draw("same");

	Graph_RelError_BorexinoLike_f->GetXaxis()->SetLimits(Xmin_f,Xmax_f);
	c->Update();
	
	//Ideal scenario

        TGraphAsymmErrors *Graph_RelError_Ideal_f = new TGraphAsymmErrors(N_f,Time_Ideal_appo_f,RelError_Ideal_appo_f,0,0,Ideal_left_appo_f,Ideal_right_appo_f);
        Graph_RelError_Ideal_f->Fit("f_Ideal_f","0");
        Graph_RelError_Ideal_f->Draw("Psame");
        Graph_RelError_Ideal_f->SetMarkerStyle(21);
        Graph_RelError_Ideal_f->SetMarkerSize(1);
	Graph_RelError_Ideal_f->SetLineWidth(2);
        Graph_RelError_Ideal_f->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal_f->SetLineColor(kAzure+8);

        f_Ideal_f->SetLineColor(kAzure+8);
        f_Ideal_f->SetLineWidth(2);
        f_Ideal_f->SetLineStyle(1);
        f_Ideal_f->Draw("same");

        c->Update();

	//Baseline scenario

        TGraphAsymmErrors *Graph_RelError_Baseline_f = new TGraphAsymmErrors(N_f-1,Time_Baseline_appo_f,RelError_Baseline_appo_f,0,0,Baseline_left_appo_f,Baseline_right_appo_f);
       
        Graph_RelError_Baseline_f->Fit("f_Baseline_f","0");
        Graph_RelError_Baseline_f->Draw("Psame");
        Graph_RelError_Baseline_f->SetMarkerStyle(22);
        Graph_RelError_Baseline_f->SetMarkerSize(1);
	Graph_RelError_Baseline_f->SetLineWidth(2);
        Graph_RelError_Baseline_f->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline_f->SetLineColor(kBlue+1);

        f_Baseline_f->SetLineColor(kBlue+1);
        f_Baseline_f->SetLineWidth(2);
        f_Baseline_f->SetLineStyle(1);
        f_Baseline_f->Draw("same");


	// IBD scenario

        TGraphAsymmErrors *Graph_RelError_IBD_f = new TGraphAsymmErrors(N_f-3,Time_IBD_appo_f,RelError_IBD_appo_f,0,0,IBD_left_appo_f,IBD_right_appo_f);
        Graph_RelError_IBD_f->Fit("f_IBD_f","0");
        Graph_RelError_IBD_f->Draw("Psame");
        Graph_RelError_IBD_f->SetMarkerStyle(23);
        Graph_RelError_IBD_f->SetMarkerSize(1);
	Graph_RelError_IBD_f->SetLineWidth(2);
        Graph_RelError_IBD_f->SetMarkerColor(kViolet-7);
        Graph_RelError_IBD_f->SetLineColor(kViolet-7);

        f_IBD_f->SetLineColor(kViolet-7);
        f_IBD_f->SetLineWidth(2);
        f_IBD_f->SetLineStyle(1);
        f_IBD_f->Draw("same");

	
	f_BX_L_f->SetLineWidth(3);
	f_BX_L_f->SetLineStyle(2);
	f_BX_L_f->SetLineColor(kBlack);
	f_BX_L_f->Draw("same");

	f_BX_R_f->SetLineWidth(3);
        f_BX_R_f->SetLineStyle(2);
        f_BX_R_f->SetLineColor(kGray+1);
        f_BX_R_f->Draw("same");

	TGaxis *A3_f = new TGaxis(Xmin_f,Ymax_f,Xmax_f,Ymax_f,0, Xmax_f*9.87,310,"-");
	A3_f->SetTitle("Exposure [kt y]");
	A3_f->SetTitleSize(0.045);
	A3_f->SetTitleOffset(1.4);
	A3_f->SetLabelSize(0.045);
	A3_f->SetTextFont(42);
	A3_f->SetLabelFont(42);
	A3_f->CenterTitle(kTRUE);
	A3_f->Draw("SAME");
	c->Update();	

	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);

	gPad->SetTicks(0,1);

	//legend
	
	c->Update();	
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);
	gStyle->SetLegendTextSize(0.04);

	c->cd();
	
	double LegendStep = 1.00/6. ;

	TLegend *legend_01 = new TLegend(Border,HHH,LegendStep,HHH+T1/Height);
	legend_01->AddEntry("f_BX_f","BX-like","l");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(LegendStep,HHH,2.*LegendStep,HHH+T1/Height);
	legend_02->AddEntry("f_Ideal_f","Ideal","l");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(2.*LegendStep,HHH,3.*LegendStep,HHH+T1/Height);
	legend_03->AddEntry("f_Baseline_f","Baseline","l");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(3.*LegendStep,HHH,4.*LegendStep,HHH+T1/Height);
	legend_04->AddEntry("f_IBD_f","IBD","l");
	legend_04->Draw("same");

	TLegend *legend_05 = new TLegend(4.*LegendStep,HHH,5.*LegendStep,HHH+T1/Height);
        legend_05->AddEntry("f_BX_L_f","#sigma_{L} (BX)","l");
        legend_05->Draw("same");

	TLegend *legend_06 = new TLegend(5.*LegendStep,HHH,1-Border,HHH+T1/Height);
	legend_06->AddEntry("f_BX_R_f","#sigma_{R} (BX)","l");	
	legend_06->Draw("same");


	U->SetFillStyle(4000);
	U->Draw("same");
	U->cd();
	
	TPaveLabel *titleU = new TPaveLabel(0,0.9,0.55,0.95,"Radiopurity scenario");
	titleU->SetFillColor(4000);
	titleU->SetTextFont(42);
	titleU->Draw("same");

	TPad *newpad=new TPad("newpad","a transparent pad",0,0,1,1);
	newpad->SetFillStyle(4000);
	newpad->Draw("same");
	newpad->cd();
	TPaveLabel *title = new TPaveLabel(0.18,0.63,0.18+0.24,0.68,"No pep-#nu constraint");
	TPaveLabel *title2 = new TPaveLabel(0.74,0.63,0.74+0.24,0.68,"With pep-#nu constraint");
	//title->SetFillColor(4000);
	title->SetTextFont(42);
	title2->SetTextFont(42);
	title->Draw("same");
	title2->Draw("same");

   
		
	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig10.pdf","pdf");
	
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig10();
  return 0;
}
#endif

