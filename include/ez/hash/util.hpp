#pragma once
#include <cinttypes>
#include <cassert>

namespace ez::prng {
	inline uint8_t rotl8(uint8_t val, uint32_t amount) {
		assert(amount < 8);
		return static_cast<uint8_t>(val << amount) | (val >> (((~amount) + 1) & 7u));
	}
	inline uint16_t rotl16(uint16_t val, uint32_t amount) {
		assert(amount < 16);
		return static_cast<uint16_t>(val << amount) | (val >> (((~amount) + 1) & 15u));
	}
	inline uint32_t rotl32(uint32_t val, uint32_t amount) {
		assert(amount < 32);
		return (val << amount) | (val >> (((~amount) + 1) & 31u));
	}
	inline uint64_t rotl64(uint64_t val, uint32_t amount) {
		assert(amount < 64);
		return (val << amount) | (val >> (((~amount) + 1) & 63u));
	}

	inline uint8_t rotr8(uint8_t val, uint32_t amount) {
		assert(amount < 8);
		return static_cast<uint8_t>(val >> amount) | (val << (((~amount) + 1) & 7u));
	}
	inline uint16_t rotr16(uint16_t val, uint32_t amount) {
		assert(amount < 16);
		return static_cast<uint16_t>(val >> amount) | (val << (((~amount) + 1) & 15u));
	}
	inline uint32_t rotr32(uint32_t val, uint32_t amount) {
		assert(amount < 32);
		return (val >> amount) | (val << (((~amount) + 1) & 31u));
	}
	inline uint64_t rotr64(uint64_t val, uint32_t amount) {
		assert(amount < 64);
		return (val >> amount) | (val << (((~amount) + 1) & 63u));
	}

	// Normalize a 32 bit unsigned integer to the range [0, 1]
	static float normalizeu32(uint32_t value) {
		constexpr float maxval = static_cast<float>((1u << 23) - 1);
		constexpr float inv = 1.f / static_cast<float>(maxval);

		// shift out insignificant bits.
		value = value >> 9;

		return static_cast<float>(value) * inv;
	}

	// Normalize a 64 bit unsigned integer to the range [0, 1]
	static double normalizeu64(uint64_t value) {
		constexpr double maxval = static_cast<double>((1ull << 52) - 1);
		constexpr double inv = 1.0 / static_cast<double>(maxval);
		
		// shift out insignificant bits.
		value = value >> 12;

		return static_cast<double>(value) * inv;
	}

	// Normalize a 32 bit signed integer to the range [-1, 1]
	static float normalizei32(int32_t value) {
		constexpr float maxval = static_cast<float>((1u << 23) - 1);
		constexpr float inv = 2.f / static_cast<float>(maxval);

		// shift out insignificant bits.
		value = value >> 9;

		return static_cast<float>(value) * inv;
	}

	// Normalize a 64 bit signed integer to the range [-1, 1]
	static double normalizei64(int64_t value) {
		constexpr double maxval = static_cast<double>((1ull << 52) - 1);
		constexpr double inv = 2.0 / static_cast<double>(maxval);
		
		// shift out insignificant bits.
		value = value >> 12;

		return static_cast<double>(value) * inv;
	}
}