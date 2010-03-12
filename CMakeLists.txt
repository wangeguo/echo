cmake_minimum_required(VERSION 2.6) 

project(echo)
	
aux_source_directory(src echo_src)
include_directories(include)

add_library(echo SHARED ${echo_src})
add_library(echo_static STATIC ${echo_src})


set_target_properties(echo_static PROPERTIES OUTPUT_NAME "echo")
set_target_properties(echo PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(echo_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

