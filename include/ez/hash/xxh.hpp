#pragma once
#include <cinttypes>
#include <string_view>


namespace ez::hash {
	uint32_t xxh32(std::string_view text, uint32_t seed = 0);
	uint64_t xxh64(std::string_view text, uint32_t seed = 0);

	uint64_t xxh3_64(std::string_view text);
	uint64_t xxh3_64(std::string_view text, uint64_t seed);
}