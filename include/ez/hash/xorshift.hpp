#pragma once
#include <cinttypes>
#include <cstddef>
#include "State.hpp"

namespace ez::hash {
	class XorShift32 {
	public:
		using value_type = uint32_t;
		using state_t = State<1>;

		XorShift32(state_t _state) noexcept
			: state(_state)
		{}

		XorShift32() noexcept = default;
		~XorShift32() noexcept = default;
		XorShift32(const XorShift32&) noexcept = default;
		XorShift32& operator=(const XorShift32&) noexcept = default;

		template<typename RNG>
		static XorShift32 from(RNG && rng) noexcept {
			return XorShift32(state_t::from(rng));
		}
		
		XorShift32(uint32_t s) noexcept;

		uint32_t operator()()  noexcept;

		uint32_t advance() noexcept;
		uint32_t eval() const  noexcept;

		state_t state;
	};

	class XorShift64 {
	public:
		using value_type = uint64_t;
		using state_t = State<2, uint64_t>;

		XorShift64(state_t _state) noexcept
			: state(_state)
		{}

		XorShift64() noexcept = default;
		~XorShift64() noexcept = default;
		XorShift64(const XorShift64&) noexcept = default;
		XorShift64& operator=(const XorShift64&) noexcept = default;
		
		XorShift64(uint64_t s) noexcept;

		template<typename RNG>
		static XorShift64 from(RNG&& rng) noexcept {
			return XorShift64(state_t::from(rng));
		}

		uint64_t operator()()  noexcept;

		uint64_t advance() noexcept;

		uint64_t eval() const noexcept;

		state_t state;
	};

	class XorShift128 {
	public:
		using value_type = uint32_t;
		using state_t = State<4>;

		XorShift128(state_t _state) noexcept
			: state(_state)
		{}

		XorShift128() noexcept = default;
		~XorShift128() noexcept = default;
		XorShift128(const XorShift128&) noexcept = default;
		XorShift128& operator=(const XorShift128&) noexcept = default;
		
		XorShift128(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept;

		template<typename RNG>
		static XorShift128 from(RNG&& rng) noexcept {
			return XorShift128(state_t::from(rng));
		}

		uint32_t operator()()  noexcept;

		uint32_t advance() noexcept;

		uint32_t eval() const noexcept;

		state_t state;
	};

	class XorWow {
	public:
		using value_type = uint32_t;
		using state_t = State<4>;

		XorWow(state_t _state) noexcept
			: state(_state)
			, counter(0)
		{}

		XorWow() noexcept;
		~XorWow() noexcept = default;
		XorWow(const XorWow&) noexcept = default;
		XorWow& operator=(const XorWow&) noexcept = default;
		
		XorWow(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept;

		template<typename RNG>
		static XorWow from(RNG&& rng) noexcept {
			return XorWow(state_t::from(rng));
		}

		uint32_t operator()() noexcept;

		uint32_t advance() noexcept;
		uint32_t eval() const noexcept;

		state_t state;
		uint32_t counter;
	};
}