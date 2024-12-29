#include "header.h"


void removePunctuation(string& str) {
    str.erase(remove_if(str.begin(), str.end(), ::ispunct), str.end());
}
