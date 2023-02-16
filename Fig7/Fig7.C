#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig7() {	

	ifstream Read;
	Read.open("pep.txt",ios::in);

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

		Read >> RelError_IBD[i]; 
		Read >> IBD_left[i];
                Read >> IBD_right[i];
	}

	double *RelError_IBD_appo = new double[N-2];
	double *Time_IBD_appo = new double[N-2];
	double *IBD_left_appo = new double[N-2];
        double *IBD_right_appo = new double[N-2];

	double *RelError_Baseline_appo = new double[N];
        double *Time_Baseline_appo = new double[N];
	double *Baseline_left_appo = new double[N];
        double *Baseline_right_appo = new double[N];

	double *RelError_Ideal_appo = new double[N];
        double *Time_Ideal_appo = new double[N];
	double *Ideal_left_appo = new double[N];
        double *Ideal_right_appo = new double[N];

	double *RelError_BorexinoLike_appo = new double[N];
        double *Time_BorexinoLike_appo = new double[N];
	double *Bx_left_appo = new double[N];
        double *Bx_right_appo = new double[N];

	double appo = 0.;
	int k_IBD = 0;
	int k_Baseline = 0;
	int k_Ideal = 0;
	int k_BorexinoLike = 0;

	for(int i=0; i<N; i++){
                if(RelError_IBD[i]==9999){
                        appo = RelError_IBD[i];
                }else{
                        RelError_IBD_appo[k_IBD] = RelError_IBD[i];
			IBD_left_appo[k_IBD] = IBD_left[i];
                        IBD_right_appo[k_IBD] = IBD_right[i];
                        Time_IBD_appo[k_IBD] = Time[i];
                        k_IBD++;
                }
        }

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

	double Ymin = 1.;
	double Ymax = 100.;
	double Xmin = 0.0;
	double Xmax = 11.0;
	
	TF1 *f_IBD = new TF1("f_IBD","[0]+[1]*pow(x,[2])",2,Xmax);
	TF1 *f_Baseline = new TF1("f_Baseline","[0]+[1]*pow(x,[2])",0.5,Xmax);	
	TF1 *f_Ideal = new TF1("f_Ideal","[0]+[1]*pow(x,[2])",0.5,Xmax);	
	TF1 *f_BX = new TF1("f_BX","[0]+[1]*pow(x,[2])",0.5,Xmax);	

	f_IBD->SetParameter(2,-0.5);
	f_Baseline->SetParameter(2,-0.5);
	f_Ideal->SetParameter(2,-0.5);
	f_BX->SetParameter(2,-0.5);

	TF1 *f_BX_Result = new TF1("f_BX_Result","[0]",0,Xmax);
	f_BX_Result->SetParameter(0,16.5);	
	
	//TFile *f = new TFile ("f.root", "RECREATE");
	//f->cd();

	double NNN = 400;
        double Width = 2*NNN;
        double Height = Width*1.05;
        TCanvas *c = new TCanvas("c","c",Width,Height);
	gStyle->SetOptTitle(0);
	
	TPad *pad1 = new TPad("pad1","",0.00,0.00,1,0.94);
	pad1->Draw();
	pad1->cd();

	pad1->SetLogy();
	pad1->SetFillStyle(4000);	
	pad1->SetBorderSize(3);
	pad1->SetTopMargin(0.18);
	pad1->SetLeftMargin(0.11);
	pad1->SetRightMargin(0.03);
	pad1->SetBottomMargin(0.12);
	
	
	//Borexino-like scenario

	TGraphAsymmErrors *Graph_RelError_BorexinoLike = new TGraphAsymmErrors(N,Time_BorexinoLike_appo,RelError_BorexinoLike_appo,0,0,Bx_left_appo,Bx_right_appo);
	Graph_RelError_BorexinoLike->GetYaxis()->SetTitle("pep-#nu rate relative uncertainty [%]");
        Graph_RelError_BorexinoLike->GetXaxis()->SetLabelSize(0.04);
        Graph_RelError_BorexinoLike->GetYaxis()->SetLabelSize(0.04);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleSize(0.04);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleSize(0.04);
        Graph_RelError_BorexinoLike->GetYaxis()->SetRangeUser(Ymin,Ymax);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleOffset(0.90);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleOffset(1.30);
        Graph_RelError_BorexinoLike->GetXaxis()->SetRangeUser(Xmin,Xmax);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitle("Time [y]");

	Graph_RelError_BorexinoLike->Fit("f_BX","0");
	Graph_RelError_BorexinoLike->Draw("AP");
	Graph_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_RelError_BorexinoLike->SetMarkerSize(2);
	Graph_RelError_BorexinoLike->SetLineWidth(2);
	Graph_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_RelError_BorexinoLike->SetLineColor(kSpring-5);

	Graph_RelError_BorexinoLike->SetTitle("Time [y]");
	Graph_RelError_BorexinoLike->GetXaxis()->SetTitleOffset(1.4);

	f_BX->SetLineColor(kSpring-5);
	f_BX->SetLineWidth(3);
	f_BX->SetLineStyle(1);	
	f_BX->Draw("same");

	Graph_RelError_BorexinoLike->GetXaxis()->SetLimits(Xmin,Xmax);
	c->Update();
	//Ideal scenario

        TGraphAsymmErrors *Graph_RelError_Ideal = new TGraphAsymmErrors(N,Time_Ideal_appo,RelError_Ideal_appo,0,0,Ideal_left_appo,Ideal_right_appo);
        Graph_RelError_Ideal->Fit("f_Ideal","0");
        Graph_RelError_Ideal->Draw("Psame");
        Graph_RelError_Ideal->SetMarkerStyle(21);
        Graph_RelError_Ideal->SetMarkerSize(2);
	Graph_RelError_Ideal->SetLineWidth(2);
        Graph_RelError_Ideal->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal->SetLineColor(kAzure+8);

        f_Ideal->SetLineColor(kAzure+8);
        f_Ideal->SetLineWidth(3);
        f_Ideal->SetLineStyle(1);
        f_Ideal->Draw("same");
        c->Update();


	//Baseline scenario

        TGraphAsymmErrors *Graph_RelError_Baseline = new TGraphAsymmErrors(N,Time_Baseline_appo,RelError_Baseline_appo,0,0,Baseline_left_appo,Baseline_right_appo);
       
        Graph_RelError_Baseline->Fit("f_Baseline","0");
        Graph_RelError_Baseline->Draw("Psame");
        Graph_RelError_Baseline->SetMarkerStyle(22);
        Graph_RelError_Baseline->SetMarkerSize(2);
	Graph_RelError_Baseline->SetLineWidth(2);
        Graph_RelError_Baseline->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline->SetLineColor(kBlue+1);

        f_Baseline->SetLineColor(kBlue+1);
        f_Baseline->SetLineWidth(3);
        f_Baseline->SetLineStyle(1);
        f_Baseline->Draw("same");


	// IBD scenario

        TGraphAsymmErrors *Graph_RelError_IBD = new TGraphAsymmErrors(N-2,Time_IBD_appo,RelError_IBD_appo,0,0,IBD_left_appo,IBD_right_appo);
        Graph_RelError_IBD->Fit("f_IBD","0");
        Graph_RelError_IBD->Draw("Psame");
        Graph_RelError_IBD->SetMarkerStyle(23);
        Graph_RelError_IBD->SetMarkerSize(2);
	Graph_RelError_IBD->SetLineWidth(2);
        Graph_RelError_IBD->SetMarkerColor(kViolet-7);
        Graph_RelError_IBD->SetLineColor(kViolet-7);

        f_IBD->SetLineColor(kViolet-7);
        f_IBD->SetLineWidth(3);
        f_IBD->SetLineStyle(1);
        f_IBD->Draw("same");

	
	f_BX_Result->SetLineWidth(4);
	f_BX_Result->SetLineStyle(2);
	f_BX_Result->SetLineColor(kBlack);
	f_BX_Result->Draw("same");

	TGaxis *A3 = new TGaxis(Xmin,Ymax,Xmax,Ymax,0, Xmax*9.87,310,"-");
	A3->SetTitle("Exposure [kton y]");
	A3->SetTitleSize(0.04);
	A3->SetTitleOffset(1.4);
	A3->SetLabelSize(0.04);
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

	gStyle->SetLegendBorderSize(0);
        gStyle->SetLegendFillColor(0);
        gStyle->SetLegendTextSize(0.036);

	double Border = 0.01;



	TLegend *legend_01 = new TLegend(Border,0.90,0.20,0.95);
	legend_01->AddEntry("f_BX","BX-like","l");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(0.20,0.90,0.35,0.95);
	legend_02->AddEntry("f_Ideal","Ideal","l");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(0.35,0.90,0.55,0.95);
	legend_03->AddEntry("f_Baseline","Baseline","l");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(0.55,0.90,0.75,0.95);
	legend_04->AddEntry("f_IBD","IBD","l");
	legend_04->Draw("same");

	TLegend *legend_05 = new TLegend(0.75,0.90,1-Border,0.95);
	legend_05->AddEntry("f_BX_Result","BX result","l");	
	legend_05->Draw("same");
	

	TPad *newpad=new TPad("newpad","a transparent pad",0,0,1,1);
	newpad->SetFillStyle(4000);
	newpad->Draw();
	newpad->cd();
	TPaveLabel *title = new TPaveLabel(0.0,0.95,0.7,1.00,"Radiopurity scenario");
	title->SetFillColor(4000);
	title->SetTextFont(42);
	title->Draw("same");
	
	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig7.pdf","pdf");
		
	//f->Close();
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig7();
  return 0;
}
#endif

