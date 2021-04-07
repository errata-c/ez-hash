#pragma once
#include <cinttypes>

namespace ez::prng {
	class XorShift32 {
	public:
		~XorShift32() noexcept = default;
		XorShift32(const XorShift32&) noexcept = default;
		XorShift32& operator=(const XorShift32&) noexcept = default;

		XorShift32() noexcept;
		XorShift32(uint32_t s) noexcept;

		uint32_t operator()()  noexcept;

		uint32_t advance() noexcept;
		uint32_t eval() const  noexcept;

		uint32_t state;
	};

	class XorShift64 {
	public:
		~XorShift64() noexcept = default;
		XorShift64(const XorShift64&) noexcept = default;
		XorShift64& operator=(const XorShift64&) noexcept = default;

		XorShift64() noexcept;
		XorShift64(uint64_t s) noexcept;

		uint64_t operator()()  noexcept;

		uint64_t advance() noexcept;

		uint64_t eval() const noexcept;

		uint64_t state;
	};


	class XorWow {
	public:
		~XorWow() noexcept = default;
		XorWow(const XorWow&) noexcept = default;
		XorWow& operator=(const XorWow&) noexcept = default;

		XorWow() noexcept;
		XorWow(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3) noexcept;

		uint32_t operator()() noexcept;

		uint32_t advance() noexcept;
		uint32_t eval() const noexcept;

		uint32_t state[4];
		uint32_t counter;
	};
}