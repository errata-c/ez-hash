#include <ez/hash/murmur.hpp>
#include <ez/hash/util.hpp>
#include <limits>
#include <cassert>

namespace ez::hash {
	Murmur32::Murmur32() noexcept
		: state(0)
	{}
	Murmur32::Murmur32(uint32_t s) noexcept {
		state.words = { s };
	}

	uint32_t Murmur32::operator()(std::string_view str)  noexcept {
		return advance(str.data(), static_cast<std::intptr_t>(str.size()));
	}
	uint32_t Murmur32::operator()(const void* key, std::intptr_t len)  noexcept {
		return advance(key, len);
	}

	uint32_t Murmur32::advance(std::string_view str)  noexcept {
		return advance(str.data(), static_cast<std::intptr_t>(str.size()));
	}
	uint32_t Murmur32::advance(const void* key, std::intptr_t len) noexcept {
		uint32_t result = eval(key, len);

		state.value() = result;
		return result;
	}

	uint32_t Murmur32::eval(std::string_view str) const  noexcept {
		return eval(str.data(), static_cast<std::intptr_t>(str.size()));
	}
	uint32_t Murmur32::eval(const void* key, std::intptr_t len) const  noexcept {
		/* 32-Bit MurmurHash3: https://code.google.com/p/smhasher/wiki/MurmurHash3 */
		uint32_t h1 = state.value();
		uint32_t k1;
		const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(key);
		const std::uint8_t* keyptr = data;
		constexpr int bsize = sizeof(k1);
		const std::intptr_t nblocks = len / bsize;

		const uint32_t c1 = 0xcc9e2d51u;
		const uint32_t c2 = 0x1b873593u;
		const std::uint8_t* tail;
		std::intptr_t i;

		/* body */
		if (!key) return 0;
		for (i = 0; i < nblocks; ++i, keyptr += bsize) {
			k1 = 0;
			k1 |= uint32_t(keyptr[0]);
			k1 |= uint32_t(keyptr[1]) << 8;
			k1 |= uint32_t(keyptr[2]) << 16;
			k1 |= uint32_t(keyptr[3]) << 24;

			k1 *= c1;
			k1 = rotl32(k1, 15);
			k1 *= c2;

			h1 ^= k1;
			h1 = rotl32(h1, 13);
			h1 = h1 * 5u + 0xe6546b64u;
		}

		/* tail */
		tail = (const uint8_t*)(data + nblocks * static_cast<std::intptr_t>(4));
		k1 = 0;
		switch (len & 3) {
		case 3: 
			k1 ^= (uint32_t)(tail[2] << 16); 
			[[fallthrough]];

		case 2: 
			k1 ^= (uint32_t)(tail[1] << 8u); 
			[[fallthrough]];

		case 1: 
			k1 ^= tail[0];
			k1 *= c1;
			k1 = rotl32(k1, 15);
			k1 *= c2;
			h1 ^= k1;
			break;

		default: 
			break;
		}

		/* finalization */
		h1 ^= (uint32_t)len;

		/* fmix32 */
		h1 ^= h1 >> 16;
		h1 *= 0x85ebca6bu;
		h1 ^= h1 >> 13;
		h1 *= 0xc2b2ae35u;
		h1 ^= h1 >> 16;

		return h1;
	}
}