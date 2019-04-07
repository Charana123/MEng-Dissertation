#include "../src/gp_utils.hpp"
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstdio>

using namespace std;
namespace bip = boost::interprocess;

void process_mem_usage(double* vm_usage, double* resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   *vm_usage     = 0.0;
   *resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   *vm_usage     = vsize / 1024.0;
   *resident_set = rss * page_size_kb;
}

int filesize(const char* filename)
{
    std::ifstream in(filename, std::ios::ate | std::ios::binary);
    return static_cast<int>(in.tellg());
}

void parse_line(string line){
    boost::trim(line);

    // boost tokenizer
    /* boost::tokenizer<> tok(line); */
    /* vector<string> ts; */
    /* for(auto& t : tok) { */
    /*     ts.push_back(t); */
    /* } */

    // strtok tokenizer
    char* cline = new char[line.size() + 1];
    strcpy(cline, line.c_str());
    char *t = std::strtok(cline, " ");
    vector<char*> ts;
    while (t != NULL) {
        ts.push_back(t);
        t = std::strtok(NULL, " ");
    }
    delete[] cline;
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

int main(int argc, char** argv){
    string file_path = string(argv[1]);

    /* time("ifstream", []() -> void{ */
    /*     std::ifstream ifs(file_path); */
    /*     for(string line; getline(ifs, line); ){ */
    /*         parse_line(line); */
    /*     } */
    /* }); */

    time("boost::mmap entire", [&]() -> void{
        bip::file_mapping mapping(file_path.c_str(), bip::read_only);
        bip::mapped_region mapped_rgn(mapping, bip::read_only);
        char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
        size_t const mmap_size = mapped_rgn.get_size();

        imemstream mmifs(mmaped_data, mmap_size);
        for(string line; getline(mmifs, line); ){
            parse_line(line);
        }
    });

    /* time("boost::mmap paging", []() -> void{ */
    /*     bip::file_mapping mapping(file_path.c_str(), bip::read_only); */
    /*     int file_size = filesize(file_path.c_str()); */
    /*     int page_size = bip::mapped_region::get_page_size(); */
    /*     int pages = file_size / page_size; */
    /*     int remain = file_size % page_size; */

    /*     int lines = 0; */
    /*     for(int page = 0; page < pages; page++){ */
    /*         bip::mapped_region mapped_rgn(mapping, bip::read_only, page * page_size, page_size); */
    /*         char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address()); */
    /*         size_t const mmap_size = mapped_rgn.get_size(); */

    /*         imemstream mmifs(mmaped_data, mmap_size); */
    /*         for(string line; getline(mmifs, line); ){ */
    /*             lines++; */
    /*         } */
    /*     } */
    /*     cout << lines << endl; */
    /* }); */

    /* time("cstyle fgets", []() -> void{ */
    /*     FILE * pFile; */
    /*     size_t buffer_size = 1024*16; */
    /*     char line [buffer_size]; */
    /*     pFile = fopen(file_path.c_str() , "r"); */
    /*     int lines = 0; */
    /*     double vm_usage, resident_set; */
    /*     for(; fgets (line, buffer_size, pFile) != NULL; ){ */
    /*         lines++; */
    /*     } */
    /*     cout << lines << endl; */
    /*     fclose (pFile); */
    /* }); */

    /* time("cstyle fread", []() -> void{ */
    /*     FILE* pFile = fopen(file_path.c_str() , "r"); */
    /*     size_t buffer_size = 1024; */
    /*     size_t read_bytes = buffer_size; */
    /*     char* c_buffer = new char[buffer_size]; */
    /*     size_t c_buffer_offset = 0; */
    /*     char* c_line = new char[buffer_size]; */
    /*     int lines = 0; */
    /*     for(int bytes_read = 0; (bytes_read = fread(c_buffer + c_buffer_offset, 1, read_bytes, pFile)) != NULL; ){ */
    /*         char* c_newline = strchr(c_buffer, '\n'); */
    /*         if(c_newline == NULL){ */
    /*             c_buffer = (char*) realloc(c_buffer, buffer_size * 2); */
    /*             c_line = (char*) realloc(c_line, buffer_size * 2); */
    /*             c_buffer_offset = buffer_size; */
    /*             read_bytes = buffer_size * 2 - buffer_size; */
    /*             buffer_size *= 2; */
    /*         } */
    /*         else{ */
    /*             char *cn = c_buffer; */
    /*             char *nn; */
    /*             for(; (nn = (char*) memchr(cn, '\n', (c_buffer + bytes_read) - cn)) != NULL; cn = nn + 1){ */
    /*                 lines++; */
    /*                 /1* cout << bytes_read << endl; *1/ */
    /*                 /1* cout << "memchr" << endl; *1/ */
    /*                 /1* string line(cn, nn - cn); *1/ */
    /*                 /1* parse_line(line); *1/ */
    /*             } */
    /*             memcpy(c_buffer, cn, (c_buffer + bytes_read) - cn); */
    /*             c_buffer_offset = (c_buffer + bytes_read) - cn; */
    /*         } */
    /*     } */
    /*     cout << "lines: " << lines << endl; */
    /*     fclose (pFile); */
    /* }); */
}














