//
// Created by anschek on 24.09.2025.
//

#include "../include/memory_pool.h"

#include <stdexcept> // std::out_of_range

MemoryPool *init_pool(size_t total_bytes, size_t block_size) {
    char *pool = new char[total_bytes];
    size_t num_blocks = total_bytes / block_size;
    bool *used = new bool[num_blocks]{}; // по умолчанию везде false (0)

    return new MemoryPool(pool, total_bytes, block_size, num_blocks, used);
}

// Возвращает указатель на первый свободный блок
void *allocate(MemoryPool *pool) {
    if (!pool) return nullptr;
    for (size_t i = 0; i < pool->num_blocks; ++i)
        if (!pool->used[i]) {
            pool->used[i] = true;
            return pool->memory + i * pool->block_size;
        }
    return nullptr;
}

// Освобождает блок по указателю
void deallocate(MemoryPool *pool, void *ptr) {
    if (!pool) return;

    // проверка выхода за границы выделенной памяти
    if (ptr < pool->memory || ptr >= pool->memory + pool->total_size) {
        throw std::out_of_range("pool pointer out of range");
    }

    std::ptrdiff_t offset = static_cast<char*>(ptr) - pool->memory;
    // проверка выравнивания: если остаток не равен 0, блок неровный
    if (offset % pool->block_size) {
        throw std::out_of_range("pointer offset does not correlate with memory block");
    }

    size_t index = offset/ pool->block_size;
    // проверка занятости: не повторный delete
    if (!pool->used[index]) {
        throw std::out_of_range("memory block is free");
    }

    pool->used[index] = false;
}

void reset_pool(MemoryPool *pool) {
    if (!pool) return;

    for (size_t i = 0; i < pool->num_blocks; ++i)
        pool->used[i] = false;
}

void destroy_pool(MemoryPool*& pool) {
    if (!pool) return;

    delete[] pool->memory;
    delete[] pool->used;
    delete pool;
    pool = nullptr;
}