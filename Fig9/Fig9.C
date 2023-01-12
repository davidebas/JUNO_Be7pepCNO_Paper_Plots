#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig9() {	

	ifstream Read;
	Read.open("input_proj_TP_1stJuly_ratio.txt",ios::in);

	int N = 8;
	
	double *tp = new double[N];
	double *RelError_IBD = new double[N];
	double *RelError_Baseline  = new double[N];
	double *RelError_Ideal  = new double[N];
	double *RelError_BorexinoLike  = new double[N];
	
	/*double *Bx_left = new double[N];
        double *Bx_right = new double[N];
	double *Ideal_left = new double[N];
        double *Ideal_right = new double[N];
	double *Baseline_left = new double[N];
        double *Baseline_right = new double[N];
	double *IBD_left = new double[N];
        double *IBD_right = new double[N];*/



	double radius = 14.;
	double DC = 1.0;
	double mass = 4./3.*3.14*pow(radius,3)*860*DC/pow(10,5);
	
	cout << "mass: " << mass << endl;


	for(int i=0; i<N; i++){

		Read >> tp[i];

		Read >> RelError_BorexinoLike[i];
		//Read >> Bx_left[i];
                //Read >> Bx_right[i];

		Read >> RelError_Ideal[i]; 
		//Read >> Ideal_left[i];
                //Read >> Ideal_right[i];

		Read >> RelError_Baseline[i]; 
		//Read >> Baseline_left[i];
                //Read >> Baseline_right[i];

		Read >> RelError_IBD[i]; 
		//Read >> IBD_left[i];
                //Read >> IBD_right[i];
	}

	double Ymin = 0.6;
	double Ymax = 1.4;
	double Xmin = 0.6;
	double Xmax = 0.95;
	
	float w = 800;
        float l = 0.15;
        float r = 0.2;
        float b = 0.15;
        float t = 0.15;

        int h = ((1.-(l+r))*w)/(1.-(b+t));

	double NNN = 400;
        double Width = 2*NNN;
        double Height = Width*1.05;
        TCanvas *c = new TCanvas("c","c",1100,800);
	gStyle->SetOptTitle(0);
	
	TPad *pad1 = new TPad("pad1","",0.03,0.03,1,0.98);
	pad1->Draw();
	pad1->cd();

	pad1->SetFillStyle(4000);	
	pad1->SetBorderSize(3);
	pad1->SetTopMargin(0.13);
	pad1->SetLeftMargin(0.11);
	pad1->SetRightMargin(0.03);
	pad1->SetBottomMargin(0.12);
	
	
	//Borexino-like scenario

	TGraphErrors *Graph_RelError_BorexinoLike = new TGraphErrors(N,tp,RelError_BorexinoLike,0,0);
	Graph_RelError_BorexinoLike->SetTitle("");
	Graph_RelError_BorexinoLike->GetYaxis()->SetTitle("pep-#nu unc. rel. to TP=0.9\% and SE=0.7\%");
	Graph_RelError_BorexinoLike->GetXaxis()->SetTitle("TFC Tagging Power");
        Graph_RelError_BorexinoLike->GetYaxis()->SetLabelSize(0.045);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleSize(0.045);
	Graph_RelError_BorexinoLike->GetXaxis()->SetLabelSize(0.045);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleSize(0.045);
        Graph_RelError_BorexinoLike->GetYaxis()->SetRangeUser(Ymin,Ymax);
        Graph_RelError_BorexinoLike->GetXaxis()->SetTitleOffset(1.20);
        Graph_RelError_BorexinoLike->GetYaxis()->SetTitleOffset(1.30);
        Graph_RelError_BorexinoLike->GetXaxis()->SetRangeUser(0.58,0.97);
        
        Graph_RelError_BorexinoLike->GetXaxis()->SetDecimals();
        Graph_RelError_BorexinoLike->GetXaxis()->SetMaxDigits(3);

        Graph_RelError_BorexinoLike->GetYaxis()->SetDecimals();
        Graph_RelError_BorexinoLike->GetYaxis()->SetMaxDigits(3);
        
       // Graph_RelError_BorexinoLike->GetXaxis

	Graph_RelError_BorexinoLike->SetMarkerStyle(20);
	Graph_RelError_BorexinoLike->SetMarkerSize(2);
	Graph_RelError_BorexinoLike->SetLineWidth(2);
	Graph_RelError_BorexinoLike->SetMarkerColor(kSpring-5);
	Graph_RelError_BorexinoLike->SetLineColor(kSpring-5);
	Graph_RelError_BorexinoLike->Draw("ALP");

	Graph_RelError_BorexinoLike->GetXaxis()->SetLimits(0.58,0.97);
	c->Update();
	//Ideal scenario

        TGraphErrors *Graph_RelError_Ideal = new TGraphErrors(N,tp,RelError_Ideal,0,0);
        Graph_RelError_Ideal->SetMarkerStyle(21);
        Graph_RelError_Ideal->SetMarkerSize(2);
	Graph_RelError_Ideal->SetLineWidth(2);
        Graph_RelError_Ideal->SetMarkerColor(kAzure+8);
        Graph_RelError_Ideal->SetLineColor(kAzure+8);
	Graph_RelError_Ideal->Draw("LPsame");

        c->Update();


	//Baseline scenario

        TGraphErrors *Graph_RelError_Baseline = new TGraphErrors(N,tp,RelError_Baseline,0,0);
       
        Graph_RelError_Baseline->SetMarkerStyle(22);
        Graph_RelError_Baseline->SetMarkerSize(2);
	Graph_RelError_Baseline->SetLineWidth(2);
        Graph_RelError_Baseline->SetMarkerColor(kBlue+1);
        Graph_RelError_Baseline->SetLineColor(kBlue+1);
	        
	Graph_RelError_Baseline->Draw("LPsame");
	// IBD scenario

        TGraphErrors *Graph_RelError_IBD = new TGraphErrors(N,tp,RelError_IBD,0,0);

        Graph_RelError_IBD->SetMarkerStyle(23);
        Graph_RelError_IBD->SetMarkerSize(2);
	Graph_RelError_IBD->SetLineWidth(2);
        Graph_RelError_IBD->SetMarkerColor(kViolet-7);
        Graph_RelError_IBD->SetLineColor(kViolet-7);
	Graph_RelError_IBD->Draw("LPsame");

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

	double LegendStep = 1.00/4. ;

	TLegend *legend_01 = new TLegend(Border,0.90,LegendStep,0.94);
	legend_01->AddEntry(Graph_RelError_BorexinoLike,"BX-like","l");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(LegendStep,0.90,2.*LegendStep,0.94);
	legend_02->AddEntry(Graph_RelError_Ideal,"Ideal","l");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(2.*LegendStep,0.90,3.*LegendStep,0.94);
	legend_03->AddEntry(Graph_RelError_Baseline,"Baseline","l");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(3.*LegendStep,0.90,4.*LegendStep,0.94);
	legend_04->AddEntry(Graph_RelError_IBD,"IBD","l");
	legend_04->Draw("same");


	/*TLegend *legend_05 = new TLegend(3.7*LegendStep,0.95,4.7*LegendStep,1.00);
        legend_05->AddEntry("f_allfree","all free","l");
        legend_05->Draw("same");

	TLegend *legend_06 = new TLegend(4.7*LegendStep,0.95,5.7*LegendStep,1.00);
	legend_06->AddEntry("f_pepc","pep constrained","l");	
	legend_06->Draw("same");*/
	TPad *newpad=new TPad("newpad","a transparent pad",0.0,0,1.00,1.00);
	newpad->SetFillStyle(4000);
	newpad->Draw();
	newpad->cd();
	TPaveLabel *title = new TPaveLabel(0.0,0.95,1.00,1.00,"Radiopurity scenario");
	title->SetFillColor(4000);
	title->SetTextFont(42);
	title->Draw("same");
	
	c->cd();

	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig9.pdf","pdf");
		
	//f->Close();
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig9();
  return 0;
}
#endif

