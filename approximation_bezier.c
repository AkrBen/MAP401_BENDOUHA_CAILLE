#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<approximation_bezier.h>

Bezier2 approx_bezier2(Contour L, int j1, int j2){
    int n1=j2-j1;
    float n=n1;
    Point C0=L->first;
    Point C1;
    Point C2=L->last;
    if (n==2){
        C1.x=(C0.x+C2.x)/2;
        C1.y=(C0.y+C2.y)/2;
    }
    else {
        float alpha=3*n/(pow(n,2)-1);
        float beta=(1-2*n)/(2*(n+1));
        Tableau_Point T=sequence_points_liste_vers_tableau(L);
        int i=1;
        int nP=T.taille;
        int somme=0;
        while(i<nP-1){
            somme=somme+T.tab[i];
            i++;
        }
        C1.x=alpha*somme+beta*(C0.x+C2.x);
        C1.y=alpha*somme+beta*(C0.y+C2.y);
    }
    Bezier2 B2;
    B2.C0=C0;
    B2.C1=C1;
    B2.C2=C2;
    return B2;
}

Liste_Point simplification_douglas_peucker_bezier2(Contour CONT, int j1, int j2, int d){
    
}