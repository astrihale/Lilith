#include "lilith/parsers/json/JsonDeserializer.h"
#include "lilith/parsers/json/JsonSerializer.h"
#include "lilith/Pair.h"
#include "lilith/Tuple.h"

#include <iostream>
#include <vector>

enum class TestEnumeration
{
    FirstValue,
    SecondValue,
    ThirdValue,
    FourthValue
};

class TextObject
{
public:
    TextObject() : m_textField{"Test Value"}, m_intField{623} {}

    [[nodiscard]] const std::string& getTextField() const { return m_textField; }

    void setTextField(const std::string& textField) { m_textField = textField; }

    [[nodiscard]] std::uint32_t getIntField() const { return m_intField; }

    void setIntField(std::uint32_t intField) { m_intField = intField; }

private:
    std::string m_textField;
    std::uint32_t m_intField;
};

RTTR_REGISTRATION
{
    registration::enumeration<TestEnumeration>("TestEnumeration")(
      value("FirstValue", TestEnumeration::FirstValue), value("SecondValue", TestEnumeration::SecondValue),
      value("ThirdValue", TestEnumeration::ThirdValue), value("FourthValue", TestEnumeration::FourthValue));

    registration::class_<std::array<std::int32_t, 3>>("std::array<std::int32_t, 3>").constructor();
    registration::class_<std::vector<std::int32_t>>("std::vector<std::int32_t>").constructor<std::size_t>();
    registration::class_<std::map<std::string, std::int32_t>>("std::map<std::string, std::int32_t>>").constructor();
    registration::class_<std::set<std::int32_t>>("std::set<std::int32_t>").constructor();

    registration::class_<lilith::Pair<std::string, std::uint64_t>>("lilith::Pair<std::string, std::uint64_t>")
      .constructor<std::vector<variant>>()
      .property("variants", &lilith::Pair<std::string, std::uint64_t>::variants);

    registration::class_<lilith::Tuple<std::string, std::uint64_t, bool>>(
      "lilith::Tuple<std::string, std::uint64_t, bool>")
      .constructor<std::vector<variant>>()
      .property("variants", &lilith::Tuple<std::string, std::uint64_t, bool>::variants);

    registration::class_<TextObject>("TextObject")
      .constructor()
      .property("textField", &TextObject::getTextField, &TextObject::setTextField)
      .property("intField", &TextObject::getIntField, &TextObject::setIntField);
}

void NumberExample()
{
    const auto inputJson = nlohmann::json::parse(R"(623)");
    auto number = lilith::parsers::json::JsonDeserializer::parseObject<std::int32_t>(inputJson);
    std::cout << "Number as value: " << number << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(number);
    std::cout << "Number as json: " << outputJson.dump() << std::endl;
}

void StringExample()
{
    const auto inputJson =
      nlohmann::json::parse(R"("And just when it can't get any worse you run out of cigarettes.")");
    auto string = lilith::parsers::json::JsonDeserializer::parseObject<std::string>(inputJson);
    std::cout << "String as value: " << string << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(string);
    std::cout << "String as json: " << outputJson.dump() << std::endl;
}

void TextObjectExample()
{
    const auto inputJson = nlohmann::json::parse(R"({"textField":"HelloWorld!","intField":666})");
    auto text = lilith::parsers::json::JsonDeserializer::parseObject<TextObject>(inputJson);
    std::cout << "TextObject as object: " << std::endl;
    std::cout << "\ttextField = " << text.getTextField() << std::endl;
    std::cout << "\tintField = " << text.getIntField() << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(text);
    std::cout << "TextObject as json: " << std::endl;
    std::cout << outputJson.dump(4) << std::endl;
}

void EnumerationExample()
{
    const auto inputJson = nlohmann::json::parse(R"("ThirdValue")");
    auto enumValue = lilith::parsers::json::JsonDeserializer::parseObject<TestEnumeration>(inputJson);
    std::cout << "TestEnumeration as value: " << static_cast<std::int32_t>(enumValue) << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(enumValue);
    std::cout << "TestEnumeration as json: " << outputJson.dump() << std::endl;
}

void ArrayExample()
{
    const auto inputJson = nlohmann::json::parse(R"([1, 2, 3])");
    auto array = lilith::parsers::json::JsonDeserializer::parseObject<std::array<std::int32_t, 3>>(inputJson);
    std::cout << "IntArray as value: " << std::endl;
    for (auto i = 0; i < 3; ++i)
    {
        std::cout << "\t" << array[i] << std::endl;
    }

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(array);
    std::cout << "IntArray as json: " << outputJson.dump() << std::endl;
}

void VectorExample()
{
    const auto inputJson = nlohmann::json::parse(R"([4, 5, 6])");
    auto vector = lilith::parsers::json::JsonDeserializer::parseObject<std::vector<std::int32_t>>(inputJson);
    std::cout << "Vector as value: " << std::endl;
    for (auto i = std::size_t{0}; i < vector.size(); ++i)
    {
        std::cout << "\t" << vector[i] << std::endl;
    }

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(vector);
    std::cout << "Vector as json: " << outputJson.dump() << std::endl;
}

void MapExample()
{
    const auto inputJson = nlohmann::json::parse(R"({"one":1,"two":2,"three":3})");
    auto map = lilith::parsers::json::JsonDeserializer::parseObject<std::map<std::string, std::int32_t>>(inputJson);
    std::cout << "Map as value: " << std::endl;
    for (const auto& kvp : map)
        std::cout << "\t" << kvp.first << " = " << kvp.second << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(map);
    std::cout << "Map as json: " << outputJson.dump() << std::endl;
}

void SetExample()
{
    const auto inputJson = nlohmann::json::parse(R"([1,2,3])");
    auto set = lilith::parsers::json::JsonDeserializer::parseObject<std::set<std::int32_t>>(inputJson);
    std::cout << "Set as value: " << std::endl;
    for (const auto& kvp : set)
        std::cout << "\t" << kvp << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(set);
    std::cout << "Set as json: " << outputJson.dump() << std::endl;
}

void PairExample()
{
    const auto inputJson = nlohmann::json::parse(R"(["TestString", 623])");
    auto lilithPair =
      lilith::parsers::json::JsonDeserializer::parseObject<lilith::Pair<std::string, std::uint64_t>>(inputJson);
    auto pair = lilithPair.asStdPair();
    std::cout << "Pair as value: " << std::endl;
    std::cout << "\tFirst = " << pair.first << std::endl;
    std::cout << "\tSecond = " << pair.second << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(lilithPair);
    std::cout << "Pair as json: " << outputJson.dump() << std::endl;
}

void TupleExample()
{
    const auto inputJson = nlohmann::json::parse(R"(["TestString", 623, false])");
    auto lilithTuple =
      lilith::parsers::json::JsonDeserializer::parseObject<lilith::Tuple<std::string, std::uint64_t, bool>>(inputJson);
    auto tuple =
      std::make_tuple(lilithTuple.get<std::string>(0), lilithTuple.get<std::uint64_t>(1), lilithTuple.get<bool>(2));
    std::cout << "Tuple as value: " << std::endl;
    std::cout << "\tFirst = " << std::get<0>(tuple) << std::endl;
    std::cout << "\tSecond = " << std::get<1>(tuple) << std::endl;
    std::cout << "\tThird = " << std::get<2>(tuple) << std::endl;

    const auto outputJson = lilith::parsers::json::JsonSerializer::parseObject(lilithTuple);
    std::cout << "Tuple as json: " << outputJson.dump() << std::endl;
}

int main()
{
    NumberExample();
    StringExample();
    TextObjectExample();
    EnumerationExample();
    ArrayExample();
    VectorExample();
    MapExample();
    SetExample();
    PairExample();
    TupleExample();
    return 0;
}
