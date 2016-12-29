#include "list.h"
#include <iostream>

int main()
{
    eda::list<int> l = { 10, 11, 12 };
    /*for ( int i = 0 ; i < 10; ++i) {
        l.push_back(i);
    }*/
    for (auto it : l ) {
        std::cout << it << std::endl;
    }
    return 0;
}
