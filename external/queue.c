#include <assert.h>
#include "queue.h"

void initQueue(queue_t *q) {
    q->head = 0;
    q->tail = 0;
}

bool isEmpty(queue_t *q) { 
    return (q->head == q->tail);
}

bool isFull(queue_t *q) { 
    return (q->tail == MAX_SIZE);
}

void enqueue(queue_t *q, int32_t value) {
    assert(!(isFull(q)));

    q->tail++;

    q->values[q->tail] = value;
}

int32_t dequeue(queue_t *q) {
    assert(!(isEmpty(q)));

    q->head++;

    return q->values[q->head - 1];
}

int32_t peek(queue_t *q) {
    assert(!(isEmpty(q)));

    return q->values[q->head];
}
