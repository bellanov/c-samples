#include "string_builder.h"
#include "test_framework.h"
#include <stdio.h>
#include <string.h>

/* Test cases */

TEST_CASE(create_and_destroy)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);
    string_builder_destroy(builder);
}

TEST_CASE(append_string)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    StringBuilderStatus status = string_builder_append(builder, "Hello");
    ASSERT_INT_EQ(status, SB_OK);
    ASSERT_STR_EQ(string_builder_get(builder), "Hello");
    ASSERT_INT_EQ(string_builder_length(builder), 5);

    string_builder_destroy(builder);
}

TEST_CASE(append_multiple_strings)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    string_builder_append(builder, "Hello");
    string_builder_append(builder, " ");
    string_builder_append(builder, "World");

    ASSERT_STR_EQ(string_builder_get(builder), "Hello World");
    ASSERT_INT_EQ(string_builder_length(builder), 11);

    string_builder_destroy(builder);
}

TEST_CASE(append_char)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    string_builder_append_char(builder, 'H');
    string_builder_append_char(builder, 'i');

    ASSERT_STR_EQ(string_builder_get(builder), "Hi");
    ASSERT_INT_EQ(string_builder_length(builder), 2);

    string_builder_destroy(builder);
}

TEST_CASE(clear_builder)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    string_builder_append(builder, "Test");
    ASSERT_INT_EQ(string_builder_length(builder), 4);

    StringBuilderStatus status = string_builder_clear(builder);
    ASSERT_INT_EQ(status, SB_OK);
    ASSERT_INT_EQ(string_builder_length(builder), 0);
    ASSERT_STR_EQ(string_builder_get(builder), "");

    string_builder_destroy(builder);
}

TEST_CASE(growth_capacity)
{
    StringBuilderHandle *builder = string_builder_create(5);
    ASSERT_NOT_NULL(builder);

    /* Append string longer than initial capacity */
    StringBuilderStatus status = string_builder_append(builder, "This is a longer string");
    ASSERT_INT_EQ(status, SB_OK);
    ASSERT_STR_EQ(string_builder_get(builder), "This is a longer string");

    string_builder_destroy(builder);
}

TEST_CASE(null_pointer_handling)
{
    /* Test with NULL builder */
    StringBuilderStatus status = string_builder_append(NULL, "test");
    ASSERT_INT_EQ(status, SB_ERR_NULL_PTR);

    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    /* Test with NULL string */
    status = string_builder_append(builder, NULL);
    ASSERT_INT_EQ(status, SB_ERR_NULL_PTR);

    /* Safe operations with NULL builder */
    size_t len = string_builder_length(NULL);
    ASSERT_INT_EQ(len, 0);

    const char *str = string_builder_get(NULL);
    ASSERT_NOT_NULL(str);
    ASSERT_STR_EQ(str, "");

    /* Destroy NULL is safe */
    string_builder_destroy(NULL);

    string_builder_destroy(builder);
}

TEST_CASE(empty_string)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    /* Appending empty string should work */
    StringBuilderStatus status = string_builder_append(builder, "");
    ASSERT_INT_EQ(status, SB_OK);
    ASSERT_INT_EQ(string_builder_length(builder), 0);

    string_builder_destroy(builder);
}

TEST_CASE(mixed_operations)
{
    StringBuilderHandle *builder = string_builder_create(10);
    ASSERT_NOT_NULL(builder);

    string_builder_append(builder, "Hello");
    string_builder_append_char(builder, ' ');
    string_builder_append(builder, "World");
    string_builder_append_char(builder, '!');

    ASSERT_STR_EQ(string_builder_get(builder), "Hello World!");
    ASSERT_INT_EQ(string_builder_length(builder), 12);

    string_builder_clear(builder);
    ASSERT_INT_EQ(string_builder_length(builder), 0);

    string_builder_append(builder, "New");
    ASSERT_STR_EQ(string_builder_get(builder), "New");

    string_builder_destroy(builder);
}

/* Main test runner */
int main(void)
{
    printf("Running string builder tests...\n\n");

    struct test_item tests[] = {
        {"create_and_destroy", test_create_and_destroy},
        {"append_string", test_append_string},
        {"append_multiple_strings", test_append_multiple_strings},
        {"append_char", test_append_char},
        {"clear_builder", test_clear_builder},
        {"growth_capacity", test_growth_capacity},
        {"null_pointer_handling", test_null_pointer_handling},
        {"empty_string", test_empty_string},
        {"mixed_operations", test_mixed_operations},
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        run_test(&tests[i]);
    }

    print_summary();

    return test_failed > 0 ? 1 : 0;
}
