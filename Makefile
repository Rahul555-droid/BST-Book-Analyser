CPP = bst_analyser.cpp
EXE = bst_analyser

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
WFLAG = -w

$(EXE):
	$(CC) $(LFLAGS) $(CPP) -o $(EXE)

clean:
	rm *.o $(EXE) *~ -v
