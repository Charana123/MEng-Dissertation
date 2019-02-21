#include "rssc.hpp"

string filename = "./dataset/chess.dat";
float c = 5;
float accuracy_delta = 0.5;

int main(){
    Stream* stream = new Stream(filename);
    RSSCInput rssc_input = {stream, stream->get_universe(), stream->find_m(), c,accuracy_delta};
    RSSCOutput* rssc_output = rssc(rssc_input);
}
