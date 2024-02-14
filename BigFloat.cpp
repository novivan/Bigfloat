//
// Created by Ivan Novikov on 14.02.2024.
//

#include "BigFloat.h"


#include <iostream>
#include <vector>





BigFloat::BigFloat(){
    digits = std::vector <int> (0);
    negative = false;
    count_digits = 0;
    order = 0;
    there_is_a_point_flag = 0;
}

BigFloat::BigFloat(int number) {
    there_is_a_point_flag = 0;
    count_digits = 1;
    order = 1;
    negative = number < 0 ? 1 : 0;

    int pow_10 = 1, number_copy = std::abs(number);

    while(pow_10 * 10 <= number_copy) {
        pow_10 *= 10;
        order++;
    }
    count_digits = order;
    digits = std::vector <int> (order);
    for (int i = 0; i < order; i++) {
        digits[i] = number_copy / pow_10;
        number_copy %= pow_10;
        pow_10 /= 10;
    }


}

void BigFloat::read() {
    std::string input;
    std::cin >> input;

    // TODO: Parse the input string
    digits.clear();
    count_digits = 0;
    order = -1;
    there_is_a_point_flag = 0;
    for (char c : input) {
        if (std::isdigit(c)) {
            digits.push_back(c - '0');
            count_digits++;
        } else if (c == '-' && count_digits == 0) {
            negative = true;
        } else if (c == '.') {
            order = count_digits;
            there_is_a_point_flag = 1;
        }
    }
    if (order == -1) {
        order = count_digits;
    }
}

void BigFloat::write() const {
    if (negative) {
        std::cout << "-";
    }

    if (order == 0) {
        std::cout << "0";
    }
    for (int i = 0; i < order; i++) {
        std::cout << digits[i];
    }
    if (there_is_a_point_flag == 1) {
        std::cout << ".";
    }

    for (int i = order; i < count_digits; i++) {
        std::cout << digits[i];
    }

    std::cout << std::endl;
}

bool BigFloat::operator< (const BigFloat& other) const {
    if (negative != other.negative) {
        return negative;
    }
    if (negative) {
        if (order > other.order) {
            return true;
        } else if (order < other.order) {
            return false;
        } else {
            for (int i = 0; i < std::max(count_digits, other.count_digits); i++) {
                int first_d = (i < count_digits) ? digits[i] : 0;
                int second_d = (i < other.count_digits) ? other.digits[i] : 0;
                if (first_d < second_d) {
                    return false;
                } else if (first_d > second_d) {
                    return true;
                }
            }

        }
    } else { // negative
        if (order > other.order) {
            return false;
        } else if (order < other.order) {
            return true;
        } else {
            for (int i = 0; i < std::max(count_digits, other.count_digits); i++) {
                int first_d = (i < count_digits) ? digits[i] : 0;
                int second_d = (i < other.count_digits) ? other.digits[i] : 0;
                if (first_d < second_d) {
                    return true;
                } else if (first_d > second_d) {
                    return false;
                }
            }
        }

    }
    return false;
}

bool BigFloat::operator> (const BigFloat& other) const {
    return other < *this;
}

bool BigFloat::operator<= (const BigFloat& other) const {
    return !(*this > other);
}

bool BigFloat::operator>= (const BigFloat& other) const {
    return !(*this < other);
}

bool BigFloat::operator== (const BigFloat& other) const {
    return (*this <= other) && (*this >= other);
}

BigFloat& BigFloat::operator= (const BigFloat& other){
    negative = other.negative;
    count_digits = other.count_digits;
    order = other.order;
    there_is_a_point_flag = other.there_is_a_point_flag;
    for (int i = 0; i < count_digits; i++) {
        digits[i] = other.digits[i];
    }
    return *this;
}
/*
BigFloat& BigFloat::operator+= (const BigFloat& other){

}

BigFloat& BigFloat::operator-= (const BigFloat& other){

}

BigFloat& BigFloat::operator*= (const BigFloat& other){

}

BigFloat& BigFloat::operator/= (const BigFloat& other){

}
*/

/*
BigFloat BigFloat::operator+(const BigFloat& other) const{
    // TODO: Implement addition logic
    // Return the result as a new `BigFloat` object
    BigFloat result;
    if (negative == other.negative) {
        result.negative = negative;
        result.order = std::max(order, other.order) + 1;
        result.there_is_a_point_flag = std::min(1, there_is_a_point_flag + other.there_is_a_point_flag);
        int res_fraction_len = std::max(count_digits - order, other.count_digits - other.order);
        result.count_digits = result.order + res_fraction_len;

        */
        /*int plus_from_prev = 0;
        for (int i = 0; i < result.order; i++) {
            int self_cur_digit = i < order ? digits[order - 1 - i] : 0;
            int other_cur_digit = i < other.order ? other.digits[other.order - 1 - i] : 0;
            int cur_digit = self_cur_digit + other_cur_digit + plus_from_prev;

            result.digits[result.order - 1 - i] = cur_digit % 10;
            plus_from_prev = cur_digit / 10;
        }*/
        /*
        int plus_from_prev = 0;
        for (int i = 0; i < result.order; i++) {

        }

    } else {
        // IN DEVELOPMENT
        return
    }

}
*/


/*
BigFloat BigFloat::operator-(const BigFloat& other) const {
    // TODO: Implement subtraction logic
    // Return the result as a new `BigFloat` object
}

BigFloat BigFloat::operator*(const BigFloat& other) const {
    // TODO: Implement multiplication logic
    // Return the result as a new `BigFloat` object
}

BigFloat BigFloat::operator/(const BigFloat& other) const {
    // TODO: Implement division logic
    // Return the result as a new `BigFloat` object
}
*/


