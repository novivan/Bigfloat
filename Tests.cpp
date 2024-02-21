//#include "BigFloat.h"
//#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <algorithm>
#include "BigFloat.h"
#include "catch2/catch_session.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

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










TEST_CASE( "[BigFloat public methods]", "[All]" ) {
    BigFloat a = 1.96_bf;
    a.set_precision(2);
    REQUIRE(a.to_string() == "1.96");
    a = -a;
    REQUIRE(a == -1.96_bf);
    REQUIRE(a.abs() == 1.96_bf);
    REQUIRE(a.to_string() == "-1.96");
}

TEST_CASE("[BigFloat operators]", "[All]") {
    SECTION("+ whole numbers") {
        int a = GENERATE(take(10,random(-100, 100)));
        int b = GENERATE(take(10,random(-100, 100)));
        a = -43;
        b = 43;
        INFO(a);
        INFO(b);
        BigFloat res = BigFloat(a) + BigFloat(b);
        REQUIRE(res == BigFloat(a + b));
    }
    SECTION("+ real numbers") {
        int a = GENERATE(take(5,random(-100, 100)));
        int b = GENERATE(take(5,random(-100, 100)));
        int delA = GENERATE(take(5,random(1, 100)));
        int delB = GENERATE(take(5,random(1, 100)));
        BigFloat x = BigFloat(0);
        x.set_precision(100);
        x = BigFloat(a) / BigFloat(delA);
        BigFloat y = BigFloat(b) / BigFloat(delB);
        int lcm = delA * delB / std::gcd(delA, delB);
        BigFloat res = BigFloat(a * (lcm / delA) + b * (lcm / delB)) / BigFloat(lcm);
        REQUIRE((x + y - res).abs() < BigFloat("0.000000001"));
    }
    SECTION("*") {
        int a = GENERATE(take(10,random(-100, 100)));
        int b = GENERATE(take(10,random(-100, 100)));
        REQUIRE(BigFloat(a) * BigFloat(b) == BigFloat(a * b));
    }
    SECTION("- whole numbers") {
        int a = GENERATE(take(10,random(-100, 100)));
        int b = GENERATE(take(10,random(-100, 100)));
        REQUIRE(BigFloat(a) - BigFloat(b) == BigFloat(a - b));
    }
}

TEST_CASE("[BigFloat comparation operators]", "[All]") {
    SECTION("== and != operators") {
        int a = GENERATE(take(10,random(-100, 100)));
        REQUIRE(BigFloat(a) == BigFloat(a));
        REQUIRE(BigFloat(a) != BigFloat(a + 1));
    }
    SECTION("< and > operators") {
        int a = GENERATE(take(10,random(-100, 100)));
        int b = GENERATE(take(10,random(-100, 100)));
        if (a < b) {
            INFO(a);
            INFO(b);
            REQUIRE(BigFloat(a) < BigFloat(b));
            REQUIRE(BigFloat(b) > BigFloat(a));
        } else if (a > b) {
            INFO(a);
            INFO(b);
            REQUIRE(BigFloat(a) > BigFloat(b));
            REQUIRE(BigFloat(b) < BigFloat(a));
        }
    }
}

