//
// Created by Dell on 3/1/2025.
//

#ifndef XML_TAHA_CONTAINERS_LIST_H
#define XML_TAHA_CONTAINERS_LIST_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "coordonnees.h"
#include "dimension.h"
#include "box.h"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 256  // Définir une taille maximale pour le nom

/**
 * @brief Structure représentant un arbre avec un nom, un widget, et des pointeurs vers les enfants et les frères.
 */
typedef struct arbre {
    char nom[MAX_NAME_LENGTH];   /**< Le nom de l'élément */
    GtkWidget *widget;           /**< Pointeur vers le widget associé */
    struct arbre *frere;         /**< Pointeur vers le frère de l'élément */
    struct arbre *fils;          /**< Pointeur vers le premier fils de l'élément */
    int is_container;            /**< Indicateur pour savoir si c'est un conteneur (1) ou non (0) */
} Arbre;

/**
 * @brief Fonction pour allouer de la mémoire pour un nouveau noeud de l'arbre.
 *
 * Cette fonction crée un nouveau noeud de type `Arbre` et initialise ses champs à des valeurs .
 *
 * @return Arbre* Le pointeur vers la structure nouvellement allouée.
 */
Arbre* allouer_arbre(char* nom, GtkWidget* widget, Arbre* frere, Arbre* fils, bool is_container) {
    // Allocation mémoire pour le noeud
    Arbre* nouveau_noeud = (Arbre*)malloc(sizeof(Arbre));

    // Vérification si l'allocation a échoué
    if (nouveau_noeud == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'arbre.\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des champs à des valeurs
    strcpy(nouveau_noeud->nom, nom);
    nouveau_noeud->widget = widget;
    nouveau_noeud->frere = frere;
    nouveau_noeud->fils = fils;
    nouveau_noeud->is_container = is_container;

    return nouveau_noeud;
}

/**
 * @brief Insère un élément dans l'arbre en tant que fils du noeud dont le nom correspond à nomDuPere.
 *
 * La fonction parcourt récursivement l'arbre. Lorsqu'un noeud ayant pour nom nomDuPere
 * et marqué comme conteneur est trouvé, l'élément 'elem' est inséré en tant que fils.
 * Si le noeud possède déjà un premier fils, 'elem' est ajouté en fin de la liste des frères.
 *
 * @param racine La racine de l'arbre.
 * @param elem L'élément à insérer.
 * @param nomDuPere Le nom du noeud parent (const, non modifié).
 * @return Arbre* La racine de l'arbre mise à jour.
 */
Arbre* insererArbre(Arbre* racine, Arbre* elem, const char* nomDuPere){
    if(!racine){
        perror("errr");
        exit(-1);
    }
    Arbre* temp = racine;
    if((strcmp(nomDuPere, temp->nom) == 0) && temp->is_container){
        //Inserer comme frere du premier fils
        if(temp->fils){
            temp = temp->fils;
            //Parcourir les freres
            while(temp->frere){
                temp = temp->frere;
            }
            //Inserer dans freres
            temp->frere = elem;
        }
        else {
            //inserer comme premier fils
            temp->fils = elem;
        }
        return racine;
    }

    if(racine->fils)
        insererArbre(racine->fils, elem, nomDuPere);

    if(racine->frere)
        insererArbre(racine->frere, elem, nomDuPere);

    return racine;
}

/**
 * @brief Affiche l'arbre sous forme d'arborescence.
 *
 * La fonction affiche le nom de chaque noeud précédé d'une indentation correspondant à son niveau dans l'arbre.
 *
 * @param racine Le noeud courant de l'arbre.
 * @param niveau Le niveau d'indentation (0 pour la racine).
 */
void afficher_arbre(Arbre* racine, int niveau) {
    if (racine == NULL) {
        return;
    }

    // Affichage de l'indentation correspondant au niveau
    for (int i = 0; i < niveau; i++) {
        printf("    "); // 4 espaces par niveau
    }

    // Afficher le nom et, si c'est un conteneur, l'indiquer
    printf("%s%s\n", racine->nom, racine->is_container ? " [container]" : "");

    // Afficher récursivement le premier fils avec une indentation augmentée
    afficher_arbre(racine->fils, niveau + 1);

    // Afficher récursivement les frères au même niveau
    afficher_arbre(racine->frere, niveau);
}

#define MAX_CONTAINER_NAMES 100

/**
 * @brief Fonction récursive auxiliaire qui parcourt l'arbre et insère dans le tableau
 *        les noms des noeuds dont is_container est vrai.
 *
 * @param node Le noeud courant de l'arbre.
 * @param noms Le tableau préalloué pour stocker les noms (taille MAX_CONTAINER_NAMES).
 * @param indice Pointeur vers l'indice courant dans le tableau.
 */
void getNomsConteneursRec(Arbre *node, char *noms[MAX_CONTAINER_NAMES], int *indice) {
    if (node == NULL || *indice >= MAX_CONTAINER_NAMES - 1) {
        return;
    }

    if (node->is_container) {
        noms[*indice] = node->nom;  // On stocke directement le pointeur vers la chaîne
        (*indice)++;
    }

    // Parcours récursif sur le premier fils puis sur les frères
    getNomsConteneursRec(node->fils, noms, indice);
    getNomsConteneursRec(node->frere, noms, indice);
}

/**
 * @brief Remplit un tableau de chaînes de caractères avec les noms des conteneurs présents dans l'arbre.
 *
 * La fonction parcourt l'arbre et insère dans le tableau préalloué (de taille MAX_CONTAINER_NAMES)
 * les noms des noeuds dont is_container est vrai. Le tableau est terminé par un élément NULL.
 *
 * @param racine La racine de l'arbre à parcourir.
 * @param noms Le tableau de chaînes de caractères préalloué (taille MAX_CONTAINER_NAMES) qui sera rempli.
 */
void getNomsConteneurs(Arbre *racine, char *noms[MAX_CONTAINER_NAMES]) {
    int indice = 0;
    getNomsConteneursRec(racine, noms, &indice);
    noms[indice] = NULL;  // Terminer le tableau par NULL
}


/**
 * @brief Retourne le widget associé au noeud dont le nom correspond au nom donné.
 *
 * La fonction parcourt récursivement l'arbre à partir de la racine et compare le nom de chaque
 * noeud au nom recherché. Si une correspondance est trouvée, le widget associé est retourné.
 *
 * @param racine La racine de l'arbre à parcourir.
 * @param nom Le nom à rechercher dans l'arbre.
 * @return GtkWidget* Le widget associé au nom donné, ou NULL s'il n'est pas trouvé.
 */
GtkWidget* getWidgetByNom(Arbre *racine, const char *nom) {
    if (racine == NULL) {
        return NULL;
    }

    if (strcmp(racine->nom, nom) == 0) {
        return racine->widget;
    }

    GtkWidget *resultat = getWidgetByNom(racine->fils, nom);
    if (resultat != NULL) {
        return resultat;
    }

    return getWidgetByNom(racine->frere, nom);
}


#endif //XML_TAHA_CONTAINERS_LIST_H
