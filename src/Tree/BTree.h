//
// Created by Olcay Taner YILDIZ on 24.01.2023.
//

#ifndef DATASTRUCTURE_BTREE_H
#define DATASTRUCTURE_BTREE_H

#include "BTreeNode.h"

struct btree {
    BTree_node_ptr root;
    int d;
    int (*compare)(const void *, const void *);
};

typedef struct btree BTree;
typedef BTree *BTree_ptr;

BTree_ptr create_btree(int d, int (*compare)(const void *, const void *));

void free_btree(BTree_ptr tree, void free_method(void *data));

BTree_node_ptr search_btree(const BTree* btree, const void *value);

void insert_btree(BTree_ptr btree, void *value);

#endif //DATASTRUCTURE_BTREE_H
