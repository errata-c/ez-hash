#include <catch2/catch_all.hpp>

#include <ez/hash/util.hpp>

#include <fmt/core.h>
#include <cmath>
#include <limits>

#include <ez/hash/xorshift.hpp>
#include <ez/hash/splitmix.hpp>
#include <ez/hash/murmur.hpp>

using namespace ez::hash;

TEST_CASE("XorShift32") {
	XorShift32 func;

	func.state.words.fill(0xFF00'FF00);
	
	uint32_t val = func.eval();

	REQUIRE(val == 4243677552);
}

TEST_CASE("XorShift64") {
	XorShift64 func;

	func.state.words.fill(0xFF00'FF00);

	uint64_t val = func.eval();

	REQUIRE(val == 11773363129287524094);
}

TEST_CASE("XorWow") {
	XorWow func;
	func.state.words.fill(0xFF00'FF00);

	uint32_t val = func.eval();

	REQUIRE(val == 1314117125);
}

TEST_CASE("MurMur32") {
	Murmur32 func;
	func.state.words.fill(0xFF00'FF00);

	uint32_t val = func.eval("murmur32");

	REQUIRE(val == 1174902999);
}

TEST_CASE("random initialization") {
	std::random_device rd;

	XorShift32 xs32 = XorShift32::from(rd);
	XorShift64 xs64 = XorShift64::from(rd);
	XorShift128 xs128 = XorShift128::from(rd);
}