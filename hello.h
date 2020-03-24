#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <deque>

using namespace std;

using Buffer = deque<string>;

ostream& operator<<(ostream& out, const deque<string>& b);

struct Bar {
    explicit Bar(Buffer& b)
            : b_(b)
    {}
    Buffer& b_;
    void print() {
        cout << b_ << endl;
    }
};