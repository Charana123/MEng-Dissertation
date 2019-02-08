#include "../utils.hpp"
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstdio>

using namespace std;

int filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<int>(in.tellg());
}

vector<int> parse_line(string line){
    boost::trim(line);
    boost::tokenizer<> tok(line);
    vector<int> s;
    /* transform(tok.begin(), tok.end(), s.begin(), [](string c) -> int{ return stoi(c); }); */
    return s;
}

void time(string name, std::function<void()> func){
    auto t1 = chrono::high_resolution_clock::now();
    func();
    auto t2 = chrono::high_resolution_clock::now();
    cout << "===========" << endl;
    cout << name << endl;
    cout << "===========" << endl;
    cout << "time: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}

string file_path = "../dataset/kosarak.dat";
namespace bip = boost::interprocess;

int main(){

    time("ifstream", []() -> void{
        std::ifstream ifs(file_path);
        for(string line; getline(ifs, line); ){
            /* parse_line(line); */
        }
    });

    time("boost::mmap entire", []() -> void{
        bip::file_mapping mapping(file_path.c_str(), bip::read_only);
        bip::mapped_region mapped_rgn(mapping, bip::read_only);
        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
        size_t const mmap_size = mapped_rgn.get_size();

        imemstream mmifs(mmaped_data, mmap_size);
        for(string line; getline(mmifs, line); ){
            /* parse_line(line); */
        }
    });

    time("boost::mmap paging", []() -> void{
        bip::file_mapping mapping(file_path.c_str(), bip::read_only);
        int file_size = filesize(file_path.c_str());
        int page_size = bip::mapped_region::get_page_size();
        int pages = file_size / page_size;
        int remain = file_size % page_size;

        for(int page = 0; page < pages; page++){
            bip::mapped_region mapped_rgn(mapping, bip::read_only, page * page_size, page_size);
            char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
            size_t const mmap_size = mapped_rgn.get_size();

            imemstream mmifs(mmaped_data, mmap_size);
            for(string line; getline(mmifs, line); ){
                /* parse_line(line); */
            }
        }
    });

    time("cstyle fgets", []() -> void{
        FILE * pFile;
        char line [100];
        pFile = fopen(file_path.c_str() , "r");
        for(; fgets (line, 100, pFile) != NULL; ){
        }
        fclose (pFile);
    });

    time("cstyle fread", []() -> void{
        FILE* pFile = fopen(file_path.c_str() , "r");
        size_t buffer_size = 100;
        size_t read_bytes = buffer_size;
        char* c_buffer = new char[buffer_size];
        char* c_line = new char[buffer_size];
        size_t c_line_offset = 0;
        for(; fread(c_line + c_line_offset, 1, read_bytes, pFile) != NULL; ){
            char* newline = strchr(c_buffer, '\n');
            if(newline == NULL){
                c_buffer = (char*) realloc(c_buffer, buffer_size * 2);
                c_line = (char*) realloc(c_line, buffer_size * 2);
                c_line_offset = buffer_size;
                read_bytes = buffer_size * 2 - buffer_size;
                buffer_size *= 2;
            }
            else{
                size_t offset = newline - c_line;
                memcpy(c_line, c_buffer, offset);
                string line(c_line, offset);
                parse_line(line);
            }
        }
        fclose (pFile);
    });
}














