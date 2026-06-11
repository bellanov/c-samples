#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Simple testing framework for C.
 * Allows defining and running tests with assertions.
 */

#define TEST_PASS 0
#define TEST_FAIL 1

/* Global test state */
static int test_passed = 0;
static int test_failed = 0;
static const char *current_test = "";

/**
 * Begin a test case.
 */
#define TEST_CASE(name)                                                                            \
    void test_##name(void);                                                                        \
    static struct test_item test_item_##name __attribute__((unused)) = {#name, test_##name};       \
    void test_##name(void)

/**
 * Assert that a condition is true.
 */
#define ASSERT_TRUE(condition, message)                                                            \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            fprintf(stderr, "FAIL: %s - %s\n", current_test, message);                             \
            test_failed++;                                                                         \
            return;                                                                                \
        }                                                                                          \
    } while (0)

/**
 * Assert that a condition is false.
 */
#define ASSERT_FALSE(condition, message) ASSERT_TRUE(!(condition), message)

/**
 * Assert that two integers are equal.
 */
#define ASSERT_INT_EQ(actual, expected)                                                            \
    do {                                                                                           \
        if ((actual) != (expected)) {                                                              \
            fprintf(stderr, "FAIL: %s - Expected %ld, got %ld\n", current_test, (long) (expected), \
                    (long) (actual));                                                              \
            test_failed++;                                                                         \
            return;                                                                                \
        }                                                                                          \
    } while (0)

/**
 * Assert that two strings are equal.
 */
#define ASSERT_STR_EQ(actual, expected)                                                            \
    do {                                                                                           \
        if (strcmp((actual), (expected)) != 0) {                                                   \
            fprintf(stderr, "FAIL: %s - Expected '%s', got '%s'\n", current_test, expected,        \
                    actual);                                                                       \
            test_failed++;                                                                         \
            return;                                                                                \
        }                                                                                          \
    } while (0)

/**
 * Assert that a pointer is NULL.
 */
#define ASSERT_NULL(ptr) ASSERT_TRUE((ptr) == NULL, "Expected NULL pointer")

/**
 * Assert that a pointer is not NULL.
 */
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE((ptr) != NULL, "Expected non-NULL pointer")

/**
 * Mark a test as passed.
 */
#define TEST_PASS_MARK()                                                                           \
    do {                                                                                           \
        printf("PASS: %s\n", current_test);                                                        \
        test_passed++;                                                                             \
    } while (0)

/* Test item structure */
struct test_item {
    const char *name;
    void (*func)(void);
};

/**
 * Run a single test.
 */
static void run_test(const struct test_item *test)
{
    current_test = test->name;
    test_failed = 0;
    test->func();
    if (test_failed == 0) {
        TEST_PASS_MARK();
    }
}

/**
 * Print test summary.
 */
static void print_summary(void)
{
    int total = test_passed + test_failed;
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total: %d\n", total);
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);
    printf("========================\n");
}

#endif /* TEST_FRAMEWORK_H */
