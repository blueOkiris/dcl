#ifndef _DLIST_H_
#define _DLIST_H_

#define DLIST_PASTE(x, y)   x ## y
#define DLIST_LIST_TYPE(T)  DLIST_PASTE(T, _list_t)
#define DLIST_STRUCT(x)     DLIST_PASTE(dcl_, x)

typedef struct dcl_list {
    int x;
} DLIST_STRUCT(DLIST_LIST_TYPE(DCL_LIST_TYPE));

#endif
