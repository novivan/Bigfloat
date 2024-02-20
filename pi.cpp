#include <iostream>
#include <chrono>

#include <thread>
#include <mutex>

#include "BigFloat.h"


BigFloat pi = 0_bf;
BigFloat bf_1 = 1_bf;
BigFloat bf_2 = 2_bf;
BigFloat bf_4 = 4_bf;
BigFloat bf_8 = 8_bf;
BigFloat bf_6 = 6_bf;
BigFloat bf_5 = 5_bf;




std::vector <BigFloat> bases;

int threads_amount = 8;


void func(int n_from, int n_to) {
    static std::mutex pi_mutex;
    BigFloat summand = BigFloat(0);

    for (int k = n_from; k <= n_to; k++) {
        BigFloat cur_bf = BigFloat(k);
        summand += bf_1 / bases[k] * (
                (bf_4 / (bf_8 * cur_bf + bf_1))
                - (bf_2 / (bf_8 * cur_bf + bf_4))
                - (bf_1 / (bf_8 * cur_bf + bf_5))
                - (bf_1 / (bf_8 * cur_bf + bf_6))
        );
    }
    pi_mutex.lock();
    pi += summand;
    pi_mutex.unlock();
}

int main() {

    try {

        std::cout << "Hello, BigFloat!" << std::endl;



        std::cout << "Enter a precision (amount of digits after '.') for pi" << std::endl;
        int n;
        std::cin >> n;



        auto begin_time = std::chrono::high_resolution_clock::now();



        pi.set_precision(n);
        int help_n = n;
        n++;
        n = (n + threads_amount - 1) - ((n + threads_amount - 1) % threads_amount); // make n % threads_amount == 0

        bases.resize(std::max(threads_amount, n));
        bases[0] = BigFloat(1);
        bases[1] = BigFloat(16);
        for (int i = 2; i < bases.size(); i++) {
            bases[i] = bases[i - 1] * bases[1];
        }



        std::vector<std::thread> vector_of_threads(threads_amount);
        for (int i = 0; i < vector_of_threads.size(); i++) {
            vector_of_threads[i] = std::thread(func, i*(n/threads_amount), (i+1)*(n/threads_amount) - 1);
        }
        for (auto &i: vector_of_threads) i.join();

        /*for (int k = 0; k <= n; k++) {
            pi += bf_1 / common_denom * (
                    (bf_4 / (bf_8 * BigFloat(k) + bf_1))
                    - (bf_2 / (bf_8 * BigFloat(k) + bf_4))
                    - (bf_1 / (bf_8 * BigFloat(k) + bf_5))
                    - (bf_1 / (bf_8 * BigFloat(k) + bf_6))
            );

            common_denom *= base;
        }*/
        n = help_n;


        pi.write();
        //std::cout << "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196" <<'\n';

        auto end_time = std::chrono::high_resolution_clock::now();
        auto amount_of_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
        std::cout << "time spent on counting pi - "<< amount_of_time.count() << " ms" << std::endl;


    }
    catch(const char* err_message) {
        std::cout << err_message << std::endl;
    }


    return 0;
}
