#pragma once

#include "hello.h"

class Foo {
public:
    Foo()
            : bar(make_unique<Bar>(b_))
    {}
    Buffer& getBuffer() {return b_;}
    void print() {
        cout << "Foo has " << b_ << " and bar has ";
        bar->print();
    }
private:
    Buffer b_;
    unique_ptr<Bar> bar;
};