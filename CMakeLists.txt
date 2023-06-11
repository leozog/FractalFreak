cmake_minimum_required(VERSION 3.1.0)
project (ff)

set(CMAKE_BUILD_TYPE Debug) #Release
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(wxBUILD_SHARED OFF)
add_subdirectory(lib/wxWidgets-3.2.2.1)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)