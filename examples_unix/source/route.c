/*****************************************************************************
*                                                                            *
*  -------------------------------- route.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "graphalg.h"
#include "list.h"
#include "route.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- route --------------------------------  *
*                                                                            *
*****************************************************************************/

int route(List *paths, PathVertex *destination, PathVertex **next, int
   (*match)(const void *key1, const void *key2)) {

PathVertex         *temp,
                   *parent;

ListElmt           *element;

int                found;

/*****************************************************************************
*                                                                            *
*  Locate the destination in the list of gateways.                           *
*                                                                            *
*****************************************************************************/

found = 0;

for (element = list_head(paths); element != NULL; element =
   list_next(element)) {

   if (match(list_data(element), destination)) {

      temp = list_data(element);
      parent = ((PathVertex *)list_data(element))->parent;
      found = 1;
      break;

   }

}

/*****************************************************************************
*                                                                            *
*  Return if the destination is not reachable.                               *
*                                                                            *
*****************************************************************************/

if (!found)
   return -1;

/*****************************************************************************
*                                                                            *
*  Compute the next gateway in the shortest path to the destination.         *
*                                                                            *
*****************************************************************************/

while (parent != NULL) {

   temp = list_data(element);
   found = 0;

   for (element = list_head(paths); element != NULL; element =
      list_next(element)) {

      if (match(list_data(element), parent)) {

         parent = ((PathVertex *)list_data(element))->parent;
         found = 1;
         break;

      }

   }

   /**************************************************************************
   *                                                                         *
   *  Return if the destination is not reachable.                            *
   *                                                                         *
   **************************************************************************/

   if (!found)
      return -1;

}

*next = temp;

return 0;

}
