#include "descendants/algorithms/sorts/QuickSort.h"
#include "descendants/printing/ArrayPrinter.h"
#include "descendants/printing/ObjectArrayPrinter.h"

#include <catch2/catch_test_macros.hpp>
#include <plog/Init.h>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

using namespace descendants;
using namespace descendants::algorithms;
using namespace descendants::algorithms::sorts;
using namespace descendants::printing;

class TestObject : public descendants::algorithms::ComparableObject
{
public:
    explicit TestObject(std::int32_t value) : m_value(value) {}

    [[nodiscard]] std::int32_t getValue() const { return m_value; }

    auto operator<=>(const TestObject& right) const { return this->m_value <=> right.m_value; }

    [[nodiscard]] String toString() const { return "{Value: " + std::to_string(m_value) + "}"; }

private:
    std::int32_t m_value;
};

TEST_CASE("QuickSortTesting", "[std::int32_t]")
{
    // Initialize plog
    static auto consoleAppender = plog::ConsoleAppender<plog::TxtFormatter>{};
    plog::init(plog::debug, &consoleAppender);

    // Initialize the algorithm host
    auto algorithm = QuickSort<std::int32_t>{};

    // Common variables
    auto vector = Vector<std::int32_t>{std::int32_t{10}, std::int32_t{80}, std::int32_t{30}, std::int32_t{45},
                                       std::int32_t{40}, std::int32_t{50}, std::int32_t{70}};

    // Combination map
    auto combinations = MultiMap<SortingOrder, QuickSortPivotStrategy>{
      {SortingOrder::Ascending, QuickSortPivotStrategy::First},
      {SortingOrder::Ascending, QuickSortPivotStrategy::Middle},
      {SortingOrder::Ascending, QuickSortPivotStrategy::Last},
      {SortingOrder::Descending, QuickSortPivotStrategy::First},
      {SortingOrder::Descending, QuickSortPivotStrategy::Middle},
      {SortingOrder::Descending, QuickSortPivotStrategy::Last},
    };

    // Make a section for each combination
    SECTION("Sort the vector")
    {
        for (const auto& pair : combinations)
        {
            algorithm.setStrategy(pair.second);
            algorithm.sort(vector, pair.first);
            //            PLOG_DEBUG << ArrayPrinter<std::int32_t>::print(vector);
            REQUIRE(vector.size() == 7);
            for (auto i = std::size_t{0}; i < 6; ++i)
            {
                if (pair.first == SortingOrder::Ascending)
                    REQUIRE(vector[i] <= vector[i + 1]);
                else
                    REQUIRE(vector[i] >= vector[i + 1]);
            }
        }
    }
}

TEST_CASE("QuickSortTesting", "[TestObject]")
{
    // Initialize the algorithm host
    auto algorithm = QuickSort<TestObject>{};

    // Common variables
    auto vector = Vector<TestObject>{TestObject{10}, TestObject{80}, TestObject{30}, TestObject{45},
                                     TestObject{40}, TestObject{50}, TestObject{70}};

    // Combination map
    auto combinations = MultiMap<SortingOrder, QuickSortPivotStrategy>{
      {SortingOrder::Ascending, QuickSortPivotStrategy::First},
      {SortingOrder::Ascending, QuickSortPivotStrategy::Middle},
      {SortingOrder::Ascending, QuickSortPivotStrategy::Last},
      {SortingOrder::Descending, QuickSortPivotStrategy::First},
      {SortingOrder::Descending, QuickSortPivotStrategy::Middle},
      {SortingOrder::Descending, QuickSortPivotStrategy::Last},
    };

    // Make a section for each combination
    SECTION("Sort the vector")
    {
        for (const auto& pair : combinations)
        {
            algorithm.setStrategy(pair.second);
            algorithm.sort(vector, pair.first);
            //            PLOG_DEBUG << ObjectArrayPrinter<TestObject>::print(vector);
            REQUIRE(vector.size() == 7);
            for (auto i = std::size_t{0}; i < 6; ++i)
            {
                if (pair.first == SortingOrder::Ascending)
                    REQUIRE(vector[i] <= vector[i + 1]);
                else
                    REQUIRE(vector[i] >= vector[i + 1]);
            }
        }
    }
}
