#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

#define EPSILON 1e-6

int points_egaux(Point A, Point B) {
    return (fabs(A.x - B.x) < EPSILON) && (fabs(A.y - B.y) < EPSILON);
}

int main(){
    Point P0,P1,P2,P3,P4,P5,P6,P7,P8;
    int x0, y0, x1, y1;
    printf("Entrer valeur des abscisses de P0:\n");
    scanf("%d", &x0);
    printf("Entrer valeur des ordonnées de P0:\n");
    scanf("%d", &y0);
    printf("Entrer valeur des abscisses de P1:\n");
    scanf("%d", &x1);
    printf("Entrer valeur des ordonnées de P1:\n");
    scanf("%d", &y1);

    P0 = set_point(x0, y0);
    P1 = set_point(x1, y1);

    Tableau_Point T;
    T.taille = 2;
    T.tab = malloc(sizeof(Point) * 10000);
    T.tab[0] = P0;
    T.tab[1] = P1;

    Bezier2 B = approx_bezier2(T, 0, 1);

    if (points_egaux(B.C0, P0) &&
        points_egaux(B.C1, set_point((P0.x + P1.x) / 2, (P0.y + P1.y) / 2)) &&
        points_egaux(B.C2, P1)) {
        printf("Le test d'approx_bezier2 pour n=1 est validé\n");
    } else {
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

    Bezier2 B2 = creation_Bezier2(Q0, Q, Q2);

    Tableau_Point T2;
    T2.taille = n + 1;
    T2.tab = malloc(sizeof(Point) * 10000);

    for (int j = 0; j <= n; j++) {
        double t = (double)j / (double)n;
        T2.tab[j] = C_t_2(B2, t);
    }

    Bezier2 B3 = approx_bezier2(T2, 0, n);

    if (points_egaux(B2.C0, B3.C0) && points_egaux(B2.C1, B3.C1) && points_egaux(B2.C2, B3.C2)) {
        printf("Le test d'approx_bezier2 pour n>1 est validé\n");
    } else {
        printf("Le test d'approx_bezier2 pour n>1 n'est pas validé\n");
    }

    printf("C0 : %f,%f = %f,%f\n", B2.C0.x, B2.C0.y, B3.C0.x, B3.C0.y);
    printf("C1 : %f,%f = %f,%f\n", B2.C1.x, B2.C1.y, B3.C1.x, B3.C1.y);
    printf("C2 : %f,%f = %f,%f\n", B2.C2.x, B2.C2.y, B3.C2.x, B3.C2.y);

    Tableau_Point T3;
    T3.taille = 9;
    T3.tab = malloc(sizeof(Point) * 10000);

    P0 = set_point(0, 0);
    P1 = set_point(1, 0);
    P2 = set_point(1, 1);
    P3 = set_point(1, 2);
    P4 = set_point(2, 2);
    P5 = set_point(3, 2);
    P6 = set_point(3, 3);
    P7 = set_point(4, 3);
    P8 = set_point(5, 3);

    T3.tab[0] = P0;
    T3.tab[1] = P1;
    T3.tab[2] = P2;
    T3.tab[3] = P3;
    T3.tab[4] = P4;
    T3.tab[5] = P5;
    T3.tab[6] = P6;
    T3.tab[7] = P7;
    T3.tab[8] = P8;

    Point PF = set_point(1.547619,2.452381);

    Bezier2 B4 = approx_bezier2(T3, 0, 8); 

    printf("Test 9 Points\n");
    printf("C0 : %f,%f\n",B4.C0.x, B4.C0.y);
    printf("C1 : %f,%f\n",B4.C1.x, B4.C1.y);
    printf("C2 : %f,%f\n",B4.C2.x, B4.C2.y);
    
    if (points_egaux(B4.C0,P0) && points_egaux(B4.C1, PF)&& points_egaux(B4.C2, P8)) {
        printf("Le Test des 9 points est validé\n");
    } else {
        printf("Le Test des 9 points n'est pas validé\n");
    }

    free(T.tab);
    free(T2.tab);
    free(T3.tab);

    return 0;
}
