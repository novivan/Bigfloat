#include <iostream>

#include "BigFloat.h"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;

    BigFloat a, b;
    a.read();
    b.read();

    a.write();
    b.write();




    return 0;
}
