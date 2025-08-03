#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <stddef.h>

/**
 * @brief Structure for a node in the free list.
 *
 * This structure is used to link together the free chunks of memory
 * within the memory pool. The pointer is stored directly within the
 * memory block itself when it's free, thus using no extra memory.
 */
typedef struct FreeNode {
    struct FreeNode *next;
} FreeNode;

/**
 * @brief Structure for the memory pool.
 *
 * This holds the entire pre-allocated block of memory and a pointer
 * to the head of the free list.
 */
typedef struct MemPool {
    size_t total_size;
    size_t block_size;
    void *buffer;
    FreeNode *free_list_head;
} MemPool;

// --- Function Prototypes ---

/**
 * @brief Creates a new memory pool.
 *
 * Allocates a large buffer and initializes a free list.
 *
 * @param num_blocks The total number of memory blocks to pre-allocate.
 * @param block_size The size of each memory block in bytes.
 * @return A pointer to the initialized MemPool, or NULL on failure.
 */
MemPool* createPool(size_t num_blocks, size_t block_size);

/**
 * @brief Allocates a block of memory from the pool.
 *
 * This function is a fast alternative to malloc(). It simply pops a
 * node off the free list.
 *
 * @param pool A pointer to the memory pool.
 * @return A pointer to a free memory block, or NULL if the pool is exhausted.
 */
void* allocate(MemPool *pool);

/**
 * @brief Deallocates a block of memory and returns it to the pool.
 *
 * This function is a fast alternative to free(). It simply pushes the
 * deallocated block back onto the free list.
 *
 * @param pool A pointer to the memory pool.
 * @param ptr The pointer to the memory block to deallocate.
 */
void deallocate(MemPool *pool, void *ptr);

/**
 * @brief Destroys the memory pool and frees its main buffer.
 *
 * This function must be called to release all memory associated with the pool.
 *
 * @param pool A pointer to the memory pool to destroy.
 */
void destroyPool(MemPool *pool);

#endif // MEMPOOL_H