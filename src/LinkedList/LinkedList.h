//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H

#include <stdbool.h>
#include "Node.h"

struct linked_list {
    Node_ptr head;
    Node_ptr tail;

    int (*compare)(const void *, const void *);
};

typedef struct linked_list Linked_list;
typedef Linked_list *Linked_list_ptr;

Linked_list_ptr create_linked_list(int (*compare)(const void *, const void *));

void free_linked_list(Linked_list_ptr linked_list, void free_method(void *));

void remove_node(Linked_list_ptr linked_list, Node_ptr node, void free_method(void *));

void remove_data(Linked_list_ptr linked_list, const void *data);

void add_first(Linked_list_ptr linked_list, Node_ptr node);

void add_last(Linked_list_ptr linked_list, Node_ptr node);

void* remove_first(Linked_list_ptr linked_list);

Node_ptr remove_first_node(Linked_list_ptr linked_list);

void* remove_last(Linked_list_ptr linked_list);

Node_ptr remove_last_node(Linked_list_ptr linked_list);

bool is_linked_list_empty(const Linked_list* linked_list);

bool linked_list_contains(const Linked_list* linked_list, const void *item);

Node_ptr linked_list_get(const Linked_list* linked_list, const void *item);

void merge_linked_list(Linked_list_ptr first_list, Linked_list_ptr second_list);

#endif //DATASTRUCTURE_LINKEDLIST_H
