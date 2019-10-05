#include "lib.h"

#include <iostream>

int
main()
{
    std::cout << "build " << lib::version() << std::endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
