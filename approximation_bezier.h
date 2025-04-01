#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>
#include<exemple_sequence_point.h>

Bezier2 approx_bezier2(Contour L, int j1, int j2);

Liste_Point simplification_douglas_peucker_bezier2(Contour CONT, int j1, int j2, int d);