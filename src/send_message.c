#include "chat.h"

gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    g_mutex_lock(&main_form.mutex);
    char *message = get_text_of_textview(text_view);
    clear_text__buffer(text_view);
    puts(message);
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(json);
    free(response);
    g_mutex_unlock(&main_form.mutex);
    refresh_chat();
    g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
    

    return false;
}
