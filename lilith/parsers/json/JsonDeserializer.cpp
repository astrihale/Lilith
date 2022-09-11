#include "lilith/parsers/json/JsonDeserializer.h"

#include <iostream>

namespace lilith::parsers::json
{
variant JsonDeserializer::parseField(const rttr::type& type, const nlohmann::json& json)
{
    if (!type.is_valid())
        throw SerializationException(SerializationError::InvalidType);
    else if (type.is_arithmetic())
        return parseArithmeticalField(type, json);
    else if (type.is_associative_container())
        return parseAssociativeContainerField(type, json);
    else if (type.is_array() || type.is_sequential_container())
        return parseArrayField(type, json);
    else if (type.is_enumeration())
        return parseEnumerationField(type, json);
    else if (type.is_wrapper() || type.is_pointer())
        return parseWrapperField(type, json);
    else if (type.get_name().to_string().find("std::string") == 0)
        return json.get<std::string>();
    else if (type.is_class())
        return parseClassField(type, json);
    throw SerializationException(SerializationError::InvalidType);
}

variant JsonDeserializer::parseArithmeticalField(const rttr::type& type, const nlohmann::json& json)
{
    const auto& typeName = type.get_name();
    if (typeName == "bool")
        return json.get<bool>();
    else if (typeName == "signedchar")
        return json.get<std::int8_t>();
    else if (typeName == "short")
        return json.get<std::int16_t>();
    else if (typeName == "int")
        return json.get<std::int32_t>();
    else if (typeName == "long" || typeName == "longlong")
        return json.get<std::int64_t>();
    else if (typeName == "unsignedchar")
        return json.get<std::uint8_t>();
    else if (typeName == "unsignedshort")
        return json.get<std::uint16_t>();
    else if (typeName == "unsignedint")
        return json.get<std::uint32_t>();
    else if (typeName == "float")
        return json.get<float>();
    else if (typeName == "double" || typeName == "longdouble")
        return json.get<double>();
    return json.get<std::uint64_t>();
}

variant JsonDeserializer::parseAssociativeContainerField(const rttr::type& type, const nlohmann::json& json)
{
    throw SerializationException(SerializationError::InvalidArgument);
}

variant JsonDeserializer::parseArrayField(const rttr::type& type, const nlohmann::json& json)
{
    const auto parameters = type.get_template_arguments();
    for (const auto& parameter : parameters)
        std::cout << parameter.get_name() << std::endl;
    throw SerializationException(SerializationError::InvalidArgument);
}

variant JsonDeserializer::parseClassField(const rttr::type& type, const nlohmann::json& json)
{
    auto value = type.create();
    if (!value.is_valid())
        throw SerializationException{SerializationError::Unknown};
    for (const auto& property : type.get_properties())
        if (!property.set_value(value, parseField(property.get_type(), json[property.get_name()])))
            throw SerializationException{SerializationError::InvalidArgument};
    return value;
}

variant JsonDeserializer::parseEnumerationField(const rttr::type& type, const nlohmann::json& json)
{
    throw SerializationException(SerializationError::InvalidArgument);
}

variant JsonDeserializer::parseWrapperField(const rttr::type& type, const nlohmann::json& json)
{
    throw SerializationException(SerializationError::InvalidArgument);
}
}    // namespace lilith::parsers::json
