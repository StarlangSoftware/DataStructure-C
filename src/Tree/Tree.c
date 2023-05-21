//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include <stdlib.h>
#include "Tree.h"
#include "TreeNode.h"

Tree_ptr create_tree(int (*compare)(const void *, const void *)) {
    Tree_ptr result = malloc(sizeof(Tree));
    result->root = NULL;
    result->compare = compare;
    return result;
}

void free_tree(Tree_ptr tree, void (*free_method)(void *)) {
    if (tree->root != NULL) {
        free_tree_node(tree->root, free_method);
    }
    free(tree);
}

Tree_node_ptr search_tree(const Tree* tree, const void *value) {
    Tree_node_ptr d = tree->root;
    while (d != NULL) {
        if (tree->compare(d->data, value) == 0) {
            return d;
        } else {
            if (tree->compare(d->data, value) > 0) {
                d = d->left;
            } else {
                d = d->right;
            }
        }
    }
    return NULL;
}

void insert_child(Tree_ptr tree, Tree_node_ptr parent, Tree_node_ptr child) {
    if (parent == NULL) {
        tree->root = child;
    } else {
        if (tree->compare(child->data, parent->data) < 0) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
}

void insert_tree(Tree_ptr tree, void *value) {
    Tree_node_ptr y = NULL;
    Tree_node_ptr x = tree->root;
    while (x != NULL) {
        y = x;
        if (tree->compare(value, x->data) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    insert_child(tree, y, create_tree_node(value));
}
