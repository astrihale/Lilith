#include "lilith/parsers/json/JsonSerializer.h"

#include <sstream>

namespace lilith::parsers::json
{
nlohmann::json JsonSerializer::parseField(const variant& variant)
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
    else if (type.get_name().to_string().find("std::string") == 0)
        return variant.to_string();
    else if (type.is_class())
        return parseClassField(variant);
    return nlohmann::json{};
}

nlohmann::json JsonSerializer::parseArithmeticalField(const variant& variant)
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

nlohmann::json JsonSerializer::parseAssociativeContainerField(const variant& variant)
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

nlohmann::json JsonSerializer::parseArrayField(const variant& variant)
{
    // Take the array
    auto array = nlohmann::json::array();
    for (const auto& element : variant.create_sequential_view())
        array += parseField(element);
    return array;
}

nlohmann::json JsonSerializer::parseClassField(const variant& variant)
{
    // Take the info about the type
    const auto& type = variant.get_type();
    auto object = nlohmann::json{};
    for (const auto& property : type.get_properties())
        object[property.get_name().to_string()] = parseField(property.get_value(variant));
    return object;
}

nlohmann::json JsonSerializer::parseEnumerationField(const variant& variant)
{
    // Take the enumeration type
    return variant.to_string();
}

nlohmann::json JsonSerializer::parseWrapperField(const variant& variant)
{
    // Extract the wrapped value
    return parseField(variant.extract_wrapped_value());
}
}    // namespace lilith::parsers::json
