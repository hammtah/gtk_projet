//
// Created by Dell on 2/21/2025.
//

#ifndef XML_TAHA_PROJET_UTILITY_H
#define XML_TAHA_PROJET_UTILITY_H

#include <gtk/gtk.h>
#include "global.h"

/**
 * @brief Callback, verifiant si le charactere saisie dans le entry est un digit, sinon il le supprime
 * @param widget Le entry
 * @param data rien pour le moment
 * */
void inputHandler(GtkWidget* widget, gpointer* data){
    //Get buffer
    GtkEntryBuffer* buffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    //Get input texte
    gchar* texte = gtk_entry_get_text(GTK_ENTRY(widget));
    //Get the length of the input
    int len = gtk_entry_get_text_length(GTK_ENTRY(widget));
    //Verify it's a digit
    if(texte[len-1] < '0' || texte[len-1] > '9') {
        //Delete the char if it's not a number
        gtk_entry_buffer_delete_text(buffer, len - 1, 1);
        gtk_entry_set_buffer(GTK_ENTRY(widget), buffer);//Make the update

    }

}

/**
 * @brief Creer un choix, contenant un input(entry) et un label
 * @param label Le label à donnée au choix (exemple: color, texte...)
 * @param cord Les cordonnées où placer le choix
 * @param container Le pere du choix
 * @return GtkWidget* un pointeur vers le entry
 * */
GtkWidget* inputTexte(char* label, coordonnees* cord, GtkWidget* container){
    //Creer le box
    StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                     16, NULL,
                                     "", "6", "2",
                                     cord, dim(20, 30),container);
    create_styled_box(bxc);

    //creer le label
    creer_label(init_label(label, label,
                           NULL, NULL, bxc->widget,
                           "black", 1, "16", "Colspan"));

    //Creer le input
    entry_type_basic *basic_entry = Init_Entry_Basic(

            dim(10, 30),
            TRUE,  // editable
            TRUE,  // visible
            label,
            100,    // longueur maximale
            "",
            bxc->widget,
            cord(0, 0)
    );

    // Ajouter l'entrée basic au conteneur
    GtkWidget *basic_entry_widget = creer_entry_basic(basic_entry);

    //Retourner le input
    return (GtkWidget*) basic_entry_widget;
}

/**
 * @brief Creer un choix, contenant un input(entry) n'acceptant que des nombrse et un label
 * @param label Le label à donnée au choix (exemple: color, texte...)
 * @param cord Les cordonnées où placer le choix
 * @param container Le pere du choix
 * @return GtkWidget* un pointeur vers le entry
 * */
GtkWidget* inputNumber(char* label, coordonnees* cord, GtkWidget* container){
    //Creer le box
    StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                     16, NULL,
                                     "", "6", "2",
                                     cord, dim(20, 30),container);
    create_styled_box(bxc);

    //creer le label
    creer_label(init_label(label, label,
                           NULL, NULL, bxc->widget,
                           "black", 1, "16", "Colspan"));

    //Creer le input
    entry_type_basic *basic_entry = Init_Entry_Basic(

            dim(10, 30),
            TRUE,  // editable
            TRUE,  // visible
            label,
            100,    // longueur maximale
            "",
            bxc->widget,
            cord(0, 0)
    );

    // Ajouter l'entrée basic au conteneur
    GtkWidget *basic_entry_widget = creer_entry_basic(basic_entry);
    g_signal_connect(basic_entry_widget, "changed", (GCallback )inputHandler, NULL);

    //Retourner le input
    return (GtkWidget*) basic_entry_widget;
}

/**
 * @brief Creer un choix, contenant un bouton check et un label
 * @param label Le label à donnée au choix (exemple: color, texte...)
 * @param cord Les cordonnées où placer le choix
 * @param container Le pere du choix
 * @return GtkWidget* un pointeur vers le bouton
 * */
GtkWidget* inputCheck(char* label, coordonnees* cord, GtkWidget* container){
    //Creer le box
    StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                     16, NULL,
                                     "", "6", "2",
                                     cord, dim(20, 30),container);
    create_styled_box(bxc);

    //creer le label
    /*creer_label(init_label(label, label,
                           NULL, NULL, bxc->widget,
                           "black", 1, "16", "Colspan"));
    */

    btn* mybtn = btnCheck(label, label, label, margin(0,0,0,0),
                     bxc->widget,FALSE,NULL
    );
    Style *st = init_style("Colspan", NULL, 8, 1, NULL, -1, -1);
    creer_button(mybtn);
    appliquer_style_button(st, mybtn);
    //Retourner le input
    return (GtkWidget*) mybtn->button;
}

/**
 * @brief Creer un choix, contenant un combobox et un label
 * @param label Le label à donnée au choix (exemple: color, texte...)
 * @param cord Les cordonnées où placer le choix
 * @param container Le pere du choix
 * @param items Les élements du combobox
 * @return GtkWidget* un pointeur vers le combobox
 * */
GtkWidget* inputCombo(char* label, coordonnees* cord, GtkWidget* container,char* items[256]){
    //Creer le box
    StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                     16, NULL,
                                     "", "6", "2",
                                     cord, dim(20, 30),container);
    create_styled_box(bxc);

    //creer le label
    creer_label(init_label(label, label,
                           NULL, NULL, bxc->widget,
                           "black", 1, "16", "Colspan"));

    //Creer le combo
    gtkComboBox *combo = init_comboBox(*dim(20, 20), *cord(0, 0), "", bxc->widget);
    create_ComboBox(combo);
    int j = -1;
    while(items[++j]){
        ajouterElementComboBox(combo, items[j], items[j]);
    }
    elementActive(combo, 1);
    //Retourner le input
    return (GtkWidget*) combo->comboBox;
}
#endif //XML_TAHA_PROJET_UTILITY_H
