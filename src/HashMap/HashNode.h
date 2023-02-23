//
// Created by Olcay Taner YILDIZ on 19.01.2023.
//

#ifndef DATASTRUCTURE_HASHNODE_H
#define DATASTRUCTURE_HASHNODE_H

struct hash_node {
    void *key;
    void *value;
};

typedef struct hash_node Hash_node;
typedef Hash_node *Hash_node_ptr;

Hash_node_ptr create_hash_node(void *key, void *value);

void free_hash_node(Hash_node_ptr hash_node, void free_key_method(void *), void free_value_method(void *));

#endif //DATASTRUCTURE_HASHNODE_H
