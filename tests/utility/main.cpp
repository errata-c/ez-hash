#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ez/hash/util.hpp>

#include <fmt/core.h>
#include <cmath>
#include <limits>

using namespace ez::prng;

template<typename T>
bool approxEq(T a, T b, T delta) {
	return std::abs(b - a) < delta;
};

TEST_CASE("Rotation functions") {
	REQUIRE(rotl16(0xF00F, 4) == 0x00FF);
	REQUIRE(rotl16(0x000F, 12) == 0xF000);

	REQUIRE(rotr16(0xF00F, 4) == 0xFF00);
	REQUIRE(rotr16(0x000F, 12) == 0x00F0);
	
	REQUIRE(rotl32(0xF000'000F, 4) == 0xFF);
	REQUIRE(rotl32(0xF000'000F, 8) == 0xFF0);

	REQUIRE(rotr32(0xF000'000F, 4) == 0xFF00'0000);
	REQUIRE(rotr32(0xF000'000F, 8) == 0x0FF0'0000);

	REQUIRE(rotl64(0xF000'0000'0000'000Full, 4) == 0xFF);
	REQUIRE(rotl64(0xF000'0000'0000'000Full, 8) == 0xFF0);

	REQUIRE(rotr64(0xF000'0000'0000'000Full, 4) == 0xFF00'0000'0000'0000ull);
	REQUIRE(rotr64(0xF000'0000'0000'000Full, 8) == 0x0FF0'0000'0000'0000ull);
}

TEST_CASE("Normalize functions") {
	static constexpr uint32_t
		maxu32 = std::numeric_limits<uint32_t>::max(),
		minu32 = 0;

	static constexpr int32_t
		maxi32 = std::numeric_limits<int32_t>::max(),
		mini32 = std::numeric_limits<int32_t>::lowest();

	static constexpr uint64_t
		maxu64 = std::numeric_limits<uint64_t>::max(),
		minu64 = 0;

	static constexpr int64_t
		maxi64 = std::numeric_limits<int64_t>::max(),
		mini64 = std::numeric_limits<int64_t>::lowest();

	REQUIRE(approxEq(normalizeu32(0), 0.f, 1e-4f));
	REQUIRE(approxEq(normalizei32(0), 0.f, 1e-4f));

	REQUIRE(approxEq(normalizeu32(maxu32), 1.f, 1e-4f));
	REQUIRE(approxEq(normalizei32(maxi32), 1.f, 1e-4f));

	REQUIRE(approxEq(normalizei32(mini32), -1.f, 1e-4f));


	REQUIRE(approxEq(normalizeu64(0), 0.0, 1e-4));
	REQUIRE(approxEq(normalizei64(0), 0.0, 1e-4));

	REQUIRE(approxEq(normalizeu64(maxu64), 1.0, 1e-8));
	REQUIRE(approxEq(normalizei64(maxi64), 1.0, 1e-8));

	REQUIRE(approxEq(normalizei64(mini64), -1.0, 1e-8));
}