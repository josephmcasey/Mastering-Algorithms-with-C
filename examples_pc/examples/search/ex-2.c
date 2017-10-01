/*****************************************************************************
*                                                                            *
*  ex-2.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates spell checking (see Chapter 12).                 *
*                                                                            *
*****************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "search.h"
#include "sort.h"
#include "spell.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------ compare_str -----------------------------  *
*                                                                            *
*****************************************************************************/

static int compare_str(const void *key1, const void *key2) {

int                retval;

/*****************************************************************************
*                                                                            *
*  Compare two strings.                                                      *
*                                                                            *
*****************************************************************************/

if ((retval = strcmp((const char *)key1, (const char *)key2)) > 0)
   return 1;
else if (retval < 0)
   return -1;
else
   return 0;

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

char               dictionary[12][SPELL_SIZE],
                   lookup[SPELL_SIZE],
                   target[SPELL_SIZE];

int                i;

/*****************************************************************************
*                                                                            *
*  Create a sorted dictionary of words.                                      *
*                                                                            *
*****************************************************************************/

strcpy(dictionary[ 0], "HOP");
strcpy(dictionary[ 1], "HAT");
strcpy(dictionary[ 2], "TAP");
strcpy(dictionary[ 3], "BAT");
strcpy(dictionary[ 4], "TIP");
strcpy(dictionary[ 5], "MOP");
strcpy(dictionary[ 6], "MOM");
strcpy(dictionary[ 7], "CAT");
strcpy(dictionary[ 8], "ZOO");
strcpy(dictionary[ 9], "WAX");
strcpy(dictionary[10], "TOP");
strcpy(dictionary[11], "DIP");

if (issort(dictionary, 12, SPELL_SIZE, compare_str) != 0)
   return 1;

/*****************************************************************************
*                                                                            *
*  Perform spell checking.                                                   *
*                                                                            *
*****************************************************************************/

strcpy(lookup, "hat");
memset(target, 0, SPELL_SIZE);

for (i = 0; i < strlen(lookup); i++)
   target[i] = toupper(lookup[i]);

if (spell(dictionary, 12, target))
   fprintf(stdout, "%s is spelled correctly\n", lookup);
else
   fprintf(stdout, "%s is not spelled correctly\n", lookup);

strcpy(lookup, "dop");
memset(target, 0, SPELL_SIZE);

for (i = 0; i < strlen(lookup); i++)
   target[i] = toupper(lookup[i]);

if (spell(dictionary, 12, target))
   fprintf(stdout, "%s is spelled correctly\n", lookup);
else
   fprintf(stdout, "%s is not spelled correctly\n", lookup);

strcpy(lookup, "dip");
memset(target, 0, SPELL_SIZE);

for (i = 0; i < strlen(lookup); i++)
   target[i] = toupper(lookup[i]);

if (spell(dictionary, 12, target))
   fprintf(stdout, "%s is spelled correctly\n", lookup);
else
   fprintf(stdout, "%s is not spelled correctly\n", lookup);

return 0;

}
