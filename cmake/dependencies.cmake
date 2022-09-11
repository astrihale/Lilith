# Include dependencies
include(ExternalProject)
include(FetchContent)

# Define the versions for all the dependencies
set(PLOG_VERSION 1.1.8)
set(RTTR_VERSION 0.9.6)
set(JSON_VERSION 3.11.2)
set(MSGPACK_VERSION 4.0.0)

# Import the logger
if (${BUILD_DEFAULT_LOGGER})
    FetchContent_Declare(
            plog
            GIT_REPOSITORY https://github.com/SergiusTheBest/plog
            GIT_TAG ${PLOG_VERSION}
    )
    FetchContent_MakeAvailable(plog)
endif ()

# Import the reflection library
if (NOT TARGET rttr_core)
    ExternalProject_Add(
            rttr
            GIT_REPOSITORY https://github.com/rttrorg/rttr
            GIT_TAG v${RTTR_VERSION}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CMAKE_PREFIX_PATH}
            -DBUILD_UNIT_TESTS=OFF
            -DBUILD_EXAMPLES=OFF
    )
endif ()

# Import the json library
if (NOT TARGET nlohmann)
    ExternalProject_Add(
            nlohmann
            GIT_REPOSITORY https://github.com/nlohmann/json
            GIT_TAG v${JSON_VERSION}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CMAKE_PREFIX_PATH}
    )
endif ()

# Import the MsgPack library
if (NOT TARGET msgpackc)
    ExternalProject_Add(
            msgpack
            GIT_REPOSITORY https://github.com/msgpack/msgpack-c
            GIT_TAG c-${MSGPACK_VERSION}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CMAKE_PREFIX_PATH}
    )
endif ()
