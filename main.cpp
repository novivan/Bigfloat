#include <iostream>

#include "BigFloat.cpp"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;

    BigFloat a, b;
    a.read();
    b.read();

    a.write();
    b.write();

    BigFloat sum = a + b;
    sum.write();


    return 0;
}
