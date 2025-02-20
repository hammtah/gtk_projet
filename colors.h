//
// Created by ACER on 16/12/2024.
//

#ifndef PROJET_GTK_COLORS_H
#define PROJET_GTK_COLORS_H
#include "global.h"


// Structure pour représenter une couleur hexadécimale
typedef struct {
    GdkRGBA *color;        // Structure de couleur GTK
    gchar hex_code[100];  // Code couleur hexadécimal
} HexColor;

// Fonction pour initialiser une couleur hexadécimale
HexColor *hex_color_init(const gchar *hex_code) {
    if (!hex_code || strlen(hex_code) >= 100) {
        g_print( "Erreur : code couleur hexadécimal invalide\n");
        return NULL;
    }

    HexColor *new_color ;
    new_color =(HexColor*) malloc(sizeof(HexColor));
    if (!new_color) {
        g_print( "Erreur d'allocation mémoire pour HexColor\n");
        return NULL;
    }
    new_color->color =(GdkRGBA*) malloc(sizeof(GdkRGBA));
    if (!new_color->color) {
       g_print( "Erreur d'allocation mémoire pour GdkRGBA\n");
        free(new_color);
        return NULL;
    }

    // Copie du code couleur hexadécimal
    strcpy(new_color->hex_code, hex_code);

    // Conversion du code hexadécimal en GdkRGBA

    gint i =gdk_rgba_parse(new_color->color, new_color->hex_code);


    return new_color;
}



#endif //PROJET_GTK_COLORS_H
