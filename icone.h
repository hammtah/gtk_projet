//
// Created by ACER on 05/01/2025.
//

#ifndef TEST1_ICONE_H
#define TEST1_ICONE_H
#include "global.h"
typedef struct ic{
    GdkPixbuf *icon;
    gchar icon_path[100];
    dimension icon_dim;
    coordonnees icon_cord;
}Myicon;

GdkPixbuf* create_icon_from_file(const gchar file_path[50])
{
    GdkPixbuf *icon;
    GError *error = NULL;
    icon = gdk_pixbuf_new_from_file(file_path, &error);
    if (error != NULL)
    {
        // Affichage de l'erreur en cas d'échec du chargement de l'icône
        g_printerr("Erreur lors du chargement de l'icône : %s\n", error->message);
        g_error_free(error);
        return NULL;
    }//FIn if (error != NULL)
    return icon;
}//FIN fonction create_icon_from_file()


#endif //TEST1_ICONE_H
