//
// Created by ACER on 16/12/2024.
//

#ifndef PROJET_GTK_WINDOW_H
#define PROJET_GTK_WINDOW_H
#include "global.h"


#define MAX 100

typedef struct window {
    GtkWidget *window;
    dimension dim;        // Dimensions de la fenêtre
    gint border_size;     // Épaisseur de la bordure de la fenêtre
    gchar title[MAX];     // Titre de la fenêtre (maximum MAX caractères)
    gchar icon_name[MAX]; // Nom de l'icône de la fenêtre
    gint resisable;       // Indique si la fenêtre est redimensionnable (0: FALSE, 1: TRUE)
    gchar position;       // Position initiale de la fenêtre [c: GTK_WIN_POS_CENTER]
    // ou [m: GTK_WIN_POS_MOUSE] ...
    coordonnees cord;     // Coordonnées de positionnement de la fenêtre par rapport à l'axe y et x
    HexColor  bgColor;   // Couleur de fond de la fenêtre
    MonImage bgImg;      // Image de fond de la fenêtre (pointeur pour éviter la copie)
} Mywindow;


// Fonction pour initialiser la structure Mywindow
Mywindow* init_window(const gchar *title, const gchar *icon_name, dimension dim, gint border_size,
                      gint resizable, gchar position, coordonnees cord, HexColor bgColor, MonImage bgImg) {


    // Allocation dynamique de mémoire pour une nouvelle instance de window
    Mywindow* maFenetre=NULL;
    maFenetre=(Mywindow*)malloc(sizeof(Mywindow));
    // Vérification de l'allocation de mémoire
    if(!maFenetre)
    {
        printf("\nerreur d'allocation de memoire.");
        exit(0);
    }
    // Initialisation des champs de la structure window avec les valeurs fournies
    maFenetre->dim=dim;
    maFenetre->border_size=border_size;
    strcpy(maFenetre->title,title);
    strcpy(maFenetre->icon_name,icon_name);
    maFenetre->resisable=resizable;
    maFenetre->position=position;
    maFenetre->bgColor=bgColor;
    maFenetre->cord=cord;

    ///////////////////////////////////////////////////////////////////////////////////////::
    maFenetre->bgImg=bgImg;
   // maFenetre->bgImg.Image = gtk_image_new_from_file(maFenetre->bgImg.path);
    creer_image(&(maFenetre->bgImg));


    ////////////////////////////////////////////////////////////////////////////////
    // Retour de la structure window initialisée
    return ((Mywindow*)maFenetre);


}
void create_window(Mywindow *maFenetre)
{
    // Crée une nouvelle fenêtre GTK+ de type toplevel
    maFenetre->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Définit la taille par défaut de la fenêtre en utilisant les dimensions fournies
    gtk_window_set_default_size(GTK_WINDOW(maFenetre->window),maFenetre->dim.width,maFenetre->dim.height);
    // Définit la position initiale de la fenêtre
    gtk_window_set_position(GTK_WINDOW(maFenetre->window), maFenetre->position);
    // Définit le titre de la fenêtre
    gtk_window_set_title(GTK_WINDOW(maFenetre->window), maFenetre->title);
    // Définit l'épaisseur de la bordure de la fenêtre
    gtk_container_set_border_width(GTK_CONTAINER(maFenetre->window), maFenetre->border_size);
    // Définit si la fenêtre est redimensionnable en fonction de la valeur de resizable
    if(!maFenetre->resisable)
        gtk_window_set_resizable(GTK_WINDOW(maFenetre->window),FALSE);
    else
        gtk_window_set_resizable(GTK_WINDOW(maFenetre->window),TRUE);
    // Modifie la couleur de fond de la fenêtre
    //gtk_widget_override_background_color(maFenetre->window, GTK_STATE_FLAG_NORMAL,maFenetre->bgColor.color);
    // Déplace la fenêtre aux coordonnées spécifiées dans cord
    gtk_window_move(GTK_WINDOW(maFenetre->window), maFenetre->cord.x,maFenetre->cord.y);
    // Charge l'icône de la fenêtre à partir du chemin donné
    GdkPixbuf *icon= create_icon_from_file(maFenetre->icon_name);


    //appliquer l'icon
    gtk_window_set_icon(GTK_WINDOW(maFenetre->window), icon);
    MonImage *background_image = init_image(maFenetre->bgImg.path,maFenetre->dim,maFenetre->cord);
    // Ajoute le widget d'image à la fenêtre
    //gtk_container_add(GTK_CONTAINER(maFenetre->window), background_image->image);
}
#endif //PROJET_GTK_WINDOW_H
