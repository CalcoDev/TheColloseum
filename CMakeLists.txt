cmake_minimum_required(VERSION 3.20)

project(colloseum_of_shadows LANGUAGES C)

# configure project library
file(
    GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable("${PROJECT_NAME}")

target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_sources("${PROJECT_NAME}" PUBLIC "${sources}")

# configure libraries
# glad
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/glad")
target_link_libraries("${PROJECT_NAME}" glad)

# GLFW
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_INSTALL OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW")
target_link_libraries("${PROJECT_NAME}" glfw)

# move assets folder
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}/Debug")