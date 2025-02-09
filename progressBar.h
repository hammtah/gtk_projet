//
// Created by ACER on 06/01/2025.
//

#ifndef TEST1_PROGRESSBAR_H
#define TEST1_PROGRESSBAR_H
#include "global.h"


typedef struct {
    GtkProgressBar *progress_bar;
    guint timer_id;
    gsize total_size;
    gsize current_size;
    gboolean is_active;
} DownloadProgress;

// Update progress
static gboolean update_progress_timeout(gpointer user_data) {
    DownloadProgress *progress = (DownloadProgress *)user_data;

    if (!progress->is_active) {
        // gtk_main_quit();
        return G_SOURCE_REMOVE;

    }

    // Simulate download progress (increase by random amount)
    gsize chunk_size = g_random_int_range(1024, 1024 * 10);
    progress->current_size += chunk_size;

    if (progress->current_size >= progress->total_size) {
        progress->current_size = progress->total_size;
        progress->is_active = FALSE;
    }

    // Calculate progress fraction
    double fraction = (double)progress->current_size / progress->total_size;
    gtk_progress_bar_set_fraction(progress->progress_bar, fraction);

    // // Update text
    // char progress_text[128];
    // sprintf(progress_text, "Downloading: %.1f%%", fraction * 100);
    // gtk_progress_bar_set_text(progress->progress_bar, progress_text);

    return progress->is_active;
}



typedef struct
{   // add color to progress

    GtkWidget *pbar;
    // gint h;
    // gint w;
    dimension *dim;
    gboolean is_active;
    gchar color;
    gint pulsing_speed;


} progress_bar_type_pulse;

typedef struct
{   // add color to progress

    GtkWidget *pbar;
    // gint h;
    // gint w;
    dimension *dim;
    gboolean is_active;
    gchar color;
    gint timeout ; //added custum time , u dont want to mess with it just give it 10 , and use the progress struct to control ur progress
    gdouble fraction;


} progress_bar_type_fraction;


// Function to initialize a `progress_bar_type_pulse` structure
progress_bar_type_pulse *Init_ProgressBar_Type_Pulse( dimension *dim, gboolean active, gchar color, gint pulsing_speed) {
    progress_bar_type_pulse *pbar_pulse = (progress_bar_type_pulse *)g_malloc(sizeof(progress_bar_type_pulse));

    // Initialize the structure fields

    pbar_pulse->pbar = gtk_progress_bar_new();
    pbar_pulse->dim = dim;
    pbar_pulse->is_active = active;
    pbar_pulse->color = color;
    pbar_pulse->pulsing_speed = pulsing_speed;



    return pbar_pulse;
}

// Function to initialize a `progress_bar_type_fraction` structure
progress_bar_type_fraction *Init_ProgressBar_Type_Fraction( dimension *dim, gboolean active, gchar color, gdouble fraction) {
    progress_bar_type_fraction *pbar_fraction = (progress_bar_type_fraction *)g_malloc(sizeof(progress_bar_type_fraction));

    // Initialize the structure fields

    pbar_fraction->pbar = gtk_progress_bar_new();
    pbar_fraction->dim = dim;
    pbar_fraction->is_active = active;
    pbar_fraction->color = color;
    pbar_fraction->fraction = fraction;


    return pbar_fraction;
}



GtkWidget *add_progressbar_Tpulse(progress_bar_type_pulse *pbar_pulse){
    // Configure the progress bar
    gtk_widget_set_size_request(pbar_pulse->pbar, pbar_pulse->dim->width, pbar_pulse->dim->height);

    gtk_widget_set_halign(pbar_pulse->pbar, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(pbar_pulse->pbar, GTK_ALIGN_CENTER);

    if (pbar_pulse->is_active) {
        gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pbar_pulse->pbar));

        // gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pbar)
        g_timeout_add(pbar_pulse->pulsing_speed, (GSourceFunc)gtk_progress_bar_pulse, pbar_pulse->pbar);
    }
    // guint
    return pbar_pulse->pbar;


}


GtkWidget *add_progressbar_Tfraction(progress_bar_type_fraction* pbar_fraction,gpointer data){
    DownloadProgress *progress = (DownloadProgress *)data;

    // Configure the progress bar
    gtk_widget_set_size_request(pbar_fraction->pbar, pbar_fraction->dim->width,pbar_fraction->dim->height);



    gtk_widget_set_halign(pbar_fraction->pbar, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(pbar_fraction->pbar, GTK_ALIGN_CENTER);
    if (!pbar_fraction->is_active){

        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar_fraction->pbar), pbar_fraction->fraction);
    }
    else{
        g_timeout_add(10,(GSourceFunc)update_progress_timeout,progress);
    }






    // if (pbar_fraction->fraction >= 0.0 && pbar_fraction->fraction <= 1.0) {
    // }///should assert that the fraction should be bwten 1,0 to avoid any
    return pbar_fraction->pbar;



}
















#endif //TEST1_PROGRESSBAR_H
