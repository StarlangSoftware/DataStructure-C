//
// Created by Olcay Taner YILDIZ on 9.02.2023.
//

#include "LinkedHashMap.h"
#include "HashNode.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the linked hash map. Allocates an empty linked hash map, with a size of 11 initially. Also allocates
 * a linked list which stores the insertion order of the keys in the hash map.
 * @param hash_function Hash function for the hash map.
 * @param compare Comparator function to compare two items in the linked list. The function will be used in
 * searching the hash table.
 * @return Empty linked hash map.
 */
Linked_hash_map_ptr create_linked_hash_map(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *)) {
    Linked_hash_map_ptr result = malloc_(sizeof(Linked_hash_map), "create_linked_hash_map");
    result->hash_map = create_hash_map(hash_function, compare);
    result->linked_list = create_linked_list(compare);
    return result;
}

/**
 * Destructor method for the linked hash map. Deallocates memory allocated for the hash map and its linked lists including
 * the contents of the value in the hash node. Deallocates also the linked list that stores the insertion order.
 * @param linked_hash_map The linked hash map.
 * @param free_method Destructor method for the value in the hash node in the linked lists.
 */
void free_linked_hash_map(Linked_hash_map_ptr linked_hash_map, void (*free_method)(void *)) {
    free_hash_map(linked_hash_map->hash_map, free_method);
    free_linked_list(linked_hash_map->linked_list, NULL);
    free_(linked_hash_map);
}

/**
 * Destructor method for the linked hash map. Deallocates memory allocated for the hash map and its linked lists including
 * the contents of the key and value in the hash node. Deallocates also the linked list that stores the insertion order.
 * @param linked_hash_map The linked hash map.
 * @param key_free_method Destructor method for the key in the hash node in the linked lists.
 * @param free_method Destructor method for the value in the hash node in the linked lists.
 */
void free_linked_hash_map2(Linked_hash_map_ptr linked_hash_map, void (*key_free_method)(void *), void (*free_method)(void *)) {
    free_hash_map2(linked_hash_map->hash_map, key_free_method, free_method);
    free_linked_list(linked_hash_map->linked_list, NULL);
    free_(linked_hash_map);
}

/**
 * Inserts a new value to the linked hash map with a given (key, value) pair. Inserts also the hash node of the order
 * linked list.
 * @param linked_hash_map Hash map to insert (key, value) pair.
 * @param key Key of the item inserted.
 * @param value Value of the item inserted.
 */
void linked_hash_map_insert(Linked_hash_map_ptr linked_hash_map, void *key, void *value) {
    int contains = linked_hash_map_contains(linked_hash_map, key);
    Hash_node_ptr hash_node = hash_map_insert(linked_hash_map->hash_map, key, value);
    if (!contains) {
        add_last(linked_hash_map->linked_list, create_node(hash_node));
    } else {
        linked_hash_map_update_value(linked_hash_map, key, value);
    }
}

/**
 * Checks if the linked hash map contains the given key.
 * @param linked_hash_map Linked Hash map to search.
 * @param key Key to be searched in the linked hash map.
 * @return True if the linked hash map contains the key, false otherwise.
 */
bool linked_hash_map_contains(const Linked_hash_map* linked_hash_map, const void *key) {
    return hash_map_contains(linked_hash_map->hash_map, key);
}

/**
 * Removes an item with the given key from the linked hash map. The function also deallocates the value associated with
 * the key.
 * @param linked_hash_map Linked hash map
 * @param key Key for which item will be deleted.
 * @param free_method Destructor method for the value associated with the key.
 */
void linked_hash_map_remove(Linked_hash_map_ptr linked_hash_map, const void *key, void (*free_method)(void *)) {
    hash_map_remove(linked_hash_map->hash_map, key, free_method);
    linked_hash_map_remove_key(linked_hash_map, key);
}

/**
 * Removes an item with the given key from the linked hash map. The function also deallocates the value associated with
 * the key.
 * @param linked_hash_map Linked hash map
 * @param key Key for which item will be deleted.
 * @param free_method Destructor method for the value associated with the key.
 */
void linked_hash_map_remove2(Linked_hash_map_ptr linked_hash_map, const void *key, void (*free_method)(void *)) {
    hash_map_remove(linked_hash_map->hash_map, key, free_method);
    linked_hash_map_remove_key2(linked_hash_map, key);
}

/**
 * Removes the key from the order linked list in the linked hash map.
 * @param linked_hash_map Linked hash map
 * @param key Key for which item will be deleted.
 */
void linked_hash_map_remove_key(Linked_hash_map_ptr linked_hash_map, const void *key) {
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_hash_map->linked_list->compare(hash_node->key, key) == 0) {
            remove_node(linked_hash_map->linked_list, iterator, NULL);
            free_hash_node(hash_node, free_, NULL);
            break;
        }
        iterator = iterator->next;
    }
}

/**
 * Removes the key from the order linked list in the linked hash map.
 * @param linked_hash_map Linked hash map
 * @param key Key for which item will be deleted.
 */
void linked_hash_map_remove_key2(Linked_hash_map_ptr linked_hash_map, const void *key) {
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_hash_map->linked_list->compare(hash_node->key, key) == 0) {
            remove_node(linked_hash_map->linked_list, iterator, NULL);
            free_hash_node(hash_node, NULL, NULL);
            break;
        }
        iterator = iterator->next;
    }
}

/**
 * Updates with new value to the linked hash map with a given key. Updates also the hash node of the order
 * linked list.
 * @param linked_hash_map Hash map to update key with value.
 * @param key Key of the item updated.
 * @param value New value of the item.
 */
void linked_hash_map_update_value(Linked_hash_map_ptr linked_hash_map, const void *key, void *value) {
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        if (linked_hash_map->linked_list->compare(hash_node->key, key) == 0) {
            hash_node->value = value;
            break;
        }
        iterator = iterator->next;
    }
}

void *linked_hash_map_get(const Linked_hash_map* linked_hash_map, const void *key) {
    return hash_map_get(linked_hash_map->hash_map, key);
}

/**
 * Constructs and returns an array list of all key-value pairs (stored as Hash_node_ptr) in the linked hash map.
 * @param linked_hash_map Linked hash map
 * @return An array list of all key-value pairs (stored as Hash_node_ptr) in the linked hash map.
 */
Array_list_ptr linked_hash_map_key_value_list(const Linked_hash_map* linked_hash_map) {
    Array_list_ptr result = create_array_list();
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        array_list_add(result, hash_node);
        iterator = iterator->next;
    }
    return result;
}

/**
 * Construct and return an array list of all keys in the linked hash map.
 * @param linked_hash_map Linked hash map
 * @return An array list of all keys in the linked hash map.
 */
Array_list_ptr linked_hash_map_key_list(const Linked_hash_map* linked_hash_map) {
    Array_list_ptr result = create_array_list();
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL) {
        Hash_node_ptr hash_node = iterator->data;
        array_list_add(result, hash_node->key);
        iterator = iterator->next;
    }
    return result;
}
