#include "mp-assadi.hpp"
using namespace std;

vector<unsigned long>* SimpleSetCover(SSSCInput* sssci, vector<unsigned long>* sampled_universe, unsigned long max_elem){
    vector<bool> sample_covered(max_elem+1, false);
    for(unsigned long v : *sampled_universe) sample_covered[v] = true;
    //Project set-system to sampled universe
    vector<Set>* reduced_sets = new vector<Set>();
    Set* s;
    for(size_t i = 0; (s = sssci->stream->get_next_set()) != nullptr; i++){
        reduced_sets->push_back(Set{{}, s->i});
        for(unsigned long v : s->vertices) if(sample_covered[v]) (*reduced_sets)[i].vertices.push_back(v);
    }
    sssci->stream->reset();
    //Compute reduced offline set-covering
	SetCoverInput sci = SetCoverInput{reduced_sets, sampled_universe, sssci->m, sampled_universe->size(), 0, 0, 0};
    vector<unsigned long>* sol = greedy(&sci);
    cout << "sol.size(): " << sol->size() << endl;
    delete reduced_sets;
    return sol;
}

vector<unsigned long>* Algorithm1(SSSCInput* sssci, unsigned long alpha, float epsilon, float opt_tilda, unsigned long max_elem){
    unsigned long pruning_threshold = sssci->n/(epsilon * opt_tilda);
    vector<unsigned long>* sol = new vector<unsigned long>();

    unsigned long covered_n = 0;
    vector<bool> covered(max_elem+1, false);
    //Thresholded set sampling
    for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
        if(s->vertices.size() >= pruning_threshold){
            sol->push_back(s->i);
            for(unsigned long v : s->vertices) if(!covered[v]) {
                covered[v] = true;
                covered_n++;
            }
        }
    }
    sssci->stream->reset();
    cout << "n: " << sssci->n << endl;
    cout << "covered after pruning: " << covered_n << endl;

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<float> distribution(0.0,1.0);
    float element_sampling_prob = 16 * opt_tilda * log2f(sssci->m) * powf(sssci->n, 1.0/alpha - 1.0);
    if(element_sampling_prob >= 1.0) return nullptr;
    cout << "element_sampling_prob: " << element_sampling_prob << endl;
    //Iterative element sampling
    vector<unsigned long> sampled_universe;
    for(unsigned long j = 0; j < alpha && covered_n < sssci->n; j++){

        //3)a) randomly sample with probability p
        sampled_universe.clear();
        if(j == alpha-1){
            sample(sssci->universe->begin(), sssci->universe->end(),
                std::inserter(sampled_universe, sampled_universe.begin()), (size_t)(sssci->n * element_sampling_prob), gen);
        }
        else{
            for(unsigned long v : *sssci->universe) {
                if(!covered[v]){
                    if(distribution(gen) < element_sampling_prob) sampled_universe.push_back(v);
                }
            }
        }
        cout << "sampled_universe.size(): " << sampled_universe.size() << endl;

        //3)b) Store the projection over the set system, compute a partial cover
        vector<unsigned long>* sampled_sol = SimpleSetCover(sssci, &sampled_universe, max_elem);
        sol->insert(sol->end(), sampled_sol->begin(), sampled_sol->end());

        //3)c) Remove newly covered elements
        sort(sampled_sol->begin(), sampled_sol->end(), std::less<unsigned long>());
        unsigned long i = 0;
        for(Set* s; (s = sssci->stream->get_next_set()) != nullptr; ){
            unsigned long si = (*sampled_sol)[i];
            if(s->i == si){
                for(unsigned long v : s->vertices) {
                    if(!covered[v]){
                        covered[v] = true;
                        covered_n++;
                    }
                }
                i++;
            }
        }
        cout << "covered_n: " << covered_n << endl;
        delete sampled_sol;
        sssci->stream->reset();
    }

    if(covered_n < sssci->n) return nullptr;
    return sol;
}

vector<unsigned long>* assadiMP(SSSCInput* sssci, unsigned long alpha, float epsilon){
    /* unsigned long alpha, float epsilon, float opt_tilda, unsigned long max_elem) */
    /* cout << "n: " << sssci->n << endl; */
    /* cout << "m: " << sssci->m << endl; */

    unsigned long guesses = log2f(sssci->n)/epsilon;
    size_t max_elem = *std::max_element(sssci->universe->begin(), sssci->universe->end());
    /* cout << "guesses: " << guesses << endl; */
    vector<unsigned long>* best_sol = nullptr;
    unsigned long best_sol_size = std::numeric_limits<unsigned long>::max();;
    unsigned long best_opt_tilda = 0;
    for(unsigned long i = 1; i <= guesses; i++){
        cout << endl;
        cout << "iteration: " << i << endl;
        unsigned long opt_tilda = powf(2, i * epsilon);
        vector<unsigned long>* sol = Algorithm1(sssci, alpha, epsilon, opt_tilda, max_elem);
        if(sol == nullptr) {
            cout << "INVALID" << endl;
            continue;
        } else {
            cout << "final_sol.size(): " << sol->size() << endl;
        }
        if (sol->size() < best_sol_size) {
            best_sol = sol;
            best_sol_size = sol->size();
            best_opt_tilda = opt_tilda;
        }
    }
    return best_sol;
}






