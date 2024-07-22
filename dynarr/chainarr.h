//
// Created by dwa on 22/07/2024.
//

#ifndef DWA_CHAINARR_H
#define DWA_CHAINARR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CHAINARR_CONCATENATE_(x, y) x##y
#define CHAINARR_CONCATENATE(x, y) CHAINARR_CONCATENATE_(x, y)

#define CHAINARR_DEFINE_NAME(T, NAME)                                                \
    typedef struct CHAINARR_CONCATENATE(NAME, _node) {                               \
        T value;                                                                   \
        struct CHAINARR_CONCATENATE(NAME, _node)* next;                              \
    } CHAINARR_CONCATENATE(NAME, _node);                                             \
                                                                                   \
    typedef struct {                                                               \
        CHAINARR_CONCATENATE(NAME, _node)* head;                                     \
        CHAINARR_CONCATENATE(NAME, _node)* tail;                                     \
        size_t size;                                                               \
        bool is_freed;                                                             \
    } NAME;                                                                        \
                                                                                   \
                                                                                   \
    NAME* CHAINARR_CONCATENATE(new_, NAME)() {                                     \
        NAME* list = (NAME*)malloc(sizeof(NAME));                                  \
        if (!list) {                                                               \
            perror("Failed to allocate memory for list structure");                \
            return NULL;                                                           \
        }                                                                          \
        list->head = NULL;                                                         \
        list->tail = NULL;                                                         \
        list->size = 0;                                                            \
        list->is_freed = false;                                                    \
        return list;                                                               \
    }                                                                              \
                                                                                   \
    void CHAINARR_CONCATENATE(append_, NAME)(NAME* list, T value) {                  \
        if (list->is_freed) {                                                      \
            perror("List has been freed");                                         \
            return;                                                                \
        }                                                                          \
        CHAINARR_CONCATENATE(NAME, _node)* new_node = (CHAINARR_CONCATENATE(NAME, _node)*)malloc(sizeof(CHAINARR_CONCATENATE(NAME, _node))); \
        if (!new_node) {                                                           \
            perror("Failed to allocate memory for new node");                      \
            return;                                                                \
        }                                                                          \
        new_node->value = value;                                                   \
        new_node->next = NULL;                                                     \
        if (list->tail) {                                                          \
            list->tail->next = new_node;                                           \
        } else {                                                                   \
            list->head = new_node;                                                 \
        }                                                                          \
        list->tail = new_node;                                                     \
        list->size++;                                                              \
    }                                                                              \
                                                                                   \
    void CHAINARR_CONCATENATE(clear_, NAME)(NAME* list) {                            \
        if (list->is_freed) {                                                      \
            perror("List has been freed");                                         \
            return;                                                                \
        }                                                                          \
        CHAINARR_CONCATENATE(NAME, _node)* current = list->head;                     \
        while (current) {                                                          \
            CHAINARR_CONCATENATE(NAME, _node)* next = current->next;                 \
            free(current);                                                         \
            current = next;                                                        \
        }                                                                          \
        list->head = NULL;                                                         \
        list->tail = NULL;                                                         \
        list->size = 0;                                                            \
    }                                                                              \
                                                                                   \
    void CHAINARR_CONCATENATE(free_, NAME)(NAME* list) {                             \
        if (list->is_freed) {                                                      \
            perror("List has already been freed");                                 \
            return;                                                                \
        }                                                                          \
        CHAINARR_CONCATENATE(clear_, NAME)(list);                                    \
        list->is_freed = true;                                                     \
    }                                                                              \
                                                                                   \
    void CHAINARR_CONCATENATE(delete_, NAME)(NAME* list) {                           \
        CHAINARR_CONCATENATE(free_, NAME)(list);                                     \
        free(list);                                                                \
    }                                                                              \
                                                                                   \
    T CHAINARR_CONCATENATE(get_, NAME)(NAME* list, size_t index) {                   \
        if (index >= list->size) {                                                 \
            perror("Index out of bounds");                                         \
            exit(EXIT_FAILURE);                                                    \
        }                                                                          \
        CHAINARR_CONCATENATE(NAME, _node)* current = list->head;                     \
        for (size_t i = 0; i < index; i++) {                                       \
            current = current->next;                                               \
        }                                                                          \
        return current->value;                                                     \
    }                                                                              \
                                                                                   \
    size_t CHAINARR_CONCATENATE(size_, NAME)(NAME* list) {                           \
        return list->size;                                                         \
    }  

#define CHAINARR_DEFINE(T) CHAINARR_DEFINE_NAME(T, CHAINARR_CONCATENATE(chainarr_, T))

#endif //DWA_CHAINARR_H
