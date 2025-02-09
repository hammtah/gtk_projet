//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_LABEL_H
#define TEST1_LABEL_H
#include "global.h"



// Définition de la structure Monlabel
typedef struct {
    GtkWidget *elem;       // Widget du label
    gchar *texte;          // Texte du label
    gchar *titre;          // Titre du label
    coordonnees Crd;       // Coordonnées du label
    dimension dim;         // Dimensions du label
} Monlabel;


// Fonction pour initialiser et allouer un label
Monlabel *init_label(const gchar *texte, const gchar *tit, coordonnees C, dimension D) {
    if (!texte) {
        printf("Label vide!!!!!!\n");
        exit(-1);
    }

    Monlabel *L = (Monlabel *)malloc(sizeof(Monlabel));
    if (!L) {
        printf("Erreur d'allocation mémoire pour le label.\n");
        exit(-1);
    }

    // Allocation et initialisation du titre
    if (tit) {
        L->titre = (gchar *)malloc(30 * sizeof(gchar));
        if (!L->titre) {
            printf("Erreur d'allocation mémoire pour le titre du label.\n");
            exit(-1);
        }
        strcpy(L->titre, tit);
    } else {
        L->titre = NULL;
    }

    // Allocation et initialisation du texte
    L->texte = (gchar *)malloc(300 * sizeof(gchar));
    if (!L->texte) {
        printf("Erreur d'allocation mémoire pour le texte du label.\n");
        exit(-1);
    }
    strcpy(L->texte, texte);

    // Initialisation des coordonnées et dimensions
    L->Crd = C;
    L->dim = D;

    return L;
}

// Fonction pour créer un label GTK à partir d'un objet Monlabel
Monlabel *creer_label(Monlabel *L) {
    L->elem = gtk_label_new(L->texte);
    if (L->titre) {
        gtk_widget_set_name(L->elem, L->titre);
    }
    gtk_widget_set_size_request(L->elem, L->dim.width, L->dim.height);
    return L;
}








#endif //TEST1_LABEL_H
