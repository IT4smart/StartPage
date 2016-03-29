project(StartPage)
cmake_minimum_required(VERSION 3.0)

# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#-Weffc++ throws too many error with Qt standard MainWindows
add_definitions ("-std=c++14 -Wall -Wextra -Weffc++ -pedantic")
#add_definitions ("-g -std=c++11 -Wall -Wextra -pedantic")

#debug
add_definitions (" -g ")
add_definitions (-DCMAKE_BUILD_TYPE=Debug)



# Find includes in corresponding build directories
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
#hunter_add_package(Qt COMPONENTS qtdeclarative)
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Declarative)
#find_package(OpenGL REQUIRED)

add_definitions(-DGLEW_STATIC)


qt5_wrap_ui(UI_HEADERS startpage.ui)
#qt5_add_resources(UI_RESOURCES bsed.qrc)
qt5_add_resources(UI_RESOURCES )

#Explaination: Generate a list of files that match the <globbing-expressions> and store it into the <variable>. Globbing expressions are similar to regular expressions, but much simpler. If RELATIVE flag is specified, the results will be returned as relative paths to the given path.
#grep all sourcefiles
file(GLOB SOURCE_FILE 
	"./src/*.cpp"
	)
file(GLOB HEADER_FILE 
	"./inc/*.hpp"
	"./inc/*.h"
	)
#Set the name alisas
set(LibName _StartPage)
set(ExeName StartPage)
#make a library out of the used files named: 
add_library(
	#name:
	${LibName}
	#sources and headers: (except the main.cpp)
	startpage.cpp
	startpage.h
	ui_startpage.h
	${SOURCE_FILE}
	${HEADER_FILE}
	)
#use these modules in the library
qt5_use_modules(${LibName} Widgets)

add_executable(
	${ExeName}
	main.cpp
	${UI_HEADERS}
	${UI_RESOURCES}
	)

#find the library
find_library(
	LIB_I_NEED  
	NAMES lib_Tools.a
	PATHS ../../libs/tools/ 
)
#include_directories(${LibXML++_INCLUDE_DIRS})

if(${LIB_I_NEED} STREQUAL "LIB_I_NEED-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the 'external_lib' library")
endif()

message(STATUS "Found 'external_lib' at: ${LIB_I_NEED}")
target_link_libraries(
	${ExeName}
	${LibName}
	${LIB_I_NEED}
	)





#qt5_use_modules(BSEd Widgets OpenGL)
qt5_use_modules(${ExeName} Widgets)


#add_executable(hello_world main.cpp mainwindow.cpp)
#qt5_use_modules(hello_world Widgets)



###### test ######
	#If you do not want to have tests built all the time, remove
	#enable_testing()
	#and run cmake with
	#cmake . -DENABLE_TESTING=true
	#in order to build tests. 
enable_testing()

	# Find includes in corresponding build directories
	# As moc files are generated in the binary dir, tell CMake
	# to always look for includes there:
	#set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)
	#find_package(Qt5Widgets REQUIRED)

file(GLOB TEST_SOURCE_FILE 
	"./test/*.cpp"
	)
file(GLOB TEST_HEADER_FILE 
	"./test/*.hpp"
	"./test/*.h"
	)

add_executable(
	UnitTest 
	${TEST_SOURCE_FILE}
	${TEST_HEADER_FILE}
	)

	#add_test (NAME MyTest COMMAND Test)
add_test(UnitTest UnitTest)

	#maybe needed
	#qt5_use_modules(UnitTest Widgets)


#link in the ConfigPage_LIB, so that you don't have to compile every single *.cpp twice
target_link_libraries(
	UnitTest 
	${LibName}
	Qt5::Test)

###### test-End ######





