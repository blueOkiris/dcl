#include <stdio.h>

#include <dstr.h>

int main(int argc, char **args) {
    //printf("Hello, world!\n");
    dcl_string_t str_test = dcl_m_new_string("Hello, world!");
    dcl_string_t str_sub_test = dcl_m_substr(str_test, 1, 4);

    printf("%s\n%s\n", str_test.data, str_sub_test.data);

    dcl_m_free_string(str_test);
    dcl_m_free_string(str_sub_test);

    return 0;
}