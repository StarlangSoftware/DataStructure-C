//
// Created by Olcay Taner YILDIZ on 23.01.2023.
//

#include "BTreeNode.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the B+ Tree node. By default, it is a leaf node. Initializes the attributes.
 * @param d d in d-ary tree.
 */
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

/**
 * Another constructor of a B+ Tree node. By default, it is not a leaf node. Adds two children.
 * @param d d in d-ary tree.
 * @param first_Child First child of the root node.
 * @param second_child Second child of the root node.
 * @param newK First value in the node.
 */
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

/**
 * Searches the position of value in the list K. If the searched value is larger than the last value of node, we
 * need to continue the search with the rightmost child. If the searched value is smaller than the i. value of node,
 * we need to continue the search with the i. child.
 * @param btree_node Tree node
 * @param value Searched value
 * @param compare Comparator function which compares two elements.
 * @return The position of searched value in array K.
 */
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

/**
 * Add the new value insertedK to the array K into the calculated position index.
 * @param btree_node Tree node
 * @param index Place to insert new value
 * @param inserted_K New value to be inserted.
 */
void insert_into_K(BTree_node_ptr btree_node, int index, void *inserted_K) {
    for (int i = btree_node->m; i > index; i--) {
        btree_node->K[i] = btree_node->K[i - 1];
    }
    btree_node->K[index] = inserted_K;
}

/**
 * Transfers the last d values of the current node to the newNode.
 * @param btree_node Tree node
 * @param new_node New node.
 */
void move_half_of_the_K_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    for (int i = 0; i < btree_node->d; i++) {
        new_node->K[i] = btree_node->K[i + btree_node->d + 1];
    }
    new_node->m = btree_node->d;
}

/**
 * Transfers the last d links of the current node to the newNode.
 * @param btree_node Tree node
 * @param new_node New node.
 */
void move_half_of_the_children_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    for (int i = 0; i < btree_node->d; i++) {
        new_node->children[i] = btree_node->children[i + btree_node->d + 1];
        btree_node->children[i + btree_node->d + 1] = NULL;
    }
}

/**
 * Transfers the last d values and the last d links of the current node to the newNode.
 * @param btree_node Tree node
 * @param new_node New node.
 */
void move_half_of_the_elements_to_new_node(BTree_node_ptr btree_node, BTree_node_ptr new_node) {
    move_half_of_the_K_to_new_node(btree_node, new_node);
    move_half_of_the_children_to_new_node(btree_node, new_node);
}

/**
 * First the function position is used to determine the node or the subtree to which the new node will be added.
 * If this subtree is a leaf node, we call the function insertLeaf that will add the value to a leaf node. If this
 * subtree is not a leaf node the function calls itself with the determined subtree. Both insertNode and insertLeaf
 * functions, if adding a new value/node to that node/subtree necessitates a new child node to be added to the
 * parent node, they will both return the new added node and the node obtained by dividing the original node. If
 * there is not such a restructuring, these functions will return null. If we add a new child node to the parent
 * node, first we open a space for that child node in the value array K, then we add this new node to the array K.
 * After adding there are two possibilities:
 * <ul>
 *     <li>After inserting the new child node, the current node did not exceed its capacity. In this case, we open
 *     space for the link, which points to the new node, in the array children and place that link inside of this
 *     array.</li>
 *     <li>After inserting the new child node, the current node exceed its capacity. In this case, we need to create
 *     newNode, transfer the last d values and the last d links of the current node to the newNode. As a last case,
 *     if the divided node is the root node, we need to create a new root node and the first child of this new root
 *     node will be b, and the second child of the new root node will be newNode.</li>
 * </ul>
 * @param btree_node Tree node
 * @param value Value to be inserted into B+ tree.
 * @param compare Comparator function to compare two elements.
 * @param is_root If true, value is inserted as a root node, otherwise false.
 * @return If inserted node results in a creation of a node, the function returns that node, otherwise null.
 */
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

/**
 * First the function position is used to determine the position where the new value will be placed Then we open a
 * space for that value in the value array K, then we add this new value to the array K into the calculated
 * position. At this stage there are again two possibilities:
 * <ul>
 *     <li>After inserting the new value, the current leaf node did not exceed its capacity. The function returns
 *     null.</li>
 *     <li>After inserting the new value, the current leaf node exceed its capacity. In this case, we need to create
 *     the newNode, and transfer the last d values of node b to this newNode.</li>
 * </ul>
 * @param btree_node Tree node
 * @param value Value to be inserted into B+ tree.
 * @param compare Comparator function to compare two elements.
 * @return If inserted node results in a creation of a node, the function returns that node, otherwise null.
 */
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
