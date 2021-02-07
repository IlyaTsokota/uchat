#include "server.h"

char *add_user_to_group_chat(MYSQL *con, char *user_id, char *ch_id)
{
    char *answer;

    const char *request_parts[] = {"SELECT count(u_id) from chatusers where u_id = \"", user_id, "\" and ch_id = \"", ch_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    mysql_free_result(result);
    if (atoi(answer) == 1)
        return "0"; //user already exist in this chat

    //Добавить юзера
    const char *request_parts1[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", ch_id, "\",\"", user_id, "\",\"0\");", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    mysql_close(con);

    return "1";
}