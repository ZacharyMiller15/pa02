#include "utilities.h"

bool isValidPrefix(std::string prefix, std::string word) {
    if (prefix.length() > word.length()) return false;

    if (prefix == word || word.substr(0, prefix.length()) == prefix) return true;

    return false;
}