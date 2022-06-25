#include <plog/Formatters/TxtFormatter.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Log.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("First test case", "")
{
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);
    PLOG_DEBUG << "Hello World!";
}
