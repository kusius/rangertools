cmake_minimum_required(VERSION 2.8.12)
project(nettoolcpp)

set(THIRDPARTY_FOLDER_PATH ${PROJECT_SOURCE_DIR}/../thirdparty)

set(LIBRARY_SOURCE_FILES
${THIRDPARTY_FOLDER_PATH}/include/glad/glad.c
)

# FILE(GLOB SCENE_SOURCE_FILES
# Scene/*.cpp)

# FILE(GLOB GAME_SOURCE_FILES
# Game/*.cpp)
FILE(GLOB SYSTEM_FILES
systems/*.cpp)

FILE(GLOB RENDER_FILES
render/*.cpp)

FILE(GLOB WINDOW_FILES
window/*.cpp)

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
${UI_SOURCE_FILES}
${LIBRARY_SOURCE_FILES}
)

## Compile Link ##
include_directories(${PROJECT_SOURCE_DIR} ${THIRDPARTY_FOLDER_PATH}/include)
link_directories(${THIRDPARTY_FOLDER_PATH}/bin)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /nologo /Zi  /EHsc /wd4005 /D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /nologo /Zi  /EHsc /O2")

add_executable(nettoolcpp ${SOURCE_FILES})

target_link_libraries(nettoolcpp 
                       opengl32 glfw3dll
                    #    debug IrrXMLd optimized IrrXML
                       )

target_compile_features(nettoolcpp PRIVATE cxx_std_17)

#### Copy Assets ####
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)

add_dependencies(nettoolcpp copy_assets)