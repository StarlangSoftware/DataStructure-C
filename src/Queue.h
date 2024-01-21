//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include "LinkedList/LinkedList.h"
#include "ArrayList.h"

struct queue {
    Linked_list_ptr list;
};

typedef struct queue Queue;
typedef Queue *Queue_ptr;

Queue_ptr create_queue();

Queue_ptr create_queue2(Array_list_ptr items);

void free_queue(Queue_ptr queue, void free_method(void *));

bool is_queue_empty(const Queue* queue);

void enqueue(Queue_ptr queue, void *item);

void enqueue_front(Queue_ptr queue, void *item);

void *dequeue(Queue_ptr queue);

void* dequeue_back(Queue_ptr queue);

#endif //DATASTRUCTURE_QUEUE_H
