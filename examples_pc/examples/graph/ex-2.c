/*****************************************************************************
*                                                                            *
*  ex-2.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates breadth-first search (see Chapter 11).           *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "set.h"

/*****************************************************************************
*                                                                            *
*  Define the size of strings.                                               *
*                                                                            *
*****************************************************************************/

#define            STRSIZ                2

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_graph -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_graph(const Graph *graph) {

Set                *adjacent;

BfsVertex          *vertex;

ListElmt           *element,
                   *member;

int                i,
                   j;

/*****************************************************************************
*                                                                            *
*  Display the graph.                                                        *
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
      fprintf(stdout, "%s", (char *)vertex->data);
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
*  ----------------------------- destroy_netid ----------------------------  *
*                                                                            *
*****************************************************************************/

static void destroy_netid(void *netid) {

/*****************************************************************************
*                                                                            *
*  Free the storage associated with the network ID.                          *
*                                                                            *
*****************************************************************************/

free(((BfsVertex *)netid)->data);
free(netid);

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ match_netid -----------------------------  *
*                                                                            *
*****************************************************************************/

static int match_netid(const void *netid1, const void *netid2) {

/*****************************************************************************
*                                                                            *
*  Determine whether two network IDs match.                                  *
*                                                                            *
*****************************************************************************/

return !strcmp(((const BfsVertex *)netid1)->data, ((const BfsVertex *)netid2)
   ->data);

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

Graph              network;

BfsVertex          *netid,
                   netid1,
                   *netid2;

List               list;

ListElmt           *element;

char               data1[STRSIZ];

int                i;

/*****************************************************************************
*                                                                            *
*  Initialize the graph.                                                     *
*                                                                            *
*****************************************************************************/

graph_init(&network, match_netid, destroy_netid);

/*****************************************************************************
*                                                                            *
*  Insert some network IDs.                                                  *
*                                                                            *
*****************************************************************************/

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node1");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node2");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node3");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node4");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node5");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

if ((netid = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid->data, "node6");
fprintf(stdout, "Inserting vertex %s\n", (char *)netid->data);

if (graph_ins_vertex(&network, netid) != 0)
   return 1;

print_graph(&network);

/*****************************************************************************
*                                                                            *
*  Insert some network connections.                                          *
*                                                                            *
*****************************************************************************/

netid1.data = data1;

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node1");
strcpy((char *)netid2->data, "node2");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node2");
strcpy((char *)netid2->data, "node1");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node1");
strcpy((char *)netid2->data, "node3");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node3");
strcpy((char *)netid2->data, "node1");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node2");
strcpy((char *)netid2->data, "node3");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node3");
strcpy((char *)netid2->data, "node2");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node2");
strcpy((char *)netid2->data, "node4");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node4");
strcpy((char *)netid2->data, "node2");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node3");
strcpy((char *)netid2->data, "node5");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node5");
strcpy((char *)netid2->data, "node3");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node4");
strcpy((char *)netid2->data, "node5");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node5");
strcpy((char *)netid2->data, "node4");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node5");
strcpy((char *)netid2->data, "node6");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

if ((netid2 = (BfsVertex *)malloc(sizeof(BfsVertex))) == NULL)
   return 1;

if ((netid2->data = malloc(STRSIZ)) == NULL)
   return 1;

strcpy((char *)netid1.data, "node6");
strcpy((char *)netid2->data, "node5");
fprintf(stdout, "Inserting edge %s to %s\n", (char *)netid1.data, (char *)
   netid2->data);

if (graph_ins_edge(&network, &netid1, netid2) != 0)
   return 1;

print_graph(&network);

/*****************************************************************************
*                                                                            *
*  Perform breadth-first search.                                             *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Generating the breadth-first search listing\n");

strcpy((char *)netid1.data, "node1");

if (bfs(&network, &netid1, &list) != 0)
   return 1;

i = 0;

for (element = list_head(&list); element != NULL; element =
   list_next(element)) {

   netid = list_data(element);
   fprintf(stdout, "list[%03d]=%s (color=%d, hops=%d)\n", i, (char *)netid->
      data, netid->color, netid->hops);
   i++;

}

/*****************************************************************************
*                                                                            *
*  Destroy the linked list.                                                  *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Destroying the list\n");
list_destroy(&list);

/*****************************************************************************
*                                                                            *
*  Destroy the graph.                                                        *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Destroying the graph\n");
graph_destroy(&network);

return 0;

}
