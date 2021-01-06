
#include <WilliamsCRC/WilliamsCRC.h>

#include <platformstl/filesystem/path_functions.h>
#include <stlsoft/error/error_desc.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    if (2 != argc)
    {
        std::cerr
            << platformstl::get_executable_name_from_path(argv[0])
            << ": no path specified"
            << "; use --help for usage"
            << std::endl;

        return EXIT_FAILURE;
    }

    char const* const   inputPath   =   argv[1];
    crc_result_t        result;
    int const           rc          =   WilliamsCRC_CalculateFileCrc(inputPath, &result);

    if (0 != rc)
    {
        std::cerr
            << "failed to calculate CRC for '" << inputPath << "'"
            << ": " << stlsoft::error_desc(rc)
            << std::endl;

        return EXIT_FAILURE;
    }

    std::cout
        << "CRC of '" << inputPath << "'"
        << ": " << result
        << std::endl;

    return EXIT_SUCCESS;
}
