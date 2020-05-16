# Map Design

This will be an interesting one. Even before getting started, I'll have to make design decisions!

Do I want a hash map, an extension of lists, or some inneficient but easy to implement dictionary?

Who knows?!? I sure don't!

Anyway. Let's compare the ideas to decided on what I want to implement

## Deciding on my type

### List Extension

I have a generic struct that has a key and a value, and then make list (already implemented) of that type

```
typedef struct map_entry {
    DCL_MAP_KEY_TYPE key;
    DCL_MAP_VALUE_TYPE value;
} MAP_NAME or whatever
```

and then

```
#define DCL_LIST_TYPE MAP_NAME
#include <dlist.h>
```

or whatever the specifics would be, and then you'd have like a dcl_map_str_str_list_t or something

This approach is messy, but it reuses my existing simple, is relatively easy to understand, and is pretty easy to implement

### Fake Hash Map

I get the hash map functioning without making a hashmap. How?

Well instead of hashing, I iterate through a list of keys and find the index of the one I want, and then I pick the value in another list that is the same as that key

Instead of using a hash function to pick where I go, I just store two lists and search the key list over and over again.

It functions more like a *real* map, but it's probably horribly inneficient.

### Real Hash Map

I'll have to read about this and relearn how to make one. It likely won't be very good, and the generics from before will give me trouble

That said it's probably the *best* option in terms of efficiency and practical use.

I just might not want to do the work for it.

### Picking a Map

I think the pseudo-hash map approach is definitely out because I don't get efficiency really, and I'd have to redo generics which is ugh

So basically it's redo (from scratch) another generics thing, but I get traditional hashmap and efficiency, or sacrifice a bit of practicality for ease of creation and cohesion in the overall library system.

I'm going to go with the latter. Sorry to anyone who was still holding out hope for using this thing :/

## Drivers


