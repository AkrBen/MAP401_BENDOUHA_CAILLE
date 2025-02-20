#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geom2d.h"

int main(){
    double x1,y1,x2,y2,x3,y3,d;
    Point P,A,B;

    printf("entrer les coordonnées P.x, P.y, A.x, A.y, B.x et B.y  Pour former les points P, A et B :\n");
    printf("P.x : ");
    if (scanf("%lf",&x1)!=1){
        printf("Erreur : problème de lecture de la coordonnées P.x\n");
        return -1;
    }
    printf("P.y : ");
    if (scanf("%lf",&y1)!=1){
        printf("Erreur : problème de lecture de la coordonnées P.y\n");
        return -1;
    }
    printf("A.x : ");
    if(scanf("%lf",&x2)!=1){
        printf("Erreur : problème de lecture de la coordonnées A.x\n");
        return -1;
    }
    printf("A.y : ");
    if (scanf("%lf",&y2)!=1){
        printf("Erreur : problème de lecture de la coordonnées A.y\n");
        return -1;
    }
    printf("B.x : ");
    if (scanf("%lf",&x3)!=1){
        printf("Erreur : problème de lecture de la coordonnées B.x\n");
        return -1;
    }

    printf("B.y : ");
    if (scanf("%lf",&y3)!=1){
        printf("Erreur : problème de lecture de la coordonnées B.y\n");
        return -1;
    }

    P = set_point(x1,y1);
    printf("Point P : (%lf, %lf)\n", P.x, P.y);
   
    A = set_point(x2,y2);
    printf("Point A : (%lf, %lf)\n", A.x, A.y);

    B = set_point(x3,y3);
    printf("Point B : (%lf, %lf)\n", B.x, B.y);

    d = dist_point_seg(P,A,B);

    printf("la distance entre le Point P et le segement [A,B] est : %lf\n ",d);
 


    return 0;
}