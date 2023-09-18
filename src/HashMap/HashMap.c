//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include "HashMap.h"
#include "HashNode.h"
#include "../CounterHashMap.h"

unsigned int hash_function_string(const char *string, int N) {
    unsigned int total;
    for (int i = 0; i < strlen(string); i++) {
        total = total * 256 + string[i];
    }
    return total % N;
}

unsigned int hash_function_int(const int *number, int N) {
    return *number % N;
}

int compare_string(const char *first, const char *second) {
    return strcmp(first, second);
}

int compare_int(const int *first, const int *second) {
    return *first - *second;
}

int compare_int_r(const int *first, const int *second) {
    return *second - *first;
}

int compare_string_r(char *first, char *second) {
    return strcmp(second, first);
}

void free_int(int *value) {
    free(value);
}

void free_string(char *value) {
    free(value);
}

Linked_list_ptr *allocate_hash_table(int prime_index, int (*key_compare)(const void *, const void *)) {
    Linked_list_ptr *table;
    int N = primes[prime_index];
    table = malloc(N * sizeof(Linked_list_ptr));
    for (int i = 0; i < N; i++) {
        table[i] = create_linked_list(key_compare);
    }
    return table;
}

Hash_map_ptr create_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *)) {
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
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            if (free_method != NULL) {
                free_method(hash_node->value);
            }
            free(hash_node);
            free(removed);
        }
        free(linked_list);
    }
    free(hash_map->table);
    free(hash_map);
}

void free_hash_map_of_counter_hash_map(Hash_map_ptr hash_map) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            free_counter_hash_map(hash_node->value);
            free(hash_node);
            free(removed);
        }
        free(linked_list);
    }
    free(hash_map->table);
    free(hash_map);
}

void rehash_hash_map(Hash_map_ptr hash_map) {
    Linked_list_ptr *new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            unsigned int address = hash_map->hash_function(hash_node->key, primes[hash_map->prime_index + 1]);
            add_last(new_table[address], iterator);
            iterator = next;
        }
    }
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        free(hash_map->table[i]);
    }
    free(hash_map->table);
    hash_map->prime_index++;
    hash_map->table = new_table;
}

Hash_node_ptr hash_map_insert(Hash_map_ptr hash_map, void *key, void *value) {
    unsigned int address;
    address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    if (hash_map_contains(hash_map, key)) {
        Node_ptr node = hash_list_get(hash_map->table[address], key);
        remove_node(hash_map->table[address], node, NULL);
        hash_map->count--;
    }
    Hash_node_ptr hash_node = create_hash_node(key, value);
    add_last(hash_map->table[address], create_node(hash_node));
    hash_map->count++;
    if (hash_map->count > 0.8 * primes[hash_map->prime_index]) {
        rehash_hash_map(hash_map);
    }
    return hash_node;
}

bool hash_map_contains(const Hash_map* hash_map, const void *key) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    return hash_list_contains(hash_map->table[address], key);
}

void *hash_map_get(const Hash_map* hash_map, const void *key) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL) {
        Hash_node_ptr hash_node = node->data;
        return hash_node->value;
    } else {
        return NULL;
    }
}

void hash_map_remove(Hash_map_ptr hash_map, const void *key, void free_method(void *)) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL) {
        remove_node(hash_map->table[address], node, free_method);
        hash_map->count--;
    }
}

Node_ptr hash_list_get(const Linked_list* linked_list, const void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

bool hash_list_contains(const Linked_list* linked_list, const void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

Array_list_ptr key_value_list(const Hash_map* hash_map) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node);
            iterator = iterator->next;
        }
    }
    return result;
}

Array_list_ptr key_list(const Hash_map* hash_map) {
    Array_list_ptr result = create_array_list();
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

Array_list_ptr value_list(const Hash_map *hash_map) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node->value);
            iterator = iterator->next;
        }
    }
    return result;
}

bool hash_map_is_empty(const Hash_map* hash_map) {
    return hash_map->count == 0;
}

Hash_map_ptr create_string_hash_map() {
    return create_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                           (int (*)(const void *, const void *)) compare_string);
}

void free_hash_map2(Hash_map_ptr hash_map, void (*key_free_method)(void *), void (*value_free_method)(void *)) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            if (key_free_method != NULL) {
                key_free_method(hash_node->key);
            }
            if (value_free_method != NULL) {
                value_free_method(hash_node->value);
            }
            free(hash_node);
            free(removed);
        }
        free(linked_list);
    }
    free(hash_map->table);
    free(hash_map);
}

Hash_map_ptr create_integer_hash_map() {
    return create_hash_map((unsigned int (*)(const void *, int)) hash_function_int,
                           (int (*)(const void *, const void *)) compare_int);
}

void hash_map_merge(Hash_map_ptr hash_map1, Hash_map_ptr hash_map2) {
    for (int i = 0; i < primes[hash_map2->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map2->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            hash_map_insert(hash_map1, hash_node->key, hash_node->value);
            iterator = iterator->next;
        }
    }
}
