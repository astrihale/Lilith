#ifndef DESCENDANTS_JSONPARSER_H
#define DESCENDANTS_JSONPARSER_H

#include "descendants/Types.h"

#include <nlohmann/json.hpp>
#include <plog/Log.h>
#include <rttr/type.h>

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
     * This is the method which will take information about a property and
     * place it in the object.
     *
     * @tparam T The type of the object that should be parsed.
     * @param data The object that should be parsed.
     * @param json The object in which the information should be added.
     * @param property The property information.
     */
    template <typename T> static void parseField(const T& data, nlohmann::json& json, const property& property);
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
        parseField(data, json, property);
    return json.dump();
}

template <typename T> void JsonParser::parseField(const T& data, nlohmann::json& json, const property& property)
{
    const auto typeName = property.get_type().get_name().to_string();
    if (typeName == "std::string")
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_string();
    else if (typeName.find("uint") != std::string::npos)
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_uint64();
    else if (typeName.find("int") != std::string::npos)
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_int64();
    else if (typeName == "float")
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_float();
    else if (typeName == "double")
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_double();
    else if (typeName == "bool")
        json[std::string{property.get_name().to_string()}] = property.get_value(data).to_bool();
}
}    // namespace descendants::parsers

#endif    // DESCENDANTS_JSONPARSER_H
