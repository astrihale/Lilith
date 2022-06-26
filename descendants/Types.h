#ifndef DESCENDANTS_TYPES_H
#define DESCENDANTS_TYPES_H

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace descendants
{
// Define the alias for strings
using String = std::string;
using StringStream = std::stringstream;

// Define an alias for the standard vector
template <typename T> using Vector = std::vector<T>;

// Define an alias for the standard map
template <typename X, typename Y> using Map = std::map<X, Y>;
template <typename X, typename Y> using MultiMap = std::multimap<X, Y>;
template <typename X, typename Y> using UnorderedMap = std::unordered_map<X, Y>;

// Define the alias for lambdas
template <typename T> using Lambda = std::function<T>;
}    // namespace descendants

#endif    // DESCENDANTS_TYPES_H
