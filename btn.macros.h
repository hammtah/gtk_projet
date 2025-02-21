//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_BTN_MACROS_H
#define TEST1_BTN_MACROS_H
#include "global.h"


/******************MACROS***********************/

/******************BUTTON NORMAL***************/
//Si le bouton n'est pas fixé alors la position n'a plus d'importance.
//La dimension pour les boutons qui ne sont pas fixés represente juste la dimension minimal
//du bouton, parceque le bouton va prendre la dimension que son pere(box,grid...) va lui donner.
#define btnNormal(nom, label, tooltip, container, margin, dim, img) \
                                initBtn(NORMAL, nom, label,TRUE,tooltip,img,\
                                dim, FALSE, NULL,margin,\
                                TRUE, container, NULL,GTK_ALIGN_CENTER,1, FALSE, NULL)

#define btnNormalFixed(nom, label, tooltip, container, pos, dim, img) \
                                initBtn(NORMAL, nom, label,TRUE,tooltip,img,\
                                dim, TRUE, pos,NULL,\
                                TRUE, container, NULL,GTK_ALIGN_START,1, FALSE, NULL)

/***********************RADIO************************/
#define btnRadio(nom, label, tooltip, container, margin, groupeMember, img) \
                                initBtn(RADIO, nom, label,TRUE, tooltip,img, \
                                dim(5,5), FALSE, NULL, margin, \
                                TRUE, container, groupeMember,GTK_ALIGN_START,1, TRUE, NULL)

#define btnRadioFixed(nom, label, tooltip, container, pos, groupeMember, img) \
                                initBtn(RADIO, nom, label,TRUE, tooltip,img, \
                                dim(5,5), TRUE, pos, NULL, \
                                TRUE, container, groupeMember,GTK_ALIGN_START,1, TRUE, NULL)

/***********************CHECKBOXES************************/
#define btnCheck(nom, label, tooltip, margin, container, isChecked, img) \
                                initBtn(CHECKBOX, nom, label,TRUE, tooltip,img, \
                                dim(5,5), FALSE, NULL, margin, \
                                TRUE, container, NULL,GTK_ALIGN_START,1, isChecked, NULL)


#define btnCheckFixed(nom, label, tooltip, pos, container, isChecked, img) \
                                initBtn(CHECKBOX, nom, label,TRUE, tooltip,img, \
                                dim(5,5), TRUE, pos, NULL, \
                                TRUE, container, NULL,GTK_ALIGN_START,1, isChecked, NULL)

/***********************TOGGLE************************/
#define btnToggle(nom, label, tooltip, container, margin, dim, img) \
                                initBtn(TOGGLE, nom, label,TRUE,tooltip,img,\
                                dim, FALSE, NULL,margin,\
                                TRUE, container, NULL,GTK_ALIGN_START,1, FALSE, NULL)

#define btnToggleFixed(nom, label, tooltip, container, pos, dim, img) \
                                initBtn(TOGGLE, nom, label,TRUE,tooltip,img,\
                                dim, TRUE, pos,NULL,\
                                TRUE, container, NULL,GTK_ALIGN_START,1, FALSE, NULL)
/************************SWITCH***********************/
#define btnSwitch(nom, label, tooltip, container, margin, dim, img,isChecked) \
                                initBtn(SWITCH, nom, label,TRUE,tooltip,img,\
                                dim, FALSE, NULL,margin,\
                                TRUE, container, NULL,GTK_ALIGN_START,1, isChecked, NULL)

#define btnSwitchFixed(nom, label, tooltip, container, pos, dim, img, isChecked) \
                                initBtn(SWITCH, nom, label,TRUE,tooltip,img,\
                                dim, TRUE, pos,NULL,\
                                TRUE, container, NULL,GTK_ALIGN_START,1, isChecked, NULL)
/********************SPIN***************************/
//les champs unitilisés (img, isChecked,...) sont ingnorés
#define btnSpin(nom, label,tooltip,margin,container, spinObj) \
        initBtn(SPIN, nom, label,TRUE,tooltip, NULL,NULL, FALSE,NULL,margin,                                                 \
                TRUE,container, NULL,GTK_ALIGN_START, 1,TRUE, spinObj)

#define btnSpinFixed(nom, label,tooltip,dim,pos,container, spinObj) \
        initBtn(SPIN, nom, label,TRUE,tooltip, NULL,dim, TRUE,pos,NULL,                                                 \
                TRUE,container, NULL,GTK_ALIGN_START, 1,TRUE, spinObj)



















#endif //TEST1_BTN_MACROS_H
