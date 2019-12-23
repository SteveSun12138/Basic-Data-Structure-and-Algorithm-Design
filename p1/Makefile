CC = g++
  
CFLAG = -c -Wall

all: SearchNewBooks

SearchNewBooks: SearchNewBooks.o
	$(CC) SearchNewBooks.o -o SearchNewBooks

SearchNewBooks.o: SearchNewBooks.cc
	$(CC) $(CFLAG) SearchNewBooks.cc

clean:
	rm -rf *o SearchNewBooks

