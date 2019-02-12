#ifndef EC_UTILS_H_
#define EC_UTILS_H_
// Edge Cover Utilities

#include "gp_utils.hpp"

using namespace std;
using HyperEdge = Set;

class FileObject {
    public:
        FileObject(string filename);
        string* next_line();
    private:
        boost::interprocess::file_mapping mapping;
        int page_size;
        int pages;
        int remain;
        size_t filesize(const char* file_path);
        int page;
        imemstream mmifs;
};

class HyperEdges {
    public:
        HyperEdges(FileObject* fo) : fo(fo){}
        HyperEdge* get_next_hyperedge();
    private:
        int counter = 0;
        FileObject* fo;
};

struct EdgeCoverInput
{
    HyperEdges* hyperedges;
    float delta_cover;
    std::function<int(set<int>&)> b; // vertex benefits
    std::function<int(set<int>&)> c; // edge costs
};

EdgeCoverInput* read_eci(string filename);

#endif
