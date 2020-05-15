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
    string_t str_test_3 = new_str("abcdefg");

    printf("String tests:\n");
    printf("str_test should == 'Hello, world!':\n\t%s\n", str_test.data);
    printf("substr(str_test, 4) == 'ello':\n\t%s\n", substr(str_test, 1, 4).data);
    printf("set char 0 of prev to '3' == '3llo':\n\t%s\n", set_char(substr(str_test, 1, 4), 0, '3').data);
    printf("'Hello, ' ++ 'world!' == 'Hello, world!':\n\t%s\n", cat(new_str("Hello, "), new_str("world!")).data);
    printf("replace all 'foo' with 'bar' in 'foo foo foo' == 'bar bar bar':\n\t%s\n", replace(new_str("foo foo foo"), new_str("foo"), new_str("bar")).data);

    // Test string lists
    printf("\nList Tests\n");

    dcl_string_list_t test_list = dcl_string_list_add(dcl_string_list_add(dcl_new_string_list(str_test), str_test_2), str_test_3);
    dcl_string_list_t test_list_2 = dcl_string_list_remove(test_list, 1);
    dcl_string_list_t test_list_3 = dcl_string_list_insert(test_list_2, str_test_2, 1);
    dcl_string_list_t test_list_4 = dcl_string_list_sort(test_list, (int (*) (const void *, const void *)) &dcl_compare_str);
    dcl_string_list_t test_list_5 = dcl_string_list_sublist(dcl_string_list_add(dcl_string_list_add(test_list, str_test), str_test_2), 1, 4);

    printf("Test List:\n\t%s\n\t%s\n\t%s\n", test_list.data[0].data, test_list.data[1].data, test_list.data[2].data);
    printf("Test List without index 1:\n\t%s\n\t%s\n", test_list_2.data[0].data, test_list_2.data[1].data);
    printf("Test List with index 1 reinserted:\n\t%s\n\t%s\n\t%s\n", test_list_3.data[0].data, test_list_3.data[1].data, test_list_3.data[2].data);
    printf("Test List with items sorted (based on strcmp):\n\t%s\n\t%s\n\t%s\n", test_list_4.data[0].data, test_list_4.data[1].data, test_list_4.data[2].data);
    printf("Test List of sublist:\n\t%s\n\t%s\n\t%s\n\t%s\n", test_list_5.data[0].data, test_list_5.data[1].data, test_list_5.data[2].data, test_list_5.data[3].data);

    // Clean up all library stuff
    dcl_m_cleanup_strings();
    dcl_m_cleanup_lists();

    return 0;
}