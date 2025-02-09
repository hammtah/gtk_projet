#include <gtk/gtk.h>
#include "global.h"
#include "xml_utility.h"
#include "bouton_xml.h"
#include "checkbox_xml.h"
#include "dialog_xml.h"
#include "radio_xml.h"
#include "taha_template.h"
#include "box.h"

void on_open_file_button_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *file_dialog;
    GtkWindow *parent_window = GTK_WINDOW(user_data);

    // Créer la boîte de dialogue FileChooser
    file_dialog = gtk_file_chooser_dialog_new("Ouvrir un fichier",
                                              parent_window,
                                              GTK_FILE_CHOOSER_ACTION_OPEN,
                                              "_Annuler", GTK_RESPONSE_CANCEL,
                                              "_Ouvrir", GTK_RESPONSE_ACCEPT,
                                              NULL);

    // Afficher la boîte de dialogue et récupérer la réponse
    if (gtk_dialog_run(GTK_DIALOG(file_dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(file_dialog);

        // Récupérer le chemin du fichier sélectionné
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Fichier sélectionné : %s\n", filename);

        // Libérer la mémoire
        g_free(filename);
    }

    // Détruire la boîte de dialogue après utilisation
    gtk_widget_destroy(file_dialog);
}



int maind(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);
////////////////////////////////---création de window---///////////////////////////////////////////////
    // Dimensions et coordonnées de la fenêtre
    dimension dim = {1000, 1500}; // Largeur: 800px, Hauteur: 600px
    coordonnees cord = {200, 100}; // Position: x=200, y=100

    // Couleur de fond
    HexColor *bg_color = hex_color_init("#FFC0CB"); // Couleur rose

    // Image de fond
    MonImage bg_img = {
            .path = "background.png", // Remplacez par le chemin de votre image
            .dim = dim,
            .cord = cord
    };

    // Initialisation de la fenêtre
    Mywindow *maFenetre = init_window("Ma Première Fenêtre GTK", "icon.png",
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

   // GtkWidget *fixed;
   // fixed=gtk_fixed_new();
  //  gtk_container_add(GTK_CONTAINER(maFenetre->window),fixed);


  //  gtk_fixed_put(GTK_FIXED(fixed),maFenetre->bgImg.Image,0,0);
    // Affiche tous les widgets dans la fenêtre
////////////////////////////////////////////////////////////////////////////////////////////////////////////:

///////////////////////////////////////---fixed---//////////////////////////////////////////////////////

fixedo *fixed;
fixed= init_fixed("principal",dim);
    creer_fixed(fixed);

    gtk_container_add(GTK_CONTAINER(maFenetre->window),fixed->fixed_container);

    fixed_add_widget(fixed,maFenetre->bgImg.Image,0,0);//Appliquer l'arriere plan

 //////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////---textview---///////////////////////////////////////////////////////////////
    // Définition des coordonnées et des dimensions
    coordonnees C = {100, 300};  // Exemple de coordonnées (x, y)
    dimension D = {200, 300};   // Exemple de dimensions (largeur, hauteur)

    // Initialisation du TextView avec un texte, un titre, des coordonnées et des dimensions
    MonTextView *textview = init_textview(" exemple de texte dans le TextView.", "MonTextViewTitre", C, D);

    // Création du widget GTK TextView à partir de l'objet MonTextView
    MonTextView *created_textview = creer_textview(textview);
    fixed_add_widget(fixed,created_textview->elem,C.x,C.y);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////---label---////////////////////////////////////////////////////////////:

    // Définition des coordonnées et des dimensions
    coordonnees C1 = {100, 100};  // Exemple de coordonnées (x, y)
    dimension D1 = {200, 50};   // Exemple de dimensions (largeur, hauteur)

    // Initialisation du label avec un texte, un titre, des coordonnées et des dimensions
    Monlabel *label = init_label("Ceci est un exemple de texte dans le Label.", "MonLabelTitre", C1, D1);

    // Création du widget GTK Label à partir de l'objet Monlabel
    Monlabel *created_label = creer_label(label);
    fixed_add_widget(fixed,label->elem,C1.x,C1.y);






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////---comboBox---//////////////////////////////////////////////////////////////////

    // Définir les dimensions et les coordonnées de la ComboBox
    dimension dim1 = {50, 30};  // Largeur et hauteur
    coordonnees cord1 = {50, 50};  // Position (x, y)

    // Initialiser la structure gtkComboBox
    gtkComboBox *combo = init_comboBox(dim1, cord1, "monComboBox", fixed->fixed_container);

    // Créer la ComboBox avec la fonction create_ComboBox
    create_ComboBox(combo);

    // Ajouter des éléments à la ComboBox
    ajouterElementComboBox(combo, "1", "Option 1");
    ajouterElementComboBox(combo, "2", "Option 2");
    ajouterElementComboBox(combo, "3", "Option 3");

    // Définir l'élément actif (sélectionner l'option 1)
    elementActive(combo, 0);


////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////---menu---///////////////////////////////////////////////////////
/*
// Créer une barre de menu
    MenuBar *menu_bar = creer_menu_bar();

    // Créer un menu "Fichier"
    Menu *menu_fichier = creer_menu();
    ajouter_element_au_menu(menu_fichier, "Ouvrir", G_CALLBACK(on_menu_item_activate));
    ajouter_element_au_menu(menu_fichier, "Enregistrer", G_CALLBACK(on_menu_item_activate));

    // Ajouter un sous-menu à "Options"
    GtkWidget *sous_menu = creer_sous_menu();
    GtkWidget *item_options = gtk_menu_item_new_with_label("Options");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

    ajouter_element_au_menu(menu_fichier, "Quitter", G_CALLBACK(gtk_main_quit));
    ajouter_menu_a_barre(menu_bar, "Fichier", menu_fichier);

    // Créer un menu "Edition"
    Menu *menu_edition = creer_menu();
    ajouter_element_au_menu(menu_edition, "Couper", G_CALLBACK(on_menu_item_activate));
    ajouter_element_au_menu(menu_edition, "Copier", G_CALLBACK(on_menu_item_activate));
    ajouter_element_au_menu(menu_edition, "Coller", G_CALLBACK(on_menu_item_activate));
    ajouter_menu_a_barre(menu_bar, "Édition", menu_edition);

    // Créer un menu "Aide"
    Menu *menu_aide = creer_menu();
    ajouter_element_au_menu(menu_aide, "À propos", G_CALLBACK(on_menu_item_activate));
    ajouter_menu_a_barre(menu_bar, "Aide", menu_aide);
    fixed_add_widget(fixed,menu_bar->menu_bar,500,0);
    // Ajouter la barre de menu à la fenêtre

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////---entry---///////////////////////////////////////////////////////////////////////

    // Initialiser les dimensions
    dimension dim_basic = { .width = 200, .height = 30 };
    dimension dim_password = { .width = 200, .height = 30 };

    // Initialiser un entry_type_basic
    entry_type_basic *basic_entry = Init_Entry_Basic(

            &dim_basic,
            TRUE,  // editable
            TRUE,  // visible
            "Entrez votre texte ici...",
            50,    // longueur maximale
            "Texte par défaut"
    );

    // Ajouter l'entrée basic au conteneur
    GtkWidget *basic_entry_widget = add_entry_basic(basic_entry);
    fixed_add_widget(fixed,basic_entry_widget,600,200);

    // Initialiser un entry_type_password
    entry_type_password *password_entry = Init_Entry_Password(

            &dim_password,
            "Mot de passe...",
            '*'
    );

    // Ajouter l'entrée password au conteneur
    GtkWidget *password_entry_widget = add_entry_password(password_entry);
    fixed_add_widget(fixed,password_entry_widget,600,250);

    // Ajouter des classes CSS (facultatif)
    entry_set_css_class(basic_entry_widget, "basic-entry");
    entry_set_css_class(password_entry_widget, "password-entry");
////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////---progressBar--/////////////////////////////////////////
    // Initialiser les dimensions
    dimension dim_pulse = { .width = 300, .height = 30 };
    dimension dim_fraction = { .width = 300, .height = 30 };

    // Créer une barre de progression de type pulsation
    progress_bar_type_pulse *pbar_pulse = Init_ProgressBar_Type_Pulse(
             &dim_pulse, TRUE, 'b', 100);

    GtkWidget *pulse_widget = add_progressbar_Tpulse(pbar_pulse);
      // Position dans le conteneur fixed
    fixed_add_widget(fixed,pulse_widget,500,900);


    // Créer une barre de progression fractionnée

    progress_bar_type_fraction *pbar_fraction = Init_ProgressBar_Type_Fraction(
             &dim_fraction, TRUE, 'r', 10.0);
    // Simuler un téléchargement avec `DownloadProgress`
    DownloadProgress *progress = g_malloc(sizeof(DownloadProgress));
    progress->progress_bar = GTK_PROGRESS_BAR(pbar_fraction->pbar);
    progress->total_size = 1024 * 100;  // 100 KB
    progress->current_size = 0;
    progress->is_active = TRUE;

    GtkWidget *fraction_widget = add_progressbar_Tfraction(pbar_fraction, progress);
    fixed_add_widget(fixed,fraction_widget,500,920);

////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////---boite_Dialogue---///////////////////////////////////////
    // Exemple de boîte de dialogue avec position prédéfinie
    dimension *dim3 = creer_dimension(300,300);

    GtkWidget *content_label = gtk_label_new("Ceci est une boîte de dialogue avec position prédéfinie.");
    boite_dialog *dialog1 = DIALOG(
            content_label,//Contenu(un widget)
            "Dialogue Prédefini",//titre
            dim3,//dimension
            NULL, // Pas d'icône pour cet exemple
            maFenetre->window,//Parent(conteneur)
            TRUE,//modal ou pas
            GTK_WIN_POS_CENTER_ON_PARENT//Position
    );
    creer_boite_dialogue(dialog1);
    g_signal_connect(dialog1->dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////---fileChooser---////////////////////////////////////////////////
    // Créer un bouton
    GtkWidget *button = gtk_button_new_with_label("Ouvrir un fichier");
    fixed_add_widget(fixed,button,700,400); // Positionner à (150, 100)

    // Connecter le signal "clicked" du bouton à la fonction qui ouvre le FileChooser
    g_signal_connect(button, "clicked", G_CALLBACK(on_open_file_button_clicked), fixed->fixed_container);
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////:---image---////////////////////////////////////////////////////:
 MonImage *image;
 dimension *img_dim= creer_dimension(100,100);
 coordonnees *img_coord= create_coordonnees(1000,100);
 image= init_image("ex_img.jpg",*img_dim,*img_coord);
    creer_image(image);
    fixed_add_widget(fixed,image->Image,img_coord->x,img_coord->y);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////---Boutons---///////////////////////////////////////////////////////
    //Bouton normal avec image
    MonImage* ima = init_image("icon.png",*dim(32,32), *cord(32,32));
    creer_button(btnNormalFixed("Nom","Label","Tooltip",fixed->fixed_container, cord(0,600),dim(64,32),ima));

    //Boutons radio
    //Création du pére du groupe
    btn* pere=creer_button(btnRadioFixed("Femme","Femme","Femme",fixed->fixed_container,cord(200,600),NULL, NULL));
    //Création des autres boutons appartenant au meme groupe que 'pere'
    creer_button(btnRadioFixed("Homme","Homme","Homme",fixed->fixed_container,cord(300,600),pere->button, NULL));

    //Boutons check
    creer_button(btnCheckFixed("Foot", "Football", "Football", cord(450, 600), fixed->fixed_container, FALSE, NULL));
    creer_button(btnCheckFixed("Basket", "BasketBall", "BasketBall", cord(550, 600), fixed->fixed_container, FALSE, NULL));
    //Boutons toggle
    creer_button(btnToggleFixed("Nom","Toggle","Tooltip",fixed->fixed_container, NULL,dim(700,32),NULL));
    //Boutons switch
    creer_button(btnSwitchFixed("switch","switch","switch",fixed->fixed_container,cord(900,600),dim(64,8),NULL, TRUE));
    //Button spin
    creer_button(btnSpinFixed("spin","spin","spin",dim(128,32), cord(1050,600), fixed->fixed_container, spinObj(5,2)));


////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
    gtk_widget_show_all(maFenetre->window);

    // Boucle principale GTK
    gtk_main();

    // Libération des ressources


    return 0;
}


int mainj(int argc, char *argv[]) {
    // Initialisation de GTK
    gtk_init(&argc, &argv);
    FILE *file = fopen("desc.txt", "r");
    if (!file) {
        printf("ERREUR d'ouverture du fichier !!");
        return -1;
    }
    creer_object(file, 0);
    gtk_main();
    return 0;
}




int main(int argc, char *argv[]){
    // Initialisation de GTK
    gtk_init(&argc, &argv);
////////////////////////////////---création de window---///////////////////////////////////////////////
    // Dimensions et coordonnées de la fenêtre
    dimension dim = {1000, 1500}; // Largeur: 800px, Hauteur: 600px
    coordonnees cord = {200, 100}; // Position: x=200, y=100

    // Couleur de fond
    HexColor *bg_color = hex_color_init("#FFC0CB"); // Couleur rose

    // Image de fond
    MonImage bg_img = {
            .path = "background.png", // Remplacez par le chemin de votre image
            .dim = dim,
            .cord = cord
    };

    // Initialisation de la fenêtre
    Mywindow *maFenetre = init_window("Test des fonctions de GTK+", "icon.png",
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

///////////////////////////////////////---fixed---//////////////////////////////////////////////////////

    fixedo *fixed;
    fixed= init_fixed("principal",dim);
    creer_fixed(fixed);

    gtk_container_add(GTK_CONTAINER(maFenetre->window),fixed->fixed_container);

    fixed_add_widget(fixed,maFenetre->bgImg.Image,0,0);//Appliquer l'arriere plan

    //////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////---menu---///////////////////////////////////////////////////////
    menu(fixed);

   //////////////////////////////////liste des radios////////////////////
   //Les labels des boutons
   char* labels[256] = {"Faible", "Moyen", "Bien", "Très bien", NULL};
   //Le style commun des boutons
   Style* st = init_style("Colspan", hex_color_init("#000"), 8, 1, NULL, -1, -1);
   //Creer le box
   StyledBox* bx = init_styled_box(GTK_ORIENTATION_HORIZONTAL, TRUE,
                                   16, NULL,
                                   "light-gray", "0", "3");
   create_styled_box(bx);
   //Creer la liste des boutons radios
   liste_radios(labels, st, bx);

   //Ajouter la liste(le box) au fixed
   fixed_add_widget(fixed,bx->widget,0,600);

   ////////////////////////////////////////////////////////////////////////////////////////////////
   gtk_widget_show_all(maFenetre->window);

    // Boucle principale GTK
    gtk_main();

    // Libération des ressources
    return 0;
}
