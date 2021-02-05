#include "chat.h"

void get_chats_from_db(GtkWidget *container_chats, char *user_id)
{
    main_form.is_refresh_chat = false;
    char *num_f = strdup("17");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(json);
    free(json);
    puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return;
    }
    free(jobj);
    chat_t **chats = request_get_chats(response);
    free(response);
    if (chats != NULL)
    {
        chats_f.was_free = false;
        int size = 0;
        for (size_t i = 0; chats[i]; i++)
        {
            size++;
        }


        chats_f.chat_items = (chat_item_t **)malloc(sizeof(chat_item_t *) * (size + 1));
        chats_f.chat_items[size] = NULL;
        
        if (chats_f.curr_chat == NULL ){
            chats_f.curr_chat = strdup(chats[0]->ch_id);
        }
        message_arr *message = NULL;

        for (size_t i = 0; i < size; i++)
        {
            chats_f.chat_items[i] = (chat_item_t *)malloc(sizeof(chat_item_t));
            chats_f.chat_items[i]->event_box_contact = gtk_event_box_new();
            g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->event_box_contact, true);
            gtk_widget_set_name(chats_f.chat_items[i]->event_box_contact, chats[i]->ch_id);

            message = get_messages_from_file("messages.json", chats[i]->ch_id);
            int last_item = *message->length - 1;
            chats_f.chat_items[i]->contact_container = gtk_grid_new();
            gtk_widget_set_hexpand(chats_f.chat_items[i]->contact_container, false);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->contact_container, true);
            gtk_widget_set_size_request(chats_f.chat_items[i]->contact_container, -1, 84);
            set_style_context(chats_f.chat_items[i]->contact_container, "contact-container");

            char *time = strdup(&message->messages[last_item]->ms_datetime[11]);
            chats_f.chat_items[i]->time_last_message = gtk_label_new(time);
            gtk_widget_set_valign(chats_f.chat_items[i]->time_last_message, GTK_ALIGN_START);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->time_last_message, false);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->time_last_message, true);
            gtk_widget_set_margin_top(chats_f.chat_items[i]->time_last_message, 10);
            free(time);
            set_style_context(chats_f.chat_items[i]->time_last_message, "contact-time");

            chats_f.chat_items[i]->contact_info = gtk_grid_new();
            gtk_widget_set_hexpand(chats_f.chat_items[i]->contact_info, true);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->contact_info, true);
            set_style_context(chats_f.chat_items[i]->contact_info, "contact-body");

            chats_f.chat_items[i]->contact_last_msg = gtk_grid_new();
            gtk_widget_set_valign(chats_f.chat_items[i]->contact_last_msg, GTK_ALIGN_END);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->contact_last_msg, true);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->contact_last_msg, true);

            char *last_msg = cut_str(message->messages[last_item]->ms_text , 25);
            chats_f.chat_items[i]->text_last_message = gtk_label_new(last_msg);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->text_last_message, false);
            set_style_context(chats_f.chat_items[i]->text_last_message, "contact-lastmsg");
            set_style_context(chats_f.chat_items[i]->text_last_message, "contact-lastmessage");
            free(last_msg);

            char *last_login = strjoin(2,message->messages[last_item]->u_name, ":");
            //strcpy(&message->messages[last_item]->u_name[strlen(message->messages[last_item]->u_name)-1], ":");
            chats_f.chat_items[i]->login_last_message = gtk_label_new(last_login);
            gtk_widget_set_valign(chats_f.chat_items[i]->login_last_message, GTK_ALIGN_START);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->login_last_message, false);
            set_style_context(chats_f.chat_items[i]->login_last_message, "contact-lastmessage");
            free(last_login);
            free_messages(message);

            chats_f.chat_items[i]->contact_name_container = gtk_grid_new();

            chats_f.chat_items[i]->contact_name_lable = strcmp(chats[i]->u_login, "0") == 0 ? gtk_label_new(chats[i]->ch_name) : gtk_label_new(chats[i]->u_login);
            gtk_widget_set_margin_top(chats_f.chat_items[i]->contact_name_lable, 10);
            gtk_widget_set_halign(chats_f.chat_items[i]->contact_name_lable, GTK_ALIGN_START);
            set_style_context(chats_f.chat_items[i]->contact_name_lable, "contact-login");

            // if (is_online(chats[i]->u_lastSeen) && !(strcmp(chats[i]->u_login, "0") == 0))
            // {
            chats_f.chat_items[i]->user_is_online = gtk_grid_new();
            gtk_widget_set_size_request(chats_f.chat_items[i]->user_is_online, 10, 10);
            gtk_widget_set_halign(chats_f.chat_items[i]->user_is_online, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(chats_f.chat_items[i]->user_is_online, GTK_ALIGN_START);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->user_is_online, false);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->user_is_online, true);
            set_style_context(chats_f.chat_items[i]->user_is_online, "is-online");

            chats_f.chat_items[i]->user_is_online_round = gtk_level_bar_new();
            gtk_widget_set_opacity(chats_f.chat_items[i]->user_is_online_round, 0);
          
            css_set_for_one(chats_f.chat_items[i]->user_is_online, "share/resources/css/main.css");
          
            // }

            chats_f.chat_items[i]->contact_img_container = gtk_grid_new();
            gtk_widget_set_size_request(chats_f.chat_items[i]->contact_img_container, 57, 57);
            gtk_widget_set_halign(chats_f.chat_items[i]->contact_img_container, GTK_ALIGN_START);
            gtk_widget_set_valign(chats_f.chat_items[i]->contact_img_container, GTK_ALIGN_CENTER);
            gtk_widget_set_hexpand(chats_f.chat_items[i]->contact_img_container, false);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->contact_img_container, false);
            set_style_context(chats_f.chat_items[i]->contact_img_container, "contact-img");
            if (strcmp(chats[i]->u_avatar, "0") == 0)
            {
                // здесь ch_avatar
                chats_f.chat_items[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
            }
            else
            {
                // здесь u_avatar
                chats_f.chat_items[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
            }

            gtk_widget_set_hexpand(chats_f.chat_items[i]->img_contact, true);
            gtk_widget_set_vexpand(chats_f.chat_items[i]->img_contact, true);
            set_style_context(chats_f.chat_items[i]->img_contact, "contact-icon");

            css_set_for_one(chats_f.chat_items[i]->contact_container, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->time_last_message, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->contact_info, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->text_last_message, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->login_last_message, "share/resources/css/main.css");

            css_set_for_one(chats_f.chat_items[i]->contact_img_container, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->img_contact, "share/resources/css/main.css");
            css_set_for_one(chats_f.chat_items[i]->contact_name_lable, "share/resources/css/main.css");

            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_container), chats_f.chat_items[i]->contact_img_container, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_img_container), chats_f.chat_items[i]->img_contact, 0, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_container), chats_f.chat_items[i]->contact_info, 1, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_info), chats_f.chat_items[i]->contact_last_msg, 0, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_last_msg), chats_f.chat_items[i]->login_last_message, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_last_msg), chats_f.chat_items[i]->text_last_message, 1, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_info), chats_f.chat_items[i]->contact_name_container, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_name_container), chats_f.chat_items[i]->contact_name_lable, 0, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->user_is_online), chats_f.chat_items[i]->user_is_online_round, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_name_container), chats_f.chat_items[i]->user_is_online, 1, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(chats_f.chat_items[i]->contact_container), chats_f.chat_items[i]->time_last_message, 2, 0, 1, 1);

            gtk_container_add(GTK_CONTAINER(chats_f.chat_items[i]->event_box_contact), chats_f.chat_items[i]->contact_container);

            gtk_grid_attach(GTK_GRID(container_chats), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
        }
        
        gtk_widget_show_all(container_chats);
        free_chats(chats);
        main_form.is_refresh_chat = true;
    }
}
