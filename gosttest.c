/*
 *  gosttest.c
 *  21 Apr 1998  Markku-Juhani Saarinen <mjos@ssh.fi>
 *
 *  Test driver for GOST R 34.11-94 routines.
 *
 *  Copyright (c) 1998 SSH Communications Security, Finland
 *  All rights reserved.
 */

// Updated 12 Jan 2016  by Markku-Juhani O. Saarinen <mjos@iki.fi>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gosthash.h"

/*
 * This is the first test vector form the standard
 * (surprisingly, it's in english: "This is message, length=32 bytes")
 */

uint8_t test_text1[32] =
{
  0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20,
  0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x2c,
  0x20, 0x6c, 0x65, 0x6e, 0x67, 0x74, 0x68, 0x3d,
  0x33, 0x32, 0x20, 0x62, 0x79, 0x74, 0x65, 0x73,
};

uint8_t test_hash1[32] =
{
  0xb1, 0xc4, 0x66, 0xd3, 0x75, 0x19, 0xb8, 0x2e,
  0x83, 0x19, 0x81, 0x9f, 0xf3, 0x25, 0x95, 0xe0,
  0x47, 0xa2, 0x8c, 0xb6, 0xf8, 0x3e, 0xff, 0x1c,
  0x69, 0x16, 0xa8, 0x15, 0xa6, 0x37, 0xff, 0xfa
};

/*
 * This is the second test vector from the standard.
 * Again a string in (almost) english:
 * "Suppose the original message has length = 50 bytes"
 */

uint8_t test_text2[50] =
{
  0x53, 0x75, 0x70, 0x70, 0x6f, 0x73, 0x65, 0x20,
  0x74, 0x68, 0x65, 0x20, 0x6f, 0x72, 0x69, 0x67,
  0x69, 0x6e, 0x61, 0x6c, 0x20, 0x6d, 0x65, 0x73,
  0x73, 0x61, 0x67, 0x65, 0x20, 0x68, 0x61, 0x73,
  0x20, 0x6c, 0x65, 0x6e, 0x67, 0x74, 0x68, 0x20,
  0x3d, 0x20, 0x35, 0x30, 0x20, 0x62, 0x79, 0x74,
  0x65, 0x73
};

uint8_t test_hash2[32] =
{
  0x47, 0x1a, 0xba, 0x57, 0xa6, 0x0a, 0x77, 0x0d,
  0x3a, 0x76, 0x13, 0x06, 0x35, 0xc1, 0xfb, 0xea,
  0x4e, 0xf1, 0x4d, 0xe5, 0x1f, 0x78, 0xb4, 0xae,
  0x57, 0xdd, 0x89, 0x3b, 0x62, 0xf5, 0x52, 0x08
};


int main(int argc, char **argv)
{
  int i, j, l;
  clock_t tim;
  GostHashCtx hash;
  uint8_t digest[32], *buf;

  gosthash_init();

  /* Try the first test case */

  gosthash_reset(&hash);
  gosthash_update(&hash, test_text1, 32);
  gosthash_final(&hash, digest);

  if (memcmp(digest, test_hash1, 32) != 0)
    {
      fprintf(stderr, "Test 1 failed.\n");
      exit(-1);
    }

  /* Try the second test case */

  gosthash_reset(&hash);
  gosthash_update(&hash, test_text2, 50);
  gosthash_final(&hash, digest);

  if (memcmp(digest, test_hash2, 32) != 0)
    {
      fprintf(stderr, "Test 2 failed.\n");
      exit(-1);
    }

  /* Try the second test case in random-length pieces */

  for (i = 0; i < 1000; i++)
    {
      gosthash_reset(&hash);
      for (j = 0; j < 50; )
        {
          l = rand() % 51;
          if (l + j >= 50)
            l = 50 - j;
          gosthash_update(&hash, &test_text2[j], l);
          j += l;
        }
      if (memcmp(digest, test_hash2, 32) != 0)
        {
          fprintf(stderr, "Test 3 failed (iteration %d).\n", i);
          exit(-1);
        }
    }
     
  printf("Tests passed.\n");

  /* run a benchmark */

  buf = malloc(0x1000);
  for (i = 0; i < 0x1000; i++)
    buf[i] = (uint8_t) i;

  j = 0;
  tim = clock();
  gosthash_reset(&hash);
  do
    {
      for (i = 0; i < 0x100; i++)
        gosthash_update(&hash, buf, 0x1000);
      j++;
    }
  while(clock() - tim < 5 * CLOCKS_PER_SEC);

  gosthash_final(&hash, digest);
  free(buf);

  tim = clock() - tim;
  printf("Speed = %g MBit / second.\n",
         0.000001 * ((double) j * 0x800000) /
         ((double) tim / ((double) CLOCKS_PER_SEC)));

  return 0;
}
