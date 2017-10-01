/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a queue (see Chapter 6).                   *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_queue -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_queue(const Queue *queue) {

ListElmt           *element;

int                *data,
                   size,
                   i;

/*****************************************************************************
*                                                                            *
*  Display the queue.                                                        *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Queue size is %d\n", size = queue_size(queue));

i = 0;
element = list_head(queue);

while (i < size) {

   data = list_data(element);
   fprintf(stdout, "queue[%03d]=%03d\n", i, *data);
   element = list_next(element);
   i++;

}

return;

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

Queue              queue;

int                *data,
                   i;

/*****************************************************************************
*                                                                            *
*  Initialize the queue.                                                     *
*                                                                            *
*****************************************************************************/

queue_init(&queue, free);

/*****************************************************************************
*                                                                            *
*  Perform some queue operations.                                            *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Enqueuing 10 elements\n");

for (i = 0; i < 10; i++) {

   if ((data = (int *)malloc(sizeof(int))) == NULL)
      return 1;

   *data = i + 1;

   if (queue_enqueue(&queue, data) != 0)
      return 1;

}

print_queue(&queue);

fprintf(stdout, "Dequeuing 5 elements\n");

for (i = 0; i < 5; i++) {

   if (queue_dequeue(&queue, (void **)&data) == 0)
      free(data);
   else
      return 1;

}

print_queue(&queue);

fprintf(stdout, "Enqueuing 100 and 200\n");

if ((data = (int *)malloc(sizeof(int))) == NULL)
   return 1;

*data = 100;

if (queue_enqueue(&queue, data) != 0)
   return 1;

if ((data = (int *)malloc(sizeof(int))) == NULL)
   return 1;

*data = 200;

if (queue_enqueue(&queue, data) != 0)
   return 1;

print_queue(&queue);

if ((data = queue_peek(&queue)) != NULL)
   fprintf(stdout, "Peeking at the head element...Value=%03d\n", *data);
else
   fprintf(stdout, "Peeking at the head element...Value=NULL\n");

print_queue(&queue);

fprintf(stdout, "Dequeuing all elements\n");

while (queue_size(&queue) > 0) {

   if (queue_dequeue(&queue, (void **)&data) == 0)
      free(data);
   
}

if ((data = queue_peek(&queue)) != NULL)
   fprintf(stdout, "Peeking at an empty queue...Value=%03d\n", *data);
else
   fprintf(stdout, "Peeking at an empty queue...Value=NULL\n");

/*****************************************************************************
*                                                                            *
*  Destroy the queue.                                                        *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Destroying the queue\n");
queue_destroy(&queue);

return 0;

}
