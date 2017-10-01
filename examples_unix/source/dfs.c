/*****************************************************************************
*                                                                            *
*  -------------------------------- dfs.c ---------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "dfs.h"
#include "graph.h"
#include "list.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- dfs_main -------------------------------  *
*                                                                            *
*****************************************************************************/

static int dfs_main(Graph *graph, AdjList *adjlist, List *ordered) {

AdjList            *clr_adjlist;

DfsVertex          *clr_vertex,
                   *adj_vertex;

ListElmt           *member;

/*****************************************************************************
*                                                                            *
*  Color the vertex gray and traverse its adjacency list.                    *
*                                                                            *
*****************************************************************************/

((DfsVertex *)adjlist->vertex)->color = gray;

for (member = list_head(&adjlist->adjacent); member != NULL; member =
   list_next(member)) {

   /**************************************************************************
   *                                                                         *
   *  Determine the color of the next adjacent vertex.                       *
   *                                                                         *
   **************************************************************************/

   adj_vertex = list_data(member);

   if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0)
      return -1;

   clr_vertex = clr_adjlist->vertex;

   /**************************************************************************
   *                                                                         *
   *  Move one vertex deeper when the next adjacent vertex is white.         *
   *                                                                         *
   **************************************************************************/

   if (clr_vertex->color == white) {

      if (dfs_main(graph, clr_adjlist, ordered) != 0)
         return -1;

   }

}

/*****************************************************************************
*                                                                            *
*  Color the current vertex black and make it first in the list.             *
*                                                                            *
*****************************************************************************/

((DfsVertex *)adjlist->vertex)->color = black;

if (list_ins_next(ordered, NULL, (DfsVertex *)adjlist->vertex) != 0)
   return -1;

return 0;

}

/*****************************************************************************
*                                                                            *
*  ---------------------------------- dfs ---------------------------------  *
*                                                                            *
*****************************************************************************/

int dfs(Graph *graph, List *ordered) {

DfsVertex          *vertex;

ListElmt           *element;

/*****************************************************************************
*                                                                            *
*  Initialize all of the vertices in the graph.                              *
*                                                                            *
*****************************************************************************/

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   vertex = ((AdjList *)list_data(element))->vertex;
   vertex->color = white;

}

/*****************************************************************************
*                                                                            *
*  Perform depth-first search.                                               *
*                                                                            *
*****************************************************************************/

list_init(ordered, NULL);

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   /**************************************************************************
   *                                                                         *
   *  Ensure that every component of unconnected graphs is searched.         *
   *                                                                         *
   **************************************************************************/

   vertex = ((AdjList *)list_data(element))->vertex;

   if (vertex->color == white) {

      if (dfs_main(graph, (AdjList *)list_data(element), ordered) != 0) {

         list_destroy(ordered);
         return -1;

      }

   }

}

return 0;

}
