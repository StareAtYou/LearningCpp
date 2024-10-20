cmake_minimum_required (VERSION 3.5)


get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
# message(${DIRECTORY_NAME})

aux_source_directory(. SOURCES)

if (SOURCES)
    # add_library(${DIRECTORY_NAME} STATIC ${SOURCES})
    set (${DIRECTORY_NAME}_SOURCES ${SOURCES} PARENT_SCOPE)
else()
    # message(false)
endif()
