//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include <stdlib.h>
#include "AvlTree.h"
#include "../Stack.h"
#include "../Memory/Memory.h"

Avl_tree_ptr create_avl_tree(int (*compare)(const void *, const void *)) {
    Avl_tree_ptr result = malloc_(sizeof(Avl_tree), "create_avl_tree");
    result->root = NULL;
    result->compare = compare;
    return result;
}

void free_avl_tree(Avl_tree_ptr tree, void (*free_method)(void *)) {
    if (tree->root != NULL) {
        free_avl_tree_node(tree->root, free_method);
    }
    free_(tree);
}

Avl_tree_node_ptr search_avl_tree(const Avl_tree* tree, const void *value) {
    Avl_tree_node_ptr d = tree->root;
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

int avl_tree_node_height(const Avl_tree_node* d) {
    if (d == NULL) {
        return 0;
    } else {
        return d->height;
    }
}

Avl_tree_node_ptr rotate_left(Avl_tree_node_ptr k2) {
    Avl_tree_node_ptr k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(avl_tree_node_height(k2->left), avl_tree_node_height(k2->right)) + 1;
    k1->height = max(avl_tree_node_height(k1->left), (k1->right)->height) + 1;
    return k1;
}

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

Avl_tree_node_ptr rotate_right(Avl_tree_node_ptr k1) {
    Avl_tree_node_ptr k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->height = max((k2->left)->height, avl_tree_node_height(k2->right)) + 1;
    k1->height = max(avl_tree_node_height(k1->left), avl_tree_node_height(k1->right)) + 1;
    return k2;
}

Avl_tree_node_ptr double_rotate_left(Avl_tree_node_ptr k3) {
    k3->left = rotate_right(k3->left);
    return rotate_left(k3);
}

Avl_tree_node_ptr double_rotate_right(Avl_tree_node_ptr k1) {
    k1->right = rotate_left(k1->right);
    return rotate_right(k1);
}

void insert_avl_tree(Avl_tree_ptr tree, void *value) {
    int LEFT = 1, RIGHT = 2;
    Avl_tree_node_ptr y = NULL;
    Avl_tree_node_ptr x = tree->root;
    Avl_tree_node_ptr t;
    int dir1 = 0, dir2 = 0;
    Stack_ptr c = create_stack();
    while (x != NULL) {
        y = x;
        push(c, y);
        dir1 = dir2;
        if (tree->compare(value, x->data) < 0) {
            x = x->left;
            dir2 = LEFT;
        } else {
            x = x->right;
            dir2 = RIGHT;
        }
    }
    insert_avl_child(tree, y, create_avl_tree_node(value));
    while (!is_stack_empty(c)) {
        x = pop(c);
        x->height = max(avl_tree_node_height(x->left), avl_tree_node_height(x->right)) + 1;
        if (abs(avl_tree_node_height(x->left) - avl_tree_node_height(x->right)) == 2) {
            if (dir1 == LEFT) {
                if (dir2 == LEFT) {
                    t = rotate_left(x);
                } else {
                    t = double_rotate_left(x);
                }
            } else {
                if (dir2 == LEFT) {
                    t = double_rotate_right(x);
                } else {
                    t = rotate_right(x);
                }
            }
            y = pop(c);
            insert_avl_child(tree, y, t);
            break;
        }
    }
    free_stack(c, NULL);
}

void insert_avl_child(Avl_tree_ptr tree, Avl_tree_node_ptr parent, Avl_tree_node_ptr child) {
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
