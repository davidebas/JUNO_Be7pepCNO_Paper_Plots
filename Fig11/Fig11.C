 void Fig11(){

        TH2D* h_tfc_CNO_ideal = new TH2D("","",8,0.60,0.95,8,0.60,0.95);

        double se, tp, val;

        ifstream read_CNO;
        string input_CNO = "ratio_CNO_ideal.txt";

        read_CNO.open(input_CNO.c_str());

        for (int i = 1; i <= 64; i++){

                read_CNO >> se;
                read_CNO >> tp;
                read_CNO >> val;

                h_tfc_CNO_ideal->Fill(tp,se,val);
        }

        read_CNO.close();

        float w = 800;
        float l = 0.15;
        float r = 0.2;
        float b = 0.15;
        float t = 0.1;

        int h = ((1.-(l+r))*w)/(1.-(b+t));

        auto CNO = new TCanvas("CNO_ideal","CNO_ideal",w,h);
        CNO->SetLeftMargin(l),
        CNO->SetRightMargin(r),
        CNO->SetBottomMargin(b),
        CNO->SetTopMargin(t);

        h_tfc_CNO_ideal->SetTitle("Radiopurity scenario: ideal");
        h_tfc_CNO_ideal->GetZaxis()->SetRangeUser(0.75,1.4);
        h_tfc_CNO_ideal->GetXaxis()->SetTitle("TFC Tagging Power (TP)");
        h_tfc_CNO_ideal->GetXaxis()->SetTitleSize(0.045);
        h_tfc_CNO_ideal->GetXaxis()->SetTitleOffset(1.2);
        h_tfc_CNO_ideal->GetYaxis()->SetTitle("TFC Subtracted Exposure (SE)");
        h_tfc_CNO_ideal->GetYaxis()->SetTitleSize(0.045);
        h_tfc_CNO_ideal->GetYaxis()->SetTitleOffset(1.5);
        h_tfc_CNO_ideal->GetZaxis()->SetTitle("CNO-#nu uncert. relative to TP=0.9 and SE=0.7");
        h_tfc_CNO_ideal->GetZaxis()->SetTitleSize(0.045);
        h_tfc_CNO_ideal->GetZaxis()->SetTitleOffset(1.2);
        h_tfc_CNO_ideal->GetXaxis()->SetLabelSize(0.05);
        h_tfc_CNO_ideal->GetYaxis()->SetLabelSize(0.05);
        h_tfc_CNO_ideal->GetZaxis()->SetLabelSize(0.05);
        h_tfc_CNO_ideal->GetXaxis()->SetDecimals(3);
        h_tfc_CNO_ideal->GetXaxis()->SetMaxDigits(3);
        h_tfc_CNO_ideal->GetYaxis()->SetDecimals(3);
        h_tfc_CNO_ideal->GetYaxis()->SetMaxDigits(3);
        h_tfc_CNO_ideal->GetZaxis()->SetDecimals(2);
        h_tfc_CNO_ideal->GetZaxis()->SetMaxDigits(2);
        h_tfc_CNO_ideal->SetStats(0);
        h_tfc_CNO_ideal->GetZaxis()->SetLabelSize(0.05);
        h_tfc_CNO_ideal->Draw("colz");

        CNO->Update();
        CNO->Print("Fig11.pdf","pdf");
        CNO->Update();
}
