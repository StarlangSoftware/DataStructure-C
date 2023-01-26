//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include <stdlib.h>
#include "AvlTreeNode.h"

Avl_tree_node_ptr create_avl_tree_node(void *data) {
    Avl_tree_node_ptr result = malloc(sizeof(Avl_tree_node));
    result->left = NULL;
    result->right = NULL;
    result->data = data;
    result->height = 1;
    return result;
}

void free_avl_tree_node(Avl_tree_node_ptr tree_node, void (*free_method)(void *)) {
    if (tree_node->left != NULL){
        free_avl_tree_node(tree_node->left, free_method);
    }
    if (tree_node->right != NULL){
        free_avl_tree_node(tree_node->right, free_method);
    }
    if (free_method != NULL){
        free_method(tree_node->data);
    }
    free(tree_node);
}
