//
// Created by Olcay Taner YILDIZ on 12.10.2022.
//

#include <stdio.h>
#include <string.h>
#include "../src/Heap/Heap.h"
#include "../src/HashMap/HashMap.h"
#include "../src/Memory/Memory.h"

void test_max_heap_int() {
    int data[] = {4, 6, 2, 5, 3, 1, 7};
    Heap_ptr maxHeap = create_heap(8, (int (*)(void *, void *)) compare_int);
    for (int i = 0; i < 7; i++) {
        heap_insert(maxHeap, &data[i]);
    }
    int *maxItem = delete_top(maxHeap);
    if (*maxItem != 7) {
        printf("Test Failed in test_max_heap_int\n");
    }
    maxItem = delete_top(maxHeap);
    if (*maxItem != 6) {
        printf("Test Failed in test_max_heap_int\n");
    }
    maxItem = delete_top(maxHeap);
    if (*maxItem != 5) {
        printf("Test Failed in test_max_heap_int\n");
    }
    free_heap(maxHeap, NULL);
}

void test_min_heap_int() {
    int data[] = {4, 6, 2, 5, 3, 1, 7};
    Heap_ptr minHeap = create_heap(8, (int (*)(void *, void *)) compare_int_r);
    for (int i = 0; i < 7; i++) {
        heap_insert(minHeap, &data[i]);
    }
    int *maxItem = delete_top(minHeap);
    if (*maxItem != 1) {
        printf("Test Failed in test_min_heap_int\n");
    }
    maxItem = delete_top(minHeap);
    if (*maxItem != 2) {
        printf("Test Failed in test_min_heap_int\n");
    }
    maxItem = delete_top(minHeap);
    if (*maxItem != 3) {
        printf("Test Failed in test_min_heap_int\n");
    }
    free_heap(minHeap, NULL);
}

void test_max_heap_string() {
    char *data[] = {"d", "f", "b", "e", "c", "a", "g"};
    Heap_ptr maxHeap = create_heap(8, (int (*)(void *, void *)) compare_string);
    for (int i = 0; i < 7; i++) {
        heap_insert(maxHeap, data[i]);
    }
    char *maxItem = delete_top(maxHeap);
    if (strcmp(maxItem, "g") != 0) {
        printf("Test Failed in test_max_heap_string\n");
    }
    maxItem = delete_top(maxHeap);
    if (strcmp(maxItem, "f") != 0) {
        printf("Test Failed in test_max_heap_string\n");
    }
    maxItem = delete_top(maxHeap);
    if (strcmp(maxItem, "e") != 0) {
        printf("Test Failed in test_max_heap_string\n");
    }
    free_heap(maxHeap, NULL);
}

void test_min_heap_string() {
    char *data[] = {"d", "f", "b", "e", "c", "a", "g"};
    Heap_ptr minHeap = create_heap(8, (int (*)(void *, void *)) compare_string_r);
    for (int i = 0; i < 7; i++) {
        heap_insert(minHeap, data[i]);
    }
    char *maxItem = delete_top(minHeap);
    if (strcmp(maxItem, "a") != 0) {
        printf("Test Failed in test_min_heap_string\n");
    }
    maxItem = delete_top(minHeap);
    if (strcmp(maxItem, "b") != 0) {
        printf("Test Failed in test_min_heap_string\n");
    }
    maxItem = delete_top(minHeap);
    if (strcmp(maxItem, "c") != 0) {
        printf("Test Failed in test_min_heap_string\n");
    }
    free_heap(minHeap, NULL);
}

int main() {
    start_memory_check();
    test_max_heap_int();
    test_min_heap_int();
    test_max_heap_string();
    test_min_heap_string();
    end_memory_check();
}
