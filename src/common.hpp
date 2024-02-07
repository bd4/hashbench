#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>

#include <benchmark/benchmark.h>

using hpt_t = std::tuple<std::string, intptr_t, uintptr_t>;
using hp_t = std::tuple<std::string, intptr_t>;

using hpt_ts_map = std::unordered_map<hpt_t, int64_t>;
using hp_ts_map = std::unordered_map<hp_t, int64_t>;

// NOTE: Required to generate the hash of a tuple.
// REFERENCE:
// https://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
namespace std {
namespace {
// Code from boost
// Reciprocal of the golden ratio helps spread entropy
//     and handles duplicates.
// See Mike Seymour in magic-numbers-in-boosthash-combine:
//     https://stackoverflow.com/questions/4948780
template <class T> inline void hash_combine(std::size_t &seed, T const &v) {
  seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Recursive template code derived from Matthieu M.
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1> struct HashValueImpl {
  static void apply(size_t &seed, Tuple const &tuple) {
    HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
    hash_combine(seed, get<Index>(tuple));
  }
};

template <class Tuple> struct HashValueImpl<Tuple, 0> {
  static void apply(size_t &seed, Tuple const &tuple) { hash_combine(seed, get<0>(tuple)); }
};
} // namespace

template <typename... TT> struct hash<std::tuple<TT...>> {
  size_t operator()(std::tuple<TT...> const &tt) const {
    size_t seed = 0;
    HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
    return seed;
  }
};

template <typename... TT> struct hash<std::pair<TT...>> {
  size_t operator()(std::pair<TT...> const &tt) const {
    size_t seed = 0;
    HashValueImpl<std::pair<TT...>>::apply(seed, tt);
    return seed;
  }
};
} // namespace std
