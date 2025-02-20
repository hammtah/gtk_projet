//
// Created by ACER on 28/12/2024.
//

#ifndef TEST1_COORDONNEES_H
#define TEST1_COORDONNEES_H
#include "global.h"
typedef struct cd
{
    gint x;
    gint y;
}coordonnees;


coordonnees* create_coordonnees(gint x, gint y)
{
    // Allocation dynamique de mémoire
    coordonnees *cord = (coordonnees*)malloc(sizeof(coordonnees));
    if (cord == NULL)
    {
        // Gestion de l'échec d'allocation mémoire
        perror("Erreur lors de l'allocation de la structure coordonnees");
        //exit(EXIT_FAILURE);
        return NULL;
    }
    cord->x = x;
    cord->y = y;
    // Retourne un pointeur vers la structure coordonnees initialisée
    return cord;
}//Fin fonction create_coordonnees()
#endif //TEST1_COORDONNEES_H
