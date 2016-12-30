#include "list.h"
#include <iostream>

int main()
{
    eda::list<int> zrlam;
    zrlam.push_back(1);
    zrlam.push_back(2);
    //std::cout << zrlam.size() << std::endl;
    eda::list<int> l = { 10, 11, 11, 11, 12, 12, 14, 12, 12 };
    /*for ( int i = 0 ; i < 10; ++i) {
        l.push_back(i);
    }*/
    for (auto it : l ) {
        std::cout << it << std::endl;
    }
    std::cout << "unique" << std::endl;
    l.unique();
    for (auto it : l ) {
        std::cout << it << std::endl;
    }
    l.remove(10);
    std::cout << "unique" << std::endl;
    for (auto it : l ) {
        std::cout << it << std::endl;
    }

    return 0;
}
