//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#include "Heap.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the heap. According to the comparator, the heap could be min or max heap.
 * @param N Maximum number of elements in the heap.
 * @param comparator Comparator function to compare two elements.
 * @return Empty heap.
 */
Heap_ptr create_heap(int N, int (*comparator)(void *, void *)) {
    Heap_ptr heap = malloc_(sizeof(Heap));
    heap->array = malloc_(N * sizeof(void *));
    heap->count = 0;
    heap->N = N;
    heap->compare = comparator;
    return heap;
}

/**
 * Destructor method for the heap. Deallocates memory allocated for the heap and its elements.
 * @param heap The heap.
 * @param free_method Destructor method for the value in the hash node in the linked lists.
 */
void free_heap(Heap_ptr heap, void (*free_method)(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < heap->count; i++) {
            free_method(heap->array[i]);
        }
    }
    free_(heap->array);
    free_(heap);
}

/**
 * Checks if the heap is empty or not.
 * @param heap Heap
 * @return Returns true if the heap is empty, false otherwise.
 */
bool is_heap_empty(const Heap* heap) {
    return heap->count == 0;
}

/**
 * Swaps two heap nodes in the heap given their indexes.
 * @param heap Heap
 * @param index1 Index of the first node to swap.
 * @param index2 Index of the second node to swap.
 */
void swap_heap_node(Heap_ptr heap, int index1, int index2) {
    void *tmp = heap->array[index1];
    heap->array[index1] = heap->array[index2];
    heap->array[index2] = tmp;
}

/**
 * The function percolates down from a node of the tree to restore the max-heap property. Left or right children are
 * checked, if one of them is larger than the current element of the heap, the iteration continues. The iteration is,
 * determining the largest one of the node's children and switching that node's value with the current node's value.
 * We need to check if current node's left and right children exist or not. These checks are done with for the left
 * child and with for the right child.
 * @param heap Heap
 * @param no Index of the starting node to restore the max-heap property.
 */
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

/**
 * The function percolates up from a node of the tree to restore the max-heap property. As long as the max-heap
 * property is corrupted, the parent and its child switch their values. We need to pay attention that, the
 * calculated index of the parent must be a valid number. In other words, while going upper levels,we need to see
 * that we can not go up if we are at the root of the tree.
 * @param heap Heap
 * @param no Index of the starting node to restore the max-heap property.
 */
void percolate_up(Heap_ptr heap, int no) {
    int parent = (no - 1) / 2;
    while (parent >= 0 && heap->compare(heap->array[parent], heap->array[no]) < 0) {
        swap_heap_node(heap, parent, no);
        no = parent;
        parent = (no - 1) / 2;
    }
}

/**
 * The function will return the first element, therefore the first element is stored in the variable, and the first
 * element of the heap is set to the last element of the heap. After that, in order to restore the max-heap
 * property, we percolate down the tree using the function. As a last step, the number of element in the heap is
 * decremented by one.
 * @param heap Heap
 * @return The first element
 */
void *delete_top(Heap_ptr heap) {
    void *tmp;
    tmp = heap->array[0];
    heap->array[0] = heap->array[heap->count - 1];
    percolate_down(heap, 0);
    heap->count--;
    return tmp;
}

/**
 * The insertion of a new element to the heap, proceeds from the leaf nodes to the root node. First the new element
 * is added to the end of the heap, then as long as the max-heap property is corrupted, the new element switches
 * place with its parent.
 * @param heap Heap
 * @param data New element to be inserted.
 */
void heap_insert(Heap_ptr heap, void *data) {
    if (heap->count < heap->N) {
        heap->count++;
    }
    heap->array[heap->count - 1] = data;
    percolate_up(heap, heap->count - 1);
}
