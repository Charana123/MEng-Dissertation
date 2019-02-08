#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "prettyprint.hpp"

using namespace std;
using namespace boost;
namespace bip = boost::interprocess;

struct Set{
    set<int> vertices;
    int i;
};

bool operator==(const Set& a1, const Set& a2);
std::ostream& operator<<(std::ostream& o, const Set& s);

struct SetCoverInput
{
    map<int, Set> sets;
    Set universe;
};

struct SetCoverOutput {
    std::set<int> Sigma;
    Set C;
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
