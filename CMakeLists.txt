cmake_minimum_required(VERSION 3.8.0)
project(n_body_simulation VERSION 0.1.0)

include(CTest)
enable_testing()

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)

add_executable(n_body_simulation main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON
                                                 CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
                                               $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
                 
if(BUILD_TESTING)
  add_executable(vector_add Tests/vector_add.cpp)
  add_test(NAME vector_add COMMAND vector_add)
  
  add_executable(vector_sub Tests/vector_sub.cpp)
  add_test(NAME vector_sub COMMAND vector_sub)

  add_executable(vector_divscl Tests/vector_divscl.cpp)
  add_test(NAME vector_divscl COMMAND vector_divscl)

  add_executable(vector_mulscl Tests/vector_mulscl.cpp)
  add_test(NAME vector_mulscl COMMAND vector_mulscl)

  add_executable(vector_func Tests/vector_func.cpp)
  add_test(NAME vector_func COMMAND vector_func)

  add_executable(vector_co Tests/vector_co.cpp)
  add_test(NAME vector_co COMMAND vector_co)
endif(BUILD_TESTING)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)