#ifndef DESCENDANTS_QUICKSORT_H
#define DESCENDANTS_QUICKSORT_H

#include "descendants/algorithms/sorts/SortingAlgorithm.h"

#include <compare>
#include <plog/Log.h>

namespace descendants::algorithms::sorts
{
/**
 * This is the implementation of the QuickSort algorithm.
 *
 * @tparam T The type of the value being compared by this sorting algorithm.
 */
template <Comparable T> class QuickSort : public SortingAlgorithm<T>
{
public:
    /**
     * This is the method that actually sorts on the vector that is passed.
     *
     * @param vector The vector which should be sorted.
     * @param order The order in which the values will be ordered.
     */
    void sort(Vector<T>& vector, SortingOrder order) const override;

private:
    /**
     * This is the internal recursive method that is invoked to sort the vector.
     *
     * @param vector The vector which should be sorted.
     * @param order The order in which the values will be ordered.
     * @param start The starting index from which the vector should be sorted.
     * @param end The ending index to which the vector should be sorted.
     */
    void internalSort(Vector<T>& vector, SortingOrder order, std::size_t start, std::size_t end) const;

    /**
     * This is the internal sort sub-method that will reorder the vector in such a way that any values
     * lesser/bigger than the pivot will be placed left, and other ones will be placed right of the pivot.
     *
     * @param vector The vector which should be sorted.
     * @param order The order in which the values will be ordered.
     * @param start The starting index from which the vector should be partitioned.
     * @param end The ending index to which the vector should be partitioned.
     * @return The position of the pivot after partitioning.
     */
    [[nodiscard]] std::size_t partitionVector(Vector<T>& vector, SortingOrder order, std::size_t start,
                                              std::size_t end) const;

    /**
     * This is the internal method that will take into account sorting settings, and figure out the index of the value
     * to use for the pivot.
     *
     * @param start The earliest index used for current partitioning.
     * @param end The latest index used for current partitioning.
     * @return The initial index of the pivot.
     */
    [[nodiscard]] std::size_t decidePivotIndex(std::size_t start, std::size_t end) const;

    /**
     * This is the internal method that is used for swapping the values between two positions in the vector.
     *
     * @param vector The vector in which values need to change positions.
     * @param first The first position in the swap.
     * @param second The second position in the swap.
     */
    void swap(Vector<T>& vector, std::size_t first, std::size_t second) const;

    /**
     * This is the internal method that is used to generate the comparison predicate used when partitioning.
     *
     * @return The comparison predicate.
     */
    [[nodiscard]] Lambda<bool(const T&, const T&)> makeComparisonPredicate(SortingOrder order) const;
};

// Implementation

template <Comparable T> void QuickSort<T>::sort(Vector<T>& vector, SortingOrder order) const
{
    // Check the vector size
    if (vector.size() < 2)
        return;

    // Invoke the internal recursive method
    internalSort(vector, order, 0, vector.size() - 1);
}

template <Comparable T>
void QuickSort<T>::internalSort(Vector<T>& vector, SortingOrder order, std::size_t start, std::size_t end) const
{
    // Check for the exit condition
    if (start >= end)
        return;

    // Partition the vector
    const auto index = partitionVector(vector, order, start, end);
    internalSort(vector, order, start, index > 0 ? index - 1 : 0);
    internalSort(vector, order, index + 1, end);
}

template <Comparable T>
std::size_t QuickSort<T>::partitionVector(Vector<T>& vector, SortingOrder order, std::size_t start,
                                          std::size_t end) const
{
    // Figure out the initial index of the pivot
    const auto compare = makeComparisonPredicate(order);
    const auto pivotIndex = end;
    const auto pivotValue = vector[pivotIndex];

    // Decide the swapping index
    auto swappingIndex = start + (pivotIndex == start ? 1 : 0);
    for (auto i = std::size_t{start}; i <= end; i++)
    {
        // If the counter is currently on the pivot, just continue
        if (i == pivotIndex)
            continue;

        // Now check the value
        if (compare(vector[i], pivotValue))
            swap(vector, i, swappingIndex++);
    }

    // Swap the first larger valuer value with the pivot
    swap(vector, swappingIndex, pivotIndex);
    return swappingIndex;
}

template <Comparable T> void QuickSort<T>::swap(Vector<T>& vector, std::size_t first, std::size_t second) const
{
    // Check that the indexes are actually different
    if (first == second)
        return;

    // Swap the values
    auto temporary = vector[first];
    vector[first] = vector[second];
    vector[second] = temporary;
}

template <Comparable T> Lambda<bool(const T&, const T&)> QuickSort<T>::makeComparisonPredicate(SortingOrder order) const
{
    if (order == SortingOrder::Ascending)
        return [](const T& left, const T& right) { return left < right; };
    else
        return [](const T& left, const T& right) { return left > right; };
}
}    // namespace descendants::algorithms::sorts

#endif    // DESCENDANTS_QUICKSORT_H
