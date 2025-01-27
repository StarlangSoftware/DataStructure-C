//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#include "BTree.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the B+ tree. According to the comparator, the tree could contain any object.
 * @param d d parameter in the B+ tree.
 * @param compare Comparator function to compare two elements.
 * @return Empty tree.
 */
BTree_ptr create_btree(int d, int (*compare)(const void *, const void *)) {
    BTree_ptr result = malloc_(sizeof(BTree), "create_btree");
    result->d = d;
    result->compare = compare;
    result->root = NULL;
    return result;
}

/**
 * Destructor method for the B+ tree. Deallocates memory allocated for the B+ tree and its node
 * contents
 * @param btree B+ tree
 * @param free_method Destructor method for the value in the tree node.
 */
void free_btree(BTree_ptr btree, void (*free_method)(void *)) {
    if (btree->root != NULL) {
        free_btree_node(btree->root, free_method);
    }
    free_(btree);
}

/**
 * We start searching from the root node, the node with which we compare the searched value at each stage is
 * represented by b, and we continue the search until we arrive the leaf nodes. In order to understand the subtree
 * of node b where our searched value resides, we need to compare the searched value with the values Ki. For this,
 * the function named position is given. If the searched value is larger than the last value of node b, we need to
 * continue the search with the rightmost child. If the searched value is smaller than the i. value of node b, we
 * need to continue the search with the i. child. As a last step, the function returns the leaf node of node b.
 * @param btree B+ tree
 * @param value Value searched in B+ tree.
 * @return If the value exists in the tree, the function returns the node that contains the node. Otherwise, it
 * returns null.
 */
BTree_node_ptr search_btree(const BTree* btree, const void *value) {
    int child;
    BTree_node_ptr b;
    b = btree->root;
    while (!b->leaf) {
        child = btree_node_position(b, value, btree->compare);
        if (child < b->m && b->K[child] == value) {
            return b;
        }
        b = b->children[child];
    }
    child = btree_node_position(b, value, btree->compare);
    if (child < b->m && b->K[child] == value) {
        return b;
    }
    return NULL;
}

void insert_btree(BTree_ptr btree, void *value) {
    BTree_node_ptr s;
    if (btree->root == NULL) {
        btree->root = create_btree_node(btree->d);
    }
    if (btree->root->leaf) {
        s = insert_btree_leaf(btree->root, value, btree->compare);
        if (s != NULL) {
            BTree_node_ptr tmp = btree->root;
            btree->root = create_btree_node_with_children(tmp, s, tmp->K[btree->d], btree->d);
        }
    } else {
        s = insert_btree_node(btree->root, value, btree->compare, 1);
        if (s != NULL) {
            btree->root = s;
        }
    }
}
