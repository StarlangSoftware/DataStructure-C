//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#ifndef DATASTRUCTURE_LRUCACHE_H
#define DATASTRUCTURE_LRUCACHE_H

#include <stdbool.h>
#include "../HashMap/HashMap.h"
#include "../HashMap/LinkedHashMap.h"

struct lru_cache {
    int cache_size;
    Linked_hash_map_ptr map;
};

typedef struct lru_cache Lru_cache;
typedef Lru_cache *Lru_cache_ptr;

Lru_cache_ptr
create_lru_cache(int cache_size, unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *));

void free_lru_cache(Lru_cache_ptr lru_cache, void free_method_map_node(void *));

bool lru_cache_contains(const Lru_cache* lru_cache, const void *key);

void *lru_cache_get(const Lru_cache* lru_cache, void *key);

void lru_cache_add(Lru_cache_ptr lru_cache, void *key, void *data);

#endif //DATASTRUCTURE_LRUCACHE_H
