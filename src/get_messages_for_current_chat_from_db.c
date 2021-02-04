#include "chat.h"

void get_messages_for_current_chat_from_db(GtkWidget *container_msg, char *chat_id)
{
    message_arr *message = get_messages_from_file("messages.json", chat_id);
    if (message != NULL)
    {   
        int length = *message->length;
        messages_t **messages_g = (messages_t **)malloc(sizeof(messages_t *) * (length + 1));
        messages_g[length] = NULL;
        for (int i = 0; i < length; i++)
        {
            messages_g[i] = (messages_t *)malloc(sizeof(messages_t));
            messages_g[i]->event_box_message = gtk_event_box_new();
            // g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
            gtk_widget_set_hexpand(messages_g[i]->event_box_message, true);
            if(strcmp(message->messages[i]->u_id, data.user_id) == 0){
                gtk_widget_set_halign(messages_g[i]->event_box_message, GTK_ALIGN_END);
            } else {
                gtk_widget_set_halign(messages_g[i]->event_box_message, GTK_ALIGN_START);
            }
            gtk_widget_set_vexpand(messages_g[i]->event_box_message, true);
            gtk_widget_set_name(messages_g[i]->event_box_message, message->messages[i]->ms_id);
            gtk_widget_set_size_request(messages_g[i]->event_box_message, 500, -1);
            
            messages_g[i]->message = gtk_grid_new();
            gtk_widget_set_hexpand(messages_g[i]->message, true);
            gtk_widget_set_vexpand(messages_g[i]->message, true);
            set_style_context(messages_g[i]->message, "message-body");

            messages_g[i]->message_info = gtk_grid_new();
            gtk_widget_set_hexpand(messages_g[i]->message_info, true);
            gtk_widget_set_vexpand(messages_g[i]->message_info, true);

            messages_g[i]->message_time = gtk_label_new(message->messages[i]->ms_datetime);
            gtk_widget_set_halign(messages_g[i]->message_time, GTK_ALIGN_END);
            set_style_context(messages_g[i]->message_time, "message-time");

            messages_g[i]->message_login = gtk_label_new(message->messages[i]->u_name);
            gtk_widget_set_hexpand(messages_g[i]->message_login, true);
            gtk_widget_set_halign(messages_g[i]->message_login, GTK_ALIGN_START);
            set_style_context(messages_g[i]->message_login, "contact-login");
            set_style_context(messages_g[i]->message_login, "message-from");

            messages_g[i]->message_text = gtk_label_new(message->messages[i]->ms_text);
            gtk_widget_set_hexpand(messages_g[i]->message_text, true);
            gtk_widget_set_vexpand(messages_g[i]->message_text, true);
            gtk_widget_set_halign(messages_g[i]->message_text, GTK_ALIGN_START);
            gtk_label_set_line_wrap(GTK_LABEL(messages_g[i]->message_text), true);
            gtk_widget_set_size_request(messages_g[i]->message_text, 500, -1);
            gtk_label_set_line_wrap_mode(GTK_LABEL(messages_g[i]->message_text), PANGO_WRAP_WORD);
            gtk_label_set_max_width_chars (GTK_LABEL (messages_g[i]->message_text), 30);
            gtk_label_set_selectable(GTK_LABEL (messages_g[i]->message_text),true);
            set_style_context(messages_g[i]->message_text, "message-text");

            css_set_for_one(messages_g[i]->event_box_message, "share/resources/css/main.css");
            css_set_for_one(messages_g[i]->message, "share/resources/css/main.css");
            css_set_for_one(messages_g[i]->message_info, "share/resources/css/main.css");
            css_set_for_one(messages_g[i]->message_time, "share/resources/css/main.css");
            css_set_for_one(messages_g[i]->message_text, "share/resources/css/main.css");
            css_set_for_one(messages_g[i]->message_login, "share/resources/css/main.css");

            gtk_grid_attach(GTK_GRID(messages_g[i]->message_info), messages_g[i]->message_login, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(messages_g[i]->message_info), messages_g[i]->message_time, 1, 0, 1, 1);

            gtk_grid_attach(GTK_GRID(messages_g[i]->message), messages_g[i]->message_text, 0, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(messages_g[i]->message), messages_g[i]->message_info, 0, 0, 1, 1);

            gtk_container_add(GTK_CONTAINER(messages_g[i]->event_box_message), messages_g[i]->message);
            gtk_grid_attach(GTK_GRID(container_msg), messages_g[i]->event_box_message, 0, i, 1, 1);
        }
        gtk_widget_show_all(container_msg);
        free_messages(message);
    }
}
