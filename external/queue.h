
#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include "../include/cube.h"

#define MAX_SIZE 1082565 * 2

/*
 * Queue Struct used for BFS.
 * - Represented as an array of rubix_cube_t structures.
 * - Tracks the front (head) and back (tail) indices.
 */
typedef struct Queue {
  int32_t values[MAX_SIZE];
  int head;
  int tail;
} queue_t;

/*
 * Initialize a Queue:
 *  - Set head and tail to 0.
 */
void initQueue(queue_t *queue);

/*
 * Check if the queue is empty.
 * - Returns true if empty, false otherwise.
 */
bool isEmpty(queue_t *queue);

/*
 * Check if the queue is full.
 * - Returns true if full, false otherwise.
 */
bool isFull(queue_t *queue);

/*
 * Add an item to the back of the queue.
 */
void enqueue(queue_t *queue, int32_t value);

/*
 * Remove an item from the front of the queue.
 */
int32_t dequeue(queue_t *queue);

/*
 * Return the first item in the queue without removing it.
 */
int32_t peek(queue_t *queue);

#endif
