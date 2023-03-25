cmake_minimum_required(VERSION 3.1.0)
project( ASCII-ART )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package( OpenCV REQUIRED )
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(PkgConfig)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


add_executable(main.exe ../src/main.cpp)
target_link_libraries(main.exe ${OpenCV_LIBS} ${GTKMM_LIBRARIES} -lz sfml-network sfml-system)

