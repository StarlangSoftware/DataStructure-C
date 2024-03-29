//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include <stdlib.h>
#include "LinkedList.h"
#include "../Memory/Memory.h"

Linked_list_ptr create_linked_list(int (*compare)(const void *, const void *)) {
    Linked_list_ptr result = malloc_(sizeof(Linked_list), "create_linked_list");
    result->head = NULL;
    result->tail = NULL;
    result->compare = compare;
    return result;
}

void remove_node(Linked_list_ptr linked_list, Node_ptr node, void free_method(void *)) {
    Node_ptr next = node->next;
    Node_ptr previous = node->previous;
    if (previous != NULL) {
        previous->next = next;
    } else {
        linked_list->head = linked_list->head->next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        linked_list->tail = linked_list->tail->previous;
    }
    free_node(node, free_method);
}

void add_first(Linked_list_ptr linked_list, Node_ptr node) {
    node->previous = NULL;
    node->next = linked_list->head;
    if (linked_list->head != NULL) {
        linked_list->head->previous = node;
    } else {
        linked_list->tail = node;
    }
    linked_list->head = node;
}

Node_ptr remove_first(Linked_list_ptr linked_list) {
    if (is_linked_list_empty(linked_list)) {
        return NULL;
    }
    Node_ptr removed = linked_list->head;
    linked_list->head = linked_list->head->next;
    if (linked_list->head == NULL) {
        linked_list->tail = NULL;
    } else {
        linked_list->head->previous = NULL;
    }
    return removed;
}

Node_ptr remove_last(Linked_list_ptr linked_list) {
    if (is_linked_list_empty(linked_list)) {
        return NULL;
    }
    Node_ptr removed = linked_list->tail;
    linked_list->tail = linked_list->tail->previous;
    if (linked_list->tail == NULL) {
        linked_list->head = NULL;
    } else {
        linked_list->tail->next = NULL;
    }
    return removed;
}

void free_linked_list(Linked_list_ptr linked_list, void free_method(void *)) {
    while (linked_list->head != NULL) {
        Node_ptr removed = linked_list->head;
        linked_list->head = linked_list->head->next;
        free_node(removed, free_method);
    }
    free_(linked_list);
}

bool is_linked_list_empty(const Linked_list* linked_list) {
    return linked_list->head == NULL;
}

void add_last(Linked_list_ptr linked_list, Node_ptr node) {
    node->previous = linked_list->tail;
    node->next = NULL;
    if (linked_list->tail != NULL) {
        linked_list->tail->next = node;
    } else {
        linked_list->head = node;
    }
    linked_list->tail = node;
}

bool linked_list_contains(const Linked_list* linked_list, const void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        if (linked_list->compare(iterator->data, item) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

Node_ptr linked_list_get(const Linked_list* linked_list, const void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        if (linked_list->compare(iterator->data, item) == 0) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void remove_data(Linked_list_ptr linked_list, const void *data) {
    Node_ptr node = linked_list_get(linked_list, data);
    if (node != NULL) {
        remove_node(linked_list, node, NULL);
    }
}
