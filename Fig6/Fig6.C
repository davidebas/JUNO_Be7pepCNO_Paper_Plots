#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig6(){	

	ifstream Read;
	Read.open("7Be_Exp.txt",ios::in);

	int N_Kr = 6;
	int N_Po = 5;
	int N_Ra = 8;
	int N_Exp = 7;
	
	double *Time = new double[N_Exp];
	double *Exposure = new double[N_Exp];
	double *RelError_IBD = new double[N_Exp];
	double *RelError_Baseline  = new double[N_Exp];
	double *RelError_Ideal  = new double[N_Exp];
	double *RelError_BorexinoLike  = new double[N_Exp];
	
	double *Bx_left = new double[N_Exp];
        double *Bx_right = new double[N_Exp];
        double *Ideal_left = new double[N_Exp];
        double *Ideal_right = new double[N_Exp];
        double *Baseline_left = new double[N_Exp];
        double *Baseline_right = new double[N_Exp];
        double *IBD_left = new double[N_Exp];
        double *IBD_right = new double[N_Exp];


	double radius = 14.;
	double DC = 1.0;
	double mass = 4./3.*3.14*pow(radius,3)*860*DC/pow(10,5);
	
	cout << mass << endl;


	for(int i=0; i<N_Exp; i++){

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

		Read >> RelError_IBD[i]; 
		Read >> IBD_left[i];           
                Read >> IBD_right[i];

	}

	double Ymin = 0.1;
	double Ymax = 10;
	double Xmin = 0.0;
	double Xmax = 11.0;
	
	TF1 *f_IBD = new TF1("f_IBD","[0]+[1]*pow(x,-0.5)",0.5,Xmax);
	TF1 *f_Baseline = new TF1("f_Baseline","[0]+[1]*pow(x,-0.5)",0.5,Xmax);	
	TF1 *f_Ideal = new TF1("f_Ideal","[0]+[1]*pow(x,-0.5)",0.5,Xmax);	
	TF1 *f_BorexinoLike = new TF1("f_BorexinoLike","[0]+[1]*pow(x,-0.5)",0.5,Xmax);	

	TF1 *f_BX_Result = new TF1("f_BX_Result","[0]",0,1e7);
	f_BX_Result->SetParameter(0,2.7);
	f_BX_Result->SetLineStyle(3);
	f_BX_Result->SetLineColor(kBlack);
	
	//TFile *f = new TFile ("f.root", "RECREATE");
	//f->cd();
	//
	double NNN = 400;
	double Width = 2*NNN;
	double Height = Width*1.05;
	TCanvas *c = new TCanvas("c","c",Width,Height);
	gStyle->SetOptTitle(0);
	
	double A = 1.;
	double Border = 0.01;

	//TPad *pad_TopLeft = new TPad("pad_TopLeft","",0.03,0.03,0.5,0.48);
//	TPad *pad_TopLeft = new TPad("pad_TopLeft","",Border,NNN+Border,NNN-Border,2*NNN-Border);
	TPad *pad_TopLeft = new TPad("pad_TopLeft","",Border,NNN/Height+Border,NNN/Height-Border,2*NNN/Height-Border);
	cout << Border << " " << NNN/Height+Border << " " << (Width-Height)/NNN-Border << " " << 2*NNN/Height-Border << endl;

	pad_TopLeft->Draw();
	pad_TopLeft->cd();
	pad_TopLeft->SetFillStyle(4000);	

	pad_TopLeft->SetLogy();
	pad_TopLeft->SetBorderSize(3);
	pad_TopLeft->SetTopMargin(0.14);
	pad_TopLeft->SetLeftMargin(0.15);
	pad_TopLeft->SetRightMargin(0.03);
	pad_TopLeft->SetBottomMargin(0.14);
	
	//IBD

	TGraphAsymmErrors *Graph_RelError_IBD = new TGraphAsymmErrors(N_Exp,Time,RelError_IBD,0,0,IBD_left,IBD_right);
	Graph_RelError_IBD->GetYaxis()->SetTitle("^{7}Be-#nu rate relative uncertainty [%]");
	Graph_RelError_IBD->GetXaxis()->SetLabelSize(0.055);
	Graph_RelError_IBD->GetYaxis()->SetLabelSize(0.055);
	Graph_RelError_IBD->GetXaxis()->SetTitleSize(0.055);
	Graph_RelError_IBD->GetYaxis()->SetTitleSize(0.053);
	Graph_RelError_IBD->GetYaxis()->SetRangeUser(Ymin,Ymax);	
	Graph_RelError_IBD->GetXaxis()->SetTitleOffset(1.200);
	Graph_RelError_IBD->GetYaxis()->SetTitleOffset(1.28);
	Graph_RelError_IBD->GetXaxis()->SetRangeUser(0,Xmax);
	Graph_RelError_IBD->GetXaxis()->SetTitle("Time [y]");
	
	Graph_RelError_IBD->Fit("f_IBD","0");
	Graph_RelError_IBD->Draw("AP");
	Graph_RelError_IBD->SetMarkerStyle(23);
	Graph_RelError_IBD->SetMarkerSize(0.8);
	Graph_RelError_IBD->SetLineWidth(2);
	Graph_RelError_IBD->SetMarkerColor(kViolet-7);
	Graph_RelError_IBD->SetLineColor(kViolet-7);

	f_IBD->SetLineColor(kViolet-7);
	//f_IBD->SetLineWidth(3);
	f_IBD->Draw("same");

	//Baseline

	TGraphAsymmErrors *Graph_RelError_Baseline = new TGraphAsymmErrors(N_Exp,Time,RelError_Baseline,0,0,Baseline_left,Baseline_right);
	Graph_RelError_Baseline->Fit("f_Baseline","0");
	Graph_RelError_Baseline->Draw("Psame");
	Graph_RelError_Baseline->SetMarkerStyle(22);
	Graph_RelError_Baseline->SetMarkerSize(0.8);
	Graph_RelError_Baseline->SetLineWidth(2);
	Graph_RelError_Baseline->SetMarkerColor(kBlue+1);
	Graph_RelError_Baseline->SetLineColor(kBlue+1);

	f_Baseline->SetLineColor(kBlue+1);
	//f_Baseline->SetLineWidth(3);
	f_Baseline->Draw("same");

	//Ideal

	TGraphAsymmErrors *Graph_RelError_Ideal = new TGraphAsymmErrors(N_Exp,Time,RelError_Ideal,0,0,Ideal_left,Ideal_right);
	Graph_RelError_Ideal->Fit("f_Ideal","0");
	Graph_RelError_Ideal->Draw("Psame");
	Graph_RelError_Ideal->SetMarkerStyle(21);
	Graph_RelError_Ideal->SetMarkerSize(0.8);
	Graph_RelError_Ideal->SetLineWidth(2);
	Graph_RelError_Ideal->SetMarkerColor(kAzure+8);
	Graph_RelError_Ideal->SetLineColor(kAzure+8);

	f_Ideal->SetLineColor(kAzure+8);
	//f_Ideal->SetLineWidth(3);
	f_Ideal->Draw("same");
	c->Update();
	
	//Borexino-like

	TGraphAsymmErrors *Graph_RelError_BorexinoLike = new TGraphAsymmErrors(N_Exp,Time,RelError_BorexinoLike,0,0,Bx_left,Bx_right);
	Graph_RelError_BorexinoLike->Fit("f_BorexinoLike","0");
	Graph_RelError_BorexinoLike->Draw("Psame");
	Graph_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_RelError_BorexinoLike->SetMarkerSize(0.8);
	Graph_RelError_BorexinoLike->SetLineWidth(2);
	Graph_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_RelError_BorexinoLike->SetLineColor(kSpring-5);
	Graph_RelError_BorexinoLike->SetTitle("Time [y]");

	f_BorexinoLike->SetLineColor(kSpring-5);
	//f_BorexinoLike->SetLineWidth(3);	
	f_BorexinoLike->Draw("same");
	
	//f_BX_Result->SetLineWidth(4);
	f_BX_Result->SetRange(0.01,1e7);
	f_BX_Result->SetLineWidth(3);
	f_BX_Result->Draw("same");

	TGaxis *A3 = new TGaxis(Xmin,Ymax,Xmax,Ymax,Xmin, Xmax*9.87,310,"-");
	A3->SetTitle("Exposure [kton y]");
	A3->SetTitleSize(0.055);
	A3->SetTitleOffset(0.9);
	A3->SetLabelSize(0.055);
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

	TGraphErrors *Star_RelError_IBD = new TGraphErrors();
	Star_RelError_IBD->SetPoint(0,Time[4],RelError_IBD[4]);
	Star_RelError_IBD->SetMarkerStyle(47);
	Star_RelError_IBD->SetMarkerSize(2);
	Star_RelError_IBD->SetMarkerColor(kViolet-7);
	Star_RelError_IBD->Draw("Psame");
	TGraphErrors *Star_RelError_Baseline = new TGraphErrors();
	Star_RelError_Baseline->SetPoint(0,Time[4],RelError_Baseline[4]);
	Star_RelError_Baseline->SetMarkerStyle(47);
	Star_RelError_Baseline->SetMarkerSize(2);
	Star_RelError_Baseline->SetMarkerColor(kBlue+1);
	Star_RelError_Baseline->Draw("Psame");
	TGraphErrors *Star_RelError_Ideal = new TGraphErrors();
	Star_RelError_Ideal->SetPoint(0,Time[4],RelError_Ideal[4]);
	Star_RelError_Ideal->SetMarkerStyle(47);
	Star_RelError_Ideal->SetMarkerSize(2);
	Star_RelError_Ideal->SetMarkerColor(kAzure+8);
	Star_RelError_Ideal->Draw("Psame");
	TGraphErrors *Star_RelError_BorexinoLike = new TGraphErrors();
	Star_RelError_BorexinoLike->SetPoint(0,Time[4],RelError_BorexinoLike[4]);
	Star_RelError_BorexinoLike->SetMarkerStyle(47);
	Star_RelError_BorexinoLike->SetMarkerSize(2);
	Star_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Star_RelError_BorexinoLike->Draw("Psame");

	// Be7 vs 226Ra

	ifstream Leggi_BeRa;
	Leggi_BeRa.open("7Be_226Ra.txt",ios::in);

	double *Ra_Rate = new double[N_Ra];
	double *BeRa_RelError_IBD = new double[N_Ra];
	double *BeRa_RelError_Baseline = new double[N_Ra];
	double *BeRa_RelError_Ideal = new double[N_Ra];
	double *BeRa_RelError_BorexinoLike = new double[N_Ra];

	double *BeRa_Bx_left = new double[N_Ra];
        double *BeRa_Bx_right = new double[N_Ra];
        double *BeRa_Ideal_left = new double[N_Ra];
        double *BeRa_Ideal_right = new double[N_Ra];
        double *BeRa_Baseline_left = new double[N_Ra];
        double *BeRa_Baseline_right = new double[N_Ra];
        double *BeRa_IBD_left = new double[N_Ra];
        double *BeRa_IBD_right = new double[N_Ra];

	double *Ra_Rate_Baseline_appo = new double[N_Ra-3];
        double *BeRa_RelError_Baseline_appo  = new double[N_Ra-3];
        double *BeRa_Baseline_left_appo = new double[N_Ra-3];
        double *BeRa_Baseline_right_appo = new double[N_Ra-3];

        double *Ra_Rate_IBD_appo = new double[N_Ra-3];
        double *BeRa_RelError_IBD_appo  = new double[N_Ra-3];
        double *BeRa_IBD_left_appo = new double[N_Ra-3];
        double *BeRa_IBD_right_appo = new double[N_Ra-3];
	
	for(int i=0; i<N_Ra; i++){

		Leggi_BeRa >> Ra_Rate[i];

		Leggi_BeRa >> BeRa_RelError_BorexinoLike[i];
		Leggi_BeRa >> BeRa_Bx_left[i];
	       	Leggi_BeRa >> BeRa_Bx_right[i]; 	

		Leggi_BeRa >> BeRa_RelError_Ideal[i]; 
		Leggi_BeRa >> BeRa_Ideal_left[i];           
                Leggi_BeRa >> BeRa_Ideal_right[i]; 

		Leggi_BeRa >> BeRa_RelError_Baseline[i]; 
		Leggi_BeRa >> BeRa_Baseline_left[i];           
                Leggi_BeRa >> BeRa_Baseline_right[i];

		Leggi_BeRa >> BeRa_RelError_IBD[i]; 
		Leggi_BeRa >> BeRa_IBD_left[i];           
                Leggi_BeRa >> BeRa_IBD_right[i];	
	}

	double appo_Ra = 0.;
        int k_IBD_Ra = 0;
        int k_Baseline_Ra = 0;

        for(int i=0; i<N_Ra; i++){
                if(BeRa_RelError_IBD[i]==9999){
                        appo_Ra = BeRa_RelError_IBD[i];
                }else{
                        BeRa_RelError_IBD_appo[k_IBD_Ra] = BeRa_RelError_IBD[i];
                        BeRa_IBD_left_appo[k_IBD_Ra] = BeRa_IBD_left[i];
                        BeRa_IBD_right_appo[k_IBD_Ra] = BeRa_IBD_right[i];
                        Ra_Rate_IBD_appo[k_IBD_Ra] = Ra_Rate[i];
                        k_IBD_Ra++;
                }
        }
         for(int i=0; i<N_Ra; i++){
                if(BeRa_RelError_Baseline[i]==9999){
                        appo_Ra = BeRa_RelError_Baseline[i];
                }else{
                        BeRa_RelError_Baseline_appo[k_Baseline_Ra] = BeRa_RelError_Baseline[i];
                        BeRa_Baseline_left_appo[k_Baseline_Ra] = BeRa_Baseline_left[i];
                        BeRa_Baseline_right_appo[k_Baseline_Ra] = BeRa_Baseline_right[i];
                        Ra_Rate_Baseline_appo[k_Baseline_Ra] = Ra_Rate[i];
                        k_Baseline_Ra++;
                }
        }
	
	c->cd();
	TPad *pad_TopRight = new TPad("pad_TopRight","",NNN/Height+Border,NNN/Height+Border,2*NNN/Height-Border,2*NNN/Height-Border);

	pad_TopRight->Draw("same");
	pad_TopRight->cd();

	pad_TopRight->SetLogy();
	pad_TopRight->SetLogx();
	pad_TopRight->SetFillStyle(4000);	
	pad_TopRight->SetBorderSize(3);
	pad_TopRight->SetTopMargin(0.14);
	pad_TopRight->SetLeftMargin(0.15);
	pad_TopRight->SetRightMargin(0.04);
	pad_TopRight->SetBottomMargin(0.14);
	
	//IBD
	
	TGraphAsymmErrors *Graph_BeRa_RelError_IBD = new TGraphAsymmErrors(N_Ra-4,Ra_Rate_IBD_appo,BeRa_RelError_IBD_appo,0,0,BeRa_IBD_left_appo,BeRa_IBD_right_appo);
	Graph_BeRa_RelError_IBD->GetYaxis()->SetTitle("^{7}Be-#nu rate relative uncertainty [%]");
	Graph_BeRa_RelError_IBD->GetXaxis()->SetLabelSize(0.055);
	Graph_BeRa_RelError_IBD->GetYaxis()->SetLabelSize(0.055);
	Graph_BeRa_RelError_IBD->GetXaxis()->SetTitleSize(0.055);
	Graph_BeRa_RelError_IBD->GetYaxis()->SetTitleSize(0.053);
	Graph_BeRa_RelError_IBD->GetYaxis()->SetRangeUser(0.1,Ymax);	
	Graph_BeRa_RelError_IBD->GetXaxis()->SetTitleOffset(1.26);
	Graph_BeRa_RelError_IBD->GetYaxis()->SetTitleOffset(1.20);
	Graph_BeRa_RelError_IBD->GetXaxis()->SetRangeUser(0.1,175);
	Graph_BeRa_RelError_IBD->GetXaxis()->SetTitle("^{226}Ra rate [cpd/kt]");	
	Graph_BeRa_RelError_IBD->SetMarkerStyle(23);
	Graph_BeRa_RelError_IBD->SetMarkerSize(0.8);
	Graph_BeRa_RelError_IBD->SetMarkerColor(kViolet-7);
	Graph_BeRa_RelError_IBD->SetLineColor(kViolet-7);
	//Graph_BeRa_RelError_IBD->SetLineStyle(3);
	Graph_BeRa_RelError_IBD->Draw("ALP");

	Graph_BeRa_RelError_IBD->GetXaxis()->SetLimits(0.07,1500);
	c->Update();


	//Baseline

	TGraphAsymmErrors *Graph_BeRa_RelError_Baseline = new TGraphAsymmErrors(N_Ra-4,Ra_Rate_Baseline_appo,BeRa_RelError_Baseline_appo,0,0,BeRa_Baseline_left_appo,BeRa_Baseline_right_appo);
	Graph_BeRa_RelError_Baseline->SetMarkerStyle(22);
	Graph_BeRa_RelError_Baseline->SetMarkerSize(0.8);
	Graph_BeRa_RelError_Baseline->SetMarkerColor(kBlue+1);
	Graph_BeRa_RelError_Baseline->SetLineColor(kBlue+1);
	//Graph_BeRa_RelError_Baseline->SetLineStyle(3);
	Graph_BeRa_RelError_Baseline->Draw("LPsame");

	//Ideal

	TGraphAsymmErrors *Graph_BeRa_RelError_Ideal = new TGraphAsymmErrors(N_Ra,Ra_Rate,BeRa_RelError_Ideal,0,0,BeRa_Ideal_left,BeRa_Ideal_right);
	Graph_BeRa_RelError_Ideal->SetMarkerStyle(21);
	Graph_BeRa_RelError_Ideal->SetMarkerSize(0.8);
	Graph_BeRa_RelError_Ideal->SetMarkerColor(kAzure+8);
	Graph_BeRa_RelError_Ideal->SetLineColor(kAzure+8);	
	//Graph_BeRa_RelError_Ideal->SetLineStyle(3);
	Graph_BeRa_RelError_Ideal->Draw("LPsame");

	//Borexino-like

	TGraphAsymmErrors *Graph_BeRa_RelError_BorexinoLike = new TGraphAsymmErrors(N_Ra,Ra_Rate,BeRa_RelError_BorexinoLike,0,0,BeRa_Bx_left,BeRa_Bx_right);
	Graph_BeRa_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_BeRa_RelError_BorexinoLike->SetMarkerSize(0.8);
	Graph_BeRa_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_BeRa_RelError_BorexinoLike->SetLineColor(kSpring-5);	
	//Graph_BeRa_RelError_BorexinoLike->SetLineStyle(3);
	Graph_BeRa_RelError_BorexinoLike->Draw("LPsame");


	TGraph *Star_BeRa_RelError_IBD = new TGraph();
	Star_BeRa_RelError_IBD->SetPoint(1,Ra_Rate[0],BeRa_RelError_IBD[0]);
	Star_BeRa_RelError_IBD->SetMarkerStyle(47);
	Star_BeRa_RelError_IBD->SetMarkerSize(2);
	Star_BeRa_RelError_IBD->SetMarkerColor(kViolet-7);
	Star_BeRa_RelError_IBD->Draw("Psame");
	TGraph *Star_BeRa_RelError_Baseline = new TGraph();
	Star_BeRa_RelError_Baseline->SetPoint(1,Ra_Rate[0],BeRa_RelError_Baseline[0]);
	Star_BeRa_RelError_Baseline->SetMarkerStyle(47);
	Star_BeRa_RelError_Baseline->SetMarkerSize(2);
	Star_BeRa_RelError_Baseline->SetMarkerColor(kBlue+1);
	Star_BeRa_RelError_Baseline->Draw("Psame");
	TGraph *Star_BeRa_RelError_Ideal = new TGraph();
	Star_BeRa_RelError_Ideal->SetPoint(1,Ra_Rate[0],BeRa_RelError_Ideal[0]);
	Star_BeRa_RelError_Ideal->SetMarkerStyle(47);
	Star_BeRa_RelError_Ideal->SetMarkerSize(2);
	Star_BeRa_RelError_Ideal->SetMarkerColor(kAzure+8);
	Star_BeRa_RelError_Ideal->Draw("Psame");
	TGraph *Star_BeRa_RelError_BorexinoLike = new TGraph();
	Star_BeRa_RelError_BorexinoLike->SetPoint(1,Ra_Rate[0],BeRa_RelError_BorexinoLike[0]);
	Star_BeRa_RelError_BorexinoLike->SetMarkerStyle(47);
	Star_BeRa_RelError_BorexinoLike->SetMarkerSize(2);
	Star_BeRa_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Star_BeRa_RelError_BorexinoLike->Draw("Psame");

	f_BX_Result->SetRange(0.01,1e7);
	f_BX_Result->Draw("same");
	
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);

	c->Update();	
	
	c->cd();
	
	//7Be vs 210Po

	TPad *pad_BottomLeft = new TPad("pad_BottomLeft","",Border,Border,NNN/Height-Border,NNN/Height-Border);

	ifstream Leggi_BePo;
	Leggi_BePo.open("7Be_210Po.txt",ios::in);

	double *Po_Rate_IBD = new double[N_Po];
	double *Po_Rate_Baseline = new double[N_Po];
	double *Po_Rate_Ideal = new double[N_Po];
	double *Po_Rate_BorexinoLike = new double[N_Po];
	
	double *BePo_RelError_IBD = new double[N_Po];
	double *BePo_RelError_Baseline  = new double[N_Po];
	double *BePo_RelError_Ideal  = new double[N_Po];
	double *BePo_RelError_BorexinoLike  = new double[N_Po];

	double *BePo_Bx_left = new double[N_Po];
        double *BePo_Bx_right = new double[N_Po];
        double *BePo_Ideal_left = new double[N_Po];
        double *BePo_Ideal_right = new double[N_Po];
        double *BePo_Baseline_left = new double[N_Po];
        double *BePo_Baseline_right = new double[N_Po];
        double *BePo_IBD_left = new double[N_Po];
        double *BePo_IBD_right = new double[N_Po];
	
	for(int i=0; i<N_Po; i++){

		Leggi_BePo >> Po_Rate_BorexinoLike[i] ;
		Leggi_BePo >> BePo_RelError_BorexinoLike[i];
		Leggi_BePo >> BePo_Bx_left[i];
                Leggi_BePo >> BePo_Bx_right[i];

		Leggi_BePo >> Po_Rate_Ideal[i] ;
		Leggi_BePo >> BePo_RelError_Ideal[i]; 
		Leggi_BePo >> BePo_Ideal_left[i];
                Leggi_BePo >> BePo_Ideal_right[i];

		Leggi_BePo >> Po_Rate_Baseline[i] ;
		Leggi_BePo >> BePo_RelError_Baseline[i];
	        Leggi_BePo >> BePo_Baseline_left[i];
                Leggi_BePo >> BePo_Baseline_right[i];	
		 
		Leggi_BePo >> Po_Rate_IBD[i] ;		
		Leggi_BePo >> BePo_RelError_IBD[i]; 
		Leggi_BePo >> BePo_IBD_left[i];
                Leggi_BePo >> BePo_IBD_right[i];
			
	}
	
	pad_BottomLeft->Draw("same");
	pad_BottomLeft->cd();

	pad_BottomLeft->SetLogy();
	pad_BottomLeft->SetLogx();
	pad_BottomLeft->SetFillStyle(4000);	
	pad_BottomLeft->SetBorderSize(3);
	pad_BottomLeft->SetTopMargin(0.08);
	pad_BottomLeft->SetLeftMargin(0.15);
	pad_BottomLeft->SetRightMargin(0.04);
	pad_BottomLeft->SetBottomMargin(0.16);

	//Borexino-like
	
	TGraphAsymmErrors *Graph_BePo_RelError_BorexinoLike = new TGraphAsymmErrors(N_Po,Po_Rate_BorexinoLike,BePo_RelError_BorexinoLike,0,0,BePo_Bx_left,BePo_Bx_right);
	Graph_BePo_RelError_BorexinoLike->GetYaxis()->SetTitle("^{7}Be-#nu rate relative uncertainty [%]");
	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetLabelSize(0.055);
	Graph_BePo_RelError_BorexinoLike->GetYaxis()->SetLabelSize(0.055);
	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetTitleSize(0.055);
	Graph_BePo_RelError_BorexinoLike->GetYaxis()->SetTitleSize(0.053);
	Graph_BePo_RelError_BorexinoLike->GetYaxis()->SetRangeUser(0.1,Ymax);	
	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetTitleOffset(1.200);
	Graph_BePo_RelError_BorexinoLike->GetYaxis()->SetTitleOffset(1.28);
	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetRangeUser(100,1000000);
	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetTitle("^{210}Po rate [cpd/kt]");	
	Graph_BePo_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_BePo_RelError_BorexinoLike->SetMarkerSize(0.8);
	Graph_BePo_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_BePo_RelError_BorexinoLike->SetLineColor(kSpring-5);
	//Graph_BePo_RelError_BorexinoLike->SetLineStyle(3);
	Graph_BePo_RelError_BorexinoLike->Draw("ALP");

	Graph_BePo_RelError_BorexinoLike->GetXaxis()->SetLimits(70,1000000);
	c->Update();

	//Baseline

	TGraphAsymmErrors *Graph_BePo_RelError_Baseline = new TGraphAsymmErrors(N_Po,Po_Rate_Baseline,BePo_RelError_Baseline,0,0,BePo_Baseline_left,BePo_Baseline_right);
	Graph_BePo_RelError_Baseline->SetMarkerStyle(22);
	Graph_BePo_RelError_Baseline->SetMarkerSize(0.8);
	Graph_BePo_RelError_Baseline->SetMarkerColor(kBlue+1);
	Graph_BePo_RelError_Baseline->SetLineColor(kBlue+1);
	//Graph_BePo_RelError_Baseline->SetLineStyle(3);
	Graph_BePo_RelError_Baseline->Draw("LPsame");

	//Ideal

	TGraphAsymmErrors *Graph_BePo_RelError_Ideal = new TGraphAsymmErrors(N_Po,Po_Rate_Ideal,BePo_RelError_Ideal,0,0,BePo_Ideal_left,BePo_Ideal_right);
	Graph_BePo_RelError_Ideal->SetMarkerStyle(21);
	Graph_BePo_RelError_Ideal->SetMarkerSize(0.8);
	Graph_BePo_RelError_Ideal->SetMarkerColor(kAzure+8);
	Graph_BePo_RelError_Ideal->SetLineColor(kAzure+8);
	//Graph_BePo_RelError_Ideal->SetLineStyle(3);
	Graph_BePo_RelError_Ideal->Draw("LPsame");

	//IBD

	TGraphAsymmErrors *Graph_BePo_RelError_IBD = new TGraphAsymmErrors(N_Po,Po_Rate_IBD,BePo_RelError_IBD,0,0,BePo_IBD_left,BePo_IBD_right);
	Graph_BePo_RelError_IBD->SetMarkerStyle(23);
	Graph_BePo_RelError_IBD->SetMarkerSize(0.8);
	Graph_BePo_RelError_IBD->SetMarkerColor(kViolet-7);
	Graph_BePo_RelError_IBD->SetLineColor(kViolet-7);
	//Graph_BePo_RelError_IBD->SetLineStyle(3);
	Graph_BePo_RelError_IBD->Draw("LPsame");

	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);

	TGraph *Star_BePo_RelError_IBD = new TGraph();
	Star_BePo_RelError_IBD->SetPoint(0,Po_Rate_IBD[0],BePo_RelError_IBD[0]);
	Star_BePo_RelError_IBD->SetMarkerStyle(47);
	Star_BePo_RelError_IBD->SetMarkerSize(2);
	Star_BePo_RelError_IBD->SetMarkerColor(kViolet-7);
	Star_BePo_RelError_IBD->Draw("Psame");

	TGraph *Star_BePo_RelError_Baseline = new TGraph();
	Star_BePo_RelError_Baseline->SetPoint(0,Po_Rate_Baseline[0],BePo_RelError_Baseline[0]);
	Star_BePo_RelError_Baseline->SetMarkerStyle(47);
	Star_BePo_RelError_Baseline->SetMarkerSize(2);
	Star_BePo_RelError_Baseline->SetMarkerColor(kBlue+1);
	Star_BePo_RelError_Baseline->Draw("Psame");

	TGraph *Star_BePo_RelError_Ideal = new TGraph();
	Star_BePo_RelError_Ideal->SetPoint(0,Po_Rate_Ideal[0],BePo_RelError_Ideal[0]);
	Star_BePo_RelError_Ideal->SetMarkerStyle(47);
	Star_BePo_RelError_Ideal->SetMarkerSize(2);
	Star_BePo_RelError_Ideal->SetMarkerColor(kAzure+8);
	Star_BePo_RelError_Ideal->Draw("Psame");

	TGraph *Star_BePo_RelError_BorexinoLike = new TGraph();
	Star_BePo_RelError_BorexinoLike->SetPoint(0,Po_Rate_BorexinoLike[0],BePo_RelError_BorexinoLike[0]);
	Star_BePo_RelError_BorexinoLike->SetMarkerStyle(47);
	Star_BePo_RelError_BorexinoLike->SetMarkerSize(2);
	Star_BePo_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Star_BePo_RelError_BorexinoLike->Draw("Psame");

	TF1 *f_BX_Result_Po = new TF1("f_BX_Result","[0]",0.01,1e7);
	f_BX_Result_Po->SetParameter(0,2.7);
	f_BX_Result_Po->SetLineStyle(3);
	f_BX_Result_Po->SetLineWidth(3);
	f_BX_Result_Po->SetLineColor(kBlack);
	f_BX_Result_Po->SetRange(0.01,1e7);
	f_BX_Result_Po->Draw("same");

	c->Update();	
	
	c->cd();
	
	//7Be vs 85Kr

	TPad *pad_BottomRight = new TPad("pad_BottomRight","",NNN/Height+Border,Border,2*NNN/Height-Border,NNN/Height-Border);

	ifstream Leggi_BeKr;
	Leggi_BeKr.open("7Be_85Kr.txt",ios::in);

	double *Kr_Rate = new double[N_Kr];
	double *BeKr_RelError_IBD = new double[N_Kr];
	double *BeKr_RelError_Baseline  = new double[N_Kr];
	double *BeKr_RelError_Ideal  = new double[N_Kr];
	double *BeKr_RelError_BorexinoLike  = new double[N_Kr];
	
	double *BeKr_Bx_left = new double[N_Kr];
        double *BeKr_Bx_right = new double[N_Kr];
        double *BeKr_Ideal_left = new double[N_Kr];
        double *BeKr_Ideal_right = new double[N_Kr];
        double *BeKr_Baseline_left = new double[N_Kr];
        double *BeKr_Baseline_right = new double[N_Kr];
        double *BeKr_IBD_left = new double[N_Kr];
        double *BeKr_IBD_right = new double[N_Kr];

	double *Kr_Rate_Baseline_appo = new double[N_Kr-1];
	double *BeKr_RelError_Baseline_appo  = new double[N_Kr-1];
	double *BeKr_Baseline_left_appo = new double[N_Kr-1];
        double *BeKr_Baseline_right_appo = new double[N_Kr-1];

	double *Kr_Rate_IBD_appo = new double[N_Kr-2];
        double *BeKr_RelError_IBD_appo  = new double[N_Kr-2];
        double *BeKr_IBD_left_appo = new double[N_Kr-2];
        double *BeKr_IBD_right_appo = new double[N_Kr-2];

	
	for(int i=0; i<N_Kr; i++){

		Leggi_BeKr >> Kr_Rate[i] ;

		Leggi_BeKr >> BeKr_RelError_BorexinoLike[i];
                Leggi_BeKr >> BeKr_Bx_left[i];
                Leggi_BeKr >> BeKr_Bx_right[i];

                Leggi_BeKr >> BeKr_RelError_Ideal[i];
                Leggi_BeKr >> BeKr_Ideal_left[i];
                Leggi_BeKr >> BeKr_Ideal_right[i];

                Leggi_BeKr >> BeKr_RelError_Baseline[i];
                Leggi_BeKr >> BeKr_Baseline_left[i];
                Leggi_BeKr >> BeKr_Baseline_right[i];

                Leggi_BeKr >> BeKr_RelError_IBD[i];
                Leggi_BeKr >> BeKr_IBD_left[i];
                Leggi_BeKr >> BeKr_IBD_right[i];

		 		
	}

	double appo = 0.;
        int k_IBD = 0;
        int k_Baseline = 0;

        for(int i=0; i<N_Kr; i++){
                if(BeKr_RelError_IBD[i]==9999){
                        appo = BeKr_RelError_IBD[i];
                }else{
                        BeKr_RelError_IBD_appo[k_IBD] = BeKr_RelError_IBD[i];
                        BeKr_IBD_left_appo[k_IBD] = BeKr_IBD_left[i];
                        BeKr_IBD_right_appo[k_IBD] = BeKr_IBD_right[i];
                        Kr_Rate_IBD_appo[k_IBD] = Kr_Rate[i];
                        k_IBD++;
                }
        }
	 for(int i=0; i<N_Kr; i++){
                if(BeKr_RelError_Baseline[i]==9999){
                        appo = BeKr_RelError_Baseline[i];
                }else{
                        BeKr_RelError_Baseline_appo[k_Baseline] = BeKr_RelError_Baseline[i];
                        BeKr_Baseline_left_appo[k_Baseline] = BeKr_Baseline_left[i];
                        BeKr_Baseline_right_appo[k_Baseline] = BeKr_Baseline_right[i];
                        Kr_Rate_Baseline_appo[k_Baseline] = Kr_Rate[i];
			k_Baseline++;
                }
        }

	pad_BottomRight->Draw("same");
	pad_BottomRight->cd();
	pad_BottomRight->SetLogy();
	pad_BottomRight->SetLogx();
	pad_BottomRight->SetFillStyle(4000);	
	pad_BottomRight->SetBorderSize(3);
	pad_BottomRight->SetTopMargin(0.08);
	pad_BottomRight->SetLeftMargin(0.15);
	pad_BottomRight->SetRightMargin(0.04);
	pad_BottomRight->SetBottomMargin(0.16);

	//IBD

	TGraphAsymmErrors *Graph_BeKr_RelError_IBD = new TGraphAsymmErrors(N_Kr-2,Kr_Rate_IBD_appo,BeKr_RelError_IBD_appo,0,0,BeKr_IBD_left_appo,BeKr_IBD_right_appo);
	Graph_BeKr_RelError_IBD->GetYaxis()->SetTitle("^{7}Be-#nu rate relative uncertainty [%]");
	Graph_BeKr_RelError_IBD->GetXaxis()->SetLabelSize(0.055);
	Graph_BeKr_RelError_IBD->GetYaxis()->SetLabelSize(0.055);
	Graph_BeKr_RelError_IBD->GetXaxis()->SetTitleSize(0.055);
	Graph_BeKr_RelError_IBD->GetYaxis()->SetTitleSize(0.053);
	Graph_BeKr_RelError_IBD->GetYaxis()->SetRangeUser(0.1,10);	
	Graph_BeKr_RelError_IBD->GetXaxis()->SetTitleOffset(1.200);
	Graph_BeKr_RelError_IBD->GetYaxis()->SetTitleOffset(1.20);
	Graph_BeKr_RelError_IBD->GetXaxis()->SetRangeUser(100,10000000);
	Graph_BeKr_RelError_IBD->GetXaxis()->SetTitle("^{85}Kr rate [cpd/kt]");	
	Graph_BeKr_RelError_IBD->SetMarkerStyle(23);
	Graph_BeKr_RelError_IBD->SetMarkerSize(0.8);
	Graph_BeKr_RelError_IBD->SetMarkerColor(kViolet-7);
	//Graph_BeKr_RelError_IBD->SetLineStyle(3);
	Graph_BeKr_RelError_IBD->Draw("ALP");

	Graph_BeKr_RelError_IBD->GetXaxis()->SetLimits(60,10000000);


	//Baseline

	TGraphAsymmErrors *Graph_BeKr_RelError_Baseline = new TGraphAsymmErrors(N_Kr-1,Kr_Rate_Baseline_appo,BeKr_RelError_Baseline_appo,0,0,BeKr_Baseline_left_appo,BeKr_Baseline_right_appo);
	Graph_BeKr_RelError_Baseline->SetMarkerStyle(22);
	Graph_BeKr_RelError_Baseline->SetMarkerSize(0.8);
	Graph_BeKr_RelError_Baseline->SetMarkerColor(kBlue+1);
	Graph_BeKr_RelError_Baseline->SetLineColor(kBlue+1);
	//Graph_BeKr_RelError_Baseline->SetLineStyle(3);
	Graph_BeKr_RelError_Baseline->Draw("LPsame");

	//Ideal

	TGraphAsymmErrors *Graph_BeKr_RelError_Ideal = new TGraphAsymmErrors(N_Kr,Kr_Rate,BeKr_RelError_Ideal,0,0,BeKr_Ideal_left,BeKr_Ideal_right);
	Graph_BeKr_RelError_Ideal->SetMarkerStyle(21);
	Graph_BeKr_RelError_Ideal->SetMarkerSize(0.8);
	Graph_BeKr_RelError_Ideal->SetMarkerColor(kAzure+8);
	Graph_BeKr_RelError_Ideal->SetLineColor(kAzure+8);
	//Graph_BeKr_RelError_Ideal->SetLineStyle(3);
	Graph_BeKr_RelError_Ideal->Draw("LPsame");

	//Borexino-like

	TGraphAsymmErrors *Graph_BeKr_RelError_BorexinoLike = new TGraphAsymmErrors(N_Kr,Kr_Rate,BeKr_RelError_BorexinoLike,0,0,BeKr_Bx_left,BeKr_Bx_right);
	Graph_BeKr_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_BeKr_RelError_BorexinoLike->SetMarkerSize(0.8);
	Graph_BeKr_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_BeKr_RelError_BorexinoLike->SetLineColor(kSpring-5);
	//Graph_BeKr_RelError_BorexinoLike->SetLineStyle(3);
	Graph_BeKr_RelError_BorexinoLike->Draw("LPsame");

	TGraph *Star_BeKr_RelError_IBD = new TGraph();
	Star_BeKr_RelError_IBD->SetPoint(0,5000,BeKr_RelError_IBD_appo[0]);
	Star_BeKr_RelError_IBD->SetMarkerStyle(47);
	Star_BeKr_RelError_IBD->SetMarkerSize(2);
	Star_BeKr_RelError_IBD->SetMarkerColor(kViolet-7);
	Star_BeKr_RelError_IBD->Draw("Psame");

	TGraph *Star_BeKr_RelError_Baseline = new TGraph();
	Star_BeKr_RelError_Baseline->SetPoint(0,500,BeKr_RelError_Baseline_appo[0]);
	Star_BeKr_RelError_Baseline->SetMarkerStyle(47);
	Star_BeKr_RelError_Baseline->SetMarkerSize(2);
	Star_BeKr_RelError_Baseline->SetMarkerColor(kBlue+1);
	Star_BeKr_RelError_Baseline->Draw("Psame");

	TGraph *Star_BeKr_RelError_Ideal = new TGraph();
	Star_BeKr_RelError_Ideal->SetPoint(0,Kr_Rate[0],BeKr_RelError_Ideal[0]);
	Star_BeKr_RelError_Ideal->SetMarkerStyle(47);
	Star_BeKr_RelError_Ideal->SetMarkerSize(2);
	Star_BeKr_RelError_Ideal->SetMarkerColor(kAzure+8);
	Star_BeKr_RelError_Ideal->Draw("Psame");

	TGraph *Star_BeKr_RelError_BorexinoLike = new TGraph();
	Star_BeKr_RelError_BorexinoLike->SetPoint(0,Kr_Rate[0],BeKr_RelError_BorexinoLike[0]);
	Star_BeKr_RelError_BorexinoLike->SetMarkerStyle(47);
	Star_BeKr_RelError_BorexinoLike->SetMarkerSize(2);
	Star_BeKr_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Star_BeKr_RelError_BorexinoLike->Draw("Psame");

	TF1 *f_BX_Result_Kr = new TF1("f_BX_Result","[0]",0.01,1e7);
	f_BX_Result_Kr->SetParameter(0,2.7);
	f_BX_Result_Kr->SetLineStyle(3);
	f_BX_Result_Kr->SetLineWidth(3);
	f_BX_Result_Kr->SetLineColor(kBlack);
	f_BX_Result_Kr->SetRange(0.01,1e7);
	f_BX_Result_Kr->Draw("same");
	
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);
	c->Update();	
	
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);
	c->Update();	
	
	c->cd();
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);
	gStyle->SetLegendTextSize(0.025);

	
	TLegend *legend_01 = new TLegend(Border,0.94,0.20,0.96);
	legend_01->AddEntry("f_BorexinoLike","BX-like","l");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(0.20,0.94,0.35,0.96);
	legend_02->AddEntry("f_Ideal","Ideal","l");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(0.35,0.94,0.55,0.96);
	legend_03->AddEntry("f_Baseline","Baseline","l");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(0.55,0.94,0.75,0.96);
	legend_04->AddEntry("f_IBD","IBD","l");
	legend_04->Draw("same");

	TLegend *legend_05 = new TLegend(0.75,0.94,1-Border,0.96);
	legend_05->AddEntry("f_BX_Result","BX result","l");	
	legend_05->Draw("same");	

	TPad *newpad=new TPad("newpad","a transparent pad",0.0,0.97,0.7,1.00);
	newpad->SetFillStyle(4000);
	newpad->Draw();
	newpad->cd();
	TPaveLabel *title = new TPaveLabel(0.0,0,1,1.00,"Radiopurity scenario");
	title->SetFillColor(4000);
	title->SetTextFont(42);
	title->Draw("same");

	
	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig6.pdf","pdf");
	
	
	
	//f->Close();
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig6();
  return 0;
}
#endif
