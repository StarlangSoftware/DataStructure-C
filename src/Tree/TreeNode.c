//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include "TreeNode.h"
#include "../Memory/Memory.h"

Tree_node_ptr create_tree_node(void *data) {
    Tree_node_ptr result = malloc_(sizeof(Tree_node), "create_tree_node");
    result->left = NULL;
    result->right = NULL;
    result->data = data;
    return result;
}

void free_tree_node(Tree_node_ptr tree_node, void (*free_method)(void *)) {
    if (tree_node->left != NULL) {
        free_tree_node(tree_node->left, free_method);
    }
    if (tree_node->right != NULL) {
        free_tree_node(tree_node->right, free_method);
    }
    if (free_method != NULL) {
        free_method(tree_node->data);
    }
    free_(tree_node);
}
