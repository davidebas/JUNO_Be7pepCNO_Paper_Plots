#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig15() {	

	ifstream Read_LS;
	ifstream Read_SS;
	Read_LS.open("LS_Median_AB.data",ios::in);
	Read_SS.open("SS_Median_AB.data",ios::in);

	TGraph *g_BX_LS = new TGraph();
	TGraph *g_BX_SS = new TGraph();
	TGraph *g_Ideal_LS = new TGraph();
	TGraph *g_Ideal_SS = new TGraph();
	TGraph *g_Baseline_LS = new TGraph();
	TGraph *g_Baseline_SS = new TGraph();
	TGraph *g_IBD_LS = new TGraph();
	TGraph *g_IBD_SS = new TGraph();
	
	double Time[5];
	double ADN_BX_LS[5];
	double ADN_BX_SS[5];	
	double ADN_Ideal_LS[5];
	double ADN_Ideal_SS[5];	
	double ADN_Baseline_LS[5];
	double ADN_Baseline_SS[5];	
	double ADN_IBD_LS[5];
	double ADN_IBD_SS[5];	
	
	Float_t temp=0;

	std::string unused;
	
	for(int i=0; i<5;i++){
		Read_LS >> Time[i];
		Read_LS >> ADN_BX_LS[i];
		Read_LS >> ADN_Ideal_LS[i];
		Read_LS >> ADN_Baseline_LS[i];
		Read_LS >> ADN_IBD_LS[i];
		g_BX_LS->SetPoint(i,Time[i],ADN_BX_LS[i]);
		g_Ideal_LS->SetPoint(i,Time[i],ADN_Ideal_LS[i]);
		g_Baseline_LS->SetPoint(i,Time[i],ADN_Baseline_LS[i]);
		g_IBD_LS->SetPoint(i,Time[i],ADN_IBD_LS[i]);

		//cout << i << "   "  << Time[i] << "    " << ADN_LS[i] << "     " << ADN_SS[i] << endl;
	}
	
	for(int i=0; i<5;i++){
		Read_SS >> Time[i];
		Read_SS >> ADN_BX_SS[i];
		Read_SS >> ADN_Ideal_SS[i];
		Read_SS >> ADN_Baseline_SS[i];
		Read_SS >> ADN_IBD_SS[i];
		g_BX_SS->SetPoint(i,Time[i],ADN_BX_SS[i]);
		g_Ideal_SS->SetPoint(i,Time[i],ADN_Ideal_SS[i]);
		g_Baseline_SS->SetPoint(i,Time[i],ADN_Baseline_SS[i]);
		g_IBD_SS->SetPoint(i,Time[i],ADN_IBD_SS[i]);

		//cout << i << "   "  << Time[i] << "    " << ADN_SS[i] << "     " << ADN_SS[i] << endl;
	}
	

   	
	TFile *f = new TFile ("f.root", "RECREATE");
	f->cd();

	double NNN = 600;
        double Width = NNN;
        double Height = Width*0.7;

	TCanvas *c = new TCanvas("c","c",Width,Height);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	
	c->cd();
	c->SetGrid();
	
	TPad *U=new TPad("newpad","a transparent pad",0,0,1,1);	
	TPad *pad1 = new TPad("pad1","",0.00,0.00,1,1);
	pad1->Draw();
	pad1->cd();
	pad1->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	//pad1->SetLogx();
	pad1->SetFillStyle(4000);	
	pad1->SetBorderSize(3);
	pad1->SetTopMargin(0.18);
	pad1->SetLeftMargin(0.14);
	pad1->SetRightMargin(0.03);
	pad1->SetBottomMargin(0.16);
	
	g_BX_LS->SetLineColor(kSpring-5);
	g_BX_LS->SetLineStyle(1);
	g_BX_LS->SetLineWidth(3);
	g_BX_LS->SetMarkerStyle(8);	
	g_BX_LS->SetMarkerSize(1);
	g_BX_LS->SetMarkerColor(kSpring-5);

	g_Ideal_LS->SetLineColor(kAzure+8);
	g_Ideal_LS->SetLineStyle(1);
	g_Ideal_LS->SetLineWidth(3);
	g_Ideal_LS->SetMarkerStyle(8);	
	g_Ideal_LS->SetMarkerSize(1);
	g_Ideal_LS->SetMarkerColor(kAzure+8);

	g_Baseline_LS->SetLineColor(kBlue+1);
	g_Baseline_LS->SetLineStyle(1);
	g_Baseline_LS->SetLineWidth(3);
	g_Baseline_LS->SetMarkerStyle(8);	
	g_Baseline_LS->SetMarkerSize(1);
	g_Baseline_LS->SetMarkerColor(kBlue+1);

	g_IBD_LS->SetLineColor(kViolet-7);
	g_IBD_LS->SetLineStyle(1);
	g_IBD_LS->SetLineWidth(3);
	g_IBD_LS->SetMarkerStyle(8);	
	g_IBD_LS->SetMarkerSize(1);
	g_IBD_LS->SetMarkerColor(kViolet-7);

	g_BX_SS->SetLineColor(kSpring-5);
	g_BX_SS->SetLineStyle(2);
	g_BX_SS->SetLineWidth(3);
	g_BX_SS->SetMarkerStyle(8);	
	g_BX_SS->SetMarkerSize(1);
	g_BX_SS->SetMarkerColor(kSpring-5);

	g_Ideal_SS->SetLineColor(kAzure+8);
	g_Ideal_SS->SetLineStyle(2);
	g_Ideal_SS->SetLineWidth(3);
	g_Ideal_SS->SetMarkerStyle(8);	
	g_Ideal_SS->SetMarkerSize(1);
	g_Ideal_SS->SetMarkerColor(kAzure+8);

	g_Baseline_SS->SetLineColor(kBlue+1);
	g_Baseline_SS->SetLineStyle(2);
	g_Baseline_SS->SetLineWidth(3);
	g_Baseline_SS->SetMarkerStyle(8);	
	g_Baseline_SS->SetMarkerSize(1);
	g_Baseline_SS->SetMarkerColor(kBlue+1);

	g_IBD_SS->SetLineColor(kViolet-7);
	g_IBD_SS->SetLineStyle(2);
	g_IBD_SS->SetLineWidth(3);
	g_IBD_SS->SetMarkerStyle(8);	
	g_IBD_SS->SetMarkerSize(1);
	g_IBD_SS->SetMarkerColor(kViolet-7);
	
	TMultiGraph *mg = new TMultiGraph();
	mg->Add(g_BX_LS,"lp");
	mg->Add(g_Ideal_LS,"lp");
	mg->Add(g_Baseline_LS,"lp");
	mg->Add(g_IBD_LS,"lp");	
	mg->Add(g_BX_SS,"lp");
	mg->Add(g_Ideal_SS,"lp");
	mg->Add(g_Baseline_SS,"lp");
	mg->Add(g_IBD_SS,"lp");	
	mg->Draw("A");
	
	mg->GetYaxis()->SetTitle("Minimum detectable A_{DN} [%]");
	mg->GetXaxis()->SetTitle("Time [y]");
	mg->GetYaxis()->SetTitleSize(0.055);
	mg->GetXaxis()->SetTitleSize(0.055);
	mg->GetYaxis()->SetLabelSize(0.055);
	mg->GetXaxis()->SetLabelSize(0.055);
	
	mg->GetYaxis()->SetRangeUser(0,5);		
	gPad->Modified();
	
	c->cd();

        c->Update();

	g_BX_LS->Write();
		
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	//gPad->SetTicks(0,1);

	c->Update();	
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);

	gStyle->SetLegendTextSize(0.055);

	double Dep = 0.05 ;
	double H = (1-Dep)/4. ;
	
	TLegend *legend_01 = new TLegend(Dep,0.85,Dep+H,0.90);
	legend_01->AddEntry(g_BX_SS,"BX-like","p");
	legend_01->Draw("same");

	TLegend *legend_02 = new TLegend(Dep+H,0.85,Dep+2*H,0.90);
	legend_02->AddEntry(g_Ideal_SS,"Ideal","p");
	legend_02->Draw("same");

	TLegend *legend_03 = new TLegend(Dep+2*H,0.85,Dep+3*H,0.90);
	legend_03->AddEntry(g_Baseline_SS,"Baseline","p");
	legend_03->Draw("same");

	TLegend *legend_04 = new TLegend(Dep+3*H,0.85,Dep+4*H,0.90);
	legend_04->AddEntry(g_IBD_SS,"IBD","p");
	legend_04->Draw("same");

	U->SetFillStyle(4000);
	U->Draw("same");
	U->cd();
	
	TPaveLabel *titleU = new TPaveLabel(0,0.93,1,1,"Radiopurity scenario");
	titleU->SetFillColor(4000);
	titleU->SetTextFont(42);
	titleU->Draw("same");
	

	pad1->cd();
	c->Update();
	c->Write("c");	
	c->Update();
	c->Print("Fig15.pdf","pdf");
}

#ifndef __CINT__
int main() {
  Fig15();
  return 0;
}
#endif

