CC=clang++
CFLAGS=-Wall -O3
PROG=run.exe
ARGS=scores.txt

all: assign1.o
	$(CC) -o $(PROG) assign1.o

assign1.o: assign1.cpp
	$(CC) $(CFLAGS) -c assign1.cpp

clean:
	rm -f *.o $(PROG)

run: $(PROG)
	./$(PROG) $(ARGS) 

