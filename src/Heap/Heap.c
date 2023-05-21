//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#include <stdlib.h>
#include "Heap.h"

Heap_ptr create_heap(int N, int (*comparator)(void *, void *)) {
    Heap_ptr heap = malloc(sizeof(Heap));
    heap->array = malloc(N * sizeof(void *));
    heap->count = 0;
    heap->N = N;
    heap->compare = comparator;
    return heap;
}

void free_heap(Heap_ptr heap, void (*free_method)(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < heap->count; i++) {
            free_method(heap->array[i]);
        }
    }
    free(heap->array);
    free(heap);
}

bool is_heap_empty(const Heap* heap) {
    return heap->count == 0;
}

void swap_heap_node(Heap_ptr heap, int index1, int index2) {
    void *tmp = heap->array[index1];
    heap->array[index1] = heap->array[index2];
    heap->array[index2] = tmp;
}

void percolate_down(Heap_ptr heap, int no) {
    int left = 2 * no + 1;
    int right = 2 * no + 2;
    while ((left < heap->count && heap->compare(heap->array[no], heap->array[left]) < 0) ||
           (right < heap->count && heap->compare(heap->array[no], heap->array[right]) < 0)) {
        if (right >= heap->count || heap->compare(heap->array[left], heap->array[right]) > 0) {
            swap_heap_node(heap, no, left);
            no = left;
        } else {
            swap_heap_node(heap, no, right);
            no = right;
        }
        left = 2 * no + 1;
        right = 2 * no + 2;
    }
}

void percolate_up(Heap_ptr heap, int no) {
    int parent = (no - 1) / 2;
    while (parent >= 0 && heap->compare(heap->array[parent], heap->array[no]) < 0) {
        swap_heap_node(heap, parent, no);
        no = parent;
        parent = (no - 1) / 2;
    }
}

void *delete_top(Heap_ptr heap) {
    void *tmp;
    tmp = heap->array[0];
    heap->array[0] = heap->array[heap->count - 1];
    percolate_down(heap, 0);
    heap->count--;
    return tmp;
}

void heap_insert(Heap_ptr heap, void *data) {
    if (heap->count < heap->N) {
        heap->count++;
    }
    heap->array[heap->count - 1] = data;
    percolate_up(heap, heap->count - 1);
}
