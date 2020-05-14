#include <stdlib.h>
#include <string.h>

#include <dstr.h>

dcl_string_t dcl_m_new_string(const char *value) {
    int size = strlen(value);

    char *data = malloc(sizeof(char) * (size + 1));
    strcpy(data, value);
    data[size] = '\0';

    return (dcl_string_t) { size, data };
}

dcl_string_t dcl_m_substr(dcl_string_t str, int index, int length) {
    char *new_string = malloc(sizeof(char) * (length + 1));
    memcpy(new_string, str.data + index, length);
    new_string[length] = '\0';

    dcl_string_t new_string_t = dcl_m_new_string((const char *) new_string);
    new_string_t.length = length;
    free(new_string);
    return new_string_t;
}

dcl_string_t dcl_m_set_char(dcl_string_t str, int index, char new_value) {
    return dcl_m_new_string("");
}

dcl_string_t dcl_m_concat(dcl_string_t str1, dcl_string_t str2) {
    return dcl_m_new_string("");
}

dcl_string_t dcl_m_replace_string(dcl_string_t str, dcl_string_t substr) {
    return dcl_m_new_string("");
}

dcl_string_t *dcl_m_split(dcl_string_t str, dcl_string_t separator) {
    return NULL;
}

void dcl_m_free_string(dcl_string_t str) {
    free((char *) str.data);
}

void dcl_string_to_array(char *dest, dcl_string_t str) {

}