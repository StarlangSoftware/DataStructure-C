//
// Created by Olcay Taner YILDIZ on 26.01.2023.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/CounterHashMap.h"

void testPut1() {
    char *items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                                  (int (*)(const void *, const void *)) compare_string);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[2]);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[0]);
    if (count_counter_hash_map(counterHashMap, items[0]) != 3) {
        printf("Test Failed in testPut1\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testPut2() {
    int *value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_int,
                                                                  (int (*)(const void *, const void *)) compare_int);
    for (int i = 0; i < 1000; i++) {
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map(counterHashMap, value);
    }
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        value = malloc(sizeof(int));
        *value = i;
        count += count_counter_hash_map(counterHashMap, value);
    }
    if (count != 1000) {
        printf("Test Failed in testPut2\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testSumOfCounts() {
    int *value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_int,
                                                                  (int (*)(const void *, const void *)) compare_int);
    for (int i = 0; i < 1000; i++) {
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map(counterHashMap, value);
    }
    if (sum_of_counts_counter_hash_map(counterHashMap) != 1000) {
        printf("Test Failed in testSumOfCounts\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testPutNTimes1() {
    char *items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                                  (int (*)(const void *, const void *)) compare_string);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    put_counter_hash_map_n_times(counterHashMap, items[1], 3);
    put_counter_hash_map_n_times(counterHashMap, items[2], 6);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    put_counter_hash_map_n_times(counterHashMap, items[1], 3);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    if (count_counter_hash_map(counterHashMap, items[0]) != 6) {
        printf("Test Failed in testPutNTimes\n");
    }
    if (count_counter_hash_map(counterHashMap, items[1]) != 6) {
        printf("Test Failed in testPutNTimes\n");
    }
    if (count_counter_hash_map(counterHashMap, items[2]) != 6) {
        printf("Test Failed in testPutNTimes\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testPutNTimes2() {
    int *value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_int,
                                                                  (int (*)(const void *, const void *)) compare_int);
    for (int i = 0; i < 1000; i++) {
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map_n_times(counterHashMap, value, i + 1);
    }
    if (sum_of_counts_counter_hash_map(counterHashMap) != 500500) {
        printf("Test Failed in testPutNTimes2\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testMax() {
    char *items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                                  (int (*)(const void *, const void *)) compare_string);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[2]);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[0]);
    if (strcmp(max_counter_hash_map(counterHashMap), items[0]) != 0) {
        printf("Test Failed in testMax\n");
    }
    free_counter_hash_map(counterHashMap);
}

void testTopN() {
    char *items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                                  (int (*)(const void *, const void *)) compare_string);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[2]);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[0]);
    Array_list_ptr top_n = top_N_counter_hash_map(counterHashMap, 1);
    Hash_node_ptr hashNode = array_list_get(top_n, 0);
    if (strcmp(hashNode->key, items[0]) != 0) {
        printf("Test Failed in testTopN 1\n");
    }
    free_array_list(top_n, NULL);
    top_n = top_N_counter_hash_map(counterHashMap, 2);
    hashNode = array_list_get(top_n, 1);
    if (strcmp(hashNode->key, items[1]) != 0) {
        printf("Test Failed in testTopN 2\n");
    }
    free_array_list(top_n, NULL);
    top_n = top_N_counter_hash_map(counterHashMap, 3);
    hashNode = array_list_get(top_n, 2);
    if (strcmp(hashNode->key, items[2]) != 0) {
        printf("Test Failed in testTopN 3\n");
    }
    free_array_list(top_n, NULL);
    free_counter_hash_map(counterHashMap);
}

int main() {
    testPut1();
    testPut2();
    testSumOfCounts();
    testPutNTimes1();
    testPutNTimes2();
    testMax();
    testTopN();
}