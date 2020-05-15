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
    DCL_LIST_TYPE x;
} DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME));
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

 - UC1: Stores data in some sort of accessible array and stores the length as well

 - UC2: Dynamically add/remove items from the list

 - UC3: Sort functionality

### Quality attributes

 - QA1: Like string, don't be annoying with memory management on the user end

 - QA2: Must be generic (can use any data type in it)

## Iteration 1

### Goals

UC1, UC2

### Design choices

So naturally, we'll have a pointer to the type of data we're using and we'll have an int to keep length. Of course, we'll keep it generic like in my concept description.

Then we'll have functions that take a list and an item and add it and take a list and an index and remove the item there (both return copies of data).

In order to make use of the description above, I can't make anything in a C file. This means I may no longer need a header guard. It also means my add and subtract functions will be generic.

I think that I don't have a better way to do large scale memory management, so we'll create a giant generic end of program garbage collector again.

### Analysis

Again, not happy on the backend of the memory stuff, but on the front end it satisfies QA1.

UC1 and UC2 are easily met, and QA2 is met with the description/concept thing I already designed.

However, UC3 is *not* met as in using generic things, sorting cannot be done (there's no comparison system)

## Iteration 2

### Goals

UC3

### Design choices

My idea is to pass in a compare function for each object, something like:

```
DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) DLIST_PASTE(DLIST_STRUCT(DCL_LIST_TYPE),_list_sort) (DLIST_STRUCT(DLIST_LIST_TYPE(DCL_NEW_LIST_NAME)) old_list, int (*cmpr_func) ( DCL_LIST_TYPE a, DCL_LIST_TYPE b ) {
    ...
}
```

so you'd get

```
dcl_int_list_t dcl_int_list_sort (dcl_int_list_t old_list, int (*cmpr_func) ( int a, int b ) {
    ...
}
```

### Analysis

Assuming this works, this is a pretty good idea. It allows basically anything to be used in a list, and follows the typical C compare function system. For instance if you had char \*s, you could pass `&strcmpr` (I think). And with dcl_string_t, I think you can use `&dcl_compare_str`. So I actually like this a lot.

The problem is going to be the memory management now that I think about it, since there won't be a c file to store the giant array thing in. I might have to do it on a case by case basis, or something. Either way it needs to be figured out. I don't want to hand manage the memory or not use intuitive add/remove methods.

## Iteration 3

### Goals

QA1

### Design Choices

I need to fix the memory management thing because as it stands, I can't implement it.

One option is to just make a free call for everything, but as I realized in my string attempt, that option SUCKS. Managing memory that way when we're constantly remaking new structs is just awful.

Another is to use the solution I found for strings, but unfortunately I can't do that without a c file...

Or can I?

What if I make a c file (and header) that creates an external void ** and int for managing list memory, and then I can access *that* list in all the creation of new lists! Then I can put a dcl_lists_free function in the second header and boom! I can call that instead. Or I can even make a second header guard just for that method and then add the C file which will undef the first guard and not have any types defined, and then def (by including) the second guard

### Analysis

This works pretty well and is easily adaptable for users

## Iteration 4

### Purpose

I need to implement the sorting algorithm for the list. I'm gonna do a pretty simple sort, but it will be helpful to have an insert function I think, even if my sort ends up using arrays in the end

### Design Choices

I don't know what this sort is called, but I believe it is O(n * log(n)), maybe TreeSort? if that's a thing

Basically, iterate through a list, and create a new list as you go. If the item is bigger than the center item, check left, if greater check right. Then check if the item is less than or greater than for the sub list, and so on. You basically for a binary tree like:

&nbsp;&nbsp;5
&nbsp;2&nbsp;&nbsp;8
1&nbsp;&nbsp;6&nbsp;7

but it's stored as my list type and then returned sorted.

Alternatively, I can just use qsort on "data" and then rebind it to a new list.

This will be MUCH less memory intensive, and probably work better, so I'll do that

### Analysis

I may need an insert method and a sublist method for my algorithm, but I'll include them anyway since they could be useful.

qsort is a nice standard function that afaik people trust, so it'll probably work great for my library, and it will be better as far as memory management is concerned.
