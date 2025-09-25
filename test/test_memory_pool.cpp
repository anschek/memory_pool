//
// Created by anschek on 25.09.2025.
//

#include <cassert>

#include "../include/memory_pool.h"

void test_init(MemoryPool *&pool) {
    size_t total_bytes = 6, block_size = 2;
    pool = init_pool(total_bytes, block_size);
    std::cout << pool << std::endl;
    assert(pool != nullptr);
    assert(pool->total_size == total_bytes);
    assert(pool->block_size == block_size);

    for (size_t i = 0; i < pool->num_blocks; ++i)
        std::cout << pool->used[i] << ' ';
    std::cout << '\n' << __func__ << " passed\n";
}

void test_allocate(MemoryPool *pool) {
    void *memory1 = allocate(pool);
    assert(memory1 != nullptr);
    assert(pool->used[0]);
    for (size_t i = 1; i < pool->num_blocks; ++i)
        assert(!pool->used[i]);

    allocate(pool); // 2
    allocate(pool); // 3
    for (size_t i = 0; i < pool->num_blocks; ++i)
        assert(pool->used[i]);

    void *memory4 = allocate(pool);
    assert(memory4 == nullptr);

    std::cout << __func__ << " passed\n";
}

void test_deallocate(MemoryPool *pool) {
    // успешное освобождение блока памяти
    void *memory1 = pool->memory;
    deallocate(pool, memory1);
    assert(!pool->used[0]);

    // ошибка выхода за границы пула
    try {
        __int8 *memory4 = static_cast<__int8 *>(memory1) + 4*2;
        deallocate(pool, memory4);
        assert(false);
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }

    // ошибка выравнивания блока памяти
    try {
        __int8 *memory3 = static_cast<__int8 *>(memory1) + 3;
        deallocate(pool, memory3);
        assert(false);
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }

    // ошибка повторного освобождения
    try {
        deallocate(pool, memory1);
        assert(false);
    }catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }

    std::cout << __func__ << " passed\n";
}

void memory_pool_test_all() {
    MemoryPool *pool = nullptr;
    test_init(pool);
    test_allocate(pool);
    test_deallocate(pool);
    std::cout << "all tests passed\n";
}
