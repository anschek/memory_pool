//
// Created by anschek on 24.09.2025.
//

#include "../include/memory_pool.h"

MemoryPool *init_pool(size_t total_bytes, size_t block_size) {
    __int8 *pool = new __int8[total_bytes];
    size_t num_blocks = total_bytes / block_size;
    bool *used = new bool[num_blocks]{}; // по умолчанию везде false (0)

    return new MemoryPool(pool, total_bytes, block_size, num_blocks, used);
}

// Возвращает указатель на первый свободный блок
void *allocate(MemoryPool *pool) {
    for (size_t i = 0; i < pool->num_blocks; ++i)
        if (!pool->used[i]) {
            pool->used[i] = true;
            return pool->memory + i * pool->block_size;
        }
    return nullptr;
}

// Освобождает блок по указателю
void deallocate(MemoryPool *pool, void *ptr) {
    // проверка выхода за границы выделенной памяти
    if (ptr < pool->memory || ptr >= pool->memory + pool->total_size) {
        throw std::out_of_range("pool pointer out of range");
    }

    long long ptr_diff = static_cast<__int8*>(ptr) - pool->memory;
    // проверка выравнивания: если остаток не равен 0, блок неровный
    if (ptr_diff % pool->block_size) {
        throw std::out_of_range("pointer offset does not correlate with memory block");
    }

    size_t index = ptr_diff/ pool->block_size;
    // проверка занятости: не повторный delete
    if (!pool->used[index]) {
        throw std::out_of_range("memory block is free");
    }

    pool->used[index] = false;
}