//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/Cache/LRUCache.h"
#include "../src/Memory/Memory.h"

void lru_cache_test1() {
    char* datum;
    char *keys[3] = {"item1", "item2", "item3"};
    char *data[3] = {"1", "2", "3"};
    Lru_cache_ptr cache = create_lru_cache(50,
                                           (unsigned int (*)(const void *, int)) hash_function_string,
                                           (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < 3; i++) {
        char* dst = malloc_(strlen(keys[i]) + 1);
        strcpy(dst, keys[i]);
        lru_cache_add(cache, dst, data[i]);
    }
    if (!lru_cache_contains(cache, "item1")) {
        printf("Test Failed in lru_cache_test1\n");
    } else {
        datum = lru_cache_get(cache, "item1");
        if (strcmp(datum, "1") != 0){
            printf("Test Failed in lru_cache_test1\n");
        }
    }
    if (!lru_cache_contains(cache, "item2")) {
        printf("Test Failed in lru_cache_test1\n");
    } else {
        datum = lru_cache_get(cache, "item2");
        if (strcmp(datum, "2") != 0){
            printf("Test Failed in lru_cache_test1\n");
        }
    }
    if (lru_cache_contains(cache, "item4")) {
        printf("Test Failed in lru_cache_test1\n");
    }
    free_lru_cache(cache, free_, NULL);
}

void lru_cache_test2() {
    char *datum;
    char *keys[3] = {"item1", "item2", "item3"};
    char *data[3] = {"1", "2", "3"};
    Lru_cache_ptr cache = create_lru_cache(2,
                                           (unsigned int (*)(const void *, int)) hash_function_string,
                                           (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < 3; i++) {
        char* dst = malloc_(strlen(keys[i]) + 1);
        strcpy(dst, keys[i]);
        lru_cache_add(cache, dst, data[i]);
    }
    if (lru_cache_contains(cache, "item1")) {
        printf("Test Failed in lru_cache_test2\n");
    }
    if (!lru_cache_contains(cache, "item2")) {
        printf("Test Failed in lru_cache_test2\n");
    } else {
        datum = lru_cache_get(cache, "item2");
        if (strcmp(datum, "2") != 0){
            printf("Test Failed in lru_cache_test2\n");
        }
    }
    if (!lru_cache_contains(cache, "item3")) {
        printf("Test Failed in lru_cache_test2\n");
    } else {
        datum = lru_cache_get(cache, "item3");
        if (strcmp(datum, "3") != 0){
            printf("Test Failed in lru_cache_test2\n");
        }
    }
    free_lru_cache(cache, free_, NULL);
}

void lru_cache_test3() {
    int keys[10000];
    int data;
    Lru_cache_ptr cache = create_lru_cache(10000,
                                           (unsigned int (*)(const void *, int)) hash_function_int,
                                           (int (*)(const void *, const void *)) compare_int);
    for (int i = 0; i < 10000; i++) {
        keys[i] = i;
        lru_cache_add(cache, &keys[i], &keys[i]);
    }
    for (int i = 0; i < 1000; i++) {
        data = random() % 10000;
        if (!lru_cache_contains(cache, &data)) {
            printf("Test Failed in lru_cache_test2\n");
        }
    }
    free_lru_cache(cache, NULL, NULL);
}

int main() {
    start_memory_check();
    lru_cache_test1();
    lru_cache_test2();
    lru_cache_test3();
    end_memory_check();
}