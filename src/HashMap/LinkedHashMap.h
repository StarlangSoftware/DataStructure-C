//
// Created by Olcay Taner YILDIZ on 9.02.2023.
//

#ifndef DATASTRUCTURE_LINKEDHASHMAP_H
#define DATASTRUCTURE_LINKEDHASHMAP_H

#include "HashMap.h"

struct linked_hash_map {
    Hash_map_ptr hash_map;
    Linked_list_ptr linked_list;
};

typedef struct linked_hash_map Linked_hash_map;
typedef Linked_hash_map *Linked_hash_map_ptr;

Linked_hash_map_ptr create_linked_hash_map(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *));

void free_linked_hash_map(Linked_hash_map_ptr linked_hash_map, void free_method(void *));

void free_linked_hash_map2(Linked_hash_map_ptr linked_hash_map, void key_free_method(void *), void free_method(void *));

void linked_hash_map_insert(Linked_hash_map_ptr linked_hash_map, void *key, void *value);

bool linked_hash_map_contains(const Linked_hash_map * linked_hash_map, const void *key);

void linked_hash_map_remove(Linked_hash_map_ptr linked_hash_map, void *key, void free_method(void *));

void linked_hash_map_remove_key(Linked_hash_map_ptr linked_hash_map, const void *key);

void linked_hash_map_update_value(Linked_hash_map_ptr linked_hash_map, const void *key, void *value);

void *linked_hash_map_get(const Linked_hash_map* linked_hash_map, const void *key);

Array_list_ptr linked_hash_map_key_value_list(const Linked_hash_map* linked_hash_map);

Array_list_ptr linked_hash_map_key_list(const Linked_hash_map* linked_hash_map);

#endif //DATASTRUCTURE_LINKEDHASHMAP_H
