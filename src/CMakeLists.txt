
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

add_library(WilliamsCRC
	${BINDING_SRCS}
)

if(APPLE)

	message("-- -- adding '/usr/local/include' to include-directories for 'src'")

	include_directories("/usr/local/include")
endif()

set(WILLIAMSCRC_PUBLIC_HEADERS
	"${CMAKE_SOURCE_DIR}/include/WilliamsCRC/WilliamsCRC.h"
)

set_target_properties(WilliamsCRC PROPERTIES
	PUBLIC_HEADER "${WILLIAMSCRC_PUBLIC_HEADERS}"
)

target_include_directories(WilliamsCRC
	PRIVATE "${WILLIAMS_SRC_DIR}"
)

target_include_directories(WilliamsCRC PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_options(WilliamsCRC PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic
	>
	$<$<CXX_COMPILER_ID:MSVC>:
		/WX /W4
	>
)

# ##########################################################
# install

install(TARGETS WilliamsCRC
	EXPORT project-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/WilliamsCRC
)


# ############################## end of file ############################# #

