#include "ssc_utils.hpp"

FileObject::FileObject(string file_path){
    this->mapping = new boost::interprocess::file_mapping(file_path.c_str(), boost::interprocess::read_only);
    int file_size = filesize(file_path.c_str());
    this->page_size = boost::interprocess::mapped_region::get_page_size();
    this->pages = file_size / this->page_size + 1;
    this->page = 0;

    this->mapped_rgn = new boost::interprocess::mapped_region(*mapping, boost::interprocess::read_only, this->page * this->page_size, this->page_size);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn->get_address());
    size_t const mmap_size = mapped_rgn->get_size();
    this->mmifs = new imemstream(mmaped_data, mmap_size);
}

size_t FileObject::filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<int>(in.tellg());
}

int FileObject::next_line(string& line){

    // Return line, if line read and EOF isn't reached
    if (getline(*this->mmifs, line) && !this->mmifs->eof()) return 0;
    // Stop reading if at last page
    else if(this->page == this->pages) return -1;
    // Read the remainder of the line after EOF is reached
    else {
        if(++this->page == this->pages) return -1;
        this->mapped_rgn = new boost::interprocess::mapped_region(*mapping, boost::interprocess::read_only, this->page * this->page_size, this->page_size);
        char const* const mmaped_data = static_cast<char*>(mapped_rgn->get_address());
        size_t const mmap_size = mapped_rgn->get_size();
        this->mmifs = new imemstream(mmaped_data, mmap_size);

        string remain; this->next_line(remain);
        line.assign(line + remain);
        return 0;
    }
}

int Stream::get_next_set(Set& s) {
    string line;
    if(this->next_line(line) == -1) return -1;

    boost::tokenizer<> tok(line);
    for(auto beg=tok.begin(); beg!=tok.end(); ++beg){
        s.vertices.insert(std::stoi(*beg));
    }
    s.i = counter++;
    return 0;
}

void Stream::get_universe(Set& universe){
    for(Set s; this->get_next_set(s) != -1; ){
        std::set_difference(s.vertices.begin(), s.vertices.end(), universe.vertices.begin(), universe.vertices.end(), std::inserter(universe.vertices, universe.vertices.end()));
    }
    this->reset();
}

int Stream::get_m(){
    int m = 0;
    for(Set s; this->get_next_set(s) != -1; m++){}
    this->reset();
    return m;
}


/* int main(){ */

/*     Stream stream("./dataset/test.dat"); */
/*     for(int i = 0; i < 5; i++){ */
/*         string str; */
/*         stream.next_line(str); */
/*         cout << "i: " << i << endl; */
/*         cout << str << endl; */
/*     } */
/*     stream.reset(); */

/*     for(Set s; stream.get_next_set(s) != -1; s = {}){ */
/*         cout << "i: " << s.i << endl; */
/*         cout << s.vertices << endl; */
/*     } */
/* } */










