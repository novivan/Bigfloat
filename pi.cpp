#include <iostream>
#include <chrono>

#include "BigFloat.h"

int main() {

    try {

        std::cout << "Hello, BigFloat!" << std::endl;


        /*
        std::cout << "Enter a precision (amount of digits after '.') for pi" << std::endl;
        int n;
        std::cin >> n;


        auto begin_time = std::chrono::high_resolution_clock::now();

        BigFloat pi = BigFloat(0);
        pi.set_precision(n);

        BigFloat bf_1 = BigFloat(1);
        BigFloat bf_2 = bf_1 + bf_1;
        BigFloat bf_4 = bf_2 * bf_2;
        BigFloat bf_8 = bf_4 * bf_2;
        BigFloat bf_6 = bf_8 - bf_2;
        BigFloat bf_5 = bf_6 - bf_1;

        BigFloat common_denom = bf_1;
        BigFloat base = bf_4 * bf_4;

        for (int k = 0; k <= n; k++) {
            pi += bf_1 / common_denom * (
                    (bf_4 / (bf_8 * BigFloat(k) + bf_1))
                    - (bf_2 / (bf_8 * BigFloat(k) + bf_4))
                    - (bf_1 / (bf_8 * BigFloat(k) + bf_5))
                    - (bf_1 / (bf_8 * BigFloat(k) + bf_6))
            );

            common_denom *= base;
        }


        pi.write();
        std::cout << "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196" <<'\n';

        auto end_time = std::chrono::high_resolution_clock::now();
        auto amount_of_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        std::cout << amount_of_time.count() << "ms" << std::endl;
        */



        int amount;
        std::cin >> amount;
        for (int i = 0; i < amount; i++) {
            BigFloat a, b;
            a.set_precision(100);
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

    }
    catch(const char* err_message) {
        std::cout << err_message << std::endl;
    }


    return 0;
}
