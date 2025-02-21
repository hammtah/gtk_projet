//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_COMBOBOX_H
#define TEST1_COMBOBOX_H
#include "global.h"



typedef struct {
    GtkWidget *comboBox;           // Widget de combobox GTK+
    dimension dim;                 // Dimensions de la comboBox
    coordonnees cord;              // Coordonnées de la comboBox
    gchar nom_class[30];           // Classe de la comboBox
    GtkWidget *conteneur;          // Conteneur générique auquel la combobox est attachée
} gtkComboBox;


//---------> fonction d'initialisation d'un combo box
/*************************************************************
Nom          : init_comboBox()
Entrée       : Une structure dimension && Une structure coordonnees
               Une chaîne de caractères && Un pointeur vers le widget GTK+ du conteneur fixed
Sortie       : renvoie un pointeur vers une structure gtkComboBox
Description  : Est utilisée pour initialiser une structure gtkComboBox
*************************************************************/
gtkComboBox* init_comboBox(dimension dim, coordonnees cord, gchar nom_class[30], GtkWidget *conteneur) {
    // Allocation de mémoire pour une nouvelle instance de gtkComboBox
    gtkComboBox *myCombo = (gtkComboBox *)malloc(sizeof(gtkComboBox));
    if (!myCombo) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Initialisation des champs de la structure gtkComboBox
    myCombo->dim.height = dim.height;
    myCombo->dim.width = dim.width;
    myCombo->cord.x = cord.x;
    myCombo->cord.y = cord.y;
    strcpy(myCombo->nom_class, nom_class);
    myCombo->conteneur = conteneur; // Conteneur générique

    return myCombo;
}


//--------> fonction de creation d'un combo box
/*************************************************************
Nom          : create_ComboBox()
Entrée       : Un pointeur vers une structure gtkComboBox
Sortie       : -
Description  : Elle prend en entrée un pointeur vers une structure gtkComboBox contenant
les informations nécessaires pour créer et configurer la combobox.
*************************************************************/
void create_ComboBox(gtkComboBox *myCombo) {
    // Création de la nouvelle combobox
    myCombo->comboBox = gtk_combo_box_text_new();

    // Attribution d'une classe à la combobox
    gtk_widget_set_name(myCombo->comboBox, myCombo->nom_class);

    // Ajustement de la taille de la combobox
    gtk_widget_set_size_request(myCombo->comboBox, myCombo->dim.width, myCombo->dim.height);

    // Ajouter la combobox au conteneur
    if (GTK_IS_FIXED(myCombo->conteneur)) {
        gtk_fixed_put(GTK_FIXED(myCombo->conteneur), myCombo->comboBox, myCombo->cord.x, myCombo->cord.y);
    } else {
        gtk_container_add(GTK_CONTAINER(myCombo->conteneur), myCombo->comboBox);
    }
}
//Fin fonction create_ComboBox()

//--------> fonction pour ajouter des elements à comboBox
/*************************************************************
Nom          : ajouterElementComboBox()
Entrée       : myCombo - Un pointeur vers une structure gtkComboBox
              id - Identifiant de l'élément à ajouter à la combobox (chaîne de caractères)
              text - Texte de l'élément à ajouter à la combobox (chaîne de caractères)
Sortie       : -
Description  : Ajoute un élément à la combobox spécifiée
*************************************************************/
void ajouterElementComboBox(gtkComboBox *myCombo,char id[50],char text[50])
{
    // Ajout de l'élément à la combobox en utilisant l'identifiant et le texte fournis
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(myCombo->comboBox),id, text);
}//Fin fonction ajouterElementComboBox()


//--------> definir l'element active dans le ComboBox
/*************************************************************
Nom          : elementActive()
Entrée       : myCombo - Un pointeur vers une structure gtkComboBox
               index - L'indice de l'élément à rendre actif dans la combobox
Sortie       : -
Description  : Rend l'élément à l'indice spécifié actif dans la combobox.
*************************************************************/
void elementActive(gtkComboBox *myCombo, gint index)
{
    // Assurez-vous que 'myCombo->comboBox' est bien un GtkComboBox avant de passer à la fonction
    if (GTK_IS_COMBO_BOX(myCombo->comboBox)) {
        // Rend l'élément à l'indice spécifié actif dans la combobox
        gtk_combo_box_set_active(GTK_COMBO_BOX(myCombo->comboBox), index);
    } else {
        fprintf(stderr, "Erreur : Ce widget n'est pas un GtkComboBox\n");
    }
}
























#endif //TEST1_COMBOBOX_H
