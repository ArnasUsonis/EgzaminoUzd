#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cerr;
using std::string;
using std::transform;
using std::map;
using std::getline;
using std::istringstream;
using std::remove_if;

void removePunctuation(string& str);

#endif // HEADER_H_INCLUDED
