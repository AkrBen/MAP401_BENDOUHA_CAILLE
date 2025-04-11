#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>

Bezier2 approx_bezier2(Tableau_Point CONT, int j1, int j2); //renvoie en fonction d'un tableau de points CONT et de deux indices j1 et j2, la courbe de Bézier 2 qui approxime le segment [j1,j2] du tableau CONT

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, int d); //renvoie la liste de points qui approxime le segment [j1,j2] du tableau CONT par une courbe de Bézier 2, en fonction d'un paramètre d de distance maximale entre le segment et la courbe de Bézier 2

Bezier3 approx_bezier3 (Tableau_Point CONT,int j1,int j2); //renvoie en fonction d'un tableau de points CONT et de deux indices j1 et j2, la courbe de Bézier 3 qui approxime le segment [j1,j2] du tableau CONT

Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point CONT,int j1,int j2, int d); //renvoie la liste de points qui approxime le segment [j1,j2] du tableau CONT par une courbe de Bézier 3, en fonction d'un paramètre d de distance maximale entre le segment et la courbe de Bézier 2