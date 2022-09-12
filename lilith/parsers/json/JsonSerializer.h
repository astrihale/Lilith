#ifndef LILITH_JSONSERIALIZER_H
#define LILITH_JSONSERIALIZER_H

#include "lilith/Types.h"

#include <nlohmann/json.hpp>
#include <optional>
#include <rttr/type.h>
#include <rttr/variant.h>

using namespace rttr;

namespace lilith::parsers::json
{
/**
 * This is the class that parses values using the reflection library.
 * This specific implementation is used to parse values into JSON.
 */
class JsonSerializer
{
public:
    /**
     * This is the method that allows the user to parse any value that is
     * of a type signed with the reflection library.
     *
     * @tparam T The type of the value that should be parsed.
     * @param data The value that should be parsed.
     * @return The parsed value as a json representation.
     */
    template <typename T> static nlohmann::json parseObject(const T& data);

private:
    /**
     * This is the method which will take information about a property and place it in the object.
     *
     * @tparam T The type of the value that should be parsed.
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseField(const variant& variant);

    /**
     * This is the method which will take information about an arithmetical property and place it in the object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseArithmeticalField(const variant& variant);

    /**
     * This is the method which will take information about an associative container property and place it in the
     * object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseAssociativeContainerField(const variant& variant);

    /**
     * This is the method which will take information about an array property and place it in the object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseArrayField(const variant& variant);

    /**
     * This is the method which will take information about a class property and place it in the object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseClassField(const variant& variant);

    /**
     * This is the method which will take information a tuple-like and place it in the object.
     *
     * @param tupleVariant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseTuplelike(const variant& tupleVariant);

    /**
     * This is the method which will take information about an enumeration property and place it in the object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseEnumerationField(const variant& variant);

    /**
     * This is the method which will take information about a wrapper property and place it in the object.
     *
     * @param variant The variant.
     * @return The parsed JSON value.
     */
    static nlohmann::json parseWrapperField(const variant& variant);
};

template <typename T> nlohmann::json JsonSerializer::parseObject(const T& data)
{
    // Check whether the RTTR contains data on the object.
    return type::get(data).is_valid() ? parseField(variant{data}) : nlohmann::json{};
}
}    // namespace lilith::parsers::json

#endif    // LILITH_JSONSERIALIZER_H
