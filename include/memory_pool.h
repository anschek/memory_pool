//
// Created by anschek on 24.09.2025.
//

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include <iostream>
struct MemoryPool {
    __int8* memory;
    size_t total_size;
    size_t block_size;
    size_t num_blocks;
    bool* used; // массив флагов: занят ли блок
};

MemoryPool* init_pool(size_t total_bytes, size_t block_size);
void* allocate(MemoryPool* pool);
void deallocate(MemoryPool* pool, void* ptr);
void reset_pool(MemoryPool* pool);
void destroy_pool(MemoryPool* pool);
#endif //MEMORY_POOL_H