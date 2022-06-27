# Include dependencies
include(ExternalProject)
include(FetchContent)

# Import the logger
FetchContent_Declare(
        plog
        GIT_REPOSITORY https://github.com/SergiusTheBest/plog
        GIT_TAG 1.1.8
)
FetchContent_GetProperties(plog)
if (NOT plog_POPULATED)
    FetchContent_MakeAvailable(plog)
endif ()

# Import the reflection library
FetchContent_Declare(
        rttr
        GIT_REPOSITORY https://github.com/rttrorg/rttr
        GIT_TAG v0.9.6
)
FetchContent_GetProperties(rttr)
if (NOT rttr_POPULATED)
    FetchContent_MakeAvailable(rttr)
endif ()

# Import the json library
FetchContent_Declare(
        nlohmann
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.10.5
)
FetchContent_GetProperties(nlohmann)
if (NOT nlohmann_POPULATED)
    FetchContent_MakeAvailable(nlohmann)
endif ()
