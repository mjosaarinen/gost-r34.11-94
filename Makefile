
#  Makefile
#  21 Apr 1998  Markku-Juhani Saarinen <mjos@ssh.fi>
#
#  GOST R 34.11-94, Russian Standard Hash Function

GOSTTEST_OBJS	= gosthash.o gosttest.o
GOSTAN_OBJS	= gosthash.o gostan.o
DIST		= gost-r34.11-94

# compile rules

CC		= gcc
CFLAGS		= -Wall -O3
INCLUDES	=
LDFLAGS		=
LIBS		=

all:		gosttest gostan

gosttest:	$(GOSTTEST_OBJS)
		$(CC) $(LDFLAGS) -o gosttest $(GOSTTEST_OBJS) $(LIBS)

gostan:		$(GOSTAN_OBJS)
		$(CC) $(LDFLAGS) -o gostan $(GOSTAN_OBJS) $(LIBS)

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<

test:		gosttest
		./gosttest

clean:
		rm -f gosttest gostan *.o *~ *core $(DIST).tar.gz

dist:		clean
		rm -f /tmp/$(DIST).tar /tmp/$(DIST).tar.gz $(DIST).tar.gz
		cd ..; tar cfv /tmp/$(DIST).tar $(DIST)/*
		gzip /tmp/$(DIST).tar
		mv /tmp/$(DIST).tar.gz .
