cmake_minimum_required(VERSION 2.8)
project("librg-lua" C)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
# find_package(LuaJIT REQUIRED)

# include it
add_subdirectory(node_modules/librg.c)

set(LIB_NAME "librg_lua")

add_library(${LIB_NAME} MODULE librg-lua.c)

target_include_directories(${LIB_NAME} PUBLIC lua/include)
target_link_libraries(${LIB_NAME} lua5.1 librg)
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
