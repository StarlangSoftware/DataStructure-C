//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include "LinkedList.h"
#include "../Memory/Memory.h"

/**
 * Constructor of the linked list. Allocates an empty linked list.
 * @param compare Comparator function to compare the contents of the nodes in the linked list.
 * @return Empty linked list.
 */
Linked_list_ptr create_linked_list(int (*compare)(const void *, const void *)) {
    Linked_list_ptr result = malloc_(sizeof(Linked_list));
    result->head = NULL;
    result->tail = NULL;
    result->compare = compare;
    return result;
}

/**
 * Removes and deallocates a node from linked list .
 * @param linked_list Linked list
 * @param node Node to be deleted
 * @param free_method Destructor method for the contents of the node
 */
void remove_node(Linked_list_ptr linked_list, Node_ptr node, void free_method(void *)) {
    Node_ptr next = node->next;
    Node_ptr previous = node->previous;
    if (previous != NULL) {
        previous->next = next;
    } else {
        linked_list->head = linked_list->head->next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        linked_list->tail = linked_list->tail->previous;
    }
    free_node(node, free_method);
}

/**
 * Inserts a new as the first (head) node in the linked list.
 * @param linked_list Linked list
 * @param node New first (head) node
 */
void add_first(Linked_list_ptr linked_list, Node_ptr node) {
    node->previous = NULL;
    node->next = linked_list->head;
    if (linked_list->head != NULL) {
        linked_list->head->previous = node;
    } else {
        linked_list->tail = node;
    }
    linked_list->head = node;
}

/**
 * Removes and returns the first (head) node from the linked list.
 * @param linked_list Linked list
 * @return The head node.
 */
void* remove_first(Linked_list_ptr linked_list) {
    void* data = NULL;
    Node_ptr removed = remove_first_node(linked_list);
    if (removed != NULL) {
        data = removed->data;
        free_(removed);
    }
    return data;
}

/**
 * Removes and returns the first (head) node from the linked list.
 * @param linked_list Linked list
 * @return The head node.
 */
Node_ptr remove_first_node(Linked_list_ptr linked_list) {
    if (is_linked_list_empty(linked_list)) {
        return NULL;
    }
    Node_ptr removed = linked_list->head;
    linked_list->head = linked_list->head->next;
    if (linked_list->head == NULL) {
        linked_list->tail = NULL;
    } else {
        linked_list->head->previous = NULL;
    }
    return removed;
}

void* remove_last(Linked_list_ptr linked_list) {
    void* data = NULL;
    Node_ptr removed = remove_last_node(linked_list);
    if (removed != NULL) {
        data = removed->data;
        free_(removed);
    }
    return data;
}
/**
 * Removes and returns the last (tail) node from the linked list.
 * @param linked_list Linked list
 * @return The tail node.
 */
Node_ptr remove_last_node(Linked_list_ptr linked_list) {
    if (is_linked_list_empty(linked_list)) {
        return NULL;
    }
    Node_ptr removed = linked_list->tail;
    linked_list->tail = linked_list->tail->previous;
    if (linked_list->tail == NULL) {
        linked_list->head = NULL;
    } else {
        linked_list->tail->next = NULL;
    }
    return removed;
}

/**
 * Destructor method for the linked list. Deallocates memory allocated for the linked list and its nodes including
 * the contents of the node.
 * @param linked_list Linked list
 * @param free_method Destructor method for the contents of the node
 */
void free_linked_list(Linked_list_ptr linked_list, void free_method(void *)) {
    while (linked_list->head != NULL) {
        Node_ptr removed = linked_list->head;
        linked_list->head = linked_list->head->next;
        free_node(removed, free_method);
    }
    free_(linked_list);
}

/**
 * Checks if the linked list is empty or not.
 * @param linked_list Linked list
 * @return True if the linked list is empty, false otherwise.
 */
bool is_linked_list_empty(const Linked_list* linked_list) {
    return linked_list->head == NULL;
}

/**
 * Inserts a new as the last (tail) node in the linked list.
 * @param linked_list Linked list
 * @param node New last (tail) node
 */
void add_last(Linked_list_ptr linked_list, Node_ptr node) {
    node->previous = linked_list->tail;
    node->next = NULL;
    if (linked_list->tail != NULL) {
        linked_list->tail->next = node;
    } else {
        linked_list->head = node;
    }
    linked_list->tail = node;
}

/**
 * Checks if the linked list contains a specific item. Comparison will be done using the compare method set in the
 * linked list construction.
 * @param linked_list Linked list
 * @param item Item to be searched
 * @return True if the linked list contains the item, false otherwise.
 */
bool linked_list_contains(const Linked_list* linked_list, const void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        if (linked_list->compare(iterator->data, item) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

/**
 * Checks if the linked list contains a specific item. Comparison will be done using the compare method set in the
 * linked list construction.
 * @param linked_list Linked list
 * @param item Item to be searched
 * @return The node containing the item if the linked list contains the item, NULL otherwise.
 */
Node_ptr linked_list_get(const Linked_list* linked_list, const void *item) {
    Node_ptr iterator = linked_list->head;
    while (iterator != NULL) {
        if (linked_list->compare(iterator->data, item) == 0) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void merge_linked_list(Linked_list_ptr first_list, Linked_list_ptr second_list) {
    if (first_list->tail != NULL) {
        first_list->tail->next = second_list->head;
    } else {
        first_list->head = second_list->head;
    }
    first_list->tail = second_list->tail;
}

/**
 * Checks an item if the linked list contains a specific item, and removes if it exists. Comparison will be done using
 * the compare method set in the linked list construction.
 * @param linked_list Linked list
 * @param data Item to be searched
 */
void remove_data(Linked_list_ptr linked_list, const void *data) {
    Node_ptr node = linked_list_get(linked_list, data);
    if (node != NULL) {
        remove_node(linked_list, node, NULL);
    }
}
