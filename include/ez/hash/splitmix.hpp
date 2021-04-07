#pragma once
#include <cinttypes>

namespace ez::prng {
	class SplitMix64 {
	public:
		~SplitMix64() noexcept = default;
		SplitMix64(const SplitMix64&)  noexcept = default;
		SplitMix64& operator=(const SplitMix64&) noexcept = default;

		SplitMix64() noexcept;
		SplitMix64(uint64_t s) noexcept;

		uint64_t operator()() noexcept;

		uint64_t advance()  noexcept;

		uint64_t eval() const noexcept;

		uint64_t state;
	};
}