//
// Created by Olcay Taner YILDIZ on 9.02.2023.
//

#include <stdlib.h>
#include "LinkedHashMap.h"
#include "HashNode.h"

Linked_hash_map_ptr create_linked_hash_map(unsigned int (*hash_function)(void *, int), int (*compare)(void *, void *)) {
    Linked_hash_map_ptr result = malloc(sizeof(Linked_hash_map));
    result->hash_map = create_hash_map(hash_function, compare);
    result->linked_list = create_linked_list(compare);
    return result;
}

void free_linked_hash_map(Linked_hash_map_ptr linked_hash_map, void (*free_method)(void *)) {
    free_hash_map(linked_hash_map->hash_map, free_method);
    free_linked_list(linked_hash_map->linked_list, NULL);
}

void linked_hash_map_insert(Linked_hash_map_ptr linked_hash_map, void *key, void* value) {
    Hash_node_ptr hash_node = hash_map_insert(linked_hash_map->hash_map, key, value);
    if (linked_hash_map_contains(linked_hash_map, key)){
        linked_hash_map_remove_key(linked_hash_map, key);
    }
    add_last(linked_hash_map->linked_list, create_node(hash_node));
}

int linked_hash_map_contains(Linked_hash_map_ptr linked_hash_map, void *key) {
    return hash_map_contains(linked_hash_map->hash_map, key);
}

void linked_hash_map_remove(Linked_hash_map_ptr linked_hash_map, void *key, void (*free_method)(void *)) {
    hash_map_remove(linked_hash_map->hash_map, key, free_method);
    linked_hash_map_remove_key(linked_hash_map, key);
}

void linked_hash_map_remove_key(Linked_hash_map_ptr linked_hash_map, void *key) {
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL){
        Hash_node_ptr hash_node = iterator->data;
        if (linked_hash_map->linked_list->compare(hash_node->key, key) == 0){
            remove_node(linked_hash_map->linked_list, iterator, NULL);
            break;
        }
        iterator = iterator->next;
    }
}

void *linked_hash_map_get(Linked_hash_map_ptr linked_hash_map, void *key) {
    return hash_map_get(linked_hash_map->hash_map, key);
}

Array_list_ptr linked_hash_map_key_value_list(Linked_hash_map_ptr linked_hash_map) {
    Array_list_ptr result = create_array_list();
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL){
        Hash_node_ptr hash_node = iterator->data;
        array_list_add(result, hash_node);
        iterator = iterator->next;
    }
    return result;
}

Array_list_ptr linked_hash_map_key_list(Linked_hash_map_ptr linked_hash_map) {
    Array_list_ptr result = create_array_list();
    Node_ptr iterator = linked_hash_map->linked_list->head;
    while (iterator != NULL){
        Hash_node_ptr hash_node = iterator->data;
        array_list_add(result, hash_node->key);
        iterator = iterator->next;
    }
    return result;
}
