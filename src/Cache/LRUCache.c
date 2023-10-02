//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdlib.h>
#include "LRUCache.h"

/**
 * A constructor of LRUCache class which takes cacheSize as input. It creates new
 * CacheLinkedList and map.
 *
 * @allocated map
 * @param cache_size Integer input defining cache size.
 */
Lru_cache_ptr
create_lru_cache(int cache_size, unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *)) {
    Lru_cache_ptr result = malloc(sizeof(Lru_cache));
    result->cache_size = cache_size;
    result->map = create_linked_hash_map(hash_function, compare);
    return result;
}

/**
 * Destructor of LRUCache class
 *
 * @freed Itself
 * @param lru_cache
 * @param free_method_map_node Free method for hash map node
 */
void free_lru_cache(Lru_cache_ptr lru_cache, void (*free_method_map_node)(void *)) {
    free_linked_hash_map(lru_cache->map, free_method_map_node);
    free(lru_cache);
}

/**
 * The contains method takes a T type input key and returns true if the map has the given key,
 * false otherwise.
 *
 * @param key T type input key.
 * @return 1 if the map has the given key, 0 otherwise.
 */
bool lru_cache_contains(const Lru_cache *lru_cache, const void *key) {
    return linked_hash_map_contains(lru_cache->map, key);
}

/**
 * The get method takes T type input key and returns the least recently used value. First it checks
 * whether the map has the given key, if so it gets the corresponding cacheNode. It removes
 * that cacheNode from LinkedList and adds it again to the beginning of the list since it is
 * more likely to be used again. At the end, returns the data value of that cacheNode.
 *
 * @param key T type input key.
 * @return data value if the {@link map} has the given key, nullptr otherwise.
 */
void *lru_cache_get(const Lru_cache* lru_cache, void *key) {
    if (lru_cache_contains(lru_cache, key)) {
        void *value = linked_hash_map_get(lru_cache->map, key);
        linked_hash_map_remove(lru_cache->map, key, NULL);
        linked_hash_map_insert(lru_cache->map, key, value);
        return value;
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
    if (lru_cache->map->hash_map->count == lru_cache->cache_size) {
        Hash_node_ptr hash_node = lru_cache->map->linked_list->head->data;
        linked_hash_map_remove(lru_cache->map, hash_node->key, NULL);
    }
    linked_hash_map_insert(lru_cache->map, key, data);
}
