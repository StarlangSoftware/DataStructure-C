//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include "AvlTreeNode.h"

struct avl_tree{
    Avl_tree_node_ptr root;
    int (*compare)(void*, void*);
};

typedef struct avl_tree Avl_tree;
typedef Avl_tree* Avl_tree_ptr;

Avl_tree_ptr create_avl_tree(int (*compare)(void*, void*));
void free_avl_tree(Avl_tree_ptr tree, void free_method(void* data));
Avl_tree_node_ptr search_avl_tree(Avl_tree_ptr tree, void* value);
int avl_tree_node_height(Avl_tree_node_ptr d);
Avl_tree_node_ptr rotate_left(Avl_tree_node_ptr k2);
int max(int x, int y);
Avl_tree_node_ptr rotate_right(Avl_tree_node_ptr k1);
Avl_tree_node_ptr double_rotate_left(Avl_tree_node_ptr k3);
Avl_tree_node_ptr double_rotate_right(Avl_tree_node_ptr k1);
void insert_avl_tree(Avl_tree_ptr tree, void* value);
void insert_avl_child(Avl_tree_ptr tree, Avl_tree_node_ptr parent, Avl_tree_node_ptr child);

#endif //DATASTRUCTURE_AVLTREE_H
