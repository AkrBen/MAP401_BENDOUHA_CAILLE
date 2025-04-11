#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

#define EPSILON 1e-6

int points_egaux(Point p1, Point p2) {
    return (fabs(p1.x - p2.x) < EPSILON && fabs(p1.y - p2.y) < EPSILON);
}

int main() {
    printf("------ Test approx_bezier3 ------\n");

    // Cas (a) : n = 1
    printf("Test pour n = 1\n");
    int xa, ya, xb, yb;
    printf("Entrer coordonnées de P0 (x y) : ");
    scanf("%d %d", &xa, &ya);
    printf("Entrer coordonnées de P1 (x y) : ");
    scanf("%d %d", &xb, &yb);

    Tableau_Point T1;
    T1.taille = 2;
    T1.tab = malloc(sizeof(Point) * 2);
    T1.tab[0] = set_point(xa, ya);
    T1.tab[1] = set_point(xb, yb);

    Bezier3 B1 = approx_bezier3(T1, 0, 1);

    Point e_C1 = set_point((2 * xa + xb) / 3.0, (2 * ya + yb) / 3.0);
    Point e_C2 = set_point((xa + 2 * xb) / 3.0, (ya + 2 * yb) / 3.0);

    if (points_egaux(B1.C0, T1.tab[0]) &&
        points_egaux(B1.C1, e_C1) &&
        points_egaux(B1.C2, e_C2) &&
        points_egaux(B1.C3, T1.tab[1])) {
        printf("Test n = 1 validé\n");
    } else {
        printf("Test n = 1 non validé\n");
    }

    // Cas (b) : n = 2
    printf("\nTest pour n = 2\n");
    int x0, y0, x1, y1, x2, y2;
    printf("Entrer coordonnées de P0 (x y) : ");
    scanf("%d %d", &x0, &y0);
    printf("Entrer coordonnées de P1 (x y) : ");
    scanf("%d %d", &x1, &y1);
    printf("Entrer coordonnées de P2 (x y) : ");
    scanf("%d %d", &x2, &y2);

    Tableau_Point T2;
    T2.taille = 3;
    T2.tab = malloc(sizeof(Point) * 3);
    T2.tab[0] = set_point(x0, y0);
    T2.tab[1] = set_point(x1, y1);
    T2.tab[2] = set_point(x2, y2);

    Bezier3 B2 = approx_bezier3(T2, 0, 2);
    Point C1_e = set_point((4.0 * x1 - x2) / 3.0, (4.0 * y1 - y2) / 3.0);
    Point C2_e = set_point((4.0 * x1 - x0) / 3.0, (4.0 * y1 - y0) / 3.0);

    if (points_egaux(B2.C0, T2.tab[0]) &&
        points_egaux(B2.C1, C1_e) &&
        points_egaux(B2.C2, C2_e) &&
        points_egaux(B2.C3, T2.tab[2])) {
        printf("Test n = 2 validé\n");
    } else {
        printf("Test n = 2 non validé\n");
    }

    // Cas (c) : n >= 3
    printf("\nTest pour n >= 3\n");
    int n;
    do {
        printf("Entrer une valeur entière pour n (n >= 3) : ");
        scanf("%d", &n);
    } while (n < 3);

    int q0x, q0y, q1x, q1y, q2x, q2y, q3x, q3y;
    printf("Entrer les coordonnées de Q0 (x y) : ");
    scanf("%d %d", &q0x, &q0y);
    printf("Entrer les coordonnées de Q1 (x y) : ");
    scanf("%d %d", &q1x, &q1y);
    printf("Entrer les coordonnées de Q2 (x y) : ");
    scanf("%d %d", &q2x, &q2y);
    printf("Entrer les coordonnées de Q3 (x y) : ");
    scanf("%d %d", &q3x, &q3y);

    Bezier3 Q = creation_Bezier3(set_point(q0x, q0y), set_point(q1x, q1y), set_point(q2x, q2y), set_point(q3x, q3y));

    Tableau_Point T3;
    T3.taille = n + 1;
    T3.tab = malloc(sizeof(Point) * (n + 1));
    for (int i = 0; i <= n; i++) {
        double t = (double)i / (double)n;
        T3.tab[i] = C_t_3(Q, t);
    }

    Bezier3 B3 = approx_bezier3(T3, 0, n);

    if (points_egaux(B3.C0, Q.C0) &&
        points_egaux(B3.C1, Q.C1) &&
        points_egaux(B3.C2, Q.C2) &&
        points_egaux(B3.C3, Q.C3)) {
        printf("Test n >= 3 validé\n");
    } else {
        printf("Test n >= 3 non validé\n");
    }

    Tableau_Point T4;
    T4.taille = 9;
    T4.tab = malloc(sizeof(Point) * 10000);

    Point P0 = set_point(0, 0);
    Point P1 = set_point(1, 0);
    Point P2 = set_point(1, 1);
    Point P3 = set_point(1, 2);
    Point P4 = set_point(2, 2);
    Point P5 = set_point(3, 2);
    Point P6 = set_point(3, 3);
    Point P7 = set_point(4, 3);
    Point P8 = set_point(5, 3);

    T4.tab[0] = P0;
    T4.tab[1] = P1;
    T4.tab[2] = P2;
    T4.tab[3] = P3;
    T4.tab[4] = P4;
    T4.tab[5] = P5;
    T4.tab[6] = P6;
    T4.tab[7] = P7;
    T4.tab[8] = P8;

    
    Point PF2 = set_point(1.737287,0.929380);
    Point PF3 = set_point(1.844176,3.489158);
    

    Bezier3 B4 = approx_bezier3(T4, 0, 8); 

    printf("Test 9 Points\n");
    printf("C0 : %f,%f\n",B4.C0.x, B4.C0.y);
    printf("C1 : %f,%f\n",B4.C1.x, B4.C1.y);
    printf("C2 : %f,%f\n",B4.C2.x, B4.C2.y);
    printf("C2 : %f,%f\n",B4.C3.x, B4.C3.y);
    
    if (points_egaux(B4.C0,P0) && points_egaux(B4.C1, PF2)&&points_egaux(B4.C2, PF3)&& points_egaux(B4.C3, P8)) {
        printf("Le Test des 9 points est validé\n");
    } else {
        printf("Le Test des 9 points n'est pas validé\n");
    }


    // Libération mémoire
    free(T1.tab);
    free(T2.tab);
    free(T3.tab);
    free(T4.tab);

    return 0;
}
