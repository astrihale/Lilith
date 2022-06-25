#ifndef DESCENDANTS_TYPES_H
#define DESCENDANTS_TYPES_H

#include <vector>

namespace descendants
{
// Define an alias for the standard vector
template <typename T> using Vector = std::vector<T>;

// Define the alias for lambdas
template <typename T> using Lambda = std::function<T>;
}    // namespace descendants

#endif    // DESCENDANTS_TYPES_H
