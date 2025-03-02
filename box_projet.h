//
// Created by Dell on 3/1/2025.
//

#ifndef XML_TAHA_BOX_PROJET_H
#define XML_TAHA_BOX_PROJET_H

#include "global.h"
#include "coordonnees.h"
#include "button.h"
#include "bouton_xml.h"
#include "containers_list.h"


GtkWidget* inputTexte(char* label, coordonnees* cord, GtkWidget* container, char* defaultTexte);
GtkWidget* inputNumber(char* label, coordonnees* cord, GtkWidget* container, int defaultNum, float steps);
GtkWidget* inputCheck(char* label, coordonnees* cord, GtkWidget* container, gboolean isChecked);
GtkWidget* inputCombo(char* label, coordonnees* cord, GtkWidget* container,char* items[256]);

void boxProperties(char* titre, char* message, char* messageIcon, char* icon,
                          coordonnees c, Arbre* racine, StyledBox *box);
//Structure regroupant les widgets contenus dans un dialogue de creation de bouton
//nom, label, tooltip, container, margin, dim, img
typedef struct {
    GtkWidget *orientation;
    GtkWidget *homogeneous;
    GtkWidget *spacing;
    GtkWidget *css_classes;
    GtkWidget *background_color;
    GtkWidget *border_radius;
    GtkWidget *border;
    GtkWidget *posY;
    GtkWidget *posX;
    GtkWidget *dimX;
    GtkWidget *dimY;
    GtkWidget *nom;
    GtkWidget *container;
    Arbre *racine;
    StyledBox *box;

} DialogWidgets_box;

DialogWidgets_box* creerDialogWidgets_box(){
    DialogWidgets_box* data = (DialogWidgets_box*) malloc(sizeof(DialogWidgets_box));
    if(!data){
        perror("Erreur d'allocation de DialogWidgets");
        exit(-1);
    }
    return data;
}

void boxModify(GtkWidget* widget, gpointer* data){
    /*btnNew* bn = (btnNew*) data;
    btnNormaleProperties("Button Normale", "Modification d'un bouton normale",
                         "ex_img.jpg", "icon.png", *cord(1200, 600),
                         bn->b->container, bn);*/
}

void deleteWidget(GtkWidget* widget, gpointer* data){
    GtkWidget* w = (GtkWidget*) w;
    gtk_widget_destroy(w);
}
//Traiter les réponses provenants du boite de dialogue(nice)
void boxPropertiesResponse(GtkDialog *dialog, gint response_id, gpointer *user_data) {
    //Creer la boite de creation d'un box
    if (response_id == GTK_RESPONSE_OK) {
        //Cast
        DialogWidgets_box* data = (DialogWidgets_box*) user_data;
        //Get widgets data
        const gchar *background_color = gtk_entry_get_text(GTK_ENTRY(data->background_color));
        gchar *nom = gtk_entry_get_text(GTK_ENTRY(data->nom));
        gboolean homogeneous = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->homogeneous));
        //const gchar *img = gtk_entry_get_text(GTK_ENTRY(data->img));
        const gchar *width = gtk_entry_get_text(GTK_ENTRY(data->dimX));
        const gchar *height = gtk_entry_get_text(GTK_ENTRY(data->dimY));
        const gchar *x = gtk_entry_get_text(GTK_ENTRY(data->posX));
        const gchar *y = gtk_entry_get_text(GTK_ENTRY(data->posY));
        const gchar *border = gtk_entry_get_text(GTK_ENTRY(data->border));
        const gchar *border_radius = gtk_entry_get_text(GTK_ENTRY(data->border_radius));
        const gchar *spacing = gtk_entry_get_text(GTK_ENTRY(data->spacing));
        const gchar* orientation = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->orientation));
        const gchar *containerString = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->container));
        g_print("\ncontainerstring %s", containerString);
        GtkWidget* container = getWidgetByNom(data->racine, containerString);
        //GtkWidget* container = data->container;

/*
        //Default values, provided when the input is empty
        if(strlen(label) == 0 ) label = "button";
        if(strlen(width) == 0 ) width = "10";
        if(strlen(height) == 0 ) height = "10";
        if(strlen(x) == 0 ) x = "10";
        if(strlen(y) == 0 ) y = "10";
        if(strlen(color) == 0 ) color = "#000";
        if(strlen(taille) == 0 ) taille = "8";
        if(strlen(border) == 0 ) border = "0";
        if(strlen(border_radius) == 0 ) border_radius = "0";
        if(strlen(opacite) == 0 ) opacite = "1";
        //if(strlen(bg) == 0 ) bg = "";
*/

        bool borientation = strcmp(orientation, "Horizontal");//0:hori
        StyledBox *bx = init_styled_box(borientation,homogeneous, atoi(spacing),
        NULL, background_color,border_radius, border, cord(atoi(x), atoi(y)), dim(atoi(width), atoi(height)),
                container, nom);
        create_styled_box(bx);

        //Ajouter le box dans l'arbre
        data->racine = insererArbre(data->racine, allouer_arbre(bx->nom, bx->widget, NULL, NULL, 1), containerString);



        //Ajouter le callback permettant la modification du bouton
        //g_signal_connect(bx->widget, "clicked", G_CALLBACK(boxModify), bx);

        //Détruire l'ancien bouton s'il existe déja(dans le cas de modification d'un bouton déja existant)
        if(data->box){
            gtk_widget_destroy(data->box->widget);
        }
        //Show all
        gtk_widget_show_all(container);
        //Fermer le dialogue
        gtk_widget_destroy(GTK_WIDGET(dialog));

    }
    else if(response_id == GTK_RESPONSE_CANCEL || response_id == GTK_RESPONSE_CLOSE) {
        gtk_widget_destroy(GTK_WIDGET(dialog));
    }

    // Fermer la boîte de dialogue
}



void boxProperties(char* titre, char* message, char* messageIcon, char* icon,
                          coordonnees c, Arbre* racine, StyledBox* box) {
    boite_dialog *boite = NULL;

// Le conteneur des widgets formant le contenue du dialogue (content area)
    GtkWidget *contentArea = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);  // Espacement de 10 pixels
// Ajoute 20 pixels de padding autour du contenu de la boîte(faire semblant que le box est centré)
    gtk_container_set_border_width(GTK_CONTAINER(contentArea), 24);
//Label
    GtkWidget *content_label = gtk_label_new(message);
//Ajouter le label(message) au conteneur (contentArea)
    gtk_box_pack_start(GTK_BOX(contentArea), content_label, TRUE, TRUE, 0);
    DialogWidgets_box *data = creerDialogWidgets_box();

    //'bouton' est null çad qu'on va creer un nouveau bouton
    if(!box) {
        //Creation des inputs
        //char *options[] = {"Red", "Blue", "Green", NULL};
//data->align = inputCombo("Align", cord(100, 100), contentArea, options);
        char *orientations[] = {"Horizontal", "Vertical", NULL};
        data->orientation = inputCombo("Orientation", cord(100, 100), contentArea, orientations);
        data->homogeneous = inputCheck("Homogeneous", cord(100, 100), contentArea, TRUE);
        data->spacing = inputNumber("Spacing", cord(100, 100), contentArea, 0, 1);

        data->background_color =  inputTexte("Background", cord(100, 100), contentArea, "");
        data->border_radius = inputNumber("Border Radius", cord(100, 100), contentArea, 0, 1);
        data->border = inputNumber("Border", cord(100, 100), contentArea, 0, 1);
        data->dimX = inputNumber("width", cord(100, 100), contentArea, 10, 10);
        data->dimY = inputNumber("height", cord(100, 100), contentArea, 10, 10);
        data->posX = inputNumber("x", cord(100, 100), contentArea, 10, 10);
        data->posY = inputNumber("y", cord(100, 100), contentArea, 10, 10);
        data->nom = inputTexte("Nom", cord(100, 100), contentArea, "");
        data->racine = racine;
        char* containers[20];
        getNomsConteneurs(racine, containers);
        data->container = inputCombo("Container", cord(100, 100), contentArea, containers);
        data->box = NULL;
    }
        //on va modifier un bouton existant
        /*
    else{
        //Creation des inputs
        data->label = inputTexte("Label", cord(100, 100), contentArea, bouton->b->label);
        data->hasMnemonic = inputCheck("HasMnemonic", cord(100, 100), contentArea, bouton->b->hasMnemonic);
        data->img = inputTexte("Image", cord(100, 100), contentArea, bouton->b->img? bouton->b->img->path: "");
        //width
        data->dimX = inputNumber("width", cord(100, 100), contentArea, bouton->b->dim->width, 10);
        //height
        data->dimY = inputNumber("height", cord(100, 100), contentArea, bouton->b->dim->height, 10);
        //x
        data->posX = inputNumber("x", cord(100, 100), contentArea, bouton->b->pos->x, 10);
        //y
        data->posY = inputNumber("y", cord(100, 100), contentArea, bouton->b->pos->y, 10);
        data->isSensitive = inputCheck("isSensitive", cord(100, 100), contentArea, bouton->b->isSensitive);
        //opacity
        data->opacity = inputNumber("Opacité", cord(100, 100), contentArea, bouton->b->opacity, 0.1);
        //data->container = parent;

        //should get it from style structure
        data->color = inputTexte("Color", cord(100, 100), contentArea, bouton->s->color->hex_code);
        data->taille = inputNumber("Taille", cord(100, 100), contentArea, bouton->s->taille, 1);
        data->gras = inputCheck("Gras", cord(100, 100), contentArea, bouton->s->gras);
        data->border = inputNumber("Border", cord(100, 100), contentArea, bouton->s->border, 1);
        data->border_radius = inputNumber("Border Radius", cord(100, 100), contentArea, bouton->s->border_radius, 1);
        //data->margin
        //char *options[] = {"Red", "Blue", "Green", NULL};
        //data->align = inputCombo("Color", cord(100, 100), contentArea, options);
        data->bouton = bouton->b;
        data->bg = inputTexte("Background", cord(100, 100), contentArea, bouton->s->bgcolor);
        //police
        char *polices[] = {
                "Arial", "Verdana", "Tahoma", "Times New Roman", "Georgia",
                "Calibri", "Cambria", "Courier New", "Consolas", "Trebuchet MS",
                "Segoe UI", "Lucida Sans Unicode", "Comic Sans MS", "Impact",
                "Palatino Linotype", "Gadugi", "Microsoft Sans Serif", NULL
        };
        data->police = inputCombo("Police", cord(100, 100), contentArea, polices);

        g_print("\nlast bgcolor: %s", bouton->s->bgcolor);

    }
*/
//Creer le box
    boite = DIALOG(
            contentArea,//Contenu(un widget)
            titre,//titre
            dim(500, 200),//dimension
            icon, // Pas d'icône pour cet exemple
            racine->widget,//Parent(conteneur)
            TRUE,//modal ou pas
            GTK_WIN_POS_CENTER//Position
    );
    creer_boite_dialogue(boite);
    if(box){
        //Ajouter bouton de suppression
        GtkWidget* delete = gtk_button_new_with_label("Supprimer");
        g_signal_connect(delete, "clicked", G_CALLBACK(deleteWidget), box->widget);
        addActionWidget(boite, delete, GTK_RESPONSE_CLOSE);
    }
    //Ajouter des boutons
    GtkWidget *btnOk = gtk_button_new_with_label("Oui");
    addActionWidget(boite, btnOk, GTK_RESPONSE_OK);

    //Ajouter des boutons
    GtkWidget *btnAn = gtk_button_new_with_label("Annuler");
    addActionWidget(boite, btnAn, GTK_RESPONSE_CANCEL);
    //Associer un signal au boite
    g_signal_connect(boite->dialog, "response", G_CALLBACK(boxPropertiesResponse), data);

}

#endif //XML_TAHA_BOX_PROJET_H
