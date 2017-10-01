/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates sorting algorithms (see Chapter 12).             *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "sort.h"

/*****************************************************************************
*                                                                            *
*  Define the size of strings.                                               *
*                                                                            *
*****************************************************************************/

#define            STRSIZ                6

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_idata -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_idata(const int *array, int size) {

int                i;

/*****************************************************************************
*                                                                            *
*  Display the array of integers.                                            *
*                                                                            *
*****************************************************************************/

for (i = 0; i < size; i++)
   fprintf(stdout, "A[%02d]=%d\n", i, array[i]);

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_sdata -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_sdata(char array[][STRSIZ], int size) {

int                i;

/*****************************************************************************
*                                                                            *
*  Display the array of strings.                                             *
*                                                                            *
*****************************************************************************/

for (i = 0; i < size; i++)
   fprintf(stdout, "A[%02d]=%s\n", i, array[i]);

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ compare_int -----------------------------  *
*                                                                            *
*****************************************************************************/

static int compare_int(const void *int1, const void *int2) {

/*****************************************************************************
*                                                                            *
*  Compare two integers.                                                     *
*                                                                            *
*****************************************************************************/

if (*(const int *)int1 > *(const int *)int2)
   return 1;
else if (*(const int *)int1 < *(const int *)int2)
   return -1;
else
   return 0;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ compare_str -----------------------------  *
*                                                                            *
*****************************************************************************/

static int compare_str(const void *str1, const void *str2) {

int                retval;

/*****************************************************************************
*                                                                            *
*  Compare two strings.                                                      *
*                                                                            *
*****************************************************************************/

if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0)
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

int                iarray[10],
                   marray[10],
                   qarray[10],
                   carray[10],
                   rarray[10];

char               sarray[10][STRSIZ];

int                size = 10;

/*****************************************************************************
*                                                                            *
*  Load the arrays with data to sort.                                        *
*                                                                            *
*****************************************************************************/

iarray[0] = 0;
iarray[1] = 5;
iarray[2] = 1;
iarray[3] = 7;
iarray[4] = 3;
iarray[5] = 2;
iarray[6] = 8;
iarray[7] = 9;
iarray[8] = 4;
iarray[9] = 6;

memcpy(marray, iarray, size * sizeof(int));
memcpy(qarray, iarray, size * sizeof(int));
memcpy(carray, iarray, size * sizeof(int));

rarray[0] = 11111323;
rarray[1] = 99283743;
rarray[2] = 98298383;
rarray[3] = 99987444;
rarray[4] = 43985209;
rarray[5] = 99911110;
rarray[6] = 11111324;
rarray[7] = 39842329;
rarray[8] = 97211029;
rarray[9] = 99272928;

strcpy(sarray[0], "ebcde");
strcpy(sarray[1], "ghidj");
strcpy(sarray[2], "ghiea");
strcpy(sarray[3], "abaae");
strcpy(sarray[4], "abaaa");
strcpy(sarray[5], "abcde");
strcpy(sarray[6], "abbcd");
strcpy(sarray[7], "ddaab");
strcpy(sarray[8], "faeja");
strcpy(sarray[9], "aaaaa");

/*****************************************************************************
*                                                                            *
*  Perform insertion sort.                                                   *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Before issort\n");
print_idata(iarray, size);

if (issort(iarray, size, sizeof(int), compare_int) != 0)
   return 1;

fprintf(stdout, "After issort\n");
print_idata(iarray, size);

/*****************************************************************************
*                                                                            *
*  Perform quicksort.                                                        *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Before qksort\n");
print_idata(qarray, size);

if (qksort(qarray, size, sizeof(int), 0, size - 1, compare_int) != 0)
   return 1;

fprintf(stdout, "After qksort\n");
print_idata(qarray, size);

/*****************************************************************************
*                                                                            *
*  Perform merge sort.                                                       *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Before mgsort\n");
print_sdata(sarray, size);

if (mgsort(sarray, size, STRSIZ, 0, size - 1, compare_str) != 0)
   return 1;

fprintf(stdout, "After mgsort\n");
print_sdata(sarray, size);

/*****************************************************************************
*                                                                            *
*  Perform counting sort.                                                    *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Before ctsort\n");
print_idata(carray, size);

if (ctsort(carray, size, 10) != 0)
   return 1;

fprintf(stdout, "After ctsort\n");
print_idata(carray, size);

/*****************************************************************************
*                                                                            *
*  Perform radix sort.                                                       *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Before rxsort\n");
print_idata(rarray, size);

if (rxsort(rarray, size, 8, 10) != 0)
   return 1;

fprintf(stdout, "After rxsort\n");
print_idata(rarray, size);

return 0;

}
