#include "ec_utils.hpp"

FileObject::FileObject(string file_path){
    this->mapping = boost::interprocess::file_mapping(file_path.c_str(), boost::interprocess::read_only);
    int file_size = filesize(file_path.c_str());
    this->page_size = boost::interprocess::mapped_region::get_page_size();
    this->pages = file_size / page_size;
    this->remain = file_size % page_size;
    this->page = 0;

    boost::interprocess::mapped_region mapped_rgn(mapping, boost::interprocess::read_only, this->page * page_size, page_size);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    this->mmifs = imemstream(mmaped_data, mmap_size);
}

size_t FileObject::filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<int>(in.tellg());
}

string* FileObject::next_line(){

    string* line = new string();
    if (getline(this->mmifs, *line)){
        cout << "after  getline3" << endl;
        return line;
    }
    else if(this->page == this->pages + 1){
        cout << "after  getline2" << endl;
        return nullptr;
    }
    else {
        cout << "after  getline1" << endl;
        if(++this->page == this->pages + 1){
            return nullptr;
        }
        boost::interprocess::mapped_region mapped_rgn(mapping, boost::interprocess::read_only, this->page * this->page_size, this->page_size);
        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
        size_t const mmap_size = mapped_rgn.get_size();
        this->mmifs = imemstream(mmaped_data, mmap_size);
        return this->next_line();
    }
}

HyperEdge* HyperEdges::get_next_hyperedge() {
    cout << "before read line" << endl;
    string* line = fo->next_line();
    cout << "after read line" << endl;
    if(line == nullptr) return nullptr;

    set<int> vertices;
    boost::tokenizer<> tok(*line);
    for(auto beg=tok.begin(); beg!=tok.end(); ++beg){
        vertices.insert(std::stoi(*beg));
    }
    Set* s = new Set{vertices, counter++};
    return s;
}

int default_b(set<int>& V){ return V.size(); }
int default_c(set<int>& E){ return 1; }

EdgeCoverInput* read_eci(string filename){
    FileObject* fo = new FileObject(filename);
	return new EdgeCoverInput{.hyperedges=new HyperEdges(fo), .delta_cover=1, .b=default_b, .c=default_c};
}






