//
// Created by Olcay Taner YILDIZ on 26.01.2023.
//
#include <stdio.h>
#include "../src/Tree/Tree.h"
#include "../src/Tree/AvlTree.h"
#include "../src/Tree/BTree.h"

int compareIntMax(const int *first, const int *second) {
    return *first - *second;
}

void testTree() {
    int array[8] = {4, 6, 2, 5, 3, 1, 7, 8};
    Tree_ptr tree = create_tree((int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 7; i++) {
        insert_tree(tree, &array[i]);
    }
    if (search_tree(tree, &array[4]) == NULL) {
        printf("Test Failed in testTree\n");
    }
    if (search_tree(tree, &array[7]) != NULL) {
        printf("Test Failed in testTree\n");
    }
}

void testTree2() {
    int array[32];
    for (int i = 0; i < 31; i++) {
        array[i] = i;
    }
    array[31] = 31;
    Avl_tree_ptr tree = create_avl_tree((int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 31; i++) {
        insert_avl_tree(tree, &array[i]);
    }
    for (int i = 0; i < 31; i++) {
        if (search_avl_tree(tree, &array[i]) == NULL) {
            printf("Test Failed in testTree2\n");
        }
    }
    if (search_avl_tree(tree, &array[31]) != NULL) {
        printf("Test Failed in testTree2\n");
    }
}

void testTree3() {
    int array[32];
    for (int i = 0; i < 31; i++) {
        array[i] = i;
    }
    array[31] = 31;
    BTree_ptr tree = create_btree(1, (int (*)(void *, void *)) compareIntMax);
    for (int i = 0; i < 31; i++) {
        insert_btree(tree, &array[i]);
    }
    for (int i = 0; i < 31; i++) {
        if (search_btree(tree, &array[i]) == NULL) {
            printf("Test Failed in testTree3\n");
        }
    }
    if (search_btree(tree, &array[31]) != NULL) {
        printf("Test Failed in testTree3\n");
    }
}

int main() {
    testTree();
    testTree2();
    testTree3();
}