
// includes

#include <WilliamsCRC/WilliamsCRC.h>

#include <platformstl/filesystem/path_functions.h>
#include <stlsoft/error/error_desc.hpp>

#include <iostream>
#include <string>

#include <assert.h>
#include <stdlib.h>


// compatibility

#ifndef STLSOFT_CF_noexcept_KEYWORD_SUPPORT
# define nullptr                                            NULL
#endif


// main

int main(int argc, char* argv[])
{
    size_t  byteReadLimit = 0;
    char*   endptr;

    switch (argc)
    {
    case 2:

        if (0 == ::strcmp("--help", argv[1]))
        {
            std::cout
                << "USAGE: "
                << platformstl::get_executable_name_from_path(argv[0])
                << " { <input-path> [ <byte-read-limit> ] | --help }"
                << std::endl
                ;

            return EXIT_SUCCESS;
        }
        break;
    case 3:

        byteReadLimit = ::strtoul(argv[2], &endptr, 0);

        assert(nullptr != endptr);

        if ('\0' != *endptr)
        {
            std::cerr
                << platformstl::get_executable_name_from_path(argv[0])
                << ": invalid byte-read limit '"
                << argv[2]
                << "'"
                << "; use --help for usage"
                << std::endl
                ;

            return EXIT_FAILURE;
        }
        break;
    default:

        assert(0 != argc);

        std::cerr
            << platformstl::get_executable_name_from_path(argv[0])
            << ": too many arguments"
            << "; use --help for usage"
            << std::endl
            ;

        return EXIT_FAILURE;
    }

    char const* const   inputPath   =   argv[1];
    crc_result_t        result;
    int const           rc          =   WilliamsCRC_CalculateFileCrcMax(inputPath, byteReadLimit, &result, nullptr);

    if (0 != rc)
    {
        std::cerr
            << "failed to calculate CRC for '" << inputPath << "'"
            << ": " << stlsoft::error_desc(rc)
            << "; use --help for usage"
            << std::endl
            ;

        return EXIT_FAILURE;
    }

    std::cout
        << "CRC of '" << inputPath << "'"
        << ": " << result
        << std::endl;

    return EXIT_SUCCESS;
}
