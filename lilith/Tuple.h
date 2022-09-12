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
    Tuple(const std::tuple<Types...>& tuple)
    {
        for (auto i = std::size_t{0}; i < std::tuple_size(tuple); ++i)
            variants.template emplace_back(std::get<i>(tuple));
    }

    Tuple(std::vector<variant> variants) : variants{std::move(variants)} {}

    template <std::size_t i, typename... TypeList> decltype(auto) getType(TypeList... types)
    {
        return std::get<i>(std::forward_as_tuple(types...));
    }

    template <typename T> [[nodiscard]] T get(std::size_t index)
    {
        return variants[index].template get_wrapped_value<T>();
    }

    std::vector<variant> variants;
};
}    // namespace lilith

#endif    // LILITH_TUPLE_H
