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
#include "taha_template.h"

#ifndef XML_TAHA_BOX_H
#define XML_TAHA_BOX_H

typedef struct {
    GtkOrientation orientation; // GTK_ORIENTATION_HORIZONTAL ou GTK_ORIENTATION_VERTICAL
    gboolean homogeneous; // TRUE si tous les enfants ont la même taille
    gint spacing; // Espacement entre les widgets
    gchar *css_classes; // Classes CSS pour le style
    gchar *background_color; // Couleur de fond en CSS
    gchar *border_radius; // Rayon de bordure en CSS
    GtkWidget *widget; // Le GtkBox lui-même
} StyledBox;

/**
 * @brief Initialise une structure StyledBox avec les valeurs fournies.
 *
 * Cette fonction configure les propriétés d'un StyledBox, telles que son orientation,
 * son homogénéité, l'espacement entre les enfants et les styles CSS associés.
 * Elle ne crée pas encore le GtkBox lui-même, cela se fera dans une autre fonction.
 *
 * @param box Pointeur vers la structure StyledBox à initialiser.
 * @param orientation Orientation du GtkBox (GTK_ORIENTATION_HORIZONTAL ou GTK_ORIENTATION_VERTICAL).
 * @param homogeneous Définit si les enfants ont la même taille (TRUE ou FALSE).
 * @param spacing Espacement entre les widgets à l'intérieur du GtkBox.
 * @param css_classes Liste de classes CSS optionnelles à appliquer (peut être NULL).
 * @param background_color Couleur de fond en CSS (peut être NULL).
 * @param border_radius Rayon de la bordure en CSS (peut être NULL).
 */
void init_styled_box(StyledBox *box, GtkOrientation orientation, gboolean homogeneous, gint spacing,
                     const gchar *css_classes, const gchar *background_color, const gchar *border_radius) {
    box->orientation = orientation;
    box->homogeneous = homogeneous;
    box->spacing = spacing;

    // Copie des styles CSS s'ils sont fournis
    box->css_classes = css_classes ? g_strdup(css_classes) : NULL;
    box->background_color = background_color ? g_strdup(background_color) : NULL;
    box->border_radius = border_radius ? g_strdup(border_radius) : NULL;

    box->widget = NULL; // Le widget sera créé dans une autre fonction
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

    // Application des styles CSS si des valeurs sont fournies
    if (box->background_color || box->border_radius) {
        GtkCssProvider *provider = gtk_css_provider_new();
        gchar *css = g_strdup_printf(
                "box { background-color: %s; border-radius: %s; }",
                box->background_color ? box->background_color : "transparent",
                box->border_radius ? box->border_radius : "0px"
        );

        // Chargement et application du style CSS
        gtk_css_provider_load_from_data(provider, css, -1, NULL);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

        // Libération de la mémoire
        g_free(css);
        g_object_unref(provider);
    }
}


#endif //XML_TAHA_BOX_H
