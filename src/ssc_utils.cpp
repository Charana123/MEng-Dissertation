#include "ssc_utils.hpp"

POfflineStream** get_streams(string filename, int ts) {
    OfflineStream* stream = new OfflineStream(filename);
    POfflineStream** streams = new POfflineStream*[ts];
    vector<Set*>* sets = new vector<Set*>[ts];

    Set* s;
    unsigned long tblock = stream->sci->m / ts;
    for(int t = 0; t < ts; t++){
        for(unsigned long ts = 0; ts < tblock && (s = stream->get_next_set()) != nullptr; ){
            sets[t].push_back(s);
        }
    }
    for(; (s = stream->get_next_set()) != nullptr; ){
        sets[ts-1].push_back(s);
    }
    for(int t = 0; t < ts - 1; t++) {
        PSetCoverInput* psci = new PSetCoverInput{sets + t,
            stream->sci->universe, stream->sci->m, stream->sci->n, 0, 0, 0, 0};
        streams[t] = new POfflineStream(psci, t, ts, tblock + t != ts ? stream->sci->m % ts : 0);
    }
    return streams;
}

OnlineStream::OnlineStream(string filename) : Stream() {
    this->mapping = bip::file_mapping(filename.c_str(), bip::read_only);
    this->mapped_rgn = bip::mapped_region(this->mapping, bip::read_only);
    char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
    size_t const mmap_size = mapped_rgn.get_size();
    this->mmistream = new imemstream(mmaped_data, mmap_size);
}

OfflineStream::OfflineStream(string filename) : Stream() {
    this->sci = read_sci(filename);
    this->m = this->sci->m;
}

POfflineStream::POfflineStream(PSetCoverInput* psci, int t, int ts, unsigned long tsize) {
    this->psci = psci;
    this->m = this->psci->m;
    this->ts = ts;
    this->t = t;
    this->position = 0;
    this->tsize = tsize;
}

Set* OfflineStream::get_next_set(){
    if(this->position >= m) return nullptr;
    return this->sci->sets->data() + (this->position++);
}

Set* POfflineStream::get_next_set(){
    cout << "here2.1.1" << endl;
    if(this->position >= this->tsize) return nullptr;
    Set* s = (*this->psci->sets)[this->position++];
    cout << "here2.1.2" << endl;
    return s;
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
    *avg = this->sci->avg;
    *M = this->sci->M;
    *median = this->sci->median;
    *largest = this->sci->largest;
}

void POfflineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M){
    *universe = *this->psci->universe;
    *m = this->psci->m;
    *avg = this->psci->avg;
    *M = this->psci->M;
    *median = this->psci->median;
    *largest = this->psci->largest;
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

void POfflineStream::reset(){
    this->position = 0;
}

void OnlineStream::reset(){
    char const* const mmaped_data = static_cast<char*>(this->mapped_rgn.get_address());
    size_t const mmap_size = this->mapped_rgn.get_size();
    this->mmistream = new imemstream(mmaped_data, mmap_size);
    this->position = 0;
}
