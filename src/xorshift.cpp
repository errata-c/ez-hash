#include <ez/hash/xorshift.hpp>

namespace ez::prng {
	XorShift32::XorShift32() noexcept
		: state(0)
	{}
	XorShift32::XorShift32(uint32_t s) noexcept
		: state(s)
	{}

	uint32_t XorShift32::operator()()  noexcept {
		return advance();
	}

	uint32_t XorShift32::advance() noexcept {
		state = eval();
		return state;
	}

	uint32_t XorShift32::eval() const  noexcept {
		uint32_t x = state;
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}


	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~


	XorShift64::XorShift64() noexcept
		: state(0)
	{}
	XorShift64::XorShift64(uint64_t s) noexcept
		: state(s)
	{}

	uint64_t XorShift64::operator()()  noexcept {
		return advance();
	}

	uint64_t XorShift64::advance() noexcept {
		state = eval();
		return state;
	}

	uint64_t XorShift64::eval() const noexcept {
		uint64_t x = state;
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		return x;
	}


	/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	XorWow::XorWow() noexcept
		: state{ 0,0,0,0 }
		, counter(0)
	{}
	XorWow::XorWow(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept
		: state{ s0, s1, s2, s3 }
		, counter(0)
	{}

	uint32_t XorWow::operator()() noexcept {
		return advance();
	}

	uint32_t XorWow::advance() noexcept {
		/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
		uint32_t t = state[3];

		uint32_t const s = state[0];
		state[3] = state[2];
		state[2] = state[1];
		state[1] = s;

		t ^= t >> 2;
		t ^= t << 1;
		t ^= s ^ (s << 4);
		state[0] = t;

		counter += 362437;
		return t + counter;
	}

	uint32_t XorWow::eval() const noexcept {
		/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
		uint32_t t = state[3];
		uint32_t const s = state[0];

		t ^= t >> 2;
		t ^= t << 1;
		t ^= s ^ (s << 4);

		return t + counter + 362437;
	}
}