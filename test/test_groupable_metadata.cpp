#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

// Exposes whether a button has property storage, to test that it is only allocated on first use.
class InspectableButton : public CtrlBtn
{
    public:
        using CtrlBtn::CtrlBtn;
        bool hasPropertyStorage() const { return this->propertyStorage != nullptr; }
};

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

static void test_groupable_storage_is_allocated_on_first_use()
{
    InspectableButton button(1, TEST_DEBOUNCE);
    TEST_ASSERT_FALSE(button.hasPropertyStorage());

    // Reading never allocates.
    TEST_ASSERT_EQUAL_INT(0, button.getInteger("note"));
    TEST_ASSERT_FALSE(button.getBoolean("on"));
    TEST_ASSERT_EQUAL_STRING("", button.getString("name"));
    TEST_ASSERT_FALSE(button.hasPropertyStorage());

    button.setInteger("note", 60);
    TEST_ASSERT_TRUE(button.hasPropertyStorage());
    TEST_ASSERT_EQUAL_INT(60, button.getInteger("note"));
}

static void test_groupable_uses_provided_storage()
{
    CtrlProperties storage;
    InspectableButton button(1, TEST_DEBOUNCE);
    button.setProperties(storage);

    button.setInteger("note", 60);
    button.setBoolean("on", true);
    button.setString("name", "Kick");

    TEST_ASSERT_EQUAL_INT(3, storage.count);
    TEST_ASSERT_EQUAL_STRING("note", storage.properties[0].key);
    TEST_ASSERT_EQUAL_INT(60, button.getInteger("note"));
    TEST_ASSERT_TRUE(button.getBoolean("on"));
    TEST_ASSERT_EQUAL_STRING("Kick", button.getString("name"));
}

static void test_groupable_set_properties_keeps_existing_values()
{
    CtrlBtn button(1, TEST_DEBOUNCE);
    button.setInteger("note", 60);

    CtrlProperties storage;
    button.setProperties(storage);

    TEST_ASSERT_EQUAL_INT(1, storage.count);
    TEST_ASSERT_EQUAL_INT(60, button.getInteger("note"));
    button.setInteger("velocity", 100);
    TEST_ASSERT_EQUAL_INT(2, storage.count);
}

static void test_groupable_provided_storage_respects_limits()
{
    CtrlProperties storage;
    CtrlBtn button(1, TEST_DEBOUNCE);
    button.setProperties(storage);

    char key[8];
    for (int i = 0; i < CtrlProperties::MAX_PROPERTIES + 2; ++i) {
        snprintf(key, sizeof(key), "k%d", i);
        button.setInteger(key, i);
    }
    TEST_ASSERT_EQUAL_INT(CtrlProperties::MAX_PROPERTIES, storage.count);
    TEST_ASSERT_EQUAL_INT(0, button.getInteger("k9"));
}

static void test_groupable_copy_has_its_own_storage()
{
    CtrlBtn original(1, TEST_DEBOUNCE);
    original.setInteger("note", 60);

    CtrlBtn copy = original;
    TEST_ASSERT_EQUAL_INT(60, copy.getInteger("note"));

    copy.setInteger("note", 62);
    TEST_ASSERT_EQUAL_INT(60, original.getInteger("note"));
    TEST_ASSERT_EQUAL_INT(62, copy.getInteger("note"));

    CtrlBtn assigned(2, TEST_DEBOUNCE);
    assigned.setInteger("note", 1);
    assigned = original;
    TEST_ASSERT_EQUAL_INT(60, assigned.getInteger("note"));
    assigned = assigned; // Self-assignment keeps the values.
    TEST_ASSERT_EQUAL_INT(60, assigned.getInteger("note"));
}

static void test_groupable_copies_without_properties_stay_empty()
{
    InspectableButton original(1, TEST_DEBOUNCE);
    InspectableButton copy = original;
    TEST_ASSERT_FALSE(copy.hasPropertyStorage());
}

void run_groupable_metadata_tests()
{
    RUN_TEST(test_groupable_storage_is_allocated_on_first_use);
    RUN_TEST(test_groupable_uses_provided_storage);
    RUN_TEST(test_groupable_set_properties_keeps_existing_values);
    RUN_TEST(test_groupable_provided_storage_respects_limits);
    RUN_TEST(test_groupable_copy_has_its_own_storage);
    RUN_TEST(test_groupable_copies_without_properties_stay_empty);
    RUN_TEST(test_groupable_missing_integer_returns_zero);
    RUN_TEST(test_groupable_missing_boolean_returns_false);
    RUN_TEST(test_groupable_missing_string_returns_empty);
    RUN_TEST(test_groupable_overwrite_integer);
    RUN_TEST(test_groupable_overwrite_boolean);
    RUN_TEST(test_groupable_overwrite_string);
    RUN_TEST(test_groupable_type_mismatch_returns_default);
    RUN_TEST(test_groupable_multiple_properties);
}
