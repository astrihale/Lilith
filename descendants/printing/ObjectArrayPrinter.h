#ifndef DESCENDANTS_OBJECTARRAYPRINTER_H
#define DESCENDANTS_OBJECTARRAYPRINTER_H

#include "descendants/Types.h"
#include "descendants/printing/Printable.h"

namespace descendants::printing
{
/**
 * This class contains a static method which is able to convert any Vector containing printable elements into a single
 * printable string.
 * @tparam T The type of the elements of the vector that should be printed.
 */
template <PrintableObject T> class ObjectArrayPrinter
{
public:
    /**
     * This is the method which will present a vector as a string.
     *
     * @param vector The vector containing the elements.
     * @param elementPerLine Whether to print every line in a separate line.
     * @return The string containing the representation of the vector.
     */
    static String print(const Vector<T>& vector, bool elementPerLine = false);
};

template <PrintableObject T> String ObjectArrayPrinter<T>::print(const Vector<T>& vector, bool elementPerLine)
{
    // Make the string stream
    auto stream = StringStream{};
    stream << "[";

    // Add in all the elements
    for (auto i = std::size_t{0}; i < vector.size(); ++i)
    {
        if (elementPerLine)
            stream << "\n\t";
        stream << vector[i].toString();
        if (i < vector.size() - 1)
            stream << ", ";
    }

    // Add the end of the vector
    if (elementPerLine && !vector.empty())
        stream << "\n";
    stream << "]";
    return stream.str();
}
}    // namespace descendants::printing

#endif    // DESCENDANTS_OBJECTARRAYPRINTER_H
