// list.c
#include "linked_list.h" // Include our own header file
#include <stdio.h>  // For printf
#include <stdlib.h> // For malloc, free

// Helper function to create a new node
static Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE); // Or handle error gracefully
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

LinkedList* createList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        perror("Failed to allocate memory for LinkedList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int isEmpty(LinkedList *list) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in isEmpty.\n");
        return 1; // Treat as empty or error
    }
    return list->head == NULL; // Or list->size == 0;
}

void insertAtBeginning(LinkedList *list, int data) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in insertAtBeginning.\n");
        return;
    }
    Node *newNode = createNode(data);
    newNode->next = list->head; // New node points to old head
    list->head = newNode;       // List head now points to new node
    list->size++;
    printf("Inserted %d at beginning. Size: %zu\n", data, list->size);
}

void insertAtEnd(LinkedList *list, int data) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in insertAtEnd.\n");
        return;
    }
    Node *newNode = createNode(data);

    if (list->head == NULL) { // If list is empty, new node is the head
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) { // Traverse to the last node
            current = current->next;
        }
        current->next = newNode; // Last node points to the new node
    }
    list->size++;
    printf("Inserted %d at end. Size: %zu\n", data, list->size);
}

int insertAfter(LinkedList *list, int data, int after_value) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in insertAfter.\n");
        return 0;
    }
    Node *current = list->head;
    while (current != NULL && current->data != after_value) {
        current = current->next;
    }

    if (current == NULL) { // Value not found
        printf("Value %d not found. Cannot insert %d after it.\n", after_value, data);
        return 0;
    }

    // Value found, insert newNode after current
    Node *newNode = createNode(data);
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
    printf("Inserted %d after %d. Size: %zu\n", data, after_value, list->size);
    return 1;
}


int deleteNode(LinkedList *list, int data) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty or NULL. Cannot delete %d.\n", data);
        return 0; // List is empty
    }

    Node *current = list->head;
    Node *prev = NULL;

    // Case 1: Node to be deleted is the head
    if (current != NULL && current->data == data) {
        list->head = current->next; // Move head to next node
        free(current);             // Free the old head
        current = NULL;
        list->size--;
        printf("Deleted %d from list. Size: %zu\n", data, list->size);
        return 1;
    }

    // Case 2: Node to be deleted is elsewhere in the list
    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) { // Data not found
        printf("%d not found in list. No deletion.\n", data);
        return 0;
    }

    // Data found, bypass the current node
    prev->next = current->next;
    free(current); // Free the node
    current = NULL;
    list->size--;
    printf("Deleted %d from list. Size: %zu\n", data, list->size);
    return 1;
}

int deleteAtPosition(LinkedList *list, int position) {
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "Error: List is empty or NULL. Cannot delete from position %d.\n", position);
        return -1; // Indicate error
    }

    if (position < 0 || (size_t)position >= list->size) {
        fprintf(stderr, "Error: Invalid position %d for deletion (list size: %zu).\n", position, list->size);
        return -1; // Indicate error
    }

    Node *temp = list->head;
    int deleted_data;

    // If head needs to be removed
    if (position == 0) {
        list->head = temp->next;
        deleted_data = temp->data;
        free(temp);
        temp = NULL;
        list->size--;
        printf("Deleted %d at position %d. Size: %zu\n", deleted_data, position, list->size);
        return deleted_data;
    }

    // Find previous node of the node to be deleted
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL) {
        fprintf(stderr, "Error: Position %d out of bounds during traversal.\n", position);
        return -1; // Should not happen if previous checks are correct
    }

    Node *node_to_delete = temp->next; // Node at the given position
    deleted_data = node_to_delete->data;
    temp->next = node_to_delete->next; // Unlink the node
    free(node_to_delete);             // Free memory
    node_to_delete=NULL;
    list->size--;
    printf("Deleted %d at position %d. Size: %zu\n", deleted_data, position, list->size);
    return deleted_data;
}


Node* searchList(LinkedList *list, int data) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in searchList.\n");
        return NULL;
    }
    Node *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current; // Found the data
        }
        current = current->next;
    }
    return NULL; // Data not found
}

void printList(LinkedList *list) {
    if (list == NULL) {
        printf("List is NULL.\n");
        return;
    }
    if (isEmpty(list)) {
        printf("List is empty.\n");
        return;
    }
    Node *current = list->head;
    printf("List elements (%zu): ", list->size);
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

size_t getListSize(LinkedList *list) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in getListSize.\n");
        return 0;
    }
    return list->size;
}

void destroyList(LinkedList *list) {
    if (list == NULL) {
        return; // Nothing to destroy
    }
    Node *current = list->head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next; // Store next node before freeing current
        free(current);             // Free the current node
        current =NULL;
        current = next_node;       // Move to the next node
    }
    free(list); // Free the LinkedList structure itself
    list =NULL;
    printf("List destroyed and memory deallocated.\n");
}