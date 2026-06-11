#include "string_builder.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 64
#define GROWTH_FACTOR 1.5

/**
 * Internal structure of the string builder.
 * This is only visible to the implementation.
 */
struct string_builder {
    char* data;
    size_t length;
    size_t capacity;
};

StringBuilderHandle* string_builder_create(size_t capacity) {
    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }

    StringBuilderHandle* builder = (StringBuilderHandle*)malloc(sizeof(StringBuilderHandle));
    if (builder == NULL) {
        return NULL;
    }

    builder->data = (char*)malloc(capacity);
    if (builder->data == NULL) {
        free(builder);
        return NULL;
    }

    builder->data[0] = '\0';
    builder->length = 0;
    builder->capacity = capacity;

    return builder;
}

void string_builder_destroy(StringBuilderHandle* builder) {
    if (builder == NULL) {
        return;
    }

    free(builder->data);
    free(builder);
}

static StringBuilderStatus ensure_capacity(StringBuilderHandle* builder, size_t needed) {
    if (needed <= builder->capacity) {
        return SB_OK;
    }

    size_t new_capacity = (size_t)(builder->capacity * GROWTH_FACTOR);
    if (new_capacity < needed) {
        new_capacity = needed;
    }

    char* new_data = (char*)realloc(builder->data, new_capacity);
    if (new_data == NULL) {
        return SB_ERR_ALLOC;
    }

    builder->data = new_data;
    builder->capacity = new_capacity;
    return SB_OK;
}

StringBuilderStatus string_builder_append(StringBuilderHandle* builder, const char* str) {
    if (builder == NULL || str == NULL) {
        return SB_ERR_NULL_PTR;
    }

    size_t str_len = strlen(str);
    size_t needed = builder->length + str_len + 1;

    StringBuilderStatus status = ensure_capacity(builder, needed);
    if (status != SB_OK) {
        return status;
    }

    memcpy(builder->data + builder->length, str, str_len);
    builder->length += str_len;
    builder->data[builder->length] = '\0';

    return SB_OK;
}

StringBuilderStatus string_builder_append_char(StringBuilderHandle* builder, char ch) {
    if (builder == NULL) {
        return SB_ERR_NULL_PTR;
    }

    size_t needed = builder->length + 2;

    StringBuilderStatus status = ensure_capacity(builder, needed);
    if (status != SB_OK) {
        return status;
    }

    builder->data[builder->length] = ch;
    builder->length++;
    builder->data[builder->length] = '\0';

    return SB_OK;
}

size_t string_builder_length(const StringBuilderHandle* builder) {
    if (builder == NULL) {
        return 0;
    }
    return builder->length;
}

const char* string_builder_get(const StringBuilderHandle* builder) {
    if (builder == NULL) {
        return "";
    }
    return builder->data;
}

StringBuilderStatus string_builder_clear(StringBuilderHandle* builder) {
    if (builder == NULL) {
        return SB_ERR_NULL_PTR;
    }

    builder->length = 0;
    builder->data[0] = '\0';
    return SB_OK;
}
