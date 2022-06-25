# Include dependencies
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
