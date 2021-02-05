#include "chat.h"

void create_one_messages(int length, message_t *message, GtkWidget *container_msg)
{
    curr_chat.messages_g = (messages_t **)realloc(curr_chat.messages_g, sizeof(messages_t *) * (length + 2));
    curr_chat.messages_g[length] = (messages_t *)malloc(sizeof(messages_t));
    curr_chat.messages_g[length]->event_box_message = gtk_event_box_new();
    // g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
    gtk_widget_set_hexpand(curr_chat.messages_g[length]->event_box_message, true);
    if (strcmp(message->u_id, data.user_id) == 0)
    {
        gtk_widget_set_halign(curr_chat.messages_g[length]->event_box_message, GTK_ALIGN_END);
    }
    else
    {
        gtk_widget_set_halign(curr_chat.messages_g[length]->event_box_message, GTK_ALIGN_START);
    }
        gtk_widget_set_vexpand(curr_chat.messages_g[length]->event_box_message, true);
        gtk_widget_set_name(curr_chat.messages_g[length]->event_box_message, message->ms_id);
        gtk_widget_set_size_request(curr_chat.messages_g[length]->event_box_message, 500, -1);

        curr_chat.messages_g[length]->message = gtk_grid_new();
        gtk_widget_set_hexpand(curr_chat.messages_g[length]->message, true);
        gtk_widget_set_vexpand(curr_chat.messages_g[length]->message, true);
        set_style_context(curr_chat.messages_g[length]->message, "message-body");

        curr_chat.messages_g[length]->message_info = gtk_grid_new();
        gtk_widget_set_hexpand(curr_chat.messages_g[length]->message_info, true);
        gtk_widget_set_vexpand(curr_chat.messages_g[length]->message_info, true);

        curr_chat.messages_g[length]->message_time = gtk_label_new(message->ms_datetime);
        gtk_widget_set_halign(curr_chat.messages_g[length]->message_time, GTK_ALIGN_END);
        set_style_context(curr_chat.messages_g[length]->message_time, "message-time");

        curr_chat.messages_g[length]->message_login = gtk_label_new(message->u_name);
        gtk_widget_set_hexpand(curr_chat.messages_g[length]->message_login, true);
        gtk_widget_set_halign(curr_chat.messages_g[length]->message_login, GTK_ALIGN_START);
        set_style_context(curr_chat.messages_g[length]->message_login, "contact-login");
        set_style_context(curr_chat.messages_g[length]->message_login, "message-from");

        curr_chat.messages_g[length]->message_text = gtk_label_new(message->ms_text);
        gtk_widget_set_hexpand(curr_chat.messages_g[length]->message_text, true);
        gtk_widget_set_vexpand(curr_chat.messages_g[length]->message_text, true);
        gtk_widget_set_halign(curr_chat.messages_g[length]->message_text, GTK_ALIGN_START);
        gtk_label_set_line_wrap(GTK_LABEL(curr_chat.messages_g[length]->message_text), true);
        gtk_widget_set_size_request(curr_chat.messages_g[length]->message_text, 500, -1);
        gtk_label_set_xalign(GTK_LABEL(curr_chat.messages_g[length]->message_text), 0);
        gtk_label_set_line_wrap_mode(GTK_LABEL(curr_chat.messages_g[length]->message_text), PANGO_WRAP_WORD);
        gtk_label_set_max_width_chars(GTK_LABEL(curr_chat.messages_g[length]->message_text), 30);
        gtk_label_set_selectable(GTK_LABEL(curr_chat.messages_g[length]->message_text), true);
        set_style_context(curr_chat.messages_g[length]->message_text, "message-text");

        css_set_for_one(curr_chat.messages_g[length]->event_box_message, "share/resources/css/main.css");
        css_set_for_one(curr_chat.messages_g[length]->message, "share/resources/css/main.css");
        css_set_for_one(curr_chat.messages_g[length]->message_info, "share/resources/css/main.css");
        css_set_for_one(curr_chat.messages_g[length]->message_time, "share/resources/css/main.css");
        css_set_for_one(curr_chat.messages_g[length]->message_text, "share/resources/css/main.css");
        css_set_for_one(curr_chat.messages_g[length]->message_login, "share/resources/css/main.css");

        gtk_grid_attach(GTK_GRID(curr_chat.messages_g[length]->message_info), curr_chat.messages_g[length]->message_login, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(curr_chat.messages_g[length]->message_info), curr_chat.messages_g[length]->message_time, 1, 0, 1, 1);

        gtk_grid_attach(GTK_GRID(curr_chat.messages_g[length]->message), curr_chat.messages_g[length]->message_text, 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(curr_chat.messages_g[length]->message), curr_chat.messages_g[length]->message_info, 0, 0, 1, 1);

        gtk_container_add(GTK_CONTAINER(curr_chat.messages_g[length]->event_box_message), curr_chat.messages_g[length]->message);
        gtk_grid_attach(GTK_GRID(container_msg), curr_chat.messages_g[length]->event_box_message, 0, length, 1, 1);
        curr_chat.messages_g[length + 1] = NULL;
        curr_chat.length = length + 1;
    }