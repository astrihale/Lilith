#include "lilith/Types.h"
#include "lilith/parsers/json/JsonDeserializer.h"
#include "lilith/parsers/json/JsonSerializer.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <rttr/registration.h>
#include <set>

using namespace lilith;
using namespace lilith::parsers;
using namespace rttr;

enum class TestEnumeration
{
    FirstValue,
    SecondValue,
    ThirdValue,
    FourthValue
};

class Point
{
public:
    double x;
    double y;
};

class TextObject
{
public:
    std::string text;
};

struct TestObject
{
    explicit TestObject(Point& point) : refPoint(point) {}

    Point point;
    //    std::unique_ptr<Point> noPoint;
    //    std::unique_ptr<Point> uniquePoint;
    std::shared_ptr<Point> sharedPoint;
    std::reference_wrapper<Point> refPoint;
    TestEnumeration testEnumeration;
    bool b;
    std::int8_t i8;
    std::int16_t i16;
    std::int32_t i32;
    std::int64_t i64;
    std::uint8_t u8;
    std::uint16_t u16;
    std::uint32_t u32;
    std::uint64_t u64;
    signed s;
    signed int si;
    signed long sl;
    signed long int sli;
    signed long long sll;
    signed long long int slli;
    unsigned u;
    unsigned int ui;
    unsigned long ul;
    unsigned long int uli;
    unsigned long long ull;
    unsigned long long int ulli;
    std::float_t sf;
    float f;
    std::double_t sd;
    double d;
    long double ld;
    std::vector<std::int32_t> ints;
    std::int32_t arrayOfInts[3];
    std::map<std::string, std::int32_t> mapOfInts;
    std::map<std::int32_t, std::string> mapOfStrings;
    std::set<std::int32_t> setOfInts;
};

RTTR_REGISTRATION
{
    registration::enumeration<TestEnumeration>("TestEnumeration")(
      value("FirstValue", TestEnumeration::FirstValue), value("SecondValue", TestEnumeration::SecondValue),
      value("ThirdValue", TestEnumeration::ThirdValue), value("FourthValue", TestEnumeration::FourthValue));

    registration::class_<Point>("Point").constructor<>().property("x", &Point::x).property("y", &Point::y);

    registration::class_<TestObject>("TestObject")
      .constructor<Point&>()
      .property("point", &TestObject::point)
      //      .property("noPoint", &TestObject::noPoint)
      //      .property("uniquePoint", &TestObject::uniquePoint)
      .property("sharedPoint", &TestObject::sharedPoint)
      .property("refPoint", &TestObject::refPoint)
      .property("testEnumeration", &TestObject::testEnumeration)
      .property("b", &TestObject::b)
      .property("i8", &TestObject::i8)
      .property("i16", &TestObject::i16)
      .property("i32", &TestObject::i32)
      .property("i64", &TestObject::i64)
      .property("u8", &TestObject::u8)
      .property("u16", &TestObject::u16)
      .property("u32", &TestObject::u32)
      .property("u64", &TestObject::u64)
      .property("s", &TestObject::s)
      .property("si", &TestObject::si)
      .property("sl", &TestObject::sl)
      .property("sli", &TestObject::sli)
      .property("sll", &TestObject::sll)
      .property("slli", &TestObject::slli)
      .property("u", &TestObject::u)
      .property("ui", &TestObject::ui)
      .property("ul", &TestObject::ul)
      .property("uli", &TestObject::uli)
      .property("ull", &TestObject::ull)
      .property("ulli", &TestObject::ulli)
      .property("sf", &TestObject::sf)
      .property("f", &TestObject::f)
      .property("sd", &TestObject::sd)
      .property("d", &TestObject::d)
      .property("ld", &TestObject::ld)
      .property("ints", &TestObject::ints)
      .property("arrayOfInts", &TestObject::arrayOfInts)
      .property("mapOfInts", &TestObject::mapOfInts)
      .property("mapOfStrings", &TestObject::mapOfStrings)
      .property("setOfInts", &TestObject::setOfInts);
};

TEST_CASE("TypeTests")
{
    SECTION("Run sample parse")
    {
        // Try and parse the object
        auto point = Point{10.0, 20.0};
        auto value = TestObject{point};
        value.point = {1.23, 4.56};
        value.ints = {1, 2, 3};
        //        value.uniquePoint = std::make_unique<Point>(12.34, 45.67);
        value.sharedPoint = std::make_shared<Point>();
        value.sharedPoint->x = 1.2;
        value.sharedPoint->y = 3.4;
        value.arrayOfInts[0] = 4;
        value.arrayOfInts[1] = 5;
        value.arrayOfInts[2] = 6;
        value.mapOfInts = {{"One", 1}, {"Two", 2}, {"Three", 3}};
        value.mapOfStrings = {{1, "One"}, {2, "Two"}, {3, "Three"}};
        value.setOfInts = {7, 8, 9};
        const auto parsed = json::JsonSerializer::parseObject(value);
        std::cout << parsed.dump() << std::endl;
    }

    SECTION("Parse a tuple")
    {
        const auto tuple = std::tuple<std::string, std::uint64_t>{"TestValue", 123};
        const auto parsed = json::JsonSerializer::parseTuple(tuple);
        std::cout << parsed.dump() << std::endl;
    }

    SECTION("Deserialize a string")
    {
        const auto string = json::JsonDeserializer::parseObject<std::string>(nlohmann::json::parse("\"HelloWorld!\""));
        REQUIRE(string.has_value());
        REQUIRE(string.value() == "HelloWorld!");
        std::cout << string.value() << std::endl;
    }

    SECTION("Deserialize the point")
    {
        const auto point = json::JsonDeserializer::parseObject<Point>(nlohmann::json::parse(R"({"x":1.0,"y":2.0})"));
        REQUIRE(point.has_value());
        const auto& pointValue = point.value();
        //        REQUIRE(pointValue.x == 1.0);
        //        REQUIRE(pointValue.y == 2.0);
        std::cout << "X: " << pointValue.x << " Y: " << pointValue.y << std::endl;
    }

    SECTION("Deserialize the text")
    {
        const auto textJson = nlohmann::json::parse(R"({"text":"HelloWorld!"})");
        const auto textOpt = json::JsonDeserializer::parseObject<TextObject>(textJson);
        REQUIRE(textOpt.has_value());
        const auto text = textOpt.value();
        REQUIRE(text.text == "HelloWorld!");
    }

    SECTION("Try this manually")
    {
        const auto type = rttr::type::get<Point>();
        auto value = type.create();

        const auto x = type.get_property("x");
        REQUIRE(x.set_value(value, 3.0));

        auto point = value.get_value<Point>();
        std::cout << "Point:" << std::endl;
        std::cout << "\tX = " << point.x << std::endl;
        std::cout << "\tY = " << point.y << std::endl;
        REQUIRE(point.x == 3.0);
        REQUIRE(point.y == 0.0);
    }
}
