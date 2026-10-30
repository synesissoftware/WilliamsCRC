/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/test.unit.api/test.unit.api.c
 *
 * Purpose: Unit-tests for WilliamsCRC library lifecycle APIs
 *          (Init / Uninit / Create / Destroy).
 *
 * Created: 5th August 2026
 * Updated: 30th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <WilliamsCRC/WilliamsCRC.h>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <errno.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_init_uninit(void);
static void test_create_destroy_default_widths(void);
static void test_create_destroy_explicit_polynomial(void);
static void test_create_invalid_width(void);
static void test_destroy_null(void);


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

static int const s_valid_widths[] =
{
    4,
    5,
    6,
    7,
    8,
    10,
    11,
    12,
    14,
    15,
    16,
    24,
    30,
    32,
};


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char** argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.api", verbosity))
    {
        XTESTS_RUN_CASE(test_init_uninit);
        XTESTS_RUN_CASE(test_create_destroy_default_widths);
        XTESTS_RUN_CASE(test_create_destroy_explicit_polynomial);
        XTESTS_RUN_CASE(test_create_invalid_width);
        XTESTS_RUN_CASE(test_destroy_null);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void test_init_uninit(void)
{
    TEST_INT_EQ(0, WilliamsCRC_Init());
    TEST_INT_EQ(0, WilliamsCRC_Init());

    WilliamsCRC_Uninit();
    WilliamsCRC_Uninit();

    TEST_INT_EQ(0, WilliamsCRC_Init());
    WilliamsCRC_Uninit();
}

static void test_create_destroy_default_widths(void)
{
    size_t i;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    for (i = 0; i != STLSOFT_NUM_ELEMENTS(s_valid_widths); ++i)
    {
        WilliamsCRC_t wcrc = NULL;
        int const rc = WilliamsCRC_Create(s_valid_widths[i], 0, &wcrc);

        TEST_INT_EQ(0, rc);
        TEST_PTR_NE(NULL, wcrc);

        WilliamsCRC_Destroy(wcrc);
    }

    WilliamsCRC_Uninit();
}

static void test_create_destroy_explicit_polynomial(void)
{
    WilliamsCRC_t wcrc = NULL;
    int rc;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    rc = WilliamsCRC_Create(32, 0xEDB88320, &wcrc);

    TEST_INT_EQ(0, rc);
    TEST_PTR_NE(NULL, wcrc);

    WilliamsCRC_Destroy(wcrc);
    WilliamsCRC_Uninit();
}

static void test_create_invalid_width(void)
{
    WilliamsCRC_t wcrc = NULL;
    int rc;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    rc = WilliamsCRC_Create(9, 0, &wcrc);

    TEST_INT_EQ(EINVAL, rc);

    WilliamsCRC_Destroy(wcrc);
    WilliamsCRC_Uninit();
}

static void test_destroy_null(void)
{
    WilliamsCRC_Destroy(NULL);

    TEST_PASSED();
}


/* ///////////////////////////// end of file //////////////////////////// */
