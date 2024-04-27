//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include "Tree.h"
#include "TreeNode.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the tree. According to the comparator, the tree could contain any object.
 * @param comparator Comparator function to compare two elements.
 * @return Empty tree.
 */
Tree_ptr create_tree(int (*compare)(const void *, const void *)) {
    Tree_ptr result = malloc_(sizeof(Tree), "create_tree");
    result->root = NULL;
    result->compare = compare;
    return result;
}

/**
 * Destructor method for the binary search tree. Deallocates memory allocated for the binary search tree and its node
 * contents
 * @param tree Binary search tree
 * @param free_method Destructor method for the value in the tree node.
 */
void free_tree(Tree_ptr tree, void (*free_method)(void *)) {
    if (tree->root != NULL) {
        free_tree_node(tree->root, free_method);
    }
    free_(tree);
}

/**
 * The search starts from the root node, and we represent the node, with which we compare the searched value, with
 * d. If the searched value is equal to the value of the current node, we have found the node we search for, the
 * function will return that node. If the searched value is smaller than the value of the current node , the number
 * we search for must be on the left subtree of the current node, therefore the new current node must be the left
 * child of the current node. As the last case, if the searched value is larger than the value of the current node,
 * the number we search for must be on the right subtree of the current node, therefore the new current node must be
 * the right child of the current node. If this search continues until the leaf nodes of the tree and we can't find
 * the node we search for, node d will be null and the function will return null.
 * @param tree Binary search tree
 * @param value Searched value
 * @return If the value exists in the tree, the function returns the node that contains the node. Otherwise, it
 * returns null.
 */
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

/**
 * Inserts a child to its parent as left or right child.
 * @param tree Binary search tree
 * @param parent New parent of the child node.
 * @param child Child node.
 */
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

/**
 * In order to add a new node into a binary search tree, we need to first find out the place where we will insert
 * the new node. For this, we start from the root node and traverse the tree down. At each step, we compare the
 * value of the new node with the value of the current node. If the value of the new node is smaller than the value
 * of the current node, the new node will be inserted into the left subtree of the current node. To accomplish this,
 * we continue the process with the left child of the current node. If the situation is reverse, that is, if the
 * value of the new node is larger than the value of the current node, the new node will be inserted into the right
 * subtree of the current node. In this case, we continue the process with the right child of the current node.
 * @param tree Binary search tree
 * @param node Node to be inserted.
 */
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
