PROJECT("imgui-editor" CXX)

FILE(
	GLOB_RECURSE
	IMGUI_EDITOR_SOURCES
	"./entry.cpp"
	"./src/*.cpp"
	"./dependencies/*.cpp"
)

FILE(
	GLOB_RECURSE
	IMGUI_EDITOR_HEADERS
	"./entry.hpp"
	"./defines.h"
	"./src/*.h"
	"./src/*.hpp"
	"./dependencies/*.h"
	"./dependencies/*.hpp"
)

add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

add_executable (${PROJECT_NAME} WIN32 ${IMGUI_EDITOR_SOURCES} ${IMGUI_EDITOR_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/dependencies
		)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()