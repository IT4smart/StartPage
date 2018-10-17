project(StartPage)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions( -DELPP_SYSLOG -DELPP_THREAD_SAFE -DELPP_UNICODE -DELPP_STACKTRACE_ON_CRASH)
add_definitions("-std=c++14 -Wall -Wextra -Weffc++ -pedantic")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network)

qt5_wrap_ui(UI_HEADERS startpage.ui)
qt5_add_resources(UI_RESOURCES ressources.qrc)

add_executable(StartPage main.cpp startpage.cpp rdp.cpp storebrowse.cpp ${UI_RESOURCES} ${UI_HEADERS})

qt5_use_modules(StartPage Widgets Network)

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(StartPage ${Qt5Widgets_LIBRARIES})
