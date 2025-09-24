//
// Created by anschek on 24.09.2025.
//

#include "../include/memory_pool.h"
MemoryPool* init_pool(size_t total_bytes, size_t block_size) {
    __int8* pool = new __int8[total_bytes];
    size_t num_blocks = total_bytes / block_size;
    bool* used = new bool[num_blocks]{}; // по умолчанию везде false (0)

    return new MemoryPool(pool, total_bytes, block_size, num_blocks, used);
}

// Возвращает указатель на первый свободный блок
void* allocate(MemoryPool* pool) {
    for (size_t i = 0; i < pool->num_blocks; ++i)
        if (!pool->used[i]) {
            pool->used[i] = true;
            return pool->memory + i * pool->block_size;
        }
    return nullptr;
}