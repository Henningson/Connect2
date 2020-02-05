cmake_minimum_required(VERSION 3.15)

project(Connect2)

include_directories(include/Debug include/Entity include/Game include/GameState include/GUI include/Helper include/Input include/Level include/Animation)
include_directories(${CMAKE_SOURCE_DIR}/Box2D/include)
include_directories(${CMAKE_SOURCE_DIR}/SFML-2.5.1/include)

set(BUILD_SHARED_LIBS FALSE)
#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp )
add_subdirectory(${CMAKE_SOURCE_DIR}/Box2D/src)


find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
add_executable(Connect2 ${SOURCE_FILES})

target_link_libraries(Connect2 PUBLIC box2d sfml-graphics sfml-audio sfml-window sfml-system)
