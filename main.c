#include <gtk/gtk.h>
#include "global.h"
#include "xml_utility.h"
#include "bouton_xml.h"
#include "checkbox_xml.h"
#include "dialog_xml.h"
#include "radio_xml.h"
#include "taha_template.h"
#include "box.h"
#include "projet_utility.h"
#include "btn_projet.h"

void openBtnNormaleProperties(GtkWidget* widget, gpointer *container){
    fixedo* fix = (fixedo*) container;
    btnNormaleProperties("Button Normale", "Creation d'un bouton normale",
                      "ex_img.jpg", "icon.png", *cord(1200, 600),
                      fix->fixed_container, NULL);
    printf("fixed%d", fix);

    /*
    GtkWidget* bs = gtk_button_new_with_label("hello");
    fixed_add_widget(fix, bs, 50, 50);
     */
    gtk_widget_show_all(fix->fixed_container);

   // gtk_fixed_put(GTK_FIXED(fix), bs, 100, 100);
}

int main(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);

    ////////////////////////////////---création de window---///////////////////////////////////////////////
    // Dimensions et coordonnées de la fenêtre
    dimension dim = {1000, 1500}; // Largeur: 800px, Hauteur: 600px
    coordonnees cord = {200, 100}; // Position: x=200, y=100
    fixedo *fixed;
    Mywindow *maFenetre;
        // Couleur de fond
        HexColor *bg_color = hex_color_init("#FFC0CB"); // Couleur rose

        // Image de fond
        MonImage bg_img = {
                .path = "background.png", // Remplacez par le chemin de votre image
                .dim = dim,
                .cord = cord
        };

        // Initialisation de la fenêtre
        maFenetre = init_window("Test des fonctions de GTK+", "icon.png",
                                          dim,                       // Dimensions
                                          0,                        // Bordure
                                          FALSE,                      // Redimensionnable
                                          GTK_WIN_POS_CENTER,        // Position: Centrée
                                          cord,                      // Coordonnées
                                          *bg_color,                 // Couleur de fond
                                          bg_img                     // Image de fond
        );

        // Création de la fenêtre
        create_window(maFenetre);

        fixed = init_fixed("principal", dim);
        creer_fixed(fixed);

        gtk_container_add(GTK_CONTAINER(maFenetre->window), fixed->fixed_container);

        fixed_add_widget(fixed, maFenetre->bgImg.Image, 0, 0);//Appliquer l'arriere plan



    //////////////////////////////////  Button ///////////////////////////////////////////////////////
    btnSpinFixed("Opacité", "Opacité","Opacité",dim(32,32), cord(200,200),fixed->fixed_container, spinObj(1,2));

    MonImage* ima = init_image("btn-icon.png",*dim(24,24), *cord(0,0));

    btn* bb = btnNormalFixed("nom", "Bouton Normale ", "tooltip", fixed->fixed_container,
                             cord(0, 0), dim(50, 20), ima);
    creer_button(bb);
    g_signal_connect(bb->button, "clicked", G_CALLBACK(openBtnNormaleProperties), fixed);

    Style* bst = init_style(NULL, hex_color_init("#000"),
                            -1, -1, "#ff55", -1,
                            -1);
    appliquer_style_button(bst, bb);

    PangoFontMap *font_map = pango_cairo_font_map_get_default();
    PangoFontFamily **families;
    int n_families;

    pango_font_map_list_families(font_map, &families, &n_families);

    g_print("Available fonts:\n");
    for (int i = 0; i < n_families; i++) {
        g_print("%s\n", pango_font_family_get_name(families[i]));
    }

    //inputChoix("Texte", cord(100, 100), fixed->fixed_container);
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}