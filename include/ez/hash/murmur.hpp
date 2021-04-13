#pragma once
#include <string_view>
#include <cinttypes>
#include "state.hpp"

namespace ez::hash {
	class Murmur32 {
	public:
		using state_t = State<1>;
		using value_type = uint64_t;

		~Murmur32() = default;
		Murmur32(const Murmur32&) = default;
		Murmur32& operator=(const Murmur32&) = default;

		Murmur32() noexcept;
		Murmur32(uint32_t s) noexcept;

		uint32_t operator()(std::string_view text) noexcept;
		uint32_t operator()(const void* key, std::intptr_t len) noexcept;

		uint32_t advance(std::string_view str) noexcept;
		uint32_t advance(const void* key, std::intptr_t len) noexcept;

		uint32_t eval(std::string_view text) const noexcept;
		uint32_t eval(const void* key, std::intptr_t len) const noexcept;

		state_t state;
	};
}