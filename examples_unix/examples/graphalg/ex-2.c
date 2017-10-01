/*****************************************************************************
*                                                                            *
*  ex-2.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates computing information for routing tables (see    *
*               Chapter 16).                                                 *
*                                                                            *
*****************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"
#include "route.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  Define the size of strings.                                               *
*                                                                            *
*****************************************************************************/

#define            STRSIZ                2

/*****************************************************************************
*                                                                            *
*  Define a structure for edge data in graphs.                               *
*                                                                            *
*****************************************************************************/

typedef struct EdgeData_ {

char               vertex1[STRSIZ],
                   vertex2[STRSIZ];

double             weight;

} EdgeData;

/*****************************************************************************
*                                                                            *
*  Define data for computing shortest paths.                                 *
*                                                                            *
*****************************************************************************/

#define            PTHVCT                6
#define            PTHECT               11

static char PthTestV[PTHVCT][STRSIZ] = {

   "a", "b", "c", "d", "e", "f"

};

static EdgeData PthTestE[PTHECT] = {

   {"a", "b", 8.0},
   {"a", "c", 4.0},
   {"b", "c", 6.0},
   {"b", "d", 2.0},
   {"b", "f", 4.0},
   {"c", "e", 4.0},
   {"c", "f", 1.0},
   {"e", "f", 5.0},
   {"f", "b", 2.0},
   {"f", "d", 7.0},
   {"f", "e", 4.0}

};

/*****************************************************************************
*                                                                            *
*  ---------------------------- print_graph_pth ---------------------------  *
*                                                                            *
*****************************************************************************/

static void print_graph_pth(const Graph *graph) {

Set                *adjacent;

PathVertex         *vertex;

ListElmt           *element,
                   *member;

int                i,
                   j;

/*****************************************************************************
*                                                                            *
*  Display the graph for computing shortest paths.                           *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Vertices=%d, edges=%d\n", graph_vcount(graph), graph_ecount
   (graph));

i = 0;
element = list_head(&graph_adjlists(graph));

while (i < list_size(&graph_adjlists(graph))) {

   vertex = ((AdjList *)list_data(element))->vertex;
   fprintf(stdout, "graph[%03d]=%s: ", i, (char *)vertex->data);

   j = 0;
   adjacent = &((AdjList *)list_data(element))->adjacent;
   member = list_head(adjacent);

   while (j < set_size(adjacent)) {

      vertex = list_data(member);
      if (j > 0) fprintf(stdout, ", ");
      fprintf(stdout, "%s(%4.1lf)", (char *)vertex->data, vertex->weight);
      member = list_next(member);
      j++;

   }

   i++;
   fprintf(stdout, "\n");
   element = list_next(element);

}

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- match_pth ------------------------------  *
*                                                                            *
*****************************************************************************/

static int match_pth(const void *pth1, const void *pth2) {

/*****************************************************************************
*                                                                            *
*  Determine whether the data in two PathVertex vertices match.              *
*                                                                            *
*****************************************************************************/

return !strcmp(((const PathVertex *)pth1)->data, ((const PathVertex *)pth2)->
   data);

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

Graph              graph;

PathVertex         *pth_start,
                   *pth_vertex,
                   pth_vertex1,
                   *pth_vertex2;

List               paths;

ListElmt           *element;

int                i;

/*****************************************************************************
*                                                                            *
*  Compute shortest paths.                                                   *
*                                                                            *
*****************************************************************************/

graph_init(&graph, match_pth, free);

fprintf(stdout, "Computing shortest paths\n");

for (i = 0; i < PTHVCT; i++) {

   if ((pth_vertex = (PathVertex *)malloc(sizeof(PathVertex))) == NULL)
      return 1;

   if (i == 1)
      pth_start = pth_vertex;

   pth_vertex->data = PthTestV[i];

   if (graph_ins_vertex(&graph, pth_vertex) != 0)
      return 1;

}

for (i = 0; i < PTHECT; i++) {

   if ((pth_vertex2 = (PathVertex *)malloc(sizeof(PathVertex))) == NULL)
       return 1;

   pth_vertex1.data = PthTestE[i].vertex1;
   pth_vertex2->data = PthTestE[i].vertex2;
   pth_vertex2->weight = PthTestE[i].weight;

   if (graph_ins_edge(&graph, &pth_vertex1, pth_vertex2) != 0)
      return 1;

}

print_graph_pth(&graph);

if (shortest(&graph, pth_start, &paths, match_pth) != 0)
   return 1;

for (element = list_head(&paths); element != NULL; element =
   list_next(element)) {

   pth_vertex = list_data(element);

   fprintf(stdout, "vertex=%s, parent=%s, d=%.1lf\n", (char *)pth_vertex->
      data, pth_vertex->parent != NULL ? (char *)pth_vertex->parent->data :
      "*", pth_vertex->d);

}

/*****************************************************************************
*                                                                            *
*  Determine the next vertex in the shortest route between two nodes.        *
*                                                                            *
*****************************************************************************/

pth_vertex1.data = "e";

if (route(&paths, &pth_vertex1, &pth_vertex, match_pth) != 0)
   return 1;

fprintf(stdout, "Next vertex in the route from %s to %s is %s\n", (char *)
   pth_start->data, (char *)pth_vertex1.data, (char *)pth_vertex->data);

list_destroy(&paths);
graph_destroy(&graph);

return 0;

}
