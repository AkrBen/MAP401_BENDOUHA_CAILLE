#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"

Robot nouveauRobot(){
    Robot r;
    r.orientation=Est;
    r.position=set_point(0,0);
    return r;
}

void avancer(Robot r){
    switch (r.orientation){
        case Est:
            r.position.x++;
            break;
        case Ouest:
            r.position.x--;
            break;
        case Sud:
            r.position.y++;
            break;
        case Nord:
            r.position.y--;
            break;
    }
}

void tourner_90_degrees(Robot r){
    switch (r.orientation){
        case Est:
            r.orientation=Nord;
            break;
        case Ouest:
            r.orientation=Sud;
            break;
        case Sud:
            r.orientation=Est;
            break;
        case Nord:
            r.orientation=Ouest;
            break;
    }
}

void tourner_270_degrees(Robot r){
    tourner_90_degrees(r);
    tourner_90_degrees(r);
    tourner_90_degrees(r);
}

void nouvelle_orientation(Robot r, Image I){
    Pixel Pg=get_pixel_image(I,r.position.x-1,r.position.y-1);
    Pixel Pd=get_pixel_image(I,r.position.x,r.position.y-1);
    if (Pg==NOIR){
        tourner_90_degrees(r);
    }
    else if (Pd==BLANC){
        tourner_270_degrees(r);
    }
}

void memoriser_position(Point p, Liste_Point L){
    L=ajouter_element_liste_Point(L,p);
    ecrire_contour(L);
}

Contour calcul_ecriture_contour(Image I){
    int segments=-1;
    int x0=0;
    int y0=0;
    Liste_Point L=creer_liste_Point_vide();
    Robot r=nouveauRobot();
    int l=largeur_image(I);
    int h=hauteur_image(I);
    for (int i=0;i<l;i++){
        for (int j=0;j<h;j++){
            if ((get_pixel_image(I,i,j)==NOIR)&&(get_pixel_image(I,i,j-1)==BLANC)){
                x0=i-1;
                y0=j-1;
                r.position=set_point(x0,y0);
                j=h;
                i=l;
            }
        }
    }
    int boucle=1;
    while(boucle){
        memoriser_position(r.position,L);
        segments++;
        avancer(r);
        nouvelle_orientation(r,I);
        if ((r.position.x==x0) && (r.position.y==y0) && (r.orientation==Est)){
            boucle=0;
        }
    }
    memoriser_position(r.position,L);
    segments++;
    printf("Ce contour est composé de %d segments\n", segments);
    return L;
}