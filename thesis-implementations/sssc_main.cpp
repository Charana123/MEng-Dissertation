#include "sssc.hpp"
#include "ec_utils.hpp"
#include <functional>

using namespace std;


int default_b(set<int>& V){ return V.size(); }
int default_c(set<int>& E){ return 1; }

SSSCInput* read_sssc(string filename){
    Stream* stream = new Stream(filename);
	return new SSSCInput{.stream=stream, .universe=stream->get_universe(), .epsilon_cover=1, .b=default_b, .c=default_c};
}





















