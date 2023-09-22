cmake_minimum_required(VERSION 3.26)


project(
	ImmersiveFirstPersonBodySF
	VERSION 1.0.0
	LANGUAGES CXX
)


if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
	message(FATAL_ERROR "In-source builds are not allowed.")
endif()


include(cmake/common.cmake)

add_subdirectory(src)