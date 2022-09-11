#ifndef LILITH_MSGPACKPARSER_H
#define LILITH_MSGPACKPARSER_H

#include "lilith/Types.h"

#include <msgpack.h>
#include <rttr/type.h>
#include <rttr/variant.h>

using namespace rttr;

namespace lilith::parsers::msgpack
{
/**
 * This is the class that parses objects using the reflection library.
 * This specific implementation is used to parse objects into MsgPack.
 */
class MsgPackParser
{
public:
    /**
     * This is the method that allows the user to parse any object that is
     * of a type signed with the reflection library.
     *
     * @tparam T The type of the object that should be parsed.
     * @param data The object that should be parsed.
     * @return The parsed object as a msgpack object.
     */
    template <typename T> static msgpack_object parseObject(const T& data);

private:
};

template <typename T> msgpack_object MsgPackParser::parseObject(const T& data)
{
    return msgpack_object();
}
}    // namespace lilith::parsers::msgpack

#endif    // LILITH_MSGPACKPARSER_H
