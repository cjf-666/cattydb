#include "where.h"

int where_equal1(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data == i)
                        return -1;
        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (!strcmp(str_data, val))
                        return -1;
        }

        return 0;
}
int where_bigger1(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data > i)
                        return -1;
        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (strcmp(str_data, val)>0)
                        return -1;
        }

        return 0;
}
int where_smaller1(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data < i)
                        return -1;
        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (strcmp(str_data, val)<0)
                        return -1;
        }

        return 0;
}
int where_equal1_n(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data != i)
                        return -1;

        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (strcmp(str_data, val) != 0)
                        return -1;
        }

        return 0;
}
int where_bigger1_n(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data <= i)
                        return -1;
        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (strcmp(str_data, val)<=0)
                        return -1;
        }

        return 0;
}
int where_smaller1_n(tuple_buffer* tp, char* col_name, char* val)
{
        int i = 0;
        char str_data[STRING_LENGTH];
        int int_data;

        if (buf_get_char(tp) != '\0') {
                buf_move_forward(tp, get_tot_bytes());
                return 0;
        }

        int tot = get_bef_by_name(col_name);
        buf_move_forward(tp, tot);
        tot = get_tot_bytes() - tot - get_by_name(col_name);

        if (!strcmp(get_type_by_name(col_name), "Int")) {
                int_data = buf_get_int(tp);
                sscanf(val, "%d", &i);
                buf_move_forward(tp, tot);
                if (int_data >= i)
                        return -1;
        } else {
                int_data = get_by_name(col_name);
                for(i=0; i<int_data; i++)
                        str_data[i] = buf_get_char(tp);
                str_data[i] = '\0';
                buf_move_forward(tp, tot);
                if (strcmp(str_data, val)>=0)
                        return -1;
        }

        return 0;
}

