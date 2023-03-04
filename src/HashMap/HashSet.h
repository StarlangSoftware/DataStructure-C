//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#ifndef DATASTRUCTURE_HASHSET_H
#define DATASTRUCTURE_HASHSET_H

#include "HashMap.h"

struct hash_set {
    Hash_map_ptr hash_map;
};

typedef struct hash_set Hash_set;
typedef Hash_set *Hash_set_ptr;

Hash_set_ptr create_hash_set(unsigned int (*hash_function)(void *, int), int (*compare)(void *, void *));

Hash_set_ptr create_hash_set_of_string(char *array[], int size);

void free_hash_set(Hash_set_ptr hash_set, void free_method(void *));

void hash_set_insert(Hash_set_ptr hash_set, void *key);

bool hash_set_contains(Hash_set_ptr hash_set, void *key);

void hash_set_remove(Hash_set_ptr hash_set, void *key, void free_method(void *));

void rehash_hash_set(Hash_map_ptr hash_map);

Array_list_ptr hash_set_key_list(Hash_set_ptr hash_set);

bool hash_set_is_empty(Hash_set_ptr hash_set);

#endif //DATASTRUCTURE_HASHSET_H
