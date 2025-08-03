#include <stdio.h>
#include "vector.h" // Include your library's header

int main() {
    printf("--- C Vector Implementation Demo ---\n\n");

    // --- Demo with Integers ---
    printf("Demonstrating with Integers:\n");
    Vector* int_vec = vector_create(5, sizeof(int));
    if (int_vec == NULL) {
        printf("Failed to create integer vector.\n");
        return 1;
    }

    int nums[] = {10, 20, 30, 40, 50, 60}; // 6 elements, will trigger resize
    for (int i = 0; i < sizeof(nums)/sizeof(nums[0]); ++i) {
        if (vector_add(int_vec, &nums[i]) != 0) {
            printf("Failed to add %d to vector.\n", nums[i]);
        }
    }

    printf("Integer vector size: %zu, capacity: %zu\n", vector_size(int_vec), int_vec->capacity);
    printf("Elements: ");
    for (int i = 0; i < vector_size(int_vec); ++i) {
        int* val = (int*)vector_get(int_vec, i);
        if (val != NULL) {
            printf("%d ", *val);
        }
    }
    printf("\n");

    int new_val = 99;
    if (vector_set(int_vec, 2, &new_val) == 0) {
        printf("Set element at index 2 to %d.\n", new_val);
    }
    printf("Elements after set: ");
    for (int i = 0; i < vector_size(int_vec); ++i) {
        int* val = (int*)vector_get(int_vec, i);
        if (val != NULL) {
            printf("%d ", *val);
        }
    }
    printf("\n");

    if (vector_remove(int_vec, 1) == 0) {
        printf("Removed element at index 1.\n");
    }
     printf("Elements after remove: ");
    for (int i = 0; i < vector_size(int_vec); ++i) {
        int* val = (int*)vector_get(int_vec, i);
        if (val != NULL) {
            printf("%d ", *val);
        }
    }
    printf("\n");
    printf("Integer vector size: %zu, capacity: %zu\n", vector_size(int_vec), int_vec->capacity);


    vector_destroy(int_vec);
    printf("\nInteger vector destroyed.\n");

    // --- Demo with Strings (char arrays) ---
    printf("\nDemonstrating with Strings:\n");
    // Note: For strings, you generally pass pointers to char arrays.
    // The vector will copy the content.
    Vector* str_vec = vector_create(3, 20 * sizeof(char)); // Max 19 chars + null terminator
    if (str_vec == NULL) {
        printf("Failed to create string vector.\n");
        return 1;
    }

    char s1[] = "Apple";
    char s2[] = "Banana";
    char s3[] = "Cherry";
    char s4[] = "Date"; // Will trigger resize

    vector_add(str_vec, s1);
    vector_add(str_vec, s2);
    vector_add(str_vec, s3);
    vector_add(str_vec, s4);

    printf("String vector size: %zu, capacity: %zu\n", vector_size(str_vec), str_vec->capacity);
    printf("Elements: ");
    for (int i = 0; i < vector_size(str_vec); ++i) {
        char* str_val = (char*)vector_get(str_vec, i);
        if (str_val != NULL) {
            printf("'%s' ", str_val);
        }
    }
    printf("\n");

    char s_new[] = "Grape";
    if (vector_set(str_vec, 1, s_new) == 0) {
        printf("Set element at index 1 to '%s'.\n", s_new);
    }
    printf("Elements after set: ");
    for (int i = 0; i < vector_size(str_vec); ++i) {
        char* str_val = (char*)vector_get(str_vec, i);
        if (str_val != NULL) {
            printf("'%s' ", str_val);
        }
    }
    printf("\n");

    vector_destroy(str_vec);
    printf("\nString vector destroyed.\n");

    printf("\n--- Demo End ---\n");
    return 0;
}