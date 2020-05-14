#ifdef DCL_LIST_TYPE
#ifdef DCL_NEW_LIST_NAME

#ifndef _DLIST_FUNC_H_
#define _DLIST_FUNC_H_

extern void **e_list_data;
extern int e_num_lists;
void dcl_m_cleanup_lists();

#endif

#ifndef _DLIST_H_
#define _DLIST_H_

#define DLIST_PASTE(x, y)   x ## y
#define DLIST_LIST_TYPE(T)  DLIST_PASTE(T, _list_t)
#define DLIST_STRUCT(x)     DLIST_PASTE(dcl_, x)      

typedef struct dcl_list {
    int length;
    DCL_LIST_TYPE *data_array;
} DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME));

#endif
#endif
#endif
