#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include <atomic>


#include "hello.h"


struct Bar {
    Bar(const std::string& s)
        : s_(s)
    {}

    void print() {
        std::cout << "bar string: " << s_ << std::endl;
    }
    const std::string& s_;
};

struct Foo {
    Foo(std::string s)
        : s_(std::move(s)),
        b(s_)
    {}

    void print() {
        std::cout << "Foo str: " << s_ << std::endl;
        b.print();
    }

    std::string s_;
    Bar b;
};

using namespace std;

struct TestStruct {
    string s;
    int c = 1;
};

ostream& operator<<(ostream& out, const TestStruct& t) {
    out << t.s << " " << t.c << endl;
    return out;
}

using TestHolder = shared_ptr<TestStruct>;


void handle_test(TestHolder t) {
    //this_thread::sleep_for(100ms);
    cout << *t << endl;
}

atomic_int ai = 0;
//int ai = 0;
atomic_bool ab;

int main()
{
//    static int ai = 0;
    constexpr int N = 1000;
    constexpr int TN = 10;
    auto l = [N](){
        for (int i = 0; i < N; ++i) {
            if (ab) {
                ++ai;
            } else {
                ab = true;
            }
        }
    };

    vector<future<void>> futures(TN);
    for (size_t i = 0; i < TN; ++i) {
        futures[i] = async(launch::async, l);
    }
    for (auto& f : futures) {
        f.get();
    }
    cout << "ai = " << ai << " and must be " << N * TN-1 << endl;

    return 0;
}


#include <vector>
#include <random>
#include <set>
#include <cassert>
#include <iostream>
//
//using namespace std;
//
//struct RandomArrayGenerator{
//
//    RandomArrayGenerator()
//        : mt(re())
//    {}
//
//    random_device re;
//    mt19937 mt;
//
//    vector<int> generateRandomArray(size_t size) {
//        vector<int> res(size); // numbers 1..size
//        if (size == 0) return res;
//        uniform_int_distribution<size_t> ut(0, size-1);
//        set<size_t> cache;
//        for (size_t i = 1; i <= size; ++i) {
//            size_t pos = 0;
//            assert(cache.size() < size);
//            while (true) {
//                pos = ut(mt);
//                if (!cache.count(pos)) break;
//            }
//            cache.insert(pos);
//            res[pos] = i;
//        }
//        return res;
//    }
//
//};
//
//int missing_number(const vector<int>& v) {
//    if (v.empty()) return 0;
//    size_t sum = (v.size() * (v.size() + 1)) / 2;
//    for (size_t i = 0; i+1 < v.size(); ++i) {
//        sum -= v[i];
//    }
//    return static_cast<int>(sum);
//}
//
//
//
//int main() {
//    {
//        auto res = RandomArrayGenerator().generateRandomArray(10);
//        for (auto n : res) {
//            cout << n << ", ";
//        }
//        cout << endl;
//        cout << missing_number(res) << endl;
//    }
//
//    return 0;
//}
