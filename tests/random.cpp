#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "../include/chaiscript/extras/random.hpp"

TEST_CASE( "Random functions work", "[random]" ) {
  auto randomlib = chaiscript::extras::random::bootstrap();

  auto stdlib = chaiscript::Std_Lib::library();
  chaiscript::ChaiScript chai(stdlib);
  chai.add(randomlib);

  SECTION("rand() returns a non-negative integer") {
    const auto result = chai.eval<int>("rand()");
    CHECK(result >= 0);
  }

  SECTION("rand(max) returns a value in [0, max]") {
    const auto result = chai.eval<int>("rand(10)");
    CHECK(result >= 0);
    CHECK(result <= 10);
  }

  SECTION("rand(min, max) returns a value in [min, max]") {
    const auto result = chai.eval<int>("rand(5, 10)");
    CHECK(result >= 5);
    CHECK(result <= 10);
  }

  SECTION("srand(seed) produces deterministic results") {
    chai.eval("srand(42)");
    const auto first = chai.eval<int>("rand(0, 1000)");
    chai.eval("srand(42)");
    const auto second = chai.eval<int>("rand(0, 1000)");
    CHECK(first == second);
  }

  SECTION("rand() with same seed is deterministic") {
    chai.eval("srand(123)");
    const auto a = chai.eval<int>("rand()");
    chai.eval("srand(123)");
    const auto b = chai.eval<int>("rand()");
    CHECK(a == b);
  }
}
