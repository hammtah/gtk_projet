//
// Created by Dell on 1/30/2025.
//

#ifndef XML_TAHA_CHECKBOX_XML_H
#define XML_TAHA_CHECKBOX_XML_H

#include <gtk/gtk.h>
#include "includes_button.h"
#include "button.h"
#include "xml_utility.h"

#define MAX 40

/*
Retourner un checkbox initialiser
Entrés: FILE *file: fichier à lire
       char mot[MAX]: la propriété
       int parent: le conteneur du bouton(0: window, 2: fixed...)
Description: récupére le contenu des propriétés du bouton et crée une structure btn initialisé
*/
btn* init_checkbox_xml(FILE *file, int parent){

    //Variables pour initier le bouton
    char color1[MAX], color2[MAX],boxEmplacement;
    gchar *expand_gchar,*fill_gchar;
    gint type_bg = -1; // 0:pour simple background ; 1:pour simple background modern;
    int test, hasMnemonic;
    char x[10], y[10];
    char width[MAX], height[MAX];
    gchar *bgColor_gchar, *icon_gchar;
    char title[MAX], icon[MAX];
    icon[0] = '\0';
    char car;
    int isChecked = 0;
    //Lire tout les properties
    while ((test = balise(file)) == 22) {//Tant que la balise à lire est un <property>
        char mot[MAX], taille[MAX];
        int ind = 0;
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);//Sauter le: name="
        fscanf(file, "%s", mot);//Lire le type de la propriété(text,icon,x,y...)
        // Récupération du titre du bouton
        if (!(strcmp("text\"", mot))) {
            lire_gchar_str_with_deplacement(file, title, 10);
        }
            // Récupération de l'icône du bouton
        else if (!(strcmp("icon\"", mot))) {
            lire_gchar_str_with_deplacement(file, icon, 10);
        } else if (!(strcmp("mnemonic\"", mot))) {
            hasMnemonic = char_TO_int(lire_gchar(file));
            if(hasMnemonic){
                //Ajouter le underscore ('_') au title
                char tt[MAX]; tt[0] = '_'; tt[1] = '\0';
                strcat(tt, title);
                strcpy(title, tt);
            }
        }
            // Récupération de la position x du bouton
        else if (!(strcmp("x\"", mot))) {
            lire_gchar_str_with_deplacement(file, x, 10);
        }
            // Récupération de la position y du bouton
        else if (!(strcmp("y\"", mot))) {
            lire_gchar_str_with_deplacement(file, y, 10);
        }
        else if (!(strcmp("checked\"", mot))) {
            isChecked = char_TO_int(lire_gchar(file));
        }
        //Si on veut ajuster l'emplacement du bouton dans le box
        /*
        else if (!(strcmp("boxEmplacement\"", mot))) {
            Epeurerblanc(file);
            boxEmplacement=lire_gchar(file);
        }
         */
        /*
        else if (!(strcmp("expand\"", mot))) {
            char expand[MAX];
            Epeurerblanc(file);
            fseek(file, 1, SEEK_CUR);
            while (((car = fgetc(file)) != EOF) && (car != '<')) {
                expand[ind++] = car; // Lire le mot
            }
            expand[ind] = '\0';
            printf("%s\n", expand);
            fseek(file, 10, SEEK_CUR);
            expand_gchar = g_strdup(expand);
        }
         */
        /*
        else if (!(strcmp("fill\"", mot))) {
            char fill[MAX];
            Epeurerblanc(file);
            fseek(file, 1, SEEK_CUR);
            while (((car = fgetc(file)) != EOF) && (car != '<')) {
                fill[ind++] = car; // Lire le mot
            }
            fill[ind] = '\0';
            printf("%s\n", fill);
            fseek(file, 10, SEEK_CUR);
            fill_gchar= g_strdup(fill);
        }
         */
    }//fin de while()
    //Creer l'image du bouton
    MonImage* ima = NULL;//Initier l'image avec NULL
    //Creer l'image si le path est saisie
    if(strlen(icon) > 0){
        ima = init_image(icon,*dim(24,24), *cord(0,0));
    }

    btn* mybtn = NULL;
    //Si le parent est fixed
    if(parent == 2){
        /*mybtn = btnCheckFixed(title, title, title, cord(atoi(x), atoi(y)),
                              parents[parent],FALSE,NULL
        );*/
        mybtn = btnCheckFixed(title, title, title, cord(atoi(x), atoi(y)), parents[parent], isChecked, ima);
    }
        //Si le parent n'est pas fixed
    else{
        mybtn = btnCheck(title, title, title, margin(0,0,0,0),
                              parents[parent],isChecked,ima
        );
    }
    return (btn*) mybtn;
}

//fct de creation de button a partir xml
void checkbox_xml(FILE *file, int parent) {
    btn* bb = NULL;
    // Si la balise est un <property>
    //creer_button(init_checkbox_xml(file, parent));
    bb = init_checkbox_xml(file, parent);
    //Si la balise est un <checkbox-style>
    /*
    else if (test == 25) {
        if (!(strcmp("color\"", mot))) {
            char color[MAX];
            lire_gchar_str_with_deplacement(file, color, 13);
            // Affecter la couleur lue
            strcpy(buttonStyle->color.hexa_color, color);
        }
        else if (!(strcmp("police\"", mot))) {
            char police[MAX];
            lire_gchar_str_with_deplacement(file, police, 13);
            strcpy(buttonStyle->police, police);
        }
        else if (!(strcmp("taille\"", mot))) {
            lire_gchar_str_with_deplacement(file, taille, 13);
            // Convertir en entier
            buttonStyle->taille = atoi(taille);
        }
        else if (!(strcmp("gras\"", mot))) {
            char gras;
            Epeurerblanc(file);
            fseek(file, 1, SEEK_CUR);
            while (((car = fgetc(file)) != EOF) && (car != '<')) {
                gras = car; // Lire le mot
            }
            printf("%c\n", gras);
            fseek(file, 13, SEEK_CUR);
            // Convertir en entier
            buttonStyle->gras = char_TO_int(gras);
        }
        else if (!(strcmp("bgcolor\"", mot))) {
            type_bg = 0;
            char bgcolor[MAX];
            lire_gchar_str_with_deplacement(file, bgcolor, 13);
            strcpy(maButton->back_ground.hexa_color, bgcolor);
        }
        else if (!(strcmp("modern_bgcolor\"", mot))) {
            type_bg = 1;
            Epeurerblanc(file);
            fseek(file, 1, SEEK_CUR);
            while (((car = fgetc(file)) != EOF) && (car != '<') && (car != ',')) {
                color1[ind++] = car; // Lire le mot
            }
            color1[ind] = '\0';
            ind = 0;
            while (((car = fgetc(file)) != EOF) && (car != '<')) {
                color2[ind++] = car; // Lire le mot
            }
            color2[ind] = '\0';
            fseek(file, 13, SEEK_CUR);
        }
    }
    */
    //}
    // Si test n'égal pas property (22), ignorer la balise fermante de button

    // Appliquer le style au bouton
    // Création du bouton
    /*
    maButton = creer_button_normale(maButton);
    gtk_widget_set_name(maButton->Button, "mon-bouton");
    if (type_bg == 0) {
        if (!load_css("style.css", maButton->Button,
                      maButton->back_ground.hexa_color))
        {
            g_print("error de mis en forme de l'arriere plan");
        }
    }
    else if (type_bg == 1) {
        if (!load_css_modern("style.css", maButton->Button,
                             color1, color2))
        {
            g_print("error de mis en forme de l'arriere plan");
        }
    }
    appliquer_style_button(buttonStyle, maButton->Button);
    */
    //Creer le bouton
    creer_button(bb);
    // Appel récursif pour traiter les autres balises
    creer_object(file, parent);
}


#endif //XML_TAHA_CHECKBOX_XML_H
