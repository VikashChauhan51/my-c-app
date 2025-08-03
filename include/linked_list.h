// list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h> // For NULL and size_t

// 1. Structure for a single node in the linked list
typedef struct Node {
    int data;          // Data stored in the node (can be any type, e.g., void* for generic list)
    struct Node *next; // Pointer to the next node in the list
} Node;

// 2. Structure for the linked list itself (head and size)
typedef struct LinkedList {
    Node *head;        // Pointer to the first node in the list
    size_t size;       // Current number of elements in the list
} LinkedList;

// --- Function Prototypes (Declarations) ---

/**
 * @brief Initializes a new empty linked list.
 * @return A pointer to the newly created LinkedList.
 */
LinkedList* createList();

/**
 * @brief Checks if the linked list is empty.
 * @param list A pointer to the LinkedList.
 * @return 1 if empty, 0 otherwise.
 */
int isEmpty(LinkedList *list);

/**
 * @brief Inserts a new node at the beginning of the list.
 * @param list A pointer to the LinkedList.
 * @param data The data to be stored in the new node.
 */
void insertAtBeginning(LinkedList *list, int data);

/**
 * @brief Inserts a new node at the end of the list.
 * @param list A pointer to the LinkedList.
 * @param data The data to be stored in the new node.
 */
void insertAtEnd(LinkedList *list, int data);

/**
 * @brief Inserts a new node after a specified value in the list.
 * @param list A pointer to the LinkedList.
 * @param data The data to be stored in the new node.
 * @param after_value The value after which to insert the new node.
 * @return 1 if insertion was successful, 0 if after_value was not found.
 */
int insertAfter(LinkedList *list, int data, int after_value);

/**
 * @brief Deletes the first occurrence of a node with the specified data.
 * @param list A pointer to the LinkedList.
 * @param data The data of the node to be deleted.
 * @return 1 if deletion was successful, 0 if data was not found.
 */
int deleteNode(LinkedList *list, int data);

/**
 * @brief Deletes the node at a specific position (0-indexed).
 * @param list A pointer to the LinkedList.
 * @param position The position of the node to delete.
 * @return The data of the deleted node if successful, or a special value (e.g., -1, or handle error) if position is invalid.
 */
int deleteAtPosition(LinkedList *list, int position);


/**
 * @brief Searches for a specific value in the list.
 * @param list A pointer to the LinkedList.
 * @param data The data to search for.
 * @return A pointer to the Node containing the data, or NULL if not found.
 */
Node* searchList(LinkedList *list, int data);

/**
 * @brief Prints all elements in the linked list.
 * @param list A pointer to the LinkedList.
 */
void printList(LinkedList *list);

/**
 * @brief Returns the current number of elements in the list.
 * @param list A pointer to the LinkedList.
 * @return The size of the list.
 */
size_t getListSize(LinkedList *list);

/**
 * @brief Deallocates all memory used by the linked list.
 * @param list A pointer to the LinkedList (will be set to NULL after destruction).
 */
void destroyList(LinkedList *list);

#endif // LINKED_LIST_H