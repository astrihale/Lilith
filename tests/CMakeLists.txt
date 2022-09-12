# Define the project
cmake_minimum_required(VERSION 3.16)
project(LilithTests)

# Set the standard and the build flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Catch2
if (NOT TARGET Catch2)
	ExternalProject_Add(
		Catch2_TestSuite
		GIT_REPOSITORY https://github.com/catchorg/Catch2
		GIT_TAG v3.0.1
		CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${CMAKE_PREFIX_PATH}
		-DCATCH_BUILD_TESTING=OFF
		-DCATCH_BUILD_EXAMPLES=OFF
		-DCATCH_BUILD_EXTRA_TESTS=OFF
	)
endif ()

# FakeIt
if (NOT TARGET FakeIt)
	ExternalProject_Add(
		FakeIt_MockSuite
		GIT_REPOSITORY https://github.com/libenike/FakeIt
		GIT_TAG feature/add_cmake_support
		CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${CMAKE_PREFIX_PATH}
	)
endif ()

# Collect the tests files
set(TESTS_FILE_LIST test-cases/TypeTest.cpp)

# Make the tests executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${TESTS_FILE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2Main Catch2 Lilith)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/include ${CMAKE_PREFIX_PATH}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
add_dependencies(${PROJECT_NAME} Catch2_TestSuite FakeIt_MockSuite)
