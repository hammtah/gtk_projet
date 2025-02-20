//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_CALENDRIER_H
#define TEST1_CALENDRIER_H
#include "global.h"

/* Titre: Structure Date*/
typedef struct
{
    guint year;   // Année sélectionnée
    guint month;  // Mois sélectionné
    guint day;    // Jour sélectionné
} Date;

// Structure pour stocker les données associées au calendrier
typedef struct
{
    GtkWidget *pere;      // Fenêtre principale
    GtkCalendar *calendar; // Widget Calendrier
    Date date;             // Jour sélectionné
    dimension dim;          // Structure définissant les dimensions du calendrier
    coordonnees cord;      // Structure représentant les coordonnées du calendrier
} Calender;

// Fonction d'initialisation de la structure
/*************************************************************
Nom          : init_calender()
Entrée       : pere - Le widget parent du calendrier
               cord - Les coordonnées du calendrier
               dim  - Les dimensions du calendrier
Sortie       : Calender* - Pointeur vers la structure Calender initialisée
Description  : Cette fonction initialise  l'objet Calender,
 avec les informations spécifiés en parametre
*************************************************************/
Calender *init_calender(GtkWidget *pere,coordonnees cord,dimension dim)
{
    // Allocation de mémoire pour la structure Calender
    Calender *calendrier = malloc(sizeof(Calender));
    // Vérification si l'allocation a réussi
    if (!calendrier)
    {
        printf("Erreur d'allocation !!");
        exit(-1);
    }
    if(pere) calendrier->pere = pere;
    // Initialisation des champs de date à 0
    calendrier->date.year = 0;
    calendrier->date.month = 0;
    calendrier->date.day = 0;
    // Attribution des coordonnées et dimensions spécifiées
    calendrier->cord.x = cord.x;
    calendrier->cord.y = cord.y;
    calendrier->dim.height = dim.height;
    calendrier->dim.width = dim.width;
    // Retour du pointeur vers la structure Calender initialisée
    return ((Calender*)calendrier);
}//FIN fonction init_calender()

// Fonction de rappel appelée lorsqu'un jour est sélectionné dans le calendrier
/*************************************************************
Nom          : on_day_selected()
Entrée       : calendar - Le widget calendrier GTK où la date est sélectionnée
               data     - Pointeur vers la structure Calender contenant les données
Sortie       : -
Description  : Cette fonction est appelée lorsqu'une date est sélectionnée dans
               un widget calendrier GTK. Elle récupère la date sélectionnée à partir
               du widget calendrier et met à jour les champs de la structure Calender
               spécifiée avec cette date. Ensuite,fait l'affichage
*************************************************************/
void on_day_selected(GtkCalendar *calendar, Calender *data)
{
    gtk_calendar_get_date(calendar, &(data->date.year), &(data->date.month), &(data->date.day));
    g_print("Selected Date: %d-%d-%d\n", data->date.year, data->date.month + 1, data->date.day);
}//FIN fonction on_day_selected()

// Fonction de création et de configuration du calendrier
/*************************************************************
Nom          : createCalendar
Entrée       : calendrier - Pointeur vers la structure Calender
Sortie       : -
Description  : Cette fonction crée un widget calendrier
*************************************************************/
void createCalendar(Calender *calendrier)
{
    // Création du widget calendrier GTK
    calendrier->calendar = gtk_calendar_new();
    // Connexion du signal "day-selected" à la fonction de rappel on_day_selected
    g_signal_connect(calendrier->calendar, "day-selected", G_CALLBACK(on_day_selected), calendrier);
}//FIN fonction createCalendar()

#endif //TEST1_CALENDRIER_H
