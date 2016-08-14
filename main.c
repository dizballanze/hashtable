#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "server.h"


int main(void) {
    char port[] = "31337";
    char host[] = "0.0.0.0";
    // Start server
    start_server(host, port);
    return 0;
}
