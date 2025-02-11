//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_TEXTVIEW_H
#define TEST1_TEXTVIEW_H
#include "global.h"

// Définition de la structure MonTextView
typedef struct {
    GtkWidget *elem;        // Widget du TextView
    gchar *texte;           // Texte du TextView
    gchar *titre;           // Titre du TextView (optionnel)
    coordonnees Crd;        // Coordonnées du TextView
    dimension dim;          // Dimensions du TextView
    GtkWidget* container;//conteneur
} MonTextView;



// Fonction pour initialiser un TextView
MonTextView *init_textview(const gchar *texte, const gchar *tit, coordonnees C, dimension D, GtkWidget* container) {
    if (!texte) {
        printf("Texte vide pour le TextView!\n");
        exit(-1);
    }

    MonTextView *T = (MonTextView *)malloc(sizeof(MonTextView));
    if (!T) {
        printf("Erreur d'allocation mémoire pour le TextView.\n");
        exit(-1);
    }

    // Allocation et initialisation du titre
    if (tit) {
        T->titre = (gchar *)malloc(30 * sizeof(gchar));
        if (!T->titre) {
            printf("Erreur d'allocation mémoire pour le titre du TextView.\n");
            exit(-1);
        }
        strcpy(T->titre, tit);
    } else {
        T->titre = NULL;
    }

    // Allocation et initialisation du texte
    T->texte = (gchar *)malloc(300 * sizeof(gchar));
    if (!T->texte) {
        printf("Erreur d'allocation mémoire pour le texte du TextView.\n");
        exit(-1);
    }
    strcpy(T->texte, texte);

    // Initialisation des coordonnées et dimensions
    T->Crd = C;
    T->dim = D;
    if(container) T->container = container;

    return T;
}

// Fonction pour créer un TextView GTK à partir d'un objet MonTextView
MonTextView *creer_textview(MonTextView *T) {
    T->elem = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(T->elem));
    gtk_text_buffer_set_text(buffer, T->texte, -1);

    if (T->titre) {
        gtk_widget_set_name(T->elem, T->titre);
    }
    gtk_widget_set_size_request(T->elem, T->dim.width, T->dim.height);

    if(GTK_IS_FIXED(T->container)){
        gtk_fixed_put(GTK_FIXED(T->container), T->elem, T->Crd.x, T->Crd.y);
    }
    gtk_container_add(GTK_CONTAINER(T->container), T->elem);
    return T;
}











#endif //TEST1_TEXTVIEW_H
