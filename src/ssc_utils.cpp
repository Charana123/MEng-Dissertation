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
            stream->sci->universe, stream->sci->m, stream->sci->n, 0, 0, 0};
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
    if(this->position >= this->tsize) return nullptr;
    Set* s = (*this->psci->sets)[this->position++];
    return s;
}

Set* OnlineStream::get_next_set(){

    delete this->last_set;
	string line;
    if(!getline(*this->mmistream, line)) {
        this->last_set = nullptr;
        return nullptr;
    }

    Set* s = new Set{{}, position++};
    char* cline = new char[line.size() + 1];
    strcpy(cline, line.c_str());
    char* cs = std::strtok(cline, " \t");
    /* s->vertices.push_back(stoul(cs)); */
    for(; (cs = std::strtok(NULL, " \t")) != NULL; ){
        s->vertices.push_back(stoul(cs));
    }
    this->last_set = s;
    return s;
}

void OfflineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M){
    *universe = *this->sci->universe;
    *m = this->sci->m;
    *avg = this->sci->avg;
    *M = this->sci->M;
    *largest = this->sci->largest;
}

void POfflineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M){
    *universe = *this->psci->universe;
    *m = this->psci->m;
    *avg = this->psci->avg;
    *M = this->psci->M;
    *largest = this->psci->largest;
}

void OnlineStream::get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M){
    *m = 0; *M = 0; *largest = 0;
    unsigned long maxx = 0;
    for(Set* s; (s = get_next_set()) != nullptr; (*m)++){
        *M += s->vertices.size();
        if(s->vertices.size() > *largest) *largest = s->vertices.size();
        unsigned long c_maxx = *std::max_element(s->vertices.begin(), s->vertices.end());
        if(c_maxx > maxx) maxx = c_maxx;
    }
    *avg = *M/(*m);
    reset();

    bool* covered = new bool[maxx+1];
    for(Set* s; (s = get_next_set()) != nullptr; ){
        for(unsigned long v : s->vertices) covered[v] = 1;
    }
    for(unsigned long i = 0; i < maxx+1; i++) if(covered[i] == 1) universe->push_back(i);
    delete[] covered;
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
