#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>

GtkApplication *app;

void error_win(GtkWidget *widget, char *error);
void admin_sick_list_page(GtkWidget *widget, gpointer home_page);
void admin_hospitals_list_page(GtkWidget *widget, gpointer data);
void close_win(GtkWidget *widget, gpointer window);
void person_meets_new_win(GtkWidget *widget, gpointer home_page);
void person_meets_win(GtkWidget *widget, gpointer home_page);
void person_record_test_win(GtkWidget *widget, gpointer records_page);
void person_records_win(GtkWidget *widget,gpointer home_page);
void person_new_visit_red(GtkWidget *widget, gpointer data);
void person_new_visit_handler(GtkWidget *widget, gpointer data);
void owner_home_win(GtkWidget *widget, gpointer data);
void admin_home_win(GtkWidget *widget, gpointer data);
void person_visits_win(GtkWidget *widget, gpointer home_page);
void person_home_win(GtkWidget *widget, gpointer data);
void sign_up_handle_finish_normal(GtkWidget *widget, gpointer user_data);
void sign_up_handle_finish_owner(GtkWidget *widget, gpointer user_data);
void sign_up_handle_normal_user_form(GtkWidget *widget, gpointer user_data);
void sign_up_win(GtkWidget *widget, gpointer login_win);
void forget_password_win(GtkWidget *widget, gpointer login_win);
void login_win(GtkWidget *widget, gpointer welcome_win);
void handle_login(GtkWidget *widget, gpointer user_pass);
void splash(GtkApplication *app, gpointer user_data);
#endif