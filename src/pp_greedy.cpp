#include "pp_greedy.hpp"

vector<unsigned long>* compose(SSSCInput* sssci, string pp_alg, string type){

    unordered_set<unsigned long>* sol;
    if(pp_alg.compare("Rosen") == 0) sol = sssc(sssci, type);
    if(pp_alg.compare("LSH") == 0) sol = capture(sssci);
    vector<bool> chosen(sssci->m, 0);
    for(unsigned long sid: *sol) chosen[sid] = true;
    /* vector<Set>* sets = stream->sci->sets; */
    /* sets->erase( */
    /*     std::remove_if(sets->begin(), sets->end(), [&chosen](Set& s) -> bool{ */
    /*         return chosen[s.i] == 0; */
    /*     }), */
    /*     sets->end() */
    /* ); */
    vector<Set>* sets = new vector<Set>();
    unsigned long M_prog = 0;
    for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
        if(chosen[s->i]) {
            M_prog += s->vertices.size();
            sets->push_back(*s);
        }
    }
    cout << "M_prog: " << M_prog << endl;
    sssci->stream->reset();

    unsigned long proj_m = sol->size();
    SetCoverInput* sci = new SetCoverInput{sets, sssci->universe, proj_m, sssci->n, 0, 0, 0};
    vector<unsigned long>* final_sol = DFG(sci, 1.05);
    return final_sol;
}
