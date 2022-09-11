#ifndef LILITH_TYPES_H
#define LILITH_TYPES_H

#include <chrono>
#include <functional>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace lilith
{
// Time type aliases
using TimePoint = std::chrono::system_clock::time_point;

// Define the alias for strings
using String = std::string;
using StringStream = std::stringstream;

// Define an alias for the standard linear structures
template <typename X, typename Y> using Pair = std::pair<X, Y>;
template <typename T> using Vector = std::vector<T>;

// Define an alias for the standard map
template <typename X, typename Y> using Map = std::map<X, Y>;
template <typename X, typename Y> using MultiMap = std::multimap<X, Y>;
template <typename X, typename Y> using UnorderedMap = std::unordered_map<X, Y>;

// Define the alias for lambdas
template <typename T> using Lambda = std::function<T>;

// Define the alias for optionals
template <typename T> using Optional = std::optional<T>;
}    // namespace lilith

#endif    // LILITH_TYPES_H
