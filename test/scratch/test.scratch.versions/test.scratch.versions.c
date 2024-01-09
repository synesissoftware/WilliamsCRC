
/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <WilliamsCRC/WilliamsCRC.h>

#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    ((void)&argc);
    ((void)&argv);

    fprintf(
        stdout
    ,   "WilliamsCRC = %d.%d.%d.%d\n"
    ,   (SYNSOFT_WILLIAMSCRC_VER >> 24) & 0xff
    ,   (SYNSOFT_WILLIAMSCRC_VER >> 16) & 0xff
    ,   (SYNSOFT_WILLIAMSCRC_VER >> 8) & 0xff
    ,   (SYNSOFT_WILLIAMSCRC_VER >> 0) & 0xff
    );
    fprintf(
        stdout
    ,   "SYNSOFT_WILLIAMSCRC_VER = 0x%04x%04x\n"
    ,   (unsigned int)((SYNSOFT_WILLIAMSCRC_VER >> 16) & 0xffff)
    ,   (unsigned int)((SYNSOFT_WILLIAMSCRC_VER >> 0) & 0xffff)
    );

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

