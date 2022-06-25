#ifndef DESCENDANTS_SORTINGALGORITHM_H
#define DESCENDANTS_SORTINGALGORITHM_H

#include "descendants/algorithms/ComparableObject.h"
#include "descendants/Types.h"

namespace descendants::algorithms::sorts
{
/**
 * This is the enumeration flag used for sort calls to tell whether the sort should be done
 * in ascending or descending order.
 */
enum class SortingOrder
{
    Ascending,
    Descending
};

/**
 * This is the interface for an implementation of a sorting algorithm.
 */
template <Comparable T> class SortingAlgorithm
{
public:
    /**
     * Default virtual destructor.
     */
    virtual ~SortingAlgorithm() = default;

    /**
     * This is the method that does the sorting of a vector.
     *
     * @param original The original vector of values that needs to be sorted.
     * @param order The order in which values should be sorted.
     * @return The new copy containing elements in the sorted order.
     */
    virtual Vector<T> sort(const Vector<T>& original, SortingOrder order) const = 0;
};
}    // namespace descendants::algorithms::sorts

#endif    // DESCENDANTS_SORTINGALGORITHM_H
