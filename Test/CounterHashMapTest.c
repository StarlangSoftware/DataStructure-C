//
// Created by Olcay Taner YILDIZ on 26.01.2023.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/CounterHashMap.h"

int hash_function_string(char* string, int N){
    int total;
    for (int i = 0; i < strlen(string); i++){
        total = total * 256 + string[i];
    }
    return total % N;
}

int compareStringMax(char* first, char* second){
    return strcmp(first, second);
}

int hash_function_int(const int* number, int N){
    return *number % N;
}

int compareIntMax(const int* first, const int* second){
    return *first - *second;
}

void testPut1(){
    char* items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_string,
                                                                  (int (*)(void *, void *)) compareStringMax);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[2]);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[0]);
    if (count_counter_hash_map(counterHashMap, items[0]) != 3){
        printf("Test Failed in testPut1\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

void testPut2() {
    int* value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_int,
                                                                  (int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 1000; i++){
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map(counterHashMap, value);
    }
    int count = 0;
    for (int i = 0; i < 1000; i++){
        value = malloc(sizeof(int));
        *value = i;
        count += count_counter_hash_map(counterHashMap, value);
    }
    if (count != 1000){
        printf("Test Failed in testPut2\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

void testSumOfCounts() {
    int* value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_int,
                                                                  (int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 1000; i++){
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map(counterHashMap, value);
    }
    if (sum_of_counts_counter_hash_map(counterHashMap) != 1000){
        printf("Test Failed in testSumOfCounts\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

void testPutNTimes1(){
    char* items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_string,
                                                                  (int (*)(void *, void *)) compareStringMax);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    put_counter_hash_map_n_times(counterHashMap, items[1], 3);
    put_counter_hash_map_n_times(counterHashMap, items[2], 6);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    put_counter_hash_map_n_times(counterHashMap, items[1], 3);
    put_counter_hash_map_n_times(counterHashMap, items[0], 2);
    if (count_counter_hash_map(counterHashMap, items[0]) != 6){
        printf("Test Failed in testPutNTimes\n");
    }
    if (count_counter_hash_map(counterHashMap, items[1]) != 6){
        printf("Test Failed in testPutNTimes\n");
    }
    if (count_counter_hash_map(counterHashMap, items[2]) != 6){
        printf("Test Failed in testPutNTimes\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

void testPutNTimes2() {
    int* value;
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_int,
                                                                  (int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 1000; i++){
        value = malloc(sizeof(int));
        *value = random() % 1000;
        put_counter_hash_map_n_times(counterHashMap, value, i + 1);
    }
    if (sum_of_counts_counter_hash_map(counterHashMap) != 500500){
        printf("Test Failed in testPutNTimes2\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

void testMax(){
    char* items[3] = {"item1", "item2", "item3"};
    Counter_hash_map_ptr counterHashMap = create_counter_hash_map((int (*)(void *, int)) hash_function_string,
                                                                  (int (*)(void *, void *)) compareStringMax);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[2]);
    put_counter_hash_map(counterHashMap, items[0]);
    put_counter_hash_map(counterHashMap, items[1]);
    put_counter_hash_map(counterHashMap, items[0]);
    if (strcmp(max_counter_hash_map(counterHashMap), items[0]) != 0){
        printf("Test Failed in testMax\n");
    }
    free_counter_hash_map(counterHashMap, NULL);
}

int main(){
    testPut1();
    testPut2();
    testSumOfCounts();
    testPutNTimes1();
    testPutNTimes2();
    testMax();
}