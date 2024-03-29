#ifndef BIGFLOAT_BIGFLOAT_H
#define BIGFLOAT_BIGFLOAT_H

#include <vector>
#include <string>
#include <iostream>

class BigFloat {
    private:
        std::vector<int> digits;
        bool negative;
        int count_digits;
        int order;
        int there_is_a_point_flag;
        inline static int precision;
        void delete_extra_zeros();
        inline int frac_len() const;
        BigFloat left_shift(int digs) const;
        BigFloat right_shift(int digs) const;
        BigFloat div_by_2()const;
        BigFloat mult(const BigFloat& other, const BigFloat& Eps)const;


    public:
        BigFloat();
        explicit BigFloat(int number);
        explicit BigFloat(std::string s);

        static void set_precision(int n);

        BigFloat abs() const;

        bool operator< (const BigFloat& other) const;
        bool operator> (const BigFloat& other) const;
        bool operator<= (const BigFloat& other) const;
        bool operator>= (const BigFloat& other) const;
        bool operator== (const BigFloat& other) const;
        bool operator!= (const BigFloat& other) const;

        BigFloat operator-() const;
        BigFloat& operator= (const BigFloat& other);
        BigFloat& operator+= (const BigFloat& other);
        BigFloat& operator-= (const BigFloat& other);
        BigFloat& operator*= (const BigFloat& other);
        BigFloat& operator/= (const BigFloat& other);
        BigFloat operator+(const BigFloat& other) const;
        BigFloat operator-(const BigFloat& other) const;
        BigFloat operator*(const BigFloat& other) const;
        BigFloat operator/(const BigFloat& other) const;
        std::string to_string() const;
};
BigFloat operator ""_bf(const char* s);

std::ostream &operator<<(std::ostream &os, const BigFloat &num);
std::istream &operator>>(std::istream &is, BigFloat &num);

#endif //BIGFLOAT_BIGFLOAT_H
