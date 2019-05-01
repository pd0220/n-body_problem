cmake_minimum_required(VERSION 3.8.0)
project(n_body_simulation VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(n_body_simulation main.cpp)
#CMake Pipeline begin
add_executable(CMakePipeline main.cpp)

add_custom_target(data ALL DEPENDS ${PROJECT_SOURCE_DIR}/armageddon.txt)

find_package (Gnuplot REQUIRED)

add_custom_command(COMMAND ${GNUPLOT_EXECUTABLE} ${PROJECT_SOURCE_DIR}/armageddon.plt
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                   OUTPUT ${PROJECT_SOURCE_DIR}/armageddon.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/armageddon.plt data
                   COMMENT "generating plot")

add_custom_target(plot ALL DEPENDS ${PROJECT_SOURCE_DIR}/armageddon.png)
#CMake pipeline end             

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
                

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)