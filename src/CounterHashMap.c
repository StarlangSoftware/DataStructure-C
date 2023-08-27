//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#include <stdlib.h>
#include "CounterHashMap.h"
#include "HashMap/HashNode.h"

Counter_hash_map_ptr
create_counter_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *)) {
    Counter_hash_map_ptr result = malloc(sizeof(Counter_hash_map));
    result->map = create_hash_map(hash_function, key_compare);
    return result;
}

void free_counter_hash_map(Counter_hash_map_ptr counter_hash_map) {
    free_hash_map(counter_hash_map->map, free);
    free(counter_hash_map);
}

/**
 * The put method takes a T type input. If this map contains a mapping for the key, it puts this key after
 * incrementing its value by one. If his map does not contain a mapping, then it directly puts key with the value of 1.
 *
 * @param counter_hash_map Map to process.
 * @param key to put.
 */
void put_counter_hash_map(Counter_hash_map_ptr counter_hash_map, void *key) {
    if (hash_map_contains(counter_hash_map->map, key)) {
        int *previous_value = hash_map_get(counter_hash_map->map, key);
        (*previous_value)++;
        hash_map_insert(counter_hash_map->map, key, previous_value);
    } else {
        int *value = malloc(sizeof(int));
        *value = 1;
        hash_map_insert(counter_hash_map->map, key, value);
    }
}

/**
 * The putNTimes method takes a T and an integer N as inputs. If this map contains a mapping for the key, it puts this key after
 * incrementing its value by N. If his map does not contain a mapping, then it directly puts key with the value of N.
 *
 * @param counter_hash_map Map to process.
 * @param key to put.
 * @param N   to increment value.
 */
void put_counter_hash_map_n_times(Counter_hash_map_ptr counter_hash_map, void *key, int N) {
    if (hash_map_contains(counter_hash_map->map, key)) {
        int *previous_value = hash_map_get(counter_hash_map->map, key);
        (*previous_value) += N;
        hash_map_insert(counter_hash_map->map, key, previous_value);
    } else {
        int *value = malloc(sizeof(int));
        *value = N;
        hash_map_insert(counter_hash_map->map, key, value);
    }
}

/**
 * The count method takes a T as input, if this map contains a mapping for the key, it returns the value corresponding
 * this key, 0 otherwise.
 *
 * @param counter_hash_map Map to process.
 * @param key to get value.
 * @return the value corresponding given key, 0 if it is not mapped.
 */
int count_counter_hash_map(const Counter_hash_map* counter_hash_map, const void *key) {
    if (hash_map_contains(counter_hash_map->map, key)) {
        return *((int *) hash_map_get(counter_hash_map->map, key));
    } else {
        return 0;
    }
}

/**
 * The sumOfCounts method loops through the values contained in this map and accumulates the counts of this values.
 *
 * @param counter_hash_map Map to process.
 * @return accumulated counts.
 */
int sum_of_counts_counter_hash_map(const Counter_hash_map* counter_hash_map) {
    int sum = 0;
    for (int i = 0; i < primes[counter_hash_map->map->prime_index]; i++) {
        Linked_list_ptr linked_list = counter_hash_map->map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            sum += *((int *) hash_node->value);
            iterator = next;
        }
    }
    return sum;
}

/**
 * The max method loops through the mappings contained in this map and if the current entry's count value is greater
 * than maxCount, which is initialized as 0, it updates the maxCount as current count and maxKey as the current count's
 * key.
 *
 * @param counter_hash_map Map to process.
 * @return T type maxKey which is the maximum valued key.
 */
void *max_counter_hash_map(const Counter_hash_map* counter_hash_map) {
    int max_count = 0;
    void *max_key = NULL;
    for (int i = 0; i < primes[counter_hash_map->map->prime_index]; i++) {
        Linked_list_ptr linked_list = counter_hash_map->map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            int count = *((int *) hash_node->value);
            if (count > max_count) {
                max_count = count;
                max_key = hash_node->key;
            }
            iterator = next;
        }
    }
    return max_key;
}

/**
 * The max method takes a threshold as input and loops through the mappings contained in this map. It accumulates the
 * count values and if the current entry's count value is greater than maxCount, which is initialized as 0,
 * it updates the maxCount as current count and maxKey as the current count's key.
 * <p>
 * At the end of the loop, if the ratio of maxCount/total is greater than the given threshold it returns maxKey, else null.
 *
 * @param counter_hash_map Map to process.
 * @param threshold double value.
 * @return T type maxKey if greater than the given threshold, null otherwise.
 */
void *max_than_threshold_counter_hash_map(const Counter_hash_map* counter_hash_map, double threshold) {
    int max_count = 0, total = 0;
    void *max_key = NULL;
    for (int i = 0; i < primes[counter_hash_map->map->prime_index]; i++) {
        Linked_list_ptr linked_list = counter_hash_map->map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            int count = *((int *) hash_node->value);
            total += count;
            if (count > max_count) {
                max_count = count;
                max_key = hash_node->key;
            }
            iterator = next;
        }
    }
    if (max_count / (total + 0.0) > threshold) {
        return max_key;
    } else {
        return NULL;
    }
}

/**
 * The add method adds value of each key of toBeAdded to the current counterHashMap.
 *
 * @param counter_hash_map Map to process.
 * @param toBeAdded CounterHashMap to be added to this counterHashMap.
 */
void add_counter_hash_map(Counter_hash_map_ptr dst, const Counter_hash_map* src) {
    for (int i = 0; i < primes[src->map->prime_index]; i++) {
        Linked_list_ptr linked_list = src->map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            int count = *((int *) hash_node->value);
            put_counter_hash_map_n_times(dst, hash_node->key, count);
            iterator = next;
        }
    }
}

/**
 * The topN method takes an integer N as inout. It creates an {@link vector} result and loops through the the
 * mappings contained in this map and adds each entry to the result {@link vector}. Then sort this {@link vector}
 * according to their values and returns an {@link vector} which is a sublist of result with N elements.
 *
 * @param counter_hash_map Map to process.
 * @param N Integer value for defining size of the sublist.
 * @return a sublist of N element.
 */
Array_list_ptr top_N_counter_hash_map(const Counter_hash_map* counter_hash_map, int N) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[counter_hash_map->map->prime_index]; i++) {
        Linked_list_ptr linked_list = counter_hash_map->map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node);
            iterator = next;
        }
    }
    array_list_sort(result, (int (*)(const void *, const void *)) compare_values_of_counter_hash_map);
    return sub_list(result, 0, N);
}

int compare_values_of_counter_hash_map(const Hash_node* item1, const Hash_node* item2) {
    int value1 = *((int *) item1->value);
    int value2 = *((int *) item2->value);
    if (value1 > value2) {
        return -1;
    } else {
        if (value1 < value2) {
            return 1;
        } else {
            return 0;
        }
    }
}
