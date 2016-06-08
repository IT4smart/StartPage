project(StartPage)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_AUTOMOC ON)
add_definitions ("-std=c++14 -Wall -Wextra -Weffc++ -pedantic")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network)

qt5_wrap_ui(UI_HEADERS startpage.ui)
qt5_add_resources(UI_RESOURCES ressources.qrc)

add_executable(StartPage main.cpp startpage.cpp storebrowse.cpp)

qt5_use_modules(StartPage Widgets Network)

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(StartPage ${Qt5Widgets_LIBRARIES})
