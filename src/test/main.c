#include <stdio.h>

#include <dstr.h>

int main(int argc, char **args) {
    //printf("Hello, world!\n");
    dcl_string_t str_test = dcl_m_new_string("Hello, world!");
    printf("%s\n", str_test.data);
    dcl_m_free_string(str_test);

    return 0;
}