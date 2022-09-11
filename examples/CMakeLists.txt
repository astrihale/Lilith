# Define the project
cmake_minimum_required(VERSION 3.16)
project(LilithExamples)

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors \
 -Wno-c++98-compat -Wno-unused-parameter -Wno-deprecated-copy-with-user-provided-copy -Wno-dtor-name")

# First example
add_executable(${PROJECT_NAME}_DeserializationExample)
target_link_directories(${PROJECT_NAME}_DeserializationExample PUBLIC ${CMAKE_PREFIX_PATH}/lib)
target_include_directories(${PROJECT_NAME}_DeserializationExample PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_DeserializationExample PUBLIC ${CMAKE_BINARY_DIR}/include ${CMAKE_PREFIX_PATH}/include)
target_link_libraries(${PROJECT_NAME}_DeserializationExample Lilith)
target_sources(${PROJECT_NAME}_DeserializationExample PRIVATE deserialization/DeserializationExample.cpp)
set_target_properties(${PROJECT_NAME}_DeserializationExample PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
