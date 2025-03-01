//
// Created by Dell on 3/1/2025.
//

#ifndef XML_TAHA_BTN_PROJET_H
#define XML_TAHA_BTN_PROJET_H
#include "global.h"
#include "coordonnees.h"
#include "button.h"
#include "bouton_xml.h"

typedef struct btnNew{
    btn* b;
    Style* s;
}btnNew;

btnNew* allocateBtnNew(){
    btnNew* mybtnNew=(btnNew*)malloc(sizeof(btnNew));//Allocation
    //Retourner un message d'erreur et sortire du programme si l'allocation est échouée
    if(!mybtnNew)
    {
        perror("Erreur d'allocation de bouton dans allocateBtnNew\n");
        exit -1;
    }
    //Retourner le bouton
    return (btnNew*) mybtnNew;
}


GtkWidget* inputTexte(char* label, coordonnees* cord, GtkWidget* container, char* defaultTexte);
GtkWidget* inputNumber(char* label, coordonnees* cord, GtkWidget* container, int defaultNum, float steps);
GtkWidget* inputCheck(char* label, coordonnees* cord, GtkWidget* container, gboolean isChecked);
GtkWidget* inputCombo(char* label, coordonnees* cord, GtkWidget* container,char* items[256]);

void btnNormaleProperties(char* titre, char* message, char* messageIcon, char* icon,
                          coordonnees c, GtkWidget* parent, btnNew* bouton);
//Structure regroupant les widgets contenus dans un dialogue de creation de bouton
//nom, label, tooltip, container, margin, dim, img
typedef struct {
    GtkWidget* label;
    GtkWidget* hasMnemonic;
    GtkWidget* img;
    GtkWidget* dimX;
    GtkWidget* dimY;
    GtkWidget* posX;
    GtkWidget* posY;
    //GtkWidget* margin;
    GtkWidget* isSensitive;
    GtkWidget* align;
    GtkWidget* opacity;
    GtkWidget* container;
    GtkWidget* color;
    GtkWidget* bg;
    GtkWidget*  police;
    GtkWidget*  taille;
    GtkWidget*  gras;
    GtkWidget*  border;
    GtkWidget*  border_radius;
    btn* bouton;
} DialogWidgets_btn;

DialogWidgets_btn* creerDialogWidgets_btn(){
    DialogWidgets_btn* data = (DialogWidgets_btn*) malloc(sizeof(DialogWidgets_btn));
    if(!data){
        perror("Erreur d'allocation de DialogWidgets");
        exit(-1);
    }
    return data;
}

void btnNormaleModify(GtkWidget* widget, gpointer* data){
    btnNew* bn = (btnNew*) data;
    btnNormaleProperties("Button Normale", "Modification d'un bouton normale",
                         "ex_img.jpg", "icon.png", *cord(1200, 600),
                         bn->b->container, bn);
}

void deleteBtn(GtkWidget* widget, gpointer* data){
    GtkWidget* btn = (GtkWidget*) data;
    gtk_widget_destroy(btn);
}
//Traiter les réponses provenants du boite de dialogue(nice)
void btnNormalePropertiesResponse(GtkDialog *dialog, gint response_id, gpointer *user_data) {
    //Creer la boite de creation d'un bouton normale
    if (response_id == GTK_RESPONSE_OK) {
        //Cast
        DialogWidgets_btn* data = (DialogWidgets_btn*) user_data;
        //Get widgets data
        const gchar *label = gtk_entry_get_text(GTK_ENTRY(data->label));
        gboolean hasMnemonic = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->hasMnemonic));
        //const gchar *img = gtk_entry_get_text(GTK_ENTRY(data->img));
        gchar *img = gtk_entry_get_text(GTK_ENTRY(data->img));
        const gchar *width = gtk_entry_get_text(GTK_ENTRY(data->dimX));
        const gchar *height = gtk_entry_get_text(GTK_ENTRY(data->dimY));
        const gchar *x = gtk_entry_get_text(GTK_ENTRY(data->posX));
        const gchar *y = gtk_entry_get_text(GTK_ENTRY(data->posY));
        const gchar *color = gtk_entry_get_text(GTK_ENTRY(data->color));
        const gchar *bg = gtk_entry_get_text(GTK_ENTRY(data->bg));
        const gchar *police = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->police));
        const gchar *taille = gtk_entry_get_text(GTK_ENTRY(data->taille));
        gboolean gras = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->gras));
        //bgcolor
        const gchar *border = gtk_entry_get_text(GTK_ENTRY(data->border));
        const gchar *border_radius = gtk_entry_get_text(GTK_ENTRY(data->border_radius));

        //data->margin
        gboolean isSensitive = 1;//Le bouton est sensible par défaut
        isSensitive = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->isSensitive));
        //const gchar *align = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->align));
        const gchar *opacite = gtk_entry_get_text(GTK_ENTRY(data->opacity));
        GtkWidget* container = data->container;

        //Creer l'image du bouton
        MonImage* ima = NULL;//Initier l'image avec NULL
        //Creer l'image si le path est saisie
        if(strlen(img) > 0){
            ima = init_image(img,*dim(24,24), *cord(0,0));
        }

        //Creation du bouton
        int isFixed = 1;
        int isChecked = 1;

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



        btn* b = initBtn(NORMAL, label, label, hasMnemonic, label, ima,
                         dim(atoi(width), atoi(height)),
                         isFixed, cord(atoi(x), atoi(y)), NULL, isSensitive,
                         container, NULL, GTK_ALIGN_CENTER,
                         atof(opacite), isChecked, NULL);
        creer_button(b);
        //Creer le style
        HexColor* h = hex_color_init(color);
        Style* style = init_style(police, h, atoi(taille),
                                  gras, bg, atoi(border),
                                  atoi(border_radius));
        appliquer_style_button(style, b);

        btnNew* bn = allocateBtnNew();
        bn->b = b;
        bn->s = style;

        //Ajouter le callback permettant la modification du bouton
        g_signal_connect(b->button, "clicked", G_CALLBACK(btnNormaleModify), bn);

        //Détruire l'ancien bouton s'il existe déja(dans le cas de modification d'un bouton déja existant)
        if(data->bouton){
            gtk_widget_destroy(data->bouton->button);
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



void btnNormaleProperties(char* titre, char* message, char* messageIcon, char* icon,
                          coordonnees c, GtkWidget* parent, btnNew* bouton) {
    boite_dialog *boite = NULL;

// Le conteneur des widgets formant le contenue du dialogue (content area)
    GtkWidget *contentArea = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);  // Espacement de 10 pixels
// Ajoute 20 pixels de padding autour du contenu de la boîte(faire semblant que le box est centré)
    gtk_container_set_border_width(GTK_CONTAINER(contentArea), 24);
//Label
    GtkWidget *content_label = gtk_label_new(message);
//Ajouter le label(message) au conteneur (contentArea)
    gtk_box_pack_start(GTK_BOX(contentArea), content_label, TRUE, TRUE, 0);
    DialogWidgets_btn *data = creerDialogWidgets_btn();

    //'bouton' est null çad qu'on va creer un nouveau bouton
    if(!bouton) {
        //Creation des inputs
        data->label = inputTexte("Label", cord(100, 100), contentArea, NULL);
        data->hasMnemonic = inputCheck("HasMnemonic", cord(100, 100), contentArea, TRUE);
        data->img = inputTexte("Image", cord(100, 100), contentArea, "");
        data->dimX = inputNumber("width", cord(100, 100), contentArea, 10, 10);
        data->dimY = inputNumber("height", cord(100, 100), contentArea, 10, 10);
        data->posX = inputNumber("x", cord(100, 100), contentArea, 10, 10);
        data->posY = inputNumber("y", cord(100, 100), contentArea, 10, 10);
        data->color = inputTexte("Color", cord(100, 100), contentArea, "");
        //data->police = inputTexte("Police", cord(100, 100), contentArea, "");
        data->taille = inputNumber("Taille", cord(100, 100), contentArea, 8, 1);
        data->gras = inputCheck("Gras", cord(100, 100), contentArea, FALSE);
        data->border = inputNumber("Border", cord(100, 100), contentArea, 0, 1);
        data->border_radius = inputNumber("Border Radius", cord(100, 100), contentArea, 0, 1);
        //data->margin
        data->isSensitive = inputCheck("isSensitive", cord(100, 100), contentArea, TRUE);
        //char *options[] = {"Red", "Blue", "Green", NULL};
        //data->align = inputCombo("Align", cord(100, 100), contentArea, options);
        //data->opacity = inputNumber("Opacité", cord(100, 100), contentArea, "1");
        data->bg = inputTexte("Background", cord(100, 100), contentArea, "");
        data->opacity = inputNumber("Opacité", cord(100, 100), contentArea, 1, 0.1);
        data->container = parent;
        data->bouton = NULL;
        char *polices[] = {
                "Arial", "Verdana", "Tahoma", "Times New Roman", "Georgia",
                "Calibri", "Cambria", "Courier New", "Consolas", "Trebuchet MS",
                "Segoe UI", "Lucida Sans Unicode", "Comic Sans MS", "Impact",
                "Palatino Linotype", "Gadugi", "Microsoft Sans Serif", NULL
        };
        data->police = inputCombo("Police", cord(100, 100), contentArea, polices);

    }
        //on va modifier un bouton existant
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
        data->container = parent;

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

//Creer le box
    boite = DIALOG(
            contentArea,//Contenu(un widget)
            titre,//titre
            dim(500, 200),//dimension
            icon, // Pas d'icône pour cet exemple
            parent,//Parent(conteneur)
            TRUE,//modal ou pas
            GTK_WIN_POS_CENTER//Position
    );
    creer_boite_dialogue(boite);
    if(bouton){
        //Ajouter bouton de suppression
        GtkWidget* delete = gtk_button_new_with_label("Supprimer");
        g_signal_connect(delete, "clicked", G_CALLBACK(deleteBtn), bouton->b->button);
        addActionWidget(boite, delete, GTK_RESPONSE_CLOSE);
    }
    //Ajouter des boutons
    GtkWidget *btnOk = gtk_button_new_with_label("Oui");
    addActionWidget(boite, btnOk, GTK_RESPONSE_OK);

    //Ajouter des boutons
    GtkWidget *btnAn = gtk_button_new_with_label("Annuler");
    addActionWidget(boite, btnAn, GTK_RESPONSE_CANCEL);
    //Associer un signal au boite
    g_signal_connect(boite->dialog, "response", G_CALLBACK(btnNormalePropertiesResponse), data);

}

#endif //XML_TAHA_BTN_PROJET_H
