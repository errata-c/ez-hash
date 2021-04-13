#pragma once
#include "util.hpp"
#include <cstddef>
#include <cinttypes>
#include <cassert>
#include <type_traits>
#include <array>

namespace ez::hash {
	// Create a state, composed of some number of 32 bit unsigned values. Allow access of those values via the type T
	// T must be an integer type
	template<std::size_t N, typename T = uint32_t>
	class State {
	public:
		static_assert(N != 0, "Cannot have a zero sized state!");
		static_assert(std::is_integral_v<T>, "Access type must be integral!");
		static_assert(((N * 4) % sizeof(T)) == 0, "Access type must align with the size of the state!");

		static constexpr std::size_t _num_values = (N * 4) / sizeof(T);

		struct uninitialized_t {};

		// Basic constructors and destructors
		~State() = default;
		State(const State&) noexcept = default;
		State& operator=(const State&) noexcept = default;

		template<typename RNG, typename = std::enable_if_t<std::is_invocable<RNG>::value>>
		static State from(RNG && rng) {
			using result_t = decltype(rng());
			static_assert(std::is_integral_v<result_t>, "Functor passed into 'State::from' must return an integral type.");
			static_assert(sizeof(result_t) == sizeof(uint32_t) || sizeof(result_t) == sizeof(T), "Functor passed into 'State::from' must return a type matching the word size or the value size.");

			State state{ uninitialized_t{} };

			if constexpr (sizeof(result_t) == sizeof(uint32_t)) {
				for (auto it = state.words.begin(), end = state.words.end(); it != end; ++it) {
					*it = rng();
				}
			}
			else {
				for (auto it = state.values.begin(), end = state.values.end(); it != end; ++it) {
					*it = rng();
				}
			}

			return state;
		}

		template<typename Iter>
		static State fromWords(Iter first, Iter last) {
			State state{ uninitialized_t{} };

			auto it = state.words.begin();
			while (first != last && it != state.words.end()) {
				*it = static_cast<uint32_t>(*first);

				++first;
				++it;
			}
			while (it != state.words.end()) {
				*it = 0;
				++it;
			}

			return state;
		}

		template<typename Iter>
		static State fromValues(Iter first, Iter last) {
			State state{ uninitialized_t{} };

			auto it = state.values.begin();
			auto eit = state.values.end();
			while (first != last && it != eit) {
				*it = static_cast<T>(*first);

				++first;
				++it;
			}
			while (it != eit) {
				*it = 0;
				++it;
			}

			return state;
		}

		// Not initialized
		State(uninitialized_t ) noexcept {}
		// Zero initialized
		State() noexcept {
			words.fill(0);
		}
		// Value initialized
		State(uint32_t val) noexcept {
			words.fill(val);
		}
		// Value initialized
		template<typename = std::enable_if_t<!std::is_same_v<uint32_t, T>>>
		State(T val) noexcept {
			values.fill(val);
		}

		T& value() noexcept {
			return values[0];
		}
		const T& value() const noexcept {
			return values[0];
		}

		constexpr std::size_t sizeBytes() const noexcept {
			return N * 4;
		}
		constexpr std::size_t sizeBits() const noexcept {
			return N * 32;
		}

		void fillWords(uint32_t word) noexcept {
			words.fill(word);
		}
		void fillValues(T value) noexcept {
			values.fill(value);
		}

		template<typename RNG, typename = std::enable_if_t<std::is_invocable_r<uint32_t, RNG>::value>>
		void fillWordsFrom(RNG&& rng) {
			for (uint32_t& val : words) {
				val = rng();
			}
		};
		template<typename RNG, typename = std::enable_if_t<std::is_invocable_r<T, RNG>::value>>
		void fillValuesFrom(RNG&& rng) {
			for (T& val : values) {
				val = rng();
			}
		};

		void swap(State& other) noexcept {
			State tmp = *this;
			*this = other;
			other = tmp;
		}
	
		union {
			std::array<uint32_t, N> words;
			std::array<T, _num_values> values;
		};
	};
}