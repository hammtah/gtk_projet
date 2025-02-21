//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_BTN_IMG_H
#define TEST1_BTN_IMG_H
#include "global.h"


#define MAX_BTN_ICON_LENGTH 100



//La structure définissant l'icone d'un button
typedef struct btn_image {
    GtkWidget *Image;
    gchar imgPath[100];//Le chemin de l'icon
    dimension imgDim;//La dimension de l'icon du button (width & height)
    GtkPositionType btnImgPos;//La position de l'icon du button
} BtnImage;

//Initialiser l'icon du bouton
void initBtnImage(BtnImage *btnimg, gchar imgPath[MAX_BTN_ICON_LENGTH], dimension imgDim, GtkPositionType btnImgPos)
{
    //Initialiser les champs de l'icon
    //Copier le path
    strncpy(imgPath, btnimg->imgPath, MAX_BTN_ICON_LENGTH);
    //Copier la dimension
    btnimg->imgDim=imgDim;
    //Copier la position
    btnimg->btnImgPos=btnImgPos;
    //Creer l'image et l'associer au bouton
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(btnimg->imgPath, btnimg->imgDim.width, btnimg->imgDim.height, NULL);
    btnimg->Image = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);//Liberer le pixbuf
    //Ajuster la position de l'icon
    //gtk_button_set_image_position(GTK_BUTTON(btn->button), btnimg->btnImgPos);
}







#endif //TEST1_BTN_IMG_H
