/*****************************************************************************
*                                                                            *
*  -------------------------------- bfs.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "queue.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- bfs ----------------------------------  *
*                                                                            *
*****************************************************************************/

int bfs(Graph *graph, BfsVertex *start, List *hops) {

Queue              queue;

AdjList            *adjlist,
                   *clr_adjlist;

BfsVertex          *clr_vertex,
                   *adj_vertex;

ListElmt           *element,
                   *member;

/*****************************************************************************
*                                                                            *
*  Initialize all of the vertices in the graph.                              *
*                                                                            *
*****************************************************************************/

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   clr_vertex = ((AdjList *)list_data(element))->vertex;

   if (graph->match(clr_vertex, start)) {

      /***********************************************************************
      *                                                                      *
      *  Initialize the start vertex.                                        *
      *                                                                      *
      ***********************************************************************/

      clr_vertex->color = gray;
      clr_vertex->hops = 0;

      }

   else {

      /***********************************************************************
      *                                                                      *
      *  Initialize vertices other than the start vertex.                    *
      *                                                                      *
      ***********************************************************************/

      clr_vertex->color = white;
      clr_vertex->hops = -1;

   }

}

/*****************************************************************************
*                                                                            *
*  Initialize the queue with the adjacency list of the start vertex.         *
*                                                                            *
*****************************************************************************/

queue_init(&queue, NULL);

if (graph_adjlist(graph, start, &clr_adjlist) != 0) {

   queue_destroy(&queue);
   return -1;

}

if (queue_enqueue(&queue, clr_adjlist) != 0) {

   queue_destroy(&queue);
   return -1;

}

/*****************************************************************************
*                                                                            *
*  Perform breadth-first search.                                             *
*                                                                            *
*****************************************************************************/

while (queue_size(&queue) > 0) {

   adjlist = queue_peek(&queue);

   /**************************************************************************
   *                                                                         *
   *  Traverse each vertex in the current adjacency list.                    *
   *                                                                         *
   **************************************************************************/

   for (member = list_head(&adjlist->adjacent); member != NULL; member =
      list_next(member)) {

      adj_vertex = list_data(member);

      /***********************************************************************
      *                                                                      *
      *  Determine the color of the next adjacent vertex.                    *
      *                                                                      *
      ***********************************************************************/

      if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0) {

         queue_destroy(&queue);
         return -1;

      }

      clr_vertex = clr_adjlist->vertex;

      /***********************************************************************
      *                                                                      *
      *  Color each white vertex gray and enqueue its adjacency list.        *
      *                                                                      *
      ***********************************************************************/

      if (clr_vertex->color == white) {

         clr_vertex->color = gray;
         clr_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;

         if (queue_enqueue(&queue, clr_adjlist) != 0) {

            queue_destroy(&queue);
            return -1;

         }

      }

   }

   /**************************************************************************
   *                                                                         *
   *  Dequeue the current adjacency list and color its vertex black.         *
   *                                                                         *
   **************************************************************************/

   if (queue_dequeue(&queue, (void **)&adjlist) == 0) {

      ((BfsVertex *)adjlist->vertex)->color = black;

      }

   else {

      queue_destroy(&queue);
      return -1;

   }

}

queue_destroy(&queue);

/*****************************************************************************
*                                                                            *
*  Pass back the hop count for each vertex in a list.                        *
*                                                                            *
*****************************************************************************/

list_init(hops, NULL);

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   /**************************************************************************
   *                                                                         *
   *  Skip vertices that were not visited (those with hop counts of -1).     *
   *                                                                         *
   **************************************************************************/

   clr_vertex = ((AdjList *)list_data(element))->vertex;

   if (clr_vertex->hops != -1) {

      if (list_ins_next(hops, list_tail(hops), clr_vertex) != 0) {

         list_destroy(hops);
         return -1;

      }

   }

}

return 0;

}
