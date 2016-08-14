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


uint8_t start_server(char *listen_host, char *listen_port) {
    int status, sockfd, yes = 1;
    struct addrinfo hints, *myaddr;

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
    char read_buffer[MAX_DATASIZE];
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
        }
    }

    return 0;
}
