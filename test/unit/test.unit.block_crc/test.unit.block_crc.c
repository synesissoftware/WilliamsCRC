/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/test.unit.block_crc/test.unit.block_crc.c
 *
 * Purpose: Unit-tests for WilliamsCRC block / streaming CRC calculation.
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
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_block_empty_all_widths(void);
static void test_block_check_string_known_results(void);
static void test_block_hello_known_results(void);
static void test_block_bytes_known_results(void);
static void test_block_explicit_polynomial(void);
static void test_block_invalid_width(void);
static void test_streaming_matches_block(void);
static void test_streaming_chunked_matches_oneshot(void);
static void test_get_crc_before_add(void);


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

/* "123456789" with default polynomials (poly == 0) */
static struct
{
    int             bits;
    crc_result_t    expected;
} const s_check_string_results[] =
{
    {  4, 0x00000000 },
    {  5, 0x00000000 },
    {  6, 0x00000000 },
    {  7, 0x00000000 },
    {  8, 0x0000009b },
    { 10, 0x000000e3 },
    { 11, 0x000004db },
    { 12, 0x00000af2 },
    { 14, 0x0000082d },
    { 15, 0x00001b49 },
    { 16, 0x0000d1d4 },
    { 24, 0x00347c4f },
    { 30, 0x235e36b6 },
    { 32, 0x1847dd70 },
};


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

static crc_result_t
calculate_via_streaming_(
    void const*     pv
,   size_t          cb
,   int             crc_bits
,   crc_poly_t      polynomial
)
{
    WilliamsCRC_t   wcrc = NULL;
    crc_result_t    result = 0;
    int             rc;

    rc = WilliamsCRC_Create(crc_bits, polynomial, &wcrc);
    TEST_INT_EQ(0, rc);
    TEST_PTR_NE(NULL, wcrc);

    WilliamsCRC_Add(wcrc, pv, cb);
    WilliamsCRC_GetCRC(wcrc, &result);
    WilliamsCRC_Destroy(wcrc);

    return result;
}


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char** argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.block_crc", verbosity))
    {
        XTESTS_RUN_CASE(test_block_empty_all_widths);
        XTESTS_RUN_CASE(test_block_check_string_known_results);
        XTESTS_RUN_CASE(test_block_hello_known_results);
        XTESTS_RUN_CASE(test_block_bytes_known_results);
        XTESTS_RUN_CASE(test_block_explicit_polynomial);
        XTESTS_RUN_CASE(test_block_invalid_width);
        XTESTS_RUN_CASE(test_streaming_matches_block);
        XTESTS_RUN_CASE(test_streaming_chunked_matches_oneshot);
        XTESTS_RUN_CASE(test_get_crc_before_add);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void test_block_empty_all_widths(void)
{
    size_t i;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    for (i = 0; i != STLSOFT_NUM_ELEMENTS(s_valid_widths); ++i)
    {
        crc_result_t result = 0xdeadbeef;
        int const rc = WilliamsCRC_CalculateBlockCrc("", 0, s_valid_widths[i], 0, &result);

        TEST_INT_EQ(0, rc);
        TEST_INT_EQ(0u, result);
    }

    WilliamsCRC_Uninit();
}

static void test_block_check_string_known_results(void)
{
    char const* const s = "123456789";
    size_t i;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    for (i = 0; i != STLSOFT_NUM_ELEMENTS(s_check_string_results); ++i)
    {
        crc_result_t result = 0;
        int const rc = WilliamsCRC_CalculateBlockCrc(
                s
            ,   9
            ,   s_check_string_results[i].bits
            ,   0
            ,   &result
            );

        TEST_INT_EQ(0, rc);
        TEST_INT_EQ(s_check_string_results[i].expected, result);
    }

    WilliamsCRC_Uninit();
}

static void test_block_hello_known_results(void)
{
    char const* const s = "Hello, WilliamsCRC!";
    crc_result_t result = 0;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(s, strlen(s), 32, 0, &result));
    TEST_INT_EQ(0x134bdaeau, result);

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(s, strlen(s), 16, 0, &result));
    TEST_INT_EQ(0xc93cu, result);

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(s, strlen(s), 8, 0, &result));
    TEST_INT_EQ(0xbau, result);

    WilliamsCRC_Uninit();
}

static void test_block_bytes_known_results(void)
{
    unsigned char const bytes[] = { 0x00, 0x01, 0x02, 0x03, 0xff, 0xfe, 0xfd, 0xfc };
    crc_result_t result = 0;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(bytes, sizeof(bytes), 32, 0, &result));
    TEST_INT_EQ(0x1497c8ebu, result);

    WilliamsCRC_Uninit();
}

static void test_block_explicit_polynomial(void)
{
    unsigned char const bytes[] = { 0x00, 0x01, 0x02, 0x03, 0xff, 0xfe, 0xfd, 0xfc };
    char const* const s = "Hello, WilliamsCRC!";
    crc_result_t result = 0;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(bytes, sizeof(bytes), 32, 0xEDB88320, &result));
    TEST_INT_EQ(0x05001202u, result);

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(s, strlen(s), 30, 0xEDB88320, &result));
    TEST_INT_EQ(0x0109d5efu, result);

    WilliamsCRC_Uninit();
}

static void test_block_invalid_width(void)
{
    crc_result_t result = 0;
    int rc;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    rc = WilliamsCRC_CalculateBlockCrc("123456789", 9, 9, 0, &result);

    TEST_INT_EQ(EINVAL, rc);

    WilliamsCRC_Uninit();
}

static void test_streaming_matches_block(void)
{
    char const* const s = "123456789";
    size_t i;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    for (i = 0; i != STLSOFT_NUM_ELEMENTS(s_valid_widths); ++i)
    {
        crc_result_t block_result = 0;
        crc_result_t stream_result;
        int const rc = WilliamsCRC_CalculateBlockCrc(s, 9, s_valid_widths[i], 0, &block_result);

        TEST_INT_EQ(0, rc);

        stream_result = calculate_via_streaming_(s, 9, s_valid_widths[i], 0);

        TEST_INT_EQ(block_result, stream_result);
    }

    WilliamsCRC_Uninit();
}

static void test_streaming_chunked_matches_oneshot(void)
{
    char const* const s = "Hello, WilliamsCRC!";
    size_t const len = strlen(s);
    WilliamsCRC_t wcrc = NULL;
    crc_result_t oneshot = 0;
    crc_result_t chunked = 0;
    size_t offset;

    TEST_INT_EQ(0, WilliamsCRC_Init());

    TEST_INT_EQ(0, WilliamsCRC_CalculateBlockCrc(s, len, 32, 0, &oneshot));

    TEST_INT_EQ(0, WilliamsCRC_Create(32, 0, &wcrc));
    TEST_PTR_NE(NULL, wcrc);

    for (offset = 0; offset != len; ++offset)
    {
        WilliamsCRC_Add(wcrc, s + offset, 1);
    }

    WilliamsCRC_GetCRC(wcrc, &chunked);
    WilliamsCRC_Destroy(wcrc);

    TEST_INT_EQ(oneshot, chunked);

    WilliamsCRC_Uninit();
}

static void test_get_crc_before_add(void)
{
    WilliamsCRC_t wcrc = NULL;
    crc_result_t result = 0xdeadbeef;

    TEST_INT_EQ(0, WilliamsCRC_Init());
    TEST_INT_EQ(0, WilliamsCRC_Create(32, 0, &wcrc));

    WilliamsCRC_GetCRC(wcrc, &result);
    TEST_INT_EQ(0u, result);

    WilliamsCRC_Destroy(wcrc);
    WilliamsCRC_Uninit();
}


/* ///////////////////////////// end of file //////////////////////////// */
