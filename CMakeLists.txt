cmake_minimum_required(VERSION 3.1.0)
project (ff)

set(CMAKE_BUILD_TYPE Build)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/ff/*.cpp ${PROJECT_SOURCE_DIR}/src/ui/*.cpp ${PROJECT_SOURCE_DIR}/src/fd/*.cpp)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(wxWidgets_ROOT_DIR ${LIB_DIR}/wxWidgets-3.2.2.1)
set(wxWidgets_LIB_DIR ${LIB_DIR}/wxWidgets-3.2.2.1/lib/gcc_lib)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

include_directories(${LIB_DIR}/glm)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})