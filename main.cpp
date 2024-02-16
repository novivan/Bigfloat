#include <iostream>

#include "BigFloat.h"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;


    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        BigFloat a, b;
        a.read();
        b.read();
        std::cout << "a = ";
        a.write();
        std::cout << "b = ";
        b.write();

        std::cout << "-a = ";
        (-a).write();

        BigFloat sum = a + b;
        std::cout << "a + b = ";
        sum.write();

        BigFloat mult = a * b;
        std::cout << "a * b = ";
        mult.write();


        BigFloat diff_ab = a - b, diff_ba = b - a;
        std::cout << "a - b = ";
        diff_ab.write();
        std::cout << "b - a = ";
        diff_ba.write();


        a += b;
        std::cout << "a = ";
        a.write();
        a += b;
        std::cout << "a = ";
        a.write();

        a -= b;
        std::cout << "a = ";
        a.write();
        a -= b;
        std::cout << "a = ";
        a.write();
        a -= b;
        std::cout << "a = ";
        a.write();
        a -= b;
        std::cout << "a = ";
        a.write();
    }



    return 0;
}
