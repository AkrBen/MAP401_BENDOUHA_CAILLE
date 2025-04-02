#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<approximation_bezier.h>

Bezier2 approx_bezier2(Contour L, int j1, int j2){
    int n1=j2-j1;
    float n=n1;
    Point C0=L.first->data;
    Point C1;
    Point C2=L.last->data;
    if (n==1){
        C1.x=(C0.x+C2.x)/2;
        C1.y=(C0.y+C2.y)/2;
    }
    else {
        float alpha=3*n/(pow(n,2)-1);
        float beta=(1-2*n)/(2*(n+1));
        Tableau_Point T=sequence_points_liste_vers_tableau(L);
        int i=1;
        int nP=T.taille;
        int sommeX=0;
        int sommeY=0;
        while(i<nP-1){
            sommeX=sommeX+T.tab[i].x;
            sommeY=sommeY+T.tab[i].y;
            i++;
        }
        C1.x=alpha*sommeX+beta*(C0.x+C2.x);
        C1.y=alpha*sommeY+beta*(C0.y+C2.y);
    }
    Bezier2 B2;
    B2.C0=C0;
    B2.C1=C1;
    B2.C2=C2;
    return B2;
}

Liste_Point simplification_douglas_peucker_bezier2(Contour CONT, int j1, int j2, int d){
    int n= j2-j1;

    Bezier2 B = approx_bezier2(CONT,j1,j2);

    Tableau_Point CONT1 =sequence_points_liste_vers_tableau(CONT);

	double dmax=0;
	int k=j1;
	for (int j=j1+1;j<=j2;j++){
        int i= j-j1;
        double ti =(double)i/(double)n;
        double dj=dist_point_bezier2(CONT1.tab[j], B, ti);
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

