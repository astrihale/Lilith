#ifndef LILITH_JSONPARSER_H
#define LILITH_JSONPARSER_H

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
class JsonParser
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

    /**
     * This is the method that allows the user to parse a pair value.
     *
     * @param pair The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B> static nlohmann::json parsePair(const std::pair<A, B>& pair);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A> static nlohmann::json parseTuple(const std::tuple<A>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B> static nlohmann::json parseTuple(const std::tuple<A, B>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C> static nlohmann::json parseTuple(const std::tuple<A, B, C>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E, typename F>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E, F>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E, typename F, typename G>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E, F, G>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E, F, G, H>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
              typename I>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E, F, G, H, I>& tuple);

    /**
     * This is the method that allows the user to parse a tuple value.
     *
     * @param tuple The value.
     * @return The parsed values as a json representation.
     */
    template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
              typename I, typename J>
    static nlohmann::json parseTuple(const std::tuple<A, B, C, D, E, F, G, H, I, J>& tuple);

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

template <typename T> nlohmann::json JsonParser::parseObject(const T& data)
{
    // Check whether the RTTR contains data on the object.
    return type::get(data).is_valid() ? parseField(variant{data}) : nlohmann::json{};
}

template <typename A, typename B> nlohmann::json JsonParser::parsePair(const std::pair<A, B>& pair)
{
    return nlohmann::json{parseField(std::get<0>(pair), std::get<1>(pair))};
}

template <typename A> nlohmann::json JsonParser::parseTuple(const std::tuple<A>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple))};
}

template <typename A, typename B> nlohmann::json JsonParser::parseTuple(const std::tuple<A, B>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple))};
}

template <typename A, typename B, typename C> nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple))};
}

template <typename A, typename B, typename C, typename D>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple)),
                          parseField(std::get<4>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E, typename F>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E, F>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple)),
                          parseField(std::get<4>(tuple)), parseField(std::get<5>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E, typename F, typename G>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E, F, G>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple)),
                          parseField(std::get<4>(tuple)), parseField(std::get<5>(tuple)),
                          parseField(std::get<6>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E, F, G, H>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple)),
                          parseField(std::get<4>(tuple)), parseField(std::get<5>(tuple)),
                          parseField(std::get<6>(tuple)), parseField(std::get<7>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E, F, G, H, I>& tuple)
{
    return nlohmann::json{
      parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)), parseField(std::get<2>(tuple)),
      parseField(std::get<3>(tuple)), parseField(std::get<4>(tuple)), parseField(std::get<5>(tuple)),
      parseField(std::get<6>(tuple)), parseField(std::get<7>(tuple)), parseField(std::get<8>(tuple))};
}

template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
          typename J>
nlohmann::json JsonParser::parseTuple(const std::tuple<A, B, C, D, E, F, G, H, I, J>& tuple)
{
    return nlohmann::json{parseField(std::get<0>(tuple)), parseField(std::get<1>(tuple)),
                          parseField(std::get<2>(tuple)), parseField(std::get<3>(tuple)),
                          parseField(std::get<4>(tuple)), parseField(std::get<5>(tuple)),
                          parseField(std::get<6>(tuple)), parseField(std::get<7>(tuple)),
                          parseField(std::get<8>(tuple)), parseField(std::get<9>(tuple))};
}
}    // namespace lilith::parsers::json

#endif    // LILITH_JSONPARSER_H
