/*
 *  gosthash.h
 *  21 Apr 1998  Markku-Juhani Saarinen <mjos@ssh.fi>
 *
 *  GOST R 34.11-94, Russian Standard Hash Function
 *  header with function prototypes.
 *
 *  Copyright (c) 1998 SSH Communications Security, Finland
 *  All rights reserved.
 */

// Updated 12 Jan 2016  by Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef _GOSTHASH_H_
#define _GOSTHASH_H_

#include <stdint.h>
#include <stdlib.h>

/* State structure */

typedef struct
{
  uint32_t sum[8];
  uint32_t hash[8];
  uint32_t len[8];
  uint8_t partial[32];
  size_t partial_bytes;
} GostHashCtx;

/* Compute some lookup-tables that are needed by all other functions. */

void gosthash_init();

/* Clear the state of the given context structure. */

void gosthash_reset(GostHashCtx *ctx);

/* Mix in len bytes of data for the given buffer. */

void gosthash_update(GostHashCtx *ctx, const uint8_t *buf, size_t len);

/* Compute and save the 32-byte digest. */

void gosthash_final(GostHashCtx *ctx, uint8_t *digest);

#endif /* GOSTHASH_H */
