#ifndef DESCENDANTS_PRINTABLE_H
#define DESCENDANTS_PRINTABLE_H

#include <concepts>

namespace descendants::printing
{
/**
 * This is the concept which describes a type that can be presented as a string.
 * @tparam T The type of the value in question.
 */
template <typename T>
concept Printable = requires(T value)
{
    {
        std::to_string(value)
        } -> std::same_as<std::string>;
};

/**
 * This is the concept which describes an object that can be presented as a string.
 * @tparam T The type of the value in question.
 */
template <typename T>
concept PrintableObject = requires(T value)
{
    {
        value.toString()
        } -> std::same_as<std::string>;
};
}    // namespace descendants::printing

#endif    // DESCENDANTS_PRINTABLE_H
