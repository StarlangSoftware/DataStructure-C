//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#include <stdlib.h>
#include "HashNode.h"

Hash_node_ptr create_hash_node(void *key, void *value) {
    Hash_node_ptr result = malloc(sizeof(Hash_node));
    result->key = key;
    result->value = value;
    return result;
}

void free_hash_node(Hash_node_ptr hash_node, void (*free_key_method)(void *), void (*free_value_method)(void *)) {
    free_key_method(hash_node->key);
    free_value_method(hash_node->value);
    free(hash_node);
}
