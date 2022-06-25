# Define the project
cmake_minimum_required(VERSION 3.22)
project(Descendants)

# Set the library version
set(DESCENDANTS_MAJOR_VERSION 0)
set(DESCENDANTS_MINOR_VERSION 1)
set(DESCENDANTS_PATCH_VERSION 0)
set(DESCENDANTS_VERSION_SUFFIX "alpha")
set(DESCENDANTS_VERSION "${DESCENDANTS_MAJOR_VERSION}.${DESCENDANTS_MINOR_VERSION}.${DESCENDANTS_PATCH_VERSION}")
if (NOT ${DESCENDANTS_VERSION_SUFFIX} STREQUAL "")
    set(DESCENDANTS_VERSION "${DESCENDANTS_VERSION}-${DESCENDANTS_VERSION_SUFFIX}")
endif ()
configure_file(generate/Version.in ${PROJECT_SOURCE_DIR}/descendants/Version.h)

# Set the paths that are used through out the project
if (NOT SET ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif ()
if (NOT SET ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

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
option(BUILD_SHARED "Build the main library as a shared library." ON)
option(BUILD_TESTS "Build the tests and require testing dependencies." ${BUILD_DEBUG})
option(ENABLE_INSTALL "Whether to enable the install target, and CPack settings for this package." ${BUILD_RELEASE})

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors \
 -Wno-c++98-compat")
if (${BUILD_TESTS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif ()

# Adding the dependencies
include(cmake/dependencies.cmake)

# Decide the library type
if (${BUILD_SHARED})
    set(LIB_TYPE SHARED)
else ()
    set(LIB_TYPE STATIC)
endif ()

# Collect all the files
set(SOURCE_FILE_LIST descendants/Placeholder.cpp)
set(HEADER_FILE_LIST descendants/Placeholder.h
        descendants/Types.h
        descendants/Version.h
        descendants/algorithms/ComparableObject.h
        descendants/algorithms/sorts/SortingAlgorithm.h
        descendants/algorithms/sorts/QuickSort.h)

# Build the library
add_library(${PROJECT_NAME} ${LIB_TYPE})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC plog::plog)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILE_LIST})
target_sources(${PROJECT_NAME} PUBLIC ${HEADER_FILE_LIST})

# If tests need to be built
if (${BUILD_TESTS})
    add_subdirectory(tests)
endif ()

# Enable CPack
if (${ENABLE_INSTALL})
    include(cmake/install.cmake)
    include(cmake/cpack.cmake)
endif ()
