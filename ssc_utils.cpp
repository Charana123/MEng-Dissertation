#include "ec_utils.hpp"

FileObject::FileObject(string file_path){
    this->mapping = new boost::interprocess::file_mapping(file_path.c_str(), boost::interprocess::read_only);
    int file_size = filesize(file_path.c_str());
    this->page_size = boost::interprocess::mapped_region::get_page_size();
    this->pages = file_size / this->page_size;
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

string* FileObject::next_line(){

    string* line = new string("one");
    if (getline(*this->mmifs, *line) && !this->mmifs->eof()){
        return line;
    }
    else if(this->page == this->pages + 1){
        return nullptr;
    }
    else {
        if(++this->page == this->pages + 1){
            return nullptr;
        }
        this->mapped_rgn = new boost::interprocess::mapped_region(*mapping, boost::interprocess::read_only, this->page * this->page_size, this->page_size);
        char const* const mmaped_data = static_cast<char*>(mapped_rgn->get_address());
        size_t const mmap_size = mapped_rgn->get_size();
        this->mmifs = new imemstream(mmaped_data, mmap_size);
        return new string(*line + *this->next_line());
    }
}

Set* Stream::get_next_set() {
    string* line = this->next_line();
    if(line == nullptr) return nullptr;

    set<int> vertices;
    boost::tokenizer<> tok(*line);
    for(auto beg=tok.begin(); beg!=tok.end(); ++beg){
        vertices.insert(std::stoi(*beg));
    }
    Set* s = new Set{vertices, counter++};
    return s;
}

Set* Stream::get_universe(){
    Set* universe = new Set({{}, -1});
    for(Set* he; (he = this->get_next_set()) != nullptr; ){
        std::set_difference(he->vertices.begin(), he->vertices.end(), universe->vertices.begin(), universe->vertices.end(), std::inserter(universe->vertices, universe->vertices.end()));
    }
    this->reset();
    return universe;
}

int Stream::find_m(){
    int m;
    for(m = 0; this->get_next_set() != nullptr; m++){}
    this->reset();
    return m;
}


int main(){

    Stream stream("./dataset/chess.dat");
    /* for(int i = 0; i < 3196; i++){ */
    /*     string* str = he.next_line(); */
    /*     cout << "i[" << i << "] = " << *str << endl; */
    /* } */

    /* ofstream myfile("./dataset/read_dataset"); */
    /* for(int i = 0; i < 3000; i++){ */
    /*     myfile << i << " " << i * 1 << " " << i * 2 << endl; */
    /* } */
}










