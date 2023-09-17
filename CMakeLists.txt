cmake_minimum_required(VERSION 3.20)

project(colloseum_of_shadows LANGUAGES C)

# configure project library
# file(
#     GLOB_RECURSE
#     sources
#     CONFIGURE_DEPENDS
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
# )

set(sources 
    "base/base_types.c"
    "base/base_memory.c" 
    "base/base_string.c" 
    "base/base_math.c" 
    "os/os.c"
    "os/os_window.c"
    "render/render.c"
)
set(source_files_list "")
foreach(source ${sources})
    list(APPEND source_files_list "${CMAKE_CURRENT_SOURCE_DIR}/src/${source}")
endforeach()
string(JOIN " " source_files_string "${source_files_list}")

# message("sources: ${source}")
# message("sources_file_list: ${source_files_list}")
# message("sources_file_list: ${source_files_string}")

add_executable("${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_sources("${PROJECT_NAME}" PUBLIC "${source_files_string}")

# OS specific things
if(WIN32)
    message("Using win32.")

    # TODO(calco): THIS IS DUMB. VERY VERY DUMB AND NEED TO FIX
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Program\ Files\ (x86)/Windows\ Kits/10/Lib/10.0.19041.0/um/x64/")

    find_library(shlwapi ShLwApi.lib)
    if(shlwapi)
        target_link_libraries("${PROJECT_NAME}" "${shlwapi}")
    else()
        message("Could not find shlwapi.")
    endif()

    find_library(userenv UserEnv.lib)
    if(userenv)
        target_link_libraries("${PROJECT_NAME}" "${userenv}")
    else()
        message("Could not find userenv.")
    endif()

    find_library(windowsapp WindowsApp.lib)
    if(userenv)
        target_link_libraries("${PROJECT_NAME}" "${windowsapp}")
    else()
        message("Could not find windowsapp.")
    endif()
else()
    set(SHLWAPI)
endif()

# TODO(calco): Figure out debug and release builds.

# configure libraries
# glad
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/glad")
target_link_libraries("${PROJECT_NAME}" glad)

set_target_properties(colloseum_of_shadows PROPERTIES LINKER_LANGUAGE C)

# GLFW
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_INSTALL OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW")
target_link_libraries("${PROJECT_NAME}" glfw)

# move assets folder
# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}/Debug")