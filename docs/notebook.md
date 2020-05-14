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

   + [ ] operators

   + compare

   + substr

   + \+ operator

So I've got an idea of what I need to implement. I'll make some requirements.

## Drivers

### Use Cases

 - UC1: I want to replace char[] array and char * since managing return values with strings are anoying. I want to be able to return type "string"

 - UC2: Strings should be dynamic and be able to be concatenated, split, and substringed

### Quality attributes

 - QA1: Should be able to plug and play with char[] and char *

 - QA2: Should be easily modifiable so I can add more string methods later on as needed

 - QA3: I shouldn't have to worry about managing the memory. It should act as if it's a primitive type and hide any malloc's from me (when using, not when designing the string itself)

### Requirements

 - Must be compatible for x86/x86_64 GNU C as of 2020

### Concerns

 - CRN1: Should be memory safe

