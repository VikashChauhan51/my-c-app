#include "vector.h" // Include your library's header
#include <stdio.h>  // For perror, fprintf
#include <stdlib.h> // For malloc, realloc, free
#include <string.h> // For memcpy


// Private helper function (static means it's only visible within this file)
static int vector_resize(Vector* vec, size_t new_capacity) {
    if (new_capacity < vec->size) { // Should not happen with typical doubling strategy
        fprintf(stderr, "Warning: Resizing to a capacity smaller than current size.\n");
    }
    void** new_data = (void**)realloc(vec->data, new_capacity * sizeof(void*));
    if (new_data == NULL) {
        perror("vector_resize: Failed to reallocate vector data");
        return -1; // Indicate failure
    }
    vec->data = new_data;
    vec->capacity = new_capacity;
    return 0; // Indicate success
}

Vector* vector_create(size_t initial_capacity, size_t element_size){
    if(initial_capacity==0 || element_size==0){
         fprintf(stderr, "vector::vector_create: Initial capacity and element size must be greater than 0.\n");
        return NULL;
    }
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if(vec == NULL){
        perror("vector::vector_create: Failed to allocate memory for Vector structure.");
        return NULL;
    }
    vec->data = (void**)malloc(initial_capacity * sizeof(void*));
    if(vec->data == NULL){
        perror("vector::vector_create: Failed to allocate memory for Vector data array.");
        free(vec);
        return NULL;
    }
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->element_size = element_size;
    return vec;
}

int vector_add(Vector* vec, const void* element){
    if (vec == NULL || element == NULL) {
        fprintf(stderr, "vector::vector_add: Vector or element is NULL.\n");
        return -1; // Indicate failure
    }
    if (vec->size >= vec->capacity) {
        // Double the capacity if we are out of space
        size_t new_capacity = vec->capacity * 2;
        if (vector_resize(vec, new_capacity) != 0) {
            return -1; // Indicate failure
        }
    }
    // Allocate memory for the new element
    void* new_element = malloc(vec->element_size);
    if (new_element == NULL) {
        perror("vector::vector_add: Failed to allocate memory for new element.");
        return -1; // Indicate failure
    }
    // Copy the element data into the new element
    memcpy(new_element, element, vec->element_size);
    // Add the new element to the vector
    vec->data[vec->size] = new_element;
    vec->size++;
    return 0; // Indicate success
    
}

void* vector_get(const Vector* vec, int index){
    if (vec == NULL || index < 0 || index >= vec->size) {
        fprintf(stderr, "vector::vector_get: Invalid vector or index out of bounds.\n");
        return NULL; // Indicate failure
    }
    return vec->data[index]; // Return the element at the specified index
}
int vector_set(Vector* vec, int index, const void* element){
    if (vec == NULL || element == NULL || index < 0 || index >= vec->size) {
        fprintf(stderr, "vector::vector_set: Invalid vector, element, or index out of bounds.\n");
        return -1; // Indicate failure
    }
    // Allocate memory for the new element
    void* new_element = malloc(vec->element_size);
    if (new_element == NULL) {
        perror("vector::vector_set: Failed to allocate memory for new element.");
        return -1; // Indicate failure
    }
    // Copy the element data into the new element
    memcpy(new_element, element, vec->element_size);
    // Free the old element and replace it with the new one
    free(vec->data[index]);
    vec->data[index] = NULL; // Set to NULL to avoid dangling pointer
    // Assign the new element to the vector at the specified index
    vec->data[index] = new_element;
    return 0; // Indicate success
}

int vector_remove(Vector* vec, int index) {
    if (vec == NULL || index < 0 || index >= vec->size) {
        fprintf(stderr, "vector::vector_remove: Invalid vector or index out of bounds.\n");
        return -1; // Indicate failure
    }
    // Free the memory for the element being removed
    free(vec->data[index]);
    vec->data[index] = NULL; // Set to NULL to avoid dangling pointer
    // Shift elements to fill the gap
    for (size_t i = index; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->data[vec->size - 1] = NULL; // Clear the last element
    vec->size--; // Decrease the size of the vector
    return 0; // Indicate success
}
size_t vector_size(const Vector* vec) {
    if (vec == NULL) {
        fprintf(stderr, "vector::vector_size: Invalid vector.\n");
        return 0; // Indicate failure
    }
    return vec->size; // Return the current size of the vector
}
void vector_destroy(Vector* vec){
    if (vec == NULL) {
        fprintf(stderr, "vector::vector_destroy: Invalid vector.\n");
        return; // Nothing to destroy
    }
    // Free each element in the vector
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->data[i]);
        vec->data[i] = NULL; // Set to NULL to avoid dangling pointers
    }
    // Free the data array and the vector structure itself
    free(vec->data);
    vec->data = NULL; // Set to NULL to avoid dangling pointer
    vec->size = 0; // Reset size    
    free(vec);
    vec = NULL; // Set to NULL to avoid dangling pointer
    fprintf(stderr, "vector::vector_destroy: Vector destroyed successfully.\n");
}