/* 힙 정렬 — 최대 힙(Max Heap)을 구성하여 최댓값을 뒤로 보내며 정렬한다. */
#include "sort.h"
#include "sortctx.h"

static void heapify(SortCtx *c, size_t n, size_t i, size_t depth) {
    if (c->stats != NULL && depth > c->stats->maxDepth) {
        c->stats->maxDepth = depth;
    }

    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && sortCompareAt(c, left, largest) > 0) {
        largest = left;
    }
    if (right < n && sortCompareAt(c, right, largest) > 0) {
        largest = right;
    }
    if (largest != i) {
        sortSwap(c, i, largest);
        heapify(c, n, largest, depth + 1);
    }
}

void heapSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats) {
    SortCtx c;
    if (!sortBegin(&c, base, n, size, cmp, stats)) {
        return;
    }

    /* 1. 최대 힙(Max Heap) 구성 */
    for (size_t i = n / 2; i > 0; i--) {
        heapify(&c, n, i - 1, 1);
    }

    /* 2. 최댓값(루트 0번)을 뒤로 보내고 힙 크기를 줄여가며 재정렬 */
    for (size_t i = n - 1; i > 0; i--) {
        sortSwap(&c, 0, i);
        heapify(&c, i, 0, 1);
    }

    sortEnd(&c);
}
