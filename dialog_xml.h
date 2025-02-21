//
// Created by Dell on 2/1/2025.
//

#ifndef XML_TAHA_DIALOG_XML_H
#define XML_TAHA_DIALOG_XML_H
#include <gtk/gtk.h>
#include "xml_utility.h"
#include "dialogue.h"
#include "colors.h"
//Traiter les réponses provenants du boite de dialogue
void dialog_response_callback(GtkDialog *dialog, gint response_id, gpointer user_data) {
    switch (response_id) {
        case GTK_RESPONSE_OK:
            g_print("\nOK cliqué\n");
            // Traitement pour OK
            break;

        case GTK_RESPONSE_CANCEL:
            g_print("\nAnnulation cliquée\n");
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
    gtk_widget_destroy(GTK_WIDGET(dialog));

    // Si besoin, accéder aux données utilisateur
    //MyData *data = (MyData *)user_data;
    // ... utilisation de data ...
}

//fct de creation de boite de dialog
void BoiteDialog_xml(FILE *file,int parent)
{
    HexColor *color=NULL;
    gchar *bgColor_gchar;
    char title_gchar[MAX], width[MAX], height[MAX], icon[MAX],
            iconMessage[MAX], message[MAX], x[MAX], y[MAX], label[256];
    //hexa_color *color=NULL;
    char modal;

    // Le conteneur des widgets formant le contenue du dialogue (content area)
    GtkWidget *contentArea = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);  // Espacement de 10 pixels
    // Ajoute 20 pixels de padding autour du contenu de la boîte(faire semblant que le box est centré)
    gtk_container_set_border_width(GTK_CONTAINER(contentArea), 50);

    GtkWidget *btnOk = NULL;
    GtkWidget *btnAnnuler = NULL;
    GtkWidget *btnNon = NULL;

    while((balise(file))==22)
    {
        char mot[MAX];
        int ind=0;

        Epeurerblanc(file);  // Ignorer les espaces blancs
        fseek(file, 6, SEEK_CUR);//Sauter le: name="
        fscanf(file, "%s", mot);//Lire le type de la propriété(text,icon,x,y...)
        if (!(strcmp("title\"", mot))) //recuperation du title
        {
            lire_gchar_str(file,title_gchar);
        }
        else if (!(strcmp("width\"", mot))) //recuperation de width
        {
            lire_gchar_str(file,width);
        }
        else if (!(strcmp("height\"", mot)))  //recuperation de height
        {
            lire_gchar_str(file,height);
        }//FIN if (!(strcmp("height\"", mot)))
        else if (!(strcmp("x\"", mot)))  //recuperation de x
        {
            lire_gchar_str(file,x);
        }
        else if (!(strcmp("y\"", mot))) //recupearation de y
        {
            lire_gchar_str(file,y);
        }
            /*
            if (!(strcmp("bgColor\"", mot)))  //recuperation de bgColor
            {
                char bgColor[MAX];
                lire_gchar_str(file,bgColor);
                bgColor_gchar = g_strdup(bgColor);
                color=init_hexa_color(color,bgColor_gchar);
                // Met à jour la couleur de fond de la fenêtre
                dialog->bgColor=*color;
            }//FIN if (!(strcmp("bgColor\"", mot)))
             */
        else if (!(strcmp("icon\"", mot)))
        {
            lire_gchar_str(file,icon);
        }
        else if (!(strcmp("modal\"", mot)))
        {
            modal=lire_gchar(file);
        }
        else if (!(strcmp("message\"", mot)))
        {
            //Récuperer le message
            lire_gchar_str(file,message);
            //Creer le label
            GtkWidget *content_label = gtk_label_new(message);
            //Ajouter le label(message) au conteneur (contentArea)
            gtk_box_pack_start(GTK_BOX(contentArea), content_label, TRUE, TRUE, 0);

        }
            //Ajouter une image au message
        else if (!(strcmp("iconMessage\"", mot)))
        {
            //Récuperer le path de l'image
            lire_gchar_str(file,iconMessage);
            //Creer l'image
            MonImage* ima = init_image(iconMessage,*dim(48,48), *cord(32,32));
            creer_image(ima);
            //Ajouter l'image au conteneur (contentArea)
            gtk_box_pack_start(GTK_BOX(contentArea), ima->Image, TRUE, TRUE, 0);
        }

        if (!(strcmp("bgColor\"", mot)))  //recuperation de bgColor
        {
            char bgColor[MAX];
            lire_gchar_str(file,bgColor);
            color=hex_color_init(bgColor);
        }//FIN if (!(strcmp("bgColor\"", mot)))


        //Les boutons de l'actionArea (btnOk pour OK, btnAnnuler pour Cancel et btnNon pour NO)
        else if (!(strcmp("btnOk\"", mot)))
        {
            //Récuperer le label du bouton
            lire_gchar_str(file,label);
            //Creer le bouton
            btnOk = gtk_button_new_with_label(label);
            //Ajuster la marge pour le bouton
            gtk_widget_set_margin_start(btnOk, 16);
            gtk_widget_set_margin_end(btnOk, 16);
        }
        else if (!(strcmp("btnAnnuler\"", mot)))
        {
            //Récuperer le label du bouton
            lire_gchar_str(file,label);
            //Creer le bouton
            btnAnnuler = gtk_button_new_with_label(label);
            //Ajuster la marge pour le bouton
            gtk_widget_set_margin_start(btnAnnuler, 16);
            gtk_widget_set_margin_end(btnAnnuler, 16);
        }
        else if (!(strcmp("btnNon\"", mot)))
        {
            //Récuperer le label du bouton
            lire_gchar_str(file,label);
            //Creer le bouton
            btnNon = gtk_button_new_with_label(label);
            //Ajuster la marge pour le bouton
            gtk_widget_set_margin_start(btnNon, 16);
            gtk_widget_set_margin_end(btnNon, 16);
        }
    }//FIN while((test=balise(file))==22)

    boite_dialog *boite = NULL;
    //Si le parent est fixed
    if(parent == 2) {
        //Initier le dialogue
        boite = DIALOG_XY(
                contentArea,//Contenu(un widget)
                title_gchar,//titre
                dim(atoi(width), atoi(height)),//dimension
                icon, // Pas d'icône pour cet exemple
                parents[parent],//Parent(conteneur)
                char_TO_int(modal),//modal ou pas
                cord(atoi(x), atoi(y))//Position
        );
    }
        //Si le parent n'est pas fixed
    else{
        boite = DIALOG(
                contentArea,//Contenu(un widget)
                title_gchar,//titre
                dim(atoi(width), atoi(height)),//dimension
                icon, // Pas d'icône pour cet exemple
                parents[parent],//Parent(conteneur)
                char_TO_int(modal),//modal ou pas
                GTK_WIN_POS_CENTER_ON_PARENT//Position
        );
    }

    //Creer la boite
    creer_boite_dialogue(boite);
    //Ajouter le background color s'il existe
    if(color)
        gtk_widget_override_background_color(boite->dialog, GTK_STATE_FLAG_NORMAL,
                                             color->color);
    //Ajouter les bouton au actionArea s'ils existent
    if(btnOk )
        addActionWidget(boite, btnOk, GTK_RESPONSE_OK);
    if(btnAnnuler)
        addActionWidget(boite, btnAnnuler, GTK_RESPONSE_CANCEL);
    if(btnNon)
        addActionWidget(boite, btnNon, GTK_RESPONSE_NO);


    //Associer un signal au boite
    g_signal_connect(boite->dialog, "response", G_CALLBACK(dialog_response_callback), NULL);
    //Traiter les autres balises
    creer_object(file,parent);
}//FIN fonction BoiteDialog_xml

#endif //XML_TAHA_DIALOG_XML_H
