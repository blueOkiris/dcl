#pragma once

// Create a string list type for dcl_m_split
#define DCL_LIST_TYPE string
#include <dlist.h>
#undef DCL_LIST_TYPE
#undef _DLIST_H_

typedef struct dcl_string {
    int length;
    const char *data;
} dcl_string_t;

dcl_string_t dcl_new_string(const char *value);

dcl_string_t dcl_substr(dcl_string_t str, int index, int length);
dcl_string_t dcl_set_char(dcl_string_t str, int index, char new_value);
dcl_string_t dcl_concat(dcl_string_t str1, dcl_string_t str2);
int dcl_compare_str(dcl_string_t str1, dcl_string_t str2);
int dcl_index_of(dcl_string_t str, dcl_string_t substr, int start);
dcl_string_t dcl_replace_string(dcl_string_t str, dcl_string_t substr, dcl_string_t newsub);

void dcl_m_cleanup_strings();

dcl_string_list_t dcl_split(dcl_string_t str, dcl_string_t separator);
