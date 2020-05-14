#include <stdio.h>

#include <dstr.h>

int main(int argc, char **args) {
    dcl_string_t str_test = dcl_new_string("Hello, world!");

    printf("%s\n%s\n%s\n",
        str_test.data,
        dcl_substr(str_test, 1, 4).data,
        dcl_set_char(dcl_substr(str_test, 1, 4), 0, '3').data);

    dcl_m_cleanup_strings();

    return 0;
}