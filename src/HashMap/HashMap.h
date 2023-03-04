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
                       10000019, 23000009, 52000007};

struct hash_map {
    Linked_list_ptr *table;
    int prime_index;
    int count;

    unsigned int (*hash_function)(void *, int);

    int (*key_compare)(void *, void *);
};

typedef struct hash_map Hash_map;
typedef Hash_map *Hash_map_ptr;

unsigned int hash_function_string(char *string, int N);

unsigned int hash_function_int(const int *number, int N);

int compare_string(char *first, char *second);

int compare_int(const int *first, const int *second);

int compare_int_r(const int *first, const int *second);

int compare_string_r(char *first, char *second);

void free_int(int *value);

void free_string(char *value);

Linked_list_ptr *allocate_hash_table(int prime_index, int (*key_compare)(void *, void *));

Hash_map_ptr create_hash_map(unsigned int (*hash_function)(void *, int), int (*key_compare)(void *, void *));

void free_hash_map(Hash_map_ptr hash_map, void free_method(void *));

Hash_node_ptr hash_map_insert(Hash_map_ptr hash_map, void *key, void *value);

bool hash_map_contains(Hash_map_ptr hash_map, void *key);

void *hash_map_get(Hash_map_ptr hash_map, void *key);

void hash_map_remove(Hash_map_ptr hash_map, void *key, void free_method(void *));

void rehash_hash_map(Hash_map_ptr hash_map);

Node_ptr hash_list_get(Linked_list_ptr linked_list, void *key);

bool hash_list_contains(Linked_list_ptr linked_list, void *key);

Array_list_ptr key_value_list(Hash_map_ptr hash_map);

Array_list_ptr key_list(Hash_map_ptr hash_map);


#endif //DATASTRUCTURE_HASHMAP_H
