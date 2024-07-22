#ifndef DWA_DYNARR_H
#define DWA_DYNARR_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DYNARR_STRCONC_(x, y) x##y
#define DYNARR_STRCONC(x, y) DYNARR_STRCONC_(x, y)

#define DYNARR_PTR(NAME) DYNARR_STRCONC(PTR_, NAME)
#define DYNARR_NEW(NAME) DYNARR_STRCONC(new_, NAME)
#define DYNARR_INIT(NAME) DYNARR_STRCONC(init_, NAME)
#define DYNARR_APPEND(NAME) DYNARR_STRCONC(append_, NAME)
#define DYNARR_CLEAR(NAME) DYNARR_STRCONC(clear_, NAME)
#define DYNARR_FREE(NAME) DYNARR_STRCONC(free_, NAME)
#define DYNARR_DELETE(NAME) DYNARR_STRCONC(delete_, NAME)
#define DYNARR_GET(NAME) DYNARR_STRCONC(get_, NAME)
#define DYNARR_SIZE(NAME) DYNARR_STRCONC(size_, NAME)
#define DYNARR_CAPACITY(NAME) DYNARR_STRCONC(capacity_, NAME)
#define DYNARR_CONCAT(NAME) DYNARR_STRCONC(concat_, NAME)
#define DYNARR_RESIZE(NAME) DYNARR_STRCONC(resize_, NAME)
#define DYNARR_INSERT(NAME) DYNARR_STRCONC(insert_, NAME)
#define DYNARR_REMOVE(NAME) DYNARR_STRCONC(remove_, NAME)
#define DYNARR_FIND(NAME) DYNARR_STRCONC(find_, NAME)

#define DYNARR_DEFINE_NAME(T, NAME)                                                 \
    typedef struct {                                                                \
        T* data;                                                                    \
        size_t size;                                                                \
        size_t capacity;                                                            \
        bool is_freed;                                                              \
    } NAME;                                                                         \
                                                                                    \
    typedef NAME* DYNARR_PTR(NAME);                                                 \
                                                                                    \
    DYNARR_PTR(NAME) DYNARR_NEW(NAME)(size_t initial_capacity) {                    \
        NAME* array = (NAME*)malloc(sizeof(NAME));                                  \
        if (!array) {                                                               \
            perror("Failed to allocate memory for array structure");                \
            return NULL;                                                            \
        }                                                                           \
        array->data = (T*)malloc(initial_capacity * sizeof(T));                     \
        if (!array->data) {                                                         \
            perror("Failed to allocate memory for array data");                     \
            free(array);                                                            \
            return NULL;                                                            \
        }                                                                           \
        array->size = 0;                                                            \
        array->capacity = initial_capacity;                                         \
        array->is_freed = false;                                                    \
        return array;                                                               \
    }                                                                               \
                                                                                    \
    void DYNARR_INIT(NAME)(DYNARR_PTR(NAME) array, size_t initial_capacity) {       \
        array->data = (T*)malloc(initial_capacity * sizeof(T));                     \
        if (!array->data) {                                                         \
            perror("Failed to allocate memory for array data");                     \
            return;                                                                 \
        }                                                                           \
        array->size = 0;                                                            \
        array->capacity = initial_capacity;                                         \
        array->is_freed = false;                                                    \
    }                                                                               \
                                                                                    \
    void DYNARR_APPEND(NAME)(DYNARR_PTR(NAME) array, T value) {                     \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        if (array->size == array->capacity) {                                       \
            array->capacity *= 2;                                                   \
            T* new_data = (T*)realloc(array->data, array->capacity * sizeof(T));    \
            if (!new_data) {                                                        \
                perror("Failed to reallocate memory for array data");               \
                return;                                                             \
            }                                                                       \
            array->data = new_data;                                                 \
        }                                                                           \
        array->data[array->size++] = value;                                         \
    }                                                                               \
                                                                                    \
    void DYNARR_CLEAR(NAME)(DYNARR_PTR(NAME) array) {                               \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        array->size = 0;                                                            \
    }                                                                               \
                                                                                    \
    void DYNARR_FREE(NAME)(DYNARR_PTR(NAME) array) {                                \
        if (array->is_freed) {                                                      \
            perror("Array has already been freed");                                 \
            return;                                                                 \
        }                                                                           \
        free(array->data);                                                          \
        array->size = 0;                                                            \
        array->capacity = 0;                                                        \
        array->is_freed = true;                                                     \
    }                                                                               \
                                                                                    \
    void DYNARR_DELETE(NAME)(DYNARR_PTR(NAME) array) {                              \
        DYNARR_FREE(NAME)(array);                                                   \
        free(array);                                                                \
    }                                                                               \
                                                                                    \
    T DYNARR_GET(NAME)(DYNARR_PTR(NAME) array, size_t index) {                      \
        if (index < array->size) {                                                  \
            return array->data[index];                                              \
        } else {                                                                    \
            perror("Index out of bounds");                                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
    }                                                                               \
                                                                                    \
    size_t DYNARR_SIZE(NAME)(DYNARR_PTR(NAME) array) {                              \
        return array->size;                                                         \
    }                                                                               \
                                                                                    \
    size_t DYNARR_CAPACITY(NAME)(DYNARR_PTR(NAME) array) {                          \
        return array->capacity;                                                     \
    }                                                                               \
                                                                                    \
    void DYNARR_CONCAT(NAME)(DYNARR_PTR(NAME) dest, DYNARR_PTR(NAME) src) {         \
        if (dest->is_freed || src->is_freed) {                                      \
            perror("One of the arrays has been freed");                             \
            return;                                                                 \
        }                                                                           \
        size_t new_size = dest->size + src->size;                                   \
        if (new_size > dest->capacity) {                                            \
            size_t new_capacity = new_size * 2;                                     \
            T* new_data = (T*)realloc(dest->data, new_capacity * sizeof(T));        \
            if (!new_data) {                                                        \
                perror("Failed to reallocate memory for concatenation");            \
                return;                                                             \
            }                                                                       \
            dest->data = new_data;                                                  \
            dest->capacity = new_capacity;                                          \
        }                                                                           \
        memcpy(dest->data + dest->size, src->data, src->size * sizeof(T));          \
        dest->size = new_size;                                                      \
    }                                                                               \
                                                                                    \
    void DYNARR_RESIZE(NAME)(DYNARR_PTR(NAME) array, size_t new_capacity) {         \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        T* new_data = (T*)realloc(array->data, new_capacity * sizeof(T));           \
        if (!new_data) {                                                            \
            perror("Failed to resize array");                                       \
            return;                                                                 \
        }                                                                           \
        array->data = new_data;                                                     \
        array->capacity = new_capacity;                                             \
        if (array->size > new_capacity) {                                           \
            array->size = new_capacity;                                             \
        }                                                                           \
    }                                                                               \
                                                                                    \
    void DYNARR_INSERT(NAME)(DYNARR_PTR(NAME) array, size_t index, T value) {       \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        if (index > array->size) {                                                  \
            perror("Index out of bounds");                                          \
            return;                                                                 \
        }                                                                           \
        if (array->size == array->capacity) {                                       \
            DYNARR_RESIZE(NAME)(array, array->capacity * 2);                        \
        }                                                                           \
        memmove(&array->data[index + 1], &array->data[index],                       \
                (array->size - index) * sizeof(T));                                 \
        array->data[index] = value;                                                 \
        array->size++;                                                              \
    }                                                                               \
                                                                                    \
    void DYNARR_REMOVE(NAME)(DYNARR_PTR(NAME) array, size_t index) {                \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        if (index >= array->size) {                                                 \
            perror("Index out of bounds");                                          \
            return;                                                                 \
        }                                                                           \
        memmove(&array->data[index], &array->data[index + 1],                       \
                (array->size - index - 1) * sizeof(T));                             \
        array->size--;                                                              \
    }                                                                               \
                                                                                    \
    int DYNARR_FIND(NAME)(DYNARR_PTR(NAME) array, T value) {                        \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return -1;                                                              \
        }                                                                           \
        for (size_t i = 0; i < array->size; i++) {                                  \
            if (memcmp(&array->data[i], &value, sizeof(T)) == 0) {                  \
                return i;                                                           \
            }                                                                       \
        }                                                                           \
        return -1;                                                                  \
    }

#define DYNARR_DEFINE(T) DYNARR_DEFINE_NAME(T, DYNARR_STRCONC(dynarr_, T))

#endif //DWA_DYNARR_H