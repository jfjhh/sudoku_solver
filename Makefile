CC = gcc
override CFLAGS = -Wall -g
OBJECTS = main.c sudoku.c testSudoku.c
EXE = sudokusolver

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -r *.o *.dSYM 2> /dev/null

