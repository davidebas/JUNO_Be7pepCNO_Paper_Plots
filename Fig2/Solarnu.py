import ROOT as r
import array

s_arr = ["pp","n13","o15","f17","b8","hep"]  #defining species

ofile = r.TFile("SolarNuspectrum.root","RECREATE") #output root file
c1 = r.TCanvas("c1","c1")
c1.SetLogy()
c1.SetLogx()
for species in s_arr:  # Looping over species
   print(species)
   sumv = 0
   with open(species+"spectrum.dat","r") as infile:  #to open the theoretical spectrum saved in .dat file
       E_pp_arr = array.array('d',[])
       p_pp_arr = array.array('d',[])
       n=0
       if species=="pp":
          scale_f = (5.98*pow(10,10))    # scale_f = flux normalisation scaling factor taken from HZ-SSM predictions
       if species=="b8":
          scale_f = (5.46*pow(10,6))
       if species=="n13":
          scale_f = (2.78*pow(10,8))
       if species=="o15":
          scale_f = (2.05*pow(10,8))
       if species=="f17":
          scale_f = (5.29*pow(10,6))
       if species=="hep":
          scale_f = (7.98*pow(10,3))
       for line in infile:
           line_strip = line.strip()
           if species=="pp":
              value = line_strip.split(" ")
           if (species=="n13") or (species=="o15") or (species=="f17"):
              value = line_strip.split("  ")
           if species == "hep":   
              value = line_strip.split("  ")
           if species=="b8":
              value = line_strip.split("           ")
           E_pp = float(value[-2])            # getting energy value from .dat file
           p_pp = float(value[-1])*scale_f    #getting probability to corresponding above energy value and multiplying it with scaling factor
           E_pp_arr.insert(n,E_pp)
           p_pp_arr.insert(n,p_pp)
           if(n>0):
                sumv = sumv + p_pp_arr[n]*(E_pp_arr[n]-E_pp_arr[n-1])   #checking final normalisation 
           n=n+1
       if species=="pp":
          E_pp_arr[-1] = 0.41838
          p_pp_arr[-1] = 0.0001    # inserting a small last value for better line visualisation
          gr_pp = r.TGraph(n,E_pp_arr,p_pp_arr)
       if species=="b8":
          gr_b8 = r.TGraph(n,E_pp_arr,p_pp_arr)
       if species=="n13":
          E_pp_arr[-1] = 1.19301
          p_pp_arr[-1] = 0.0001   # inserting a small last value for better line visualisation
          gr_n13 = r.TGraph(n,E_pp_arr,p_pp_arr)
       if species=="o15":
          gr_o15 = r.TGraph(n,E_pp_arr,p_pp_arr)
       if species=="f17":
          gr_f17 = r.TGraph(n,E_pp_arr,p_pp_arr)
       if species=="hep":
          gr_hep = r.TGraph(n,E_pp_arr,p_pp_arr)
       print(sumv)

# For monoenergetic lines, inseting some extra points at some random energy values for better line visualisation       
E_be7_862 = array.array('d',[0.5,0.8617,0.8618,0.8619,0.9])
p_be7_862 = array.array('d',[0.0001,0.0001,0.897*(4.93*pow(10,9)),0.0001,0.0001])
E_be7_384 = array.array('d',[0.3,0.3842,0.3843,0.3844,0.4])
p_be7_384 = array.array('d',[0.00001,0.0001,0.103*(4.93*pow(10,9)),0.0001,0.0001])
E_pep = array.array('d',[1.0,1.4399,1.44,1.4401,1.441])
p_pep = array.array('d',[0.0001,0.0001,(1.44*pow(10,8)),0.0001,0.0001])
gr_be7_862 = r.TGraph(5,E_be7_862,p_be7_862)
gr_be7_384 = r.TGraph(5,E_be7_384,p_be7_384)
gr_pep = r.TGraph(5,E_pep,p_pep)

               
r.gStyle.SetOptTitle(0)
c1.cd()
c1.Range(-4.369567,-4.362157,968.6522,2.124133);
c1.SetFillColor(0);
c1.SetBorderMode(0);
c1.SetBorderSize(2);
c1.SetLogy();
c1.SetRightMargin(0.08);
c1.SetLeftMargin(0.12);
c1.SetTopMargin(0.08);
c1.SetBottomMargin(0.12);
c1.SetFrameBorderMode(0);

gr_b8.GetXaxis().CenterTitle(1)
gr_b8.GetYaxis().CenterTitle(1);
gr_b8.GetYaxis().SetTitleSize(0.055);
gr_b8.GetYaxis().SetTitleOffset(1.0);
gr_b8.GetXaxis().SetTitleOffset(1.0);
gr_b8.GetYaxis().SetTitleFont(42);
gr_b8.GetXaxis().SetTitleFont(42);
gr_b8.GetYaxis().SetLabelFont(42);
gr_b8.GetXaxis().SetLabelFont(42);
gr_b8.GetXaxis().SetLabelSize(0.055);
gr_b8.GetYaxis().SetLabelSize(0.055);
gr_b8.GetXaxis().SetTitleSize(0.055);


gr_b8.SetLineColor(15)
gr_b8.SetLineWidth(2)
gr_b8.GetXaxis().SetRangeUser(0.1,20)
gr_b8.GetXaxis().SetTitle("Neutrino Energy [MeV]")
gr_b8.GetYaxis().SetTitle("Flux [cm^{-2}s^{-1}]")
gr_b8.GetYaxis().SetRangeUser(10,pow(10,13))
gr_b8.Draw("AL")
gr_pp.SetLineColor(14)
gr_pp.SetLineWidth(2)
gr_pp.Draw("Lsame")
gr_n13.SetLineColor(906)
gr_n13.SetLineWidth(2)
gr_n13.SetLineStyle(9)
gr_n13.Draw("Lsame")
gr_o15.SetLineColor(618)
gr_o15.SetLineWidth(2)
gr_o15.SetLineStyle(9)
gr_o15.Draw("Lsame")
gr_f17.SetLineColor(613)
gr_f17.SetLineWidth(2)
gr_f17.SetLineStyle(9)
gr_f17.Draw("Lsame")
gr_be7_862.SetLineColor(632)
gr_be7_862.SetLineWidth(2)
gr_be7_862.Draw("Lsame")
gr_be7_384.SetLineColor(632)
gr_be7_384.SetLineWidth(2)
gr_be7_384.Draw("Lsame")
gr_pep.SetLineColor(797)
gr_pep.SetLineWidth(2)
gr_pep.Draw("Lsame")
gr_hep.SetLineColor(17)
gr_hep.SetLineWidth(2)
gr_hep.Draw("Lsame")

c1.Update();

ofile.cd()
c1.Write()
ofile.Close()
c1.SaveAs("SolarNuspectrum.eps","RECREATE")
