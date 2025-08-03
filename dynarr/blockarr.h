#ifndef BLOCKARR_fd0d24c21f5aa2bdbac83e7d2cf4215c0617d83a3634048a168163ab9106243c_H
#define BLOCKARR_fd0d24c21f5aa2bdbac83e7d2cf4215c0617d83a3634048a168163ab9106243c_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCKARR__STRCAT_(x, y) x##y
#define BLOCKARR__STRCAT(x, y) BLOCKARR__STRCAT_(x, y)

#define BLOCKARR_DEFINE_NAME(T, NAME)                                               \
    typedef struct BLOCKARR__STRCAT(NAME, _block) {                                 \
        T* data;                                                                    \
        size_t capacity;                                                            \
        struct BLOCKARR__STRCAT(NAME, _block)* next;                                \
    } BLOCKARR__STRCAT(NAME, _block);                                               \
                                                                                    \
    typedef struct {                                                                \
        BLOCKARR__STRCAT(NAME, _block)* head;                                       \
        BLOCKARR__STRCAT(NAME, _block)* tail;                                       \
        size_t size;                                                                \
        size_t block_size;                                                          \
        bool is_freed;                                                              \
    } NAME;                                                                         \
                                                                                    \
                                                                                    \
    NAME* BLOCKARR__STRCAT(new_, NAME)(size_t block_size) {                         \
        NAME* list = (NAME*)malloc(sizeof(NAME));                                   \
        if (!list) {                                                                \
            perror("Failed to allocate memory for list structure");                 \
            return NULL;                                                            \
        }                                                                           \
        BLOCKARR__STRCAT(NAME, _block)* block = (BLOCKARR__STRCAT(NAME, _block)*)malloc(sizeof(BLOCKARR__STRCAT(NAME, _block))); \
        if (!block) {                                                               \
            perror("Failed to allocate memory for initial block");                  \
            free(list);                                                             \
            return NULL;                                                            \
        }                                                                           \
        block->data = (T*)malloc(block_size * sizeof(T));                           \
        if (!block->data) {                                                         \
            perror("Failed to allocate memory for block data");                     \
            free(block);                                                            \
            free(list);                                                             \
            return NULL;                                                            \
        }                                                                           \
        block->capacity = block_size;                                               \
        block->next = NULL;                                                         \
        list->head = block;                                                         \
        list->tail = block;                                                         \
        list->size = 0;                                                             \
        list->block_size = block_size;                                              \
        list->is_freed = false;                                                     \
        return list;                                                                \
    }                                                                               \
                                                                                    \
    void BLOCKARR__STRCAT(append_, NAME)(NAME* list, T value) {                     \
        if (list->is_freed) {                                                       \
            perror("List has been freed");                                          \
            return;                                                                 \
        }                                                                           \
        if (list->size % list->block_size == 0 && list->size != 0) {                \
            BLOCKARR__STRCAT(NAME, _block)* new_block = (BLOCKARR__STRCAT(NAME, _block)*)malloc(sizeof(BLOCKARR__STRCAT(NAME, _block))); \
            if (!new_block) {                                                       \
                perror("Failed to allocate memory for new block");                  \
                return;                                                             \
            }                                                                       \
            new_block->data = (T*)malloc(list->block_size * sizeof(T));             \
            if (!new_block->data) {                                                 \
                perror("Failed to allocate memory for new block data");             \
                free(new_block);                                                    \
                return;                                                             \
            }                                                                       \
            new_block->capacity = list->block_size;                                 \
            new_block->next = NULL;                                                 \
            list->tail->next = new_block;                                           \
            list->tail = new_block;                                                 \
        }                                                                           \
        size_t index_in_block = list->size % list->block_size;                      \
        list->tail->data[index_in_block] = value;                                   \
        list->size++;                                                               \
    }                                                                               \
                                                                                    \
    void BLOCKARR__STRCAT(clear_, NAME)(NAME* list) {                               \
        if (list->is_freed) {                                                       \
            perror("List has been freed");                                          \
            return;                                                                 \
        }                                                                           \
        BLOCKARR__STRCAT(NAME, _block)* current = list->head;                       \
        while (current) {                                                           \
            BLOCKARR__STRCAT(NAME, _block)* next = current->next;                   \
            free(current->data);                                                    \
            free(current);                                                          \
            current = next;                                                         \
        }                                                                           \
        list->head = NULL;                                                          \
        list->tail = NULL;                                                          \
        list->size = 0;                                                             \
    }                                                                               \
                                                                                    \
    void BLOCKARR__STRCAT(free_, NAME)(NAME* list) {                                \
        if (list->is_freed) {                                                       \
            perror("List has already been freed");                                  \
            return;                                                                 \
        }                                                                           \
        BLOCKARR__STRCAT(clear_, NAME)(list);                                       \
        list->is_freed = true;                                                      \
    }                                                                               \
                                                                                    \
    void BLOCKARR__STRCAT(delete_, NAME)(NAME* list) {                              \
        BLOCKARR__STRCAT(free_, NAME)(list);                                        \
        free(list);                                                                 \
    }                                                                               \
                                                                                    \
    T BLOCKARR__STRCAT(get_, NAME)(NAME* list, size_t index) {                      \
        if (index >= list->size) {                                                  \
            perror("Index out of bounds");                                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
        size_t block_index = index / list->block_size;                              \
        size_t index_in_block = index % list->block_size;                           \
        BLOCKARR__STRCAT(NAME, _block)* current = list->head;                       \
        for (size_t i = 0; i < block_index; i++) {                                  \
            current = current->next;                                                \
        }                                                                           \
        return current->data[index_in_block];                                       \
    }                                                                               \
                                                                                    \
    size_t BLOCKARR__STRCAT(size_, NAME)(NAME* list) {                              \
        return list->size;                                                          \
    }                                                                               \


#define BLOCKARR_DEFINE(T) BLOCKARR_DEFINE_NAME(T, BLOCKARR__STRCAT(blockarr_, T))

#endif //BLOCKARR_fd0d24c21f5aa2bdbac83e7d2cf4215c0617d83a3634048a168163ab9106243c_H
