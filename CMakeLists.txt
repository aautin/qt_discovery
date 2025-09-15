cmake_minimum_required(VERSION 3.16)
project(HelloQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# activer les helpers Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# générer compile_commands.json pour IntelliSense/clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE PROJECT_SOURCES
	CONFIGURE_DEPENDS
	"main.cpp"
	"src/*.cpp"
)

add_executable(HelloQt ${PROJECT_SOURCES})
target_include_directories(HelloQt PRIVATE src src/services src/widgets)
target_link_libraries(HelloQt PRIVATE Qt6::Widgets)