#ifdef DCL_LIST_TYPE
#ifdef DCL_NEW_LIST_NAME
#ifdef DCL_LIST_HEADER

#ifndef _DLIST_FUNC_H_
#define _DLIST_FUNC_H_

extern void **e_list_data;
extern int e_num_lists;
void dcl_m_cleanup_lists();

#endif

#define DLIST_PASTE(x, y)   x ## y
#define DLIST_LIST_TYPE(T)  DLIST_PASTE(T, _list_t)
#define DLIST_STRUCT(x)     DLIST_PASTE(dcl_, x)
#define DLIST_ADD_NEW(x)    DLIST_PASTE(new_, x)
#define DLIST_ADD_LIST(x)   DLIST_PASTE(x, _list)
#define DLIST_ADD_ADD(x)    DLIST_PASTE(x, _add)
#define DLIST_ADD_REMOVE(x) DLIST_PASTE(x, _remove)

#include <stdlib.h>

// Define stuf for header files

typedef struct dcl_list {
    int length;
    DCL_LIST_TYPE *data;
} DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME));

DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_NEW(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) (DCL_LIST_TYPE first);
DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_ADD(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) old_list, DCL_LIST_TYPE elem );
DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_REMOVE(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) old_list, int index );
#else

// Define the implementations for c files

DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_NEW(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) (DCL_LIST_TYPE first) {
    DCL_LIST_TYPE *new_array = malloc(sizeof(DCL_LIST_TYPE));
    new_array[0] = first;

    e_num_lists++;
    if(e_list_data == NULL)
        e_list_data = malloc(sizeof(void *));
    else
        e_list_data = realloc(e_list_data, sizeof(void *) * (e_num_lists));
    
    e_list_data[e_num_lists - 1] = (void *) new_array;

    return ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) ) { 1, new_array };
}

DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_ADD(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) old_list, DCL_LIST_TYPE elem ) {
    DCL_LIST_TYPE *new_array = malloc(sizeof(DCL_LIST_TYPE) * (old_list.length + 1));

    memcpy(new_array, old_list.data, sizeof(DCL_LIST_TYPE) * old_list.length);
    new_array[old_list.length] = elem;

    e_num_lists++;
    e_list_data = realloc(e_list_data, sizeof(void *) * (e_num_lists));
    
    e_list_data[e_num_lists - 1] = (void *) new_array;

    return ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) ) { old_list.length + 1, new_array };
}

DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_STRUCT(DLIST_ADD_REMOVE(DLIST_ADD_LIST(DCL_NEW_LIST_NAME))) ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) old_list, int index ) {
    DCL_LIST_TYPE *new_array = malloc(sizeof(DCL_LIST_TYPE) * (old_list.length - 1));

    memcpy(new_array, old_list.data, sizeof(DCL_LIST_TYPE) * index);
    memcpy(new_array, old_list.data + index + 1, sizeof(DCL_LIST_TYPE) * (old_list.length - index - 1));

    e_num_lists++;
    e_list_data = realloc(e_list_data, sizeof(void *) * (e_num_lists));
    
    e_list_data[e_num_lists - 1] = (void *) new_array;

    return ( DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) ) { old_list.length - 1, new_array };
}

#endif
#endif
#endif
