//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_DIALOGUE_H
#define TEST1_DIALOGUE_H
#include "global.h"
#include "coordonnees.h"

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


//Traiter les réponses provenants du boite de dialogue
void dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    switch (response_id) {
        case GTK_RESPONSE_OK:
            g_print("\nOK cliqué\n");
            // Traitement pour OK
            break;

        case GTK_RESPONSE_CANCEL:
            g_print("\nAnnulation cliquée\n");
            gtk_widget_destroy(GTK_WIDGET(dialog));

            // Traitement pour Annuler
            break;

        case GTK_RESPONSE_NO:
            g_print("\nNon cliqué\n");
            // Traitement pour Non
            break;

        default:
            g_print("\nRéponse inattendue: %d\n", response_id);
            // Traitement par défaut
            break;
    }

    // Fermer la boîte de dialogue

    // Si besoin, accéder aux données utilisateur
    //MyData *data = (MyData *)user_data;
    // ... utilisation de data ...
}


void dialogue_template(char* titre, char* message, char* messageIcon, char* icon,
                       coordonnees c, GtkWidget* parent) {
    boite_dialog *boite = NULL;

// Le conteneur des widgets formant le contenue du dialogue (content area)
    GtkWidget *contentArea = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);  // Espacement de 10 pixels
// Ajoute 20 pixels de padding autour du contenu de la boîte(faire semblant que le box est centré)
    gtk_container_set_border_width(GTK_CONTAINER(contentArea), 50);
//Image
    MonImage *ima = init_image(messageIcon, *dim(48, 48), *cord(32, 32));
    creer_image(ima);
//Ajouter l'image au conteneur (contentArea)
    gtk_box_pack_start(GTK_BOX(contentArea), ima->Image, TRUE, TRUE, 0);
//Label
    GtkWidget *content_label = gtk_label_new(message);
//Ajouter le label(message) au conteneur (contentArea)
    gtk_box_pack_start(GTK_BOX(contentArea), content_label, TRUE, TRUE, 0);


//Creer le box
    boite = DIALOG_XY(
            contentArea,//Contenu(un widget)
            titre,//titre
            dim(200, 100),//dimension
            icon, // Pas d'icône pour cet exemple
            parent,//Parent(conteneur)
            TRUE,//modal ou pas
            cord(c.x, c.y)//Position
    );
    creer_boite_dialogue(boite);

    //Ajouter des boutons
    GtkWidget *btnOk = gtk_button_new_with_label("Oui");
    addActionWidget(boite, btnOk, GTK_RESPONSE_OK);

    //Ajouter des boutons
    GtkWidget *btnNon = gtk_button_new_with_label("Non");
    addActionWidget(boite, btnNon, GTK_RESPONSE_NO);

    //Ajouter des boutons
    GtkWidget *btnAn = gtk_button_new_with_label("Annuler");
    addActionWidget(boite, btnAn, GTK_RESPONSE_CANCEL);
    //Associer un signal au boite
    g_signal_connect(boite->dialog, "response", G_CALLBACK(dialog_response), NULL);

}











#endif //TEST1_DIALOGUE_H
