#include "pp_greedy.hpp"

vector<unsigned long>* compose(SSSCInput* sssci, string pp_alg){

    unordered_set<unsigned long>* sol;
    if(pp_alg.compare("Rosen") == 0) sol = sssc(sssci);
    if(pp_alg.compare("LHS") == 0) sol = capture(sssci);
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
    for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
        if(chosen[s->i]) sets->push_back(*s);
    }

    unsigned long proj_m = sol->size();
    SetCoverInput* sci = new SetCoverInput{sets, sssci->universe, proj_m, sssci->n, 0, 0, 0, 0};
    vector<unsigned long>* final_sol = DFG(sci, 1.05);
    return final_sol;
}
