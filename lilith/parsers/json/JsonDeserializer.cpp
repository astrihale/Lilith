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
    else if (type.get_name().to_string().find("lilith::Pair") == 0 ||
             type.get_name().to_string().find("lilith::Tuple") == 0)
        return parseTuplelike(type, json);
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
    const auto typeName = type.get_name().to_string();
    const auto keyType = *type.get_template_arguments().begin();

    auto collection = type.create();
    if (!collection.is_valid())
        throw SerializationException{SerializationError::UnregisteredType};
    auto view = collection.create_associative_view();

    if (typeName.find("std::map") == 0 || typeName.find("std::multimap") == 0)
    {
        const auto valueType = *(++type.get_template_arguments().begin());
        for (const auto& item : json.items())
            view.insert(parseField(keyType,
                                   [&]
                                   {
                                       if (keyType.get_name().to_string().find("std::string") == 0)
                                           return nlohmann::json::parse('"' + item.key() + '"');
                                       return nlohmann::json::parse(item.key());
                                   }()),
                        parseField(valueType, item.value()));
    }
    else
    {
        for (const auto& item : json.items())
            view.insert(parseField(keyType,
                                   [&]
                                   {
                                       if (keyType.get_name().to_string().find("std::string") == 0)
                                           return nlohmann::json::parse('"' + item.key() + '"');
                                       return nlohmann::json::parse(item.key());
                                   }()));
    }
    return collection;
}

variant JsonDeserializer::parseArrayField(const rttr::type& type, const nlohmann::json& json)
{
    const auto typeName = type.get_name().to_string();
    auto array = [&]
    {
        if (typeName.find("std::array") == 0)
            return type.create();
        return type.create({json.size()});
    }();
    if (!array.is_valid())
        throw SerializationException{SerializationError::UnregisteredType};
    auto view = array.create_sequential_view();
    auto start = 0;
    for (const auto& item : json.items())
        view.set_value(start++, parseField(*type.get_template_arguments().begin(), item.value()));
    return array;
}

variant JsonDeserializer::parseClassField(const rttr::type& type, const nlohmann::json& json)
{
    auto value = type.create();
    if (!value.is_valid())
        throw SerializationException{SerializationError::UnregisteredType};
    for (const auto& property : type.get_properties())
        if (!property.set_value(value, parseField(property.get_type(), json[property.get_name()])))
            throw SerializationException{SerializationError::InvalidArgument};
    return value;
}

variant JsonDeserializer::parseTuplelike(const rttr::type& type, const nlohmann::json& json)
{
    auto variants = std::vector<variant>{};
    auto currentType = type.get_template_arguments().begin();
    for (const auto& item : json.items())
        variants.emplace_back(parseField(*(currentType++), item.value()));
    auto value = type.create({variants});
    if (!value.is_valid())
        throw SerializationException{SerializationError::UnregisteredType};
    return value;
}

variant JsonDeserializer::parseEnumerationField(const rttr::type& type, const nlohmann::json& json)
{
    return type.get_enumeration().name_to_value(json.get<std::string>());
}

variant JsonDeserializer::parseWrapperField(const rttr::type& type, const nlohmann::json& json)
{
    return parseField(type.get_wrapped_type(), json);
}
}    // namespace lilith::parsers::json
