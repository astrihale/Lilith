#ifndef LILITH_SERIALIZATIONEXCEPTION_H
#define LILITH_SERIALIZATIONEXCEPTION_H

#include "lilith/Types.h"

#include <stdexcept>

namespace lilith::parsers
{
/**
 * This is the enumeration describing some basic errors
 * that can happen while an ObjectSerializer serializes an object.
 */
enum class SerializationError
{
    InvalidArgument,
    InvalidType,
    ErrorWhileParsing,
    Unknown,
};

/**
 * This is the utility method that is used to convert a SerializationError into a string value.
 *
 * @param error The error value.
 * @return The string representation of the error value.
 */
String toString(SerializationError error);

/**
 * This is the object that carries information about an error that occurred while serializing an object.
 * It can carry information about a generic SerializationError, or a custom message.
 */
class SerializationException : public std::runtime_error
{
public:
    /**
     * This is the default parameter constructor that takes a generic error.
     *
     * @param error A generic error value.
     */
    explicit SerializationException(SerializationError error);

    /**
     * This is the parameter constructor that takes a custom error.
     *
     * @param errorMessage A custom error message.
     */
    explicit SerializationException(const String& errorMessage);

    /**
     * This is the getter which describes the error that this object describes.
     *
     * @return The error value.
     */
    [[nodiscard]] SerializationError getError() const;

    /**
     * This is the getter for the error message.
     *
     * @return The error message.
     */
    [[nodiscard]] const String& getErrorMessage() const;

    /**
     * This is the overridden method from the `std::runtime_error` class.
     * This is the method which describes the error when handled as an exception.
     *
     * @return The error message.
     */
    [[nodiscard]] const char* what() const _NOEXCEPT override;

private:
    // Make the exception prefix
    inline static const String EXCEPTION_PREFIX = "[SerializationException] -> ";

    // Data the error carries
    SerializationError m_error;
    String m_errorMessage;
};
}    // namespace lilith::parsers

#endif    // LILITH_SERIALIZATIONEXCEPTION_H
