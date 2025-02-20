//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_INCLUDES_BUTTON_H
#define TEST1_INCLUDES_BUTTON_H
#include "global.h"

#define DETAILED_SIGNAL_LENGTH 20
#define MAX_LENGTH 100
#define MARKUP_LENGTH 50



/*************************MACORS***************************/
//Certains sont utils, permettant de réduire le nombre de paramétres en retirant ceux indésirable.
//Et certains sert juste à simplifier l'écriture et l'appel de certains fonctions.
#define dim(width,height) creer_dimension(height, width)
//#define pos(x,y) creer_position(x, y)
#define margin(top,right,bottom,left) creer_margin(top,right,bottom,left)
#define cord(x,y) create_coordonnees(x,y)
//Macro pour un spin qui comporte des entiers naturels, elle a comme borne sup: 100 et borne inf: -100
#define spinObj(start, step)  createSpinObj(start, -100, 100, step, 0)
//Les valeurs par défaults
#define DEFAULT_BTN_DIM dim(8, 8) //La dimension par défaut d'un bouton
#define DEFAULT_BTN_POS cord(0, 0) //La position par défaut d'un bouton
#define DEFAULT_BTN_MARGIN margin(0,0,0,0);//La margine par défaut d'un bouton
/*******IMAGE**********/
//Le macro dim(x,y) retourne un pointeur vers une dimension, cependant
// la fonction creer_image a besoin d'un passage par valeur, quant aux coordonnées ils ne sont
//pas nécessaires si on veut ajouter une image à un bouton (voir GTK_POS_TYPE)
#define btnImage(path, dim)  creer_image(init_image(path, *dim, *cord(0,0)));

//////////////////////////DIMENSION//////////////////////////////





/*
//////////////////////////POSITION//////////////////////////////
//La position d'un widget
typedef struct position{
    gint x;//Position dans l'axe des abscisses
    gint y;//position dans l'axe des ordonnées
}Position;


// fonction pour creer une dimmension

Position* creer_position(gint x , gint y)
{
    //Allocation de la structure position
    Position *pos=(Position *) malloc(sizeof (Position ));
    if(pos == NULL){
        g_print("\n Erreur d'allocation ");
        exit(EXIT_FAILURE);
    }
    //Assignation des cordonnés
    pos->x=x;
    pos->y=y;
    //Retourner la position
    return ((Position*)pos);
}

*/

////////////////////////MARGIN////////////////////////////////
//Structure representant la marge d'un button
typedef struct margin{
    gint mleft;//margin left
    gint mright;//margin right
    gint mtop;//margin top
    gint mbottom;//margin bottom
}Margin;

// fonction pour creer margine

Margin* creer_margin(gint mtop, gint mright,gint mbottom, gint mleft)
{
    //Allocation
    Margin *mar=(Margin *) malloc(sizeof (Margin ));
    //Si Erreur d'allocation alors sortir avec un code d'erreur
    if(mar == NULL){
        g_print("\n Erreur d'allocation ");
        exit(EXIT_FAILURE);
    }
    //Assignation
    mar->mleft=mleft;
    mar->mright=mright;
    mar->mtop=mtop;
    mar->mbottom=mbottom;
    //Retourner la marge
    return ((Margin*)mar);
}

//Structure définissant les paramètres d'un bouton de type SPIN
typedef struct spinObj{
    gdouble start;//Valeur de commencement
    gdouble borneInf;//La borne inférieur des valeurs possibles
    gdouble borneSup;//Valeur à ne pas dépasser
    gdouble step;//Le pas d'incrementation/décrementation
    guint digits;//Combien de nombres après virgules
}spinObj;

//Creation et initialisation et retourne d'un objet de type spinObj
spinObj* createSpinObj(gdouble start, gdouble borneInf, gdouble borneSup, gdouble step, guint digits)
{
    //Allocation
    spinObj *sp=(spinObj *) malloc(sizeof (spinObj ));
    //Si Erreur d'allocation alors sortir avec un code d'erreur
    if(sp == NULL){
        g_print("\n Erreur d'allocation de spinObj");
        exit(EXIT_FAILURE);
    }
    //Assignation
    sp->start= start;
    sp->borneInf= borneInf;
    sp->borneSup= borneSup;
    sp->step= step;
    sp->digits=digits;
    //Retourner le spinObjet
    return ((spinObj*)sp);
}


















#endif //TEST1_INCLUDES_BUTTON_H
