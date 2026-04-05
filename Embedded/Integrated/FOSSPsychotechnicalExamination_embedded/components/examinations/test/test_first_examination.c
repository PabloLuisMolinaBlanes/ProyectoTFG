#include "unity.h"

TEST_CASE("Sanity test (are tests working overall)?", "")
{
    const int values[] = { 0 };
    TEST_ASSERT_EQUAL(0, values[0]);
}