#include <iostream>

#include "BigFloat.h"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;



    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        BigFloat a, b;
        a.read();
        b.read();

        BigFloat mult = a * b;
        std::cout << "a * b = ";
        mult.write();

        BigFloat div_a_b = a / b;
        std::cout << "a / b = ";
        div_a_b.write();
        BigFloat div_b_a = b / a;
        std::cout << "b / a = ";
        div_b_a.write();
    }



    return 0;
}
