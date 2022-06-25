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

TEST_CASE("MergeSortTesting", "[TestObject]")
{
    // Initialize the algorithm host
    const auto algorithm = QuickSort<TestObject>{};

    SECTION("Check Merging")
    {
        auto left = std::vector<TestObject>{TestObject{1}, TestObject{2}};
        auto right = std::vector<TestObject>{TestObject{3}, TestObject{4}};
        algorithm.merge(left, right);
        REQUIRE(left.size() == 4);
        auto i = std::int32_t{1};
        for (const auto& value : left)
            REQUIRE(i++ == value.getValue());
    }

    SECTION("Sort First 5 Numbers That Are In Reverse")
    {
        auto vector = Vector<TestObject>{TestObject{5}, TestObject{4}, TestObject{3}, TestObject{2}, TestObject{1}};
        const auto sorted = algorithm.sort(vector, SortingOrder::Ascending);
        REQUIRE(sorted.size() == 5);
        auto i = std::int32_t{1};
        for (const auto& value : sorted)
            REQUIRE(i++ == value.getValue());
    }
}
