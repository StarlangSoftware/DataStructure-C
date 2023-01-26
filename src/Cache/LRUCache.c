//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdlib.h>
#include "LRUCache.h"
#include "CacheData.h"

/**
 * A constructor of {@link LRUCache} class which takes cacheSize as input. It creates new
 * {@link CacheLinkedList} and {@link map}.
 *
 * @param cache_size Integer input defining cache size.
 */
Lru_cache_ptr create_lru_cache(int cache_size, int (*hash_function)(void*, int), int (*compare)(void*, void*)) {
    Lru_cache_ptr result = malloc(sizeof(Lru_cache));
    result->cache_size = cache_size;
    result->map = create_hash_map(hash_function, compare);
    result->cache = create_linked_list(compare);
    return result;
}

void free_lru_cache(Lru_cache_ptr lru_cache, void (*free_method_map_node)(void *), void (*free_method_node)(void *)) {
    free_hash_map(lru_cache->map, free_method_map_node);
    free_linked_list(lru_cache->cache, free_method_node);
    free(lru_cache);
}

/**
 * The contains method takes a T type input key and returns true if the {@link map} has the given key,
 * false otherwise.
 *
 * @param key T type input key.
 * @return 1 if the {@link map} has the given key, 0 otherwise.
 */
int lru_cache_contains(Lru_cache_ptr lru_cache, void *key) {
    return hash_map_contains(lru_cache->map, key);
}

/**
 * The get method takes T type input key and returns the least recently used value. First it checks
 * whether the {@link map} has the given key, if so it gets the corresponding cacheNode. It removes
 * that cacheNode from {@link LinkedList} and adds it again to the beginning of the list since it is
 * more likely to be used again. At the end, returns the data value of that cacheNode.
 *
 * @param key T type input key.
 * @return data value if the {@link map} has the given key, nullptr otherwise.
 */
void *lru_cache_get(Lru_cache_ptr lru_cache, void *key) {
    if (lru_cache_contains(lru_cache, key)){
        Cache_data_ptr cache_node = hash_map_get(lru_cache->map, key);
        remove_data(lru_cache->cache, cache_node);
        add_first(lru_cache->cache, create_node(cache_node));
        return cache_node->data;
    } else {
        return NULL;
    }
}

/**
 * The add method take a key and a data as inputs. First it checks the size of the {@link map}, if it is
 * full (i.e equal to the given cacheSize) then it removes the last cacheNode in the @link LinkedList}. If
 * it has space for new entries, it creates new cacheNode with given inputs and adds this cacheNode to the
 * {@link LinkedList} and also puts it to the {@link map}.
 *
 * @param key  T type input.
 * @param data T type input.
 */
void lru_cache_add(Lru_cache_ptr lru_cache, void *key, void *data) {
    Cache_data_ptr cache_data;
    if (lru_cache->map->count == lru_cache->cache_size){
        Node_ptr removed = remove_last(lru_cache->cache);
        cache_data = removed->data;
        hash_map_remove(lru_cache->map, cache_data->key, NULL);
    }
    cache_data = create_cache_data(data, key);
    add_first(lru_cache->cache, create_node(cache_data));
    hash_map_insert(lru_cache->map, key, cache_data);
}
