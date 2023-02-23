//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#ifndef DATASTRUCTURE_AVLTREENODE_H
#define DATASTRUCTURE_AVLTREENODE_H

struct avl_tree_node {
    void *data;
    struct avl_tree_node *left;
    struct avl_tree_node *right;
    int height;
};

typedef struct avl_tree_node Avl_tree_node;
typedef Avl_tree_node *Avl_tree_node_ptr;

Avl_tree_node_ptr create_avl_tree_node(void *data);

void free_avl_tree_node(Avl_tree_node_ptr tree_node, void free_method(void *data));

#endif //DATASTRUCTURE_AVLTREENODE_H
