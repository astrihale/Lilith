#ifndef DESCENDANTS_JSONPARSER_H
#define DESCENDANTS_JSONPARSER_H

#include "descendants/Types.h"

#include <nlohmann/json.hpp>
#include <plog/Log.h>
#include <rttr/type.h>
#include <rttr/variant.h>

using namespace rttr;

namespace descendants::parsers
{
/**
 * This is the class that parses objects using the reflection library.
 */
class JsonParser
{
public:
    /**
     * This is the method that allows the user to parse any object that is
     * of a type signed with the reflection library.
     *
     * @tparam T The type of the object that should be parsed.
     * @param data The object that should be parsed.
     * @return The parsed object as a string.
     */
    template <typename T> static String parseObject(const T& data);

private:
    /**
     * This is the method which will take information about a property and place it in the object.
     *
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

template <typename T> String JsonParser::parseObject(const T& data)
{
    // Check whether the RTTR contains data on the object.
    const auto type = type::get(data);
    if (!type.is_valid())
        return {};

    // Go through every property
    auto json = nlohmann::json{};
    for (const auto& property : type.get_properties())
        json[property.get_name().to_string()] = parseField(property.get_value(data));
    return json.dump();
}

nlohmann::json JsonParser::parseField(const variant& variant)
{
    const auto& type = variant.get_type();
    if (!type.is_valid())
        return nlohmann::json{};
    else if (type.is_arithmetic())
        return parseArithmeticalField(variant);
    else if (type.is_associative_container())
        return parseAssociativeContainerField(variant);
    else if (type.is_array() || type.is_sequential_container())
        return parseArrayField(variant);
    else if (type.is_enumeration())
        return parseEnumerationField(variant);
    else if (type.is_wrapper() || type.is_pointer())
        return parseWrapperField(variant);
    else if (type.get_name().to_string().find("string") != std::string::npos)
        return variant.to_string();
    else if (type.is_class())
        return parseClassField(variant);
    return nlohmann::json{};
}

nlohmann::json JsonParser::parseArithmeticalField(const variant& variant)
{
    const auto& typeName = variant.get_type().get_name().to_string();
    if (typeName == "bool")
        return variant.to_bool();
    else if (typeName == "signedchar")
        return variant.to_int8();
    else if (typeName == "short")
        return variant.to_int16();
    else if (typeName == "int")
        return variant.to_int32();
    else if (typeName == "long" || typeName == "longlong")
        return variant.to_int64();
    else if (typeName == "unsignedchar")
        return variant.to_uint8();
    else if (typeName == "unsignedshort")
        return variant.to_uint16();
    else if (typeName == "unsignedint")
        return variant.to_uint32();
    else if (typeName == "float")
        return variant.to_float();
    else if (typeName == "double" || typeName == "longdouble")
        return variant.to_double();
    return variant.to_uint64();
}

nlohmann::json JsonParser::parseAssociativeContainerField(const variant& variant)
{
    const auto& typeName = variant.get_type().get_name().to_string();
    if (typeName.find("set") != std::string::npos)
    {
        // Make an array
        auto array = nlohmann::json::array();
        for (const auto& element : variant.create_associative_view())
            array += parseField(element.first);
        return array;
    }
    else if (typeName.find("map") != std::string::npos)
    {
        // Make an object
        auto object = nlohmann::json{};
        for (const auto& element : variant.create_associative_view())
            object[element.first.to_string()] = parseField(element.second);
        return object;
    }
    return nlohmann::json{};
}

nlohmann::json JsonParser::parseArrayField(const variant& variant)
{
    // Take the array
    auto array = nlohmann::json::array();
    for (const auto& element : variant.create_sequential_view())
        array += parseField(element);
    return array;
}

nlohmann::json JsonParser::parseClassField(const variant& variant)
{
    // Take the info about the type
    const auto& type = variant.get_type();
    auto object = nlohmann::json{};
    for (const auto& property : type.get_properties())
        object[property.get_name().to_string()] = parseField(property.get_value(variant));
    return object;
}

nlohmann::json JsonParser::parseEnumerationField(const variant& variant)
{
    // Take the enumeration type
    return variant.to_string();
}

nlohmann::json JsonParser::parseWrapperField(const variant& variant)
{
    // Extract the wrapped value
    return parseField(variant.extract_wrapped_value());
}
}    // namespace descendants::parsers

#endif    // DESCENDANTS_JSONPARSER_H
