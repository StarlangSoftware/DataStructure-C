//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include "Node.h"
#include "../Memory/Memory.h"

Node_ptr create_node(void *data) {
    Node_ptr result = malloc_(sizeof(Node));
    result->data = data;
    result->previous = NULL;
    result->next = NULL;
    return result;
}

void free_node(Node_ptr node, void free_method(void *data)) {
    if (free_method != NULL) {
        free_method(node->data);
    }
    free_(node);
}

void *get_data(Node_ptr node) {
    return node->data;
}

Node_ptr get_next(Node_ptr node) {
    return node->next;
}

Node_ptr get_previous(Node_ptr node) {
    return node->previous;
}

void set_previous(Node_ptr node, Node_ptr previous) {
    node->previous = previous;
}

void set_next(Node_ptr node, Node_ptr next) {
    node->next = next;
}
