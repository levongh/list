#include "list.h"
#include <iostream>

int main()
{
    eda::list<int> l;
    l.push_back(0);
    l.push_back(1);
    for ( int i = 0 ; i < 10; ++i) {
        l.push_back(i);
    }
    for ( auto iter = l.begin(); iter != l.end(); ++iter) {
        std::cout << *iter <<std::endl;
    }
    return 0;
}
