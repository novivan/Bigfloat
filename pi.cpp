#include <iostream>

#include "BigFloat.h"

int main() {
    std::cout << "Hello, BigFloat!" << std::endl;



    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        BigFloat a, b;
        a.read();
        b.read();

        std::cout << "a_left_shift ";
        a.left_shift(3).write();
        std::cout << "a_right_shift ";
        a.right_shift(3).write();
        std::cout << "b_left_shift ";
        b.left_shift(3).write();
        std::cout << "b_right_shift ";
        b.right_shift(3).write();


        std::cout << "sum, diff:" << std::endl;
        BigFloat diff = a - b, sum = a + b;

        sum.write();
        diff.write();

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
