#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Coord.h"

/// <summary>
/// Gets a substring between the given left and right characters.
/// </summary>
/// <param name="str">The string to search</param>
/// <param name="l">Left character</param>
/// <param name="r">Right character</param>
/// <returns>The substring between [l] and [r]</returns>
inline std::string get_string_between(std::string& str, char l, char r) {

    size_t li = str.find(l);
    size_t ri = str.find(r);

    return str.substr(li + 1, ri - li - 1);

}

/// <summary>
/// Splits a string by the given character and returns a vector of the resulting sub-strings.
/// </summary>
/// <param name="str">The string to split</param>
/// <param name="c">The character to split by</param>
/// <returns>A list of the resulting sub-strings</returns>
inline std::vector<std::string> string_split(std::string& str, char c) {

    std::vector<std::string> result;

    std::string s = str;
    s.push_back(c);

    size_t prev_c = -1;
    size_t next_c = 0;

    while ((next_c = s.find(c, next_c + 1)) != std::string::npos) {
        std::string r = s.substr(prev_c + 1, next_c - prev_c - 1);
        result.push_back(r);
        prev_c = next_c;
    }

    return result;

}

/// <summary>
/// Checks if any of the elements in a vector is equal to the given element.
/// </summary>
/// <param name="vec">Vector of elements</param>
/// <param name="element">Element to check against the vector</param>
/// <returns>True if any of the elements in the vector are equal to the given element</returns>
inline bool vector_contains(std::vector<Coord> vec, Coord element) {

    for (Coord el : vec) {
        if (el == element)
            return true;
    }

    return false;

}