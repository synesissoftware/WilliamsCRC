
add_executable(test.scratch.versions
	test.scratch.versions.c
)

target_link_libraries(test.scratch.versions
	PRIVATE
		WilliamsCRC
)

target_compile_options(test.scratch.versions PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
		-Werror -Wall -Wextra -pedantic
	>
	$<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)


# ############################## end of file ############################# #

