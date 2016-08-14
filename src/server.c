/* Simple non-blocking TCP server */
#include "server.h"


/* Make specified socket non blocking */
int make_socket_non_blocking(int sfd) {
    int curr_flags, result;
    // Get current socket flags
    curr_flags = fcntl(sfd, F_GETFL, 0);
    if (curr_flags == -1) {
        perror("fcntl");
        return -1;
    }

    result = fcntl(sfd, F_SETFL, curr_flags | O_NONBLOCK);
    if (result == -1) {
        perror("fcntl");
        return -1;
    }
    return 0;
}

/* Remove line breaks from the end of the string */
void remove_linebreak(char *str) {
    char *linebreak;
    linebreak = strrchr(str, '\n');
    if (linebreak)
        *linebreak = '\0';
    linebreak = strrchr(str, '\r');
    if (linebreak)
        *linebreak = '\0';
}

/* SET command handler */
void set_handler(hash_table *table, char *key, char *value) {
    char *key_holder = malloc(strlen(key));
    char *value_holder = malloc(strlen(value));
    strcpy(key_holder, key);
    strcpy(value_holder, value);
    hash_table_insert(table, key_holder, value_holder);
    // Increase table if it half-filled
    if ((table->used_items_count / table->size) >= 0.5) {
        hash_table_extend(table, table->size * 2);
    }
}

/* GET command handler */
char *get_handler(hash_table *table, char *key) {
    hash_table_item *needle;
    needle = hash_table_search(table, key);
    if (!needle) {
        return NULL;
    }
    return needle->value;
}

/* DELETE command handler */
uint8_t delete_handler(hash_table *table, char *key) {
    return hash_table_delete_item_by_key(table, key);
}

/* COUNT command handler */
uint64_t count_handler(hash_table *table) {
    return table->not_deleted_used_items_count;
}

/* Process user command */
uint8_t process_user_input(hash_table *table, char *input, char *resp_buffer) {
    char *command;
    char *key;
    char *value;
    command = strtok(input, " \r\n");
    if (!command) {
        sprintf(resp_buffer, "Error: Empty command\n");
        return 0;
    }
    if (strcmp(command, "SET") == 0) {
        key = strtok(NULL, " ");
        value = key + strlen(key) + 1;
        remove_linebreak(value);
        printf("SET command with key %s and value %s\n", key, value);
        set_handler(table, key, value);
        sprintf(resp_buffer, "DONE\n");
        return 1;
    }
    if (strcmp(command, "GET") == 0) {
        key = strtok(NULL, " ");
        remove_linebreak(key);
        value = get_handler(table, key);
        if (value) {
            sprintf(resp_buffer, "DONE\n%s\n", value);
        } else {
            sprintf(resp_buffer, "NOT FOUND\n");
        }
        return 1;
    }
    if (strcmp(command, "DELETE") == 0) {
        key = strtok(NULL, " ");
        remove_linebreak(key);
        if (delete_handler(table, key)) {
            sprintf(resp_buffer, "DONE\n");
        } else {
            sprintf(resp_buffer, "NOT FOUND\n");
        }
        return 1;
    }
    if (strcmp(command, "COUNT") == 0) {
        sprintf(resp_buffer, "DONE\n%" PRIu64 "\n", count_handler(table));
        return 1;
    }
    printf("Unknown command: %s\n", command);
    sprintf(resp_buffer, "Error: Unknown command\n");
    return 0;
}


uint8_t start_server(char *listen_host, char *listen_port) {
    hash_table table;
    int status, sockfd, yes = 1;
    struct addrinfo hints, *myaddr;

    // Initialize hash table
    hash_table_init(&table, 128);

    // Get server (self) address info
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(listen_host, listen_port, &hints, &myaddr))) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // Create socket fd
    sockfd = socket(myaddr->ai_family, myaddr->ai_socktype, myaddr->ai_protocol);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    // Configure socket
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }

    // Bind to port
    if (bind(sockfd, myaddr->ai_addr, myaddr->ai_addrlen) == -1) {
        perror("bind");
        return 1;
    }
    freeaddrinfo(myaddr);

    // Make server socket non blocking
    if (make_socket_non_blocking(sockfd)) {
        return 1;
    }

    // Listen for connections
    if (listen(sockfd, MAX_PENDING_CONNS) == -1) {
        perror("listen");
        return 1;
    }
    printf("Ready to accept connection on %s:%s...\n", listen_host, listen_port);

    // Event loop
    int epfd, received, received_events;
    int client_fd;
    size_t sended;
    char *read_buffer = malloc(MAX_DATASIZE);
    char *resp_buffer = malloc(MAX_RESP_SIZE);
    struct epoll_event epevent, curr_event;
    struct epoll_event events[MAX_EVENTS];
    
    // Create epoll instance
    epfd = epoll_create1(0);
    if (epfd < 0) {
        perror("epoll_create1");
        return 1;
    }

    // Listen to server socket read event
    epevent.data.fd = sockfd;
    epevent.events = EPOLLIN;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &epevent)) {
        perror("epoll_ctl");
        return 1;
    }

    while (1) {
        // Wait for events
        received_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (received_events == -1) {
            perror("epoll_wait");
            return 1;
        }
        for (int i=0; i < received_events; i++) {
            curr_event = events[i];
            // Accept new connection
            if (curr_event.data.fd == sockfd) {
                printf("New connection\n");
                struct sockaddr_storage client_addr;
                socklen_t addr_size;
                addr_size = sizeof client_addr;
                client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
                if (client_fd == -1) {
                    perror("accept");
                    continue;
                }
                if (make_socket_non_blocking(client_fd)) {
                    return 1;
                }
                // Add client descriptor to epoll
                epevent.data.fd = client_fd;
                epevent.events = EPOLLIN;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &epevent)) {
                    perror("epoll_ctl");
                    return 1;
                }
                continue;
            }
            if ((received = recv(client_fd, read_buffer, MAX_DATASIZE-1, 0)) < 0) {
                perror("recv");
                continue;
            }
            // Client close connection
            if (received == 0) {
                printf("Connection closed\n");
                close(client_fd);
                continue;
            }
            read_buffer[received] = '\0';
            printf("Message: %s\n", read_buffer);
            process_user_input(&table, read_buffer, resp_buffer);
            sended = send(client_fd, resp_buffer, strlen(resp_buffer), 0);
            if (sended != strlen(resp_buffer)) {
                perror("send");
                continue;
            }
        }
    }

    free(read_buffer);
    free(resp_buffer);
    return 0;
}
