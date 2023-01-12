#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Comparison_LS_SS() {	

	ifstream Read_0;
	Read_0.open("BX.data",ios::in);

	TGraph *g_LS = new TGraph();
	TGraph *g_SS = new TGraph();
	
	double Time[5];
	double ADN_LS[5];
	double ADN_SS[5];	
	
	Float_t temp=0;

	std::string unused;
	
	for(int i=0; i<5;i++){
		Read_0 >> Time[i];
		Read_0 >> ADN_LS[i];
		Read_0 >> ADN_SS[i];
		g_LS->SetPoint(i,Time[i],ADN_LS[i]);
		g_SS->SetPoint(i,Time[i],ADN_SS[i]);
	
		cout << i << "   "  << Time[i] << "    " << ADN_LS[i] << "     " << ADN_SS[i] << endl;
	}
	
   	
	TFile *f = new TFile ("f.root", "RECREATE");
	f->cd();

	TCanvas *c = new TCanvas("c","c",600,500);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	
	c->cd();
	g_LS->Draw();
	g_SS->Draw("same");
	
	g_LS->GetXaxis()->SetTitle("Minimum detectable A_{DN}");
	g_LS->GetYaxis()->SetTitle("Time [y]");
	g_LS->GetYaxis()->SetTitleSize(0.05);
	g_LS->GetXaxis()->SetTitleSize(0.05);
	g_LS->GetYaxis()->SetLabelSize(0.05);
	g_LS->GetXaxis()->SetLabelSize(0.05);
	
	g_LS->GetYaxis()->SetRangeUser(0,1.5);	
	
	g_LS->SetLineColor(kRed);
	g_SS->SetLineColor(kBlue);
	g_LS->SetLineStyle(2);
	g_SS->SetLineStyle(2);
	g_LS->SetLineWidth(3);
	g_SS->SetLineWidth(3);
	g_LS->SetMarkerStyle(8);
	g_SS->SetMarkerStyle(8);
	
	g_LS->SetMarkerSize(1);
	g_SS->SetMarkerSize(1);
	g_LS->SetMarkerColor(kRed);
	g_SS->SetMarkerColor(kBlue);
	
        c->Update();

	g_LS->Write();
	g_SS->Write();
		
	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	//gPad->SetTicks(0,1);

	c->Update();	
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);

	gStyle->SetLegendTextSize(0.045);

	c->cd();

	TLegend *legend_01 = new TLegend(0.6,0.6,0.8,0.8);
	legend_01->AddEntry(g_LS,"Lomb-Scargle method","lp");
	legend_01->AddEntry(g_SS,"Statistical subtraction method","lp");
	legend_01->SetFillStyle(0);
	legend_01->Draw("same");
	
	//c->SetGridx();
	//c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");	
	c->Update();

}

#ifndef __CINT__
int main() {
  Comparison_LS_SS();
  return 0;
}
#endif

