#include <iostream>
#include <algorithm>
#include "BigFloat.h"
#include "catch2/catch_session.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

//examples of tests with certain numbers

TEST_CASE("logic operations") {
    REQUIRE(0_bf == BigFloat("-0"));
}
TEST_CASE("arithmetic operations") {
    SECTION("addition") {
        REQUIRE(1_bf + 1_bf == 2_bf);
        REQUIRE(1_bf + 2_bf == 3_bf);
        REQUIRE(1_bf + 0.5_bf == 1.5_bf);
        REQUIRE(123454345654.56756785_bf + 123454345654.56756785_bf == 246908691309.1351357_bf);
    }
    SECTION("subtraction") {
        REQUIRE(1_bf - 1_bf == 0_bf);
        REQUIRE(1_bf - 2_bf == -1_bf);
        REQUIRE(1_bf - 0.5_bf == 0.5_bf);
    }
    SECTION("multiplication") {
        REQUIRE(1_bf * 1_bf == 1_bf);
        REQUIRE(1_bf * 2_bf == 2_bf);
        REQUIRE(1_bf * 0.5_bf == 0.5_bf);
    }
    SECTION("division") {
        REQUIRE(1_bf / 1_bf == 1_bf);
        REQUIRE(1_bf / 2_bf == 0.5_bf);
        REQUIRE(1_bf / 0.5_bf == 2_bf);
        REQUIRE(2345678654323473535554_bf / 2345678654323473535554_bf == 1_bf);
        REQUIRE(3456543212345.9045846969_bf / 345654321234590.45846969_bf == 0.01_bf);
    }
}
TEST_CASE( "non arithmetic or boolean public methods",) {
    BigFloat::set_precision(3);
    BigFloat a = -100.059_bf;
    REQUIRE(a.abs() == 100.059_bf);
    REQUIRE(a.to_string() == "-100.059");
    a = -a;
    REQUIRE(a == 100.059_bf);
    REQUIRE(a.to_string() == "100.059");
}

//Tests Generator
TEST_CASE("BigFloat arithmetic operators",) {
    SECTION("unary operator -") {
        int a = GENERATE(take(2, random(-100000000, 100000000)));
        BigFloat x = BigFloat(a);
        BigFloat minus_x = BigFloat(-a);
        REQUIRE(-x == minus_x);
    }
    SECTION("operator = ") {
        BigFloat::set_precision(100);
        int a = GENERATE(take(2, random(-100000000, 100000000)));
        BigFloat x = BigFloat(a);
        BigFloat y = BigFloat(2 * a);
        REQUIRE((2_bf * x) == y);
    }
    SECTION("+ and - binary operators") {
        BigFloat::set_precision(100);
        int num_a = GENERATE(take(4,random(-1000, 1000)));
        int num_b = GENERATE(take(4,random(-1000, 1000)));

        int denom_a = GENERATE(take(4,random(1, 1000)));
        int denom_b = GENERATE(take(4,random(1, 1000)));

        BigFloat A = BigFloat(num_a) / BigFloat(denom_a);
        BigFloat B = BigFloat(num_b) / BigFloat(denom_b);
        int gcd = std::gcd(denom_a, denom_b);
        int lcm = denom_a * denom_b / gcd;
        BigFloat res_plus = BigFloat(num_a * (denom_b / gcd) + num_b * (denom_a / gcd)) / BigFloat(lcm);
        BigFloat res_minus = BigFloat(num_a * (denom_b / gcd) - num_b * (denom_a / gcd)) / BigFloat(lcm);
        REQUIRE((A + B - res_plus).abs() < BigFloat("0.000000001"));
        REQUIRE(((A - B) - res_minus).abs() < BigFloat("0.000000001"));
    }
    SECTION("operator *") {
        int a = GENERATE(take(4,random(-10000, 10000)));
        int b = GENERATE(take(4,random(-10000, 10000)));
        REQUIRE(BigFloat(a) * BigFloat(b) == BigFloat(a * b));
    }
    SECTION("operator /") {
        BigFloat::set_precision(100);
        int a = GENERATE(take(4,random(-100, 100)));
        int b = 0;
        while (b == 0) {
            b = GENERATE(take(4,random(-100, 100)));
        }
        int delA = 0;
        while (delA == 0) {
            delA = GENERATE(take(4,random(1, 100)));
        }
        int delB = 0;
        while(delB == 0) {
            delB = GENERATE(take(4,random(1, 100)));
        }
        BigFloat x = BigFloat(a) / BigFloat(delA);
        BigFloat y = BigFloat(b) / BigFloat(delB);
        int lcm = delA * delB / std::gcd(delA, delB);
        BigFloat res = BigFloat(a * (lcm / delA)) / BigFloat(lcm) / (BigFloat(b * (lcm / delB)) / BigFloat(lcm));
        REQUIRE((x / y - res).abs() < BigFloat("0.000000001"));
    }
}

TEST_CASE("BigFloat comparison operators") {
    SECTION("== and != operators") {
        int a = GENERATE(take(5,random(-10000, 10000)));
        REQUIRE(BigFloat(a) == BigFloat(a));
        REQUIRE(BigFloat(a) != BigFloat(a + 1));
    }
    SECTION("< and > operators") {
        int a = GENERATE(take(5,random(-10000, 10000)));
        int b = GENERATE(take(5,random(-10000, 10000)));
        if (a < b) {
            REQUIRE(BigFloat(a) < BigFloat(b));
            REQUIRE(BigFloat(b) > BigFloat(a));
        } else if (a > b) {
            REQUIRE(BigFloat(a) > BigFloat(b));
            REQUIRE(BigFloat(b) < BigFloat(a));
        }
    }
    SECTION("<= and >= operators") {
        int a = GENERATE(take(5,random(-10000, 10000)));
        int b = GENERATE(take(5,random(-10000, 10000)));
        if (a <= b) {
            REQUIRE(BigFloat(a) <= BigFloat(b));
            REQUIRE(BigFloat(b) >= BigFloat(a));
        } else if (a >= b) {
            REQUIRE(BigFloat(a) >= BigFloat(b));
            REQUIRE(BigFloat(b) <= BigFloat(a));
        }
    }
}

