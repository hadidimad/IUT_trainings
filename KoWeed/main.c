#include <stdio.h>
#include <sqlite3.h>
#include <gtk/gtk.h>
#include "./include/db.h"
#include "./include/app.h"
#include "./include/gui.h"
#include "./include/data.h"
#include <time.h>

int main(int argc, char *argv[])
{

    connect_db("./KoWeed.sqlite");

    int status;

    app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(splash), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}