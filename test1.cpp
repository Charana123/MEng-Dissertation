#include <map>
#include <set>

using namespace std;
int main(){
    map<int, int> m;
    set<int> s = {1,2,3};
    for(int v : s){
        m[v] = v;
    }
}
