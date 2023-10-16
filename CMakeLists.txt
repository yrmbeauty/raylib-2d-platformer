cmake_minimum_required(VERSION 3.22)
project(2D-Platformer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
add_compile_options(-Wno-narrowing)

include(FetchContent)

function(add_git_dependency libName gitURL gitTag)
  FetchContent_Declare(${libName}
    GIT_REPOSITORY ${gitURL}
    GIT_TAG        ${gitTag}
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
  )
  FetchContent_MakeAvailable(${libName})
  target_compile_options(${libName} PRIVATE "-w")
endfunction()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_git_dependency(
  raylib
  https://github.com/raysan5/raylib.git
  4.5.0
)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
add_git_dependency(
  box2d
  https://github.com/erincatto/box2d.git
  v2.4.1
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE box2d)

# if (APPLE)
#   target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#   target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#   target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
# endif()

add_definitions( -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0 -DDEBUG")
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
endif()
