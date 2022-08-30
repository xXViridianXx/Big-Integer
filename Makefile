#------------------------------------------------------------------------------
#  Makefile for Matrix ADT
#
#  make             makes Sparse
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -g -std=c++17 -Wall
HEADERS = $(wildcard *.h)
MODULES = List BigInteger
OBJECTS_AC = $(AC).o $(patsubst %, %.o, ${MODULES})
OBJECTS_BI = $(BI).o $(patsubst %, %.o, ${MODULES})
OBJECTS_LT = $(LT).o $(patsubst %, %.o, ${MODULES})
AC = Arithmetic
BI = BigIntegerTest
LT =  ListTest

.PHONY: all done

all: AC BI LT

AC: $(AC)
BI: $(BI)
LT: $(LT)

$(AC): $(OBJECTS_AC)
	$(CC) -o $@ $^

$(BI): $(OBJECTS_BI)
	$(CC) -o $@ $^

$(LT): $(OBJECTS_LT)
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -c

clean: tidy
	$(RM) $(AC) $(BI) $(LT)

tidy:
	$(RM) $(OBJECTS_AC) $(OBJECTS_BI) $(OBJECTS_LT)

check:
	valgrind --leak-check=full ./Arithmetic 

test:
	valgrind --leak-check=full ./BigIntegerTest


