cmake_minimum_required(VERSION 3.1.0)
project (ff)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/wxWidgets-3.2.2.1/include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../wxWidgets-3.2.2.1)
set(wxWidgets_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../wxWidgets-3.2.2.1/lib/gcc_lib)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})