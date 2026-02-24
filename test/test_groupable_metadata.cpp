#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_groupable_missing_integer_returns_zero()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    TEST_ASSERT_EQUAL_INT(0, button.getInteger("nonexistent"));
}

static void test_groupable_missing_boolean_returns_false()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    TEST_ASSERT_FALSE(button.getBoolean("nonexistent"));
}

static void test_groupable_missing_string_returns_empty()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    TEST_ASSERT_EQUAL_STRING("", button.getString("nonexistent"));
}

static void test_groupable_overwrite_integer()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    button.setInteger("id", 10);
    TEST_ASSERT_EQUAL_INT(10, button.getInteger("id"));

    button.setInteger("id", 42);
    TEST_ASSERT_EQUAL_INT(42, button.getInteger("id"));
}

static void test_groupable_overwrite_boolean()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    button.setBoolean("active", true);
    TEST_ASSERT_TRUE(button.getBoolean("active"));

    button.setBoolean("active", false);
    TEST_ASSERT_FALSE(button.getBoolean("active"));
}

static void test_groupable_overwrite_string()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    button.setString("name", "first");
    TEST_ASSERT_EQUAL_STRING("first", button.getString("name"));

    button.setString("name", "second");
    TEST_ASSERT_EQUAL_STRING("second", button.getString("name"));
}

static void test_groupable_type_mismatch_returns_default()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    button.setInteger("val", 99);
    TEST_ASSERT_FALSE(button.getBoolean("val"));
    TEST_ASSERT_EQUAL_STRING("", button.getString("val"));

    button.setBoolean("flag", true);
    TEST_ASSERT_EQUAL_INT(0, button.getInteger("flag"));
    TEST_ASSERT_EQUAL_STRING("", button.getString("flag"));

    button.setString("label", "hello");
    TEST_ASSERT_EQUAL_INT(0, button.getInteger("label"));
    TEST_ASSERT_FALSE(button.getBoolean("label"));
}

static void test_groupable_multiple_properties()
{
    CtrlBtn button(1, TEST_DEBOUNCE);

    button.setInteger("id", 1);
    button.setString("name", "btn1");
    button.setBoolean("active", true);
    button.setInteger("channel", 5);

    TEST_ASSERT_EQUAL_INT(1, button.getInteger("id"));
    TEST_ASSERT_EQUAL_STRING("btn1", button.getString("name"));
    TEST_ASSERT_TRUE(button.getBoolean("active"));
    TEST_ASSERT_EQUAL_INT(5, button.getInteger("channel"));
}

void run_groupable_metadata_tests()
{
    RUN_TEST(test_groupable_missing_integer_returns_zero);
    RUN_TEST(test_groupable_missing_boolean_returns_false);
    RUN_TEST(test_groupable_missing_string_returns_empty);
    RUN_TEST(test_groupable_overwrite_integer);
    RUN_TEST(test_groupable_overwrite_boolean);
    RUN_TEST(test_groupable_overwrite_string);
    RUN_TEST(test_groupable_type_mismatch_returns_default);
    RUN_TEST(test_groupable_multiple_properties);
}
