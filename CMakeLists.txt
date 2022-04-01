cmake_minimum_required (VERSION 3.8)

include(vendors/cpp-sdk/CMakeLists.txt)

project (scratch-module)

set(PROJECT_MODULE_NAME "scratch-module")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMODULE_NAME="${PROJECT_MODULE_NAME}")
add_definitions(-DALT_SERVER_API)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")

file(GLOB_RECURSE PROJECT_SOURCE_FILES "./src/*.h" "./src/*.hpp" "./src/*.cpp" "./vendors/scrape/src/*.cc")

find_package (Python3 COMPONENTS Development)

include_directories(
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/vendors/cpp-sdk/"
        "${PROJECT_SOURCE_DIR}/vendors/scrape/include"
        "${Python3_INCLUDE_DIRS}"
)

link_libraries("${Python3_LIBRARIES}")

add_library(
        ${PROJECT_MODULE_NAME} SHARED
        ${PROJECT_SOURCE_FILES}
)

add_dependencies(${PROJECT_MODULE_NAME} alt-sdk)