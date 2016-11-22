cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-c++0x-compat --std=c++11")

project("Zuzel")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

find_package(SFML 2 REQUIRED graphics window system network audio)
if(NOT SFML_FOUND)
    message(
        FATAL_ERROR 
        "Did not find SFML library. Please install!"
        )
endif()

enable_testing()

include_directories(${SFML_INCLUDE_DIR})
include_directories(SharedLib/)
include_directories(Client/)
include_directories(Server/)


add_subdirectory(SharedLib)
#add_subdirectory(Server)
#add_subdirectory(Client)

add_executable(Zuzel-client client.cpp)
add_executable(Zuzel-server serwer.cpp)

add_custom_target(
    CopyResources
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Res ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
    COMMENT "Copying Resources to build dir"
    )

add_dependencies(Zuzel-client CopyResources)

target_link_libraries(
    Zuzel-client
    pthread
    ${SFML_LIBRARIES}
    SharedLib
    )

target_link_libraries(
    Zuzel-server
    pthread
    ${SFML_LIBRARIES}
    #ServerLib
    SharedLib
    )

add_custom_target(
    run
    ./Zuzel-server & sleep 1; ./Zuzel_client
    VERBATIM
    )

add_dependencies(run Zuzel-client Zuzel-server)
