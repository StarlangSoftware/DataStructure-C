//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include <stdlib.h>
#include "Queue.h"

Queue_ptr create_queue() {
    Queue_ptr result = malloc(sizeof(Queue));
    result->list = create_linked_list(NULL);
    return result;
}

void free_queue(Queue_ptr queue, void free_method(void *)) {
    free_linked_list(queue->list, free_method);
    free(queue->list);
    free(queue);
}

bool is_queue_empty(const Queue* queue) {
    return is_linked_list_empty(queue->list);
}

void enqueue(Queue_ptr queue, void *item) {
    add_last(queue->list, create_node(item));
}

void *dequeue(Queue_ptr queue) {
    if (is_linked_list_empty(queue->list)) {
        return NULL;
    }
    Node_ptr node = remove_first(queue->list);
    void *item = node->data;
    free(node);
    return item;
}
