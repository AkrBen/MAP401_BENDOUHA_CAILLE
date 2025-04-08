#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<approximation_bezier.h>

Bezier2 approx_bezier2 (Tableau_Point CONT, int j1, int j2) {
    Bezier2 B;
    B.C0 = CONT.tab[j1];
    B.C2 = CONT.tab[j2];

    int n = j2 - j1;
    
    if (n == 1) {
        B.C1.x = (CONT.tab[j1].x + CONT.tab[j2].x) / 2;
        B.C1.y = (CONT.tab[j1].y + CONT.tab[j2].y) / 2;

    } else if (n >= 2) {
        double alpha = (3.0 * (double)n) / ((double)n * (double)n - 1.0);
        double beta = (1.0 - 2.0 * (double)n) / (2.0 * ((double)n + 1.0));
        double Sx = 0;
        double Sy = 0;

        for (int i = 1; i <= n - 1; i++) {
            Sx = Sx + CONT.tab[i+j1].x;
            Sy = Sy + CONT.tab[i+j1].y;
        }

        B.C1.x = alpha * Sx + beta * (CONT.tab[j1].x + CONT.tab[j2].x);
        B.C1.y = alpha * Sy + beta * (CONT.tab[j1].y + CONT.tab[j2].y);
    }
    return B;
}

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, int d){
    int n= j2-j1;
    
    Bezier2 B = approx_bezier2(CONT,j1,j2);

	double dmax=0;
	int k=j1;
	for (int j=j1+1;j<=j2;j++){
        int i= j-j1;
        double ti =(double)(i)/(double)n;
        double dj=dist_point_bezier2(CONT.tab[j], B, ti);
		if (dmax<dj){
			dmax=dj;
			k=j;
		}
	}

	Liste_Point L=creer_liste_Point_vide();
	Liste_Point L1=creer_liste_Point_vide();
	Liste_Point L2=creer_liste_Point_vide();
	if (dmax<=d){
		L=ajouter_element_liste_Point(L, B.C0);
        L=ajouter_element_liste_Point(L, B.C1);
        L=ajouter_element_liste_Point(L, B.C2);
	}
	else {
		L1=simplification_douglas_peucker_bezier2(CONT, j1, k, d);
		L2=simplification_douglas_peucker_bezier2(CONT, k, j2, d);
		L=concatener_liste_Point(L1,L2);
	}
	return L;
}

