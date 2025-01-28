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

Point avancer_inter(Robot r){
    switch (r.orientation){
        case Est:
            return set_point(r.position.x+1,r.position.y);
        case Ouest:
            return set_point(r.position.x-1,r.position.y);
        case Sud:
            return set_point(r.position.x,r.position.y+1);
        case Nord:
            return set_point(r.position.x,r.position.y-1);
    }
}

Robot avancer(Robot r){
    Robot r1=nouveauRobot();
    Point p=avancer_inter(r);
    r1.position=set_point(p.x,p.y); 
    r1.orientation=r.orientation;
    return r1;
}

Orientation tourner_90_degrees(Robot r){
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
    return r.orientation;
}

Orientation tourner_270_degrees(Robot r){
    r.orientation=tourner_90_degrees(r);
    r.orientation=tourner_90_degrees(r);
    r.orientation=tourner_90_degrees(r);
    return r.orientation;
}
Pixel valeur_pixel_gauche(Robot r, Image I){
    switch (r.orientation){
        case Est:
            return get_pixel_image(I,r.position.x+1,r.position.y);
        case Ouest:
            return get_pixel_image(I,r.position.x,r.position.y+1);
        case Nord:
            return get_pixel_image(I,r.position.x,r.position.y);
        case Sud:
            return get_pixel_image(I,r.position.x+1,r.position.y+1);
    }
}

Pixel valeur_pixel_droite(Robot r, Image I){
    switch (r.orientation){
        case Est:
            return get_pixel_image(I,r.position.x+1,r.position.y+1);
        case Ouest:
            return get_pixel_image(I,r.position.x,r.position.y);
        case Nord:
            return get_pixel_image(I,r.position.x+1,r.position.y);
        case Sud:
            return get_pixel_image(I,r.position.x,r.position.y+1);
    }
}

Orientation nouvelle_orientation(Robot r, Image I){
    Pixel Pg=valeur_pixel_gauche(r,I);
    Pixel Pd=valeur_pixel_droite(r,I);
    if (Pg==NOIR){
        r.orientation=tourner_90_degrees(r);
    }
    else if (Pd==BLANC){
        r.orientation=tourner_270_degrees(r);
    }
    return r.orientation;
}

Liste_Point memoriser_position(Point p, Liste_Point L){
    L=ajouter_element_liste_Point(L,p);
    return L;
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
    while(boucle==1){
        L=memoriser_position(r.position,L);
        segments++;
        r=avancer(r);
        r.orientation=nouvelle_orientation(r,I);
        if ((r.position.x==x0) && (r.position.y==y0) && (r.orientation==Est)){
            boucle=0;
        }
    }
    L=memoriser_position(r.position,L);
    ecrire_contour(L);
    segments++;
    printf("Ce contour est composé de %d segments\n", segments);
    return L;
}