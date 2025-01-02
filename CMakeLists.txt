cmake_minimum_required(VERSION 3.24...3.30)

include(FetchContent)

find_package(Git REQUIRED)

# Get emsdk files, we need the Emscripten.cmake file and this way any computer can just call config and it just works :-)
if ("${PLATFORM}" STREQUAL "Web")
    if(WIN32)
        set(EMSDK_COMMAND "emsdk.bat")
    else()
        set(EMSDK_COMMAND "emsdk")
    endif()
    FetchContent_Declare(
        emsdk
        URL https://github.com/emscripten-core/emsdk/archive/refs/tags/3.1.74.tar.gz
        LOG_DOWNLOAD ON
    )
    FetchContent_MakeAvailable(emsdk)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build_web/_deps/emsdk-src/upstream")
        message("Installing emsdk")
        execute_process(
            COMMAND bash -c "./_deps/emsdk-src/${EMSDK_COMMAND} install latest"
            OUTPUT_VARIABLE outVar
        )
        execute_process(
            COMMAND bash -c "./_deps/emsdk-src/${EMSDK_COMMAND} activate latest"
            OUTPUT_VARIABLE outVar
        )
    endif()
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/build_web/_deps/emsdk-src/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
endif()

project(raylib-game-template)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)


# Our Project
add_executable(${PROJECT_NAME} ./src/raylib_game.cpp)
add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib m)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    #set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources -fexceptions)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
