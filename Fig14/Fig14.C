#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void DeltaChi2() {	

	ifstream Read_LS;
	Read_LS.open("Output_MedianIdeal_AB_6.0y_0.006.txt",ios::in);

	ifstream Read_SS;
	Read_SS.open("Output_MedianIdeal_SS.txt",ios::in);

	int N_Bins = 100;
	Float_t Max = 0.0012;
	Float_t Max_SS = 40;

	TH1F *Power_LS_0 = new TH1F("Power_LS_0","Power_LS_0",N_Bins,0,Max);
	TH1F *Power_LS_A = new TH1F("Power_LS_A","Power_LS_A",N_Bins,0,Max);
	
	TH1F *Power_SS_0 = new TH1F("Power_SS_0","Power_SS_0",N_Bins,0,Max_SS);
	TH1F *Power_SS_A = new TH1F("Power_SS_A","Power_SS_A",N_Bins,0,Max_SS);
	
	Float_t temp=0;

	std::string unused;


	while ( std::getline(Read_LS, unused) ){
		Read_LS >> temp;
		Read_LS >> temp;
		Power_LS_A->Fill(temp);
		cout << temp << endl;
		Read_LS >> temp;
		Power_LS_0->Fill(temp);
	}

	while ( std::getline(Read_SS, unused) ){
		Read_SS >> temp;
		Read_SS >> temp;
		Power_SS_A->Fill(temp);
		cout << temp << endl;
		Read_SS >> temp;
		Power_SS_0->Fill(temp);
	}

	double Ymin = 5.;
	double Ymax = 100.;
	double Xmin = 0.0;
	double Xmax = 11.0;
	
	double NNN = 400;
	double Width = 2*NNN;
	double Height = Width*1.05;

	TCanvas *c = new TCanvas("c","c",Width,Height/2);
	gStyle->SetOptTitle(0);
	
	double A = 1.;
	double Border = 0.001;


	cout << Border << " " << NNN/Height+Border << " " << (Width-Height)/NNN-Border << " " << 2*NNN/Height-Border << endl;


	
	TFile *f = new TFile ("f.root", "RECREATE");
	f->cd();
	Power_LS_0->Write();

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	
	c->cd();

	TPad *pad_TopLeft = new TPad("pad_TopLeft","",NNN/Height+Border,Border,2*NNN/Height-Border,2*NNN/Height-Border);
	//TPad *pad_TopLeft = new TPad("pad_TopLeft","",Border,Border,NNN/Height-Border,2*NNN/Height-Border);
	pad_TopLeft->Draw();
	pad_TopLeft->cd();

	Power_LS_A->Draw();
	Power_LS_0->Draw("same");
	
	Power_LS_A->GetXaxis()->SetTitle("Normalized LS Power");
	Power_LS_A->GetYaxis()->SetTitle("Entries");
	Power_LS_A->GetYaxis()->SetTitleSize(0.05);
	Power_LS_A->GetXaxis()->SetTitleSize(0.05);
	Power_LS_A->GetYaxis()->SetLabelSize(0.045);
	Power_LS_A->GetXaxis()->SetLabelSize(0.045);
	
	Power_LS_0->SetLineColor(kOrange+6);
	Power_LS_A->SetLineColor(kAzure-4);
	
	Power_LS_0->SetLineWidth(0);
	Power_LS_A->SetLineWidth(0);
	
	Power_LS_0->SetFillColorAlpha(kOrange+6, 0.7);
	Power_LS_A->SetFillColorAlpha(kAzure-4, 0.7);

	TGraph *g_Median = new TGraph();
	g_Median->SetPoint(0,2.78e-4,0.1);
	g_Median->SetPoint(1,2.78e-4,1e3);
	g_Median->SetLineWidth(3);
	g_Median->SetLineStyle(2);
	g_Median->SetLineColor(kBlue);
	g_Median->Draw("same");
	g_Median->Write();

		
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

	TLegend *legend_01 = new TLegend(0.25,0.8,1,1);
	legend_01->AddEntry(g_Median,"Modulated dataset 50% limit","l");
	legend_01->AddEntry(Power_LS_A,"Modulated dataset (A_{DN}=0.6%)","f");
	legend_01->AddEntry(Power_LS_0,"Unmodulated dataset","f");		
	legend_01->Draw("same");
	
	//c->SetGridx();
	//c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");	
	c->Update();


	pad_TopLeft->SetLogy();
	pad_TopLeft->SetFillStyle(4000);	
	pad_TopLeft->SetBorderSize(3);
	pad_TopLeft->SetTopMargin(0.2);
	pad_TopLeft->SetLeftMargin(0.15);
	pad_TopLeft->SetRightMargin(0.03);
	pad_TopLeft->SetBottomMargin(0.14);
	
	//N13 free

	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	gPad->SetTicks(0,1);


	c->cd();

//	TPad *pad_TopRight = new TPad("pad_TopRight","",NNN/Height+Border,Border,2*NNN/Height-Border,2*NNN/Height-Border);
	TPad *pad_TopRight = new TPad("pad_TopRight","",Border,Border,NNN/Height-Border,2*NNN/Height-Border);

	pad_TopRight->Draw("same");
	pad_TopRight->cd();

	pad_TopRight->SetLogy();
	pad_TopRight->SetFillStyle(4000);	
	pad_TopRight->SetBorderSize(3);
	pad_TopRight->SetTopMargin(0.2);
	pad_TopRight->SetLeftMargin(0.15);
	pad_TopRight->SetRightMargin(0.03);
	pad_TopRight->SetBottomMargin(0.14);

	Power_SS_A->Draw();
	Power_SS_0->Draw("same");
	
	Power_SS_A->GetXaxis()->SetTitle("#Delta#chi^{2}");
	Power_SS_A->GetYaxis()->SetTitle("Entries");
	Power_SS_A->GetYaxis()->SetTitleSize(0.05);
	Power_SS_A->GetXaxis()->SetTitleSize(0.05);
	Power_SS_A->GetYaxis()->SetLabelSize(0.045);
	Power_SS_A->GetXaxis()->SetLabelSize(0.045);
	
	Power_SS_0->SetLineColor(kOrange+6);
	Power_SS_A->SetLineColor(kAzure-4);
	
	Power_SS_0->SetLineWidth(0);
	Power_SS_A->SetLineWidth(0);
	
	Power_SS_0->SetFillColorAlpha(kOrange+6, 0.7);
	Power_SS_A->SetFillColorAlpha(kAzure-4, 0.7);

	TGraph *g_Median_SS = new TGraph();
	g_Median_SS->SetPoint(0,10.925,0.1);
	g_Median_SS->SetPoint(1,10.925,1e3);
	g_Median_SS->SetLineWidth(3);
	g_Median_SS->SetLineStyle(2);
	g_Median_SS->SetLineColor(kBlue);
	g_Median_SS->Draw("same");
	g_Median_SS->Write();

	//TLegend *legend_02 = new TLegend(0.05,0.8,0.5,1);
	//legend_02->AddEntry(g_Median,"Modulated dataset 50% limit","l");
	//legend_02->AddEntry(Power_SS_A,"Modulated dataset (A_{gMode}=0.6%)","f");
	//legend_02->AddEntry(Power_SS_0,"Unmodulated dataset","f");		
	//legend_02->Draw("same");	
	
	//O15 free
	
	
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

	
	c->SetGridx();
	c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");
	c->Print("Fig14.pdf","pdf");
	
	
	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig14();
  return 0;
}
#endif

