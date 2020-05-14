# Designing Strings

## Concept

I want to implement strings into this library.

C "strings" are simply character arrays, but they could be so much more!

Some string *object* examples:

 - Important Java String class (C#'s string works fairly similarly)

   + String(char[] value) - Convert chars into "char array" object, which is string

   + charAt(int index) - Get char at a position

   + compareTo(String other)

   + concat(String str)

   + endsWith(String str), startsWith(String str)

   + indexOf(char), indexOf(String)

   + isEmpty()

   + length()

   + replace(char, char), replace(String, String)

   + String[] split(String regex)

   + char[] toCharArray()

   + String toLower(), String toUpper()

   + Note string data is immutable, so it always returns a new string copy, never the original

 - Important C++ string methods:

   + length()

   + \[ \] operators

   + compare

   + substr

   + \+ operator

So I've got an idea of what I need to implement. I'll make some requirements.

## Drivers

### Use Cases

 - UC1: I want to replace char\[\] array and char \* since managing return values with strings are anoying. I want to be able to return type "string"

 - UC2: Strings should be dynamic and be able to be concatenated, split, and substringed

### Quality attributes

 - QA1: Should be able to plug and play with char\[\] and char \*

 - QA2: Should be easily modifiable so I can add more string methods later on as needed

 - QA3: I shouldn't have to worry about managing the memory. It should act as if it's a primitive type and hide any malloc's from me (when using, not when designing the string itself)

### Requirements

 - Must be compatible for x86/x86_64 GNU C as of 2020

### Concerns

 - CRN1: Should be memory safe

## Iteration 1

### Purpose

I want to focus on UC1 while keeping in mind QA3 and CRN1

So basically, I need to create a returnable type of "string" that manages memory behind the scenes

### Design Decisions

I'll try to work this as if it's OOP first, and then return to the design stuff

Basically you'd have a class that has some underlying char \* and keep track of its length (without needing to be updated)

Then you could get the length, and there would be methods to append to the data (and update length)

Then I'd have a couple find methods and a lookup method. I'd love to use \[ \] for indexing, but I don't think that will work.

Going to C, I could just use \[ \] on the "data" variable in the struct. I could make it immutable and make that const.

But how do I store data w/ out malloc(ideal)? Well, instead of a char \*, I use char \[ length \]. That way all data is just stored in the struct.

So you'd have something like this:

```
typedef struct string {
    int length;
    const char data[];
} struct_t;
```

It really might be that simple.

I also have to decide on names for functions. Do I just do "new_string" or should I do "dcl_new_string" or even "dcl_newString"? I like the idea that using the "dcl_" prefix will help to not conflict with other libraries, but it makes everything wordier.

However, I think it best to do all "_" (not camel) as that's the standard for C, and then to add the prefix anyway (for all classes in the library)

Then I'd need a few methods. I could pass it in as a parameter and return a new value, or I could make a function pointer, though it would have to do the same thing anyway, so essentially these will be functions to implement:

 1. string_t dcl_new_string(const char *value)

 2. string_t dcl_append_string(string_t start)

 3. string_t dcl_substr(string_t start, int index, int length)

 4. string_t dcl_set_char(string_t start, int index, char new_value)

 5. string_t dcl_concat(string_t str1, string_t str2)

 6. string_t *dcl_m_split(string_t str, string_t separator) - Note that this one uses malloc to create a list of strings (maybe I'll try to design a list system next)

 7. void dcl_string_to_array(char *dest, string_t str)

### Analysis

I like this design. I have all the needed functions, and it seems that memory allocation will be totally unnecessary, even for return values!

I don't love that I have a bunch of functions that take string and return new string (I'd prefer modification of state here), but I think its the best idea for C, and I don't have another solution. Plus, there are some who'd argue that immutability of strings is a good idea generally, so at least this enforces that easily.

The current design also satisfies QA2, in that all I'd need for a new string "method" is taking a string_t as a parameter

Function 7 satisfies QA1, and the various others satisfy UC2

So basically this first idea actually will satisfy all my needs, so I can start coding
