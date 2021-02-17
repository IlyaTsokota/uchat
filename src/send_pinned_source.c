#include "chat.h"

gboolean send_pinned_resource(GtkWidget *widget)
{
  GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File",
                                                  GTK_WINDOW(data.win),
                                                  GTK_RESPONSE_ACCEPT,
                                                  "OPEN",
                                                  GTK_RESPONSE_CANCEL,
                                                  "CLOSE",
                                                  //    GTK_RESPONSE_ACCEPT,
                                                  NULL);
  gint res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT)
  {
    puts("AAAAAAAA");
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    char *filename = gtk_file_chooser_get_filename(chooser);
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "1", filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(data.socket_desc, json, sizeof(json));
    send_image(data.socket_desc, filename);
    int stat;
     puts("AAAAAAAA");
    long size = 0;
    size_t packet_size = 1024, packet_count = 0, read_index = 0;
    char buff[1024];
    char *str;
    stat = 1025;
    read(data.socket_desc, (void *)&size, sizeof(long));
    size = ntohl(size);
    str = mx_strnew(size);
     puts("AAAAAAAA");
    do
    {
      if (size < packet_size)
      {
        packet_size = size;
      }
      stat = recv(data.socket_desc, buff, packet_size, 0);
      memcpy(&str[read_index], buff, packet_size);
      if (stat == -1)
      {
        break;
      }
      size -= stat;
      read_index += stat;
      str[read_index] = '\0';

    } while (size > 0);
     puts("AAAAAAAA");
    free(str);
    stat = read(data.socket_desc, buff, 1);
    g_free(filename);
     puts("AAAAAAAA");
  }

  gtk_widget_destroy(dialog);
  return false;
}
