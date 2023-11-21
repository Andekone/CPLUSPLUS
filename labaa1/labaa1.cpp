#include <iostream>
#include <string>
#include <algorithm>

/*
1) strlen - C++ has a size() function for string objects of std::string class, which returns the length of the string.
2) strcpy - in C++ you can use assignment operator = to copy strings: string a = "foo"; string b; a = b;.
3) strcmp - C++ has the string.compare() function that compares two strings and returns the result of the comparison (a negative number if the first string is smaller; a positive number if the first string is larger; 0 if the strings are equal).
4) strcat - C++ has a + operator that can be used to concatenate strings OR strcat().
5) someString[index] - C++ uses the [] operator to access string characters by index: string a = "boo"; a[index] OR a.at(index).
6) push_back - a method of the std::string class that adds a character to the end of the string. In C: char str[5] = "Foo"; arr[3] = value; - no direct equivalent.
7) pop_back - a method of std::string class that removes the last character from the string. In C: char str[5] = "Foo"; str[strlen(str) - 1] = "\0"; - no direct equivalent.

The main difference between strings in C and
C++ is that in C strings are represented as arrays of characters,
while in C++ there are arrays of characters.
arrays of characters, while in C++ there is a std::string class
that provides convenient methods and operators for working with
strings. and operators for working with strings. The std::string
class provides safer work with strings because it performs
automaticwith strings, because it performs automatic memory
management and prevents buffer overflow errors,
related to buffer overflows. Also, the std::string
class provides more convenient functions for working with strings.
*/


int main() {
    // Remove spaces and punctuation marks
    inputString.erase(
        std::remove_if(inputString.begin(), inputString.end(),
            [](unsigned char c) { return std::isspace(c) || std::ispunct(c); }),
        inputString.end());

    //  Sort the letters in alphabetical order
    std::sort(inputString.begin(), inputString.end());

    // Output the sorted string
    std::cout << "the sorted string: " << inputString << std::endl;

    return 0;
}﻿
