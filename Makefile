CFLAGS = -Wall -g -std=gnu99 -O0
LIBS = -lm
SRCDIR = src
BIN = main
BIN_NAME = hashtable
OBJS = prime.o hash.o table.o server.o
DEFS =

$(BIN): $(OBJS) $(SRCDIR)/$(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(SRCDIR)/$(BIN).c -o $(BIN_NAME) $(LIBS)

%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
