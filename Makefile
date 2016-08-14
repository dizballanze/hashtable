CFLAGS = -Wall -g -std=gnu99
LIBS = -lm
BIN = main
BIN_NAME = hashtable
OBJS = prime.o hash.o table.o server.o
DEFS =

$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(LIBS) $(OBJS) $(BIN).c -o $(BIN_NAME)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
