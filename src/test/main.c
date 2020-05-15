#include <stdio.h>

#include <dstr.h>
#include <dlist.h>

#define string_t            dcl_string_t
#define new_str(x)          dcl_new_string(x)
#define substr(x, y, z)     dcl_substr(x, y, z)
#define set_char(x, y, z)   dcl_set_char(x, y, z)
#define cat(x, y)           dcl_concat(x, y)
#define replace(x, y, z)    dcl_replace_string(x, y, z)

int main(int argc, char **args) {
    // Test strings
    string_t str_test = new_str("Hello, world!");
    string_t str_test_2 = new_str("foo bar baz");

    printf("%s\n%s\n%s\n%s\n%s\n",
        str_test.data,
        substr(str_test, 1, 4).data,
        set_char(substr(str_test, 1, 4), 0, '3').data,
        cat(new_str("Hello, "), new_str("world!")).data,
        replace(new_str("foo foo foo"), new_str("foo"), new_str("bar")).data);

    // Test string lists
    dcl_string_list_t test_list = dcl_new_string_list(str_test);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
        test_list.data[0].data,
        dcl_string_list_add(dcl_string_list_add(test_list, str_test), str_test_2).data[1].data,
        dcl_string_list_add(dcl_string_list_add(test_list, str_test), str_test_2).data[2].data,
        dcl_string_list_remove(dcl_string_list_add(test_list, str_test_2), 0).data[0].data,
        dcl_string_list_sort(dcl_string_list_add(dcl_string_list_add(test_list, str_test), str_test_2), &dcl_compare_str).data[0].data,
        dcl_string_list_sort(dcl_string_list_add(dcl_string_list_add(test_list, str_test), str_test_2), &dcl_compare_str).data[1].data,
        dcl_string_list_sort(dcl_string_list_add(dcl_string_list_add(test_list, str_test_2), str_test), &dcl_compare_str).data[2].data);

    // Clean up all library stuff
    dcl_m_cleanup_strings();
    dcl_m_cleanup_lists();

    return 0;
}