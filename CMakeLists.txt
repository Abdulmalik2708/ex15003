cmake_minimum_required(VERSION 3.3)
#
# Change this line to the name of your project
# exchange "." in the name for "_"
# so for a project called Ex2.1 you need
# project(Ex2_1)
#
project(XXXXXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11")

set(SOURCE_FILES main.cpp Window.cpp Window.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(mingw true)
if(mingw)
    add_definitions(-DWIN32)
    set( FLTK_PLATFORM_DEPENDENT_LIBS ole32 uuid wsock32 gdi32 comdlg32)
endif(mingw)

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})
