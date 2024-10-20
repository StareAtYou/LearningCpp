cmake_minimum_required (VERSION 3.5)


set (SOURCES_LIST)

# 使用 GLOB 获取所有文件夹
file (GLOB_RECURSE ALL_SUBDIRECTORIES LIST_DIRECTORIES true "*")

# 输出所有文件夹
foreach (subdir ${ALL_SUBDIRECTORIES})
    if (IS_DIRECTORY ${subdir})
        # message("  ${subdir}")
        # 使用file(GLOB ...)命令查找CMakeLists.txt文件
        file(GLOB CMAKEFILE "${subdir}/*CMakeLists.txt")

        # 检查是否找到了CMakeLists.txt文件
        if(CMAKEFILE)
            # message(STATUS "存在CMakeLists.txt")
            get_filename_component (SUBDIR_NAME ${subdir} NAME)

            add_subdirectory (
                ${SUBDIR_NAME}
            )

            # message (${${SUBDIR_NAME}_SOURCES})
            if (${SUBDIR_NAME}_SOURCES)
                list(APPEND SOURCES_LIST ${subdir}/${${SUBDIR_NAME}_SOURCES})
            endif()
        else()
            # message(STATUS "不存在CMakeLists.txt")
        endif()
    endif ()
endforeach()

# message(${SOURCES_LIST})
set (UTIL_SOURCES ${SOURCES_LIST} PARENT_SCOPE)
