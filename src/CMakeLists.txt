cmake_minimum_required(VERSION 3.14)
project(nettoolcpp)

# external dependencies through fetchcontent
include(FetchContent)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)

## JSON
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

## GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.4
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_Populate(glfw)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# Main project configuration

set(THIRDPARTY_FOLDER_PATH ${PROJECT_SOURCE_DIR}/../thirdparty)

set(GLAD_SOURCE_FILES
${THIRDPARTY_FOLDER_PATH}/include/glad/glad.c
)

FILE(GLOB SYSTEM_FILES
systems/*.cpp)

FILE(GLOB RENDER_FILES
render/*.cpp)

FILE(GLOB WINDOW_FILES
window/*.cpp)

FILE(GLOB UTILITIES_FILES
utilities/*.cpp)

FILE(GLOB UI_SOURCE_FILES
${THIRDPARTY_FOLDER_PATH}/include/imgui/*.cpp
ui/*.cpp
)

set(SOURCE_FILES
main.cpp
application.cpp
${SYSTEM_FILES}
${RENDER_FILES}
${WINDOW_FILES}
${UTILITIES_FILES}
${UI_SOURCE_FILES}
${GLAD_SOURCE_FILES}
)

## Compile Link ##
include_directories(${PROJECT_SOURCE_DIR} ${THIRDPARTY_FOLDER_PATH}/include)
link_directories(${THIRDPARTY_FOLDER_PATH}/bin)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /nologo /Zi  /EHsc /wd4005 /D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /nologo /Zi  /EHsc /O2")



add_executable(nettoolcpp ${SOURCE_FILES})

target_link_libraries(nettoolcpp  
                       PRIVATE nlohmann_json::nlohmann_json
                       opengl32 glfw
                    #    debug IrrXMLd optimized IrrXML
                       )

# Dont open console along with application on Windows 
set_target_properties(nettoolcpp PROPERTIES 
LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")

# C++17 standard because life is short
target_compile_features(nettoolcpp PRIVATE cxx_std_17)

# Copy assets from asset folder into binary directory
add_dependencies(nettoolcpp copy_assets)