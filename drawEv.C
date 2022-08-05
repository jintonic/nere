// data from Fig. 3, Hayes and Vogel, Ann. Rev. Nucl. Part. Sci. 66 (2016) 219
// formula from Sec. 4.1.1, Bernstein, et al., Sci. Glob. Sec. 18 (2010) 127
void drawEv()
{
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);

	// mapping between pixel and Ev in MeV
	const int np=4; double MeV[np]={2, 4, 6, 8}, pixel[np]={133, 405, 675, 946};
	TGraph *gmp = new TGraph(np, pixel, MeV);
	gmp->SetMarkerStyle(8); gmp->SetMarkerSize(1);
	gmp->SetTitle(";pixel;E_{#nu} [MeV]");
	gmp->Draw("ap");

	gPad->Print("dN_VS_dE.pdf[");
	TF1 *fmp = new TF1("fmp","pol1",100,1000);
	gmp->Fit("fmp");
	gPad->Print("dN_VS_dE.pdf");

	// reproduce Fig. 3 in Hayes and Vogel
	const int n=11; double Ev5[n], Ev8[n], Ev9[n], Ev1[n];
 	double dNdE[n]={0.003, 0.005, 0.01, 0.02, 0.05, 0.1, 0.3, 0.5, 0.7, 1, 2};
	double pixel5[n]={895, 856, 813, 747, 647, 556, 404, 319, 257, 186, 33};
	double pixel8[n]={971, 930, 871, 815, 711, 627, 464, 377, 315, 232, 62};
	double pixel9[n]={848, 814, 749, 683, 574, 486, 358, 270, 219, 156, 22};
	double pixel1[n]={872, 841, 790, 726, 630, 544, 407, 325, 262, 192, 33};
	for (int i=0; i<n; i++) {
		Ev5[i] = fmp->Eval(pixel5[i]);
		Ev8[i] = fmp->Eval(pixel8[i]);
		Ev9[i] = fmp->Eval(pixel9[i]);
		Ev1[i] = fmp->Eval(pixel1[i]);
	}
	TGraph *gne5 = new TGraph(n, Ev5, dNdE);
	TGraph *gne8 = new TGraph(n, Ev8, dNdE);
	TGraph *gne9 = new TGraph(n, Ev9, dNdE);
	TGraph *gne1 = new TGraph(n, Ev1, dNdE);

	gne5->SetTitle(";E_{#nu} [MeV]; dN_{#nu}/dE_{#nu}");
	gne5->SetMarkerStyle(8); gne5->SetMarkerSize(1);
	gne8->SetMarkerStyle(8); gne8->SetMarkerSize(1);
	gne9->SetMarkerStyle(8); gne9->SetMarkerSize(1);
	gne1->SetMarkerStyle(8); gne1->SetMarkerSize(1);

	gne5->SetMarkerColor(kOrange); gne5->SetLineColor(kOrange);
	gne8->SetMarkerColor(kAzure+1); gne8->SetLineColor(kAzure+1);
	gne9->SetMarkerColor(8); gne9->SetLineColor(8);
	gne1->SetMarkerColor(kRed); gne1->SetLineColor(kRed);

	gne5->Draw("apc");
	gne8->Draw("pc");
	gne9->Draw("pc");
	gne1->Draw("pc");

	// empirical formula from Bernstein, et al.
	TF1 *f5 = new TF1("f5", "exp(-([0]+[1]*x+[2]*x*x+[3]*x*x*x))",1,9);
	TF1 *f8 = new TF1("f8", "exp(-([0]+[1]*x+[2]*x*x+[3]*x*x*x))",1,9);
	TF1 *f9 = new TF1("f9", "exp(-([0]+[1]*x+[2]*x*x+[3]*x*x*x))",1,9);
	TF1 *f1 = new TF1("f1", "exp(-([0]+[1]*x+[2]*x*x+[3]*x*x*x))",1,9);

	f5->SetLineColor(kOrange);
	f8->SetLineColor(kAzure+1);
	f9->SetLineColor(8);
	f1->SetLineColor(kRed);

	gne5->Fit("f5");
	gne8->Fit("f8");
	gne9->Fit("f9");
	gne1->Fit("f1");

	TLegend *leg = new TLegend(0.8, 0.6, 0.98, 0.98);
	leg->AddEntry(f5, "^{235}U", "l");
	leg->AddEntry(f8, "^{238}U", "l");
	leg->AddEntry(f9, "^{239}Pu", "l");
	leg->AddEntry(f1, "^{241}Pu", "l");
	leg->Draw();

	gPad->Print("dN_VS_dE.pdf");

	gPad->SetLogy();
	gPad->Print("dN_VS_dE.pdf");
	gPad->Print("dN_VS_dE.pdf]");
}
