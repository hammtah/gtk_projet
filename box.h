//
// Created by Dell on 2/9/2025.
//

#include <gtk/gtk.h>
#include "global.h"
#include "xml_utility.h"
#include "bouton_xml.h"
#include "checkbox_xml.h"
#include "dialog_xml.h"
#include "radio_xml.h"

#ifndef XML_TAHA_BOX_H
#define XML_TAHA_BOX_H

typedef struct {
    GtkOrientation orientation; // GTK_ORIENTATION_HORIZONTAL ou GTK_ORIENTATION_VERTICAL
    gboolean homogeneous; // TRUE si tous les enfants ont la même taille
    gint spacing; // Espacement entre les widgets
    gchar *css_classes; // Classes CSS pour le style
    gchar *background_color; // Couleur de fond en CSS
    gchar *border_radius; // Rayon de bordure en CSS
    gchar *border; // Epaisseur de bordure en CSS
    GtkWidget *widget; // Le GtkBox lui-même
    coordonnees* cord; //Position
    GtkWidget* container;//Conteneur (fixed)
} StyledBox;

/**
 * @brief Alloue dynamiquement une structure StyledBox et vérifie si l'allocation a réussi.
 * @return Un pointeur vers un StyledBox alloué ou NULL si l'allocation échoue.
 */
StyledBox *allocate_styled_box() {
    StyledBox *box = (StyledBox *)malloc(sizeof(StyledBox));
    if (!box) {
        fprintf(stderr, "Erreur: Échec de l'allocation mémoire pour StyledBox.\n");
        return NULL;
    }
    return box;
}

/**
 * @brief Initialise une structure StyledBox avec les valeurs fournies.
 *
 * Cette fonction configure les propriétés d'un StyledBox, telles que son orientation,
 * son homogénéité, l'espacement entre les enfants et les styles CSS associés.
 * Elle ne crée pas encore le GtkBox lui-même, cela se fera dans une autre fonction.
 *
 * @param orientation Orientation du GtkBox (GTK_ORIENTATION_HORIZONTAL ou GTK_ORIENTATION_VERTICAL).
 * @param homogeneous Définit si les enfants ont la même taille (TRUE ou FALSE).
 * @param spacing Espacement entre les widgets à l'intérieur du GtkBox.
 * @param css_classes Liste de classes CSS optionnelles à appliquer (peut être NULL).
 * @param background_color Couleur de fond en CSS (peut être NULL).
 * @param border_radius Rayon de la bordure en CSS (peut être NULL).
 * @param border Epaisseur de la bordure en CSS (peut être NULL).
 * @param cord Position du box (x et y)
 * @param container Le conteneur (fixed)
 *
 * @return *box un pointeur vers le box initialisé
 */

StyledBox *init_styled_box( GtkOrientation orientation, gboolean homogeneous, gint spacing,
                     const gchar *css_classes, const gchar *background_color,
                     const gchar *border_radius, const gchar *border, coordonnees* cord,
                     GtkWidget* container) {
    StyledBox* box = allocate_styled_box();
    box->orientation = orientation;
    box->homogeneous = homogeneous;
    box->spacing = spacing;

    // Copie des styles CSS s'ils sont fournis
    box->css_classes = css_classes ? g_strdup(css_classes) : NULL;
    box->background_color = background_color ? g_strdup(background_color) : NULL;
    box->border_radius = border_radius ? g_strdup(border_radius) : NULL;
    box->border = border ? g_strdup(border) : NULL;
    box->cord = cord ;
    box->widget = NULL; // Le widget sera créé dans une autre fonction
    box->container = container;
}


/**
 * @brief Crée un GtkBox en utilisant les paramètres d'une structure StyledBox (compatible GTK3).
 *
 * Cette fonction instancie un GtkBox avec l'orientation, l'homogénéité et l'espacement
 * définis dans la structure StyledBox. Elle applique également les styles CSS si définis.
 *
 * @param box Pointeur vers une structure StyledBox préalablement initialisée.
 */
void create_styled_box(StyledBox *box) {
    if (!box) return; // Vérification de la validité du pointeur

    // Création du GtkBox avec les propriétés définies
    box->widget = gtk_box_new(box->orientation, box->spacing);
    gtk_box_set_homogeneous(GTK_BOX(box->widget), box->homogeneous);

    // Récupération du contexte de style
    GtkStyleContext *context = gtk_widget_get_style_context(box->widget);

    // Ajout des classes CSS si définies
    if (box->css_classes) {
        gtk_style_context_add_class(context, box->css_classes);
    }

    //Associé le box à un conteneur
    if(GTK_IS_FIXED(box->container)){
        gtk_fixed_put(GTK_FIXED(box->container), box->widget, box->cord->x, box->cord->y);
    }
    gtk_container_add(GTK_CONTAINER(box->container), box->widget);
    // Application des styles CSS si des valeurs sont fournies
    if (box->background_color || box->border_radius) {
        GtkCssProvider *provider = gtk_css_provider_new();
        gchar *css = g_strdup_printf(
                "box { background: %s; border-radius: %s; border: %s solid}",
                box->background_color ? box->background_color : "transparent",
                box->border_radius ? box->border_radius : "0px",
                box->border ? box->border : "0px"
        );

        // Chargement et application du style CSS
        gtk_css_provider_load_from_data(provider, css, -1, NULL);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

        // Libération de la mémoire
        g_free(css);
        g_object_unref(provider);
    }
}


//Xml things
void box_xml(FILE *file,int parent)
{
    char border_radius[MAX], border[MAX],  cord[MAX];
    char homogeneous,spacing[MAX],x[MAX],y[MAX],bgColor[MAX], width[MAX], height[MAX];
    int orientation;
    int test;
    //si on trouve property balise retourne 22
    while((test=balise(file))==22)
    {
        char mot[MAX];
        int ind=0;
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", mot);

        //recuperation du l'orientation de box
        // 0 pour horizontal et 1 pour vertical
        if (!(strcmp("orientation\"", mot)))
        {
            orientation = char_TO_int(lire_gchar(file));
            printf("orientation: %d", orientation);
        }
        if (!(strcmp("spacing\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, spacing, 10);
        }
            //recuperation de width
        else if (!(strcmp("width\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, width, 10);
        }
            //recuperation de height
        else if (!(strcmp("height\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, height, 10);
        }
            //recuperation de l'homogeneté
        else if (!(strcmp("homogene\"", mot)))
        {
            homogeneous = char_TO_int(lire_gchar(file));
        }
            //recuperation de couleur de fond
        else if (!(strcmp("bgColor\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, bgColor, 10);
        }
            //recuperation de couleur de fond
        else if (!(strcmp("x\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, x, 10);
        }
            //recuperation de couleur de fond
        else if (!(strcmp("y\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, y, 10);
        }
        else if (!(strcmp("border\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, border, 10);
        }
        else if (!(strcmp("border_radius\"", mot)))
        {
            lire_gchar_str_with_deplacement(file, border_radius, 10);
        }
    }
    //creation
    //Creer le box et le mettre dans le conteneur fixed
    StyledBox* b = init_styled_box(orientation, homogeneous, atoi(spacing),
                                   NULL, bgColor,border_radius, border,
                                   cord(atoi(x), atoi(y)), parents[parent]);
    create_styled_box(b);
    //le mettre dans fixed
    //gtk_fixed_put(GTK_FIXED(parents[parent]),MonBox->box,cord.xw,cord.yh);
    //si child balise retourne 23
    if((test==23))
    {
        parents[3]=b->widget;
        creer_object(file,3);
    }

}


#endif //XML_TAHA_BOX_H
