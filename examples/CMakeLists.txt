# Define the project
cmake_minimum_required(VERSION 3.16)
project(LilithExamples)

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# First example
add_executable(${PROJECT_NAME}_ParsingExample)
target_link_directories(${PROJECT_NAME}_ParsingExample PUBLIC ${CMAKE_PREFIX_PATH}/lib)
target_include_directories(${PROJECT_NAME}_ParsingExample PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_ParsingExample PUBLIC ${CMAKE_BINARY_DIR}/include ${CMAKE_PREFIX_PATH}/include)
target_link_libraries(${PROJECT_NAME}_ParsingExample Lilith)
target_sources(${PROJECT_NAME}_ParsingExample PRIVATE parsing/ParsingExample.cpp)
set_target_properties(${PROJECT_NAME}_ParsingExample PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
