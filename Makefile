# File:          Makefile
# Author:        Henry M. Walker
# Created:       20 April 2008
# Simplified:    18 November 2011
# Adapted:       21 November 2017 by Aabid Shamji
#----------------------------------------------------------------------------
# Use the clang compiler
CC = clang

# Set compilation flags
#   -ansi       check syntax against the American National Standard for C
#   -g          include debugging information
#   -Wall       report all warnings
#   -std=gnu99  use the GNU extensions of the C99 standard
CFLAGS =

FLAGS = -ansi -g -Wall -std=gnu99

#----------------------------------------------------------------------------
# build rules:
#
# Each rule takes the following form  (Note there MUST be a tab,
# as opposed to several spaces, preceeding each command.
#
# target_name:  dependency_list
#	command(s)

all: test_listarray

# List program components, what they depend on, and how to compile or link each

test_listarray:  test_listarray.o listarray.o
	$(CC) $(CFLAGS) -o $@ $^

test_listarray.o:  test_listarray.c listarray.h listarray.c
	$(CC) $(FLAGS) $(CFLAGS) -c $<

listarray.o:  listarray.c listarray.h
	$(CC) $(FLAGS) -c $<

#----------------------------------------------------------------------------
# cleanup rules: To invoke this command, type "make clean".
# Use this target to clean up your directory, deleting (without warning)
#   the built program, object files, old emacs source versions, and core dumps.

clean:
	rm -f test_listarray *.o *~ core*
