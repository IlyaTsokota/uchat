#include "chat.h"

void get_chats_from_db(GtkWidget *container_chats)
{
    char *num_f = strdup("17");
    char *arr[] = {"3", NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    chat_t **chats = request_get_chats(json);
    free(json);
    // if (chats != NULL)
    // {
    //    puts("GG");
    //     int size = 0;
    //     for (size_t i = 0; chats[i]; i++)
    //     {
    //         size++;
    //     }
    //     GtkBuilder *builder = glade_file_to_interface("share/chat_item.glade");
    //     chat_item_t **chat_items = (chat_item_t **)malloc(sizeof(chat_item_t *) * (size + 1));
    //     chat_items[size] = NULL;

    //     for (size_t i = 0; i < size; i++)
    //     {
    //         chat_items[i] = (chat_item_t *)malloc(sizeof(chat_item_t));
    //         chat_items[i]->event_box_contact = gtk_event_box_new();
    //         gtk_widget_set_hexpand(chat_items[i]->event_box_contact, true);
    //         gtk_widget_set_name(chat_items[i]->event_box_contact, chats[i]->ch_id);

    //         chat_items[i]->contact_container = gtk_grid_new();
    //         set_style_context(chat_items[i]->contact_container, "contact-container");
    //         gtk_widget_set_hexpand(chat_items[i]->contact_container, false);
    //         gtk_widget_set_vexpand(chat_items[i]->contact_container, true);
    //         gtk_widget_set_size_request(chat_items[i]->contact_container, -1, 84);

    //         chat_items[i]->time_last_message = gtk_label_new("11.05");
    //         gtk_widget_set_valign(chat_items[i]->time_last_message, GTK_ALIGN_START);
    //         gtk_widget_set_hexpand(chat_items[i]->time_last_message, false);
    //         gtk_widget_set_vexpand(chat_items[i]->time_last_message, true);
    //         gtk_widget_set_margin_top(chat_items[i]->time_last_message, 10);
    //         set_style_context(chat_items[i]->time_last_message, "contact-time");

    //         chat_items[i]->contact_info = gtk_grid_new();
    //         gtk_widget_set_hexpand(chat_items[i]->contact_info, true);
    //         gtk_widget_set_vexpand(chat_items[i]->contact_info, true);
    //         set_style_context(chat_items[i]->contact_info, "contact-body");

    //         chat_items[i]->contact_last_msg = gtk_grid_new();
    //         gtk_widget_set_valign(chat_items[i]->contact_last_msg, GTK_ALIGN_END);
    //         gtk_widget_set_hexpand(chat_items[i]->contact_last_msg, true);
    //         gtk_widget_set_vexpand(chat_items[i]->contact_last_msg, true);

    //         chat_items[i]->text_last_message = gtk_label_new("text last");
    //         gtk_widget_set_hexpand(chat_items[i]->text_last_message, false);
    //         set_style_context(chat_items[i]->text_last_message, "contact-lastmsg");
    //         set_style_context(chat_items[i]->text_last_message, "contact-lastmessage");

    //         chat_items[i]->login_last_message = gtk_label_new("login last");
    //         gtk_widget_set_valign(chat_items[i]->login_last_message, GTK_ALIGN_START);
    //         gtk_widget_set_hexpand(chat_items[i]->login_last_message, false);
    //         set_style_context(chat_items[i]->login_last_message, "contact-lastmessage");

    //         chat_items[i]->contact_name_container = gtk_grid_new();

    //         chat_items[i]->contact_name_lable = strcmp(chats[i]->u_login, "0") == 0 ? gtk_label_new(chats[i]->ch_name) : gtk_label_new(chats[i]->u_login);

    //         gtk_widget_set_halign(chat_items[i]->contact_name_lable, GTK_ALIGN_START);
    //         set_style_context(chat_items[i]->contact_name_lable, "contact-login");

    //         chat_items[i]->user_is_online = gtk_grid_new();
    //         gtk_widget_set_size_request(chat_items[i]->user_is_online, 10, 10);
    //         gtk_widget_set_halign(chat_items[i]->user_is_online, GTK_ALIGN_CENTER);
    //         gtk_widget_set_valign(chat_items[i]->user_is_online, GTK_ALIGN_START);
    //         gtk_widget_set_hexpand(chat_items[i]->user_is_online, false);
    //         gtk_widget_set_vexpand(chat_items[i]->user_is_online, true);
    //         set_style_context(chat_items[i]->user_is_online, "is-online");

    //         chat_items[i]->user_is_online_round = gtk_level_bar_new();
    //         gtk_widget_set_opacity(chat_items[i]->user_is_online_round, 0);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->user_is_online), chat_items[i]->user_is_online_round, 0, 0, 1, 1);

    //         chat_items[i]->contact_img_container = gtk_grid_new();
    //         gtk_widget_set_size_request(chat_items[i]->contact_img_container, 57, 57);
    //         gtk_widget_set_halign(chat_items[i]->contact_img_container, GTK_ALIGN_START);
    //         gtk_widget_set_valign(chat_items[i]->contact_img_container, GTK_ALIGN_CENTER);
    //         gtk_widget_set_hexpand(chat_items[i]->contact_img_container, false);
    //         gtk_widget_set_vexpand(chat_items[i]->contact_img_container, false);
    //         set_style_context(chat_items[i]->contact_img_container, "contact-img");
    //         if (strcmp(chats[i]->u_avatar, "0") == 0)
    //         {
    //             // здесь ch_avatar
    //             chat_items[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
    //         }
    //         else
    //         {
    //             // здесь u_avatar
    //             chat_items[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
    //         }
    //         gtk_widget_set_hexpand(chat_items[i]->img_contact, true);
    //         gtk_widget_set_vexpand(chat_items[i]->img_contact, true);
    //         set_style_context(chat_items[i]->img_contact, "contact-icon");

    //         css_set_for_one(chat_items[i]->contact_container, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->time_last_message, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->contact_info, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->text_last_message, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->login_last_message, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->user_is_online, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->contact_img_container, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->img_contact, "share/resources/css/main.css");
    //         css_set_for_one(chat_items[i]->contact_name_lable, "share/resources/css/main.css");

    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->contact_img_container, 0, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_img_container), chat_items[i]->img_contact, 0, 0, 1, 1);

    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->contact_info, 1, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_info), chat_items[i]->contact_last_msg, 0, 1, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_last_msg), chat_items[i]->login_last_message, 0, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_last_msg), chat_items[i]->text_last_message, 1, 0, 1, 1);

    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_info), chat_items[i]->contact_name_container, 0, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_name_container), chat_items[i]->contact_name_lable, 0, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_name_container), chat_items[i]->user_is_online, 1, 0, 1, 1);

    //         gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->time_last_message, 2, 0, 1, 1);

    //         gtk_container_add(GTK_CONTAINER(chat_items[i]->event_box_contact), chat_items[i]->contact_container);

    //         gtk_grid_attach(GTK_GRID(container_chats), chat_items[i]->event_box_contact, 0, i, 1, 1);
    //     }
    //     free_chats(chats);
    //     g_object_unref(builder);
    // }
    // else
    // {
    //     g_print("Unknown Error 404-5050-31231! Let`s try again! \n");
    //     get_chats_from_db(container_chats);
    // }
}