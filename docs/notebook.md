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

