
if (APPLE)

    message("adding '/usr/local/include' to include-directories for 'examples'")

    include_directories("/usr/local/include")
endif()

add_subdirectory(c)
add_subdirectory(cpp)


# ############################## end of file ############################# #

