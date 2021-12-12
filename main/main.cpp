import std.core;
import std.regex;
import util.myvec;
import util.mylist;
import util.mymap;

using namespace std;

int main() {
    mymap<string, unsigned> map_;
    for (int i = 0; i < 500; ++i) {
        map_.insert({ format("he{:03d}", i), 11451 + i });
    }
    myvec<pair<string, unsigned>> vec2;
    for (auto pr : map_) {
        vec2.push_back(pr);
    }
    sort(vec2.begin(), vec2.end());
    for (auto pr : vec2) {
        cout << format("{}-{} ", pr.first, pr.second);
    }
    cout << (map_.find("hello7") == map_.end()) << endl;
    cout << (map_.find("hello8") == map_.end()) << endl;
    cout << map_["he514"] << endl;
}
