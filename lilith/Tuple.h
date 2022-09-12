#ifndef LILITH_TUPLE_H
#define LILITH_TUPLE_H

#include <rttr/variant.h>
#include <utility>
#include <vector>
#include <tuple>
#include <utility>

using namespace rttr;

namespace lilith
{
template <typename... Types> class Tuple
{
public:
    explicit Tuple(const std::tuple<Types...>& tuple) : variants{}
    {
        for (auto i = std::size_t{0}; i < std::tuple_size(tuple); ++i)
            variants.template emplace_back(std::get<i>(tuple));
    }

    explicit Tuple(const std::vector<variant>& vector) : variants{}
    {
        for (const auto& variant : vector)
            variants.template emplace_back(variant);
    }

    template <typename T> [[nodiscard]] T get(std::size_t index)
    {
        if (index >= variants.size())
            throw std::runtime_error("Invalid index.");
        return variants[index].template get_wrapped_value<T>();
    }

    std::vector<variant> variants;
};
}    // namespace lilith

#endif    // LILITH_TUPLE_H
