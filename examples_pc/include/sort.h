/*****************************************************************************
*                                                                            *
*  -------------------------------- sort.h --------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef SORT_H
#define SORT_H

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

int issort(void *data, int size, int esize, int (*compare)(const void *key1,
   const void *key2));

int qksort(void *data, int size, int esize, int i, int k, int (*compare)
   (const void *key1, const void *key2));

int mgsort(void *data, int size, int esize, int i, int k, int (*compare)
   (const void *key1, const void *key2));

int ctsort(int *data, int size, int k);

int rxsort(int *data, int size, int p, int k);

#endif
