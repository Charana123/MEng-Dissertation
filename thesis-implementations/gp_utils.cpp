#include "gp_utils.hpp"

bool operator==(const Set& a1, const Set& a2)
{
    if(a1.vertices == a2.vertices && a1.i == a2.i) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& o, const Set& s){
    o << "{ k:" << s.i << "," << s.vertices << " }";
    return o;
}

