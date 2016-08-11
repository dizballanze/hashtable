CFLAGS = -Wall -g -std=gnu99
LIBS = -lm
BIN = hashtable
OBJS = prime.o
DEFS =

$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(LIBS) $(OBJS) $(BIN).c -o $(BIN)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
