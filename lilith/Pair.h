#ifndef LILITH_PAIR_H
#define LILITH_PAIR_H

#include <rttr/registration.h>
#include <rttr/variant.h>

#include <utility>

using namespace rttr;

namespace lilith
{
template <typename X, typename Y> class Pair
{
public:
    Pair(const X& key, const Y& value) : variants{key, value} {}

    Pair(const std::pair<X, Y>& pair) : variants{pair.first, pair.second} {}

    Pair(const std::vector<variant>& variants) : variants{variants[0], variants[1]} {}

    [[nodiscard]] std::pair<X, Y> asStdPair() const
    {
        return std::make_pair(variants[0].template get_wrapped_value<X>(), variants[1].template get_wrapped_value<Y>());
    }

    std::vector<variant> variants;
};
}    // namespace lilith

#endif    // LILITH_PAIR_H
