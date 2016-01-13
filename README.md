# gost-r34.11-94
Implementation of **GOST R34.11-94** hash function. 
(This is from 1998! Only slightly modernized for 64-bit types and C99 in 2016.)

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
   
 
