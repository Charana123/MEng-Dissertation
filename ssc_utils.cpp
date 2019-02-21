#include "ssc_utils.hpp"

Stream::Stream(string filename){
    this->mapping = bip::file_mapping(filename.c_str(), bip::read_only);
    this->mapped_rgn = bip::mapped_region(this->mapping, bip::read_only);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    this->mmistream = imemstream(mmaped_data, mmap_size);
}

Set* Stream::get_next_set(){

	string line;
    if(!getline(this->mmistream, line)) return nullptr;

    set<int> vertices;
    boost::tokenizer<> tokens(line);
    for(auto& token : tokens){
        vertices.insert(std::stoi(token));
    }
    Set* s = new Set{vertices, this->counter++};
    return s;
}

void Stream::get_universe(set<int>* universe, int* m){
    for(Set* s; (s = get_next_set()) != nullptr; (*m)++){
        universe->insert(s->vertices.begin(), s->vertices.end());
    }
    reset();
}

void Stream::reset(){
    char const* const mmaped_data = static_cast<char*>(this->mapped_rgn.get_address());
    size_t const mmap_size = this->mapped_rgn.get_size();
    this->mmistream = imemstream(mmaped_data, mmap_size);
    this->counter = 0;
}
