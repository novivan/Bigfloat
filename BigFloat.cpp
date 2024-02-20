#include "BigFloat.h"


#include <vector>
#include <string>
#include <iostream>




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

BigFloat::BigFloat(std::string s) {
    digits.clear();
    count_digits = 0;
    order = -1;
    there_is_a_point_flag = 0;
    for (char c : s) {
        if (std::isdigit(c)) {
            digits.push_back(c - '0');
            count_digits++;
        } else if (c == '-' && count_digits == 0) {
            negative = true;
        } else if (c == '.' || c == ',') {
            order = count_digits;
            there_is_a_point_flag = 1;
        }
        if (frac_len() >= 2 * precision + 30) break;
    }
    if (order == -1) {
        order = count_digits;
    }
    this->delete_extra_zeros();
}



void BigFloat::set_precision(int n) {
    precision = n;
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
        } else if (c == '.' || c == ',') {
            order = count_digits;
            there_is_a_point_flag = 1;
        }
        if (frac_len() >= 2 * precision + 30) break;
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
    if (there_is_a_point_flag == 1 && precision > 0) {
        std::cout << ".";
    }
    for (int i = order; i < std::min(count_digits, order + precision); i++) {
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

bool BigFloat::operator!= (const BigFloat& other) const {
    return (*this < other) || (*this > other);
}

BigFloat BigFloat::left_shift(int digs) const {
    if (digs < 0) {
        return right_shift(-digs);
    }
    if (digs == 0){
        return *this;
    }
    BigFloat ret = *this;
    ret.order+=digs;
    ret.count_digits+=digs;
    ret.digits.resize(ret.count_digits);
    ret.delete_extra_zeros();
    return ret;
}

BigFloat BigFloat::right_shift(int digs) const {
    if (digs < 0) {
        return left_shift(-digs);
    }
    if (digs == 0){
        return *this;
    }
    BigFloat ret = *this;
    ret.there_is_a_point_flag = 1;
    ret.digits.resize(ret.count_digits + digs);
    ret.count_digits += digs;
    for (int i = ret.count_digits - digs - 1; i >=0; --i) {
        ret.digits[i + digs] = ret.digits[i];
        if (i < digs) ret.digits[i] = 0;
    }

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

BigFloat& BigFloat::operator/= (const BigFloat& other){
    *this = *this / other;
    return *this;
}




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

    if (other.abs() < Eps) {
        //implementing siple multiplication

        BigFloat ret;
        ret.count_digits = count_digits + other.count_digits;
        ret.order = order + other.order;

        ret.count_digits = std::min(ret.count_digits, ret.order + 2 * precision + 30);

        ret.digits.resize(ret.count_digits);
        ret.there_is_a_point_flag = (ret.order < ret.count_digits) ? 1 : 0;
        ret.negative = negative ^ other.negative;

        for (int i = 0; i < count_digits; i++) { //цифра в *this (номер)
            for (int j = 0; j < other.count_digits; j++) { //цифра в other (номер)
                int ret_ind = ret.order - 1 + (i - (order - 1)) + (j - (other.order - 1));

                if (ret_ind >= ret.count_digits) break;

                int mult = digits[i] * other.digits[j];
                mult += ret.digits[ret_ind];
                ret.digits[ret_ind] = mult % 10;


                if (ret_ind > 0) {
                    ret.digits[ret_ind - 1] += mult / 10;
                    ret_ind--;
                    while (ret_ind >= 0) {
                        if (ret.digits[ret_ind] > 9) {
                            if (ret_ind > 0) {
                                ret.digits[ret_ind - 1] += ret.digits[ret_ind]/10;
                            }
                            ret.digits[ret_ind] %= 10;
                            ret_ind--;
                        } else break;
                    }
                }
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
    Eps.digits.resize(10);
    Eps.digits[9] = 1;
    Eps.count_digits = 10;
    Eps.order = 1;
    Eps.there_is_a_point_flag = 1;
    Eps.negative = false;
    return this->mult(other, Eps);
}


BigFloat BigFloat::operator/(const BigFloat& other) const {

    if (other == BigFloat(0)) {
        throw "Divizion by zero error";
    }

    BigFloat res;

    int prec_help = std::max(precision, 5);

    res.digits = std::vector <int> (2 * prec_help + 2);
    res.order = prec_help + 1;
    res.count_digits = 2 * prec_help + 2;
    res.negative = negative ^ other.negative;
    res.there_is_a_point_flag = 1;

    BigFloat rest_from_this = this->abs();
    int cur_shift = prec_help;
    while (cur_shift >= -(prec_help + 1)) {

        BigFloat help_number = other.abs().left_shift(cur_shift);
        while(rest_from_this.abs() >= help_number.abs()) {
            rest_from_this -= help_number;
            res.digits[prec_help - cur_shift]++;
        }
        cur_shift--;
    }
    res.delete_extra_zeros();
    return res;
}

std::string BigFloat::to_string() const{
    std::string ret;
    if (negative) {
        //std::cout << "-";
        ret.push_back('-');
    }

    if (order == 0) {
        ret.push_back('0');
        //std::cout << "0";
    }
    for (int i = 0; i < order; i++) {
        ret.push_back('0' + digits[i]);
        //std::cout << digits[i];
    }
    if (there_is_a_point_flag == 1 && precision > 0) {
        //std::cout << ".";
        ret.push_back('.');
    }
    for (int i = order; i < std::min(count_digits, order + precision); i++) {
        //std::cout << digits[i];
        ret.push_back('0' + digits[i]);
    }

    //std::cout << std::endl;
    return ret;

}

BigFloat operator ""_bf(const char* s) {
    return std::string(s);
}


std::ostream &operator<<(std::ostream &out_stream, const BigFloat &num) {
    out_stream << num.to_string();
    return out_stream;
}

std::istream &operator>>(std::istream &input_stream, BigFloat &num) {
    std::string input;
    input_stream >> input;
    num = BigFloat(input);
    return input_stream;
}



