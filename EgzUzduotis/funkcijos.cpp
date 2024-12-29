#include "header.h"

void keepAlphaNumeric(string& str) {
    str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
        return !isalnum(c) && !isspace(c); // Palieka tik raides, skaičius ir tarpus
    }), str.end());
}
