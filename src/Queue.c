//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include <stdlib.h>
#include "Queue.h"
#include "Memory/Memory.h"

Queue_ptr create_queue() {
    Queue_ptr result = malloc_(sizeof(Queue), "create_queue");
    result->list = create_linked_list(NULL);
    return result;
}

void free_queue(Queue_ptr queue, void free_method(void *)) {
    free_linked_list(queue->list, free_method);
    free_(queue);
}

bool is_queue_empty(const Queue* queue) {
    return is_linked_list_empty(queue->list);
}

void enqueue(Queue_ptr queue, void *item) {
    add_last(queue->list, create_node(item));
}

void enqueue_front(Queue_ptr queue, void *item){
    add_first(queue->list, create_node(item));
}

void *dequeue(Queue_ptr queue) {
    if (is_linked_list_empty(queue->list)) {
        return NULL;
    }
    Node_ptr node = remove_first(queue->list);
    void *item = node->data;
    free_(node);
    return item;
}

Queue_ptr create_queue2(Array_list_ptr items) {
    Queue_ptr result = create_queue();
    for (int i = 0; i < items->size; i++){
        enqueue(result, array_list_get(items, i));
    }
    return result;
}

void *dequeue_back(Queue_ptr queue) {
    if (is_linked_list_empty(queue->list)) {
        return NULL;
    }
    Node_ptr node = remove_last(queue->list);
    void *item = node->data;
    free_(node);
    return item;
}
