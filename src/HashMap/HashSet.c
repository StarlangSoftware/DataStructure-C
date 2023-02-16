//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdlib.h>
#include "HashSet.h"

Hash_set_ptr create_hash_set(unsigned int (*hash_function)(void *, int), int (*compare)(void *, void *)) {
    Hash_set_ptr result = malloc(sizeof(Hash_set));
    result->hash_map = create_hash_map(hash_function, compare);
    return result;
}

void free_hash_set(Hash_set_ptr hash_set, void (*free_method)(void *)) {
    int N = primes[hash_set->hash_map->prime_index];
    for (int i = 0; i < N; i++){
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        while (linked_list->head != NULL){
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            if (free_method != NULL){
                free_method(removed->data);
            }
            free(removed);
        }
        free(linked_list);
    }
    free(hash_set->hash_map->table);
    free(hash_set);
}

void hash_set_insert(Hash_set_ptr hash_set, void *key) {
    unsigned int address;
    address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    if (!hash_set_contains(hash_set, key)){
        add_last(hash_set->hash_map->table[address], create_node(key));
        hash_set->hash_map->count++;
        if (hash_set->hash_map->count > 0.8 * primes[hash_set->hash_map->prime_index]){
            rehash_hash_set(hash_set->hash_map);
        }
    }
}

int hash_set_contains(Hash_set_ptr hash_set, void *key) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    return linked_list_contains(hash_set->hash_map->table[address], key);
}

void hash_set_remove(Hash_set_ptr hash_set, void *key, void (*free_method)(void *)) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    Node_ptr node = linked_list_get(hash_set->hash_map->table[address], key);
    if (node != NULL){
        remove_node(hash_set->hash_map->table[address], node, free_method);
        hash_set->hash_map->count--;
    }
}

void rehash_hash_set(Hash_map_ptr hash_map) {
    Linked_list_ptr* new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++){
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL){
            Node_ptr next = iterator->next;
            unsigned int address = hash_map->hash_function(iterator->data, primes[hash_map->prime_index + 1]);
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

Array_list_ptr hash_set_key_list(Hash_set_ptr hash_set) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_set->hash_map->prime_index]; i++){
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL){
            array_list_add(result, iterator->data);
            iterator = iterator->next;
        }
    }
    return result;
}
