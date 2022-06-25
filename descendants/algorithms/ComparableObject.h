#ifndef DESCENDANTS_COMPARABLEOBJECT_H
#define DESCENDANTS_COMPARABLEOBJECT_H

#include <cstdint>
#include <compare>
#include <concepts>

namespace descendants::algorithms
{
/**
 * This is the interface that describes an object which is capable of comparing itself with other objects of the same
 * type.
 */
class ComparableObject
{
public:
    /**
     * Default virtual destructor.
     */
    virtual ~ComparableObject() = default;

    /**
     * The comparison method that is used by the object.
     *
     * @tparam T The type of the value being compared.
     * @param rightValue The second value being compared to this.
     * @return The return of the operation. If this is less than right, return -1. If right is less than this, then
     * return 1, otherwise return 0.
     */
    template <typename T> auto operator<=>(const T& rightValue) { return this <=> rightValue; };
};

/**
 * This is the concept that describes a value that is capable of being compared to other to other values of the same
 * type.
 * @tparam T The type that is being checked.
 */
template <typename T>
concept Comparable = requires(T left, T right)
{
    {left <=> right};
};
}    // namespace descendants::algorithms

#endif    // DESCENDANTS_COMPARABLEOBJECT_H
