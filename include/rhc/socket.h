#ifndef RHC_SOCKET_H
#define RHC_SOCKET_H

#include <assert.h>
#include <stddef.h>
#include <errno.h>
#include "log.h"
#include "error.h"


struct Socket;
typedef struct Socket Socket;

static bool socket_valid(Socket self);
static Socket socket_new_invalid();
static void socket_kill(Socket *self);

static Socket socket_new_server(const char *addr, const char *port);
static Socket socket_new_client(const char *addr, const char *port);

static Socket socket_server_accept(Socket *self);

static bool socket_recv(Socket *self, void *msg, size_t size);
static bool socket_send(Socket *self, const void *msg, size_t size);


#ifdef WIN32
#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <windows.h>

struct Socket {
    SOCKET so;
};

static bool socket_valid(Socket self) {
    return self.so != INVALID_SOCKET;
}

static Socket socket_new_invalid() {
    return (Socket) {INVALID_SOCKET};
}

static void socket_kill(Socket *self) {
    closesocket(self->so);
    self->so = INVALID_SOCKET;
}

static Socket socket_new_server(const char *addr, const char *port) {
    Socket self = {0};

    // winsock startup (can be called multiple times...)
    {
        WORD version = MAKEWORD(2, 2);
        WSADATA wsadata;
        int status = WSAStartup(version, &wsadata);
        if(status != 0) {
            log_error("socket_new_server failed, WSAStartup failed: &i", status);
            rhc_error = "socket_new_server failed";
            return socket_new_invalid();
        }
    }

    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
    };
//    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // find a valid address and create a socket on it
    {
        struct addrinfo *servinfo;
        int status = getaddrinfo(addr, port, &hints, &servinfo);
        if (status != 0) {
            log_error("socket_new_server failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "socket_new_server failed";
            return socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self.so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!socket_valid(self))
                continue;

            if(bind(self.so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                socket_kill(&self);
                continue;
            }

            // valid socket + bind
            break;
        }

        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!socket_valid(self)) {
        log_error("socket_new_server failed to create the server socket");
        rhc_error = "socket_new_server failed";
        return socket_new_invalid();
    }

    // reuse socket port
    {
        BOOL yes = 1;
        setsockopt(self.so, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof yes);
    }

    int backlog = 10;   // queue size of incoming connections
    if(listen(self.so, backlog) == -1) {
        log_error("socket_new_server failed to listen");
        rhc_error = "socket_new_server failed";
        socket_kill(&self);
    }

    return self;
}

static Socket socket_new_client(const char *addr, const char *port) {
    Socket self = {0};

    // winsock startup (can be called multiple times...)
    {
        WORD version = MAKEWORD(2, 2);
        WSADATA wsadata;
        int status = WSAStartup(version, &wsadata);
        if(status != 0) {
            log_error("socket_new_server failed, WSAStartup failed: &i", status);
            rhc_error = "socket_new_server failed";
            return socket_new_invalid();
        }
    }

    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
    };

    // find a valid address and connect to it
    {
        struct addrinfo *servinfo;
        int status = getaddrinfo(addr, port, &hints, &servinfo);
        if (status != 0) {
            log_error("socket_new_client failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "socket_new_client failed";
            return socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self.so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!socket_valid(self))
                continue;

            if(connect(self.so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                socket_kill(&self);
                continue;
            }

            // valid socket + connect
            break;
        }

        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!socket_valid(self)) {
        log_error("socket_new_client failed to create the connection");
        rhc_error = "socket_new_client failed";
        return socket_new_invalid();
    }

    return self;
}

static Socket socket_server_accept(Socket *self) {
    if(!socket_valid(*self))
        return socket_new_invalid();

    Socket client = {0};

    struct sockaddr_storage addr;
    int addrlen = sizeof addr;
    client.so = accept(self->so, (struct sockaddr *) &addr, &addrlen);

    if(!socket_valid(client)) {
        log_error("socket_server_accept failed, killing the server");
        socket_kill(self);
        return socket_new_invalid();
    }

    char *client_ip = inet_ntoa(((struct sockaddr_in *) &addr)->sin_addr);
    log_info("socket_server_accept connected with: %s", client_ip);

    return client;
}


static bool socket_recv(Socket *self, void *msg, size_t size) {
    if(!socket_valid(*self))
        false;

    char *buf = msg;
    while(size > 0) {
        int n = recv(self->so, buf, (int) size, 0);
        if(n <= 0) {
            log_error("socket_recv failed, killing socket...");
            socket_kill(self);
            return false;
        }
        assert(n <= size);
        buf += n;
        size -= n;
    }
    return true;
}

static bool socket_send(Socket *self, const void *msg, size_t size) {
    if(!socket_valid(*self))
        false;

    const char *buf = msg;
    while(size > 0) {
        int n = send(self->so, buf, (int) size, 0);
        if(n <= 0) {
            log_error("socket_send failed, killing socket...");
            socket_kill(self);
            return false;
        }
        assert(n <= size);

        buf += n;
        size -= n;
    }
    return true;
}

#endif


#endif //RHC_SOCKET_H
