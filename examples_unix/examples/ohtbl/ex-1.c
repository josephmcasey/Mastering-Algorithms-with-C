/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using an open-addressed hash table (see Chapter  *
*               8).                                                          *
*                                                                            *
*****************************************************************************/

#include <stdio.h>

#include "ohtbl.h"

/*****************************************************************************
*                                                                            *
*  Define the size of the hash table.                                        *
*                                                                            *
*****************************************************************************/

#define            TBLSIZ               11

/*****************************************************************************
*                                                                            *
*  ------------------------------ match_char ------------------------------  *
*                                                                            *
*****************************************************************************/

static int match_char(const void *char1, const void *char2) {

/*****************************************************************************
*                                                                            *
*  Determine whether two characters match.                                   *
*                                                                            *
*****************************************************************************/

return (*(const char *)char1 == *(const char *)char2);

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- h1_char --------------------------------  *
*                                                                            *
*****************************************************************************/

static int h1_char(const void *key) {

/*****************************************************************************
*                                                                            *
*  Define a simplistic auxilary hash function.                               *
*                                                                            *
*****************************************************************************/

return *(const char *)key % TBLSIZ;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- h2_char --------------------------------  *
*                                                                            *
*****************************************************************************/

static int h2_char(const void *key) {

/*****************************************************************************
*                                                                            *
*  Define a simplistic auxilary hash function.                               *
*                                                                            *
*****************************************************************************/

return 1 + (*(const char *)key % (TBLSIZ - 2));

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_table -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_table(const OHTbl *htbl) {

int                i;

/*****************************************************************************
*                                                                            *
*  Display the open-addressed hash table.                                    *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Table size is %d\n", ohtbl_size(htbl));

for (i = 0; i < TBLSIZ; i++) {

   if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {

      fprintf(stdout, "Slot[%03d]=%c\n", i, *(char *)htbl->table[i]);

      }

   else {

      fprintf(stdout, "Slot[%03d]= \n", i);

   }

}

return;

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

OHTbl              htbl;

char               *data,
                   c;

int                retval,
                   i,
                   j;

/*****************************************************************************
*                                                                            *
*  Initialize the open-addressed hash table.                                 *
*                                                                            *
*****************************************************************************/

if (ohtbl_init(&htbl, TBLSIZ, h1_char, h2_char, match_char, free) != 0)
   return 1;

/*****************************************************************************
*                                                                            *
*  Perform some open-addressed hash table operations.                        *
*                                                                            *
*****************************************************************************/

for (i = 0; i < 5; i++) {

   if ((data = (char *)malloc(sizeof(char))) == NULL)
      return 1;

   /**************************************************************************
   *                                                                         *
   *  The following expression produces "random" data while avoiding dupli-  *
   *  cates.                                                                 *
   *                                                                         *
   **************************************************************************/

   *data = ((8 + (i * 9)) % 23) + 'A';

   fprintf(stdout, "Hashing %c:", *data);

   for (j = 0; j < TBLSIZ; j++)
      fprintf(stdout," %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);

   fprintf(stdout, "\n");

   if (ohtbl_insert(&htbl, data) != 0)
      return 1;

   print_table(&htbl);

}

for (i = 0; i < 5; i++) {

   if ((data = (char *)malloc(sizeof(char))) == NULL)
      return 1;

   /**************************************************************************
   *                                                                         *
   *  The following expression works similar to the one above but produces   *
   *  collisions.                                                            *
   *                                                                         *
   **************************************************************************/

   *data = ((8 + (i * 9)) % 13) + 'j';

   fprintf(stdout, "Hashing %c:", *data);

   for (j = 0; j < TBLSIZ; j++)
      fprintf(stdout," %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);

   fprintf(stdout, "\n");

   if (ohtbl_insert(&htbl, data) != 0)
      return 1;

   print_table(&htbl);

}

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'R';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Trying to insert R again...Value=%d (1=OK)\n", retval);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'n';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Trying to insert n again...Value=%d (1=OK)\n", retval);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'o';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Trying to insert o again...Value=%d (1=OK)\n", retval);

fprintf(stdout, "Removing R, n, and o\n");

c = 'R';
data = &c;

if (ohtbl_remove(&htbl, (void **)&data) == 0)
   free(data);

c = 'n';
data = &c;

if (ohtbl_remove(&htbl, (void **)&data) == 0)
   free(data);

c = 'o';
data = &c;

if (ohtbl_remove(&htbl, (void **)&data) == 0)
   free(data);

print_table(&htbl);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'R';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Hashing %c:", *data);

for (j = 0; j < TBLSIZ; j++)
   fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);

fprintf(stdout, "\n");

fprintf(stdout, "Trying to insert R again...Value=%d (0=OK)\n", retval);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'n';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Hashing %c:", *data);

for (j = 0; j < TBLSIZ; j++)
   fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);

fprintf(stdout, "\n");

fprintf(stdout, "Trying to insert n again...Value=%d (0=OK)\n", retval);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'o';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Hashing %c:", *data);

for (j = 0; j < TBLSIZ; j++)
   fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);

fprintf(stdout, "\n");

fprintf(stdout, "Trying to insert o again...Value=%d (0=OK)\n", retval);

print_table(&htbl);

fprintf(stdout, "Inserting X\n");

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'X';

if (ohtbl_insert(&htbl, data) != 0)
   return 1;

print_table(&htbl);

if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

*data = 'Y';

if ((retval = ohtbl_insert(&htbl, data)) != 0)
   free(data);

fprintf(stdout, "Trying to insert into a full table...Value=%d (-1=OK)\n",
   retval);

c = 'o';
data = &c;

if (ohtbl_lookup(&htbl, (void **)&data) == 0)
   fprintf(stdout, "Found an occurrence of o\n");
else
   fprintf(stdout, "Did not find an occurrence of X\n");

c = 'Z';
data = &c;

if (ohtbl_lookup(&htbl, (void **)&data) == 0)
   fprintf(stdout, "Found an occurrence of Z\n");
else
   fprintf(stdout, "Did not find an occurrence of Z\n");

/*****************************************************************************
*                                                                            *
*  Destroy the open-addressed hash table.                                    *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Destroying the hash table\n");
ohtbl_destroy(&htbl);

return 0;

}
