//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#ifndef DATASTRUCTURE_HASHMAP_H
#define DATASTRUCTURE_HASHMAP_H

#include <stdbool.h>
#include "../LinkedList/LinkedList.h"
#include "../ArrayList.h"
#include "HashNode.h"

static int primes[] = {11, 23, 53,
                       101, 233, 521,
                       1009, 2309, 5209,
                       10007, 23003, 52009,
                       100003, 230003, 520019,
                       1000003, 2300003, 5200007,
                       10000019, 23000009, 52000007,
                       100000007, 230000003, 520000009};

struct hash_map {
    Linked_list_ptr *table;
    int prime_index;
    int count;

    unsigned int (*hash_function)(const void *, int);

    int (*key_compare)(const void *, const void *);
};

typedef struct hash_map Hash_map;
typedef Hash_map *Hash_map_ptr;

unsigned int hash_function_string(const char *string, int N);

unsigned int hash_function_int(const int *number, int N);

int compare_string(const char *first, const char *second);

int compare_int(const int *first, const int *second);

int compare_int_r(const int *first, const int *second);

int compare_double(const double *first, const double *second);

int compare_double_r(const double *first, const double *second);

int compare_string_r(const char *first, const char *second);

void free_int(int *value);

void free_string(char *value);

Linked_list_ptr *allocate_hash_table(int prime_index, int (*key_compare)(const void *, const void *));

Hash_map_ptr create_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *));

Hash_map_ptr create_string_hash_map();

Hash_map_ptr create_integer_hash_map();

void free_hash_map(Hash_map_ptr hash_map, void free_value_method(void *));

void free_hash_map2(Hash_map_ptr hash_map, void key_free_method(void *), void value_free_method(void *));

void free_hash_map_of_counter_hash_map(Hash_map_ptr hash_map);

void free_hash_map_of_array_list(Hash_map_ptr hash_map, void (*key_free_method)(void *));

Hash_node_ptr hash_map_insert(Hash_map_ptr hash_map, void *key, void *value);

bool hash_map_contains(const Hash_map* hash_map, const void *key);

void *hash_map_get(const Hash_map* hash_map, const void *key);

void *hash_map_get_key(const Hash_map* hash_map, const void *key);

void hash_map_remove(Hash_map_ptr hash_map, const void *key, void free_method(void *));

void rehash_hash_map(Hash_map_ptr hash_map);

Node_ptr hash_list_get(const Linked_list* linked_list, const void *key);

bool hash_list_contains(const Linked_list* linked_list, const void *key);

Array_list_ptr key_value_list(const Hash_map* hash_map);

Array_list_ptr key_list(const Hash_map* hash_map);

Array_list_ptr value_list(const Hash_map* hash_map);

bool hash_map_is_empty(const Hash_map* hash_map);

void hash_map_merge(Hash_map_ptr hash_map1,
                    Hash_map_ptr hash_map2,
                    void* (*clone_key_method)(void* key),
                    void* (*clone_value_method)(void* value));

void add_to_hash_map_of_array_list(Hash_map_ptr hash_map, void* key, void* value);

#endif //DATASTRUCTURE_HASHMAP_H
