#include "descendants/Version.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Second test case", "")
{
    std::cout << "The library version is: '" << descendants::Version::getVersion() << "'." << std::endl;
}
