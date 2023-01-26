//
// Created by Olcay Taner YILDIZ on 23.01.2023.
//

#ifndef DATASTRUCTURE_BTREENODE_H
#define DATASTRUCTURE_BTREENODE_H

struct btree_node{
    void** K;
    int m;
    int d;
    int leaf;
    struct btree_node** children;
};

typedef struct btree_node BTree_node;
typedef BTree_node* BTree_node_ptr;

BTree_node_ptr create_btree_node(int d);
BTree_node_ptr create_btree_node_with_children(BTree_node_ptr first_Child,
                                               BTree_node_ptr second_child,
                                               void* newK,
                                               int d);
void free_btree_node(BTree_node_ptr btree_node, void free_method(void* data));
int btree_node_position(BTree_node_ptr btree_node, void* value, int (*compare)(void*, void*));
void insert_into_K(BTree_node_ptr btree_node, int index, void* inserted_K);
void move_half_of_the_K_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node);
void move_half_of_the_children_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node);
void move_half_of_the_elements_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node);
BTree_node_ptr insert_btree_node(BTree_node_ptr btree_node, void* value, int (*compare)(void*, void*), int is_root);
BTree_node_ptr insert_btree_leaf(BTree_node_ptr btree_node, void* value, int (*compare)(void*, void*));

#endif //DATASTRUCTURE_BTREENODE_H
