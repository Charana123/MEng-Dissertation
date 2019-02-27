#include "iter_set_cover.hpp"

//rho is the approximation factor of the offline algorithm
/* #include "DFG.hpp" */
/* float p = 1.05; */
/* set<int>* offline(SetCoverInput* sci){ */
/*     map<int, vector<Set*>>* ktoCollection = OrderBySubCollection(sci, p); */
/*     SetCoverOutput* sco = greedy(ktoCollection, p); */
/*     return sco->Sigma; */
/* } */

#include "greedy.hpp"
float p = 1;
set<int>* offline(SetCoverInput* sci){
    SetCoverOutput* sco = greedy(sci);
    return sco->Sigma;
}

set<int>* iter_set_cover(IterSetCoverInput* isci){
    assert(isci->accuracy_delta <= 1);
    assert(isci->c >= 1);
    int log_n = log2f(isci->n);

    // Run in parallel invocations of the algorithm for k \in {1...log n}
    vector<set<int>*> sols;
    /* #pragma omp parallel for */
    for(int i = 0; i <= log_n; i++){
        // sol <- \emptyset
        set<int>* sol = new set<int>();
        // compute sample_size = cpk.n^delta.logn.logm
        int k = pow(2, i);
        float rho = (p * logf(isci->n));
        int sample_size = isci->c * rho * k * powf(isci->n, isci->accuracy_delta) * logf(isci->n) * logf(isci->m);
        unsigned long threshold = sample_size / k;
        // 1/delta
        int repeat = 1/isci->accuracy_delta;
        // Copy universe each guess of the value k ~ OPT
        set<int> universe;
        universe.insert(isci->universe->begin(), isci->universe->end());

        // Iteratively element sample - 1/delta times
        for(int j = 1; j <= repeat && universe.size() > 0; j++){
            set<int, greater<int>> soli;
            set<int> S;
            sample(universe.begin(), universe.end(),
                    std::inserter(S, S.begin()), sample_size,
                    std::mt19937{std::random_device{}()});
            map<int,bool> L; vector<Set*> F_S;
            for(int v : S) L[v] = true; //uncovered elements
            for(Set* r; (r = isci->stream->get_next_set()) != nullptr; ){
                Set* diff = new Set{{}, r->i};
                for(int v : r->vertices) if(L[v]) diff->vertices.insert(v);
                if(diff->vertices.size() >= threshold){
                    soli.insert(r->i);
                    for(int v : diff->vertices) L[v] = false; //update uncovered
                }
                else F_S.push_back(diff);
            }
            isci->stream->reset();
            // remaining uncovered elements after element sampling
            set<int> U_S;
            for(auto& e : L) if(e.second) U_S.insert(e.first);
            // compute offline
            SetCoverInput* sci = new SetCoverInput{&F_S ,&U_S};
            set<int>* partial_sol = offline(sci);
            // include partial solution into final solution, remove
            soli.insert(partial_sol->begin(), partial_sol->end());
            sol->insert(soli.begin(), soli.end());
            vector<int> soli_tmp(soli.begin(), soli.end());
            for(Set* s; (s = isci->stream->get_next_set()) != nullptr; ){
                if(s->i == soli_tmp.back()) {
                    soli_tmp.pop_back();
                    for(int v : s->vertices) universe.erase(v);
                }
            }
            isci->stream->reset();
        }
        sols.push_back(sol);
    }
    set<int>* best_sol;
    unsigned long best_sol_size = 0;
    for(set<int>* sol : sols) {
        if(sol->size() > best_sol_size) {
            best_sol_size = sol->size();
            best_sol = sol;
        }
    }
    return best_sol;
}










