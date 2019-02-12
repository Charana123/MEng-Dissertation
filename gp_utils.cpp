#include "gp_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;

bool operator==(const Set& a1, const Set& a2)
{
    if(a1.vertices == a2.vertices && a1.i == a2.i) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& o, const Set& s){
    o << "{ k:" << s.i << "," << s.vertices << " }";
    return o;
}

vector<string> read_file(string filename)
{
    /* auto f = map_file("one.txt", length); */
    bip::file_mapping mapping(filename.c_str(), bip::read_only);
    bip::mapped_region mapped_rgn(mapping, bip::read_only);
	char const* const mmaped_data = static_cast<char*>(mapped_rgn.get_address());
	size_t const mmap_size = mapped_rgn.get_size();

	imemstream mmistream(mmaped_data, mmap_size);
	vector<string> lines;
	for(string line; getline(mmistream, line);){
		lines.push_back(line);
	}
	return lines;
}

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
