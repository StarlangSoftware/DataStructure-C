//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#ifndef DATASTRUCTURE_COUNTERHASHMAP_H
#define DATASTRUCTURE_COUNTERHASHMAP_H

#include "HashMap/HashMap.h"
#include "ArrayList.h"
#include "HashMap/HashNode.h"

struct counter_hash_map {
    Hash_map_ptr map;
};

typedef struct counter_hash_map Counter_hash_map;
typedef Counter_hash_map *Counter_hash_map_ptr;

Counter_hash_map_ptr
create_counter_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *));

void free_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void free_method(void *));

void put_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void *key);

void put_counter_hash_map_n_times(Counter_hash_map_ptr counter_hash_map, void *key, int N);

int count_counter_hash_map(const Counter_hash_map* counter_hash_map, const void *key);

int sum_of_counts_counter_hash_map(const Counter_hash_map* counter_hash_map);

void *max_counter_hash_map(const Counter_hash_map* counter_hash_map);

void *max_than_threshold_counter_hash_map(const Counter_hash_map* counter_hash_map, double threshold);

void add_counter_hash_map(Counter_hash_map_ptr dst, const Counter_hash_map* src);

Array_list_ptr top_N_counter_hash_map(const Counter_hash_map* counter_hash_map, int N);

int compare_values_of_counter_hash_map(const Hash_node* item1, const Hash_node* item2);

#endif //DATASTRUCTURE_COUNTERHASHMAP_H
