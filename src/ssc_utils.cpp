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

void OfflineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M){
    *universe = *this->sci->universe;
    *m = this->sci->m;
    this->m = *m;
    *avg = this->sci->avg;
    *M = this->sci->M;
    *median = this->sci->median;
    *largest = this->sci->largest;
}

void OnlineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M){
    *m = 0;
    *M = 0;
    *median = 0; *largest = 0;
    vector<unsigned long> set_sizes;
    set<unsigned long> universe_s;
    for(Set* s; (s = get_next_set()) != nullptr; (*m)++){
        *M += s->vertices.size();
        set_sizes.push_back(s->vertices.size());
        if(s->vertices.size() > *largest) *largest = s->vertices.size();
        universe_s.insert(s->vertices.begin(), s->vertices.end());
    }
    universe->insert(universe->end(), universe_s.begin(), universe_s.end());
    *avg = (*M)/(*m);
    std::nth_element(set_sizes.begin(), set_sizes.begin() + set_sizes.size()/2, set_sizes.end());
    *median = set_sizes[set_sizes.size()/2];
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
