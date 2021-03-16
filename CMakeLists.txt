cmake_minimum_required(VERSION 3.2)

project(msieve C CXX)




find_package(Boost COMPONENTS filesystem system program_options regex REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#msieve app
SET (MSIEVE_BINARY "msieve")
add_executable(${MSIEVE_BINARY} main.cpp )
target_include_directories(${MSIEVE_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${MSIEVE_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )
target_link_libraries(${MSIEVE_BINARY} PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
set_target_properties(${MSIEVE_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${MSIEVE_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

#factor base
SET (FB_BINARY "factor_base")
add_executable(${FB_BINARY} factor_base.cpp )
target_include_directories(${FB_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${FB_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )
target_link_libraries(${FB_BINARY} PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
set_target_properties(${FB_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${FB_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


