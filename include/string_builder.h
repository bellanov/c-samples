#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stddef.h>

/**
 * @file string_builder.h
 * @brief A modern C library demonstrating proper design patterns.
 *
 * This module showcases:
 * - Proper header guards
 * - Opaque data structures (encapsulation)
 * - Error handling with status codes
 * - Memory safety practices
 * - Well-documented API
 */

/**
 * Opaque handle to a string builder.
 * Users should not access the internals directly.
 */
typedef struct string_builder StringBuilderHandle;

/**
 * Status codes for string builder operations.
 */
typedef enum {
    SB_OK = 0,           /**< Operation successful */
    SB_ERR_NULL_PTR = 1, /**< NULL pointer provided */
    SB_ERR_ALLOC = 2,    /**< Memory allocation failed */
    SB_ERR_INVALID = 3   /**< Invalid operation */
} StringBuilderStatus;

/**
 * Creates a new string builder.
 *
 * @param capacity Initial capacity of the builder
 * @return Pointer to newly created string builder, or NULL on failure
 */
StringBuilderHandle *string_builder_create(size_t capacity);

/**
 * Destroys a string builder and frees its resources.
 *
 * @param builder Pointer to string builder (safe to call with NULL)
 */
void string_builder_destroy(StringBuilderHandle *builder);

/**
 * Appends a string to the builder.
 *
 * @param builder Pointer to string builder
 * @param str String to append
 * @return Status code indicating success or failure
 */
StringBuilderStatus string_builder_append(StringBuilderHandle *builder, const char *str);

/**
 * Appends a character to the builder.
 *
 * @param builder Pointer to string builder
 * @param ch Character to append
 * @return Status code indicating success or failure
 */
StringBuilderStatus string_builder_append_char(StringBuilderHandle *builder, char ch);

/**
 * Gets the current length of the built string.
 *
 * @param builder Pointer to string builder
 * @return Length of the current string, or 0 if builder is NULL
 */
size_t string_builder_length(const StringBuilderHandle *builder);

/**
 * Gets a null-terminated C string from the builder.
 * The returned string is valid until the next modification of the builder.
 *
 * @param builder Pointer to string builder
 * @return Pointer to the internal string, or empty string if builder is NULL
 */
const char *string_builder_get(const StringBuilderHandle *builder);

/**
 * Clears the builder, resetting its length to 0.
 *
 * @param builder Pointer to string builder
 * @return Status code indicating success or failure
 */
StringBuilderStatus string_builder_clear(StringBuilderHandle *builder);

#endif /* STRING_BUILDER_H */
