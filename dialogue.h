//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_DIALOGUE_H
#define TEST1_DIALOGUE_H
#include "global.h"
#include "coordonnees.h"

GtkWidget* inputTexte(char* label, coordonnees* cord, GtkWidget* container, char* defaultTexte);
GtkWidget* inputNumber(char* label, coordonnees* cord, GtkWidget* container,char* defaultNum);
GtkWidget* inputCheck(char* label, coordonnees* cord, GtkWidget* container, gboolean isChecked);
GtkWidget* inputCombo(char* label, coordonnees* cord, GtkWidget* container,char* items[256]);
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
    GtkWidget*  police;
    GtkWidget*  taille;
    GtkWidget*  gras;
    GtkWidget*  border;
    GtkWidget*  border_radius;
} DialogWidgets_btn;

DialogWidgets_btn* creerDialogWidgets(){
    DialogWidgets_btn* data = (DialogWidgets_btn*) malloc(sizeof(DialogWidgets_btn));
    if(!data){
        perror("Erreur d'allocation de DialogWidgets");
        exit(-1);
    }
    return data;
}
/*********MACROS**********/
//Définir un macro qui crée une boite de dialogue qui se positionne selon une position
// de l'enumeration: GtkWindowPosition
#define DIALOG(contentArea, title, dim, iconPath, parent_window, isModal,GTK_WIN_POSITION) \
                           init_boite_dialog(contentArea, title, dim,iconPath, \
                            parent_window,isModal, FALSE,GTK_WIN_POSITION, NULL)
//Definir un dialog qui se positionne selon des coordonnées x et y
#define DIALOG_XY(contentArea, title, dim, iconPath, parent_window, isModal, pos) \
                            init_boite_dialog(contentArea, title, dim,iconPath, \
                            parent_window,isModal, TRUE,GTK_WIN_POS_CENTER_ON_PARENT, pos)

/************************/



//Structure définissant une boite de dialogue contenant ainsi les
//attributs nécessaires pour la personnaliser.
typedef struct boite_dialog{
    GtkWidget* dialog;
    GtkWidget* contentArea;//Nécessaire pour ajouter du contenu au dialogue(texte,image,...),i.e. ensemble de widgets
    dimension *dim;//La dimension du dialogue
    gchar icon[MAX_LENGTH];//Le path de l'icon
    gchar title[MAX_LENGTH];//Titre de dialgue
    gboolean hasXY;//Si true alors la position sera définie par des cordonnés
    // sinon ça sera une position prédefinie (wpos)
    GtkWindowPosition wpos;//Position de dialogue (une position prédefinie, voir GtkWindowPosition)
    coordonnees *xyPos;//Position selon les cordonnées.
    GtkWidget* pere;//Le père du dialogue
    gboolean isModal;//Si modal(la boite ne permet pas l'interaction avec
    //d'autres windows ) ou pas.

}boite_dialog;

/**************************************
 * NOM: allocate_boite_dialog.
 * ENTRÉS: void.
 * SORTIS: un pointeur vers un 'objet' de type 'boite_dialog'.
 * DESCRIPTION: Allouer l'espace mémoire pour une boite de dialogue de type 'boite_dialog' et le retourner.
 *              En cas d'échec d'allocation on sort du programme avec un message d'erreur.
***************************************/
boite_dialog* allocate_boite_dialog(){
    //Allouer la boite
    boite_dialog* bg=(boite_dialog*) malloc(sizeof(boite_dialog));
    //Sortir avec un message d'erreur si l'allocation échoue
    if(!bg){
        printf("Erreur d'allocation dans allocate_boite_dialog()\n");
        exit(-1);
    }
    //Retourner la boite
    return (boite_dialog*)bg;
}

/**************************************
 * NOM: init_boite_dialog.
 * ENTRÉS:  GtkWidget* contentArea: le contenu du dialogue( un widget qui regroupe le contenu(texte,img...) )
 *          gchar title[MAX_LENGTH]: le titre de boite de dialogue.
 *          dimension* dim: La hauteur et largeur de la boite.
 *          gchar icon[MAX_LENGTH]: le path de l'icon de la boite.
            GtkWindow* pere: La fenetre où la boite est attachée.
            gboolean isModal: boolean indiquant si la boite va empecher l'interaction avec d'autres fenetres.
            gboolean hasXY: boolean indiquant si la position est définie par des cordonnées ou pas.
            GtkWindowPosition wpos: La position de la fenetre .
            Position *xyPos;//Position selon les cordonnées.
 * SORTIS: un pointeur vers un 'objet' de type 'boite_dialog'.
 * DESCRIPTION: Allouer l'espace mémoire pour une boite de dialogue de type 'boite_dialog' .
 *              Initier les champs de la boite avec les parametres passées.
 *              Donner une valeur par défaut(DEFAULT_DIALOG_DIM) à la dimension en cas de son abscence .
 *              Retourner la boite après initialisation.
***************************************/
boite_dialog* init_boite_dialog(GtkWidget* contentArea,gchar title[MAX_LENGTH], dimension* dim,
                                gchar icon[MAX_LENGTH],GtkWidget* pere, gboolean isModal,
                                gboolean hasXY,GtkWindowPosition wpos, coordonnees *xyPos){
    //Allocation de la boite
    boite_dialog* bg=allocate_boite_dialog();
    //Initialisation
    bg->contentArea=contentArea;//Pointer sur le contentArea
    //Initilasier le titre et le path de l'icon
    bg->title[0] = '\0';
    bg->icon[0] = '\0';
    //Copier le titre et le path de l'icon s'ils sont non null
    if(title)
        strcpy(bg->title, title);//Copier le titre
    if(icon)
        strcpy(bg->icon, icon);//Copier le path de l'icon
    bg->isModal=isModal;//Modal ou pas
    bg->pere=pere;//Assigner le pere du dialog
    //Copier la dimension si elle est non null
    if(dim){
        bg->dim=dim;
    }
        //Donner une valeur par défaut en cas d'abscence de dimension
    else{
        bg->dim=dim(64, 64);
    }
    //Copier le type de position
    bg->hasXY=hasXY;
    //Copier la position prédefine
    bg->wpos=wpos;

    //Copier la position basée sur les coordonnées si elle existe, ou la donner une par défaut sinon
    if(xyPos){
        //Copier les cordonnées
        bg->xyPos=xyPos;
    }
    else{
        //Définir des coordonnées par défaut(x=0,y=0)
        bg->xyPos=cord(0,0);
    }
    //Retourner le dialog
    return (boite_dialog*) bg;
}

/**************************************
 * NOM: ajusterDialogue.
 * ENTRÉS: boite_dialog* bg: une boîte de dialogue à ajuster.
 * SORTIS: void.
 * DESCRIPTION: + Ajuste les caractéristiques d'une boîte de dialogue, y compris le titre,
 *                l'icône, la position, la dimension, et le mode modal.
 *              + Sort du programme si la structure passée est NULL.
***************************************/
void ajusterDialogue(boite_dialog* bg){
    //Structure vide
    if(!bg){
        printf("La structure de dialog n'existe pas.\n");
        exit(-1);
    }
    //Ajouter le titre
    if(bg->title[0] != '\0')
        gtk_window_set_title(GTK_WINDOW(bg->dialog), bg->title);
    //Ajouter la dimension par défaut
    //gtk_window_set_default_size(GTK_WINDOW(bg->dialog), bg->dim->width, bg->dim->height);
    //Ajouter l'icon
    if(bg->icon[0] != '\0')
        gtk_window_set_icon_from_file(GTK_WINDOW(bg->dialog), bg->icon, NULL);
    //Ajuster la position
    if(bg->hasXY)
        //Positionner selon les coordonnées.
        gtk_window_move(GTK_WINDOW(bg->dialog), bg->xyPos->x, bg->xyPos->y);
    else
        //Positionner selon les valeurs de l'enum GTKWINDOWPOSITION.
        gtk_window_set_position(GTK_WINDOW(bg->dialog), bg->wpos);

    //Définir le père
    gtk_window_set_transient_for(GTK_WINDOW(bg->dialog), GTK_WINDOW(bg->pere));
    //Modal ou pas
    gtk_window_set_modal(GTK_WINDOW(bg->dialog), bg->isModal);
    //Afficher le dialog
    gtk_widget_show_all(bg->dialog);
    //Parfois en se trouve avec des cas ou dès qu'on redimonsionne le dialogue
    //avec la souris, il garde ces dimensions meme si on change ces derniers dans
    //le programme donc on a fait recours à la fonction de gtk_widget_resize, l'appel
    //de cette fonction doit être après l'affichage du dialogue(show_all)
    gtk_window_resize(GTK_WINDOW(bg->dialog), bg->dim->width, bg->dim->height);
}




/**************************************
 * NOM: creer_boite_dialogue.
 * ENTRÉS: boite_dialog* bg: une boite de dialogue passé par adresse
 * SORTIS: void
 * DESCRIPTION: +La fonction crée une boite de dialogue et la personnalise selon les
 *                 champs(attributs) du dialogue(boite_dialog* bg) passé.
 *              +On sort du programme si le pointeur passé est NULL.
***************************************/
void creer_boite_dialogue(boite_dialog* bg){
    //Structure vide
    if(!bg){
        printf("La structure de dialog n'existe pas.\n");
        exit(-1);
    }
    //Création du dialogue
    bg->dialog= gtk_dialog_new();
    //Définir le content area
    GtkWidget* contentArea=gtk_dialog_get_content_area(GTK_DIALOG(bg->dialog));
    //Ajouter le widget(s) au content area du dialog
    gtk_container_add(GTK_CONTAINER(contentArea),bg->contentArea);
    gtk_widget_show_all(bg->contentArea);//Afficher le content area
    //Ajuster les caractéristiques du dialogue(dimension, position...)
    ajusterDialogue(bg);
}

/**************************************
 * NOM: addToContentArea.
 * ENTRÉS: boite_dialog* bg: une boite de dialogue passé par adresse
 *         GtkWidget* widget: Le widget qu'on souhaite ajouter à la zone de contenu.
 * SORTIS: void
 * DESCRIPTION: +La fonction ajoute un widget passé en parametre au content area d'un dialogue passé
 *              en parametre et l'affiche .
 *              +Sort du programme si les pointeurs passés sont NULL.
***************************************/
void addToContentArea(boite_dialog* bg, GtkWidget* widget)
{
    if(!bg || !widget){
        g_warning("La boite_dialog ou le widget est NULL, dans addToContentArea\n");
        exit(-1);
    }
    if(!(bg->dialog)){
        g_warning("Le dialog est NULL, dans addToContentArea\n");
        exit(-2);
    }
    //Grabber le content area du dialogue
    GtkWidget* contentArea=gtk_dialog_get_content_area(GTK_DIALOG(bg->dialog));
    //Ajouter le widget(s) au content area du dialog
    gtk_container_add(GTK_CONTAINER(contentArea),widget);
    //Afficher le widget recemment ajouté
    //gtk_widget_show(widget);
    gtk_widget_show_all(bg->dialog);

}

//!IMPORTANT NOTE: Un widget ne peut pas etre à la fois associé au "content area" et au "action area".
//Il est ainsi recommendé de regrouper vos widgets dans un seul conteneur box et de passer
//le box comme argument de la fonction.

/**************************************
 * NOM: addActionWidget.
 * ENTRÉS: boite_dialog* bg: une boite de dialogue passé par adresse.
 *         GtkWidget* widget: Le widget qu'on souhaite ajouter à la zone des actions.
 *         GtkResponseType res: enumération de type GtkResponseType indiquant le type
 *                              de réponse associé à ce widget.
 * SORTIS: void
 * DESCRIPTION: +La fonction ajoute un widget passé en parametre au actions area d'un dialogue passé
 *              en parametre et l'affiche .
 *              +Sort du programme si les pointeurs passés sont NULL.
***************************************/
void addActionWidget(boite_dialog* bg, GtkWidget* widget, GtkResponseType res){
    boite_dialog* this=bg;
    if(!this || ! widget){
        g_warning("Boite de dialogue ou widget NULLs dans addActionWidget\n");
        exit(-1);
    }
    //Ajouter l'action au dialogue
    gtk_dialog_add_action_widget(GTK_DIALOG(this->dialog), GTK_WIDGET(widget), res);
    //Afficher le dialog et ses composants
    gtk_widget_show_all(this->dialog);
}


/***TEST PHASE***/
void free_boite_dialog(boite_dialog* bg) {
    if (bg) {
        gtk_widget_destroy(bg->dialog); // Important pour libérer les ressources
        free(bg);
    }
}

void btnNormaleModify(GtkWidget* widget, gpointer* data){
    btn* b = (btn*) data;
    g_print("%s", b->label);
}

//Traiter les réponses provenants du boite de dialogue(nice)
void dialog_response(GtkDialog *dialog, gint response_id, gpointer *user_data) {
    //Creer la boite de creation d'un bouton normale
    if (response_id == GTK_RESPONSE_OK) {
        //Cast
        DialogWidgets_btn* data = (DialogWidgets_btn*) user_data;
        //Get widgets data
        const gchar *label = gtk_entry_get_text(GTK_ENTRY(data->label));
        gboolean hasMnemonic = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->hasMnemonic));
        const gchar *img = gtk_entry_get_text(GTK_ENTRY(data->img));
        const gchar *width = gtk_entry_get_text(GTK_ENTRY(data->dimX));
        const gchar *height = gtk_entry_get_text(GTK_ENTRY(data->dimY));
        const gchar *x = gtk_entry_get_text(GTK_ENTRY(data->posX));
        const gchar *y = gtk_entry_get_text(GTK_ENTRY(data->posY));
        const gchar *color = gtk_entry_get_text(GTK_ENTRY(data->color));
        const gchar *police = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->police));
        const gchar *taille = gtk_entry_get_text(GTK_ENTRY(data->taille));
        gboolean gras = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->gras));
        //bgcolor
        const gchar *border = gtk_entry_get_text(GTK_ENTRY(data->border));
        const gchar *border_radius = gtk_entry_get_text(GTK_ENTRY(data->border_radius));

        //data->margin
        gboolean isSensitive = 1;//Le bouton est sensible par défaut
        isSensitive = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->isSensitive));
        const gchar *align = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->align));
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



        btn* b = initBtn(NORMAL, label, label, hasMnemonic, label, ima,
                         dim(atoi(width), atoi(height)),
                         isFixed, cord(atoi(x), atoi(y)), NULL, isSensitive,
                         container, NULL, GTK_ALIGN_CENTER,
                         atoi(opacite), isChecked, NULL);
        creer_button(b);
        //Creer le style
        HexColor* h = hex_color_init(color);
        Style* style = init_style(police, h, atoi(taille),
                                  gras, "", atoi(border),
                                  atoi(border_radius));
        appliquer_style_button(style, b);

        //Ajouter le callback permettant la modification du bouton
        g_signal_connect(b->button, "clicked", G_CALLBACK(btnNormaleModify), b);

        //Show all
        gtk_widget_show_all(container);
    }
    else if(response_id == GTK_RESPONSE_CANCEL) {
        gtk_widget_destroy(GTK_WIDGET(dialog));
    }

    // Fermer la boîte de dialogue
}


void btnNormaleProperties(char* titre, char* message, char* messageIcon, char* icon,
                       coordonnees c, GtkWidget* parent) {
    boite_dialog *boite = NULL;

// Le conteneur des widgets formant le contenue du dialogue (content area)
    GtkWidget *contentArea = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);  // Espacement de 10 pixels
// Ajoute 20 pixels de padding autour du contenu de la boîte(faire semblant que le box est centré)
    gtk_container_set_border_width(GTK_CONTAINER(contentArea), 24);
//Label
    GtkWidget *content_label = gtk_label_new(message);
//Ajouter le label(message) au conteneur (contentArea)
    gtk_box_pack_start(GTK_BOX(contentArea), content_label, TRUE, TRUE, 0);


    //Creation des inputs
    DialogWidgets_btn *data = creerDialogWidgets();
    data->label = inputTexte("Label", cord(100, 100), contentArea, NULL);
    data->hasMnemonic = inputCheck("HasMnemonic", cord(100, 100), contentArea, TRUE);
    data->img = inputTexte("Image", cord(100, 100), contentArea, "");
    data->dimX = inputNumber("width", cord(100, 100), contentArea, "10");
    data->dimY = inputNumber("height", cord(100, 100), contentArea, "10");
    data->posX = inputNumber("x", cord(100, 100), contentArea, "10");
    data->posY = inputNumber("y", cord(100, 100), contentArea, "10");
    data->color = inputTexte("Color", cord(100, 100), contentArea, "");
    data->police = inputTexte("Police", cord(100, 100), contentArea, "");
    data->taille = inputNumber("Taille", cord(100, 100), contentArea, "8");
    data->gras = inputCheck("Gras", cord(100, 100), contentArea, FALSE);
    data->border = inputNumber("Border", cord(100, 100), contentArea,"");
    data->border_radius = inputNumber("Border Radius", cord(100, 100), contentArea, "0");
    //data->margin
    data->isSensitive = inputCheck("isSensitive", cord(100, 100), contentArea, TRUE);
    char* options[] = {"Red", "Blue", "Green", NULL};
    data->align = inputCombo("Color", cord(100, 100), contentArea, options);
    data->opacity = inputNumber("Opacité", cord(100, 100), contentArea, "1");
    data->container = parent;


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

    //Ajouter des boutons
    GtkWidget *btnOk = gtk_button_new_with_label("Oui");
    addActionWidget(boite, btnOk, GTK_RESPONSE_OK);

    //Ajouter des boutons
    GtkWidget *btnAn = gtk_button_new_with_label("Annuler");
    addActionWidget(boite, btnAn, GTK_RESPONSE_CANCEL);
    //Associer un signal au boite
    g_signal_connect(boite->dialog, "response", G_CALLBACK(dialog_response), data);

}











#endif //TEST1_DIALOGUE_H
