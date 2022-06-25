#include "descendants/algorithms/sorts/QuickSort.h"

#include <catch2/catch_test_macros.hpp>

using namespace descendants;
using namespace descendants::algorithms;
using namespace descendants::algorithms::sorts;

class TestObject : public descendants::algorithms::ComparableObject
{
public:
    explicit TestObject(std::int32_t value) : m_value(value) {}

    [[nodiscard]] std::int32_t getValue() const { return m_value; }

    auto operator<=>(const TestObject& right) const { return this->m_value <=> right.m_value; }

private:
    std::int32_t m_value;
};

TEST_CASE("QuickSortTesting", "[TestObject]")
{
    // Initialize the algorithm host
    auto algorithm = QuickSort<TestObject>{};

    // Common variables
    auto vector = Vector<TestObject>{TestObject{10}, TestObject{80}, TestObject{30}, TestObject{90},
                                     TestObject{40}, TestObject{50}, TestObject{70}};

    SECTION("Sort example array")
    {
        algorithm.sort(vector, SortingOrder::Ascending);
        REQUIRE(vector.size() == 7);
        for (auto i = std::size_t{0}; i < 6; ++i)
            REQUIRE(vector[i] <= vector[i + 1]);
    }

    SECTION("Sort in descending order")
    {
        algorithm.sort(vector, SortingOrder::Descending);
        REQUIRE(vector.size() == 7);
        for (auto i = std::size_t{0}; i < 6; ++i)
            REQUIRE(vector[i] >= vector[i + 1]);
    }
}
