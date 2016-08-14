#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "server.h"


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Wrong argument count!\nUsage example: hashtable <host> <port>\n");
        return 1;
    }
    // Start server
    start_server(argv[1], argv[2]);
    return 0;
}
