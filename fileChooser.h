//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_FILECHOOSER_H
#define TEST1_FILECHOOSER_H
#include "global.h"




/**************************************
 * NOM: fChooserOpen, fChooserSave, fChooserSelectFolder, fChooserCreateFolder.
 * ENTRÉS: title (gchar*): Le titre de la boîte.
 *         dim (dimension*): Les dimensions de la boîte.
 *         icon (gchar*): L'icône associée à la boîte.
 *         pere (GtkWidget*): Le widget parent.
 * SORTIS: void.
 * DESCRIPTION: Ces macros créent un 'fileChooser' en fonction de l'action désirée :
 *              - fChooserOpen : Ouvrir un fichier.
 *              - fChooserSave : Enregistrer un fichier.
 *              - fChooserSelectFolder : Sélectionner un dossier.
 *              - fChooserCreateFolder : Créer un dossier.
 *              !: Ces macros ignore plusieurs parametres, et prennent juste ceux
 *              qu'on va travailler avec, mais en cas de besoin on peut
 *              creer d'autres qui permettent plus de fléxibilité.
***************************************/

#define fChooserOpen(title, dim, icon, pere) \
                init_fchooser(title, dim,icon, GTK_WIDGET(pere), TRUE, FALSE,\
                GTK_WIN_POS_CENTER, pos(0, 250),GTK_FILE_CHOOSER_ACTION_OPEN,\
                TRUE, NULL, NULL, NULL)
#define fChooserSave(title, dim, icon, pere) \
                init_fchooser(title, dim,icon, GTK_WIDGET(pere), TRUE, FALSE,\
                GTK_WIN_POS_CENTER, pos(0, 250),GTK_FILE_CHOOSER_ACTION_SAVE,\
                TRUE, NULL, NULL, NULL)
#define fChooserSelectFolder(title, dim, icon, pere) \
                init_fchooser(title, dim,icon, GTK_WIDGET(pere), TRUE, FALSE,\
                GTK_WIN_POS_CENTER, pos(0, 250),GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,\
                TRUE, NULL, NULL, NULL)
#define fChooserCreateFolder(title, dim, icon, pere) \
                init_fchooser(title, dim,icon, GTK_WIDGET(pere), TRUE, FALSE,\
                GTK_WIN_POS_CENTER, pos(0, 250),GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,\
                TRUE, NULL, NULL, NULL)

//La structure representant un file chooser.
//Vue que le file chooser et le dialogue possédent plusieurs propriétés communes
// on a décidé de l'ajouter comme un attribut du filechooser (c'est comme une sorte
// d'héritage).
typedef struct fileChooser{
    //La boite de dialogue
    boite_dialog* bg;
    //L'action que le filechooser va performer(ouvrir un fichier existant
    // ou enregistrer dans un nouveau fichier).
    GtkFileChooserAction action;
    //Peut on choisir plusieurs fichiers ou pas?.
    gboolean acceptMutli;
    //Le répertoire courant de selection.
    gchar repertoireInitial[256];
    //Le premier bouton du fileChooser, permet soit d'ouvrir, d'enregistrer,
    // choisir dossier, creer dossier(ça depend des valeurs de 'action').
    GtkWidget* openBtn;
    //Le deuxieme bouton qui permet d'annuler la selection.
    GtkWidget* closeBtn;

}fileChooser;

/**************************************
 * NOM: allocate_fchooser.
 * ENTRÉS: void.
 * SORTIS: un pointeur vers un 'objet' de type 'fileChooser'.
 * DESCRIPTION: Allouer l'espace mémoire pour une boite de dialogue de type 'fileChooser' et le retourner.
 *              En cas d'échec d'allocation on sort du programme avec un message d'erreur.
***************************************/
fileChooser* allocate_fchooser(){
    //Allouer le filechooser
    fileChooser* fc=(fileChooser*) malloc(sizeof(fileChooser));
    //Sortir avec un message d'erreur si l'allocation échoue
    if(!fc){
        printf("Erreur d'allocation dans allocate_fchooser()\n");
        exit(-1);
    }
    //Retourner la boite
    return (fileChooser*)fc;
}

/**************************************
 * NOM: init_fchooser.
 * ENTRÉS: title (gchar[MAX_LENGTH]): Le titre de la boîte de dialogue.
 *         dim (dimension*): Les dimensions de la boîte de dialogue.
 *         icon (gchar[MAX_LENGTH]): L'icône associée à la boîte.
 *         pere (GtkWidget*): Le widget parent de la boîte de dialogue.
 *         isModal (gboolean): Indique si la boîte est modale.
 *         hasXY (gboolean): Indique si la boîte a une position fixe.
 *         wpos (GtkWindowPosition): La position de la boîte.
 *         xyPos (Position*): La position fixe si applicable.
 *         action (GtkFileChooserAction): L'action associée au FileChooser.
 *         acceptMutli (gboolean): Permet la sélection multiple ou non.
 *         repertoireInitial (gchar[256]): Le répertoire initial.
 *         openBtn (GtkWidget*): Le bouton principal (Ouvrir, Enregistrer...).
 *         closeBtn (GtkWidget*): Le bouton d'annulation.
 * SORTIS: Un pointeur vers une structure 'fileChooser'.
 * DESCRIPTION: Initialise et retourne une structure de type 'fileChooser' avec les paramètres spécifiés.
***************************************/

fileChooser* init_fchooser(gchar title[MAX_LENGTH],
                           dimension* dim,gchar icon[MAX_LENGTH],
                           GtkWidget* pere, gboolean isModal,
                           gboolean hasXY,GtkWindowPosition wpos,
                           coordonnees *xyPos,GtkFileChooserAction action,
                           gboolean acceptMutli, gchar repertoireInitial[256],
                           GtkWidget* openBtn, GtkWidget* closeBtn ){
    //Allouer le file chooser
    fileChooser* fc = allocate_fchooser();
    //Initialiser la boite de dialogue contenu dans le file chooser
    fc->bg = init_boite_dialog(NULL, title, dim,
                               icon, pere, isModal,
                               hasXY, wpos, xyPos);
    //Initier l'action
    fc->action = action;
    //Est ce que le filechooser permet de choisir plusieurs fichiers
    fc->acceptMutli = acceptMutli;
    //Le repertoire initial de selection des fichiers
    fc->repertoireInitial[0] = '\0';//Initialisation
    //Si le repertoire entré n'est pas null alors le copier
    if(repertoireInitial){
        strcpy(fc->repertoireInitial, repertoireInitial);
    }
    //Assigner les boutons du filechooser
    fc->openBtn = openBtn;
    fc->closeBtn = closeBtn;
    //Retourner le filechooser apres initialisation
    return (fileChooser*) fc;
}

/**************************************
 * NOM: creerFchooser.
 * ENTRÉS: fc (fileChooser*): Une structure 'fileChooser' à initialiser.
 * SORTIS: void.
 * DESCRIPTION: + Initialise et configure un 'GtkFileChooserDialog' basé sur les paramètres de la structure 'fileChooser'.
 *              + Ajoute les boutons nécessaires (action et annulation).
 *              + Définit les propriétés telles que le répertoire initial et la sélection multiple.
 *              + La fonction sort du programme si la structure 'fileChooser' est NULL.
***************************************/
void creerFchooser(fileChooser* fc){
    //Structure vide
    if(!fc){
        printf("La structure du filechooser n'existe pas.\n");
        exit(-1);
    }
    //Création du dialogue
    fc->bg->dialog= gtk_file_chooser_dialog_new(NULL, NULL, fc->action, NULL);
    //Ajuster les caractéristiques du dialogue(dimension, position...)
    ajusterDialogue(fc->bg);
    //Définir le repertoire de selection initial
    if(fc->repertoireInitial[0] != '\0'){
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(fc->bg->dialog), fc->repertoireInitial);
    }
    //Ajouter la possibilité de selectionner plusieurs fichiers ou pas.
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(fc->bg->dialog), fc->acceptMutli);
    //Ajouter les boutons nécessaires
    //Si le premier bouton (le bouton d'action) est fourni alors l'associer au fileChooser
    if(fc->openBtn != NULL){
        addActionWidget(fc->bg, fc->openBtn, fc->action);
    }
        //S'il est null alors fournir un bouton par défaut selon l'action désiré,
        //ça permet de simplifier le callback de réponse associé au filechooser
    else{
        GtkWidget *custom_button;
        switch (fc->action) {
            //S'il s'agit d'une action d'ouverture alors le label du bouton sera 'open'.
            case GTK_FILE_CHOOSER_ACTION_OPEN:
                custom_button = gtk_button_new_with_label("Open");
                break;
                //S'il s'agit d'une action d'enregistrement alors le label du bouton sera 'Save'.
            case GTK_FILE_CHOOSER_ACTION_SAVE:
                custom_button = gtk_button_new_with_label("Save");
                break;
                //S'il s'agit d'une action de creation d'un dossier.
            case GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER:
                custom_button = gtk_button_new_with_label("Creer dossier");
                break;
                //S'il s'agit d'une action de selection d'un dossier.
            case GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER:
                custom_button = gtk_button_new_with_label("Selectioner dossier");
                break;
        }
        //Ajouter le bouton correspondant
        addActionWidget(fc->bg, custom_button, fc->action);
    }
    //Ajouter le bouton d'annulation s'il est non null
    if(fc->closeBtn != NULL){
        addActionWidget(fc->bg, fc->closeBtn, GTK_RESPONSE_CANCEL);
    }
        //Ajouter un bouton d'annulation par défaut s'il est null
    else{
        GtkWidget *annulerBtn = gtk_button_new_with_label("Annuler");
        addActionWidget(fc->bg, annulerBtn, GTK_RESPONSE_CANCEL);

    }
}


/**************************************
 * NOM: addFChooserFilter.
 * ENTRÉS: fc (fileChooser*): Une structure 'fileChooser'.
 *         filterName (gchar*): Le nom du filtre.
 *         mimeType (gchar*): Le type MIME à filtrer (ex.: image/png, text/plain).
 * SORTIS: void.
 * DESCRIPTION: + Ajoute un filtre au 'GtkFileChooser' en fonction du nom et du type MIME spécifiés.
 *              + La fonction doit être appelée après la création du fileChooser avec 'creerFchooser'.
***************************************/
void addFChooserFilter(fileChooser* fc, gchar* filterName, gchar* mimeType){
    if(filterName && mimeType){
        GtkFileFilter *filter = gtk_file_filter_new();//Creer un nouveau filtre
        gtk_file_filter_set_name(filter, filterName);//Assigner un nom au filtre
        gtk_file_filter_add_mime_type(filter, mimeType);//Filtrer par un mimetype(image/png, text/plain,...)
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fc->bg->dialog), filter);//Ajouter le filtre au filechooser
    }
}






#endif //TEST1_FILECHOOSER_H
