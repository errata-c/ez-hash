#include <ez/hash/splitmix.hpp>

namespace ez::prng {
	SplitMix64::SplitMix64() noexcept
		: state(0)
	{}
	SplitMix64::SplitMix64(uint64_t s) noexcept
		: state(s)
	{}

	uint64_t SplitMix64::operator()() noexcept {
		return advance();
	}

	uint64_t SplitMix64::advance()  noexcept {
		uint64_t result = state;

		state = result + 0x9E3779B97f4A7C15;
		result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
		result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
		return result ^ (result >> 31);
	}

	uint64_t SplitMix64::eval() const noexcept {
		uint64_t result = state;

		//state = result + 0x9E3779B97f4A7C15;
		result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
		result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
		return result ^ (result >> 31);
	}
}