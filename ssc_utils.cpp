#include "ssc_utils.hpp"

OnlineStream::OnlineStream(string filename) : Stream() {
    this->mapping = bip::file_mapping(filename.c_str(), bip::read_only);
    this->mapped_rgn = bip::mapped_region(this->mapping, bip::read_only);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    this->mmistream = new imemstream(mmaped_data, mmap_size);
}

OfflineStream::OfflineStream(string filename) : Stream() {
    this->sci = read_sci(filename);
}

Set* OfflineStream::get_next_set(){
    if(this->position >= m) return nullptr;
    return &(*this->sci->sets)[this->position++];
}

Set* OnlineStream::get_next_set(){

	string line;
    if(!getline(*this->mmistream, line)) return nullptr;

    Set* s = new Set{{}, position};
    boost::tokenizer<> tokens(line);
    for(auto& token : tokens){
        s->vertices.push_back(std::stoi(token));
    }
    this->position++;
    return s;
}

void OfflineStream::get_universe(vector<int>* universe, int* m, int* avg){
    *universe = *this->sci->universe;
    *m = this->sci->m;
    this->m = *m;
    *avg = this->sci->avg;
}

void OnlineStream::get_universe(vector<int>* universe, int* m, int* avg){
    *m = 0;
    int total = 0;
    set<int> universe_s;
    for(Set* s; (s = get_next_set()) != nullptr; (*m)++){
        total += s->vertices.size();
        universe_s.insert(s->vertices.begin(), s->vertices.end());
    }
    universe->insert(universe->end(), universe_s.begin(), universe_s.end());
    *avg = total/(*m);
    reset();
}

void OfflineStream::reset(){
    this->position = 0;
}

void OnlineStream::reset(){
    char const* const mmaped_data = static_cast<char*>(this->mapped_rgn.get_address());
    size_t const mmap_size = this->mapped_rgn.get_size();
    this->mmistream = new imemstream(mmaped_data, mmap_size);
    this->position = 0;
}
