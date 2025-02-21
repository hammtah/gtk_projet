//
// Created by ACER on 05/01/2025.
//

#ifndef TEST1_IMAGE_H
#define TEST1_IMAGE_H
#include "global.h"

#ifndef PROJET_GTK_IMAGE_H
#define PROJET_GTK_IMAGE_H
#include "global.h"

typedef struct img {
    GtkWidget *Image;
    gchar path[300];
    dimension dim;
    coordonnees cord;
} MonImage;

// Fonction pour redimensionner une image
GtkWidget* redimensionner_image(GtkWidget *image, gint width, gint height) {
    if (!image) {
        g_print("\nErreur : image invalide.\n");
        return NULL;
    }

    GdkPixbuf *pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(image));
    if (!pixbuf) {
        g_print("\nErreur : impossible d'obtenir le pixbuf de l'image.\n");
        return NULL;
    }

    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    if (!scaled_pixbuf) {
        g_print("\nErreur lors du redimensionnement du pixbuf.\n");
        return NULL;
    }

    GtkWidget *resized_image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    //g_object_unref(scaled_pixbuf); // Libération du pixbuf redimensionné
    return resized_image;
}

// Fonction pour créer une image
MonImage* init_image(const gchar path[300], dimension dim, coordonnees cord) {
    if (!path || strlen(path) >= 100) {
        g_print("\nErreur : chemin invalide ou trop long.\n");
        return NULL;
    }

    MonImage *new_img = (MonImage *)malloc(sizeof(MonImage));
    if (!new_img) {
        g_print("\nErreur d'allocation mémoire pour MonImage.\n");
        return NULL;
    }

    // Initialisation de la structure
    strcpy(new_img->path, path);
    new_img->dim.height = dim.height;
    new_img->dim.width = dim.width;
    new_img->cord.x = cord.x;
    new_img->cord.y = cord.y;

    return new_img;

}

void creer_image(MonImage *img){

    if (!img) {
        g_print("\nErreur d'allocation mémoire pour MonImage.\n");
        exit(EXIT_FAILURE);
    }

img->Image = gtk_image_new_from_file(img->path);
    if (!img->Image) {
        g_print("\nErreur .\n");
        exit(EXIT_FAILURE);
    }
    img->Image= redimensionner_image(GTK_WIDGET(img->Image),img->dim.width,img->dim.height);
    if (!img->Image) {
        g_print("\nErreur lors du redimensionnement de l'image.\n");

        exit(EXIT_FAILURE);
    }
}


#endif // PROJET_GTK_IMAGE_H


















#endif //TEST1_IMAGE_H
