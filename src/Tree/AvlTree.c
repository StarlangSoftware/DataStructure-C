//
// Created by Olcay Taner YILDIZ on 22.01.2023.
//

#include <stdlib.h>
#include "AvlTree.h"
#include "../Stack.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the Avl tree. According to the comparator, the Avl tree could contain any object.
 * @param compare Comparator function to compare two elements.
 * @return Empty tree.
 */
Avl_tree_ptr create_avl_tree(int (*compare)(const void *, const void *)) {
    Avl_tree_ptr result = malloc_(sizeof(Avl_tree), "create_avl_tree");
    result->root = NULL;
    result->compare = compare;
    return result;
}

/**
 * Destructor method for the Avl tree. Deallocates memory allocated for the Avl tree and its node
 * contents
 * @param tree Avl tree
 * @param free_method Destructor method for the value in the tree node.
 */
void free_avl_tree(Avl_tree_ptr tree, void (*free_method)(void *)) {
    if (tree->root != NULL) {
        free_avl_tree_node(tree->root, free_method);
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
 * @param tree Avl tree
 * @param value Searched value
 * @return If the value exists in the tree, the function returns the node that contains the node. Otherwise, it
 * returns null.
 */
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

/**
 * In rotate left, we move node k1 one level up, since due to the binary search tree
 * property k2 > k1, we move node k2 one level down. The links updated are:
 * <ul>
 *     <li>Since k2 > B > k1, the left child of node k2 is now the old right child of k1</li>
 *     <li>The right child of k1 is now k2 </li>
 * </ul>
 * Note that, the root node of the subtree is now k1. In order to modify the parent link of k2, the new root of the
 * subtree is returned by the function.
 * @param k2 Root of the subtree, which does not satisfy the AVL tree property.
 * @return The new root of the subtree
 */
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

/**
 * In order to restore the AVL tree property, we move node k2 one level up, since due to the binary search tree
 * property k2 > k1, we move node k1 one level down. The links updated are:
 * <ul>
 *     <li>Since k2 > B > k1, the right child of node k1 is now the old left child of k2.</li>
 *     <li>The left child of k2 is now k1</li>
 * </ul>
 * Note that, the root node of the subtree is now k2. In order to modify the parent link of k1, the new root of the
 * subtree is returned by the function.
 * @param k1 Root of the subtree, which does not satisfy the AVL tree property.
 * @return The new root of the subtree
 */
Avl_tree_node_ptr rotate_right(Avl_tree_node_ptr k1) {
    Avl_tree_node_ptr k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->height = max((k2->left)->height, avl_tree_node_height(k2->right)) + 1;
    k1->height = max(avl_tree_node_height(k1->left), avl_tree_node_height(k1->right)) + 1;
    return k2;
}

/**
 * <p>In the first phase we will do single right rotation on the subtree rooted with k1. With this rotation, the left
 * child of node k2 will be k1, whereas the right child of node k1 will be B (the old left child of node k2).</p>
 *
 * <p>In the second phase, we will do single left rotation on the subtree rooted with k3. With this rotation, the
 * right child of node k2 will be k3, whereas the left child of node k3 will be C (the old right child of k2).</p>
 *
 * Note that, the new root node of the subtree is now k2. In order to modify the parent link of k3, the new root of
 * the subtree is returned by the function.
 * @param k3 Root of the subtree, which does not satisfy the AVL tree property.
 * @return The new root of the subtree
 */
Avl_tree_node_ptr double_rotate_left(Avl_tree_node_ptr k3) {
    k3->left = rotate_right(k3->left);
    return rotate_left(k3);
}

/**
 * <p>In the first phase we will do single right rotation on the subtree rooted with k3. With this rotation, the right
 * child of node k2 will be k3, whereas the left child of node k3 will be C (the old right child of node k2).</p>
 *
 * <p>In the second phase, we will do single right rotation on the subtree rooted with k1. With this rotation, the left
 * child of node k2 will be k1, whereas the left child of node k1 will be B (the old left child of k2).</p>
 *
 * Note that, the new root node of the subtree is now k2. In order to modify the parent link of k1, the new root of
 * the subtree is returned by the function.
 * @param k1 Root of the subtree, which does not satisfy the AVL tree property.
 * @return The new root of the subtree
 */
Avl_tree_node_ptr double_rotate_right(Avl_tree_node_ptr k1) {
    k1->right = rotate_left(k1->right);
    return rotate_right(k1);
}

/**
 * <p>First we will proceed with the stages the same when we add a new node into a binary search tree. For this, we
 * start from the root node and traverse in down manner. The current node we visit is represented with x and the
 * previous node is represented with y. At each time we compare the value of the current node with the value of the
 * new node. If the value of the new node is smaller than the value of the current node, the new node will be
 * inserted into the left subtree of the current node. For this, we will continue with the left child to process. If
 * the reverse is true, that is, if the value of the new node is larger than the value of the current node, the new
 * node will be inserted into the right subtree of the current node. In this case, we will continue with the right
 * child to process. At each step, we store the current node in a separate stack.</p>
 *
 * <p>When we insert a new node into an AVL tree, we need to change the heights of the nodes and check if the AVL tree
 * property is satisfied or not. Only the height of the nodes, which we visit while we are finding the place for the
 * new node, can be changed. So, what we should do is to pop those nodes from the stack one by one and change the
 * heights of those nodes.</p>
 *
 * <p>Similarly, the nodes, which we visit while we are finding the place for the new node, may no longer satisfy the
 * AVL tree property. So what we should do is to pop those nodes from the stack one by one and calculate the
 * difference of the heights of their left and right subtrees. If the height difference is 2, the AVL tree property
 * is not satisfied. If we added the new node into the left subtree of the left child, we need to do left single
 * rotation, if we added into the right subtree of the left child, we need to do left double rotation, if we added
 * into the left subtree of the right child, we need to do right double rotation, if we added into the right subtree
 * of the right child, we need to the right single rotation. Since  the root node of the subtree will be changed
 * after a rotation, the new child of y will be the new root node t.</p>
 * @param tree Avl tree
 * @param value Value to be inserted.
 */
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

/**
 * Inserts a child to its parent as left or right child.
 * @param tree Avl tree
 * @param parent New parent of the child node.
 * @param child Child node.
 */
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
