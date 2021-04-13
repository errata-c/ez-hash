#include <ez/hash/xorshift.hpp>

namespace ez::hash {
	XorShift32::XorShift32(uint32_t s) noexcept {
		state.words = {s};
	}

	uint32_t XorShift32::operator()()  noexcept {
		return advance();
	}

	uint32_t XorShift32::advance() noexcept {
		state.value() = eval();
		return state.value();
	}

	uint32_t XorShift32::eval() const  noexcept {
		uint32_t x = state.value();
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}


	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~


	XorShift64::XorShift64(uint64_t s) noexcept {
		state.values = { s };
	}

	uint64_t XorShift64::operator()()  noexcept {
		return advance();
	}

	uint64_t XorShift64::advance() noexcept {
		state.value() = eval();
		return state.value();
	}

	uint64_t XorShift64::eval() const noexcept {
		uint64_t x = state.value();
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		return x;
	}

	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	XorShift128::XorShift128(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept {
		state.words = { s0, s1, s2, s3 };
	}

	uint32_t XorShift128::operator()()  noexcept {
		return advance();
	}

	uint32_t XorShift128::advance() noexcept {
		uint32_t t = state.words[3];
		uint32_t s = state.words[0];

		state.words[3] = state.words[2];
		state.words[2] = state.words[1];
		state.words[1] = s;

		t ^= t << 11;
		t ^= t >> 8;

		state.words[0] = t ^ s ^ (s >> 19);

		return state.words[0];
	}

	uint32_t XorShift128::eval() const noexcept {
		uint32_t t = state.words[3];
		uint32_t s = state.words[0];

		t ^= t << 11;
		t ^= t >> 8;
		return t ^ s ^ (s >> 19);
	}


	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	XorWow::XorWow() noexcept
		: state{ 0 }
		, counter(0)
	{}
	XorWow::XorWow(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept
		: counter(0)
	{
		state.words = { s0, s1, s2, s3 };
	}

	uint32_t XorWow::operator()() noexcept {
		return advance();
	}

	uint32_t XorWow::advance() noexcept {
		/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
		uint32_t t = state.words[3];

		uint32_t const s = state.words[0];
		state.words[3] = state.words[2];
		state.words[2] = state.words[1];
		state.words[1] = s;

		t ^= t >> 2;
		t ^= t << 1;
		t ^= s ^ (s << 4);
		state.words[0] = t;

		counter += 362437;
		return t + counter;
	}

	uint32_t XorWow::eval() const noexcept {
		/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
		uint32_t t = state.words[3];
		uint32_t const s = state.words[0];

		t ^= t >> 2;
		t ^= t << 1;
		t ^= s ^ (s << 4);

		return t + counter + 362437;
	}
}