#include "lilith/parsers/json/JsonDeserializer.h"
#include "lilith/parsers/json/JsonSerializer.h"

#include <iostream>
#include <string>

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

int main()
{
    NumberExample();
    StringExample();
    TextObjectExample();

    return 0;
}
