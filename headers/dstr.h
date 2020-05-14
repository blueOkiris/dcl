#pragma once

typedef struct dcl_string {
    int length;
    const char *data;
} dcl_string_t;

dcl_string_t dcl_m_new_string(const char *value);

dcl_string_t dcl_substr(dcl_string_t str, int index, int length);
dcl_string_t dcl_set_char(dcl_string_t str, int index, char new_value);
dcl_string_t dcl_concat(dcl_string_t str1, dcl_string_t str2);
dcl_string_t dcl_replace_string(dcl_string_t str, dcl_string_t substr);

void dcl_m_free_string(dcl_string_t str);

dcl_string_t *dcl_m_split(dcl_string_t str, dcl_string_t separator);
void dcl_dcl_string_to_array(char *dest, dcl_string_t str);