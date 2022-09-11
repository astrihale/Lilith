# Define the project
cmake_minimum_required(VERSION 3.16)
project(Lilith)

# Set the library version
set(LILITH_MAJOR_VERSION 0)
set(LILITH_MINOR_VERSION 1)
set(LILITH_PATCH_VERSION 0)
set(LILITH_VERSION_SUFFIX "alpha")
set(LILITH_VERSION "${LILITH_MAJOR_VERSION}.${LILITH_MINOR_VERSION}.${LILITH_PATCH_VERSION}")
if (NOT ${LILITH_VERSION_SUFFIX} STREQUAL "")
    set(LILITH_VERSION "${LILITH_VERSION}-${LILITH_VERSION_SUFFIX}")
endif ()
configure_file(generate/Version.in ${PROJECT_SOURCE_DIR}/lilith/Version.h)

# Set the paths that are used through out the project
if (NOT SET ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif ()
if (NOT SET ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()
if (NOT SET ${CMAKE_PREFIX_PATH})
    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/build)
endif ()
link_directories(${CMAKE_PREFIX_PATH}/lib)

# Define the options that should affect the library
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(BUILD_DEBUG ON)
else ()
    set(BUILD_DEBUG OFF)
endif ()
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(BUILD_RELEASE ON)
else ()
    set(BUILD_RELEASE OFF)
endif ()
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    set(ROOT_PROJECT ON)
else ()
    set(ROOT_PROJECT OFF)
endif ()
option(BUILD_SHARED "Build the main library as a shared library." ON)
option(BUILD_TESTS "Build the tests and require testing dependencies." ${BUILD_DEBUG})
option(BUILD_DEFAULT_LOGGER "Build the default logger implementation." ${ROOT_PROJECT})
option(ENABLE_INSTALL "Whether to enable the install target, and CPack settings for this package." ${BUILD_RELEASE})
if (${BUILD_DEFAULT_LOGGER})
    add_compile_definitions(DEFAULT_LOGGER)
endif ()

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors \
 -Wno-c++98-compat -Wno-unused-parameter -Wno-deprecated-copy-with-user-provided-copy -Wno-dtor-name")

# Adding the dependencies
include(cmake/dependencies.cmake)

# Decide the library type
if (${BUILD_SHARED})
    set(LIB_TYPE SHARED)
else ()
    set(LIB_TYPE STATIC)
endif ()

# Collect all the files
set(SOURCE_FILE_LIST lilith/parsers/json/JsonParser.cpp
        lilith/parsers/msgpack/MsgPackParser.cpp
        lilith/parsers/SerializationException.cpp)
set(HEADER_FILE_LIST lilith/Types.h
        lilith/Version.h
        lilith/parsers/SerializationException.h
        lilith/parsers/json/JsonParser.h
        lilith/parsers/msgpack/MsgPackParser.h)

# Build the library
add_library(${PROJECT_NAME} ${LIB_TYPE})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_PREFIX_PATH}/lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/include ${CMAKE_PREFIX_PATH}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC rttr_core)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILE_LIST})
target_sources(${PROJECT_NAME} PUBLIC ${HEADER_FILE_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN")
add_dependencies(${PROJECT_NAME} msgpack nlohmann rttr)

# If tests need to be built
if (${BUILD_TESTS})
    add_subdirectory(tests)
endif ()

# Enable CPack
if (${ENABLE_INSTALL})
    include(cmake/install.cmake)
    include(cmake/cpack.cmake)
endif ()
