//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_FIXED_H
#define TEST1_FIXED_H
#include "global.h"

typedef struct {
    GtkWidget *fixed_container;  // Conteneur GtkFixed
    dimension fixed_dim;         // Dimensions (largeur, hauteur)
    gchar *fixed_name;           // Nom du conteneur
} fixedo;

// Fonction pour initialiser un conteneur fixed
fixedo* init_fixed(const gchar *name, dimension dim) {
    fixedo *nv_fixed = g_malloc(sizeof(fixedo));
    if (!nv_fixed) {
        g_print("Erreur lors de l'allocation de fixed\n");
        return NULL;
    }

    nv_fixed->fixed_container = gtk_fixed_new();
    nv_fixed->fixed_dim = dim;
    nv_fixed->fixed_name = g_strdup(name);

    return nv_fixed;
}

// Fonction pour configurer et appliquer les propriétés du fixed
void creer_fixed(fixedo *nv_fixed) {
    if (!nv_fixed || !nv_fixed->fixed_container) {
        g_print("Conteneur fixed invalide\n");
        return;
    }

    // Appliquer le nom et les dimensions
    gtk_widget_set_name(nv_fixed->fixed_container, nv_fixed->fixed_name);
    gtk_widget_set_size_request(nv_fixed->fixed_container,
                                nv_fixed->fixed_dim.width,
                                nv_fixed->fixed_dim.height);
}

// Fonction pour libérer la mémoire allouée
void detruire_fixed(fixedo *nv_fixed) {
    if (!nv_fixed) return;

    if (nv_fixed->fixed_name) g_free(nv_fixed->fixed_name);
    g_free(nv_fixed);
}
void fixed_add_widget(fixedo *nv_fixed, GtkWidget *widget, int x, int y) {
    gtk_fixed_put(GTK_FIXED(nv_fixed->fixed_container), widget, x, y);

}














#endif //TEST1_FIXED_H
