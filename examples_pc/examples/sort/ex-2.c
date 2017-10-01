/*****************************************************************************
*                                                                            *
*  ex-2.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates sorting a directory listing (see Chapter 12).    *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <sys/param.h>
#include <unistd.h>

#include "directls.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

Directory          *dir;

char               buffer[MAXPATHLEN];

int                count,
                   i;

/*****************************************************************************
*                                                                            *
*  Get the directory listing.                                                *
*                                                                            *
*****************************************************************************/

if (argc > 1) {

   if ((count = directls(argv[1], &dir)) < 0) {

      fprintf(stdout, "Could not read directory\n");
      exit(1);

   }

   }

else {
   
   if ((count = directls(getcwd(buffer, MAXPATHLEN), &dir)) < 0) {

      fprintf(stdout, "Could not read directory\n");
      exit(1);

   }

}

/*****************************************************************************
*                                                                            *
*  Display the directory listing.                                            *
*                                                                            *
*****************************************************************************/

for (i = 0; i < count; i++)
   fprintf(stdout, "%s\n", dir[i].name);

fprintf(stdout, "%d found\n", count);
free(dir);

return 0;

}
