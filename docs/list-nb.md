# Designing List Type

## Concept

I already have a framework in mind for the generic type

```
#define DCL_LIST_TYPE whatever
#include <dlist.h>
#undef DCL_LIST_TYPE
#undef _DLIST_H_
```

The header guard may end up being unecessary, but I'll keep it for now.

Basically, I define a generic set of operations like adding, sorting, etc but I leave it in terms of DLIST_LIST_TYPE(DCL_LIST_TYPE):

```
#define DLIST_PASTE(x, y)   x ## y
#define DLIST_LIST_TYPE(T)  DLIST_PASTE(T, _list_t)
#define DLIST_STRUCT(x)     DLIST_PASTE(dcl_, x)

typedef struct dcl_list {
    DLIST_LIST_TYPE(DCL_LIST_TYPE) x;
} DLIST_STRUCT(DLIST_LIST_TYPE(DCL_LIST_TYPE));
```

And then when I include that thing, it will generate the list type that I want, so

```
#define DCL_LIST_TYPE int
#include <dlist.h>
#undef DCL_LIST_TYPE
#undef _DLIST_H_
```

would generate:

```
typedef struct dcl_list {
    int x;
} dcl_int_list_t;
```

Which means I can define a whole set of generic list operations without knowing the data type itself!

## Drivers

### Use Cases
