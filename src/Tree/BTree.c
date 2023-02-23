//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#include <stdlib.h>
#include "BTree.h"

BTree_ptr create_btree(int d, int (*compare)(void *, void *)) {
    BTree_ptr result = malloc(sizeof(BTree));
    result->d = d;
    result->compare = compare;
    result->root = NULL;
    return result;
}

void free_btree(BTree_ptr btree, void (*free_method)(void *)) {
    if (btree->root != NULL) {
        free_btree_node(btree->root, free_method);
    }
    free(btree);
}

BTree_node_ptr search_btree(BTree_ptr btree, void *value) {
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
