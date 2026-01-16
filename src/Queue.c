//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include "Queue.h"
#include "Memory/Memory.h"

/**
 * Constructor for a FIFO or LIFO queue. Allocates an empty queue.
 * @return Empty queue.
 */
Queue_ptr create_queue() {
    Queue_ptr result = malloc_(sizeof(Queue));
    result->list = create_linked_list(NULL);
    return result;
}

/**
 * Constructor of a queue from an array list of items.
 * @param items Items to be inserted when the queue is created.
 * @return Allocated and filled queue.
 */
Queue_ptr create_queue2(Array_list_ptr items) {
    Queue_ptr result = create_queue();
    for (int i = 0; i < items->size; i++){
        enqueue(result, array_list_get(items, i));
    }
    return result;
}

/**
 * Destructor method for the queue. Deallocates memory allocated for the queue and the contents of the
 * elements if needed.
 * @param queue Queue
 * @param free_method Destructor method for the contents of the elements of the queue
 */
void free_queue(Queue_ptr queue, void free_method(void *)) {
    free_linked_list(queue->list, free_method);
    free_(queue);
}

/**
 * Checks if the queue is empty or not.
 * @param queue Queue
 * @return Returns true if the queue is empty, false otherwise.
 */
bool is_queue_empty(const Queue* queue) {
    return is_linked_list_empty(queue->list);
}

/**
 * Adds an element to the end of the queue.
 * @param queue Queue
 * @param item Element added to the queue.
 */
void enqueue(Queue_ptr queue, void *item) {
    add_last(queue->list, create_node(item));
}

/**
 * Adds an element to the front of the queue.
 * @param queue Queue
 * @param item Element added to the queue.
 */
void enqueue_front(Queue_ptr queue, void *item){
    add_first(queue->list, create_node(item));
}

/**
 * Removes an element from the start of the queue.
 * @param queue Queue
 * @return Removed item
 */
void *dequeue(Queue_ptr queue) {
    return remove_first(queue->list);
}

/**
 * Removes an element from the end of the queue.
 * @param queue Queue
 * @return Removed item.
 */
void *dequeue_back(Queue_ptr queue) {
    return remove_last(queue->list);
}
