#include "header.h"

void SkyrybosZenkluIstrynimas(string& str) {
    str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
        return !isalnum(c) && !isspace(c); // Palieka tik raides ir skaicius
    }), str.end());
}
