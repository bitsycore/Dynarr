#ifndef DYNARR_30F075E42018AC5D_H
#define DYNARR_30F075E42018AC5D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNARR___STRCONC___2(x, y) x##y
#define DYNARR___STRCONC(x, y) DYNARR___STRCONC___2(x, y)

#define DYNARR(NAME) DYNARR___STRCONC(dynarr_, NAME)

#define DYNARR_New(NAME) DYNARR___STRCONC(new_, NAME)
#define DYNARR_Init(NAME) DYNARR___STRCONC(init_, NAME)
#define DYNARR_Append(NAME) DYNARR___STRCONC(append_, NAME)
#define DYNARR_Clear(NAME) DYNARR___STRCONC(clear_, NAME)
#define DYNARR_Free(NAME) DYNARR___STRCONC(free_, NAME)
#define DYNARR_Delete(NAME) DYNARR___STRCONC(delete_, NAME)
#define DYNARR_Get(NAME) DYNARR___STRCONC(get_, NAME)
#define DYNARR_Size(NAME) DYNARR___STRCONC(size_, NAME)
#define DYNARR_Capacity(NAME) DYNARR___STRCONC(capacity_, NAME)
#define DYNARR_Concat(NAME) DYNARR___STRCONC(concat_, NAME)
#define DYNARR_Resize(NAME) DYNARR___STRCONC(resize_, NAME)
#define DYNARR_Insert(NAME) DYNARR___STRCONC(insert_, NAME)
#define DYNARR_Remove(NAME) DYNARR___STRCONC(remove_, NAME)
#define DYNARR_Find(NAME) DYNARR___STRCONC(find_, NAME)

#define DYNARR_DECLARE_NAME(T, NAME)                                    \
                                                                        \
    typedef struct {                                                    \
        T* data;                                                        \
        size_t size;                                                    \
        size_t capacity;                                                \
        bool is_freed;                                                  \
    } NAME;                                                             \
                                                                        \
    NAME* DYNARR_New(NAME)(size_t initial_capacity);                    \
    void DYNARR_Init(NAME)(NAME* array, size_t initial_capacity);       \
    void DYNARR_Append(NAME)(NAME* array, T value);                     \
    void DYNARR_Clear(NAME)(NAME* array);                               \
    void DYNARR_Free(NAME)(NAME* array);                                \
    void DYNARR_Delete(NAME)(NAME* array);                              \
    T DYNARR_Get(NAME)(NAME* array, size_t index);                      \
    size_t DYNARR_Size(NAME)(NAME* array);                              \
    size_t DYNARR_Capacity(NAME)(NAME* array);                          \
    void DYNARR_Concat(NAME)(NAME* dest, NAME* src);                    \
    void DYNARR_Resize(NAME)(NAME* array, size_t new_capacity);         \
    void DYNARR_Insert(NAME)(NAME* array, size_t index, T value);       \
    void DYNARR_Remove(NAME)(NAME* array, size_t index);                \
    int DYNARR_Find(NAME)(NAME* array, T value);                        \

#define DYNARR_IMPLEMENT_NAME(T, NAME)                                              \
    NAME* DYNARR_New(NAME)(size_t initial_capacity) {                               \
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
    void DYNARR_Init(NAME)(NAME* array, size_t initial_capacity) {                  \
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
    void DYNARR_Append(NAME)(NAME* array, T value) {                                \
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
    void DYNARR_Clear(NAME)(NAME* array) {                                          \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        array->size = 0;                                                            \
    }                                                                               \
                                                                                    \
    void DYNARR_Free(NAME)(NAME* array) {                                           \
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
    void DYNARR_Delete(NAME)(NAME* array) {                                         \
        DYNARR_Free(NAME)(array);                                                   \
        free(array);                                                                \
    }                                                                               \
                                                                                    \
    T DYNARR_Get(NAME)(NAME* array, size_t index) {                                 \
        if (index < array->size) {                                                  \
            return array->data[index];                                              \
        } else {                                                                    \
            perror("Index out of bounds");                                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
    }                                                                               \
                                                                                    \
    size_t DYNARR_Size(NAME)(NAME* array) {                                         \
        return array->size;                                                         \
    }                                                                               \
                                                                                    \
    size_t DYNARR_Capacity(NAME)(NAME* array) {                                     \
        return array->capacity;                                                     \
    }                                                                               \
                                                                                    \
    void DYNARR_Concat(NAME)(NAME* dest, NAME* src) {                               \
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
    void DYNARR_Resize(NAME)(NAME* array, size_t new_capacity) {                    \
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
    void DYNARR_Insert(NAME)(NAME* array, size_t index, T value) {                  \
        if (array->is_freed) {                                                      \
            perror("Array has been freed");                                         \
            return;                                                                 \
        }                                                                           \
        if (index > array->size) {                                                  \
            perror("Index out of bounds");                                          \
            return;                                                                 \
        }                                                                           \
        if (array->size == array->capacity) {                                       \
            DYNARR_Resize(NAME)(array, array->capacity * 2);                        \
        }                                                                           \
        memmove(&array->data[index + 1], &array->data[index],                       \
                (array->size - index) * sizeof(T));                                 \
        array->data[index] = value;                                                 \
        array->size++;                                                              \
    }                                                                               \
                                                                                    \
    void DYNARR_Remove(NAME)(NAME* array, size_t index) {                           \
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
    int DYNARR_Find(NAME)(NAME* array, T value) {                                   \
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

#define DYNARR_IMPLEMENT(T) DYNARR_IMPLEMENT_NAME(T, DYNARR(T))
#define DYNARR_DECLARE(T) DYNARR_DECLARE_NAME(T, DYNARR(T))

#endif // DYNARR_30F075E42018AC5D_H