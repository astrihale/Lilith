#include "lilith/parsers/SerializationException.h"

namespace lilith::parsers
{
String toString(SerializationError error)
{
    switch (error)
    {
    case SerializationError::InvalidArgument:
        return "An argument has an invalid value.";
    case SerializationError::InvalidType:
        return "A value is of an invalid type.";
    default:
        return {};
    }
}

SerializationException::SerializationException(SerializationError error)
: std::runtime_error{EXCEPTION_PREFIX + toString(error)}, m_error{error}, m_errorMessage{toString(error)}
{
}

SerializationException::SerializationException(const String& errorMessage)
: std::runtime_error{EXCEPTION_PREFIX + errorMessage}
, m_error{SerializationError::Unknown}
, m_errorMessage{errorMessage}
{
}

SerializationError SerializationException::getError() const
{
    return m_error;
}

const String& SerializationException::getErrorMessage() const
{
    return m_errorMessage;
}

const char* SerializationException::what() const noexcept
{
    return runtime_error::what();
}
}    // namespace lilith::parsers
