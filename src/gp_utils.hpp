#ifndef GP_UTILS_H_
#define GP_UTILS_H_
// General Purpose Utilities

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "prettyprint.hpp"
#include <fstream>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

using namespace std;

struct Set{
    vector<int> vertices;
    int i;
};

bool operator==(const Set& a1, const Set& a2);
std::ostream& operator<<(std::ostream& o, const Set& s);

struct membuf: streambuf {
    membuf(char const* base, size_t size) {
        char* p(const_cast<char*>(base));
        this->setg(p, p, p + size);
    }
};

struct imemstream: virtual membuf, istream {
    imemstream()
        : membuf(nullptr, 0)
          , istream(static_cast<streambuf*>(this)){
    }
    imemstream(char const* base, size_t size)
        : membuf(base, size)
        , istream(static_cast<streambuf*>(this)) {
    }
};

#endif
