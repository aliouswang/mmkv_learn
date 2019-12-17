//
// Created by aliouswang on 2019-12-17.
//

#ifndef MMKV_LEARN_MMBUFFER_H
#define MMKV_LEARN_MMBUFFER_H

#include <cstdint>

enum MMBufferCopyFlag : bool {
    MMBufferCopy = false,
    MMBufferNoCopy = true,
};

class MMBuffer {
private:
    void *ptr;
    size_t size;
    MMBufferCopyFlag  isNoCopy;

public:
    void *getPtr() const {
        return ptr;
    }

    size_t length() const {
        return size;
    }

    explicit MMBuffer(size_t length = 0);

    MMBuffer(void *source, size_t length, MMBufferCopyFlag nocopy = MMBufferCopy);

    MMBuffer(MMBuffer &&other) noexcept;
    MMBuffer &operator=(MMBuffer &&other) noexcept;

    ~MMBuffer();

private:
    // those are expensive, just forbid it for possibly misuse
    MMBuffer(const MMBuffer &other) = delete;
};


#endif //MMKV_LEARN_MMBUFFER_H
