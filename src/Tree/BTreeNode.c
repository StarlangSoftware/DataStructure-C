//
// Created by Olcay Taner YILDIZ on 23.01.2023.
//

#include <stdlib.h>
#include "BTreeNode.h"
#include "../Memory/Memory.h"

BTree_node_ptr create_btree_node(int d) {
    BTree_node_ptr result = malloc_(sizeof(BTree_node), "create_btree_node_1");
    result->m = 0;
    result->d = d;
    result->leaf = 1;
    result->K = malloc_((2 * d + 1) * sizeof(void *), "create_btree_node_2");
    result->children = malloc_((2 * d + 1) * sizeof(BTree_node_ptr), "create_btree_node_3");
    for (int i = 0; i < 2 * d + 1; i++){
        result->children[i] = NULL;
    }
    return result;
}

BTree_node_ptr create_btree_node_with_children(BTree_node_ptr first_Child,
                                               BTree_node_ptr second_child,
                                               void *newK,
                                               int d) {
    BTree_node_ptr result = malloc_(sizeof(BTree_node), "create_btree_node_with_children_1");
    result->m = 1;
    result->d = d;
    result->leaf = 0;
    result->K = malloc_((2 * d + 1) * sizeof(void *), "create_btree_node_with_children_2");
    result->children = malloc_((2 * d + 1) * sizeof(BTree_node_ptr), "create_btree_node_with_children_3");
    for (int i = 0; i < 2 * d + 1; i++){
        result->children[i] = NULL;
    }
    result->children[0] = first_Child;
    result->children[1] = second_child;
    result->K[0] = newK;
    return result;
}

void free_btree_node(BTree_node_ptr btree_node, void (*free_method)(void *)) {
    if (!btree_node->leaf) {
        for (int i = 0; i < 2 * btree_node->d + 1; i++) {
            if (btree_node->children[i] != NULL){
                free_btree_node(btree_node->children[i], free_method);
            }
        }
        free_(btree_node->children);
    } else {
        free_(btree_node->children);
    }
    if (free_method != NULL) {
        for (int i = 0; i < 2 * btree_node->d + 1; i++) {
            free_method(btree_node->K[i]);
        }
    }
    free_(btree_node->K);
    free_(btree_node);
}

int btree_node_position(const BTree_node* btree_node, const void *value, int (*compare)(const void *, const void *)) {
    if (btree_node->m == 0) {
        return 0;
    }
    if (compare(value, btree_node->K[btree_node->m - 1]) > 0) {
        return btree_node->m;
    } else {
        for (int i = 0; i < btree_node->m; i++) {
            if (compare(value, btree_node->K[i]) <= 0) {
                return i;
            }
        }
    }
    return -1;
}

void insert_into_K(BTree_node_ptr btree_node, int index, void *inserted_K) {
    for (int i = btree_node->m; i > index; i--) {
        btree_node->K[i] = btree_node->K[i - 1];
    }
    btree_node->K[index] = inserted_K;
}

void move_half_of_the_K_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    for (int i = 0; i < btree_node->d; i++) {
        new_node->K[i] = btree_node->K[i + btree_node->d + 1];
    }
    new_node->m = btree_node->d;
}

void move_half_of_the_children_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    for (int i = 0; i < btree_node->d; i++) {
        new_node->children[i] = btree_node->children[i + btree_node->d + 1];
        btree_node->children[i + btree_node->d + 1] = NULL;
    }
}

void move_half_of_the_elements_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    move_half_of_the_K_to_new_node(btree_node, new_node);
    move_half_of_the_children_to_new_node(btree_node, new_node);
}

BTree_node_ptr insert_btree_node(BTree_node_ptr btree_node, void *value, int (*compare)(const void *, const void *), int is_root) {
    BTree_node_ptr s;
    BTree_node_ptr new_node;
    int child;
    child = btree_node_position(btree_node, value, compare);
    if (!btree_node->children[child]->leaf) {
        s = insert_btree_node(btree_node->children[child], value, compare, 0);
    } else {
        s = insert_btree_leaf(btree_node->children[child], value, compare);
    }
    if (s == NULL) {
        return NULL;
    }
    insert_into_K(btree_node, child, btree_node->children[child]->K[btree_node->d]);
    if (btree_node->m < 2 * btree_node->d) {
        btree_node->children[child + 1] = s;
        btree_node->m++;
        return NULL;
    } else {
        new_node = create_btree_node(btree_node->d);
        new_node->leaf = 0;
        move_half_of_the_elements_to_new_node(btree_node, new_node);
        new_node->children[btree_node->d] = s;
        btree_node->m = btree_node->d;
        if (is_root) {
            BTree_node_ptr a = create_btree_node_with_children(btree_node, new_node, btree_node->K[btree_node->d],
                                                               btree_node->d);
            return a;
        } else {
            return new_node;
        }
    }
}

BTree_node_ptr insert_btree_leaf(BTree_node_ptr btree_node, void *value, int (*compare)(const void *, const void *)) {
    int child;
    BTree_node_ptr new_node;
    child = btree_node_position(btree_node, value, compare);
    insert_into_K(btree_node, child, value);
    if (btree_node->m < 2 * btree_node->d) {
        btree_node->m++;
        return NULL;
    } else {
        new_node = create_btree_node(btree_node->d);
        move_half_of_the_K_to_new_node(btree_node, new_node);
        btree_node->m = btree_node->d;
        return new_node;
    }
}
