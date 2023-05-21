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

Hash_set_ptr create_hash_set(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *));

Hash_set_ptr create_hash_set_of_string(char *array[], int size);

void free_hash_set(Hash_set_ptr hash_set, void free_method(void *));

void hash_set_insert(Hash_set_ptr hash_set, void *key);

bool hash_set_contains(const Hash_set* hash_set, const void *key);

void hash_set_remove(Hash_set_ptr hash_set, const void *key, void free_method(void *));

void rehash_hash_set(Hash_map_ptr hash_map);

Array_list_ptr hash_set_key_list(const Hash_set* hash_set);

bool hash_set_is_empty(const Hash_set* hash_set);

void hash_set_merge(Hash_set_ptr hash_set1, const Hash_set* hash_set2);

#endif //DATASTRUCTURE_HASHSET_H
