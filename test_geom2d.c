#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geom2d.h"

int main(){
    double x1,y1,x2,y2,a,s,e,d;
    Point P1,P2,P3,P4;
    Vecteur V1,V2,V3,V4;
    printf("entrer les coordonnées x1, y1, x2, y2  et le réel a :\n");
    printf("x1 : ");
    if (scanf("%lf",&x1)!=1){
        printf("Erreur : problème de lecture de la coordonnées x1\n");
        return -1;
    }
    printf("y1 : ");
    if (scanf("%lf",&y1)!=1){
        printf("Erreur : problème de lecture de la coordonnées y1\n");
        return -1;
    }
    printf("x2 : ");
    if(scanf("%lf",&x2)!=1){
        printf("Erreur : problème de lecture de la coordonnées x2\n");
        return -1;
    }
    printf("y2 : ");
    if (scanf("%lf",&y2)!=1){
        printf("Erreur : problème de lecture de la coordonnées y2\n");
        return -1;
    }
    printf("a : ");
    if (scanf("%lf",&a)!=1){
        printf("Erreur : problème de lecture du réel a\n");
        return -1;
    }

    /* Premier point former a partir des deux premières coordonnées */
    P1 = set_point(x1,y1);
    printf("Point P1 créé avec x1 et y1 : (%lf, %lf)\n", P1.x, P1.y);
    /* Deuxième point former a partir des deux coordonnées suivantes */
    P2 = set_point(x2,y2);
    printf("Point P2 créé avec x2 et y2 : (%lf, %lf)\n", P2.x, P2.y);
    /* Troisième Point former a partir de l'addition des deux Points P1 et P2 */
    P3 = add_point(P1,P2); 
    printf("Point P3 (P1 + P2) : (%lf, %lf)\n", P3.x, P3.y);
    /* Premier Vecteur bi-point former a partir des deux Points P1 et P2 */
    V1 = vect_bipoint(P1,P2);
    printf("Vecteur V1 (P1 , P2) : (%lf, %lf)\n", V1.x, V1.y);
    /* Deuxième Vecteur bi-point former a partir des deux Points P1 et P3 */
    V2 = vect_bipoint(P1,P3);
    printf("Vecteur V2 (P1 , P3) : (%lf, %lf)\n", V2.x, V2.y);
    /* Toisième Vecteur former a partir de l'addition des Points P1 et P2 */
    V3 = add_vect(V1,V2);
    printf("Vecteur V3 (V1 + V2) : (%lf, %lf)\n", V3.x, V3.y);
    /* Quatrième Point former a partir de la multiplication du Points P1 et du réel a */
    P4 = mult_point(P1,a);
    printf("Point P4 (P1 * %lf) : (%lf, %lf)\n", a, P4.x, P4.y);
    /* Quatrième Vecteur former a partir de la multiplication du Vecteur V1 et du réel a */
    V4 = mult_vect(V1,a);
    printf("Vecteur V4 (V1 * %lf) : (%lf, %lf)\n", a, V4.x, V4.y);
    /* Produit scalaire former a partir des Vecteurs V1 et V2 */
    s = scalar_prod(V1,V2);
    printf("Produit scalaire (V1 ⋅ V2) : %lf\n", s);
    /* Norme euclidienne (longueur) du Vecteur V1 */
    e = eucli_standard(V1);
    printf("Norme euclidienne de V1 : %lf\n", e);
    /* Distance entre les deux points P1 et P2 */
    d = dist(P1,P2);
    printf("Distance entre P1 et P2 : %lf\n", d);


    return 0;
}