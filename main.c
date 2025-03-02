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
#include "containers_list.h"
#include "box_projet.h"

void openBtnNormaleProperties(GtkWidget* widget, gpointer *racine){

    Arbre* r = (Arbre*) racine;

    btnNormaleProperties("Button Normale", "Creation d'un bouton normale",
                      "ex_img.jpg", "icon.png", *cord(1200, 600),
                      r, NULL);

    gtk_widget_show_all(r->widget);

}

void openBoxProperties(GtkWidget* widget, gpointer *racine){

    Arbre* r = (Arbre*) racine;

    boxProperties("Button Normale", "Creation d'un box",
                         "ex_img.jpg", "icon.png", *cord(1200, 600),
                         r, NULL);

    gtk_widget_show_all(r->widget);

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



        ///////////////////////////////////////////////////////////////////////////


    Arbre* racine = allouer_arbre("fixed", fixed->fixed_container, NULL, NULL, 1);

    StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                     16, NULL,
                                     "", "6", "2",
                                     cord(100,200), dim(200, 200),racine->widget,"child1");
    create_styled_box(bxc);

    //GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //gtk_fixed_put(GTK_FIXED(fixed->fixed_container), box, 200, 300);
    //racine = insererArbre(racine, allouer_arbre("child1", box, NULL, NULL, 1), "fixed");
    //gtk_widget_show_all(box);

    racine = insererArbre(racine, allouer_arbre(bxc->nom, bxc->widget, NULL, NULL, 1), "fixed");
    gtk_widget_show_all(bxc->widget);


//////////////////////////////////  Button ///////////////////////////////////////////////////////
MonImage* ima = init_image("btn-icon.png",*dim(24,24), *cord(0,0));

btn* bb = btnNormalFixed("nom", "Bouton Normale ", "tooltip", fixed->fixed_container,
                     cord(0, 0), dim(50, 20), ima);
creer_button(bb);
g_signal_connect(bb->button, "clicked", G_CALLBACK(openBtnNormaleProperties), racine);

Style* bst = init_style(NULL, hex_color_init("#000"),
                    -1, -1, "#ff55", -1,
                    -1);
appliquer_style_button(bst, bb);


//Container* containers = NULL;
//Creer le box
/*StyledBox *bxc = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                             16, NULL,
                             "", "6", "2",
                             cord(100,200), dim(20, 30),fix->fixed_container);
create_styled_box(bxc);
*/
    //containers= inserer_container("box1", bxc->widget, containers);
    //le fixed eest en queue de liste donc
    //containers= inserer_container("fixed", fixed->fixed_container, containers);


    //////////////box

    btn* btnx = btnNormalFixed("btnx", "Box ", "Box", fixed->fixed_container,
                             cord(0, 150), dim(50, 20), NULL);
    creer_button(btnx);

    g_signal_connect(btnx->button, "clicked", G_CALLBACK(openBoxProperties), racine);


    // Affichage de l'arbre
    printf("Arborescence de l'arbre :\n");
    afficher_arbre(racine, 0);

    //inputChoix("Texte", cord(100, 100), fixed->fixed_container);
    gtk_widget_show_all(maFenetre->window);
    gtk_main();
    return 0;
}

