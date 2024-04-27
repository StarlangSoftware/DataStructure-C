//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include "HashSet.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the hash set. Allocates an empty hash set, with a size of 11 initially.
 * @param hash_function Hash function for the hash set.
 * @param compare Comparator function to compare two items in the linked list. The function will be used in
 * searching the hash table.
 * @return Empty hash set.
 */
Hash_set_ptr create_hash_set(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *)) {
    Hash_set_ptr result = malloc_(sizeof(Hash_set), "create_hash_set");
    result->hash_map = create_hash_map(hash_function, compare);
    return result;
}

/**
 * Constructor of a string hash set. Calls create_hash_set method for string objects. The function initializes the hash
 * set with the elements in the array.
 * @param array Array containing the strings to be stored in the hash set.
 * @param size Size of the array.
 * @return Hash set with an array of strings.
 */
Hash_set_ptr create_hash_set_of_string(char **array, int size) {
    Hash_set_ptr result = create_hash_set((unsigned int (*)(const void *, int)) hash_function_string,
                                          (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < size; i++) {
        hash_set_insert(result, array[i]);
    }
    return result;
}

/**
 * Constructor of a string hash set. Calls create_hash_set method for string objects. The function initializes the hash
 * set with the elements in the array list.
 * @param list Array list containing the strings to be stored in the hash set.
 * @return Hash set with an array list of strings.
 */
Hash_set_ptr create_hash_set_of_string2(Array_list_ptr list) {
    Hash_set_ptr result = create_hash_set((unsigned int (*)(const void *, int)) hash_function_string,
                                          (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < list->size; i++) {
        hash_set_insert(result, array_list_get(list, i));
    }
    return result;
}

/**
 * Destructor method for the hash set. Deallocates memory allocated for the hash set and its linked lists including
 * the contents of the node in the linked list.
 * @param hash_map The hash set.
 * @param free_value_method Destructor method for the contents of the node in the linked lists.
 */
void free_hash_set(Hash_set_ptr hash_set, void (*free_method)(void *)) {
    int N = primes[hash_set->hash_map->prime_index];
    for (int i = 0; i < N; i++) {
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        while (linked_list->head != NULL) {
            Node_ptr removed = linked_list->head;
            linked_list->head = linked_list->head->next;
            if (free_method != NULL) {
                free_method(removed->data);
            }
            free_(removed);
        }
        free_(linked_list);
    }
    free_(hash_set->hash_map->table);
    free_(hash_set->hash_map);
    free_(hash_set);
}

/**
 * Inserts a new value to the hash set with a given key.
 * @param hash_set Hash set to insert key.
 * @param key Key of the item inserted.
 */
void hash_set_insert(Hash_set_ptr hash_set, void *key) {
    unsigned int address;
    address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    if (!hash_set_contains(hash_set, key)) {
        add_last(hash_set->hash_map->table[address], create_node(key));
        hash_set->hash_map->count++;
        if (hash_set->hash_map->count > 0.8 * primes[hash_set->hash_map->prime_index]) {
            rehash_hash_set(hash_set->hash_map);
        }
    }
}

/**
 * Checks if the hash set contains the given key.
 * @param hash_set Hash set to search.
 * @param key Key to be searched in the hash set.
 * @return True if the hash set contains the key, false otherwise.
 */
bool hash_set_contains(const Hash_set* hash_set, const void *key) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    return linked_list_contains(hash_set->hash_map->table[address], key);
}

/**
 * Removes an item with the given key from the hash set. The function also deallocates the value associated with
 * the key.
 * @param hash_set Hash set
 * @param key Key for which item will be deleted.
 * @param free_method Destructor method for the value associated with the key.
 */
void hash_set_remove(Hash_set_ptr hash_set, const void *key, void (*free_method)(void *)) {
    unsigned int address = hash_set->hash_map->hash_function(key, primes[hash_set->hash_map->prime_index]);
    Node_ptr node = linked_list_get(hash_set->hash_map->table[address], key);
    if (node != NULL) {
        remove_node(hash_set->hash_map->table[address], node, free_method);
        hash_set->hash_map->count--;
    }
}

/**
 * Rehashes the hash set. It basically allocates a new hash table of size primes[hash_map->prime_index + 1] and rehashes
 * all the data already hashed in the original hash set. Original hash table is freed and new hash table is created.
 * @param hash_map The hash map to be rehashed.
 */
void rehash_hash_set(Hash_map_ptr hash_map) {
    Linked_list_ptr *new_table = allocate_hash_table(hash_map->prime_index + 1, hash_map->key_compare);
    for (int i = 0; i < primes[hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            Node_ptr next = iterator->next;
            unsigned int address = hash_map->hash_function(iterator->data, primes[hash_map->prime_index + 1]);
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
 * Construct and return an array list of all keys in the hash set.
 * @param hash_set Hash set
 * @return An array list of all keys in the hash set.
 */
Array_list_ptr hash_set_key_list(const Hash_set* hash_set) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < primes[hash_set->hash_map->prime_index]; i++) {
        Linked_list_ptr linked_list = hash_set->hash_map->table[i];
        Node_ptr iterator = linked_list->head;
        while (iterator != NULL) {
            array_list_add(result, iterator->data);
            iterator = iterator->next;
        }
    }
    return result;
}

/**
 * Checks if the hash set is empty or not.
 * @param hash_set Hash set
 * @return Returns true if the hash set is empty, false otherwise.
 */
bool hash_set_is_empty(const Hash_set* hash_set) {
    return hash_map_is_empty(hash_set->hash_map);
}

/**
 * Inserts all elements in the second hash set to the first hash set. The keys are copied or cloned
 * depending on the clone_method. If the clone method is NULL, the element is copied, otherwise it is cloned and
 * the clone is inserted.
 * @param hash_map1 First hash map
 * @param hash_map2 Second hash map
 * @param clone_method Cloning method for creating a clone of the key.
 */
void hash_set_merge(Hash_set_ptr hash_set1, const Hash_set* hash_set2, void* (*clone_method)(void* item)) {
    Array_list_ptr key_list = hash_set_key_list(hash_set2);
    for (int i = 0; i < key_list->size; i++){
        if (clone_method != NULL){
            if (!hash_set_contains(hash_set1, array_list_get(key_list, i))){
                hash_set_insert(hash_set1, clone_method(array_list_get(key_list, i)));
            }
        } else {
            hash_set_insert(hash_set1, array_list_get(key_list, i));
        }
    }
    free_array_list(key_list, NULL);
}
