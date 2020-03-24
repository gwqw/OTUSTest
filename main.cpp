#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <deque>
#include <future>
#include <vector>
#include <cassert>

#include "hello.h"
#include "test.h"

using namespace std;

int g = 0;

void inc() {
    ++g;
}


int main() {
    {
    vector<future<void>> futures;
    for (int i = 0; i < 100; ++i) {
        futures.push_back(async(inc));
    }

    }
    cout <<  g << endl;
    assert(g == 100);



//    auto f1 = make_unique<Foo>();
//    auto f2 = make_unique<Foo>();
//    auto& buffer1 = f1->getBuffer();
//    auto& buffer2 = f2->getBuffer();
//    buffer1.emplace_back("test1");
//    buffer2.emplace_back("test2");
//    cout << "1: ";
//    f1->print();
//    cout << "2: ";
//    f2->print();

    return 0;
}
