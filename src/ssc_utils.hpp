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
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M, float* var) = 0;
        virtual void reset() = 0;
};

class OnlineStream : public Stream {
    public:
        OnlineStream(string filename);
        virtual Set* get_next_set() override;
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M, float* var) override;
        virtual void reset() override;
    private:
        bip::file_mapping mapping;
        bip::mapped_region mapped_rgn;
        imemstream* mmistream;
        Set* last_set = nullptr;
        unsigned long position = 0;
};

class OfflineStream : public Stream {
    public:
        OfflineStream(string filename);
        virtual Set* get_next_set() override;
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M, float* var) override;
        virtual void reset() override;
        SetCoverInput* sci;
    private:
        unsigned long position = 0;
        unsigned long m;
};

class POfflineStream : public Stream {
    // override the constructor and next set methods
    public:
        POfflineStream(PSetCoverInput* psci, int t, int ts, unsigned long tsize);
        virtual Set* get_next_set() override;
        virtual void get_universe(vector<unsigned long>* universe, unsigned long* m, unsigned long* avg, unsigned long* largest, unsigned long* M, float* var) override;
        virtual void reset() override;
        PSetCoverInput* psci;
    private:
        int t, ts;
        unsigned long position, tsize;
        unsigned long m;
};

POfflineStream** get_streams(string filename, int ts);

#endif








