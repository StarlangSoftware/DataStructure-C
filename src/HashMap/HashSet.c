//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdlib.h>
#include "HashSet.h"
#include "../Memory/Memory.h"

Hash_set_ptr create_hash_set(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *)) {
    Hash_set_ptr result = malloc_(sizeof(Hash_set), "create_hash_set");
    result->hash_map = create_hash_map(hash_function, compare);
    return result;
}

void free_hash_set(Hash_set_ptr hash_set, void (*free_method)(void *)) {
    int N = primes[hash_set->hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            if (free_method != NULL) {
                free_method(removed->data);
            }
            free_(removed);
        }
        free_(linked_list);
    }
    free_(hash_set->hash_map->table);
    free_(hash_set->hash_map);
    free_(hash_set);
}

void hash_set_insert(Hash_set_ptr hash_set, void *key) {
    unsigned int address;
    address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    if (!hash_set_contains(hash_set, key)) {
        add_last(hash_set->hash_map->table[address], create_node(key));
        hash_set->hash_map->count++;
        if (hash_set->hash_map->count > 0.8 * primes[hash_set->hash_map->prime_index]) {
            rehash_hash_set(hash_set->hash_map);
        }
    }
}

bool hash_set_contains(const Hash_set* hash_set, const void *key) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    return linked_list_contains(hash_set->hash_map->table[address], key);
}

void hash_set_remove(Hash_set_ptr hash_set, const void *key, void (*free_method)(void *)) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    Node_ptr node = linked_list_get(hash_set->hash_map->table[address], key);
    if (node != NULL) {
        remove_node(hash_set->hash_map->table[address], node, free_method);
        hash_set->hash_map->count--;
    }
}

void rehash_hash_set(Hash_map_ptr hash_map) {
    Linked_list_ptr *new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            unsigned int address = hash_map->hash_function(iterator->data, primes[hash_map->prime_index + 1]);
            add_last(new_table[address], iterator);
            iterator = next;
        }
    }
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        free_(hash_map->table[i]);
    }
    free_(hash_map->table);
    hash_map->prime_index++;
    hash_map->table = new_table;
}

Array_list_ptr hash_set_key_list(const Hash_set* hash_set) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_set->hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            array_list_add(result, iterator->data);
            iterator = iterator->next;
        }
    }
    return result;
}

Hash_set_ptr create_hash_set_of_string(char **array, int size) {
    Hash_set_ptr result = create_hash_set((unsigned int (*)(const void *, int)) hash_function_string,
                                          (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < size; i++) {
        hash_set_insert(result, array[i]);
    }
    return result;
}

bool hash_set_is_empty(const Hash_set* hash_set) {
    return hash_map_is_empty(hash_set->hash_map);
}

void hash_set_merge(Hash_set_ptr hash_set1, const Hash_set* hash_set2, void* (*clone_method)(void* item)) {
    Array_list_ptr key_list = hash_set_key_list(hash_set2);
    for (int i = 0; i < key_list->size; i++){
        if (clone_method != NULL){
            if (!hash_set_contains(hash_set1, array_list_get(key_list, i))){
                hash_set_insert(hash_set1, clone_method(array_list_get(key_list, i)));
            }
        } else {
            hash_set_insert(hash_set1, array_list_get(key_list, i));
        }
    }
    free_array_list(key_list, NULL);
}

Hash_set_ptr create_hash_set_of_string2(Array_list_ptr list) {
    Hash_set_ptr result = create_hash_set((unsigned int (*)(const void *, int)) hash_function_string,
                                          (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < list->size; i++) {
        hash_set_insert(result, array_list_get(list, i));
    }
    return result;
}
