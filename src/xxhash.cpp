#include <ez/hash/xxh.hpp>
#include "xxhash.h"

namespace ez::hash {
	uint32_t xxh32(std::string_view text, uint32_t seed) {
		return XXH32(text.data(), text.size(), seed);
	}
	uint64_t xxh64(std::string_view text, uint32_t seed) {
		return XXH64(text.data(), text.size(), seed);
	}
	
	uint64_t xxh3_64(std::string_view text) {
		return XXH3_64bits(text.data(), text.size());
	}
	uint64_t xxh3_64(std::string_view text, uint64_t seed) {
		return XXH3_64bits_withSeed(text.data(), text.size(), seed);
	}
}