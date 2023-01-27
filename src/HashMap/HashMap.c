//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include "HashMap.h"
#include "HashNode.h"

int hash_function_string(char* string, int N){
    int total;
    for (int i = 0; i < strlen(string); i++){
        total = total * 256 + string[i];
    }
    return total % N;
}

int hash_function_int(const int* number, int N){
    return *number % N;
}

int compare_string(char* first, char* second){
    return strcmp(first, second);
}

int compare_int(const int* first, const int* second){
    return *first - *second;
}

int compare_int_r(const int* first, const int* second){
    return *second - *first;
}

int compare_string_r(char* first, char* second){
    return strcmp(second, first);
}

Linked_list_ptr* allocate_hash_table(int prime_index, int (*key_compare)(void*, void*)) {
    Linked_list_ptr* table;
    int N = primes[prime_index];
    table = malloc(N * sizeof(Linked_list_ptr));
    for (int i = 0; i < N; i++){
        table[i] = create_linked_list(key_compare);
    }
    return table;
}

Hash_map_ptr create_hash_map(int (*hash_function)(void *, int), int (*key_compare)(void*, void*)) {
    Hash_map_ptr result = malloc(sizeof(Hash_map));
    result->prime_index = 0;
    result->table = allocate_hash_table(result->prime_index, key_compare);
    result->hash_function = hash_function;
    result->key_compare = key_compare;
    result->count = 0;
    return result;
}

void free_hash_map(Hash_map_ptr hash_map, void (*free_method)(void *)) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++){
        free_linked_list(hash_map->table[i], free_method);
    }
    free(hash_map->table);
    free(hash_map);
}

void rehash_hash_map(Hash_map_ptr hash_map) {
    Linked_list_ptr* new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++){
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL){
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            int address = hash_map->hash_function(hash_node->key, primes[hash_map->prime_index + 1]);
            add_last(new_table[address], iterator);
            iterator = next;
        }
    }
    for (int i = 0; i < primes[hash_map->prime_index]; i++){
        free(hash_map->table[i]);
    }
    free(hash_map->table);
    hash_map->prime_index++;
    hash_map->table = new_table;
}

void hash_map_insert(Hash_map_ptr hash_map, void *key, void* value) {
    int address;
    address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    if (hash_map_contains(hash_map, key)){
        Node_ptr node = hash_list_get(hash_map->table[address], key);
        remove_node(hash_map->table[address], node, NULL);
        hash_map->count--;
    }
    Hash_node_ptr hash_node = create_hash_node(key, value);
    add_last(hash_map->table[address], create_node(hash_node));
    hash_map->count++;
    if (hash_map->count > 0.8 * primes[hash_map->prime_index]){
        rehash_hash_map(hash_map);
    }
}

int hash_map_contains(Hash_map_ptr hash_map, void *key) {
    int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    return hash_list_contains(hash_map->table[address], key);
}

void *hash_map_get(Hash_map_ptr hash_map, void *key) {
    int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL){
        Hash_node_ptr hash_node = node->data;
        return hash_node->value;
    } else {
        return NULL;
    }
}

void hash_map_remove(Hash_map_ptr hash_map, void *key, void free_method(void *)) {
    Node_ptr node = hash_map_get(hash_map, key);
    if (node != NULL){
        int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
        remove_node(hash_map->table[address], node, free_method);
        hash_map->count--;
    }
}

Node_ptr hash_list_get(Linked_list_ptr linked_list, void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL){
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

int hash_list_contains(Linked_list_ptr linked_list, void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL){
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0){
            return 1;
        }
        iterator = iterator->next;
    }
    return 0;
}
