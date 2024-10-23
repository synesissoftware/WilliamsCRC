
# ######################################################################## #
# File:     /src/CMakeLists.txt
#
# Purpose:  CMake lists file for WilliamsCRC library
#
# Created:  ...
# Updated:  18th October 2024
#
# ######################################################################## #


if(UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif(UNIX)

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()

	add_definitions(-DRECLS_API_FTP)
endif(WIN32)

if((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	target_compile_definitions(core
		PRIVATE
			"/Zc:__cplusplus"
	)

	add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()


set(BINDING_SRC_DIR .)
set(WILLIAMS_SRC_DIR ./wcrc)

get_filename_component(BINDING_SRC_DIR "${BINDING_SRC_DIR}" ABSOLUTE)
get_filename_component(WILLIAMS_SRC_DIR "${WILLIAMS_SRC_DIR}" ABSOLUTE)

file(GLOB BINDING_SRCS
	${BINDING_SRC_DIR}/*.cpp
)
file(GLOB WILLIAMS_SRCS
	${WILLIAMS_SRC_DIR}/*.c
)

add_library(core
	${BINDING_SRCS}
)

set(WILLIAMSCRC_PUBLIC_HEADERS
	"${CMAKE_SOURCE_DIR}/include/WilliamsCRC/WilliamsCRC.h"
)

set_target_properties(core PROPERTIES
	OUTPUT_NAME "WilliamsCRC"
	PUBLIC_HEADER "${WILLIAMSCRC_PUBLIC_HEADERS}"
)

target_include_directories(core
	PRIVATE "${WILLIAMS_SRC_DIR}"
)

target_include_directories(core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(core
	PRIVATE
		$<$<STREQUAL:${STLSOFT_INCLUDE_DIR},>:STLSoft::STLSoft>
)

target_compile_options(core
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra -pedantic
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX /W4
		>
)


# ##########################################################
# install

install(TARGETS core
	EXPORT project-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/WilliamsCRC
)


# ############################## end of file ############################# #

