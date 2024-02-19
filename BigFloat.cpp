//
// Created by Ivan Novikov on 14.02.2024.
//

#include "BigFloat.h"


#include <iostream>
#include <vector>
#include <limits.h>






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
    negative = number < 0;

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


BigFloat::~BigFloat() {

}

BigFloat BigFloat::abs() const {
    BigFloat ret = *this;
    ret.negative = false;
    return ret;
}

void BigFloat::read() {
    std::string input;
    std::cin >> input;

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
    this->delete_extra_zeros();
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

void BigFloat::delete_extra_zeros() {
    int begin_del = 0, end_del = 0;
    for (int i = 0; i < order - 1; i++) {
        if (digits[i] == 0) begin_del++;
        else break;
    }
    for (int i = 0; i < frac_len(); i++) {
        if (digits[count_digits - 1 - i] == 0) end_del++;
        else break;
    }
    if ((begin_del + end_del) > 0) {
        for (int i = 0; i < count_digits - (begin_del + end_del); i++) {
            digits[i] = digits[i + begin_del];
        }
        digits.resize(count_digits - (begin_del + end_del));
    }
    count_digits -= (begin_del + end_del);
    order -= begin_del;
    there_is_a_point_flag = (order == count_digits) ? 0 : 1;
    return;
}

int BigFloat::frac_len() const {
    return count_digits - order;
}

bool BigFloat::operator< (const BigFloat& other) const {
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

BigFloat BigFloat::left_shift() const {
    BigFloat ret = *this;
    if (ret.frac_len() == 1) {
        ret.there_is_a_point_flag = 0;
    }
    ret.order++;
    ret.count_digits++;
    ret.digits.resize(count_digits);
    ret.delete_extra_zeros();
    return ret;
}

BigFloat BigFloat::right_shift() const {
    BigFloat ret = *this;
    ret.there_is_a_point_flag = 1;
    ret.digits.resize(ret.count_digits + 1);
    ret.count_digits++;
    for (int i = ret.count_digits - 2; i >=0; --i) {
        ret.digits[i + 1] = ret.digits[i];
    }
    ret.digits[0] = 0;
    ret.delete_extra_zeros();
    return ret;
}


BigFloat BigFloat::operator-() const {
    BigFloat ret = *this;
    ret.negative = !ret.negative;
    return ret;
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
    this->delete_extra_zeros();
    return *this;
}

BigFloat& BigFloat::operator+= (const BigFloat& other){
    if (negative == other.negative) {
        //result parametres
        int max_ord = std::max(order, other.order) + 1;
        int max_frac_len = std::max(frac_len(), other.frac_len());
        int new_size = max_ord + max_frac_len;
        int left_displacement = max_ord - order;

        //resizing
        if (new_size > count_digits) {
            digits.resize(new_size);
            if (left_displacement > 0) {
                std::vector <int> help_new_vector (new_size, 0);
                for (int i = 0; i < count_digits; i++) {
                    help_new_vector[left_displacement + i] = digits[i];
                }
                for (int i = 0; i < new_size; i++) digits[i] = help_new_vector[i];
            }
            count_digits = new_size;
            order = max_ord;
            if (order < count_digits) {
                there_is_a_point_flag = 1;
            }
        }

        //executing addition
        int plus_from_prev = 0;
        for (int i = count_digits - 1; i >= 0; --i) {
            int other_digit;
            if (i >= order) { // digit in fraction
                int fraction_index = i - order;
                other_digit = (fraction_index + other.order < other.count_digits) ? other.digits[fraction_index + other.order] : 0;
            } else { // digit in integer part
                int integer_index = order - 1 - i;
                other_digit = (integer_index  < other.order) ? other.digits[other.order - 1 - integer_index] : 0;
            }
            this->digits[i] += other_digit + plus_from_prev;
            plus_from_prev = this->digits[i]/10;
            this->digits[i] %= 10;
        }
        this->delete_extra_zeros();
        return *this;
    } else {
        BigFloat a = this->abs(), b = other.abs();
        BigFloat help;
        if (b > a) {
            help = *this;
            *this = other;
        } else {
            help = other;
        }


        //result parametres
        int max_ord = std::max(order, help.order);
        int max_frac_len = std::max(frac_len(), help.frac_len());
        int new_size = max_ord + max_frac_len;
        int left_displacement = max_ord - order;

        //resizing
        if (new_size > count_digits) {
            digits.resize(new_size);
            if (left_displacement > 0) {
                std::vector <int> help_new_vector (new_size, 0);
                for (int i = 0; i < count_digits; i++) {
                    help_new_vector[left_displacement + i] = digits[i];
                }
                for (int i = 0; i < new_size; i++) digits[i] = help_new_vector[i];
            }
            count_digits = new_size;
            order = max_ord;
            if (order < count_digits) {
                there_is_a_point_flag = 1;
            }
        }

        //executing addition
        int minus_from_prev = 0;
        for (int i = count_digits - 1; i >= 0; --i) {
            int other_digit;
            if (i >= order) { // digit in fraction
                int fraction_index = i - order;
                other_digit = (fraction_index + help.order < help.count_digits) ? help.digits[fraction_index + help.order] : 0;
            } else { // digit in integer part
                int integer_index = order - 1 - i;
                other_digit = (integer_index  < help.order) ? help.digits[help.order - 1 - integer_index] : 0;
            }
            this->digits[i] -= other_digit + minus_from_prev;
            minus_from_prev = 0;
            while(this->digits[i] < 0) {
                this->digits[i] += 10;
                minus_from_prev++;
            }
        }
        this->delete_extra_zeros();
        return *this;

    }

}

BigFloat& BigFloat::operator-= (const BigFloat& other){
    BigFloat help = other;
    help.negative = !help.negative;
    *this += help;
    return *this;
}

BigFloat& BigFloat::operator*= (const BigFloat& other){
    BigFloat result = (*this) * other;
    *this = result;
    return *this;
}
/*
BigFloat& BigFloat::operator/= (const BigFloat& other){

}
*/



BigFloat BigFloat::operator+(const BigFloat& other) const{
    BigFloat ret = *this;
    ret += other;
    return ret;
}

BigFloat BigFloat::operator-(const BigFloat& other) const {
    BigFloat ret = *this;
    ret -= other;
    return ret;
}





BigFloat BigFloat::div_by_2() const {
    int res_from_prev_digit = 0;
    int i = 0;
    BigFloat ans = *this;
    while(i < count_digits) {
        ans.digits[i] += res_from_prev_digit;
        res_from_prev_digit = (ans.digits[i] % 2) * 10;
        ans.digits[i]/=2;
        i++;
    }
    if (res_from_prev_digit > 0) {
        ans.digits.resize(ans.count_digits + 1);
        ans.digits[count_digits] = res_from_prev_digit / 2;
        ans.count_digits++;
        ans.there_is_a_point_flag = (ans.count_digits > ans.order);
    }
    return ans;
}


BigFloat BigFloat::mult(const BigFloat& other, const BigFloat& Eps)const {

    //TODO : MAKE IT FASTER!!!
    if (other.abs() < Eps) {
        //перемножим тупо
        BigFloat ret;
        ret.count_digits = count_digits + other.count_digits;
        ret.order = order + other.order;
        ret.digits.resize(ret.count_digits);
        ret.there_is_a_point_flag = (ret.order < ret.count_digits) ? 1 : 0;
        ret.negative = negative ^ other.negative;

        for (int i = 0; i < count_digits; i++) { //цифра в *this (номер)
            for (int j = 0; j < other.count_digits; j++) { //цифра в other (номер)
                int mult = digits[i] * other.digits[j];
                int ret_ind = ret.order - 1 + (i - (order - 1)) + (j - (other.order - 1));
                mult += ret.digits[ret_ind];
                ret.digits[ret_ind] = mult % 10;
                if (ret_ind > 0) ret.digits[ret_ind - 1] += mult / 10;
            }
        }
        ret.delete_extra_zeros();
        return ret;
    } else {
        BigFloat half_ans = mult(other.div_by_2(), Eps);
        BigFloat ret = half_ans + half_ans;
        ret.delete_extra_zeros();
        return ret;
    }
};



BigFloat BigFloat::operator*(const BigFloat& other) const {
    BigFloat Eps = BigFloat(0);
    Eps.digits.resize(20);
    Eps.digits[19] = 1;
    Eps.count_digits = 20;
    Eps.order = 1;
    Eps.there_is_a_point_flag = 1;
    Eps.negative = false;
    return this->mult(other, Eps);
}

BigFloat BigFloat::operator/(const BigFloat& other) const {
    //TODO : FIND HOW TO THROW 'DIVISION BY 0' ERROR
    //TODO : MAKE IT FASTER

    BigFloat Eps = BigFloat(0);
    Eps.digits.resize(20);
    Eps.digits[19] = 1;
    Eps.count_digits = 20;
    Eps.order = 1;
    Eps.there_is_a_point_flag = 1;
    Eps.negative = false;
    BigFloat l, m, r;
    BigFloat big_number = BigFloat(INT_MAX / 10);


    if (negative == other.negative) {
        l = BigFloat(0);
        r = (*this);
        r.negative = false;
        for (int i = 0; i < 10; i++) r *= big_number;

        if (negative) {
            while(r - l > Eps) {
                m = (r + l).div_by_2();
                if (other * m < (*this)) r = m;
                else l = m;
            }
        } else {
            while(r - l > Eps) {
                m = (r + l).div_by_2();
                if (other * m < (*this)) l = m;
                else r = m;
            }
        }


    }  else {
        return -((*this) / (-other));
    }
    return m;
}



