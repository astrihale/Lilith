# Define the project
cmake_minimum_required(VERSION 3.22)
project(DescendantsTests)

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors \
 -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-documentation-unknown-command \
 -Wno-covered-switch-default -Wno-switch-enum -Wno-sign-conversion -Wno-double-promotion -Wno-old-style-cast \
 -Wno-extra-semi -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-suggest-destructor-override \
 -Wno-inconsistent-missing-destructor-override -Wno-global-constructors -Wno-redundant-parens \
 -Wno-zero-as-null-pointer-constant -Wno-zero-length-array -Wno-weak-vtables -Wno-shorten-64-to-32 \
 -Wno-disabled-macro-expansion -Wno-suggest-override")

# Obtain the dependencies
include(FetchContent)

# Catch2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.0.1
)
FetchContent_GetProperties(Catch2)
if (NOT Catch2_POPULATED)
    FetchContent_MakeAvailable(Catch2)
endif ()

# FakeIt
FetchContent_Declare(
        FakeIt
        GIT_REPOSITORY https://github.com/libenike/FakeIt
        GIT_TAG feature/add_cmake_support
)
FetchContent_GetProperties(FakeIt)
if (NOT FakeIt_POPULATED)
    FetchContent_MakeAvailable(FakeIt)
endif ()

# Collect the tests files
set(TESTS_FILE_LIST test-cases/QuickSortTesting.cpp
        test-cases/Test.cpp
        test-cases/Test2.cpp
        test-cases/Test3.cpp)

# Make the tests executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${TESTS_FILE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE FakeIt::FakeIt Catch2::Catch2WithMain Descendants)
include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
