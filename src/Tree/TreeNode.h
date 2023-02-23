//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#ifndef DATASTRUCTURE_TREENODE_H
#define DATASTRUCTURE_TREENODE_H

struct tree_node {
    void *data;
    struct tree_node *left;
    struct tree_node *right;
};

typedef struct tree_node Tree_node;
typedef Tree_node *Tree_node_ptr;

Tree_node_ptr create_tree_node(void *data);

void free_tree_node(Tree_node_ptr tree_node, void free_method(void *data));

#endif //DATASTRUCTURE_TREENODE_H
