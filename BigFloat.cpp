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

BigFloat BigFloat::abs() const {
    BigFloat ret = *this;
    ret.negative = false;
    return ret;
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

int BigFloat::frac_len() const {
    return count_digits - order;
}

bool BigFloat::operator< (const BigFloat& other) const {
    //TODO: correct "orders/count_digits" mistake
    if (negative != other.negative) {
        return negative;
    }
    if (negative) {
        int max_ord = std::max(order, other.order);
        int max_frac_len = std::max(frac_len(), other.frac_len());
        int extended_size = max_ord + max_frac_len;
        for (int i = 0; i < extended_size; i++) {
            int self_digit;
            int other_digit;
            if (i >= max_ord - order && i - max_ord < frac_len()) {
                self_digit = digits[i - max_ord + order];
            } else self_digit = 0;
            if (i >= max_ord - other.order && i - max_ord < other.frac_len()) {
                other_digit = other.digits[i - max_ord + other.order];
            } else other_digit = 0;
            if (self_digit != other_digit) {
                return self_digit > other_digit;
            }
        }
        return false;
    } else { // positive
        int max_ord = std::max(order, other.order);
        int max_frac_len = std::max(frac_len(), other.frac_len());
        int extended_size = max_ord + max_frac_len;
        for (int i = 0; i < extended_size; i++) {
            int self_digit;
            int other_digit;
            if (i >= max_ord - order && i - max_ord < frac_len()) {
                self_digit = digits[i - max_ord + order];
            } else self_digit = 0;
            if (i >= max_ord - other.order && i - max_ord < other.frac_len()) {
                other_digit = other.digits[i - max_ord + other.order];
            } else other_digit = 0;
            if (self_digit != other_digit) {
                return self_digit < other_digit;
            }
        }
        return false;
    }
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
    digits = std::vector <int> (count_digits, 0);
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


BigFloat BigFloat::operator+(const BigFloat& other) const{
    // Return the result as a new `BigFloat` object
    // !!!! TODO: correct "leading zeros" mistake
    BigFloat result;
    if (negative == other.negative) {
        result.negative = negative;
        result.order = std::max(order, other.order) + 1;
        result.there_is_a_point_flag = std::min(1, there_is_a_point_flag + other.there_is_a_point_flag);
        int res_fraction_len = std::max(frac_len(), other.frac_len());
        result.count_digits = result.order + res_fraction_len;
        result.digits = std::vector <int> (result.count_digits, 0);

        int plus_from_prev = 0;
        for (int i = 0; i < result.count_digits; i++) {
            int this_cur_digit, other_cur_digit;

            if (i < res_fraction_len){ // we are still in fraction

                this_cur_digit = (res_fraction_len - 1 - i < frac_len()) ? digits[order + res_fraction_len - 1 - i] : 0;
                other_cur_digit = (res_fraction_len - 1 - i < other.frac_len()) ? other.digits[other.order + res_fraction_len - 1 - i] : 0;
            } else { // we're already in integer part

                this_cur_digit =  (order - 1 - (i - res_fraction_len) >= 0)? digits[order - 1 - (i - res_fraction_len)] : 0;
                other_cur_digit =  (other.order - 1 - (i - res_fraction_len) >= 0)? other.digits[other.order - 1 - (i - res_fraction_len)] : 0;
            }
            int new_cur_digit = this_cur_digit + other_cur_digit + plus_from_prev;

            result.digits[result.count_digits - 1 - i] = new_cur_digit % 10;
            plus_from_prev = new_cur_digit / 10;
        }

        return result;

    } else {
        BigFloat a = this->abs(), b = other.abs();
        BigFloat result;
        if (a > b) { // just subtract absolute meanings
            result = *this;
            if (result.frac_len() < other.frac_len()) {
                int diff = other.frac_len() - result.frac_len();
                result.count_digits += diff;
                result.digits.resize(result.count_digits);
            }
            int minus_from_prev = 0; // always >= 0
            for (int i = 0; i < result.count_digits; i++) {
                int cur_res_digit = result.digits[result.count_digits - 1 - i];
                int cur_other_digit = i < other.count_digits ? other.digits[other.count_digits - 1 - i] : 0;
                int ans_digit = cur_res_digit - cur_other_digit - minus_from_prev;
                minus_from_prev = 0;
                while (ans_digit < 0) {
                    ans_digit += 10;
                    minus_from_prev += 1;
                }
                result.digits[result.count_digits - 1 - i] = ans_digit;
            }
        } else {
            result = other + *this;
        }
        // IN DEVELOPMENT
        return result;
    }

}



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


