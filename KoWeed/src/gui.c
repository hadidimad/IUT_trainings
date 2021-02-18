#include "../include/gui.h"
#include "../include/app.h"
#include "../include/db.h"
#include <gtk/gtk.h>
#include <stdlib.h>

void close_win(GtkWidget *widget, gpointer window)
{
    gtk_widget_destroy(GTK_WIDGET(window));
}

void error_win(GtkWidget *widget, char *error)
{
    GtkWidget *window;
    GtkWidget *top_label;
    GtkWidget *error_label;
    GtkWidget *image;
    GtkCssProvider *provider;
    GtkStyleContext *context;
    GtkWidget *fixed;
    GtkWidget *return_button;

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 40px;"
                                    "}",
                                    -1,
                                    NULL);
    top_label = gtk_label_new("خطا!!!!");
    error_label = gtk_label_new(error);
    context = gtk_widget_get_style_context(top_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    return_button = gtk_button_new_with_label("بازگشت");

    image = gtk_image_new_from_file("./assets/error.png");
    gtk_window_set_title(GTK_WINDOW(window), "خطا");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), top_label, 480, 0);
    gtk_fixed_put(GTK_FIXED(fixed), error_label, 450, 150);

    g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(close_win), (gpointer)window);
    gtk_widget_set_size_request(return_button, 400, 60);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 320, 260);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_widget_show_all(window);
}

void person_record_test_handler(GtkWidget *widget, gpointer data)
{
    GtkWidget *cough_yes = g_object_get_data(G_OBJECT(data), "cough");
    GtkWidget *fever_yes = g_object_get_data(G_OBJECT(data), "fever");
    GtkWidget *breathe_yes = g_object_get_data(G_OBJECT(data), "breathe");
    GtkWidget *pain_yes = g_object_get_data(G_OBJECT(data), "pain");
    GtkWidget *throat_yes = g_object_get_data(G_OBJECT(data), "throat");
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");

    int health_score = 0;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cough_yes)))
    {
        health_score += 30;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fever_yes)))
    {
        health_score += 20;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(breathe_yes)))
    {
        health_score += 20;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pain_yes)))
    {
        health_score += 15;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(throat_yes)))
    {
        health_score += 15;
    }
    int code = 0;
    if (health_score <= 15)
    {
        code = 1;
    }
    else if (health_score <= 50)
    {
        code = 2;
    }
    else if (health_score <= 75)
    {
        code = 3;
    }
    else if (health_score <= 100)
    {
        code = 4;
    }
    session.person.status = code;
    save_record_person(session.person, code, time(NULL));
    handle_sick_meets(session.person, code, time(NULL));

    person_update(session.person);
    person_records_win(NULL, window);
}

void person_record_test_win(GtkWidget *widget, gpointer records_page)
{
    close_win(NULL, records_page);
    GtkWidget *window;

    //label
    GtkWidget *header_label;
    GtkWidget *cough_label;
    GtkWidget *fever_label;
    GtkWidget *breathe_label;
    GtkWidget *pain_label;
    GtkWidget *throat_label;

    //buttons
    GtkWidget *save_button;

    //radio
    GtkWidget *cough_yes;
    GtkWidget *fever_yes;
    GtkWidget *breathe_yes;
    GtkWidget *pain_yes;
    GtkWidget *throat_yes;
    GtkWidget *cough_no;
    GtkWidget *fever_no;
    GtkWidget *breathe_no;
    GtkWidget *pain_no;
    GtkWidget *throat_no;

    //dataholder
    GtkWidget *data_holder;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 18px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "ثبت وضعیت سلامتی جدید");

    header_label = gtk_label_new("برای ثبت وضعیت خود به سوالات پاسخ دهید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    cough_label = gtk_label_new("آیا سرفه خشک با تعداد بالا دارید؟");
    fever_label = gtk_label_new("آیا تب بالای ۳۷ درجه دارید؟");
    breathe_label = gtk_label_new("آیا تنگی نفس دارید؟");
    pain_label = gtk_label_new("آیااحساس درد و کوفتگی دارید؟");
    throat_label = gtk_label_new("آیا گلو درد دارید؟");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 100, 10);

    gtk_fixed_put(GTK_FIXED(fixed), cough_label, 250, 50);
    gtk_fixed_put(GTK_FIXED(fixed), fever_label, 250, 90);
    gtk_fixed_put(GTK_FIXED(fixed), breathe_label, 250, 130);
    gtk_fixed_put(GTK_FIXED(fixed), pain_label, 250, 190);
    gtk_fixed_put(GTK_FIXED(fixed), throat_label, 250, 230);

    cough_yes = gtk_radio_button_new_with_label(NULL, "بلی");
    cough_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cough_yes),
                                                           "خیر");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cough_yes), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cough_no), TRUE);

    fever_yes = gtk_radio_button_new_with_label(NULL, "بلی");
    fever_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(fever_yes),
                                                           "خیر");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fever_yes), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(fever_no), TRUE);

    breathe_yes = gtk_radio_button_new_with_label(NULL, "بلی");
    breathe_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(breathe_yes),
                                                             "خیر");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(breathe_yes), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(breathe_no), TRUE);

    pain_yes = gtk_radio_button_new_with_label(NULL, "بلی");
    pain_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pain_yes),
                                                          "خیر");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pain_yes), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pain_no), TRUE);

    throat_yes = gtk_radio_button_new_with_label(NULL, "بلی");
    throat_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(throat_yes),
                                                            "خیر");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(throat_yes), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(throat_no), TRUE);

    gtk_fixed_put(GTK_FIXED(fixed), cough_no, 50, 50);
    gtk_fixed_put(GTK_FIXED(fixed), fever_no, 50, 90);
    gtk_fixed_put(GTK_FIXED(fixed), breathe_no, 50, 130);
    gtk_fixed_put(GTK_FIXED(fixed), pain_no, 50, 190);
    gtk_fixed_put(GTK_FIXED(fixed), throat_no, 50, 230);
    gtk_fixed_put(GTK_FIXED(fixed), cough_yes, 150, 50);
    gtk_fixed_put(GTK_FIXED(fixed), fever_yes, 150, 90);
    gtk_fixed_put(GTK_FIXED(fixed), breathe_yes, 150, 130);
    gtk_fixed_put(GTK_FIXED(fixed), pain_yes, 150, 190);
    gtk_fixed_put(GTK_FIXED(fixed), throat_yes, 150, 230);

    //data
    data_holder = gtk_entry_new();
    g_object_set_data(G_OBJECT(data_holder), "cough", (gpointer)cough_yes);
    g_object_set_data(G_OBJECT(data_holder), "fever", (gpointer)fever_yes);
    g_object_set_data(G_OBJECT(data_holder), "breathe", (gpointer)breathe_yes);
    g_object_set_data(G_OBJECT(data_holder), "pain", (gpointer)pain_yes);
    g_object_set_data(G_OBJECT(data_holder), "throat", (gpointer)throat_yes);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //button
    save_button = gtk_button_new_with_label("ثبت");
    gtk_widget_set_size_request(save_button, 150, 50);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 50, 280);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(person_record_test_handler), data_holder);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_records_win(GtkWidget *widget, gpointer home_page)
{

    close_win(NULL, home_page);

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), " تاریخچه وضعیت سلامت");

    header_label = gtk_label_new("تاریخچه سلامتی شما");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);

    new_record_button = gtk_button_new_with_label("ثبت وضعیت سلامتی");
    return_button = gtk_button_new_with_label("بازگشت");

    gtk_widget_set_size_request(new_record_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new_record_button, 10, 40);

    gtk_widget_set_size_request(return_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 260, 40);

    g_signal_connect(G_OBJECT(new_record_button), "clicked", G_CALLBACK(person_record_test_win), window);
    g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(person_home_win), window);

    Health_record *records = health_record_list(session.user.id);
    int counter = 0;
    while (records->id != -1)
    {
        char label[100];
        char *status;
        if (records->code == 1)
        {
            status = "سالم";
        }
        else if (records->code == 2)
        {
            status = "مشکوک";
        }
        else if (records->code == 3)
        {
            status = "خطرناک";
        }
        else if (records->code == 4)
        {
            status = "بیمار";
        }
        struct tm *record_date;
        record_date = localtime(&(records->time));
        sprintf(label, "%i - %s                                                %i/%i/%i  %i:%i:%i", counter + 1, status, record_date->tm_mday, (record_date->tm_mon) + 1, (record_date->tm_year) + 1900, (record_date->tm_hour) + 1, (record_date->tm_min) + 1, (record_date->tm_sec) + 1);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
        records++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_meets_new_handle(GtkWidget *widget, gpointer data)
{
    g_print("fucking here fucker");
    GtkWidget *idcode_entry = g_object_get_data(G_OBJECT(data), "idcode");
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");

    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    g_print(" %s \n", idcode);
    int rc = save_meeting_person(session.person, idcode, time(NULL));
    if (rc != 0)
    {
        if (rc == -1)
        {
            error_win(NULL, "کاربر یافت نشد");
        }
        else
        {
            error_win(NULL, " مشکلی در ‌ثبت ملاقات وجود دارد");
        }
    }
    else
    {
        person_meets_win(NULL, window);
    }
}

void person_meets_new_win(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;

    GtkWidget *idcode_label;

    //entrys
    GtkEntry *idcode_entry;

    //buttons
    GtkWidget *return_button;
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 20px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    gtk_window_set_title(GTK_WINDOW(window), " ثبت ملاقات");

    //labels
    header_label = gtk_label_new("کد ملی شخص را وارد کنید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    idcode_label = gtk_label_new(" کد ملی:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 100, 10);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 70);

    //entries
    idcode_entry = GTK_ENTRY(gtk_entry_new());

    gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 70);

    //preparing data
    data_holder = gtk_entry_new();

    g_object_set_data(G_OBJECT(data_holder), "idcode", (gpointer)idcode_entry);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    return_button = gtk_button_new_with_label("بازگشت");
    save_button = gtk_button_new_with_label("ثبت");

    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(person_meets_win), window);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(person_meets_new_handle), data_holder);

    gtk_widget_set_size_request(return_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 200, 100);
    gtk_widget_set_size_request(save_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 10, 100);

    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    gtk_widget_show_all(window);
}

void person_meets_win(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), " تاریخچه  ملاقات ها");

    header_label = gtk_label_new("تاریخچه ملاقات های شما");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);

    new_record_button = gtk_button_new_with_label("ثبت ملاقت جدید");
    return_button = gtk_button_new_with_label("بازگشت");

    gtk_widget_set_size_request(new_record_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new_record_button, 10, 40);

    gtk_widget_set_size_request(return_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 260, 40);

    g_signal_connect(G_OBJECT(new_record_button), "clicked", G_CALLBACK(person_meets_new_win), window);
    g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(person_home_win), window);

    Meet *meets = meet_list(session.user.id);
    int counter = 0;
    while (meets->id != -1)
    {
        char label[100];
        struct tm *record_date;
        record_date = localtime(&(meets->time));
        sprintf(label, "%i- %s   %s     %i/%i/%i  %i:%i:%i", counter + 1, meets->user_a.username, meets->user_b.username, record_date->tm_mday, (record_date->tm_mon) + 1, (record_date->tm_year) + 1900, (record_date->tm_hour) + 1, (record_date->tm_min) + 1, (record_date->tm_sec) + 1);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
        meets++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_edit_handle(GtkWidget *widget, gpointer user_data)
{
    GtkEntry *username_entry = g_object_get_data(user_data, "username_entry");
    GtkEntry *firstname_entry = g_object_get_data(user_data, "firstname_entry");
    GtkEntry *lastname_entry = g_object_get_data(user_data, "lastname_entry");
    GtkEntry *idcode_entry = g_object_get_data(user_data, "idcode_entry");
    GtkEntry *email_entry = g_object_get_data(user_data, "email_entry");
    GtkEntry *blood_entry = g_object_get_data(user_data, "blood_entry");
    GtkEntry *height_entry = g_object_get_data(user_data, "height_entry");
    GtkEntry *weight_entry = g_object_get_data(user_data, "weight_entry");
    GtkWidget *window = g_object_get_data(user_data, "window");

    char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    char *firstname = gtk_entry_get_text(GTK_ENTRY(firstname_entry));
    char *lastname = gtk_entry_get_text(GTK_ENTRY(lastname_entry));
    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    char *blood = gtk_entry_get_text(GTK_ENTRY(blood_entry));
    int weight = atoi(gtk_entry_get_text(GTK_ENTRY(weight_entry)));
    int height = atoi(gtk_entry_get_text(GTK_ENTRY(height_entry)));

    int rc = edit_person(session.person, username, firstname, lastname, idcode, email, blood, weight, height);
    if (rc != 0)
    {
        error_win(NULL, "مشکلی در ویرایش اطاعات وجود دارد");
    }
    else
    {
        person_home_win(NULL, window);
    }
}

void person_edit_win(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *username_label;
    GtkWidget *firstname_label;
    GtkWidget *lastname_label;
    GtkWidget *idcode_label;
    GtkWidget *email_label;
    GtkWidget *blood_label;
    GtkWidget *height_label;
    GtkWidget *weight_label;

    //entrys
    GtkEntry *username_entry;
    GtkEntry *firstname_entry;
    GtkEntry *lastname_entry;
    GtkEntry *idcode_entry;
    GtkEntry *email_entry;
    GtkEntry *blood_entry;
    GtkEntry *height_entry;
    GtkEntry *weight_entry;

    //buttons
    GtkWidget *save_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "ویرایش حساب");

    //labels
    header_label = gtk_label_new("ویرایش اظلاعات کاربری");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    username_label = gtk_label_new("نام کاربری :");
    firstname_label = gtk_label_new("نام:");
    lastname_label = gtk_label_new("نام خانوادگی:");
    idcode_label = gtk_label_new("کد ملی:");
    email_label = gtk_label_new("ایمیل:");
    blood_label = gtk_label_new("گروه خونی");
    height_label = gtk_label_new("قد:");
    weight_label = gtk_label_new("وزن:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 120, 5);
    gtk_fixed_put(GTK_FIXED(fixed), username_label, 300, 40);
    gtk_fixed_put(GTK_FIXED(fixed), firstname_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), lastname_label, 300, 110);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 150);
    gtk_fixed_put(GTK_FIXED(fixed), email_label, 300, 190);
    gtk_fixed_put(GTK_FIXED(fixed), blood_label, 300, 230);
    gtk_fixed_put(GTK_FIXED(fixed), height_label, 300, 270);
    gtk_fixed_put(GTK_FIXED(fixed), weight_label, 300, 310);

    //entries
    username_entry = GTK_ENTRY(gtk_entry_new());
    firstname_entry = GTK_ENTRY(gtk_entry_new());

    lastname_entry = GTK_ENTRY(gtk_entry_new());
    idcode_entry = GTK_ENTRY(gtk_entry_new());
    email_entry = GTK_ENTRY(gtk_entry_new());
    blood_entry = GTK_ENTRY(gtk_entry_new());
    height_entry = GTK_ENTRY(gtk_entry_new());
    weight_entry = GTK_ENTRY(gtk_entry_new());

    gtk_entry_set_text(GTK_ENTRY(username_entry), session.user.username);
    gtk_entry_set_text(GTK_ENTRY(firstname_entry), session.person.firstname);
    gtk_entry_set_text(GTK_ENTRY(lastname_entry), session.person.lastname);
    gtk_entry_set_text(GTK_ENTRY(idcode_entry), session.person.idcode);
    gtk_entry_set_text(GTK_ENTRY(email_entry), session.person.email);
    gtk_entry_set_text(GTK_ENTRY(blood_entry), session.person.blood);
    char height[5];
    sprintf(height, "%i", session.person.height);
    gtk_entry_set_text(GTK_ENTRY(height_entry), height);
    char weight[5];
    sprintf(weight, "%i", session.person.weight);
    gtk_entry_set_text(GTK_ENTRY(weight_entry), weight);

    gtk_fixed_put(GTK_FIXED(fixed), username_entry, 100, 40);
    gtk_fixed_put(GTK_FIXED(fixed), firstname_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), lastname_entry, 100, 110);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 150);
    gtk_fixed_put(GTK_FIXED(fixed), email_entry, 100, 190);
    gtk_fixed_put(GTK_FIXED(fixed), blood_entry, 100, 230);
    gtk_fixed_put(GTK_FIXED(fixed), height_entry, 100, 270);
    gtk_fixed_put(GTK_FIXED(fixed), weight_entry, 100, 310);

    //preparing data
    data_holder = gtk_entry_new();
    g_object_set_data(G_OBJECT(data_holder), "username_entry", (gpointer)username_entry);
    g_object_set_data(G_OBJECT(data_holder), "firstname_entry", (gpointer)firstname_entry);
    g_object_set_data(G_OBJECT(data_holder), "lastname_entry", (gpointer)lastname_entry);
    g_object_set_data(G_OBJECT(data_holder), "idcode_entry", (gpointer)idcode_entry);
    g_object_set_data(G_OBJECT(data_holder), "email_entry", (gpointer)email_entry);
    g_object_set_data(G_OBJECT(data_holder), "blood_entry", (gpointer)blood_entry);
    g_object_set_data(G_OBJECT(data_holder), "height_entry", (gpointer)height_entry);
    g_object_set_data(G_OBJECT(data_holder), "weight_entry", (gpointer)weight_entry);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    save_button = gtk_button_new_with_label(" ثبت تغییرات");
    return_button = gtk_button_new_with_label("بازگشت");

    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(person_edit_handle), data_holder);
    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(person_home_win), window);

    gtk_widget_set_size_request(save_button, 180, 40);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 20, 350);

    gtk_widget_set_size_request(return_button, 180, 40);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 210, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_hospitals_list(GtkWidget *widget, gpointer data)
{
    GtkWidget *city_entry = g_object_get_data(G_OBJECT(data), "city");
    GtkWidget *district_entry = g_object_get_data(G_OBJECT(data), "district");
    // GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");
    char *city = gtk_entry_get_text(GTK_ENTRY(city_entry));
    int district = atoi(gtk_entry_get_text(GTK_ENTRY(district_entry)));

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "مراکز درمانی نزدیک شما");

    header_label = gtk_label_new(" مراکز درمانی نزدیک شما ");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);

    Hospital *hospitals = hospital_list(city, district);
    int counter = 0;
    while (hospitals->id != -1)
    {
        char label[100];

        sprintf(label, "-- %s --", hospitals->name);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 100, counter * 30 + 100);
        hospitals++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_hospitals_win(GtkWidget *widget, gpointer home_page)
{
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *district_label;
    GtkWidget *city_label;

    //entrys
    GtkEntry *city_entry;
    GtkEntry *district_entry;

    //buttons
    GtkWidget *return_button;
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 20px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    gtk_window_set_title(GTK_WINDOW(window), " نمایش مراکز درمانی ");

    //labels
    header_label = gtk_label_new("اطلاعات محل زندگی خود را وارد کنید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    city_label = gtk_label_new(" نام شهر:");
    district_label = gtk_label_new(" کد محله :");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 100, 10);
    gtk_fixed_put(GTK_FIXED(fixed), city_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), district_label, 300, 110);

    //entries
    city_entry = GTK_ENTRY(gtk_entry_new());
    district_entry = GTK_ENTRY(gtk_entry_new());

    gtk_fixed_put(GTK_FIXED(fixed), city_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), district_entry, 100, 110);

    //preparing data
    data_holder = gtk_entry_new();

    g_object_set_data(G_OBJECT(data_holder), "city", (gpointer)city_entry);
    g_object_set_data(G_OBJECT(data_holder), "district", (gpointer)district_entry);

    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    return_button = gtk_button_new_with_label("بازگشت");
    save_button = gtk_button_new_with_label("نمایش");

    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(close_win), window);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(person_hospitals_list), data_holder);

    gtk_widget_set_size_request(return_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 200, 150);
    gtk_widget_set_size_request(save_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 10, 150);

    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    gtk_widget_show_all(window);
}

void person_new_visit_red(GtkWidget *widget, gpointer data)
{
    GtkWidget *place_entry = g_object_get_data(G_OBJECT(data), "place");
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");
    GtkWidget *ask_win = g_object_get_data(G_OBJECT(data), "ask_win");
    close_win(NULL, ask_win);
    char *place_name = gtk_entry_get_text(GTK_ENTRY(place_entry));
    Owner o;
    o.id = 0;
    o.user.id = 0;
    o.place_name = place_name;
    o = owner_get(o);
    save_visit(session.person, place_name, time(NULL), 1);
    person_visits_win(NULL, window);
}

void person_new_visit_handler(GtkWidget *widget, gpointer data)
{
    g_print("fucking here");
    GtkWidget *place_entry = g_object_get_data(G_OBJECT(data), "place");
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");
    char *place_name = gtk_entry_get_text(GTK_ENTRY(place_entry));
    g_print("fucking here");
    Owner o;
    o.id = 0;
    o.user.id = 0;
    o.place_name = place_name;
    o = owner_get(o);
    g_print("fucking here");
    if (o.id == -1)
    {
        gtk_entry_set_text(GTK_ENTRY(place_entry), "");
        error_win(NULL, "مکان مورد نظر یافت نشد");
    }
    else
    {
        if (o.status == 0)
        {
            save_visit(session.person, place_name, time(NULL), 0);
            person_visits_win(NULL, window);
        }
        else
        {
            GtkWidget *window;
            GtkWidget *top_label;
            GtkWidget *error_label;

            GtkCssProvider *provider;
            GtkStyleContext *context;
            GtkWidget *fixed;
            GtkWidget *return_button;
            GtkWidget *ok_button;

            window = gtk_application_window_new(app);

            fixed = gtk_fixed_new();
            gtk_container_add(GTK_CONTAINER(window), fixed);
            gtk_widget_show(fixed);

            provider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(provider,
                                            "label {"
                                            " font-size: 30px;"
                                            "}",
                                            -1,
                                            NULL);
            top_label = gtk_label_new("هشدار");
            error_label = gtk_label_new("وضعیت مکان مورد نظر قرمز است آیا از رفتن خود اطمینان دارید؟");
            context = gtk_widget_get_style_context(top_label);
            gtk_style_context_add_provider(context,
                                           GTK_STYLE_PROVIDER(provider),
                                           GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

            return_button = gtk_button_new_with_label("خیر");
            ok_button = gtk_button_new_with_label("بلی");
            gtk_window_set_title(GTK_WINDOW(window), "هشدار");
            gtk_fixed_put(GTK_FIXED(fixed), top_label, 100, 0);
            gtk_fixed_put(GTK_FIXED(fixed), error_label, 10, 90);
            g_object_set_data(G_OBJECT(data), "ask_win", window);

            g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(close_win), (gpointer)window);
            g_signal_connect(G_OBJECT(ok_button), "clicked", G_CALLBACK(person_new_visit_red), (gpointer)data);

            gtk_widget_set_size_request(return_button, 100, 40);
            gtk_fixed_put(GTK_FIXED(fixed), return_button, 100, 150);
            gtk_widget_set_size_request(ok_button, 100, 40);
            gtk_fixed_put(GTK_FIXED(fixed), ok_button, 200, 150);
            gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
            gtk_widget_show_all(window);
        }
    }
}

void person_new_visit_win(GtkWidget *widget, gpointer visits_win)
{
    close_win(NULL, visits_win);
    GtkWidget *window;
    //labels
    GtkWidget *header_label;

    GtkWidget *place_label;

    //entrys
    GtkEntry *place_entry;

    //buttons
    GtkWidget *return_button;
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 20px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    gtk_window_set_title(GTK_WINDOW(window), " ثبت مکان");

    //labels
    header_label = gtk_label_new("نام محل را وارد کنید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    place_label = gtk_label_new(" نام مکان:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 100, 10);
    gtk_fixed_put(GTK_FIXED(fixed), place_label, 300, 70);

    //entries
    place_entry = GTK_ENTRY(gtk_entry_new());

    gtk_fixed_put(GTK_FIXED(fixed), place_entry, 100, 70);

    //preparing data
    data_holder = gtk_entry_new();

    g_object_set_data(G_OBJECT(data_holder), "place", (gpointer)place_entry);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    return_button = gtk_button_new_with_label("بازگشت");
    save_button = gtk_button_new_with_label("ثبت");

    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(person_visits_win), window);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(person_new_visit_handler), data_holder);

    gtk_widget_set_size_request(return_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 200, 100);
    gtk_widget_set_size_request(save_button, 150, 30);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 10, 100);

    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    gtk_widget_show_all(window);
}

void person_visits_win(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);

    GtkWidget *window;
    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), " تاریخچه رفت و آمد");

    header_label = gtk_label_new("تاریخچه  رفت وآمد شما");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);

    new_record_button = gtk_button_new_with_label("ثبت مکان جدید");
    return_button = gtk_button_new_with_label("بازگشت");

    gtk_widget_set_size_request(new_record_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new_record_button, 10, 40);

    gtk_widget_set_size_request(return_button, 240, 40);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 260, 40);

    g_signal_connect(G_OBJECT(new_record_button), "clicked", G_CALLBACK(person_new_visit_win), window);
    g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(person_home_win), window);

    Visit *visits = visit_list(session.user.id);
    int counter = 0;
    while (visits->id != -1)
    {
        char label[100];
        char *status;
        if (visits->status == 0)
        {
            status = "سفید";
        }
        else if (visits->status == 1)
        {
            status = "قرمز";
        }

        struct tm *record_date;
        record_date = localtime(&(visits->time));
        sprintf(label, "%i - %s           %i/%i/%i  %i:%i:%i            %s", counter + 1, visits->place_name, record_date->tm_mday, (record_date->tm_mon) + 1, (record_date->tm_year) + 1900, (record_date->tm_hour) + 1, (record_date->tm_min) + 1, (record_date->tm_sec) + 1, status);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
        visits++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void person_logout(GtkWidget *widget, gpointer home_win)
{
    Person p;
    User u;
    Owner o;
    session.person = p;
    session.user = u;
    session.owner = o;
    close_win(NULL, home_win);

    login_win(NULL, NULL);
}

void person_home_win(GtkWidget *widget, gpointer data)
{
    close_win(NULL, data);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *welcome_label;
    GtkWidget *status_label;
    GtkWidget *statistic_label;
    GtkWidget *sick_label;
    GtkWidget *dieded_label;
    GtkWidget *improved_label;
    GtkWidget *sick_num_label;
    GtkWidget *dieded_num_label;
    GtkWidget *improved_num_label;

    //buttons
    GtkWidget *edit_button;
    GtkWidget *meets_button;
    GtkWidget *health_button;
    GtkWidget *hospitals_button;
    GtkWidget *visits_button;
    GtkWidget *logout_button;
    GtkWidget *tutorials_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "منوی اصلی");

    //labels
    header_label = gtk_label_new(" به KoWeed خوش آمدید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    char welcome_msg[100] = "خوش آمدی ";
    strcat(welcome_msg, session.person.firstname);
    g_print("\n%i \n", session.person.id);

    welcome_label = gtk_label_new(welcome_msg);
    char *health_msg;
    if (session.person.status == 1)
    {
        health_msg = "خوشبختانه شما سالم هستید";
    }
    else if (session.person.status == 2)
    {
        health_msg = "شما مشکوک به بیماری هستید";
    }
    else if (session.person.status == 3)
    {
        health_msg = "وضعیت شما خطرناک است";
    }
    else if (session.person.status == 4)
    {
        health_msg = " شما مبتلا هستید";
    }
    else
    {
        health_msg = " وضعیت شما نامشخص است";
    }

    status_label = gtk_label_new(health_msg);
    statistic_label = gtk_label_new("آمار کرونا تا این لحظه");
    dieded_label = gtk_label_new("فوت شده");
    sick_label = gtk_label_new("مبتلا شده");
    improved_label = gtk_label_new("بهبود یافته");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    gtk_fixed_put(GTK_FIXED(fixed), welcome_label, 320, 70);
    gtk_fixed_put(GTK_FIXED(fixed), status_label, 270, 110);

    // //buttons

    edit_button = gtk_button_new_with_label("ویرایش اطلاعات");
    meets_button = gtk_button_new_with_label("ملاقات ها");
    health_button = gtk_button_new_with_label("وضعیت سلامت");
    hospitals_button = gtk_button_new_with_label(" مراکز درمانی");
    visits_button = gtk_button_new_with_label("اماکن");
    tutorials_button = gtk_button_new_with_label("آموزش های کرونایی");
    logout_button = gtk_button_new_with_label("خروج");

    gtk_widget_set_size_request(edit_button, 245, 40);
    gtk_widget_set_size_request(meets_button, 245, 40);
    gtk_widget_set_size_request(health_button, 245, 40);
    gtk_widget_set_size_request(hospitals_button, 245, 40);
    gtk_widget_set_size_request(visits_button, 245, 40);
    gtk_widget_set_size_request(tutorials_button, 245, 40);
    gtk_widget_set_size_request(logout_button, 490, 40);

    gtk_fixed_put(GTK_FIXED(fixed), edit_button, 10, 150);
    gtk_fixed_put(GTK_FIXED(fixed), meets_button, 260, 150);
    gtk_fixed_put(GTK_FIXED(fixed), health_button, 10, 200);
    gtk_fixed_put(GTK_FIXED(fixed), hospitals_button, 260, 200);
    gtk_fixed_put(GTK_FIXED(fixed), visits_button, 10, 250);
    gtk_fixed_put(GTK_FIXED(fixed), tutorials_button, 260, 250);
    gtk_fixed_put(GTK_FIXED(fixed), logout_button, 10, 300);

    g_signal_connect(GTK_BUTTON(health_button), "clicked", G_CALLBACK(person_records_win), window);
    g_signal_connect(GTK_BUTTON(meets_button), "clicked", G_CALLBACK(person_meets_win), window);
    g_signal_connect(GTK_BUTTON(edit_button), "clicked", G_CALLBACK(person_edit_win), window);
    g_signal_connect(GTK_BUTTON(hospitals_button), "clicked", G_CALLBACK(person_hospitals_win), window);
    g_signal_connect(GTK_BUTTON(visits_button), "clicked", G_CALLBACK(person_visits_win), window);
    g_signal_connect(GTK_BUTTON(logout_button), "clicked", G_CALLBACK(person_logout), window);

    // gtk_widget_set_size_request(save_button, 180, 40);
    // gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void owner_clean_place(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);

    GtkWidget *window;
    GtkWidget *top_label;
    GtkWidget *error_label;
    GtkWidget *image;
    GtkCssProvider *provider;
    GtkStyleContext *context;
    GtkWidget *fixed;
    GtkWidget *return_button;

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 40px;"
                                    "}",
                                    -1,
                                    NULL);
    top_label = gtk_label_new("");
    error_label = gtk_label_new("مکان شما با موفقیت ضد عفونی شد");
    context = gtk_widget_get_style_context(top_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    return_button = gtk_button_new_with_label("بازگشت");

    image = gtk_image_new_from_file("./assets/success.png");
    gtk_window_set_title(GTK_WINDOW(window), "تایید");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), top_label, 480, 0);
    gtk_fixed_put(GTK_FIXED(fixed), error_label, 450, 150);
    session.owner.status = 0;
    owner_update(session.owner);

    g_signal_connect(G_OBJECT(return_button), "clicked", G_CALLBACK(owner_home_win), (gpointer)window);
    gtk_widget_set_size_request(return_button, 400, 60);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 320, 260);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_widget_show_all(window);
}

void owner_edit_handle(GtkWidget *widget, gpointer user_data)
{
    GtkEntry *username_entry = g_object_get_data(user_data, "username_entry");
    GtkEntry *place_name_entry = g_object_get_data(user_data, "place_name_entry");
    GtkEntry *district_entry = g_object_get_data(user_data, "district_entry");
    GtkEntry *idcode_entry = g_object_get_data(user_data, "idcode_entry");
    GtkEntry *email_entry = g_object_get_data(user_data, "email_entry");
    GtkEntry *city_entry = g_object_get_data(user_data, "city_entry");
    GtkWidget *window = g_object_get_data(user_data, "window");
    char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    char *place_name = gtk_entry_get_text(GTK_ENTRY(place_name_entry));
    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    char *city = gtk_entry_get_text(GTK_ENTRY(city_entry));
    int district = atoi(gtk_entry_get_text(GTK_ENTRY(district_entry)));
    int rc = edit_owner(session.owner, username, place_name, district, idcode, email, city);
    if (rc != 0)
    {
        error_win(NULL, "مشکلی در ویرایش اطاعات وجود دارد");
    }
    else
    {
        owner_home_win(NULL, window);
    }
}

void owner_edit_page(GtkWidget *widget, gpointer home_page)
{
    close_win(NULL, home_page);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *username_label;
    GtkWidget *place_name_label;
    GtkWidget *district_label;
    GtkWidget *city_label;
    GtkWidget *email_label;
    GtkWidget *idcode_label;

    //entrys
    GtkEntry *username_entry;
    GtkEntry *place_name_entry;
    GtkEntry *district_entry;
    GtkEntry *idcode_entry;
    GtkEntry *email_entry;
    GtkEntry *city_entry;

    //buttons
    GtkWidget *save_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "ویرایش حساب");

    //labels
    header_label = gtk_label_new("ویرایش اظلاعات کاربری");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    username_label = gtk_label_new("نام کاربری :");
    place_name_label = gtk_label_new("نام مکان:");
    district_label = gtk_label_new("کد محله:");
    city_label = gtk_label_new("نام شهر :");
    email_label = gtk_label_new("ایمیل:");
    idcode_label = gtk_label_new(" کد ملی:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 120, 5);
    gtk_fixed_put(GTK_FIXED(fixed), username_label, 300, 40);
    gtk_fixed_put(GTK_FIXED(fixed), place_name_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), district_label, 300, 110);
    gtk_fixed_put(GTK_FIXED(fixed), city_label, 300, 150);
    gtk_fixed_put(GTK_FIXED(fixed), email_label, 300, 190);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 230);

    //entries
    username_entry = GTK_ENTRY(gtk_entry_new());
    place_name_entry = GTK_ENTRY(gtk_entry_new());

    district_entry = GTK_ENTRY(gtk_entry_new());
    city_entry = GTK_ENTRY(gtk_entry_new());
    email_entry = GTK_ENTRY(gtk_entry_new());
    idcode_entry = GTK_ENTRY(gtk_entry_new());

    gtk_entry_set_text(GTK_ENTRY(username_entry), session.user.username);
    gtk_entry_set_text(GTK_ENTRY(place_name_entry), session.owner.place_name);
    // gtk_entry_set_text(GTK_ENTRY(district_entry), session.owner.district);
    gtk_entry_set_text(GTK_ENTRY(city_entry), session.owner.city);
    gtk_entry_set_text(GTK_ENTRY(email_entry), session.owner.email);
    gtk_entry_set_text(GTK_ENTRY(idcode_entry), session.owner.idcode);
    char district[5];
    sprintf(district, "%i", session.owner.district);
    gtk_entry_set_text(GTK_ENTRY(district_entry), district);

    gtk_fixed_put(GTK_FIXED(fixed), username_entry, 100, 40);
    gtk_fixed_put(GTK_FIXED(fixed), place_name_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), district_entry, 100, 110);
    gtk_fixed_put(GTK_FIXED(fixed), city_entry, 100, 150);
    gtk_fixed_put(GTK_FIXED(fixed), email_entry, 100, 190);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 230);

    //preparing data
    data_holder = gtk_entry_new();
    g_object_set_data(G_OBJECT(data_holder), "username_entry", (gpointer)username_entry);
    g_object_set_data(G_OBJECT(data_holder), "place_name_entry", (gpointer)place_name_entry);
    g_object_set_data(G_OBJECT(data_holder), "district_entry", (gpointer)district_entry);
    g_object_set_data(G_OBJECT(data_holder), "city_entry", (gpointer)city_entry);
    g_object_set_data(G_OBJECT(data_holder), "email_entry", (gpointer)email_entry);
    g_object_set_data(G_OBJECT(data_holder), "idcode_entry", (gpointer)idcode_entry);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    save_button = gtk_button_new_with_label(" ثبت تغییرات");
    return_button = gtk_button_new_with_label("بازگشت");

    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(owner_edit_handle), data_holder);
    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(owner_home_win), window);

    gtk_widget_set_size_request(save_button, 180, 40);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 20, 350);

    gtk_widget_set_size_request(return_button, 180, 40);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 210, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}
void owner_home_win(GtkWidget *widget, gpointer data)
{
    close_win(NULL, data);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *welcome_label;
    GtkWidget *status_label;
    GtkWidget *statistic_label;
    GtkWidget *sick_label;
    GtkWidget *danger_label;
    GtkWidget *sus_label;
    GtkWidget *sick_num_label;
    GtkWidget *danger_num_label;
    GtkWidget *sus_num_label;

    //buttons
    GtkWidget *edit_button;
    GtkWidget *clean_button;
    GtkWidget *logout_button;
    GtkWidget *tutorials_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "منوی اصلی");

    //labels
    header_label = gtk_label_new(" به KoWeed خوش آمدید");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    char welcome_msg[100] = "خوش آمدی ";
    strcat(welcome_msg, session.user.username);
    g_print("\n%i \n", session.owner.id);

    welcome_label = gtk_label_new(welcome_msg);
    char *health_msg;
    if (session.owner.status == 0)
    {
        health_msg = " وضعیت مکان شما سفید است";
    }
    else if (session.owner.status == 1)
    {
        health_msg = "وضعیت مکان شما قرمز است";
    }
    else
    {
        health_msg = " وضعیت مکان شما نامشخص است";
    }

    status_label = gtk_label_new(health_msg);
    statistic_label = gtk_label_new("موارد بازدید ناسالم از مکان شما");
    danger_label = gtk_label_new("خطرناک");
    sick_label = gtk_label_new("مبتلا شده");
    sus_label = gtk_label_new("مشکوک");
    int sick_counter = 0;
    int sus_counter = 0;
    int danger_counter = 0;

    Visit *visits = visit_list(0);
    while (visits->id != -1)
    {
        g_print("%s   %s \n", visits->place_name, session.owner.place_name);
        if (!strcmp(visits->place_name, session.owner.place_name))
        {
            Person p;
            p.id = 0;
            p.user.id = visits->user.id;
            p = person_get(p);
            if (p.status == 4)
            {
                sick_counter++;
            }
            else if (p.status == 3)
            {
                danger_counter++;
            }
            else if (p.status == 2)
            {
                sus_counter++;
            }
        }
        visits++;
    }
    char d_num[3];
    sprintf(d_num, "%i", danger_counter);
    danger_num_label = gtk_label_new(d_num);
    char si_num[3];
    sprintf(si_num, "%i", sick_counter);
    sick_num_label = gtk_label_new(si_num);
    char su_num[3];
    sprintf(su_num, "%i", sus_counter);
    sus_num_label = gtk_label_new(su_num);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    gtk_fixed_put(GTK_FIXED(fixed), welcome_label, 320, 70);
    gtk_fixed_put(GTK_FIXED(fixed), status_label, 270, 110);
    gtk_fixed_put(GTK_FIXED(fixed), statistic_label, 150, 300);
    gtk_fixed_put(GTK_FIXED(fixed), sick_label, 20, 400);
    gtk_fixed_put(GTK_FIXED(fixed), sick_num_label, 40, 360);
    gtk_fixed_put(GTK_FIXED(fixed), danger_label, 230, 400);
    gtk_fixed_put(GTK_FIXED(fixed), danger_num_label, 250, 360);
    gtk_fixed_put(GTK_FIXED(fixed), sus_label, 410, 400);
    gtk_fixed_put(GTK_FIXED(fixed), sus_num_label, 430, 360);

    // //buttons

    edit_button = gtk_button_new_with_label("ویرایش اطلاعات");
    clean_button = gtk_button_new_with_label(" اعلام ضد عفونی");

    tutorials_button = gtk_button_new_with_label("آموزش های کرونایی");
    logout_button = gtk_button_new_with_label("خروج");

    gtk_widget_set_size_request(edit_button, 245, 40);
    gtk_widget_set_size_request(clean_button, 245, 40);

    gtk_widget_set_size_request(tutorials_button, 245, 40);
    gtk_widget_set_size_request(logout_button, 490, 40);

    gtk_fixed_put(GTK_FIXED(fixed), edit_button, 10, 150);
    gtk_fixed_put(GTK_FIXED(fixed), clean_button, 260, 150);

    gtk_fixed_put(GTK_FIXED(fixed), tutorials_button, 260, 200);
    gtk_fixed_put(GTK_FIXED(fixed), logout_button, 10, 250);

    g_signal_connect(GTK_BUTTON(clean_button), "clicked", G_CALLBACK(owner_clean_place), window);
    g_signal_connect(GTK_BUTTON(edit_button), "clicked", G_CALLBACK(owner_edit_page), window);
    g_signal_connect(GTK_BUTTON(logout_button), "clicked", G_CALLBACK(person_logout), window);

    // gtk_widget_set_size_request(save_button, 180, 40);
    // gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void admin_users_list_page(GtkWidget *widget, gpointer home_page)
{

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "کاربران نرم افزار");

    header_label = gtk_label_new("لیست کاربران نرم افزار");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    Person *persons = person_list();
    int counter = 0;
    while (persons->id != -1)
    {
        char label[100];
        char *status;
        if (persons->status == 1)
        {
            status = "سالم";
        }
        else if (persons->status == 2)
        {
            status = "مشکوک";
        }
        else if (persons->status == 3)
        {
            status = "خطرناک";
        }
        else if (persons->status == 4)
        {
            status = "بیمار";
        }
        else if (persons->status == -1)
        {
            status = "فوت شده";
        }

        sprintf(label, "%i- %s              %s              %s          %s", counter + 1, persons->firstname, persons->lastname, persons->idcode, status);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
        persons++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void admin_owners_list_page(GtkWidget *widget, gpointer home_page)
{

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "کاربران نرم افزار");

    header_label = gtk_label_new("لیست کاربران نرم افزار");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    Owner *owners = owner_list();
    int counter = 0;
    while (owners->id != -1)
    {
        char label[100];
        char *status;
        if (owners->status == 0)
        {
            status = "سفید";
        }
        else if (owners->status == 2)
        {
            status = "قرمز";
        }
        else
        {
            status = "نامشخص";
        }

        sprintf(label, "%i- %s              %s              %s  ", counter + 1, owners->place_name, owners->idcode, status);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
        owners++;
        counter++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void admin_handle_fine(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");
    Person *person = g_object_get_data(G_OBJECT(data), "person");
    person->status = 2;
    person_update(*person);
    close_win(NULL, window);
    admin_sick_list_page(NULL, NULL);
}

void admin_handle_die(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = g_object_get_data(G_OBJECT(data), "window");
    Person *person = g_object_get_data(G_OBJECT(data), "person");
    person->status = -1;
    person_update(*person);
    close_win(NULL, window);
    admin_sick_list_page(NULL, NULL);
}

void admin_sick_list_page(GtkWidget *widget, gpointer home_page)
{
    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), " مبتلایان");

    header_label = gtk_label_new(" لیست مبتلایان");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    Person *persons = person_list();
    int counter = 0;
    while (persons->id != -1)
    {
        if (persons->status == 4)
        {
            char label[100];

            sprintf(label, "%i- %s  %s   %s", counter + 1, persons->firstname, persons->lastname, persons->idcode);
            GtkWidget *record_label = gtk_label_new(label);
            GtkWidget *fine_button = gtk_button_new_with_label("ترخیص");
            GtkWidget *die_button = gtk_button_new_with_label("فوت");
            GtkWidget *data_holder = gtk_entry_new();
            g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);
            g_object_set_data(G_OBJECT(data_holder), "person", (gpointer)persons);

            gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
            gtk_fixed_put(GTK_FIXED(fixed), fine_button, 380, counter * 30 + 100);
            gtk_fixed_put(GTK_FIXED(fixed), die_button, 450, counter * 30 + 100);
            g_signal_connect(GTK_BUTTON(fine_button), "clicked", G_CALLBACK(admin_handle_fine), data_holder);
            g_signal_connect(GTK_BUTTON(die_button), "clicked", G_CALLBACK(admin_handle_die), data_holder);

            counter++;
        }
        persons++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void admin_dead_list_page(GtkWidget *widget, gpointer home_page)
{

    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), " فوت شدگان ");

    header_label = gtk_label_new(" لیست کاربران فوت شده");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    Person *persons = person_list();
    int counter = 0;
    while (persons->id != -1)
    {
        if (persons->status == -1)
        {
            char label[100];

            sprintf(label, "%i- %s  %s   %s", counter + 1, persons->firstname, persons->lastname, persons->idcode);
            GtkWidget *record_label = gtk_label_new(label);
            gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 100);
            counter++;
        }
        persons++;
    }

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void admin_new_hospital_handle(GtkWidget *widget, gpointer data)
{
    GtkEntry *name_entry = g_object_get_data(data, "name");
    GtkEntry *city_entry = g_object_get_data(data, "city");
    GtkEntry *district_entry = g_object_get_data(data, "district");
    GtkWidget *window = g_object_get_data(data, "window");
    char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    char *city = gtk_entry_get_text(GTK_ENTRY(city_entry));
    int district = atoi(gtk_entry_get_text(GTK_ENTRY(district_entry)));

    Hospital h;
    h.name = name;
    h.city = city;
    h.district = district;
    int rc = hospital_add(h);
    if (rc != 0)
    {
        error_win(NULL, "مشکلی در ثبت بیمارستان وجود دارد");
    }
    else
    {
        close_win(NULL, window);
        admin_home_win(NULL, NULL);
    }
}

void admin_hospitals_new(GtkWidget *widget, gpointer data)
{
    close_win(NULL, data);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *account_info_label;
    GtkWidget *name_label;
    GtkWidget *city_label;
    GtkWidget *district_label;

    //entrys
    GtkEntry *name_entry;
    GtkEntry *city_entry;
    GtkEntry *district_entry;

    //radio
    GtkWidget *normal_user;
    GtkWidget *owner_user;
    GtkWidget *layout_holder;

    //buttons
    GtkWidget *return_button;
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    gtk_window_set_title(GTK_WINDOW(window), "ثبت بیمارستان جدید  ");

    //labels
    header_label = gtk_label_new("اطلاعات بیمارستان را وارد کنید ");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    name_label = gtk_label_new("نام:");
    city_label = gtk_label_new(" شهر :");
    district_label = gtk_label_new("کد منطقه:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 100, 10);
    gtk_fixed_put(GTK_FIXED(fixed), name_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), city_label, 300, 110);
    gtk_fixed_put(GTK_FIXED(fixed), district_label, 300, 150);

    //entries
    name_entry = GTK_ENTRY(gtk_entry_new());
    city_entry = GTK_ENTRY(gtk_entry_new());
    district_entry = GTK_ENTRY(gtk_entry_new());

    gtk_fixed_put(GTK_FIXED(fixed), name_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), city_entry, 100, 110);
    gtk_fixed_put(GTK_FIXED(fixed), district_entry, 100, 150);

    //preparing data
    data_holder = gtk_entry_new();

    g_object_set_data(G_OBJECT(data_holder), "name", (gpointer)name_entry);
    g_object_set_data(G_OBJECT(data_holder), "city", (gpointer)city_entry);
    g_object_set_data(G_OBJECT(data_holder), "district", (gpointer)district_entry);

    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    return_button = gtk_button_new_with_label("بازگشت");
    save_button = gtk_button_new_with_label("ثبت ");

    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(admin_hospitals_list_page), window);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(admin_new_hospital_handle), data_holder);

    gtk_widget_set_size_request(return_button, 100, 30);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 200, 220);
    gtk_widget_set_size_request(save_button, 100, 30);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 80, 220);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    gtk_widget_show_all(window);
}

void admin_hospitals_list_page(GtkWidget *widget, gpointer data)
{
    GtkWidget *window;

    //label
    GtkWidget *header_label;

    //buttons
    GtkWidget *new_record_button;
    GtkWidget *return_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "مراکز درمانی");
    header_label = gtk_label_new("لیست بیمارستانها");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    Hospital *hospitals = hospital_list("", -1);
    int counter = 0;
    while (hospitals->id != -1)
    {
        char label[100];

        sprintf(label, "%i- %s                   %s                %i ", counter + 1, hospitals->name, hospitals->city, hospitals->district);
        GtkWidget *record_label = gtk_label_new(label);
        gtk_fixed_put(GTK_FIXED(fixed), record_label, 20, counter * 30 + 110);
        hospitals++;
        counter++;
    }

    new_record_button = gtk_button_new_with_label(" ثبت بیمارستان");
    gtk_widget_set_size_request(new_record_button, 480, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new_record_button, 10, 60);

    g_signal_connect(GTK_BUTTON(new_record_button), "clicked", G_CALLBACK(admin_hospitals_new), window);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}
void admin_home_win(GtkWidget *widget, gpointer data)
{
    close_win(NULL, data);
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *welcome_label;
    GtkWidget *status_label;
    GtkWidget *statistic_label;
    GtkWidget *sick_label;
    GtkWidget *dieded_label;
    GtkWidget *improved_label;
    GtkWidget *sick_num_label;
    GtkWidget *dieded_num_label;
    GtkWidget *improved_num_label;

    //buttons
    GtkWidget *edit_button;
    GtkWidget *users_button;
    GtkWidget *sick_button;
    GtkWidget *hospitals_button;
    GtkWidget *died_button;
    GtkWidget *logout_button;
    GtkWidget *works_button;

    //layouts
    GtkWidget *fixed;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "منوی اصلی");

    //labels
    header_label = gtk_label_new("پنل مدیریت نرم افزار KoWeed .");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    char welcome_msg[100] = "خوش آمدی ";
    strcat(welcome_msg, session.user.username);
    g_print("\n%i \n", session.user.id);

    welcome_label = gtk_label_new(welcome_msg);

    status_label = gtk_label_new("");
    statistic_label = gtk_label_new("آمار کرونا تا این لحظه");
    dieded_label = gtk_label_new("فوت شده");
    sick_label = gtk_label_new("مبتلا شده");
    improved_label = gtk_label_new("بهبود یافته");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 130, 10);
    gtk_fixed_put(GTK_FIXED(fixed), welcome_label, 320, 70);
    gtk_fixed_put(GTK_FIXED(fixed), status_label, 270, 110);

    // //buttons

    edit_button = gtk_button_new_with_label("ویرایش اطلاعات");
    users_button = gtk_button_new_with_label("کاربران نرم افزار");
    sick_button = gtk_button_new_with_label(" افراد مبتلا");
    hospitals_button = gtk_button_new_with_label(" مراکز درمانی");
    died_button = gtk_button_new_with_label("فوت شدگان");
    works_button = gtk_button_new_with_label(" صاحبین کسب و کار ");
    logout_button = gtk_button_new_with_label("خروج");

    gtk_widget_set_size_request(edit_button, 245, 40);
    gtk_widget_set_size_request(users_button, 245, 40);
    gtk_widget_set_size_request(sick_button, 245, 40);
    gtk_widget_set_size_request(hospitals_button, 245, 40);
    gtk_widget_set_size_request(died_button, 245, 40);
    gtk_widget_set_size_request(works_button, 245, 40);
    gtk_widget_set_size_request(logout_button, 490, 40);

    gtk_fixed_put(GTK_FIXED(fixed), edit_button, 10, 150);
    gtk_fixed_put(GTK_FIXED(fixed), users_button, 260, 150);
    gtk_fixed_put(GTK_FIXED(fixed), sick_button, 10, 200);
    gtk_fixed_put(GTK_FIXED(fixed), hospitals_button, 260, 200);
    gtk_fixed_put(GTK_FIXED(fixed), died_button, 10, 250);
    gtk_fixed_put(GTK_FIXED(fixed), works_button, 260, 250);
    gtk_fixed_put(GTK_FIXED(fixed), logout_button, 10, 300);

    g_signal_connect(GTK_BUTTON(sick_button), "clicked", G_CALLBACK(admin_sick_list_page), window);
    g_signal_connect(GTK_BUTTON(users_button), "clicked", G_CALLBACK(admin_users_list_page), window);
    g_signal_connect(GTK_BUTTON(edit_button), "clicked", G_CALLBACK(person_edit_win), window);
    g_signal_connect(GTK_BUTTON(hospitals_button), "clicked", G_CALLBACK(admin_hospitals_list_page), window);
    g_signal_connect(GTK_BUTTON(died_button), "clicked", G_CALLBACK(admin_dead_list_page), window);
    g_signal_connect(GTK_BUTTON(logout_button), "clicked", G_CALLBACK(person_logout), window);
    g_signal_connect(GTK_BUTTON(works_button), "clicked", G_CALLBACK(admin_owners_list_page), window);

    // gtk_widget_set_size_request(save_button, 180, 40);
    // gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void handle_login(GtkWidget *widget, gpointer user_pass)
{
    // GtkWidget username_entry, *password_entry;
    GtkEntry *username_entry = g_object_get_data(user_pass, "username");
    GtkEntry *password_entry = g_object_get_data(user_pass, "password");
    GtkWidget *window = g_object_get_data(user_pass, "window");

    char *username = strdup(gtk_entry_get_text(GTK_ENTRY(username_entry)));
    char *password = strdup(gtk_entry_get_text(GTK_ENTRY(password_entry)));

    User user;
    user.id = 0;
    user.username = strdup(username);
    user.pass = strdup(password);

    user = user_get(user);

    if (user.id == -1)
    {
        error_win(NULL, "نام کاربری یا رمز عبور اشتباه است");
    }
    else
    {
        if (user.type == 2)
        {

            Person person;
            person.id = 0;
            person.user = user;
            person = person_get(person);
            session.user = user;
            session.person = person;
            close_win(NULL, window);
            g_print("logged in user person");
            person_home_win(NULL, NULL);
            close_win(NULL, window);
        }
        else if (user.type == 3)
        {
            Owner owner;
            owner.id = 0;
            owner.user = user;
            owner = owner_get(owner);
            session.user = user;
            session.owner = owner;
            g_print("logged in user owner");
            owner_home_win(NULL, NULL);
            close_win(NULL, window);
        }
        else if (user.type == 1)
        {
            session.user = user;
            session.user = user_get(user);
            admin_home_win(NULL, window);
        }
    }

    printf("here\n");
    gtk_entry_set_text(GTK_ENTRY(username_entry), "");
    gtk_entry_set_text(GTK_ENTRY(password_entry), "");
}

void login_win(GtkWidget *widget, gpointer welcome_win)
{
    gtk_widget_destroy(GTK_WIDGET(welcome_win));
    GtkWidget *window;

    GtkWidget *login_button;
    GtkWidget *forget_button;
    GtkWidget *new_button;
    GtkWidget *top_label;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkEntry *username_entry;
    GtkEntry *password_entry;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    GtkWidget *fixed;
    GtkWidget *image;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 20px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    image = gtk_image_new_from_file("./assets/login_win.png");

    gtk_window_set_title(GTK_WINDOW(window), "به کوویید خوش آمدید");

    top_label = gtk_label_new("نام کاربری و رمز عبور خود را وارد کنید");
    username_label = gtk_label_new("نام کاربری :");
    password_label = gtk_label_new("رمز عبور :");

    login_button = gtk_button_new_with_label("ورود ");
    forget_button = gtk_button_new_with_label("فراموشی رمز عبور");
    new_button = gtk_button_new_with_label(" ثبت نام ");

    username_entry = GTK_ENTRY(gtk_entry_new());
    password_entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    context = gtk_widget_get_style_context(top_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_widget_set_size_request(login_button, 350, 30);
    gtk_fixed_put(GTK_FIXED(fixed), login_button, 230, 160);

    gtk_widget_set_size_request(forget_button, 180, 25);
    gtk_fixed_put(GTK_FIXED(fixed), forget_button, 230, 190);

    gtk_widget_set_size_request(new_button, 180, 25);
    gtk_fixed_put(GTK_FIXED(fixed), new_button, 400, 190);

    gtk_fixed_put(GTK_FIXED(fixed), top_label, 250, 10);
    gtk_fixed_put(GTK_FIXED(fixed), username_label, 500, 60);
    gtk_fixed_put(GTK_FIXED(fixed), password_label, 500, 100);

    gtk_widget_set_size_request(GTK_WIDGET(username_entry), 245, 25);
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(username_entry), 250, 55);
    gtk_widget_set_size_request(GTK_WIDGET(password_entry), 245, 25);
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(password_entry), 250, 100);

    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    GtkWidget *user_data_holder = gtk_entry_new();
    g_object_set_data(G_OBJECT(user_data_holder), "username", (gpointer)username_entry);
    g_object_set_data(G_OBJECT(user_data_holder), "password", (gpointer)password_entry);
    g_object_set_data(G_OBJECT(user_data_holder), "window", (gpointer)window);

    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(handle_login), (gpointer)user_data_holder);
    g_signal_connect(G_OBJECT(new_button), "clicked", G_CALLBACK(sign_up_win), (gpointer)NULL);
    g_signal_connect(G_OBJECT(forget_button), "clicked", G_CALLBACK(forget_password_win), (gpointer)NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    gtk_widget_show_all(window);
}

void forget_password_handle(GtkWidget *widget, gpointer user_data)
{

    GtkEntry *email_entry = g_object_get_data(user_data, "email_entry");
    GtkEntry *username_entry = g_object_get_data(user_data, "username_entry");
    GtkEntry *idcode_entry = g_object_get_data(user_data, "idcode_entry");
    GtkEntry *password_entry = g_object_get_data(user_data, "password_entry");
    GtkEntry *password_again_entry = g_object_get_data(user_data, "password_again");
    GtkWidget *window = g_object_get_data(user_data, "window");
    char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    char *password_again = gtk_entry_get_text(GTK_ENTRY(password_again_entry));

    int rc = reset_password(email, username, idcode, password, password_again);
    if (rc == -1)
    {
        gtk_entry_set_text(GTK_ENTRY(password_entry), "");
        gtk_entry_set_text(GTK_ENTRY(password_again_entry), "");
        error_win(NULL, "رمز عبور و تکرار هماهنگی ندارد");
    }
    else if (rc == -2)
    {
        error_win(NULL, "اطلاعات کاربری صحیح نیست");
    }
    else
    {
        close_win(NULL, window);
    }
}

void forget_password_win(GtkWidget *widget, gpointer login_win)
{
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *email_label;
    GtkWidget *username_label;
    GtkWidget *idcode_label;
    GtkWidget *password_label;
    GtkWidget *password_again_label;

    //entrys
    GtkEntry *email_entry;
    GtkEntry *username_entry;
    GtkEntry *idcode_entry;
    GtkEntry *password_entry;
    GtkEntry *password_again;
    GtkEntry *height_entry;
    GtkEntry *weight_entry;

    //buttons
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);
    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    gtk_window_set_title(GTK_WINDOW(window), "فراموشی رمز عبور");

    //labels
    header_label = gtk_label_new(" فراموشی رمز عبور");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    username_label = gtk_label_new("نام کاربری:");
    idcode_label = gtk_label_new("کد ملی:");
    email_label = gtk_label_new("ایمیل:");
    password_label = gtk_label_new("رمر عبور جدید:");
    password_again_label = gtk_label_new("تکرار رمز عبور:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 180, 10);
    gtk_fixed_put(GTK_FIXED(fixed), email_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), username_label, 300, 110);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 150);
    gtk_fixed_put(GTK_FIXED(fixed), password_label, 300, 190);
    gtk_fixed_put(GTK_FIXED(fixed), password_again_label, 300, 230);

    //entries
    email_entry = GTK_ENTRY(gtk_entry_new());
    username_entry = GTK_ENTRY(gtk_entry_new());
    idcode_entry = GTK_ENTRY(gtk_entry_new());
    password_entry = GTK_ENTRY(gtk_entry_new());
    password_again = GTK_ENTRY(gtk_entry_new());
    height_entry = GTK_ENTRY(gtk_entry_new());
    weight_entry = GTK_ENTRY(gtk_entry_new());

    gtk_fixed_put(GTK_FIXED(fixed), email_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), username_entry, 100, 110);
    gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 150);
    gtk_fixed_put(GTK_FIXED(fixed), password_entry, 100, 190);
    gtk_fixed_put(GTK_FIXED(fixed), password_again, 100, 230);

    //preparing data
    data_holder = gtk_entry_new();
    g_object_set_data(G_OBJECT(data_holder), "email_entry", (gpointer)email_entry);
    g_object_set_data(G_OBJECT(data_holder), "username_entry", (gpointer)username_entry);
    g_object_set_data(G_OBJECT(data_holder), "idcode_entry", (gpointer)idcode_entry);
    g_object_set_data(G_OBJECT(data_holder), "password_entry", (gpointer)password_entry);
    g_object_set_data(G_OBJECT(data_holder), "password_again", (gpointer)password_again);

    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    save_button = gtk_button_new_with_label("تغییر رمز عبور");

    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(forget_password_handle), data_holder);

    gtk_widget_set_size_request(save_button, 180, 40);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

void sign_up_handle_finish_normal(GtkWidget *widget, gpointer user_data)
{
    GtkEntry *firstname_entry = g_object_get_data(user_data, "firstname_entry");
    GtkEntry *lastname_entry = g_object_get_data(user_data, "lastname_entry");
    GtkEntry *idcode_entry = g_object_get_data(user_data, "idcode_entry");
    GtkEntry *email_entry = g_object_get_data(user_data, "email_entry");
    GtkEntry *blood_entry = g_object_get_data(user_data, "blood_entry");
    GtkEntry *height_entry = g_object_get_data(user_data, "height_entry");
    GtkEntry *weight_entry = g_object_get_data(user_data, "weight_entry");
    GtkWidget *sign_up_window = g_object_get_data(user_data, "window");

    int user_id = get_last_id();
    char *firstname = gtk_entry_get_text(GTK_ENTRY(firstname_entry));
    char *lastname = gtk_entry_get_text(GTK_ENTRY(lastname_entry));
    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    char *blood = gtk_entry_get_text(GTK_ENTRY(blood_entry));
    int weight = atoi(gtk_entry_get_text(GTK_ENTRY(weight_entry)));
    int height = atoi(gtk_entry_get_text(GTK_ENTRY(height_entry)));
    int rc = sign_up_person(user_id, firstname, lastname, idcode, email, blood, weight, height);
    if (rc != 0)
    {
        error_win(NULL, "مشکلی در اطلاعات وجود دارد!");
    }
    close_win(NULL, sign_up_window);
}

void sign_up_handle_finish_owner(GtkWidget *widget, gpointer user_data)
{
    GtkEntry *place_name_entry = g_object_get_data(user_data, "place_name_entry");
    GtkEntry *city_entry = g_object_get_data(user_data, "city_entry");
    GtkEntry *idcode_entry = g_object_get_data(user_data, "idcode_entry");
    GtkEntry *email_entry = g_object_get_data(user_data, "email_entry");
    GtkEntry *district_entry = g_object_get_data(user_data, "district_entry");
    GtkWidget *sign_up_window = g_object_get_data(user_data, "window");

    int user_id = get_last_id();
    char *place_name = gtk_entry_get_text(GTK_ENTRY(place_name_entry));
    char *city = gtk_entry_get_text(GTK_ENTRY(city_entry));
    char *idcode = gtk_entry_get_text(GTK_ENTRY(idcode_entry));
    char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    int district = atoi(gtk_entry_get_text(GTK_ENTRY(district_entry)));
    int rc = sign_up_owner(user_id, place_name, city, idcode, email, district);
    if (rc != 0)
    {
        error_win(NULL, "مشکلی در اطلاعات وجود دارد!");
    }
    close_win(NULL, sign_up_window);
}

void sign_up_handle_normal_user_form(GtkWidget *widget, gpointer user_data)
{

    GtkEntry *username_entry = g_object_get_data(user_data, "username");
    GtkEntry *password_entry = g_object_get_data(user_data, "password");
    GtkEntry *password_again_entry = g_object_get_data(user_data, "password_again");
    GtkWidget *user_type = g_object_get_data(user_data, "normal_user");
    GtkWidget *sign_up_window = g_object_get_data(user_data, "window");
    char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    char *re_password = gtk_entry_get_text(GTK_ENTRY(password_again_entry));
    int type;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(user_type)))
    {
        type = 2;
        g_print("sign up normal user \n");
    }
    else
    {
        type = 3;
        g_print("sign up owner user \n");
    }
    int rc = sign_up_user(username, password, re_password, type);
    if (rc != 0)
    {
        if (rc == -1)
        {
            error_win(NULL, "رمز عبور و تکرار آن برابر نیست");
            gtk_entry_set_text(password_entry, "");
            gtk_entry_set_text(password_again_entry, "");
        }
        if (rc == -2)
        {
            error_win(NULL, "نام کاربری تکراری است");
            gtk_entry_set_text(username_entry, "");
            gtk_entry_set_text(password_entry, "");
            gtk_entry_set_text(password_again_entry, "");
        }
    }
    close_win(NULL, sign_up_window);
    if (type == 2)
    {
        GtkWidget *window;

        //labels
        GtkWidget *header_label;
        GtkWidget *firstname_label;
        GtkWidget *lastname_label;
        GtkWidget *idcode_label;
        GtkWidget *email_label;
        GtkWidget *blood_label;
        GtkWidget *height_label;
        GtkWidget *weight_label;

        //entrys
        GtkEntry *firstname_entry;
        GtkEntry *lastname_entry;
        GtkEntry *idcode_entry;
        GtkEntry *email_entry;
        GtkEntry *blood_entry;
        GtkEntry *height_entry;
        GtkEntry *weight_entry;

        //buttons
        GtkWidget *save_button;

        //layouts
        GtkWidget *fixed;

        // data_holder
        GtkWidget *data_holder;

        GtkCssProvider *provider;
        GtkStyleContext *context;
        provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider,
                                        "label {"
                                        " font-size: 25px;"
                                        "}",
                                        -1,
                                        NULL);
        window = gtk_application_window_new(app);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window), fixed);
        gtk_widget_show(fixed);
        gtk_window_set_title(GTK_WINDOW(window), "ثبت نام کاربر عادی");

        //labels
        header_label = gtk_label_new("تکمیل اطلاعات کاربری");
        context = gtk_widget_get_style_context(header_label);
        gtk_style_context_add_provider(context,
                                       GTK_STYLE_PROVIDER(provider),
                                       GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        firstname_label = gtk_label_new("نام:");
        lastname_label = gtk_label_new("نام خانوادگی:");
        idcode_label = gtk_label_new("کد ملی:");
        email_label = gtk_label_new("ایمیل:");
        blood_label = gtk_label_new("گروه خونی");
        height_label = gtk_label_new("قد:");
        weight_label = gtk_label_new("وزن:");

        gtk_fixed_put(GTK_FIXED(fixed), header_label, 180, 10);
        gtk_fixed_put(GTK_FIXED(fixed), firstname_label, 300, 70);
        gtk_fixed_put(GTK_FIXED(fixed), lastname_label, 300, 110);
        gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 150);
        gtk_fixed_put(GTK_FIXED(fixed), email_label, 300, 190);
        gtk_fixed_put(GTK_FIXED(fixed), blood_label, 300, 230);
        gtk_fixed_put(GTK_FIXED(fixed), height_label, 300, 270);
        gtk_fixed_put(GTK_FIXED(fixed), weight_label, 300, 310);

        //entries
        firstname_entry = GTK_ENTRY(gtk_entry_new());
        lastname_entry = GTK_ENTRY(gtk_entry_new());
        idcode_entry = GTK_ENTRY(gtk_entry_new());
        email_entry = GTK_ENTRY(gtk_entry_new());
        blood_entry = GTK_ENTRY(gtk_entry_new());
        height_entry = GTK_ENTRY(gtk_entry_new());
        weight_entry = GTK_ENTRY(gtk_entry_new());

        gtk_fixed_put(GTK_FIXED(fixed), firstname_entry, 100, 70);
        gtk_fixed_put(GTK_FIXED(fixed), lastname_entry, 100, 110);
        gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 150);
        gtk_fixed_put(GTK_FIXED(fixed), email_entry, 100, 190);
        gtk_fixed_put(GTK_FIXED(fixed), blood_entry, 100, 230);
        gtk_fixed_put(GTK_FIXED(fixed), height_entry, 100, 270);
        gtk_fixed_put(GTK_FIXED(fixed), weight_entry, 100, 310);

        //preparing data
        data_holder = gtk_entry_new();
        g_object_set_data(G_OBJECT(data_holder), "firstname_entry", (gpointer)firstname_entry);
        g_object_set_data(G_OBJECT(data_holder), "lastname_entry", (gpointer)lastname_entry);
        g_object_set_data(G_OBJECT(data_holder), "idcode_entry", (gpointer)idcode_entry);
        g_object_set_data(G_OBJECT(data_holder), "email_entry", (gpointer)email_entry);
        g_object_set_data(G_OBJECT(data_holder), "blood_entry", (gpointer)blood_entry);
        g_object_set_data(G_OBJECT(data_holder), "height_entry", (gpointer)height_entry);
        g_object_set_data(G_OBJECT(data_holder), "weight_entry", (gpointer)weight_entry);
        g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

        //buttons
        save_button = gtk_button_new_with_label("تکمیل ثبت نام");

        g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(sign_up_handle_finish_normal), data_holder);

        gtk_widget_set_size_request(save_button, 180, 40);
        gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

        gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
        gtk_widget_show_all(window);
    }
    else if (type == 3)
    {
        GtkWidget *window;

        //labels
        GtkWidget *header_label;
        GtkWidget *place_name_label;
        GtkWidget *idcode_label;
        GtkWidget *email_label;
        GtkWidget *district_label;
        GtkWidget *status_label;
        GtkWidget *city_label;

        //entrys
        GtkEntry *place_name_entry;
        GtkEntry *idcode_entry;
        GtkEntry *email_entry;
        GtkEntry *district_entry;
        GtkEntry *status_entry;
        GtkEntry *city_entry;

        //buttons
        GtkWidget *save_button;

        //layouts
        GtkWidget *fixed;

        // data_holder
        GtkWidget *data_holder;

        GtkCssProvider *provider;
        GtkStyleContext *context;
        provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider,
                                        "label {"
                                        " font-size: 25px;"
                                        "}",
                                        -1,
                                        NULL);
        window = gtk_application_window_new(app);

        fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window), fixed);
        gtk_widget_show(fixed);
        gtk_window_set_title(GTK_WINDOW(window), "ثبت نام کاربر عادی");

        //labels
        header_label = gtk_label_new("تکمیل اطلاعات کاربری");
        context = gtk_widget_get_style_context(header_label);
        gtk_style_context_add_provider(context,
                                       GTK_STYLE_PROVIDER(provider),
                                       GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        place_name_label = gtk_label_new("نام محل");
        city_label = gtk_label_new("شهر:");
        idcode_label = gtk_label_new("کد ملی:");
        email_label = gtk_label_new("ایمیل:");
        district_label = gtk_label_new(" کد منطقه:");

        gtk_fixed_put(GTK_FIXED(fixed), header_label, 180, 10);
        gtk_fixed_put(GTK_FIXED(fixed), place_name_label, 300, 70);
        gtk_fixed_put(GTK_FIXED(fixed), city_label, 300, 110);
        gtk_fixed_put(GTK_FIXED(fixed), district_label, 300, 150);
        gtk_fixed_put(GTK_FIXED(fixed), email_label, 300, 190);
        gtk_fixed_put(GTK_FIXED(fixed), idcode_label, 300, 230);

        //entries
        place_name_entry = GTK_ENTRY(gtk_entry_new());
        city_entry = GTK_ENTRY(gtk_entry_new());
        district_entry = GTK_ENTRY(gtk_entry_new());
        email_entry = GTK_ENTRY(gtk_entry_new());
        idcode_entry = GTK_ENTRY(gtk_entry_new());

        gtk_fixed_put(GTK_FIXED(fixed), place_name_entry, 100, 70);
        gtk_fixed_put(GTK_FIXED(fixed), city_entry, 100, 110);
        gtk_fixed_put(GTK_FIXED(fixed), district_entry, 100, 150);
        gtk_fixed_put(GTK_FIXED(fixed), email_entry, 100, 190);
        gtk_fixed_put(GTK_FIXED(fixed), idcode_entry, 100, 230);

        //preparing data
        data_holder = gtk_entry_new();
        g_object_set_data(G_OBJECT(data_holder), "place_name_entry", (gpointer)place_name_entry);
        g_object_set_data(G_OBJECT(data_holder), "city_entry", (gpointer)city_entry);
        g_object_set_data(G_OBJECT(data_holder), "idcode_entry", (gpointer)idcode_entry);
        g_object_set_data(G_OBJECT(data_holder), "email_entry", (gpointer)email_entry);
        g_object_set_data(G_OBJECT(data_holder), "district_entry", (gpointer)district_entry);
        g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

        //buttons
        save_button = gtk_button_new_with_label("تکمیل ثبت نام");

        g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(sign_up_handle_finish_owner), data_holder);

        gtk_widget_set_size_request(save_button, 180, 40);
        gtk_fixed_put(GTK_FIXED(fixed), save_button, 100, 350);

        gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
        gtk_widget_show_all(window);
    }
}

void sign_up_win(GtkWidget *widget, gpointer login_win)
{
    // gtk_widget_destroy(GTK_WIDGET(welcome_win));
    GtkWidget *window;

    //labels
    GtkWidget *header_label;
    GtkWidget *account_info_label;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *password_again_label;
    GtkWidget *account_type_label;

    //entrys
    GtkEntry *username_entry;
    GtkEntry *password_entry;
    GtkEntry *password_again_entry;

    //radio
    GtkWidget *normal_user;
    GtkWidget *owner_user;
    GtkWidget *layout_holder;

    //buttons
    GtkWidget *return_button;
    GtkWidget *save_button;

    //layouts
    GtkWidget *fixed;

    // data_holder
    GtkWidget *data_holder;

    GtkCssProvider *provider;
    GtkStyleContext *context;

    GtkWidget *image;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "label {"
                                    " font-size: 25px;"
                                    "}",
                                    -1,
                                    NULL);

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    image = gtk_image_new_from_file("./assets/login_win.png");

    gtk_window_set_title(GTK_WINDOW(window), "ثبت نام کاربر جدید");

    //labels
    header_label = gtk_label_new("ثبت نام");
    context = gtk_widget_get_style_context(header_label);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    account_info_label = gtk_label_new("اطلاعات کاربری:");
    username_label = gtk_label_new("نام کاربری :");
    password_label = gtk_label_new("رمز عبور :");
    password_again_label = gtk_label_new("تکرار رمز عبور  :");
    account_type_label = gtk_label_new("نوع حساب:");

    gtk_fixed_put(GTK_FIXED(fixed), header_label, 220, 10);
    gtk_fixed_put(GTK_FIXED(fixed), account_info_label, 420, 40);
    gtk_fixed_put(GTK_FIXED(fixed), username_label, 300, 70);
    gtk_fixed_put(GTK_FIXED(fixed), password_label, 300, 110);
    gtk_fixed_put(GTK_FIXED(fixed), password_again_label, 300, 150);
    gtk_fixed_put(GTK_FIXED(fixed), account_type_label, 300, 190);

    //entries
    username_entry = GTK_ENTRY(gtk_entry_new());
    password_entry = GTK_ENTRY(gtk_entry_new());
    password_again_entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(password_again_entry), FALSE);

    gtk_fixed_put(GTK_FIXED(fixed), username_entry, 100, 70);
    gtk_fixed_put(GTK_FIXED(fixed), password_entry, 100, 110);
    gtk_fixed_put(GTK_FIXED(fixed), password_again_entry, 100, 150);

    //radio
    normal_user = gtk_radio_button_new_with_label(NULL, "کاربر عادی");
    owner_user = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(normal_user),
                                                             "صاحب مکان");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(normal_user), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(owner_user), FALSE);
    gtk_fixed_put(GTK_FIXED(fixed), normal_user, 200, 190);
    gtk_fixed_put(GTK_FIXED(fixed), owner_user, 90, 190);

    layout_holder = gtk_entry_new();

    //preparing data
    data_holder = gtk_entry_new();

    g_object_set_data(G_OBJECT(data_holder), "username", (gpointer)username_entry);
    g_object_set_data(G_OBJECT(data_holder), "password", (gpointer)password_entry);
    g_object_set_data(G_OBJECT(data_holder), "password_again", (gpointer)password_again_entry);
    g_object_set_data(G_OBJECT(data_holder), "normal_user", (gpointer)normal_user);
    g_object_set_data(G_OBJECT(data_holder), "window", (gpointer)window);

    //buttons
    return_button = gtk_button_new_with_label("بازگشت");
    save_button = gtk_button_new_with_label("ثبت نام");

    g_signal_connect(GTK_BUTTON(return_button), "clicked", G_CALLBACK(close_win), window);
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(sign_up_handle_normal_user_form), data_holder);

    gtk_widget_set_size_request(return_button, 100, 30);
    gtk_fixed_put(GTK_FIXED(fixed), return_button, 200, 220);
    gtk_widget_set_size_request(save_button, 100, 30);
    gtk_fixed_put(GTK_FIXED(fixed), save_button, 80, 220);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    gtk_widget_show_all(window);
}

void splash(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *enter_button;
    GtkWidget *fixed;
    GtkWidget *image;

    window = gtk_application_window_new(app);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    image = gtk_image_new_from_file("./assets/mask.jpg");

    gtk_window_set_title(GTK_WINDOW(window), "به ماسک خوش آمدید");
    enter_button = gtk_button_new_with_label("وارد شوید");

    gtk_widget_set_size_request(enter_button, 100, 50);
    gtk_fixed_put(GTK_FIXED(fixed), enter_button, 320, 300);
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    g_signal_connect(G_OBJECT(enter_button), "clicked", G_CALLBACK(login_win), G_OBJECT(window));
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);

    gtk_widget_show_all(window);
}