//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#include <string.h>
#include "HashMap.h"
#include "HashNode.h"
#include "../CounterHashMap.h"
#include "../Memory/Memory.h"

/**
 * Hash function for a string. Calculates the value of the string as if it is a number in base 256. Then takes modulus
 * N.
 * @param string String for which hash function is calculated.
 * @param N Modulus N
 * @return Hash function result for a given string.
 */
unsigned int hash_function_string(const char *string, int N) {
    unsigned int total;
    for (int i = 0; i < strlen(string); i++) {
        total = total * 256 + string[i];
    }
    return total % N;
}

/**
 * Hash function for an integer. Takes modulus N.
 * @param number Number for which hash function is calculated.
 * @param N Modulus N.
 * @return Hash function result for a given number.
 */
unsigned int hash_function_int(const int *number, int N) {
    return *number % N;
}

/**
 * Comparator function to compare two string lexicographically. Uses strcmp for the comparison.
 * @param first First string to compare.
 * @param second Second string to compare.
 * @return An integer greater than, equal to, or less than 0, according as the string first is greater than, equal to, or
 * less than the string second.
 */
int compare_string(const char *first, const char *second) {
    return strcmp(first, second);
}

/**
 * Comparator function to compare two integers.
 * @param first First integer to compare.
 * @param second Second integer to compare.
 * @return An integer greater than, equal to, or less than 0, according as the integer first is greater than, equal to, or
 * less than the integer second.
 */
int compare_int(const int *first, const int *second) {
    return *first - *second;
}

/**
 * Comparator function to compare two integers in reverse.
 * @param first
 * @param second
 * @param first First integer to compare.
 * @param second Second integer to compare.
 * @return An integer greater than, equal to, or less than 0, according as the integer first is less than, equal to, or
 * greater than the integer second.
 */
int compare_int_r(const int *first, const int *second) {
    return -compare_int(first, second);
}

/**
 * Comparator function to compare two doubles.
 * @param first First double to compare.
 * @param second Second double to compare.
 * @return -1, 0, +1, according as the integer double is less than, equal to, or greater than the double second.
 */
int compare_double(const double *first, const double *second) {
    if (*first < *second){
        return -1;
    } else {
        if (*first > *second){
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Comparator function to compare two doubles in reverse order.
 * @param first First double to compare.
 * @param second Second double to compare.
 * @return -1, 0, +1, according as the integer double is greater than, equal to, or less than the double second.
 */
int compare_double_r(const double *first, const double *second) {
    return -compare_double(first, second);
}

/**
 * Comparator function to compare two string lexicographically in reverse. Uses strcmp for the comparison.
 * @param first First string to compare.
 * @param second Second string to compare.
 * @return An integer greater than, equal to, or less than 0, according as the string first is less than, equal to, or
 * greater than the string second.
 */
int compare_string_r(char *first, char *second) {
    return strcmp(second, first);
}

/**
 * Deallocates memory allocated for an integer
 * @param value Memory storing the integer
 */
void free_int(int *value) {
    free_(value);
}

/**
 * Deallocates memory allocated for a string
 * @param value Memory storing the string
 */
void free_string(char *value) {
    free_(value);
}

/**
 * Allocates memory for the hash table in rehashing. Allocates an array of linked lists, where the size of the
 * array is prime number primes[prime_index].
 * @param prime_index Index that determines the next prime number for the size of the hash table.
 * @param key_compare Comparator function to compare two items in the linked list. The function will be used in
 * searching the hash table.
 * @return Allocated hash table.
 */
Linked_list_ptr *allocate_hash_table(int prime_index, int (*key_compare)(const void *, const void *)) {
    Linked_list_ptr *table;
    int N = primes[prime_index];
    table = malloc_(N * sizeof(Linked_list_ptr), "allocate_hash_table");
    for (int i = 0; i < N; i++) {
        table[i] = create_linked_list(key_compare);
    }
    return table;
}

/**
 * Constructor of the hash map. Allocates an empty hash map, with a size of 11 initially.
 * @param hash_function Hash function for the hash map.
 * @param key_compare Comparator function to compare two items in the linked list. The function will be used in
 * searching the hash table.
 * @return Empty hash map.
 */
Hash_map_ptr create_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *)) {
    Hash_map_ptr result = malloc_(sizeof(Hash_map), "create_hash_map");
    result->prime_index = 0;
    result->table = allocate_hash_table(result->prime_index, key_compare);
    result->hash_function = hash_function;
    result->key_compare = key_compare;
    result->count = 0;
    return result;
}

/**
 * Creates a default string hash map using create_hash_map.
 * @return Empty string hash map
 */
Hash_map_ptr create_string_hash_map() {
    return create_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                           (int (*)(const void *, const void *)) compare_string);
}

/**
 * Creates a default integer hash map using create_hash_map.
 * @return Empty integer hash map
 */
Hash_map_ptr create_integer_hash_map() {
    return create_hash_map((unsigned int (*)(const void *, int)) hash_function_int,
                           (int (*)(const void *, const void *)) compare_int);
}

/**
 * Destructor method for the hash map. Deallocates memory allocated for the hash map and its linked lists including
 * the contents of the value in the hash node.
 * @param hash_map The hash map.
 * @param free_value_method Destructor method for the value in the hash node in the linked lists.
 */
void free_hash_map(Hash_map_ptr hash_map, void (*free_value_method)(void *)) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            if (free_value_method != NULL) {
                free_value_method(hash_node->value);
            }
            free_(hash_node);
            free_(removed);
        }
        free_(linked_list);
    }
    free_(hash_map->table);
    free_(hash_map);
}

/**
 * Destructor method for the hash map. Deallocates memory allocated for the hash map and its linked lists including
 * the contents of the key and value in the hash node.
 * @param hash_map The hash map.
 * @param key_free_method Destructor method for the key in the hash node in the linked lists.
 * @param value_free_method Destructor method for the value in the hash node in the linked lists.
 */
void free_hash_map2(Hash_map_ptr hash_map, void (*key_free_method)(void *), void (*value_free_method)(void *)) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            if (key_free_method != NULL) {
                key_free_method(hash_node->key);
            }
            if (value_free_method != NULL) {
                value_free_method(hash_node->value);
            }
            free_(hash_node);
            free_(removed);
        }
        free_(linked_list);
    }
    free_(hash_map->table);
    free_(hash_map);
}

/**
 * Destructor method for the hash map, which has Counter Hash maps as content, that is node values. Does the same
 * job in free_hash_map except it calls free_counter_hash_map instead of free_value_method.
 * @param hash_map The hash map.
 */
void free_hash_map_of_counter_hash_map(Hash_map_ptr hash_map) {
    int N = primes[hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            Hash_node_ptr hash_node = removed->data;
            free_counter_hash_map(hash_node->value);
            free_(hash_node);
            free_(removed);
        }
        free_(linked_list);
    }
    free_(hash_map->table);
    free_(hash_map);
}

/**
 * Rehashes the hash map. It basically allocates a new hash table of size primes[hash_map->prime_index + 1] and rehashes
 * all the data already hashed in the original hash map. Original hash table is freed and new hash table is created.
 * @param hash_map The hash map to be rehashed.
 */
void rehash_hash_map(Hash_map_ptr hash_map) {
    Linked_list_ptr *new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            Hash_node_ptr hash_node = iterator->data;
            unsigned int address = hash_map->hash_function(hash_node->key, primes[hash_map->prime_index + 1]);
            add_last(new_table[address], iterator);
            iterator = next;
        }
    }
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        free_(hash_map->table[i]);
    }
    free_(hash_map->table);
    hash_map->prime_index++;
    hash_map->table = new_table;
}

/**
 * Inserts a new value to the hash map with a given (key, value) pair.
 * @param hash_map Hash map to insert (key, value) pair.
 * @param key Key of the item inserted.
 * @param value Value of the item inserted.
 * @return Created and inserted linked list node that contains the key and value.
 */
Hash_node_ptr hash_map_insert(Hash_map_ptr hash_map, void *key, void *value) {
    unsigned int address;
    address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    if (hash_map_contains(hash_map, key)) {
        Node_ptr node = hash_list_get(hash_map->table[address], key);
        remove_node(hash_map->table[address], node, NULL);
        hash_map->count--;
    }
    Hash_node_ptr hash_node = create_hash_node(key, value);
    add_last(hash_map->table[address], create_node(hash_node));
    hash_map->count++;
    if (hash_map->count > 0.8 * primes[hash_map->prime_index]) {
        rehash_hash_map(hash_map);
    }
    return hash_node;
}

/**
 * Checks if the hash map contains the given key.
 * @param hash_map Hash map to search.
 * @param key Key to be searched in the hash map.
 * @return True if the hash map contains the key, false otherwise.
 */
bool hash_map_contains(const Hash_map* hash_map, const void *key) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    return hash_list_contains(hash_map->table[address], key);
}

/**
 * Checks if the hash map contains the given key, and it contains returns the value corresponding for that key,
 * otherwise it returns NULL.
 * @param hash_map Hash map to search the key.
 * @param key Key to be searched in the hash map.
 * @return The value for the key, if the key exists, NULL otherwise.
 */
void *hash_map_get(const Hash_map* hash_map, const void *key) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL) {
        Hash_node_ptr hash_node = node->data;
        return hash_node->value;
    } else {
        return NULL;
    }
}

/**
 * Removes an item with the given key from the hash map. The function also deallocates the value associated with
 * the key.
 * @param hash_map Hash map
 * @param key Key for which item will be deleted.
 * @param free_method Destructor method for the value associated with the key.
 */
void hash_map_remove(Hash_map_ptr hash_map, const void *key, void free_method(void *)) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL) {
        remove_node(hash_map->table[address], node, free_method);
        hash_map->count--;
    }
}

/**
 * Checks if the linked list contains a specific item. Comparison will be done using the compare method set in the
 * linked list construction.
 * @param linked_list Linked list
 * @param key Item to be searched
 * @return The node containing the item if the linked list contains the item, NULL otherwise.
 */
Node_ptr hash_list_get(const Linked_list* linked_list, const void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

/**
 * Checks if the linked list contains a specific item. Comparison will be done using the compare method set in the
 * linked list construction.
 * @param linked_list Linked list
 * @param key Item to be searched
 * @return True if the linked list contains the item, false otherwise.
 */
bool hash_list_contains(const Linked_list* linked_list, const void *key) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_list->compare(hash_node->key, key) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

/**
 * Constructs and returns an array list of all key-value pairs (stored as Hash_node_ptr) in the hash map.
 * @param hash_map Hash map
 * @return An array list of all key-value pairs (stored as Hash_node_ptr) in the hash map.
 */
Array_list_ptr key_value_list(const Hash_map* hash_map) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node);
            iterator = iterator->next;
        }
    }
    return result;
}

/**
 * Construct and return an array list of all keys in the hash map.
 * @param hash_map Hash map
 * @return An array list of all keys in the hash map.
 */
Array_list_ptr key_list(const Hash_map* hash_map) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node->key);
            iterator = iterator->next;
        }
    }
    return result;
}

/**
 * Construct and return an array list of all values in the hash map.
 * @param hash_map Hash map
 * @return An array list of all values in the hash map.
 */
Array_list_ptr value_list(const Hash_map *hash_map) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            array_list_add(result, hash_node->value);
            iterator = iterator->next;
        }
    }
    return result;
}

/**
 * Checks if the hash map is empty or not.
 * @param hash_map Hash map
 * @return Returns true if the hash map is empty, false otherwise.
 */
bool hash_map_is_empty(const Hash_map* hash_map) {
    return hash_map->count == 0;
}

/**
 * Inserts all elements in the second hash map to the first hash map. The keys and values are copied or cloned
 * depending on the clone_key_method and clone_value_method respectively. If a clone method is NULL, the element is
 * copied, otherwise it is cloned and the clone is inserted.
 * @param hash_map1 First hash map
 * @param hash_map2 Second hash map
 * @param clone_key_method Cloning method for creating a clone of the key.
 * @param clone_value_method Cloning method for creating a clone of the value.
 */
void hash_map_merge(Hash_map_ptr hash_map1,
                    Hash_map_ptr hash_map2,
                    void* (*clone_key_method)(void* key),
                    void* (*clone_value_method)(void* value)) {
    for (int i = 0; i < primes[hash_map2->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map2->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Hash_node_ptr hash_node = iterator->data;
            if (clone_key_method != NULL){
                if (clone_value_method != NULL){
                    hash_map_insert(hash_map1, clone_key_method(hash_node->key), clone_value_method(hash_node->value));
                } else {
                    hash_map_insert(hash_map1, clone_key_method(hash_node->key), hash_node->value);
                }
            } else {
                if (clone_value_method != NULL){
                    hash_map_insert(hash_map1, hash_node->key, clone_value_method(hash_node->value));
                } else {
                    hash_map_insert(hash_map1, hash_node->key, hash_node->value);
                }
            }
            iterator = iterator->next;
        }
    }
}

/**
 * Returns the key object as if it is stored in the hash map.
 * @param hash_map Hash map to search for the key.
 * @param key Key to be searched in the hash map
 * @return If the key exists, returns the address of the key, otherwise it returns NULL.
 */
void *hash_map_get_key(const Hash_map *hash_map, const void *key) {
    unsigned int address = hash_map->hash_function(key, primes[hash_map->prime_index]);
    Node_ptr node = hash_list_get(hash_map->table[address], key);
    if (node != NULL) {
        Hash_node_ptr hash_node = node->data;
        return hash_node->key;
    } else {
        return NULL;
    }
}
