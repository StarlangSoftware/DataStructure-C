//
// Created by Olcay Taner YILDIZ on 26.11.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "Memory.h"

unsigned int hash_function_address(const void *address, int N){
    return ((long)address) % N;
}

int compare_address(const void *first, const void *second){
    return ((long)first - (long)second);
}

Linked_list_ptr create_linked_list_(int (*compare)(const void *, const void *)) {
    Linked_list_ptr result = malloc(sizeof(Linked_list));
    result->head = NULL;
    result->tail = NULL;
    result->compare = compare;
    return result;
}

Linked_list_ptr *allocate_hash_table_(int prime_index, int (*key_compare)(const void *, const void *)) {
    Linked_list_ptr *table;
    int N = primes[prime_index];
    table = malloc(N * sizeof(Linked_list_ptr));
    for (int i = 0; i < N; i++) {
        table[i] = create_linked_list_(key_compare);
    }
    return table;
}

Hash_map_ptr create_hash_map2(unsigned int (*hash_function)(const void *, int),
                              int (*key_compare)(const void *, const void *),
                              int prime_index) {
    Hash_map_ptr result = malloc(sizeof(Hash_map));
    result->prime_index = prime_index;
    result->table = allocate_hash_table_(result->prime_index, key_compare);
    result->hash_function = hash_function;
    result->key_compare = key_compare;
    result->count = 0;
    return result;
}

void start_memory_check() {
    memory_map = create_hash_map2(hash_function_address, compare_address, 10);
}

void start_medium_memory_check() {
    memory_map = create_hash_map2(hash_function_address, compare_address, 15);
}

void start_large_memory_check() {
    memory_map = create_hash_map2(hash_function_address, compare_address, 20);
}

void start_x_large_memory_check() {
    memory_map = create_hash_map2(hash_function_address, compare_address, 23);
}

void remove_node_(Linked_list_ptr linked_list, Node_ptr node) {
    Node_ptr next = node->next;
    Node_ptr previous = node->previous;
    if (previous != NULL) {
        previous->next = next;
    } else {
        linked_list->head = linked_list->head->next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        linked_list->tail = linked_list->tail->previous;
    }
    free(node);
}

Hash_node_ptr create_hash_node_(void *key, void *value) {
    Hash_node_ptr result = malloc(sizeof(Hash_node));
    result->key = key;
    result->value = value;
    return result;
}

Node_ptr create_node_(void *data) {
    Node_ptr result = malloc(sizeof(Node));
    result->data = data;
    result->previous = NULL;
    result->next = NULL;
    return result;
}

Hash_node_ptr hash_map_insert_(Hash_map_ptr hash_map, void *key, void *value) {
    unsigned int address;
    address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    if (hash_map_contains(hash_map, key)) {
        Node_ptr node = hash_list_get(hash_map->table[address], key);
        remove_node_(hash_map->table[address], node);
        hash_map->count--;
    }
    if (hash_map->count > 0.95 * primes[hash_map->prime_index]) {
        printf("Warning hash map almost full 95 percent\n");
    }
    Hash_node_ptr hash_node = create_hash_node_(key, value);
    add_last(hash_map->table[address], create_node_(hash_node));
    hash_map->count++;
    return hash_node;
}

void* malloc_(size_t size, char* function_name){
    void* allocated = malloc(size);
    if (memory_map != NULL){
        hash_map_insert_(memory_map, allocated, function_name);
    }
    return allocated;
}

void free_(void* allocated){
    if (memory_map != NULL){
        hash_map_remove(memory_map, allocated, NULL);
    }
    free(allocated);
}

Array_list_ptr create_array_list_() {
    Array_list_ptr array_list = malloc(sizeof(Array_list));
    array_list->maxSize = 10;
    array_list->array = malloc(array_list->maxSize * sizeof(void *));
    array_list->size = 0;
    return array_list;
}

Array_list_ptr key_list_(const Hash_map* hash_map) {
    Array_list_ptr result = create_array_list_();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node->key);
            iterator = iterator->next;
        }
    }
    return result;
}

void end_memory_check() {
    if (memory_map->count > 0){
        Array_list_ptr list = key_list_(memory_map);
        for (int i = 0; i < list->size; i++){
            printf("Method: %s\n", (char*) hash_map_get(memory_map, array_list_get(list, i)));
        }
        free_array_list(list, NULL);
    }
}

void *realloc_(void *ptr, size_t size, char* function_name) {
    void* allocated = realloc(ptr, size);
    if (memory_map != NULL){
        hash_map_remove(memory_map, ptr, NULL);
        hash_map_insert_(memory_map, allocated, function_name);
    }
    return allocated;
}

void *calloc_(size_t count, size_t size, char *function_name) {
    void* allocated = calloc(count, size);
    if (memory_map != NULL){
        hash_map_insert_(memory_map, allocated, function_name);
    }
    return allocated;
}
