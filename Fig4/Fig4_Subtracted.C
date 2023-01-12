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


void Fig4_Subtracted() {	

	int maximumplot = 3e7;
	double minimumplot = 1;

	TFile f("Inputs/OutputRoot_Test_Baseline_6Y.root","read");
	TH1D* h1 = (TH1D*)f.Get("PseudoDataset_Sub")->Clone();
	f.cd("PDFs");
	TH1D* h2 = (TH1D*)f.Get("PDFs/Be7;1")->Clone();
	TH1D* h3 = (TH1D*)f.Get("PDFs/pep;1")->Clone();
	TH1D* h4 = (TH1D*)f.Get("PDFs/CNO;1")->Clone();
	TH1D* h5 = (TH1D*)f.Get("PDFs/Bi210;1")->Clone();
	TH1D* h6 = (TH1D*)f.Get("PDFs/K40;1")->Clone();
	TH1D* h7 = (TH1D*)f.Get("PDFs/Kr85;1")->Clone();
	TH1D* h8 = (TH1D*)f.Get("PDFs/U238;1")->Clone();
	TH1D* h9 = (TH1D*)f.Get("PDFs/Th232;1")->Clone();
	TH1D* h10 = (TH1D*)f.Get("PDFs/Po210;1")->Clone();
	TH1D* h11 = (TH1D*)f.Get("PDFs/C11;1")->Clone();

	TH1D* h12 = (TH1D*)f.Get("PDFs/C10_2;1")->Clone();
	TH1D* h13 = (TH1D*)f.Get("PDFs/He6_2;1")->Clone();

	TFile f2("Inputs/PDFs_NuSol_J21v1r0-Pre0_r15_Thr300_1Y_Smoothed_2021-June_N13O15.root","read");
	TH1D* h_N13 = (TH1D*)f2.Get("h_NQE_N13")->Clone();
	TH1D* h_O15 = (TH1D*)f2.Get("h_NQE_O15")->Clone();




	h1->SetBinContent(h1->GetNbinsX(),0);	
	
	TCanvas *c1 = new TCanvas("c1", "",700,500);
	c1->cd();
	//gStyle->SetOptTitle(0);
	c1->Range(-4.369567,-4.362157,968.6522,2.124133);
	c1->SetFillColor(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(2);
	c1->SetLogy();
	c1->SetRightMargin(0.08);
	c1->SetLeftMargin(0.12);
	c1->SetTopMargin(0.10);
	c1->SetBottomMargin(0.12);
	c1->SetFrameBorderMode(0);

	TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.52,0.90,0.95);
	pad1->SetFillColor(11);
	pad1->Draw();
		
	/**** DATA ****/
	h1->GetXaxis()->CenterTitle(kTRUE);
	h1->GetYaxis()->CenterTitle(kTRUE);
	h1->GetYaxis()->SetTitleSize(0.055);
	h1->GetYaxis()->SetTitleOffset(1.0);
	h1->GetYaxis()->SetTitleFont(42);
	h1->GetXaxis()->SetTitleFont(42);
	h1->GetYaxis()->SetLabelFont(42);
	h1->GetXaxis()->SetLabelFont(42);							
	h1->GetYaxis()->SetTitle("Events / p.e.");
	h1->GetYaxis()->SetLabelSize(0.055);
	h1->GetXaxis()->SetLabelSize(0.055);
	
	h1->GetXaxis()->SetTickSize(0);
	h1->GetXaxis()->SetLabelSize(0);

	h1->GetXaxis()->SetTitleSize(0.055);
	h1->GetXaxis()->SetTitleOffset(1.0);
	h1->GetXaxis()->SetTitle("Reconstructed energy [p.e.]");
	h1->GetXaxis()->SetRangeUser(650,2400);
	h1->GetYaxis()->SetRangeUser(minimumplot,maximumplot);
	h1->SetLineColor(kBlack);
	h1->SetLineWidth(2);

	h1->SetTitle("");
	gStyle->SetTitleFontSize(0.055);

	h1->DrawCopy("P0L");
	h1->SetLineWidth(2);



	gStyle->SetOptStat(0);
	c1->Update();

	TString vinit[13] = {"Be7", "pep", "Bi210", "K40", "Kr85", "U238", "Th232","Po210","CNO","C10_2","He6_2","C11","C11_2"};	// default species
	//632,632,842,799,600,921,870,800,632,844,425,616,616
	
	/**** BACKGROUNDS ****/
	h5->SetLineColor(842); h5->SetLineWidth(2); h5->SetLineStyle(3);
	h5->DrawCopy("same");

	h6->SetLineColor(kOrange+4); h6->SetLineWidth(2); h6->SetLineStyle(3);
	h6->DrawCopy("same");

	h7->SetLineColor(kViolet+4); h7->SetLineWidth(2); h7->SetLineStyle(3);
	h7->DrawCopy("same");

	h8->SetLineColor(921); h8->SetLineWidth(2); h8->SetLineStyle(3);
	h8->DrawCopy("same");

	h9->SetLineColor(870); h9->SetLineWidth(2); h9->SetLineStyle(3);
	h9->DrawCopy("same");

	h10->SetLineColor(kOrange-2); h10->SetLineWidth(2); h10->SetLineStyle(3);
	h10->DrawCopy("same");

	h11->SetLineColor(833); h11->SetLineWidth(2); h11->SetLineStyle(3);	
	h11->DrawCopy("same");
	
	h_N13->Scale(72173./h_N13->Integral());
	h_O15->Scale(54647./h_O15->Integral());

	/**** SOLAR NEUTRINOS ****/
	h2->SetLineColor(kRed); h2->SetLineWidth(4); 
	h2->DrawCopy("same");

	h3->SetLineColor(kOrange+1); h3->SetLineWidth(4); 
	h3->DrawCopy("same");

	h_N13->SetLineColor(906); h_N13->SetLineWidth(4);
	h_N13->DrawCopy("same");

	h_O15->SetLineColor(kOrange-1); h_O15->SetLineWidth(4);
	h_O15->DrawCopy("same");
	
	// LEGEND
	TLegend *leg1 = new TLegend(0.25,0.66,0.45,0.86,NULL,"brNDC");
	leg1->SetTextAlign(13);
	leg1->SetTextSize(0.05);
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(0);
	leg1->SetTextFont(42);
	leg1->AddEntry(h2,"^{7}Be-#nu","l");	
	leg1->AddEntry(h3,"pep-#nu","l");	
	leg1->AddEntry(h_N13,"^{13}N-#nu","l");	
	leg1->AddEntry(h_O15,"^{15}O-#nu","l");
	
	leg1->Draw();
	c1->Update();

	TLegend *leg2 = new TLegend(0.45,0.61,0.7,0.86,NULL,"brNDC");
	leg2->SetTextAlign(13);
	leg2->SetTextSize(0.055);
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(42);	
	leg2->AddEntry(h5,"^{210}Bi","l");
	leg2->AddEntry(h7,"^{85}Kr","l");
	leg2->AddEntry(h8,"^{238}U chain","l");
	leg2->AddEntry(h9,"^{232}Th chain","l");
	leg2->AddEntry(h6,"^{40}K","l");
	leg2->Draw();
	c1->Update();

	TLegend *leg3 = new TLegend(0.7,0.61,0.9,0.86,NULL,"brNDC");
	leg3->SetTextAlign(13);
	leg3->SetTextSize(0.055);
	leg3->SetBorderSize(0);
	leg3->SetFillStyle(0);
	leg3->SetTextFont(42);	
	leg3->AddEntry(h10,"^{210}Po","l");
	leg3->AddEntry(h11,"^{11}C","l");
	
	leg3->AddEntry(h1,"dataset","l");
	leg3->Draw();
	
	// upper x axis
	TGaxis *A3 = new TGaxis(650,maximumplot,2400,maximumplot,650, 2400,10,"-");
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
	TF1 *LowerAxis3=new TF1("LowerAxis3",funzione4,funzione3(650),funzione3(2400),0);
	TGaxis *A5 = new TGaxis(650,minimumplot,2400,minimumplot,"LowerAxis3",520);
	A5->SetTitle("");
	A5->SetLabelSize(0.05);
	A5->SetTitleSize(0.05);
	A5->SetTitleOffset(0.);
	A5->SetLabelFont(42);
	A5->SetTextFont(42);
	A5->Draw();
	c1->Update();

  	c1->Print("Fig4_Subtracted.pdf","pdf");
}

#ifndef __CINT__
int main() {
  Fig4_Subtracted();
}
#endif
