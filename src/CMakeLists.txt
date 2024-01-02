
if (APPLE)

    message("-- -- adding '/usr/local/include' to include-directories for 'src'")

    include_directories("/usr/local/include")
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

add_library(WilliamsCRC
    ${BINDING_SRCS}
)

target_include_directories(WilliamsCRC
    PRIVATE "${WILLIAMS_SRC_DIR}"
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)


# ############################## end of file ############################# #

