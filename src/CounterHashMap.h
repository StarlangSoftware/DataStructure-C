//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#ifndef DATASTRUCTURE_COUNTERHASHMAP_H
#define DATASTRUCTURE_COUNTERHASHMAP_H

#include "HashMap/HashMap.h"
#include "ArrayList.h"
#include "HashMap/HashNode.h"

struct counter_hash_map{
    Hash_map_ptr map;
};

typedef struct counter_hash_map Counter_hash_map;
typedef Counter_hash_map* Counter_hash_map_ptr;

Counter_hash_map_ptr create_counter_hash_map(int (*hash_function)(void*, int), int (*key_compare)(void*, void*));
void free_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void free_method(void *));
void put_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void* key);
void put_counter_hash_map_n_times(Counter_hash_map_ptr counter_hash_map, void* key, int N);
int count_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void* key);
int sum_of_counts_counter_hash_map(Counter_hash_map_ptr counter_hash_map);
void* max_counter_hash_map(Counter_hash_map_ptr counter_hash_map);
void* max_than_threshold_counter_hash_map(Counter_hash_map_ptr counter_hash_map, double threshold);
void add_counter_hash_map(Counter_hash_map_ptr dst, Counter_hash_map_ptr src);
Array_list_ptr top_N_counter_hash_map(Counter_hash_map_ptr counter_hash_map, int N);
int compare_values_of_counter_hash_map(Hash_node_ptr item1, Hash_node_ptr item2);

#endif //DATASTRUCTURE_COUNTERHASHMAP_H
