/*****************************************************************************
*                                                                            *
*  -------------------------------- graph.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ graph_init ------------------------------  *
*                                                                            *
*****************************************************************************/

void graph_init(Graph *graph, int (*match)(const void *key1, const void
   *key2), void (*destroy)(void *data)) {

/*****************************************************************************
*                                                                            *
*  Initialize the graph.                                                     *
*                                                                            *
*****************************************************************************/

graph->vcount = 0;
graph->ecount = 0;
graph->match = match;
graph->destroy = destroy;

/*****************************************************************************
*                                                                            *
*  Initialize the list of adjacency-list structures.                         *
*                                                                            *
*****************************************************************************/

list_init(&graph->adjlists, NULL);

return;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- graph_destroy ----------------------------  *
*                                                                            *
*****************************************************************************/

void graph_destroy(Graph *graph) {

AdjList            *adjlist;

/*****************************************************************************
*                                                                            *
*  Remove each adjacency-list structure and destroy its adjacency list.      *
*                                                                            *
*****************************************************************************/

while (list_size(&graph->adjlists) > 0) {

   if (list_rem_next(&graph->adjlists, NULL, (void **)&adjlist) == 0) {

      set_destroy(&adjlist->adjacent);

      if (graph->destroy != NULL)
         graph->destroy(adjlist->vertex);

      free(adjlist);

   }

}

/*****************************************************************************
*                                                                            *
*  Destroy the list of adjacency-list structures, which is now empty.        *
*                                                                            *
*****************************************************************************/

list_destroy(&graph->adjlists);

/*****************************************************************************
*                                                                            *
*  No operations are allowed now, but clear the structure as a precaution.   *
*                                                                            *
*****************************************************************************/

memset(graph, 0, sizeof(Graph));

return;

}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_ins_vertex ---------------------------  *
*                                                                            *
*****************************************************************************/

int graph_ins_vertex(Graph *graph, const void *data) {

ListElmt           *element;

AdjList            *adjlist;

int                retval;

/*****************************************************************************
*                                                                            *
*  Do not allow the insertion of duplicate vertices.                         *
*                                                                            *
*****************************************************************************/

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data, ((AdjList *)list_data(element))->vertex))
      return 1;

}

/*****************************************************************************
*                                                                            *
*  Insert the vertex.                                                        *
*                                                                            *
*****************************************************************************/

if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL)
   return -1;

adjlist->vertex = (void *)data;
set_init(&adjlist->adjacent, graph->match, graph->destroy);

if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists),
   adjlist)) != 0) {

   return retval;

}

/*****************************************************************************
*                                                                            *
*  Adjust the vertex count to account for the inserted vertex.               *
*                                                                            *
*****************************************************************************/

graph->vcount++;

return 0;

}

/*****************************************************************************
*                                                                            *
*  ---------------------------- graph_ins_edge ----------------------------  *
*                                                                            *
*****************************************************************************/

int graph_ins_edge(Graph *graph, const void *data1, const void *data2) {

ListElmt           *element;

int                retval;

/*****************************************************************************
*                                                                            *
*  Do not allow insertion of an edge without both its vertices in the graph. *
*                                                                            *
*****************************************************************************/

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data2, ((AdjList *)list_data(element))->vertex))
      break;

}

if (element == NULL)
   return -1;

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
      break;

}

if (element == NULL)
   return -1;

/*****************************************************************************
*                                                                            *
*  Insert the second vertex into the adjacency list of the first vertex.     *
*                                                                            *
*****************************************************************************/

if ((retval = set_insert(&((AdjList *)list_data(element))->adjacent, data2))
   != 0) {

   return retval;

}

/*****************************************************************************
*                                                                            *
*  Adjust the edge count to account for the inserted edge.                   *
*                                                                            *
*****************************************************************************/

graph->ecount++;

return 0;

}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_rem_vertex ---------------------------  *
*                                                                            *
*****************************************************************************/

int graph_rem_vertex(Graph *graph, void **data) {

ListElmt           *element,
                   *temp,
                   *prev;

AdjList            *adjlist;

int                found;

/*****************************************************************************
*                                                                            *
*  Traverse each adjacency list and the vertices it contains.                *
*                                                                            *
*****************************************************************************/

prev = NULL;
found = 0;

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   /**************************************************************************
   *                                                                         *
   *  Do not allow removal of the vertex if it is in an adjacency list.      *
   *                                                                         *
   **************************************************************************/

   if (set_is_member(&((AdjList *)list_data(element))->adjacent, *data))
      return -1;

   /**************************************************************************
   *                                                                         *
   *  Keep a pointer to the vertex to be removed.                            *
   *                                                                         *
   **************************************************************************/

   if (graph->match(*data, ((AdjList *)list_data(element))->vertex)) {
 
      temp = element;
      found = 1;

   }

   /**************************************************************************
   *                                                                         *
   *  Keep a pointer to the vertex before the vertex to be removed.          *
   *                                                                         *
   **************************************************************************/

   if (!found)
      prev = element;

}
 
/*****************************************************************************
*                                                                            *
*  Return if the vertex was not found.                                       *
*                                                                            *
*****************************************************************************/

if (!found)
   return -1;

/*****************************************************************************
*                                                                            *
*  Do not allow removal of the vertex if its adjacency list is not empty.    *
*                                                                            *
*****************************************************************************/

if (set_size(&((AdjList *)list_data(temp))->adjacent) > 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Remove the vertex.                                                        *
*                                                                            *
*****************************************************************************/

if (list_rem_next(&graph->adjlists, prev, (void **)&adjlist) != 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Free the storage allocated by the abstract data type.                     *
*                                                                            *
*****************************************************************************/

*data = adjlist->vertex;
free(adjlist);

/*****************************************************************************
*                                                                            *
*  Adjust the vertex count to account for the removed vertex.                *
*                                                                            *
*****************************************************************************/

graph->vcount--;

return 0;

}

/*****************************************************************************
*                                                                            *
*  ---------------------------- graph_rem_edge ----------------------------  *
*                                                                            *
*****************************************************************************/

int graph_rem_edge(Graph *graph, void *data1, void **data2) {

ListElmt           *element;

/*****************************************************************************
*                                                                            *
*  Locate the adjacency list for the first vertex.                           *
*                                                                            *
*****************************************************************************/

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
      break;

}

if (element == NULL)
   return -1;

/*****************************************************************************
*                                                                            *
*  Remove the second vertex from the adjacency list of the first vertex.     *
*                                                                            *
*****************************************************************************/

if (set_remove(&((AdjList *)list_data(element))->adjacent, data2) != 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Adjust the edge count to account for the removed edge.                    *
*                                                                            *
*****************************************************************************/

graph->ecount--;

return 0;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- graph_adjlist ----------------------------  *
*                                                                            *
*****************************************************************************/

int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist) {

ListElmt           *element,
                   *prev;

/*****************************************************************************
*                                                                            *
*  Locate the adjacency list for the vertex.                                 *
*                                                                            *
*****************************************************************************/

prev = NULL;

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data, ((AdjList *)list_data(element))->vertex))
      break;

   prev = element;

}

/*****************************************************************************
*                                                                            *
*  Return if the vertex was not found.                                       *
*                                                                            *
*****************************************************************************/

if (element == NULL)
   return -1;

/*****************************************************************************
*                                                                            *
*  Pass back the adjacency list for the vertex.                              *
*                                                                            *
*****************************************************************************/

*adjlist = list_data(element);

return 0;

}

/*****************************************************************************
*                                                                            *
*  --------------------------- graph_is_adjacent --------------------------  *
*                                                                            *
*****************************************************************************/

int graph_is_adjacent(const Graph *graph, const void *data1, const void
   *data2) {

ListElmt           *element,
                   *prev;

/*****************************************************************************
*                                                                            *
*  Locate the adjacency list of the first vertex.                            *
*                                                                            *
*****************************************************************************/

prev = NULL;

for (element = list_head(&graph->adjlists); element != NULL; element =
   list_next(element)) {

   if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
      break;

   prev = element;

}

/*****************************************************************************
*                                                                            *
*  Return if the first vertex was not found.                                 *
*                                                                            *
*****************************************************************************/

if (element == NULL)
   return 0;

/*****************************************************************************
*                                                                            *
*  Return whether the second vertex is in the adjacency list of the first.   *
*                                                                            *
*****************************************************************************/

return set_is_member(&((AdjList *)list_data(element))->adjacent, data2);

}
