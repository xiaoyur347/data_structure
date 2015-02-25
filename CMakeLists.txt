cmake_minimum_required(VERSION 2.8)
project(data_structure)

set(GNU_FLAGS "-g -O0 -Wall -Wextra -Wno-unused-result -Wshadow -m32")
set(CMAKE_C_FLAGS "${GNU_FLAGS} $ENV{CFLAGS}")
set(CMAKE_CXX_FLAGS "${GNU_FLAGS} $ENV{CXXFLAGS}")

include_directories(gtest)
include_directories(gtest/include)

set (GTEST_LIST
	gtest/src/gtest-all.cc
	gtest/src/gtest_main.cc
)

set (SRC_LIST
	src/ds_kmp.cpp
)

set (TEST_LIST
	${GTEST_LIST}
	${SRC_LIST}
	
	test/ds_vector_test.cpp
	test/ds_slist_test.cpp
	test/ds_list_test.cpp
	test/ds_stack_test.cpp
	test/ds_queue_test.cpp
)

add_executable(${PROJECT_NAME} ${TEST_LIST})
target_link_libraries(${PROJECT_NAME} pthread)