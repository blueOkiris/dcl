#include <stdio.h>

#include <dstr.h>

#define string_t            dcl_string_t
#define new_str(x)          dcl_new_string(x)
#define substr(x, y, z)     dcl_substr(x, y, z)
#define set_char(x, y, z)   dcl_set_char(x, y, z)
#define cat(x, y)           dcl_concat(x, y)

int main(int argc, char **args) {
    string_t str_test = new_str("Hello, world!");

    printf("%s\n%s\n%s\n%s\n",
        str_test.data,
        substr(str_test, 1, 4).data,
        set_char(substr(str_test, 1, 4), 0, '3').data,
        cat(new_str("Hello, "), new_str("world!")).data);

    dcl_m_cleanup_strings();

    return 0;
}