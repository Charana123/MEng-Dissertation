#ifndef SSC_UTILS_H_
#define SSC_UTILS_H_

#include "gp_utils.hpp"
#include "sc_utils.hpp"

using namespace boost;
namespace bip = boost::interprocess;

class Stream {
    public:
        Stream(){};
        virtual Set* get_next_set() = 0;
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M) = 0;
        virtual void reset() = 0;
};

class OnlineStream : public Stream {
    public:
        OnlineStream(string filename);
        Set* get_next_set();
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M);
        void reset();
    private:
        bip::file_mapping mapping;
        bip::mapped_region mapped_rgn;
        imemstream* mmistream;
        unsigned long position = 0;
};

class OfflineStream : public Stream {
    public:
        OfflineStream(string filename);
        Set* get_next_set();
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* median, unsigned long* largest, unsigned long* M);
        void reset();
        SetCoverInput* sci;
    private:
        unsigned long position = 0;
        unsigned long m;
};

#endif










