#include "chat.h"

void server_set_connection()
{
    struct sockaddr_in client_addr;
    data.socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    int port = data.port;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(data.ipv4);
    client_addr.sin_port = htons(port);

    if (connect(data.socket_desc, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        //printf("Connected to server, port is %d\n", port);
    }
    else
    {
        // сверстать окно об ошибке и вызывать здесь и вызывать функцию которая будет каждые 60 секунд вызывать повторное соединение с сервером рекурсией
        // server_set_connection();
        //printf("Something wrong!\n");
        exit(1);
    }
}

void application_activate(GtkApplication *application, gpointer user_data)
{

    g_mutex_init(&main_form.mutex);
    g_mutex_init(&main_form.mutex_seding_msg);
    g_mutex_init(&main_form.mutex_file_transfer);
    g_mutex_init(&main_form.mutex_update);

    server_set_connection();

    char *settings = mx_file_to_str("settings.json");
    if (settings == NULL)
    {
        create_settings_json("NULL", "Dark", "English", "FALSE");
    }

    settings = mx_file_to_str("settings.json");
    settings_t *settings_field = get_settings(settings);
    GtkBuilder *builder = glade_file_to_interface("share/window_auth.glade");
    data.win = GTK_WIDGET(gtk_builder_get_object(builder, "windowAuth"));
    what_theme_select(settings_field->theme);
    css_set_for_one(data.win, data.auth_theme_path);
    init_language_interface(settings_field->language);
    g_object_unref(builder);

    if (strcmp(settings_field->is_in, "FALSE") == 0)
    {
        open_login(data.win);
    }
    else
    {
        autorization.login_text = strdup(settings_field->login);
        open_form_pin(data.win, true);
    }
    free_settings(settings_field);
    gtk_application_add_window(application, GTK_WINDOW(data.win));
    gtk_widget_show_all(data.win);
}

void application_shutdown(GtkApplication *application, gpointer user_data)
{
    // if (g_mutex_trylock(&main_form.mutex))
    // {
    //     g_mutex_unlock(&main_form.mutex);
    // }
    // if (g_mutex_trylock(&main_form.mutex_seding_msg))
    // {
    //     g_mutex_unlock(&main_form.mutex_seding_msg);
    // }

    // g_mutex_clear(&main_form.mutex);
    // g_mutex_clear(&main_form.mutex_seding_msg);

    if (main_form.main_grid != NULL && data.user_id != NULL)
    {
        if (main_form.last_ms_id != NULL)
        {
            free(main_form.last_ms_id);
            main_form.last_ms_id = NULL;
        }
        main_form.last_ms_id = strdup("0");
        remove("messages.json");
        get_all_messages(data.user_id, main_form.last_ms_id);
    }
    close(data.socket_desc);
    g_application_quit(G_APPLICATION(application));
}

int main(int argc, char *argv[])
{
    // setlocale(LC_ALL, "");
    if (argc != 3)
    {
        puts("Usage: ./uchat [ipv4][port]");
        return 1;
    }
    data.port = atoi(argv[2]);
        data.ipv4 = strdup(argv[1]);

    gtk_init(&argc, &argv);
    data.app = gtk_application_new("gtk.org", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(data.app, "activate", G_CALLBACK(application_activate), NULL);
    g_signal_connect(data.app, "shutdown", G_CALLBACK(application_shutdown), NULL);
    gint res = g_application_run(G_APPLICATION(data.app), 0, NULL);
    return 0;
}
