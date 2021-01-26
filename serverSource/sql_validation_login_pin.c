#include "server.h"

char *pin_check(MYSQL *con, char *login, char *pin)
{
    char *answer;
    char *encrypted_pin = crypt(pin, "1337_1488");
    const char *request_parts[] = {"SELECT COUNT(user.u_id) FROM user Join credentials on credentials.u_id = user.u_id WHERE credentials.cr_pincode = \"", encrypted_pin, 
    "\" AND user.u_login = \"", login, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    //puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR
    //free(encrypted_pin);//IR

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
    mysql_close(con);
    return answer; //0 or >0
}
