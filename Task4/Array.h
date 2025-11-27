#ifndef ARRAY_H
#define ARRAY_H

#include <cstdint>

struct Block {
    int width;
    int height;
};

struct IntArray {
    int* data = nullptr;
    size_t size = 0;
    uint64_t capacity = 0;
};

struct BlockArray {
    Block* data = nullptr;
    size_t size = 0;
    uint64_t capacity = 0;
};

void IntPush(IntArray& arr, int value);
int IntGet(const IntArray& arr, int index);
void IntClear(IntArray& arr);

void BlockPush(BlockArray& arr, const Block& block);
Block BlockGet(const BlockArray& arr, int index);
void BlockClear(BlockArray& arr);

#endif
