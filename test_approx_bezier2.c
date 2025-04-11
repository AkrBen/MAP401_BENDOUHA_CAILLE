#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<approximation_bezier.h>

Bezier2 approx_bezier2 (Tableau_Point CONT, int j1, int j2) {
    Bezier2 B2;
    B2.C0 = CONT.tab[j1];
    B2.C2 = CONT.tab[j2];

    int n = j2 - j1;

    if (n == 1) {
        B2.C1.x = (CONT.tab[j1].x + CONT.tab[j2].x) / 2;
        B2.C1.y = (CONT.tab[j1].y + CONT.tab[j2].y) / 2;

    } else if (n >= 2) {
        double a = (3.0 * (double)n) / ((double)n * (double)n - 1.0);
        double b = (1.0 - 2.0 * (double)n) / (2.0 * ((double)n + 1.0));
        double Sx = 0;
        double Sy = 0;

        for (int i = 1; i <= n - 1; i++) {
            Sx = Sx + CONT.tab[i+j1].x;
            Sy = Sy + CONT.tab[i+j1].y;
        }

        B2.C1.x = a * Sx + b * (CONT.tab[j1].x + CONT.tab[j2].x);
        B2.C1.y = a * Sy + b * (CONT.tab[j1].y + CONT.tab[j2].y);
    }
    return B2;
}

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, int d){
    int n= j2-j1;
    
    Bezier2 B2 = approx_bezier2(CONT,j1,j2);

	double dmax=0;
	int k=j1;
	for (int j=j1+1;j<=j2;j++){
        int i= j-j1;
        double ti =(double)(i)/(double)n;
        double dj=dist_point_bezier2(CONT.tab[j], B2, ti);
		if (dmax<dj){
			dmax=dj;

			k=j;
		}
	}

	Liste_Point L=creer_liste_Point_vide();
	Liste_Point L1=creer_liste_Point_vide();
	Liste_Point L2=creer_liste_Point_vide();
	if (dmax<=d){
		L=ajouter_element_liste_Point(L, B2.C0);
        L=ajouter_element_liste_Point(L, B2.C1);
        L=ajouter_element_liste_Point(L, B2.C2);
	}
	else {
		L1=simplification_douglas_peucker_bezier2(CONT, j1, k, d);
		L2=simplification_douglas_peucker_bezier2(CONT, k, j2, d);
		L=concatener_liste_Point(L1,L2);
	}
	return L;
}

Bezier3 approx_bezier3 (Tableau_Point CONT,int j1,int j2){
    Bezier3 B3;
    int n =j2-j1;
    if(n==1 || n==2){ 
        Bezier2 B2=approx_bezier2(CONT,j1,j2);
        B3 =Bezier2_en_Bezier3(B2);
    }
    else { // contour plus de trois point
        Point C0=CONT.tab[j1];
        Point C3=CONT.tab[j2];
        // Calcul des coefs
        double a=((-15)*pow((double) n,3)+5*pow((double) n,2)+2*n+4)/(3*((double) n+2)*(3*pow((double) n,2)+1));
        double b=(10*pow((double) n,3)-(15*pow((double) n,2))+(double) n+2)/(3*((double) n+2)*(3*pow((double) n,2)+1));
        double l=(70*(double) n)/(3*(pow((double) n,2)-1)*(pow((double) n,2)-4)*(3*pow((double) n,2)+1));
        Point C1;
        double sa=0;
        double so=0;
        for(int i=1;i<n;i++){
            double d_i= (double) i ;
            sa+=(6*pow(d_i,4)-8*(double) n*pow(d_i,3)+6*pow(d_i,2)-4*(double) n*d_i+pow((double) n,4)-pow((double) n,2))*CONT.tab[j1+i].x;
            so+=(6*pow(d_i,4)-8*(double) n*pow(d_i,3)+6*pow(d_i,2)-4*(double) n*d_i+pow((double) n,4)-pow((double) n,2))*CONT.tab[j1+i].y;
        }
        C1.x=a*C0.x+l*sa+b*C3.x;
        C1.y=a*C0.y+l*so+b*C3.y;
        Point C2;
        sa=0;
        so=0;
        for(int i=1;i<n;i++){
            double d_i= (double) i ;
            sa+=(6*pow((double) n-d_i,4)-8*(double) n*pow((double) n-d_i,3)+6*pow((double) n-d_i,2)-4*(double) n*((double) n-d_i)+pow((double) n,4)-pow((double) n,2))*CONT.tab[j1+i].x;
            so+=(6*pow((double) n-d_i,4)-8*(double) n*pow((double) n-d_i,3)+6*pow((double) n-d_i,2)-4*(double) n*((double) n-d_i)+pow((double) n,4)-pow((double) n,2))*CONT.tab[j1+i].y;
        }
        C2.x=b*C0.x+l*sa+a*C3.x;
        C2.y=b*C0.y+l*so+a*C3.y;
        B3=creation_Bezier3(C0,C1,C2,C3);
    }
    return B3;
}

Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point CONT,int j1,int j2,int d){

    Liste_Point L =creer_liste_Point_vide(); 
    int n =j2-j1; 
    
    Bezier3 B3 =approx_bezier3(CONT,j1,j2); 

    double dmax=0;
    int k = j1;
    for(int j=j1+1;j<=j2;j++){
        int i = j-j1;
        double ti=(double)i/(double)n;
        double dj=dist_point_bezier3(CONT.tab[j1+i],B3,ti);
        if(dmax <dj) {
            dmax=dj;
            k=j;
        }
    }if(dmax <=d){
        L=ajouter_element_liste_Point(L, B3.C0);
        L=ajouter_element_liste_Point(L, B3.C1);
        L=ajouter_element_liste_Point(L, B3.C2);
        L=ajouter_element_liste_Point(L, B3.C3);
    }else{
     
        Liste_Point L1=simplification_douglas_peucker_bezier3(CONT, j1, k, d);
        Liste_Point L2=simplification_douglas_peucker_bezier3(CONT, k, j2, d);
        L=concatener_liste_Point(L1,L2);
    }
    return L;
}




