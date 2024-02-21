#include "BigFloat.h"
#include <catch2/catch_test_macros.hpp>
#include "catch2/catch_session.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

TEST_CASE("foo", "[lolol]") {
    BigFloat a("0.01");
    BigFloat b = 0.02_bf;
    REQUIRE(true);
}
