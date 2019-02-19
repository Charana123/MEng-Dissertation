#ifndef EC_UTILS_H_
#define EC_UTILS_H_
// Edge Cover Utilities

#include "gp_utils.hpp"

using namespace std;

class FileObject {
    public:
        FileObject(string filename);
        int next_line(string& line);
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
        int get_next_set(Set& s);
        void get_universe(Set& universe);
        int get_m();
        void reset() {
            this->counter = 0;
            this->page = 0;
            this->mapped_rgn = new boost::interprocess::mapped_region(*mapping, boost::interprocess::read_only, this->page * this->page_size, this->page_size);
            char const* const mmaped_data = static_cast<char*>(mapped_rgn->get_address());
            size_t const mmap_size = mapped_rgn->get_size();
            this->mmifs = new imemstream(mmaped_data, mmap_size);
        }
    private:
        int counter = 0;
};

#endif
