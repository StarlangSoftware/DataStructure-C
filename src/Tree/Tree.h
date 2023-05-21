//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#ifndef DATASTRUCTURE_TREE_H
#define DATASTRUCTURE_TREE_H

#include "TreeNode.h"

struct tree {
    Tree_node_ptr root;
    int (*compare)(const void *, const void *);
};

typedef struct tree Tree;
typedef Tree *Tree_ptr;

Tree_ptr create_tree(int (*compare)(const void *, const void *));

void free_tree(Tree_ptr tree, void free_method(void *data));

Tree_node_ptr search_tree(const Tree* tree, const void *value);

void insert_child(Tree_ptr tree, Tree_node_ptr parent, Tree_node_ptr child);

void insert_tree(Tree_ptr tree, void *value);

#endif //DATASTRUCTURE_TREE_H
