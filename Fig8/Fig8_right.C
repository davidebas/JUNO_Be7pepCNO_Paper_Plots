 void Fig8_right(){

        TH2D* h_tfc_pep_IBD = new TH2D("","",8,0.60,0.95,8,0.60,0.95);

        double se, tp, val;

        ifstream read_pep;
        string input_pep =  "ratio_pep_IBD.txt";

        read_pep.open(input_pep.c_str());

        for (int i = 1; i <= 64; i++){

                read_pep >> se;
                read_pep >> tp;
                read_pep >> val;

                h_tfc_pep_IBD->Fill(tp,se,val);
        }

        read_pep.close();

        float w = 800;
        float l = 0.15;
        float r = 0.2;
        float b = 0.15;
        float t = 0.1;

        int h = ((1.-(l+r))*w)/(1.-(b+t));

        auto pep = new TCanvas("pep_IBD","pep_IBD",w,h);
        pep->SetLeftMargin(l),
        pep->SetRightMargin(r),
        pep->SetBottomMargin(b),
        pep->SetTopMargin(t);

        h_tfc_pep_IBD->SetTitle("Radiopurity scenario: IBD");
        h_tfc_pep_IBD->GetZaxis()->SetRangeUser(0.75,1.4);
        h_tfc_pep_IBD->GetXaxis()->SetTitle("TFC Tagging Power (TP)");
        h_tfc_pep_IBD->GetXaxis()->SetTitleSize(0.045);
        h_tfc_pep_IBD->GetXaxis()->SetTitleOffset(1.2);
        h_tfc_pep_IBD->GetYaxis()->SetTitle("TFC Subtracted Exposure (SE)");
        h_tfc_pep_IBD->GetYaxis()->SetTitleSize(0.045);
        h_tfc_pep_IBD->GetYaxis()->SetTitleOffset(1.5);
        h_tfc_pep_IBD->GetZaxis()->SetTitle("pep-#nu uncert. relative to TP=0.9 and SE=0.7");
        h_tfc_pep_IBD->GetZaxis()->SetTitleSize(0.045);
        h_tfc_pep_IBD->GetZaxis()->SetTitleOffset(1.2);
        h_tfc_pep_IBD->GetXaxis()->SetLabelSize(0.05);
        h_tfc_pep_IBD->GetYaxis()->SetLabelSize(0.05);
        h_tfc_pep_IBD->GetZaxis()->SetLabelSize(0.05);
        h_tfc_pep_IBD->GetXaxis()->SetDecimals(3);
        h_tfc_pep_IBD->GetXaxis()->SetMaxDigits(3);
        h_tfc_pep_IBD->GetYaxis()->SetDecimals(3);
        h_tfc_pep_IBD->GetYaxis()->SetMaxDigits(3);
        h_tfc_pep_IBD->GetZaxis()->SetDecimals(2);
        h_tfc_pep_IBD->GetZaxis()->SetMaxDigits(2);
        h_tfc_pep_IBD->SetStats(0);
        h_tfc_pep_IBD->GetZaxis()->SetLabelSize(0.05);
        h_tfc_pep_IBD->Draw("colz");

        pep->Update();
        pep->Print("Fig8_right.pdf","pdf");
        pep->Update();
}
