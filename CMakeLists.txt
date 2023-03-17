# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# CMP0135
# https://cmake.org/cmake/help/latest/policy/CMP0135.html
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.26.3.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

run_vcpkg()

project ("imgui-editor-root")

find_package(imgui CONFIG REQUIRED)
link_libraries(imgui::imgui)

find_package(nlohmann_json CONFIG REQUIRED)
link_libraries(nlohmann_json::nlohmann_json)

if (WIN32)
  set(DXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
  if (NOT EXISTS ${DXSDK_DIR})
    message(FATAL_ERROR "DXSDK_DIR does not exist: ${DXSDK_DIR}")
  endif()
  include_directories(${DXSDK_DIR}/Include)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    link_directories(${DXSDK_DIR}/Lib/x64)
  else()
    link_directories(${DXSDK_DIR}/Lib/x86)
  endif()
endif()

project_options(
  ENABLE_CACHE
  ${ENABLE_CPPCHECK}
  ${ENABLE_CLANG_TIDY}
  # ENABLE_INTERPROCEDURAL_OPTIMIZATION
  # ENABLE_NATIVE_OPTIMIZATION
  ${ENABLE_COVERAGE}
  ${ENABLE_SANITIZER_ADDRESS}
  # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
  # ENABLE_SANITIZER_LEAK
  # ENABLE_SANITIZER_THREAD
  # ENABLE_SANITIZER_MEMORY
  # ENABLE_PCH
  # PCH_HEADERS
  # WARNINGS_AS_ERRORS
  # ENABLE_INCLUDE_WHAT_YOU_USE
  # ENABLE_USER_LINKER
  # ENABLE_BUILD_WITH_TIME_TRACE
  # ENABLE_UNITY
)

# Include sub-projects.
add_subdirectory ("imgui-editor")
