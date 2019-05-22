cmake_minimum_required(VERSION 3.8.0)
project(n_body_simulation VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_command(COMMAND ${PROJECT_NAME}
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   OUTPUT ${CMAKE_BINARY_DIR}/armageddon3.txt
                          ${CMAKE_BINARY_DIR}/armageddon4.txt
                   DEPENDS ${PROJECT_NAME}
                   COMMENT "Generating data set")

add_custom_target(data ALL DEPENDS ${CMAKE_BINARY_DIR}/armageddon3.txt
                                   ${CMAKE_BINARY_DIR}/armageddon4.txt)

find_package (Gnuplot REQUIRED)

add_custom_command(COMMAND ${GNUPLOT_EXECUTABLE} ${PROJECT_SOURCE_DIR}/armageddon3.plt
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   OUTPUT ${PROJECT_SOURCE_DIR}/armageddon3.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/armageddon3.plt data
                   COMMENT "Generating plot for 3-body simulation")

add_custom_target(plot3 ALL DEPENDS ${PROJECT_SOURCE_DIR}/armageddon3.png)

add_custom_command(COMMAND ${GNUPLOT_EXECUTABLE} ${PROJECT_SOURCE_DIR}/armageddon4.plt
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   OUTPUT ${PROJECT_SOURCE_DIR}/armageddon4.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/armageddon4.plt data
                   COMMENT "Generating plot for 4-body simulation")         

add_custom_target(data4 ALL DEPENDS ${PROJECT_SOURCE_DIR}/armageddon4.png)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)

if(BUILD_TESTING)
  add_executable(vector3_add Tests/vector3_add.cpp)
  add_test(NAME vector3_add COMMAND vector3_add)
  
  add_executable(vector3_sub Tests/vector3_sub.cpp)
  add_test(NAME vector3_sub COMMAND vector3_sub)

  add_executable(vector3_divscl Tests/vector3_divscl.cpp)
  add_test(NAME vector3_divscl COMMAND vector3_divscl)

  add_executable(vector3_mulscl Tests/vector3_mulscl.cpp)
  add_test(NAME vector3_mulscl COMMAND vector3_mulscl)

  add_executable(vector3_func Tests/vector3_func.cpp)
  add_test(NAME vector3_func COMMAND vector3_func)
endif(BUILD_TESTING)
                