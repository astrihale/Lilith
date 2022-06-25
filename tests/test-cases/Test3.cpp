#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fakeit.hpp>

using namespace fakeit;

class RandomInterface
{
public:
    virtual void doFooBar() = 0;
};

TEST_CASE("Mock test", "")
{
    Mock<RandomInterface> mock;
    When(Method(mock, doFooBar)).AlwaysDo([&] { std::cout << "doFooBar invoked!" << std::endl; });
    mock.get().doFooBar();
}
