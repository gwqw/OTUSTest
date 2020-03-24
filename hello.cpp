#include "hello.h"

ostream& operator<<(ostream& out, const deque<string>& b)
{
    for (const auto& s : b) {
        cout << s << ", ";
    }
    return out;
}

