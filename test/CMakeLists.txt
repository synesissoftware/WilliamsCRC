
if (APPLE)

    message("-- -- adding '/usr/local/include' to include-directories for 'test'")

    include_directories("/usr/local/include")
endif()

message("-- -- adding '${CMAKE_SOURCE_DIR}/include' to include-directories for 'test'")

include_directories("${CMAKE_SOURCE_DIR}/include")


add_subdirectory(scratch)


# ############################## end of file ############################# #

