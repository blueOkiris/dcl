#include <stdlib.h>
#include <string.h>

#include <dstr.h>

int num_strings = 0;
char **string_data = NULL;

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
    return dcl_new_string("");
}

dcl_string_t dcl_concat(dcl_string_t str1, dcl_string_t str2) {
    return dcl_new_string("");
}

dcl_string_t dcl_replace_string(dcl_string_t str, dcl_string_t substr) {
    return dcl_new_string("");
}

dcl_string_t *dcl_split(dcl_string_t str, dcl_string_t separator) {
    return NULL;
}

void dcl_m_cleanup_strings() {
    for(int i = 0; i < num_strings; i++)
        free(string_data[i]);

    free(string_data);
}
