#pragma once
#include <cinttypes>
#include <cstddef>
#include <array>

#include "state.hpp"

namespace ez::hash {
	class SplitMix64 {
	public:
		using state_t = State<2, uint64_t>;
		using value_type = uint64_t;

		~SplitMix64() noexcept = default;
		SplitMix64(const SplitMix64&)  noexcept = default;
		SplitMix64& operator=(const SplitMix64&) noexcept = default;

		SplitMix64() noexcept;
		SplitMix64(uint64_t s) noexcept;

		uint64_t operator()() noexcept;

		uint64_t advance()  noexcept;

		uint64_t eval() const noexcept;

		state_t state;
	};
}