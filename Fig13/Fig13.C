#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"

double aa = -4.80508e-09;
double bb = 0.000663382;
double cc = 0.0195086;

double funzione3(double x) {
	return (cc+bb*x+aa*x*x);
}

double funzione4(double *x, double *par) {
	return (-bb+TMath::Sqrt(bb*bb-4*(cc-x[0])*aa) ) / (2*aa);
}

void Fig13() {	

	int maximumplot = 3000;
	double minimumplot = -3000;

	TFile f1("InputRoot_Fig13.root","read");
	TH1D* h1 = (TH1D*)f1.Get("PseudoDataset_Diff")->Clone();
	
	//TH1D* hPDF_Total_Diff = (TH1D*)f1.Get("hPDF_Total_Diff;1")->Clone();
	
	TH1D* hPDF_Total_Diff = (TH1D*)f1.Get("PDFs/Be7;2")->Clone();
	

	TCanvas *c1 = new TCanvas("c1", "Spectra_FourScenarios",700,500);
	c1->cd();
	//gStyle->SetOptTitle(0);
	c1->Range(-4.369567,-4.362157,968.6522,2.124133);
	c1->SetFillColor(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(2);
	//c1->SetLogy();
	c1->SetRightMargin(0.08);
	c1->SetLeftMargin(0.12);
	c1->SetTopMargin(0.10);
	c1->SetBottomMargin(0.12);
	c1->SetFrameBorderMode(0);
	c1->SetGridx();
	c1->SetGridy();

	TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.52,0.90,0.80);
	pad1->SetFillColor(11);
	pad1->Draw();
		
	/**** DATA ****/
	h1->GetXaxis()->CenterTitle(kTRUE);
	h1->GetYaxis()->CenterTitle(kTRUE);
	gStyle->SetTitleFontSize(0.055);
	h1->SetTitle("");

	h1->GetYaxis()->SetTitleSize(0.055);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->GetXaxis()->SetLabelFont(42);							
	h1->GetYaxis()->SetTitle("Events / p.e.");
	h1->GetYaxis()->SetLabelSize(0.055);
	h1->GetXaxis()->SetLabelSize(0.055);

	h1->GetXaxis()->SetTitleSize(0.055);
	h1->GetXaxis()->SetTitleOffset(1.0);
	
	h1->GetXaxis()->SetLabelSize(0);
	h1->GetXaxis()->SetTickSize(0);
		
	h1->GetXaxis()->SetTitle("Energy [MeV]");
	h1->GetXaxis()->SetRangeUser(640,1200);
	h1->GetYaxis()->SetRangeUser(minimumplot,maximumplot);
	h1->SetLineColor(kBlack);
	h1->SetLineWidth(1);
	
	TH1F* h_null = new TH1F("h1","h1",200,600,1200);
	for(int i=0;i<200;i++){
		h_null->GetBinContent(i,0);
		}
		
		
	
	h1->DrawCopy();
	gStyle->SetOptStat(0);
	hPDF_Total_Diff->SetLineWidth(2);
	hPDF_Total_Diff->Draw("same");
	h_null->SetLineStyle(2);
	h_null->SetLineWidth(2);
	h_null->SetLineColor(kRed);
	h_null->Draw("same");


	
	c1->Update();

	// LEGEND
	TLegend *leg1 = new TLegend(0.3,0.68,0.75,0.89,NULL,"brNDC");
	leg1->SetTextAlign(13);
	leg1->SetTextSize(0.055);
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(0);
	leg1->SetTextFont(42);
	leg1->AddEntry(h1,"Difference dataset","l");
	leg1->AddEntry(hPDF_Total_Diff,"Alternative hypothesis (#Delta R_{^{7}Be} free)");
	leg1->AddEntry(h_null,"Null hypothesis (#Delta R_{^{7}Be} fixed to zero)");			
	leg1->Draw();
	c1->Update();
	

	// upper x axis
	TGaxis *A3 = new TGaxis(640,maximumplot,1200,maximumplot,640, 1200,10,"-");
	A3->SetTitle("p.e.");
	A3->SetTitleSize(0.05);
	A3->SetTitleOffset(0.9);
	A3->SetLabelSize(0.05);
	A3->SetTextFont(42);
	A3->SetLabelFont(42);
	A3->CenterTitle(kTRUE);
	A3->Draw("SAME");
	c1->Update();	

	// lower x axis
	TF1 *LowerAxis3=new TF1("LowerAxis3",funzione4,funzione3(640),funzione3(1200),0);
	TGaxis *A5 = new TGaxis(640,minimumplot,1200,minimumplot,"LowerAxis3",510);
	A5->SetTitle("");
	A5->SetLabelSize(0.05);
	A5->SetTitleSize(0.05);
	A5->SetTitleOffset(0.);
	A5->SetLabelFont(42);
	A5->SetTextFont(42);
	A5->Draw();
	c1->Update();

	c1->Update();

  c1->Print("Fig13.pdf","pdf");
}

#ifndef __CINT__
int main() {
  Fig13();
}
#endif
