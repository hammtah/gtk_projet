//
// Created by Dell on 2/11/2025.
//

#ifndef XML_TAHA_MENU_XML_H
#define XML_TAHA_MENU_XML_H

#include <gtk/gtk.h>
#include "button.h"
#include "xml_utility.h"
#define MAX 40

typedef struct sp
{
    Menu *parent;/* l'élement de la liste */
    struct sp *svt; /* poiteur sur l'élement au suivant */
}subPile;

//
subPile *Creer_Cellule(Menu *parent)
{
    subPile *NE;
    /* Allouer la mémoire pour NE */
    NE=(subPile*) malloc(sizeof (subPile));
    if(!NE)/*L'allocation est mal passé */
    {
        /* Afficher un message d'errreur */
        printf("\nErreur d allocation du memoire.");
        /*Sortir du programme */
        exit(-1);
    }
    /* Ajouter l'élément */
    NE->parent=parent;
    /* Indiquer que le noueud crée n'a pas de séccessur */
    NE->svt=NULL;
    return ((subPile*)NE);/* Recupérere le noeud cré */
}


int Est_Vide_subPile(subPile *mapile)
{
    return ((int)(mapile==NULL));
}

subPile *Vider_subPile(subPile *mapile)
{
    subPile *tmp;
    // Utilisation d'une boucle pour parcourir la liste
    while (mapile)
    {
        tmp = mapile; // Stockage du pointeur vers le nœud actuel dans tmp
        mapile = mapile->svt; /* Mise à jour du pointeur Liste pour passer
		au nœud suivant*/
        free(tmp); // Libération de la mémoire occupée par le nœud actuel
    }
    // À la fin, Liste est NULL, indiquant que la liste est vidée
    return ((subPile*)mapile);
}

subPile *Empiler(subPile *mapile,  Menu *parent)
{
    subPile*ne=Creer_Cellule(parent);
    // Vérification que macel n'est pas vide (pile non vide)
    if (!Est_Vide_subPile(mapile))
    {
        ne->svt = mapile; /* Mise à jour du pointeur svt de macel
 pour pointer vers l'ancienne sommet de pile*/
        mapile = ne; /*Mise à jour de mapile pour pointer vers macel,
 qui est maintenant la nouvelle sommet de pile*/
    }
    return ((subPile*)ne);/*Renvoi du pointeur mis à jour vers la
 sommet de la pile*/
}
//////////////////
subPile *Depiler(subPile *mapile)
{
    subPile *tmp;
    // Vérification que la pile n'est pas vide
    if (!Est_Vide_subPile(mapile))
    {
        tmp = mapile; // Stockage du premier nœud dans tmp
        mapile = mapile->svt; /* Mise à jour de mapile pour pointer
	 vers le deuxième nœud*/
        free(tmp); // Libération de la mémoire occupée par le premier nœud
    }
    // Renvoi du pointeur mis à jour vers la pile
    return ((subPile *)mapile);
}

void Afficher_Ppile(subPile *mapile)
{
    printf("\naffichage de la pile:\n");
    subPile *tmp, *pcrt;
    int i =0;
    // Si la pile est vide, affichage d'un message approprié et retour
    if (Est_Vide_subPile(mapile))
    {
        printf("\nLa pile est vide");
        return;
    }
    tmp = NULL;
    // Affichage des éléments de la pile
    while (!Est_Vide_subPile(mapile))
    {
        printf("\n%deme sub", i+1);//Afficher la valeur de l'élément
        pcrt = mapile;
        mapile = mapile->svt;
        pcrt->svt = tmp;
        tmp = pcrt; // tmp conserve la cellule pour replacer plus tard
        i++;
    }
    // Replacer les cellules dans l'ordre initial de la pile
    while (!Est_Vide_subPile(tmp))
    {
        pcrt = tmp;
        tmp = tmp->svt;
        pcrt->svt = mapile;
        mapile = pcrt;
    }
}


//fct de creation d'un sous menu a partir xml
/**********************************************************************************
 -Nom : submenu_xml
 -Entrees : File *file : pointeur sur le fichier text,
            Menu* menu_parent : pointeur sur le menu pere
 -Sortie: un entier qui indique l'id de dernier balise lue.
 -Description: Cette fonction permet de créer un submenu et l'associer a son menu
*********************************************************************************/

void submenu_xml(FILE*file,subPile*mapile)
{
    Menu*menu_parent=mapile->parent;
    int test;
    char val[MAX];
    int has_accel=0, has_submenu=0;
    gchar *title_gchar="",*icon_gchar="";
    //creation d'ouvrir
    Menu *submenu = NULL;
    submenu=(Menu*)malloc(sizeof(Menu));
    if(!submenu) exit(-1);
    //tant qu'on a des propriete de menuitem
    while((test=balise(file))==22)
    {
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", val);
        if (!(strcmp("label\"", val)))
        {
            lire_gchar_str(file,val);
            title_gchar = g_strdup(val);
        }//fin if
        else if (!(strcmp("has_submenu\"", val)))
            has_submenu = char_TO_int(lire_gchar(file)) ;
        else if (!(strcmp("icon\"", val)))
        {
            lire_gchar_str(file,val);
            icon_gchar = g_strdup(val);
        }//fin else if
        else if (!(strcmp("has_accel\"", val)))
            has_accel= char_TO_int(lire_gchar(file));
    }//fin   while((test=balise(file))==22)
    ///proprietes de menu item sont fini
    //creation de menu item de submenu
    if(strlen(icon_gchar)==0)
    { printf("\nicon videeeee!alors creation sans icon");
        submenu=ajout_elem_to_submenu(menu_parent,
                                      title_gchar,has_submenu,NULL,"");
    }//fin if
    else if((has_accel==0) && strlen(icon_gchar)!=0 )
    {
        printf("creation de submenu");
        submenu=ajout_elem_to_submenu(menu_parent,
                                      title_gchar,has_submenu,
                                      NULL,icon_gchar);
    }//fin else if
    else if((has_accel==1) && strlen(icon_gchar)!=0 )
        submenu=ajout_elem_to_submenu_with_accel_and_icon
                (menu_parent,title_gchar,
                 has_submenu,NULL,icon_gchar,
                 GDK_KEY_o,GDK_CONTROL_MASK);
    if(test==-15)
    {
        printf("\non est dans le cas de test==(-15)\nfin de submenu");

        while(test==-15){
            mapile=Depiler(mapile);
            test=balise(file);
        }

        if(!mapile)
        {
            printf("\npile vide\non a sortie de submenu_xml1\n");

            return;

        }
        printf("\npile n'est pas vide");
        //test=balise(file);
        //printf("\ntest=%d",test);
        submenu_xml(file,mapile);

    }
        //printf("\n  test == %d",test);
    else if(test==16)
    {
        printf("\non est dans le cas de test==16\n");
        submenu_xml(file,mapile);
    }
    else if(test == 15)
    {
        //
        printf("\non est dans le cas de test ==15");
        mapile = Empiler(mapile,submenu);
        //on est dans le cas de submenu d'un menuitem d'un submenu de niv 1 //ex :OUvrir

        test = balise(file);//on a lue un menuitem apres sub
        //if (test == 16) printf("\non a lue un menuitem apres sub <lvl2>\n");
        submenu_xml(file, mapile);

        //sub_rec_xml(file,mapile,test);
    }
}//fin de fonction submenu_xml
void menu_xml(FILE*file,Menu *menu_parent);
//fct de creation de menu barre a partir xml
/**********************************************************************************
 -Nom : menu_barre_xml
 -Entrees : File *file : pointeur sur le fichier text,
            int parent : indice de parent
 -Sortie: -
 -Description: Cette fonction permet de créer le menu barre
 ainsi que le premier menu en respectant les propriétés décrites dans le fichier
*********************************************************************************/
void menu_barre_xml(FILE *file,int parent)
{
    int test, has_accel=0,has_submenu=0;
    char val[MAX],orientation,*title_gchar;
    Menu *menu_parent = NULL;
    menu_parent=(Menu*)malloc(sizeof(Menu));
    if(!menu_parent) exit(-1);
    while ((test = balise(file)) == 22)
    {
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", val);

        //recuperation du l'orientation de box
        if (!(strcmp("orientation\"", val))) {
            orientation = lire_gchar(file);
            menu_parent->m_barre.orientation = orientation;
        }
    }//fin while ((test = balise(file)) == 22)
    //lecture de premier menu de menu_barre, exit sinon
    if(test!=14) exit(-1);
    //lecture des proprietes de menu
    while((test=balise(file))==22)
    {
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", val);
        if (!(strcmp("title\"", val)))
        {
            lire_gchar_str(file,val);
            title_gchar = g_strdup(val);
        }
        else if (!(strcmp("has_accel\"", val)))
            has_accel= char_TO_int(lire_gchar(file));
        else if (!(strcmp("has_submenu\"", val)))
            has_submenu = char_TO_int(lire_gchar(file));
    } //fin while((test=balise(file))==22)

    //creation de menu_principale
    menu_parent=Creer_Menu_principale(title_gchar,menu_parent->m_barre.orientation,
                                      parents[parent],has_submenu,NULL,has_accel);
    if(test==15)
    {
        //lire le premier menuitem de submenu
        test=balise(file);
        subPile*mapile=NULL;
        mapile=Empiler(mapile,menu_parent);
        submenu_xml(file,mapile);
        printf("\ntest de menu_bar %d",test);
        test=balise(file);
        if(test==14) menu_xml(file,menu_parent);
    }//fin if

    else if(test==-14)
    {
        test= balise(file);
        //printf("\n test : %d on a trouver menu barre\n",test);
        if(test==14)  menu_xml(file,menu_parent);
    }
    creer_object(file,2);
}//fin de la fonction menu_barre_xml
//fct de creation de menu a partir xml
/**********************************************************************************
 -Nom : menu_xml
 -Entrees : File *file : pointeur sur le fichier text,
            Menu* menu_parent : pointeur sur le menu principale
 -Sortie: -
 -Description: Cette fonction permet de créer un menu et l'associer a son parent
 menu principale.
*********************************************************************************/
void menu_xml(FILE*file,Menu *menu_parent)
{
    int test, has_submenu=0;
    char val[MAX];
    gchar *title_gchar;
    Menu *menu = NULL;
    menu=(Menu*)malloc(sizeof(Menu));
    if(!menu) exit(-1);
    while((test=balise(file))==22)
    {
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", val);
        if (!(strcmp("label\"", val)))
        {
            lire_gchar_str(file,val);
            title_gchar = g_strdup(val);
        }//fin if
        else if (!(strcmp("has_submenu\"", val)))
            has_submenu = char_TO_int(lire_gchar(file));
    }//fin while((test=balise(file))==22)
    //creation de menu en l'associant au menu barre
    menu=ajout_Menu_to_barre(*menu_parent,title_gchar,has_submenu,NULL);
    if(test==15)
    {
        //lire le premier menuitem de submenu
        test=balise(file);
        subPile*mapile=NULL;
        mapile=Empiler(mapile,menu);
        submenu_xml(file,mapile);
        test=balise(file);
        if(test==14) menu_xml(file,menu_parent);
    }//fin if
    else if(test==-14)
    {
        test= balise(file);
        //printf("\n test : %d on a trouver menu xml\n",test);
        if(test==14) menu_xml(file,menu_parent);
    }
}//fin de fonction menu_xml

#endif //XML_TAHA_MENU_XML_H
