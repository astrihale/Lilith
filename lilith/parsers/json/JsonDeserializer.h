#ifndef LILITH_JSONDESERIALIZER_H
#define LILITH_JSONDESERIALIZER_H

#include "lilith/Types.h"
#include "lilith/parsers/SerializationException.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <rttr/registration.h>
#include <rttr/type.h>
#include <rttr/variant.h>

using namespace rttr;

namespace lilith::parsers::json
{
class JsonDeserializer
{
public:
    template <typename T> static T parseObject(const nlohmann::json& json);

private:
    static variant parseField(const rttr::type& type, const nlohmann::json& json);

    static variant parseArithmeticalField(const rttr::type& type, const nlohmann::json& json);

    static variant parseAssociativeContainerField(const rttr::type& type, const nlohmann::json& json);

    static variant parseArrayField(const rttr::type& type, const nlohmann::json& json);

    static variant parseClassField(const rttr::type& type, const nlohmann::json& json);

    static variant parseEnumerationField(const rttr::type& type, const nlohmann::json& json);

    static variant parseWrapperField(const rttr::type& type, const nlohmann::json& json);
};

template <typename T> T JsonDeserializer::parseObject(const nlohmann::json& json)
{
    //    try
    //    {
    const auto& type = rttr::type::get<T>();
    if (!type.is_valid())
        throw SerializationException{SerializationError::InvalidType};
    return parseField(type, json).template get_wrapped_value<T>();
    //    }
    //    catch (const nlohmann::json::exception& exception)
    //    {
    //        throw SerializationException{SerializationError::ErrorWhileParsing};
    //    }
}
}    // namespace lilith::parsers::json

#endif    // LILITH_JSONDESERIALIZER_H
