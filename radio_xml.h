//
// Created by Dell on 2/3/2025.
//

#ifndef XML_TAHA_RADIO_XML_H
#define XML_TAHA_RADIO_XML_H
#include <gtk/gtk.h>
#include "button.h"
#include "xml_utility.h"

#define MAX 40
//fct de cration de radio
//Initie un bouton radio à travers un groupe et une balise
//Prend un pointeur vers un style, le style est lue à travers les balises property, puis retourner à travers ce pointeur
//Retourne le bouton initialisé
btn* radio_xml(FILE *file, GtkWidget* groupe, Style** st) {
    char text[MAX], width[MAX], height[MAX], checked[MAX], mnemonic[MAX], x[MAX], y[MAX];
    //Propriétés initialisé par des chaines vides
    char title[MAX], icon[MAX], bgcolor[MAX]={0}, taille[MAX], border[MAX],
            color[MAX]={0}, police[MAX]={0}, gras[MAX],border_radius[MAX];
    char text_[MAX] = "_";//Le label avec une mnemonic

    //Les propriété qu'on doit récuperer en tant qu'entiers:
    int itaille = -1, iborder = -1, igras = -1, iborder_radius = -1;//initialiser par -1
    gint type_bg = -1; // 0:pour simple background ; 1:pour simple background modern;
    int test = balise(file);//
    printf("\n!Je suis dans un radio!\n");

    //Tant que la balise lise est un <property>
    do{
        char mot[MAX];
        int ind = 0;
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", mot);
        // Si on trouve la balise <property>
        if (test == 22)
        {
            // Récupération du texte
            if (!(strcmp("text\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,text,10);
            }
                // Récupération du mnémonique
            else if (!(strcmp("mnemonic\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,mnemonic,10);
                //S'il a une mnemonic alors introduire le "_" au label
                if(atoi(mnemonic))
                    strcat(text_, text);
                //Sinon le label sera sans underscore
                else
                    strcpy(text_, text);
            }

                // Récupération de x
                /*
            else if (!(strcmp("x\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,x,10);
            }
                // Récupération de y
            else if (!(strcmp("y\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,y,10);
            }

                // Récupération de width
            else if (!(strcmp("width\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,width,10);
            }
                // Récupération de height
            else if (!(strcmp("height\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,height,10);
            }
                 */
                // Récupération de la case cochée
            else if (!(strcmp("checked\"", mot))) {
                lire_gchar_str_with_deplacement(file,checked,10);
            }
        }
        /*
        else if (test == 29) {
            // Récupération de la couleur, de la police, de la taille et du gras
            if (!(strcmp("color\"", mot))) {
                char color[MAX];
                lire_gchar_str_with_deplacement(file, color, 12);
                // Affecter la couleur lue
                strcpy(radioStyle->color.hexa_color, color);
            } else if (!(strcmp("police\"", mot))) {
                char  police[MAX];
                lire_gchar_str_with_deplacement(file, police, 12);
                strcpy(radioStyle->police, police);
            } else if (!(strcmp("taille\"", mot))) {
                lire_gchar_str_with_deplacement(file, taille, 12);
                // Convertir en entier
                radioStyle->taille = atoi(taille);
            } else if (!(strcmp("gras\"", mot))) {
                char gras;
                Epeurerblanc(file);
                fseek(file, 1, SEEK_CUR);
                while (((car = fgetc(file)) != EOF) && (car != '<')) {
                    gras = car; // Lire le mot
                }
                printf("%c\n", gras);
                fseek(file, 12, SEEK_CUR);
                // Convertir en entier
                radioStyle->gras = char_TO_int(gras);
            }
        }
        */

        //Properties de style
        if (!(strcmp("color\"", mot))) {
            lire_gchar_str_with_deplacement(file, color, 10);
        }
        else if (!(strcmp("police\"", mot))) {
            lire_gchar_str_with_deplacement(file, police, 10);
        }
        else if (!(strcmp("taille\"", mot))) {
            lire_gchar_str_with_deplacement(file, taille, 10);
            itaille = atoi(taille);
        }
        else if (!(strcmp("gras\"", mot))) {
            lire_gchar_str_with_deplacement(file, gras, 10);
            igras = atoi(gras);

        }
        else if (!(strcmp("bgcolor\"", mot))) {
            type_bg = 0;
            lire_gchar_str_with_deplacement(file, bgcolor, 10);
        }
        else if (!(strcmp("border\"", mot))) {
            lire_gchar_str_with_deplacement(file, border, 10);
            iborder = atoi(border);
        }
        else if (!(strcmp("border_radius\"", mot))) {
            lire_gchar_str_with_deplacement(file, border_radius, 10);
            iborder_radius = atoi(border_radius);
        }

        test = balise(file);
    }while (test == 22);

    //Creer le style
    HexColor* h = NULL;//Initier La couleur
    //Creer la couleur si la balise contient la property color
    if(color[0] != '\0')
        h = hex_color_init(color);

    //Creer le style à appliquer au bouton
    *st = init_style(police, h, itaille, igras, bgcolor, iborder, iborder_radius);
    // Création du boutton
    /*
    radiobtn = creer_button_radio(radiobtn);
    appliquer_style_button(radioStyle, radiobtn->Button);
    gtk_fixed_put(GTK_FIXED(parents[parent]), radiobtn->Button,
                  radiobtn->cord.xw, radiobtn->cord.yh);
    */
    printf("\n!Voici mes info: text: %s, mnemonic: %s, checked: %s!\n", text, mnemonic, checked);

    //Creer l'objet btn
    btn* bra = btnRadio(text, text_, text, NULL, margin(0, 0, 0, 0),
                    groupe, NULL);
    //Retourner le bouton
    return (btn*)bra;
}

//fct pour creer une liste de radios
//Parcours les balises et crée les boutons radio en utilisant radio_xml()
void radioList_xml(FILE *file, int  parent) {
    /*
    group_radio_liste = (Liste *) malloc(sizeof(Liste));
    if (group_radio_liste == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour Liste\n");
    }
    group_radio_liste->group = NULL;
    int indice=balise(file);
    Bi cord;
    int test, width_int, height_int;
    char x[10], y[10];
    char car;
    gchar *title_gchar, *bgColor_gchar, *icon_gchar;
    Mybox *Box = (Mybox *) malloc(sizeof(Mybox));
    //hexa_color *myColor2 = init_hexa_color(NULL, "white");


    hexa_color *myColor2 = init_hexa_color(NULL, "white");
    dimension *dim2 = malloc(sizeof(Bi));
    dim2->height = 50;
    dim2->width = 60;
    Mybox *box = init_box("monBox", 'v', 10, *dim2, 3, 2, myColor2, 1);
    creer_box(box);
    //pour parcourir la liste des radio
*/

    //Creer le box
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    //Initialiser le pere des boutons ainsi que le(s) bouton fils
    btn* pere = NULL, * fils = NULL;
    int ind = 0;
    Epeurerblanc(file);//Supprimer les white spaces
    char car, strx[MAX], stry[MAX];
    //Positionner la liste

    //Récuperer le cordonné 'x'
    char x = fgetc(file);
    // Récupération de la position x du box des radios
    if (x == 'x') {
            fseek(file, 1, SEEK_CUR);//Sauter le ' = '
            //Récuperer la valeur de x
            while (((car = fgetc(file)) != EOF) && (car != 'y')) {
                strx[ind++] = car; // Lire le caractère
            }
            strx[ind] = '\0'; // Terminer la chaîne
            // Récupération la valeur de y
            ind = 0;
            fseek(file, 1, SEEK_CUR);//Sauter le ' = '
            while (((car = fgetc(file)) != EOF) && (car != '>')) {
                stry[ind++] = car; // Lire le caractère
            }
            stry[ind] = '\0'; // Terminer la chaîne
    }

    //Creer le pere (le 1er bouton radio)
    if(balise(file) == 4){
        Style* st ;
        pere = radio_xml(file, NULL, &st);//Récuperer le 1er bouton radio (il n'a pas de groupe)
        creer_button(pere);//Creer le pere
        //appliquer le style au bouton radio
        appliquer_style_button(st, pere);
        //Ajouter au box
        gtk_box_pack_start(GTK_BOX(hbox), pere->button, TRUE, TRUE, 0);
    }
    //Creer les autres radios
    while (balise(file) == 4) {
        Style* st ;
        fils = radio_xml(file, pere->button, &st);
        creer_button(fils);
        //appliquer le style au bouton radio
        appliquer_style_button(st, fils);
        //Ajouter le bouton au box
        gtk_box_pack_start(GTK_BOX(hbox), fils->button, TRUE, TRUE, 0);

        /*Bi cord;
        int test, width_int, height_int;
        char x[10], y[10];
        char car;
        gchar *title_gchar, *bgColor_gchar, *icon_gchar;
        hexa_color *textColor;
        Style *radioStyle = NULL;
        radioStyle = (Style *) malloc(sizeof(Style));
        Radio_Button *radiobtn1 = NULL;
        radiobtn1 = (Radio_Button *) malloc(sizeof(Radio_Button));
        if (!radiobtn1) exit(-1);
         */
/*
        // Création du boutton
        radiobtn1->group= (Liste *)group_radio_liste->group;
        radiobtn1 = creer_button_radio(radiobtn1);
        appliquer_style_button(radioStyle, radiobtn1->Button);
        box->box = ajouter_bouton_radio(box->box, radiobtn1->Button, group_radio_liste);
*/

    }

    //Ajouter le box au fixed
    gtk_fixed_put(GTK_FIXED(parents[2]), hbox,
                  atoi(strx), atoi(stry));

    creer_object(file, parent);
    //creer_object(file, parent);

}
#endif //XML_TAHA_RADIO_XML_H
