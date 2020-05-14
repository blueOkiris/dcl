#include <stdlib.h>

#define _DLIST_H_
#include <dlist.h>
#undef _DLIST_H_

void **e_list_data = NULL;
int e_num_lists = 0;

void dcl_m_cleanup_lists() {
    if(e_list_data == NULL)
        return;

    for(int i = 0; i < e_num_lists; i++)
        free(e_list_data[i]);
    free(e_list_data);
    e_list_data = NULL;
}