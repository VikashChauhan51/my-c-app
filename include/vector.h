#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h> // For size_t

// Public structure definition for the Vector
typedef struct {
    void** data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

// Public function prototypes (the API that users will call)
Vector* vector_create(size_t initial_capacity, size_t element_size);
int vector_add(Vector* vec, const void* element);
void* vector_get(const Vector* vec, int index);
int vector_set(Vector* vec, int index, const void* element);
int vector_remove(Vector* vec, int index);
size_t vector_size(const Vector* vec);
void vector_destroy(Vector* vec);

#endif // MY_VECTOR_H
