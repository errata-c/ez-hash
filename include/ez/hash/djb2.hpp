#pragma once
#include <cinttypes>
#include <type_traits>

namespace ez::prng {
	namespace intern {
		/*
		djb2
			This algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c.
		Another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i];
		The magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.
		*/
		template<typename T>
		static constexpr uint32_t djb2HashValue(T val, uint32_t seed = 5381u) {
			using utype = std::make_unsigned_t<T>;
			for (int i = 0; i < sizeof(utype); ++i) {
				// Bitshifting avoids any endianess problems, and optimizes well.
				seed = (seed * 33u) ^ static_cast<uint32_t>(val & (static_cast<utype>(0xFF) << (i << 3)));
			}

			return seed;
		}
	};
}