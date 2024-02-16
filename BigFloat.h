//
// Created by Ivan Novikov on 14.02.2024.
//

#ifndef BIGFLOAT_BIGFLOAT_H
#define BIGFLOAT_BIGFLOAT_H

#include <vector>



class BigFloat {
    private:
        std::vector<int> digits;
        bool negative;
        int count_digits;
        int order;
        int there_is_a_point_flag;


    public:
        BigFloat();
        BigFloat(int number);


        ~BigFloat();

        BigFloat abs() const;

        void read();
        void write() const;

        void delete_extra_zeros();

        int frac_len() const;





        bool operator< (const BigFloat& other) const;

        bool operator> (const BigFloat& other) const;

        bool operator<= (const BigFloat& other) const;

        bool operator>= (const BigFloat& other) const;

        bool operator== (const BigFloat& other) const;


        BigFloat operator-() const;


        BigFloat& operator= (const BigFloat& other);

        BigFloat& operator+= (const BigFloat& other);

        BigFloat& operator-= (const BigFloat& other);


        BigFloat& operator*= (const BigFloat& other);
        /*
        BigFloat& operator/= (const BigFloat& other);
        */

        BigFloat operator+(const BigFloat& other) const;

        BigFloat operator-(const BigFloat& other) const;

        BigFloat div_by_2()const;
        BigFloat mult(const BigFloat& other, const BigFloat& Eps)const;
        BigFloat operator*(const BigFloat& other) const;



        BigFloat operator/(const BigFloat& other) const;
};



#endif //BIGFLOAT_BIGFLOAT_H
