//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#ifndef DATASTRUCTURE_HEAP_H
#define DATASTRUCTURE_HEAP_H

struct heap {
    void **array;
    int count;
    int N;

    int (*compare)(void *, void *);
};

typedef struct heap Heap;
typedef Heap *Heap_ptr;

Heap_ptr create_heap(int N, int (*comparator)(void *, void *));

void free_heap(Heap_ptr heap, void free_method(void *));

int is_heap_empty(Heap_ptr heap);

void swap_heap_node(Heap_ptr heap, int index1, int index2);

void percolate_down(Heap_ptr heap, int no);

void percolate_up(Heap_ptr heap, int no);

void *delete_top(Heap_ptr heap);

void heap_insert(Heap_ptr heap, void *data);

#endif //DATASTRUCTURE_HEAP_H
