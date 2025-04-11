#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

int main(){
    //Liste_Point L=creer_liste_Point_vide();
    int x0;
    printf("Entrer valeur des abscisses de P0:\n");
    scanf("%d", &x0);

    int y0;
    printf("Entrer valeur des ordonnées de P0:\n");
    scanf("%d", &y0);

    int x1;
    printf("Entrer valeur des abscisses de P1:\n");
    scanf("%d", &x1);

    int y1;
    printf("Entrer valeur des ordonnées de P1:\n");
    scanf("%d", &y1);
    Point P0=set_point(x0,y0);
    Point P1=set_point(x1,y1);
    Tableau_Point T;
    T.taille=2;
    T.tab = malloc(sizeof(Point) * 10000);
    T.tab[0]=P0;
    T.tab[1]=P1;
    Bezier2 B=approx_bezier2(T,0,1);
    if ((dist(B.C0,P0)==0)&&(dist(B.C1,set_point((P0.x+P1.x)/2,(P0.y+P1.y)/2))==0)&&(dist(B.C2,P1)==0)){
        printf("Le test d'approx_bezier2 pour n=1 est validé\n");
    }
    else{
        printf("Le test d'approx_bezier2 pour n=1 n'est pas validé\n");
    }

    int n;
    do {
        printf("Entrer une valeur entière pour n (n >= 2) :\n");
        scanf("%d", &n);
    } while (n < 2);

    int x_0, y_0, x, y, x2, y2;

    printf("Entrer les coordonnées de Q0 (x0 y0) :\n");
    scanf("%d %d", &x_0, &y_0);

    printf("Entrer les coordonnées de Q (x y) :\n");
    scanf("%d %d", &x, &y);

    printf("Entrer les coordonnées de Q2 (x2 y2) :\n");
    scanf("%d %d", &x2, &y2);

    Point Q0 = set_point(x_0, y_0);
    Point Q = set_point(x, y);
    Point Q2 = set_point(x2, y2);

    Bezier2 B2=creation_Bezier2(Q0, Q, Q2);

    Tableau_Point T2;
    T2.taille = n+1;
    T2.tab = malloc(sizeof(Point) * 10000);
    for (int j=0; j<n+1; j++){
        T2.tab[j] = C_t_2(B2,(double)(j/n));
    }

    Bezier2 B3=approx_bezier2(T2,0,n);
    if ((B2.C0.x==B3.C0.x)&&(B2.C0.y==B3.C0.y)&&(B2.C1.x==B3.C1.x)&&(B2.C1.y==B3.C1.y)&&(B2.C2.x==B3.C2.x)&&(B2.C2.y==B3.C2.y)){
        printf("Le test d'approx_bezier2 pour n>1 est validé\n");
    }
    else{
        printf("Le test d'approx_bezier2 pour n>1 n'est pas validé\n");
    }

    return 0;
}