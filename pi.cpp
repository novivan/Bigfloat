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


    /*
    std::cout << "Enter a precision (amount of digits after '.') for pi" << std::endl;
    int n;
    std::cin >> n;

    BigFloat pi = BigFloat(0);

    //pi.set_precision(n);

    BigFloat bf_1 = BigFloat(1);
    BigFloat bf_2 = bf_1 + bf_1;
    BigFloat bf_4 = bf_2 * bf_2;
    BigFloat bf_8 = bf_4 * bf_2;
    BigFloat bf_6 = bf_8 - bf_2;
    BigFloat bf_5 = bf_6 - bf_1;

    BigFloat common_denom = bf_1;
    BigFloat base = bf_4 * bf_4;

    for (int k = 0; k <= n + 3; k++) {
        pi += bf_1 / common_denom * (
                (bf_4 / (bf_8 * BigFloat(k) + bf_1))
                - (bf_2 / (bf_8 * BigFloat(k) + bf_4))
                - (bf_1 / (bf_8 * BigFloat(k) + bf_5))
                - (bf_1 / (bf_8 * BigFloat(k) + bf_6))
                );

        common_denom *= base;
    }



    pi.write();

    */





    return 0;
}
