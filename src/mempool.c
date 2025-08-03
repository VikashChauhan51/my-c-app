#include "mempool.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Aligns a memory address to the size of a pointer.
 *
 * This ensures that a FreeNode pointer can be safely stored in any
 * memory block, even if the user-requested block size is smaller
 * than a pointer.
 *
 * @param size The size to align.
 * @return The aligned size.
 */
static size_t align_size(size_t size) {
    size_t align = sizeof(void*);
    return (size + align - 1) & ~(align - 1);
}

MemPool* createPool(size_t num_blocks, size_t block_size) {
    // We need to ensure that each block is at least the size of a FreeNode
    // so we can store a pointer in it when it's free.
    size_t effective_block_size = block_size > sizeof(FreeNode) ? block_size : sizeof(FreeNode);
    effective_block_size = align_size(effective_block_size);

    MemPool *pool = (MemPool *)malloc(sizeof(MemPool));
    if (pool == NULL) {
        perror("Failed to allocate memory for MemPool structure");
        return NULL;
    }

    // Allocate a single contiguous buffer for all blocks
    pool->total_size = num_blocks * effective_block_size;
    pool->block_size = effective_block_size;
    pool->buffer = malloc(pool->total_size);
    if (pool->buffer == NULL) {
        perror("Failed to allocate memory for memory pool buffer");
        free(pool);
        pool = NULL;
        return NULL;
    }

    // Initialize the free list
    pool->free_list_head = NULL;
    for (size_t i = 0; i < num_blocks; ++i) {
        void *current_block = (char*)pool->buffer + (i * pool->block_size);
        deallocate(pool, current_block);
    }

    printf("Memory pool created with %zu blocks of size %zu (total size: %zu bytes)\n",
           num_blocks, effective_block_size, pool->total_size);

    return pool;
}

void* allocate(MemPool *pool) {
    if (pool == NULL || pool->free_list_head == NULL) {
        printf("Error: Pool is NULL or exhausted.\n");
        return NULL; // Pool is either not created or all blocks are in use
    }

    // Pop the head of the free list
    void *block = pool->free_list_head;
    pool->free_list_head = pool->free_list_head->next;

    return block;
}

void deallocate(MemPool *pool, void *ptr) {
    if (pool == NULL || ptr == NULL) {
        return; // No-op if pool or pointer is invalid
    }

    // Push the deallocated block to the head of the free list
    FreeNode *node = (FreeNode*)ptr;
    node->next = pool->free_list_head;
    pool->free_list_head = node;
}

void destroyPool(MemPool *pool) {
    if (pool == NULL) {
        return; // No-op
    }

    if (pool->buffer != NULL) {
        free(pool->buffer);
        pool->buffer = NULL;
    }

    if (pool->free_list_head != NULL) {
        free(pool->free_list_head);
        pool->free_list_head = NULL;
    }
    pool->total_size = 0;
    pool->block_size = 0;
    free(pool);
    pool = NULL;

    printf("Memory pool destroyed.\n");
}