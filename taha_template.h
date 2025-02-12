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

void menu(fixedo* fixed){

    ////////////////////////////////////---menu---///////////////////////////////////////////////////////
    // Créer une barre de menu(container)
    MenuBar *menu_bar = creer_menu_bar();

    //Creer un menu (Mon choix)
    {
        // Créer un menu "Fichier"
        Menu *menu_fichier = creer_menu();
        //Les items(options) du menu
        //ajouter_element_au_menu(menu_fichier, "Ouvrir", G_CALLBACK(on_menu_item_activate));
        //ajouter_element_au_menu(menu_fichier, "Enregistrer", G_CALLBACK(on_menu_item_activate));

        //Ajouter un item au menu (Souschoix1)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix1");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix111", "choix112", "choix113", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix2)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix2");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix121", "choix122", "choix123", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix3)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix3");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix131", "choix132", "choix133", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter le menu au container
        ajouter_menu_a_barre(menu_bar, "Ordianateur", menu_fichier);
    }

    //Creer un menu (Votre choix)
    {
        // Créer un menu "Fichier"
        Menu *menu_fichier = creer_menu();
        //Les items(options) du menu
        //ajouter_element_au_menu(menu_fichier, "Ouvrir", G_CALLBACK(on_menu_item_activate));
        //ajouter_element_au_menu(menu_fichier, "Enregistrer", G_CALLBACK(on_menu_item_activate));

        //Ajouter un item au menu (Souschoix1)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Marque");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix211", "choix212", "choix213", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix2)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Puissance");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"Processor", "Vitesse", "Dique Dur", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix3)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Prix");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix231", "choix232", "choix233", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter le menu au container
        ajouter_menu_a_barre(menu_bar, "Portable", menu_fichier);
    }

    //Creer un menu (Leur choix)
    {
        // Créer un menu "Fichier"
        Menu *menu_fichier = creer_menu();

        //Ajouter un item au menu (Souschoix1)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix1");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix311", "choix312", "choix313", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix2)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix2");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix321", "choix322", "choix323", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter un item au menu (Souschoix3)
        {
            GtkWidget *item_options = gtk_menu_item_new_with_label(
                    "Souschoix3");//Cet item sera le parent d'un sous menu
            //Ajouter des items au sous menu ("Options")
            {
                //Creer un sous menu
                char *options[256] = {"choix331", "choix332", "choix333", NULL};
                GtkWidget *sous_menu = creer_sous_menu(options);
                //Maintenant le sous menu va etre afficher si on hover sur "Options"
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_options), sous_menu);
            }
            //Ajouter l'item "Options" (le pere du sous menu) dans le menu
            gtk_menu_shell_append(GTK_MENU_SHELL(menu_fichier->menu), item_options);

        }

        //Ajouter le menu au container
        ajouter_menu_a_barre(menu_bar, "Ecouteur", menu_fichier);
    }

    /*
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

    fixed_add_widget(fixed,menu_bar->menu_bar,0,0);

}