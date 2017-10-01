/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates data encryption (see Chapter 15).                *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "encrypt.h"

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

unsigned char      destmp[8],
                   desptx[8],
                   desctx[8],
                   deskey[8];

Huge               rsatmp,
                   rsaptx,
                   rsactx;

RsaPubKey          rsapubkey;
RsaPriKey          rsaprikey;

int                i;

/*****************************************************************************
*                                                                            *
*  Encipher some data using DES.                                             *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Enciphering with DES\n");

destmp[0] = 0xa9;
destmp[1] = 0x10;
destmp[2] = 0x11;
destmp[3] = 0x38;
destmp[4] = 0x93;
destmp[5] = 0xca;
destmp[6] = 0xb4;
destmp[7] = 0xa1;

deskey[0] = 0x01;
deskey[1] = 0x1f;
deskey[2] = 0x01;
deskey[3] = 0x1f;
deskey[4] = 0x01;
deskey[5] = 0x0e;
deskey[6] = 0x01;
deskey[7] = 0x0e;

fprintf(stdout, "Before enciphering\n");

fprintf(stdout, "destmp: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   destmp[0], destmp[1], destmp[2], destmp[3], destmp[4], destmp[5],
   destmp[6], destmp[7]);

fprintf(stdout, "deskey: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   deskey[0], deskey[1], deskey[2], deskey[3], deskey[4], deskey[5],
   deskey[6], deskey[7]);

des_encipher(destmp, desctx, deskey);

fprintf(stdout, "After enciphering\n");

fprintf(stdout, "destmp: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   destmp[0], destmp[1], destmp[2], destmp[3], destmp[4], destmp[5],
   destmp[6], destmp[7]);

fprintf(stdout, "desctx: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   desctx[0], desctx[1], desctx[2], desctx[3], desctx[4], desctx[5],
   desctx[6], desctx[7]);

fprintf(stdout, "Before deciphering\n");

fprintf(stdout, "desctx: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   desctx[0], desctx[1], desctx[2], desctx[3], desctx[4], desctx[5],
   desctx[6], desctx[7]);

fprintf(stdout, "deskey: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   deskey[0], deskey[1], deskey[2], deskey[3], deskey[4], deskey[5],
   deskey[6], deskey[7]);

des_decipher(desctx, desptx, deskey);

fprintf(stdout, "After deciphering\n");

fprintf(stdout, "desctx: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   desctx[0], desctx[1], desctx[2], desctx[3], desctx[4], desctx[5],
   desctx[6], desctx[7]);

fprintf(stdout, "desptx: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   desptx[0], desptx[1], desptx[2], desptx[3], desptx[4], desptx[5],
   desptx[6], desptx[7]);

/*****************************************************************************
*                                                                            *
*  Encipher some data using RSA.                                             *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Enciphering with RSA\n");

rsapubkey.e = 17;
rsapubkey.n = 209;
rsaprikey.d = 53;
rsaprikey.n = 209;

fprintf(stdout, "d=%d, e=%d, n=%d\n", rsaprikey.d, rsapubkey.e, rsapubkey.n);

for (i = 0; i < 128; i++) {

   rsatmp = i;
   rsa_encipher(rsatmp, &rsactx, rsapubkey);
   rsa_decipher(rsactx, &rsaptx, rsaprikey);

   if (rsatmp == rsaptx)
      fprintf(stdout, "rsatmp=%5d, rsactx=%5d, rsaptx=%5d (OK)\n", rsatmp,
         rsactx, rsaptx);
   else
      fprintf(stdout, "rsatmp=%5d, rsactx=%5d, rsaptx=%5d (ERROR)\n", rsatmp,
         rsactx, rsaptx);

}

return 0;

}
