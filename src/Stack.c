//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include <stdlib.h>
#include "Stack.h"

Stack_ptr create_stack() {
    Stack_ptr result = malloc(sizeof(Stack));
    result->list = create_linked_list(NULL);
    return result;
}

void free_stack(Stack_ptr stack, void free_method(void *)) {
    free_linked_list(stack->list, free_method);
    free(stack);
}

void push(Stack_ptr stack, void *item) {
    add_last(stack->list, create_node(item));
}

void *pop(Stack_ptr stack) {
    if (is_linked_list_empty(stack->list)) {
        return NULL;
    }
    Node_ptr node = remove_last(stack->list);
    void *item = node->data;
    free(node);
    return item;
}

bool is_stack_empty(const Stack* stack) {
    return is_linked_list_empty(stack->list);
}

void *peek(Stack_ptr stack) {
    if (is_linked_list_empty(stack->list)) {
        return NULL;
    }
    return stack->list->tail->data;
}
