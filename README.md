# gost-r34.11-94
Implementation of the old **GOST R34.11-94** hash function. 

This code is from 1998! 
I've only slightly modernised for 64-bit types and C99 in 2016.
The algorithm was successfully cryptanalysed by Mendel et al (Crypto '08)
and is no longer considered secure.
The hash function has since been replaced by an entirely different algorithm
"Streebog" revision GOST R 34.11-2012. I've published this for historical
reasons; for example some may find the original translation Postscript from '94
interesting.

Usage:
```
  % make            to compile the package
  % ./gosttest      to perform some tests
  % ./gostan        to print out the linear dependency matrices
```

Written by Markku-Juhani Saarinen <mjos@iki.fi>

* Version 1.00, 22-Apr-1998.
* Version 1.01, 12-Jun-1998.
* Version 1.02, 12-Jan-2016. Switched to stdint.h types (now works on 64-bit).
 
## Source Files

* `gosthash.h`    Header file that contains the "API".
* `gosthash.c`    The hash function itself. Link this file to your application.
* `gosttest.c`    A test driver.
* `gostan.c`      Prints some linear dependency matrices.
* `Makefile`


## Some documentation is also included

* `gost34.11.ps`

 This is a draft translation of the Russian standard GOST R 34.11-94, 
 by Michael Roe of Cambridge University, England. Only the relevant 
 technical detail is included in this paper.


* `gost28147.ps`

  This is draft translation of the standard GOST 28147-89, by 
  Aleksandr Malchik of Sun Microsystems. GOST 28147-89 is a block cipher
  which is used as a nonlinear component in the compression function.
   
 
