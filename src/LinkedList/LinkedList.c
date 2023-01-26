//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include <stdlib.h>
#include "LinkedList.h"

Linked_list_ptr create_linked_list(int (*compare)(void*, void*)){
    Linked_list_ptr result = malloc(sizeof(Linked_list));
    result->head = NULL;
    result->tail = NULL;
    result->compare = compare;
    return result;
}

void remove_node(Linked_list_ptr linked_list, Node_ptr node, void free_method(void *)){
    Node_ptr next = node->next;
    Node_ptr previous = node->previous;
    if (previous != NULL){
        previous->next = next;
    } else {
        linked_list->head = linked_list->head->next;
    }
    if (next != NULL){
        next->previous = previous;
    } else {
        linked_list->tail = linked_list->tail->previous;
    }
    free_node(node, free_method);
}

void add_first(Linked_list_ptr linked_list, Node_ptr node){
    node->previous = NULL;
    node->next = linked_list->head;
    if (linked_list->head != NULL){
        linked_list->head->previous = node;
    } else {
        linked_list->tail = node;
    }
    linked_list->head = node;
}

Node_ptr remove_first(Linked_list_ptr linked_list){
    if (is_linked_list_empty(linked_list)){
        return NULL;
    }
    Node_ptr removed = linked_list->head;
    linked_list->head = linked_list->head->next;
    if (linked_list->head == NULL){
        linked_list->tail = NULL;
    }
    return removed;
}

Node_ptr remove_last(Linked_list_ptr linked_list){
    if (is_linked_list_empty(linked_list)){
        return NULL;
    }
    Node_ptr removed = linked_list->tail;
    linked_list->tail = linked_list->tail->previous;
    if (linked_list->tail == NULL){
        linked_list->head = NULL;
    }
    return removed;
}

void free_linked_list(Linked_list_ptr linked_list, void free_method(void *)){
    while (linked_list->head != NULL){
        Node_ptr removed = linked_list->head;
        linked_list->head = linked_list->head->next;
        free_node(removed, free_method);
    }
    free(linked_list);
}

int is_linked_list_empty(Linked_list_ptr linked_list){
    return linked_list->head == NULL;
}

void add_last(Linked_list_ptr linked_list, Node_ptr node) {
    node->previous = linked_list->tail;
    node->next = NULL;
    if (linked_list->tail != NULL){
        linked_list->tail->next = node;
    } else {
        linked_list->head = node;
    }
    linked_list->tail = node;
}

int linked_list_contains(Linked_list_ptr linked_list, void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL){
        if (linked_list->compare(iterator->data, item) == 0){
            return 1;
        }
        iterator = iterator->next;
    }
    return 0;
}

Node_ptr linked_list_get(Linked_list_ptr linked_list, void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL){
        if (linked_list->compare(iterator->data, item) == 0){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void remove_data(Linked_list_ptr linked_list, void *data) {
    Node_ptr node = linked_list_get(linked_list, data);
    if (node != NULL){
        remove_node(linked_list, node, NULL);
    }
}
