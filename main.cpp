#include <cstddef>
#include <cstdio>
#include <jemalloc/jemalloc.h>

size_t fittedSize(size_t allocSize, size_t alignment) noexcept
{
    return ::nallocx(allocSize, MALLOCX_ALIGN(alignment));
}

int main()
{
    const size_t desired = 1014 * 1024;
    const size_t alignment = alignof(std::max_align_t);
    const size_t fittedSize = ::fittedSize(desired, alignment);
    printf("Desired: %zu, Fitted: %zu, alignof(std::max_align_t): %zu ; morealign=%d\n", desired, fittedSize, alignof(std::max_align_t),  MALLOCX_ALIGN(alignment));
    void *ptr = malloc(fittedSize);

    ::sdallocx(ptr, fittedSize, 0);

    return 0;
}
