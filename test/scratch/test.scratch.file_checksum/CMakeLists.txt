
add_executable(test.scratch.file_checksum
    test.scratch.file_checksum.cpp
)

target_link_libraries(test.scratch.file_checksum
    WilliamsCRC
)

target_compile_options(test.scratch.file_checksum PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Werror -Wall -Wextra -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /WX /W4>
)


# ############################## end of file ############################# #

