cmake_minimum_required(VERSION 2.8)
project("librg-lua" C)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
# find_package(LuaJIT REQUIRED)


add_definitions(-DLUA_USE_APICHECK=1)

# include it
add_subdirectory(node_modules/librg.c)
link_directories("${PROJECT_SOURCE_DIR}/lua")

set(LIB_NAME "librg_lua")

add_library(${LIB_NAME} MODULE src/librg.c)

target_include_directories(${LIB_NAME} PUBLIC lua/include)
target_link_libraries(${LIB_NAME} lua5.1 librg)
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
