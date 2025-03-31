#include <assert.h>
#include <stdio.h>
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

void enqueue(queue_t *q, rubix_cube_t cube) {
    assert(!(isFull(q)));

    q->tail++;

    q->values[q->tail] = cube;
}

rubix_cube_t dequeue(queue_t *q) {
    assert(!(isEmpty(q)));

    q->head++;

    return q->values[q->head - 1];
}

rubix_cube_t peek(queue_t *q) {
    assert(!(isEmpty(q)));

    return q->values[q->head];
}
