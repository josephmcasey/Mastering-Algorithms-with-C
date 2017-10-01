/*****************************************************************************
*                                                                            *
*  ------------------------------ shortest.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include <float.h>
#include <stdlib.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- relax --------------------------------  *
*                                                                            *
*****************************************************************************/

static void relax(PathVertex *u, PathVertex *v, double weight) {

/*****************************************************************************
*                                                                            *
*  Relax an edge between two vertices u and v.                               *
*                                                                            *
*****************************************************************************/

if (v->d > u->d + weight) {

   v->d = u->d + weight;
   v->parent = u;

}

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- shortest -------------------------------  *
*                                                                            *
*****************************************************************************/

int shortest(Graph *graph, const PathVertex *start, List *paths, int (*match)
   (const void *key1, const void *key2)) {

AdjList            *adjlist;

PathVertex         *pth_vertex,
                   *adj_vertex;

ListElmt           *element,
                   *member;

double             minimum;

int                found,
                   i;

/*****************************************************************************
*                                                                            *
*  Initialize all of the vertices in the graph.                              *
*                                                                            *
*****************************************************************************/

found = 0;

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   pth_vertex = ((AdjList *)list_data(element))->vertex;

   if (match(pth_vertex, start)) {

      /***********************************************************************
      *                                                                      *
      *  Initialize the start vertex.                                        *
      *                                                                      *
      ***********************************************************************/

      pth_vertex->color = white;
      pth_vertex->d = 0;
      pth_vertex->parent = NULL;
      found = 1;

      }

   else {

      /***********************************************************************
      *                                                                      *
      *  Initialize vertices other than the start vertex.                    *
      *                                                                      *
      ***********************************************************************/

      pth_vertex->color = white;
      pth_vertex->d = DBL_MAX;
      pth_vertex->parent = NULL;

   }

}

/*****************************************************************************
*                                                                            *
*  Return if the start vertex was not found.                                 *
*                                                                            *
*****************************************************************************/

if (!found)
   return -1;

/*****************************************************************************
*                                                                            *
*  Use Dijkstra's algorithm to compute shortest paths from the start vertex. *
*                                                                            *
*****************************************************************************/

i = 0;

while (i < graph_vcount(graph)) {

   /**************************************************************************
   *                                                                         *
   *  Select the white vertex with the smallest shortest-path estimate.      *
   *                                                                         *
   **************************************************************************/

   minimum = DBL_MAX;

   for (element = list_head(&graph_adjlists(graph)); element != NULL; element
      = list_next(element)) {

      pth_vertex = ((AdjList *)list_data(element))->vertex;

      if (pth_vertex->color == white && pth_vertex->d < minimum) {

         minimum = pth_vertex->d;
         adjlist = list_data(element);

      }

   }

   /**************************************************************************
   *                                                                         *
   *  Color the selected vertex black.                                       *
   *                                                                         *
   **************************************************************************/

   ((PathVertex *)adjlist->vertex)->color = black;

   /**************************************************************************
   *                                                                         *
   *  Traverse each vertex adjacent to the selected vertex.                  *
   *                                                                         *
   **************************************************************************/

   for (member = list_head(&adjlist->adjacent); member != NULL; member =
      list_next(member)) {

      adj_vertex = list_data(member);

      /***********************************************************************
      *                                                                      *
      *  Find the adjacent vertex in the list of adjacency-list structures.  *
      *                                                                      *
      ***********************************************************************/

      for (element = list_head(&graph_adjlists(graph)); element != NULL;
         element = list_next(element)) {

         pth_vertex = ((AdjList *)list_data(element))->vertex;

         if (match(pth_vertex, adj_vertex)) {

            /*****************************************************************
            *                                                                *
            *  Relax the adjacent vertex in the list of adjacency-list       *
            *  structures.                                                   *
            *                                                                *
            *****************************************************************/

            relax(adjlist->vertex, pth_vertex, adj_vertex->weight);

         }

      }

   }

   /**************************************************************************
   *                                                                         *
   *  Prepare to select the next vertex.                                     *
   *                                                                         *
   **************************************************************************/

   i++;

}

/*****************************************************************************
*                                                                            *
*  Load the vertices with their path information into a list.                *
*                                                                            *
*****************************************************************************/

list_init(paths, NULL);

for (element = list_head(&graph_adjlists(graph)); element != NULL; element =
   list_next(element)) {

   /**************************************************************************
   *                                                                         *
   *  Load each black vertex from the list of adjacency-list structures.     *
   *                                                                         *
   **************************************************************************/

   pth_vertex = ((AdjList *)list_data(element))->vertex;

   if (pth_vertex->color == black) {

      if (list_ins_next(paths, list_tail(paths), pth_vertex) != 0) {

         list_destroy(paths);
         return -1;

      }

   }

}

return 0;

}
