#ifndef DESCENDANTS_QUICKSORT_H
#define DESCENDANTS_QUICKSORT_H

#include "descendants/algorithms/sorts/SortingAlgorithm.h"

#include <compare>
#include <plog/Log.h>

namespace descendants::algorithms::sorts
{
/**
 * This is the mode setting for QuickSort which decides in which way the
 * pivot is chosen.
 */
enum class QuickSortPivot
{
    First,
    Middle,
    Last
};

/**
 * This is the implementation of the QuickSort algorithm.
 *
 * @tparam T The type of the value being compared by this sorting algorithm.
 */
template <Comparable T> class QuickSort : public SortingAlgorithm<T>
{
public:
    /**
     * Default parameter constructor for the sorting algorithm.
     * @param pivot The way the pivot is chosen in sorting.
     */
    explicit QuickSort(QuickSortPivot pivot = QuickSortPivot::First);

    /**
     * This is the getter for the strategy this sorting is using for picking a pivot.
     *
     * @return The pivot strategy.
     */
    [[nodiscard]] QuickSortPivot getPivot() const;

    /**
     * This is the setter for the strategy this soring is using for picking a pivot.
     *
     * @param pivot The new pivot strategy.
     */
    void setPivot(QuickSortPivot pivot);

    /**
     * This is the method which will sort the received vector using the QuickSort.
     *
     * @param original The original vector containing values.
     * @param order The order in which the values should be sorted.
     * @return The vector containing sorted values.
     */
    [[nodiscard]] Vector<T> sort(const Vector<T>& original, SortingOrder order) const override;

    /**
     * This is the method that adds all the elements from the right vector into the left.
     *
     * @param left The vector in which the values are added.
     * @param right The values that are copied into the vector.
     */
    void merge(Vector<T>& left, const Vector<T>& right) const;

private:
    /**
     * This is an internal method that is used to decide on the pivot index.
     *
     * @param vector The vector for which the pivot is being decided on.
     * @return The pivot index.
     */
    std::size_t decidePivot(const Vector<T>& vector) const;

    // Stored property which decides in which way the sort will choose the pivot.
    QuickSortPivot m_pivot;
};

// Implementation
template <Comparable T> QuickSort<T>::QuickSort(QuickSortPivot pivot) : m_pivot{pivot} {}

template <Comparable T> QuickSortPivot QuickSort<T>::getPivot() const
{
    return m_pivot;
}

template <Comparable T> void QuickSort<T>::setPivot(QuickSortPivot pivot)
{
    m_pivot = pivot;
}

template <Comparable T> Vector<T> QuickSort<T>::sort(const Vector<T>& original, SortingOrder order) const
{
    // Check whether we reached the end of the sort
    if (original.empty() || original.size() == 1)
        return original;

    // Decide the pivot
    const auto pivotIndex = decidePivot(original);
    const auto pivot = original[pivotIndex];

    // Split the elements on the left and the right
    auto left = Vector<T>{};
    auto right = Vector<T>{};
    for (auto i = std::size_t{0}; i < original.size(); ++i)
    {
        // Skip the pivot
        if (i == pivotIndex)
            continue;
        const auto& value = original[i];

        // Compare the value
        if (value < pivot)
            left.emplace_back(value);
        else
            right.emplace_back(value);
    }

    // Sort the elements
    left = sort(left, order);
    right = sort(right, order);

    // Assemble the array back
    left.emplace_back(pivot);
    merge(left, right);
    return left;
}

template <Comparable T> void QuickSort<T>::merge(Vector<T>& left, const Vector<T>& right) const
{
    for (const auto& value : right)
        left.emplace_back(value);
}

template <Comparable T> std::size_t QuickSort<T>::decidePivot(const Vector<T>& vector) const
{
    switch (m_pivot)
    {
    case QuickSortPivot::First:
        return 0;
    case QuickSortPivot::Middle:
        return vector.size() / 2;
    case QuickSortPivot::Last:
        return vector.size() - 1;
    default:
        throw std::runtime_error("QuickSort: Failed to decide on a pivot - The strategy value is invalid!");
    }
}
}    // namespace descendants::algorithms::sorts

#endif    // DESCENDANTS_QUICKSORT_H
