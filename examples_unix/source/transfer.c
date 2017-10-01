/*****************************************************************************
*                                                                            *
*  ------------------------------ transfer.c ------------------------------  *
*                                                                            *
*****************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>

#include "compress.h"
#include "transfer.h"

/*****************************************************************************
*                                                                            *
*  ------------------------------- send_comp ------------------------------  *
*                                                                            *
*****************************************************************************/

int send_comp(int s, const unsigned char *data, int size, int flags) {

unsigned char      *compressed;

int                size_comp;

/*****************************************************************************
*                                                                            *
*  Compress the data.                                                        *
*                                                                            *
*****************************************************************************/

if ((size_comp = huffman_compress(data, &compressed, size)) < 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Send the compressed data preceded by its size.                            *
*                                                                            *
*****************************************************************************/

if (send(s, (char *)&size_comp, sizeof(int), flags) != sizeof(int))
   return -1;

if (send(s, (char *)compressed, size_comp, flags) != size_comp)
   return -1;

/*****************************************************************************
*                                                                            *
*  Free the buffer of compressed data.                                       *
*                                                                            *
*****************************************************************************/

free(compressed);

return 0;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------- recv_comp ------------------------------  *
*                                                                            *
*****************************************************************************/

int recv_comp(int s, unsigned char **data, int *size, int flags) {

unsigned char      *compressed;

int                size_comp;

/*****************************************************************************
*                                                                            *
*  Receive the compressed data preceded by its size.                         *
*                                                                            *
*****************************************************************************/

if (recv(s, (char *)&size_comp, sizeof(int), flags) != sizeof(int))
   return -1;

if ((compressed = (unsigned char *)malloc(size_comp)) == NULL)
   return -1;

if (recv(s, (char *)compressed, size_comp, flags) != size_comp) {

   free(compressed);
   return -1;

}

/*****************************************************************************
*                                                                            *
*  Uncompress the data.                                                      *
*                                                                            *
*****************************************************************************/

if ((*size = huffman_uncompress(compressed, data)) < 0)
   return -1;

/*****************************************************************************
*                                                                            *
*  Free the buffer of compressed data.                                       *
*                                                                            *
*****************************************************************************/

free(compressed);

return 0;

}
