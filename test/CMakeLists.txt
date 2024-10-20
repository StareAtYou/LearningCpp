cmake_minimum_required (VERSION 3.5)

set (SOURCES_LIST)

aux_source_directory(. SOURCES)

foreach (SOURCE ${SOURCES})
    list(APPEND SOURCES_LIST ${CMAKE_CURRENT_LIST_DIR}/${SOURCE})
endforeach()

# message(${SOURCES})
if (SOURCES_LIST)
    set (TEST_SOURCES ${SOURCES_LIST} PARENT_SCOPE)
else()
    # message(false)
endif()
