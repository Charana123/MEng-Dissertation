#ifndef EC_UTILS_H_
#define EC_UTILS_H_
// Edge Cover Utilities

#include "gp_utils.hpp"

using namespace std;

class FileObject {
    public:
        FileObject(string filename);
        string* next_line();
        void reset() { this->page = 0; }
    protected:
        size_t filesize(const char* file_path);
        int page_size;
        int pages;
        int page;
        boost::interprocess::file_mapping* mapping;
        boost::interprocess::mapped_region* mapped_rgn;
        imemstream* mmifs;
};

class Stream : public FileObject {
    public:
        Stream(string filename) : FileObject(filename){}
        Set* get_next_set();
        Set* get_universe();
    private:
        int counter = 0;
};





















#endif
