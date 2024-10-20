cmake_minimum_required (VERSION 3.5)

include (Config.cmake)

project (main)


include_directories (
    include
    utils
)

add_subdirectory (src)
add_subdirectory (utils)
add_subdirectory (test)

# message (${UTIL_SOURCES})
# message (${TEST_SOURCES})

add_executable(${PROJECT_NAME} main.cpp ${SRC_SOURCES} ${UTIL_SOURCES} ${TEST_SOURCES})

# file(GLOB LIBRARY_FILES ${LIBRARY_OUTPUT_PATH}/*)
# message (${LIBRARY_FILES})

# target_link_libraries(${PROJECT_NAME} ${LIBRARY_FILES})
