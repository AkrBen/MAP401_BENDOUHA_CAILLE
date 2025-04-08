#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>

Bezier2 approx_bezier2(Tableau_Point L, int j1, int j2);

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, int d);
