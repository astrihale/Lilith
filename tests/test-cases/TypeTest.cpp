#include "descendants/Types.h"
#include "descendants/parsers/JsonParser.h"

#include <catch2/catch_test_macros.hpp>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Log.h>
#include <plog/Init.h>
#include <rttr/registration>

using namespace descendants;
using namespace descendants::parsers;
using namespace rttr;

struct TestObject
{
    void TestMethod() {}
    [[nodiscard]] static std::int32_t TestFunction() { return 1; }

    String field;
    std::int32_t property;
};

RTTR_REGISTRATION
{
    registration::class_<TestObject>("TestObject")
      .constructor<>()
      .property("field", &TestObject::field)
      .property("property", &TestObject::property)
      .method("TestMethod", &TestObject::TestMethod)
      .method("TestFunction", &TestObject::TestFunction);
};

TEST_CASE("TypeTests")
{
    static auto console = plog::ConsoleAppender<plog::TxtFormatter>();
    plog::init(plog::debug, &console);

    // Try and parse the object
    auto value = TestObject{};
    value.property = 33;
    value.field = "Test Object!";
    const auto parsed = JsonParser::parseObject(value);
    PLOG_DEBUG << "Parsed object: '" << parsed << "'.";
}
