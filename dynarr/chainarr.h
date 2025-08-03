#ifndef CHAINARR_f24c91716e4b9c7968a0bb90f2b60a4a7ea4a56e063d1d6ded0a0c6b6c9de5c9_H
#define CHAINARR_f24c91716e4b9c7968a0bb90f2b60a4a7ea4a56e063d1d6ded0a0c6b6c9de5c9_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CHAINARR_STRCAT_(x, y) x##y
#define CHAINARR_STRCAT(x, y) CHAINARR_STRCAT_(x, y)

#define CHAINARR_DEFINE_NAME(T, NAME)                                               \
    typedef struct CHAINARR_STRCAT(NAME, _node) {                                   \
        T value;                                                                    \
        struct CHAINARR_STRCAT(NAME, _node)* next;                                  \
    } CHAINARR_STRCAT(NAME, _node);                                                 \
                                                                                    \
    typedef struct {                                                                \
        CHAINARR_STRCAT(NAME, _node)* head;                                         \
        CHAINARR_STRCAT(NAME, _node)* tail;                                         \
        size_t size;                                                                \
        bool is_freed;                                                              \
    } NAME;                                                                         \
                                                                                    \
                                                                                    \
    NAME* CHAINARR_STRCAT(new_, NAME)() {                                           \
        NAME* list = (NAME*)malloc(sizeof(NAME));                                   \
        if (!list) {                                                                \
            perror("Failed to allocate memory for list structure");                 \
            return NULL;                                                            \
        }                                                                           \
        list->head = NULL;                                                          \
        list->tail = NULL;                                                          \
        list->size = 0;                                                             \
        list->is_freed = false;                                                     \
        return list;                                                                \
    }                                                                               \
                                                                                    \
    void CHAINARR_STRCAT(append_, NAME)(NAME* list, T value) {                      \
        if (list->is_freed) {                                                       \
            perror("List has been freed");                                          \
            return;                                                                 \
        }                                                                           \
        CHAINARR_STRCAT(NAME, _node)* new_node =                                    \
            (CHAINARR_STRCAT(NAME, _node)*)malloc(sizeof(CHAINARR_STRCAT(NAME, _node))); \
        if (!new_node) {                                                            \
            perror("Failed to allocate memory for new node");                       \
            return;                                                                 \
        }                                                                           \
        new_node->value = value;                                                    \
        new_node->next = NULL;                                                      \
        if (list->tail) {                                                           \
            list->tail->next = new_node;                                            \
        } else {                                                                    \
            list->head = new_node;                                                  \
        }                                                                           \
        list->tail = new_node;                                                      \
        list->size++;                                                               \
    }                                                                               \
                                                                                    \
    void CHAINARR_STRCAT(clear_, NAME)(NAME* list) {                                \
        if (list->is_freed) {                                                       \
            perror("List has been freed");                                          \
            return;                                                                 \
        }                                                                           \
        CHAINARR_STRCAT(NAME, _node)* current = list->head;                         \
        while (current) {                                                           \
            CHAINARR_STRCAT(NAME, _node)* next = current->next;                     \
            free(current);                                                          \
            current = next;                                                         \
        }                                                                           \
        list->head = NULL;                                                          \
        list->tail = NULL;                                                          \
        list->size = 0;                                                             \
    }                                                                               \
                                                                                    \
    void CHAINARR_STRCAT(free_, NAME)(NAME* list) {                                 \
        if (list->is_freed) {                                                       \
            perror("List has already been freed");                                  \
            return;                                                                 \
        }                                                                           \
        CHAINARR_STRCAT(clear_, NAME)(list);                                        \
        list->is_freed = true;                                                      \
    }                                                                               \
                                                                                    \
    void CHAINARR_STRCAT(delete_, NAME)(NAME* list) {                               \
        CHAINARR_STRCAT(free_, NAME)(list);                                         \
        free(list);                                                                 \
    }                                                                               \
                                                                                    \
    T CHAINARR_STRCAT(get_, NAME)(NAME* list, size_t index) {                       \
        if (index >= list->size) {                                                  \
            perror("Index out of bounds");                                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
        CHAINARR_STRCAT(NAME, _node)* current = list->head;                         \
        for (size_t i = 0; i < index; i++) {                                        \
            current = current->next;                                                \
        }                                                                           \
        return current->value;                                                      \
    }                                                                               \
                                                                                    \
    size_t CHAINARR_STRCAT(size_, NAME)(NAME* list) {                               \
        return list->size;                                                          \
    }  

#define CHAINARR_DEFINE(T) CHAINARR_DEFINE_NAME(T, CHAINARR_STRCAT(chainarr_, T))

#endif//CHAINARR_f24c91716e4b9c7968a0bb90f2b60a4a7ea4a56e063d1d6ded0a0c6b6c9de5c9_H