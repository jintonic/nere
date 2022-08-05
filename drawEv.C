// data from Fig. 3, Hayes and Vogel, Ann. Rev. Nucl. Part. Sci. 66 (2016) 219
// formula from Sec. 4.1.1, Bernstein, et al., Sci. Glob. Sec. 18 (2010) 127
void drawEv()
{
	const int np=4; double MeV[np]={2, 4, 6, 8}, pixel[np]={133, 405, 675, 946};
	TGraph *gmp = new TGraph(np, pixel, MeV);
	gmp->SetMarkerStyle(8); gmp->SetMarkerSize(1);
	gmp->SetTitle(";pixel;E_{#nu} [MeV]");
	gmp->Draw("ap");
	TF1 *fmp = new TF1("fmp","pol1",100,1000);
	gmp->Fit("fmp");

	const int n=7; double Ev5[n], Ev8[n], Ev9[n], Ev1[n];
 	double dNdE[n]={0.005, 0.01, 0.05, 0.1, 0.5, 1, 2};
	double pixel5[n]={856, 813, 647, 556, 319, 186, 33};
	double pixel8[n]={930, 871, 711, 627, 377, 232, 62};
	double pixel9[n]={814, 749, 574, 486, 270, 156, 22};
	double pixel1[n]={841, 790, 630, 544, 325, 192, 33};
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

	gPad->SetLogy();
	gne5->Draw("ap");
	gne8->Draw("pc");
	gne9->Draw("pc");
	gne1->Draw("pc");

	TF1 *f5 = new TF1("f5", "exp(-([0]+[1]*x+[2]*x*x))",1,9);
	gne5->Fit("f5");
}
