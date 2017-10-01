/*****************************************************************************
*                                                                            *
*  ------------------------------- encrypt.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef ENCRYPT_H
#define ENCRYPT_H

/*****************************************************************************
*                                                                            *
*  In a secure implementation, Huge should be at least 400 decimal digits,   *
*  instead of the 10 below (ULONG_MAX = 4294967295).                         *
*                                                                            *
*****************************************************************************/

typedef unsigned long Huge;

/*****************************************************************************
*                                                                            *
*  Define a structure for RSA public keys.                                   *
*                                                                            *
*****************************************************************************/

typedef struct RsaPubKey_ {

Huge               e;
Huge               n;

} RsaPubKey;

/*****************************************************************************
*                                                                            *
*  Define a structure for RSA private keys.                                  *
*                                                                            *
*****************************************************************************/

typedef struct RsaPriKey_ {

Huge               d;
Huge               n;

} RsaPriKey;

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void des_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
   const unsigned char *key);

void des_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
   const unsigned char *key);

void rsa_encipher(Huge plaintext, Huge *ciphertext, RsaPubKey pubkey);

void rsa_decipher(Huge ciphertext, Huge *plaintext, RsaPriKey prikey);

#endif
