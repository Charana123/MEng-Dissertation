#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
/* #include <boost/tokenizer.hpp> */
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
namespace bip = boost::interprocess;

struct Set{
    set<int> vertices;
    int i;
};

bool operator==(const Set& a1, const Set& a2);

struct SetCoverInput
{
    vector<Set> sets;
    Set universe;
};

SetCoverInput read_problem(string filename);

struct membuf: streambuf {
    membuf(char const* base, size_t size) {
        char* p(const_cast<char*>(base));
        this->setg(p, p, p + size);
    }
};

struct imemstream: virtual membuf, istream {
    imemstream(char const* base, size_t size)
        : membuf(base, size)
        , istream(static_cast<streambuf*>(this)) {
    }
};

#endif
