//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_ENTRY_H
#define TEST1_ENTRY_H

#include "global.h"
typedef struct {

    GtkWidget *entry;
    // gint h;
    // gint w;
    dimension *dim;
    gboolean is_editable;
    gboolean is_visible;
    gchar *placeholder_text;
    gint maxlen;
    gchar *default_text; // the difference between palce holder and defaust txt , the placehlder will be shown only when the enetry is empty ,
    // but the default text will be shown but will not be removed when u start typig
} entry_type_basic;

typedef struct {

    GtkWidget *entry;
    // gint h;
    // gint w;
    dimension *dim;
    gchar *placeholder_text;
    gchar invisible_char;

} entry_type_password;

// Add freee funct
void free_entry_basic(entry_type_basic *entry) {
    if (entry) {
        g_free(entry->placeholder_text);
        g_free(entry->default_text);
        g_free(entry);
    }
}

void free_entry_password(entry_type_password *entry) {
    if (entry) {
        g_free(entry->placeholder_text);
        g_free(entry);
    }
}

// fomction diniallisation de las structure basic enrtry
entry_type_basic *Init_Entry_Basic(

        // gint height,
        // gint width,
        dimension *dim,
        gboolean editable,
        gboolean visible,
        const gchar *placeholder,
        gint maxlen,
        const gchar *default_text
) {

    g_return_val_if_fail(dim->height > 0 && dim->width > 0, NULL);
    g_return_val_if_fail(maxlen >= 0, NULL);

    entry_type_basic *entry_basic = (entry_type_basic *)g_malloc(sizeof(entry_type_basic));


    entry_basic->entry = gtk_entry_new();
    entry_basic->dim = dim;
    entry_basic->is_editable = editable;
    entry_basic->is_visible = visible;
    entry_basic->placeholder_text = g_strdup(placeholder);
    entry_basic->maxlen = maxlen;
    entry_basic->default_text = g_strdup(default_text);

    return entry_basic;
}

// fomction diniallisation de las structure password
entry_type_password *Init_Entry_Password(

        // gint height,
        // gint width,
        dimension *dim,
        const gchar *placeholder,
        gchar invisible_char
) {


    entry_type_password *entry_password = (entry_type_password *)g_malloc(sizeof(entry_type_password));


    entry_password->entry = gtk_entry_new();
    entry_password->dim=dim;
    entry_password->placeholder_text = g_strdup(placeholder);
    entry_password->invisible_char = invisible_char;

    return entry_password;
}

// add fucnt for basci type
GtkWidget *add_entry_basic(entry_type_basic *entry_basic) {
    // Configure the entry
    gtk_widget_set_size_request(entry_basic->entry, entry_basic->dim->width, entry_basic->dim->height);


    // Set properties
    gtk_entry_set_visibility(GTK_ENTRY(entry_basic->entry), entry_basic->is_visible);
    gtk_editable_set_editable(GTK_EDITABLE(entry_basic->entry), entry_basic->is_editable);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_basic->entry), entry_basic->placeholder_text);

    if (entry_basic->maxlen > 0) {
        gtk_entry_set_max_length(GTK_ENTRY(entry_basic->entry), entry_basic->maxlen);
    }

    if (entry_basic->default_text != NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry_basic->entry), entry_basic->default_text);
    }

    // Set alignment
    gtk_widget_set_halign(entry_basic->entry, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entry_basic->entry, GTK_ALIGN_CENTER);

    return entry_basic->entry;
}

// add fucn for the password type
GtkWidget *add_entry_password(entry_type_password *entry_password) {
    gtk_widget_set_size_request(entry_password->entry, entry_password->dim->width, entry_password->dim->height);


    gtk_entry_set_visibility(GTK_ENTRY(entry_password->entry), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_password->entry), entry_password->invisible_char);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_password->entry), entry_password->placeholder_text);

    gtk_widget_set_halign(entry_password->entry, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entry_password->entry, GTK_ALIGN_CENTER);

    return entry_password->entry;
}

// adding tehs css to stylize the entriess
void entry_set_css_class(GtkWidget *entry, const gchar *class_name) {
    GtkStyleContext *context = gtk_widget_get_style_context(entry);
    gtk_style_context_add_class(context, class_name);
}
#endif //TEST1_ENTRY_H
