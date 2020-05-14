#include <stdlib.h>
#include <string.h>

#include <dstr.h>

int num_strings = 0;
char **string_data = NULL;

#define DCL_LIST_TYPE dcl_string_t
#define DCL_NEW_LIST_NAME string
#undef DCL_LIST_HEADER
#include <dlist.h>
#undef DCL_LIST_TYPE
#undef DCL_NEW_LIST_NAME

dcl_string_t dcl_new_string(const char *value) {
    int size = strlen(value);

    char *data = malloc(sizeof(char) * (size + 1));
    strcpy(data, value);
    data[size] = '\0';

    num_strings++;
    if(string_data == NULL)
        string_data = malloc(sizeof(char *));
    else
        string_data = realloc(string_data, sizeof(char *) * (num_strings));
    
    string_data[num_strings - 1] = data;

    return (dcl_string_t) { size, data };
}

dcl_string_t dcl_substr(dcl_string_t str, int index, int length) {
    char *new_string = malloc(sizeof(char) * (length + 1));
    memcpy(new_string, str.data + index, length);
    new_string[length] = '\0';

    dcl_string_t new_string_t = dcl_new_string((const char *) new_string);
    free(new_string);
    return new_string_t;
}

dcl_string_t dcl_set_char(dcl_string_t str, int index, char new_value) {
    char *new_string = malloc(sizeof(char) * (str.length + 1));
    strcpy(new_string, str.data);
    new_string[str.length] = '\0';
    new_string[index] = new_value;

    dcl_string_t new_string_t = dcl_new_string((const char *) new_string);
    free(new_string);
    return new_string_t;
}

dcl_string_t dcl_concat(dcl_string_t str1, dcl_string_t str2) {
    char *new_string = malloc(sizeof(char) * (str1.length + str2.length + 1));
    strcpy(new_string, str1.data);
    strcpy(new_string + str1.length, str2.data);
    new_string[str1.length + str2.length] = '\0';

    dcl_string_t new_string_t = dcl_new_string((const char *) new_string);
    free(new_string);
    return new_string_t;
}

int dcl_compare_str(dcl_string_t str1, dcl_string_t str2) {
    return strcmp(str1.data, str2.data);
}

int dcl_index_of(dcl_string_t str, dcl_string_t substr, int start) {
    for(int i = 0; i < str.length - substr.length + 1; i++) {
        if(0 == dcl_compare_str(dcl_substr(str, i, substr.length), substr))
            return i;
    }

    return -1;
}

dcl_string_t dcl_replace_string(dcl_string_t str, dcl_string_t substr, dcl_string_t newsub) {
    int ind;
    dcl_string_t current = dcl_new_string(str.data);

    do {
        ind = dcl_index_of(current, substr, 0);
        if(ind == -1)
            continue;

        dcl_string_t left = dcl_substr(current, 0, ind);
        dcl_string_t right = dcl_substr(current, ind + substr.length, current.length - (ind + substr.length));

        current = dcl_concat(left, dcl_concat(newsub, right));
    } while(ind != -1);

    return current;
}

void dcl_m_cleanup_strings() {
    if(string_data == NULL)
        return;

    for(int i = 0; i < num_strings; i++)
        free(string_data[i]);

    free(string_data);
    string_data = NULL;
}
