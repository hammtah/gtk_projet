//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_LABEL_H
#define TEST1_LABEL_H
#include "global.h"
#include "xml_utility.h"



// Définition de la structure Monlabel
typedef struct {
    GtkWidget *elem;       // Widget du label
    gchar *texte;          // Texte du label
    gchar *titre;          // Titre du label
    coordonnees* Crd;       // Coordonnées du label
    dimension* dim;         // Dimensions du label
    GtkWidget* container;
    char* color;
    gboolean bold;
    char* taille;
    char* police;
} Monlabel;


// Fonction pour initialiser et allouer un label
Monlabel *init_label(const gchar *texte, const gchar *tit, coordonnees* C, dimension* D,
                     GtkWidget* container,char* color, gboolean bold, char* taille, char* police) {
    if (!texte) {
        printf("Label vide!!!!!!\n");
        exit(-1);
    }

    Monlabel *L = (Monlabel *)malloc(sizeof(Monlabel));
    if (!L) {
        printf("Erreur d'allocation mémoire pour le label.\n");
        exit(-1);
    }

    // Allocation et initialisation du titre
    if (tit) {
        L->titre = (gchar *)malloc(30 * sizeof(gchar));
        if (!L->titre) {
            printf("Erreur d'allocation mémoire pour le titre du label.\n");
            exit(-1);
        }
        strcpy(L->titre, tit);
    } else {
        L->titre = NULL;
    }

    // Allocation et initialisation du texte
    L->texte = (gchar *)malloc(300 * sizeof(gchar));
    if (!L->texte) {
        printf("Erreur d'allocation mémoire pour le texte du label.\n");
        exit(-1);
    }
    strcpy(L->texte, texte);

    // Initialisation des coordonnées et dimensions
    L->Crd = C;
    L->dim = D;
    L->container = container;

    L-> color= color;
    L-> bold = bold;
    L-> taille = taille;
    L->police= police;

    return L;
}

// Fonction pour créer un label GTK à partir d'un objet Monlabel
Monlabel *creer_label(Monlabel *L) {
    L->elem = gtk_label_new(L->texte);

    if (L->titre) {
        gtk_widget_set_name(L->elem, L->titre);
    }

    if(L->dim)
        gtk_widget_set_size_request(L->elem, L->dim->width, L->dim->height);

    if(GTK_IS_FIXED(L->container)){
        gtk_fixed_put(GTK_FIXED(L->container), L->elem, L->Crd->x, L->Crd->y);
    }
    gtk_container_add(GTK_CONTAINER(L->container), L->elem);



    //Regler style
    GtkCssProvider *provider = gtk_css_provider_new();

    char* css = g_strdup_printf("#%s { color: %s ; \
                                        font-size: %s;\
                                        font-family: %s;\
                                        font-weight: %s \
                                        }",
                          L->titre, L->color, L->taille, L->police, L->bold == 1? "bold": "normal");

    // Load the CSS into the provider
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    // Get the style context of the button
    GtkStyleContext *context = gtk_widget_get_style_context(L->elem);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Free allocated memory
    g_free(css);
    g_object_unref(provider);
    //Fin style
    return L;
}


void label_xml(FILE *file, int parent)
{
    //Variables pour initier le bouton
    char color1[MAX], color2[MAX],boxEmplacement;
    gchar *expand_gchar,*fill_gchar;
    gint type_bg = -1; // 0:pour simple background ; 1:pour simple background modern;
    int test, hasMnemonic;
    char x[10], y[10];
    char width[MAX], height[MAX];
    gchar *bgColor_gchar, *icon_gchar;
    char title[MAX], icon[MAX], bgcolor[MAX], taille[MAX], border[MAX],
            color[MAX], police[MAX], gras[MAX],border_radius[MAX];
    icon[0] = '\0';
    char car;

    // Si la balise est une propriété ou un style
    while ((test = balise(file)) == 22)
    {
        char mot[MAX], taille[MAX];
        int ind = 0;
        Epeurerblanc(file);
        fseek(file, 6, SEEK_CUR);
        fscanf(file, "%s", mot);
            // Récupération du texte du label
            if (!(strcmp("text\"", mot)))
            {
                lire_gchar_str_with_deplacement(file,title,10);
            }
                // Récupération de la position x
            else if (!(strcmp("x\"", mot))) {
                lire_gchar_str_with_deplacement(file, x, 10);
            }
                // Récupération de la position y du label
            else if (!(strcmp("y\"", mot))) {
                lire_gchar_str_with_deplacement(file, y, 10);
            }
                // Récupération de la largeur du bouton
            else if (!(strcmp("width\"", mot))) {
                lire_gchar_str_with_deplacement(file, width, 10);
            }
                // Récupération de la hauteur du bouton
            else if (!(strcmp("height\"", mot))) {
                lire_gchar_str_with_deplacement(file, height, 10);
            }

        if (!(strcmp("color\"", mot))) {
            lire_gchar_str_with_deplacement(file, color, 10);
        }
        else if (!(strcmp("police\"", mot))) {
            lire_gchar_str_with_deplacement(file, police, 10);
        }
        else if (!(strcmp("taille\"", mot))) {
            lire_gchar_str_with_deplacement(file, taille, 10);
        }
        else if (!(strcmp("gras\"", mot))) {
            lire_gchar_str_with_deplacement(file, gras, 10);

        }

    }

    // Si la balise est fermante


    // Créer le label
    //Creer le style
    Monlabel* label = init_label(title, title, cord(atoi(x), atoi(y)), dim(atoi(width), atoi(height)),
            parents[parent],color, atoi(gras), taille, police);
    //Creer le bouton
    creer_label(label);
    // Créer d'autres objets à partir du fichier XML
    creer_object(file, parent);
}






#endif //TEST1_LABEL_H
