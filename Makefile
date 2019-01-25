#
# Quinn Pham
# Makefile for Gerp
# Project 2 (fall 2018)
#

CC = clang++
CFLAGS = -Wall -Wextra -O2 -c -std=c++11
OBJS = main.o Index.o HashTable.o Word.o LinkedList.o FSTree.o DirNode.o 
DEPS = Index.h HashTable.h Word.h LinkedList.h

# end file
gerp: $(OBJS)
	$(CC) -o gerp $(OBJS)

# compile
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

# clean
clean:
	rm -rf gerp *.o *~ core*

# provide
provide:
	provide comp15 gerp-phase2 Makefile README main.cpp Index.h Index.cpp \
	HashTable.h HashTable.cpp Word.h Word.cpp LinkedList.h LinkedList.cpp \
	NodeType.h FSTree.o DirNode.o 
