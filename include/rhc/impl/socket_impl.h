#ifndef RHC_SOCKET_IMPL_H
#define RHC_SOCKET_IMPL_H
#ifdef OPTION_SOCKET

#include <assert.h>
#include "../socket.h"




//
// sdl
//
#ifdef OPTION_SDL
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <limits.h>
#include "SDL2/SDL_net.h"
typedef struct {
    TCPsocket so;   // is a pointer type
} SDLSocket;
_Static_assert(sizeof (SDLSocket) <= RHC_SOCKET_STORAGE_SIZE, "storage not big enough");


static size_t socket_recv(Stream_i stream, void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        return 0;

    assume(size < INT_MAX, "sdl socket uses int instead of size_t");
    SDLSocket *impl = (SDLSocket *) self->impl_storage;

    int n = SDLNet_TCP_Recv(impl->so, msg, size);
    if(n <= 0) {
        log_error("rhc_socket_recv failed, killing socket...");
        SDLNet_TCP_Close(impl->so);
        impl->so = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static size_t socket_send(Stream_i stream, const void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        false;

    assume(size < INT_MAX, "sdl socket uses int instead of size_t");
    SDLSocket *impl = (SDLSocket *) self->impl_storage;

    int n = SDLNet_TCP_Send(impl->so, msg, size);
    if(n <= 0) {
        log_error("rhc_socket_send failed, killing socket...");
        SDLNet_TCP_Close(impl->so);
        impl->so = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static Stream_i socket_create_stream(Socket *self) {
    return (Stream_i) {
            self, socket_recv, socket_send
    };
}
//
// public
//

bool rhc_socketserver_valid(SocketServer self) {
    SDLSocket *impl = (SDLSocket *) self.impl_storage;
    return impl->so != NULL;
}

SocketServer rhc_socketserver_new_invalid() {
    SocketServer self = {0};
    SDLSocket *impl = (SDLSocket *) self.impl_storage;
    impl->so = NULL;
    return self;
}

SocketServer rhc_socketserver_new(const char *address, uint16_t port) {
    SocketServer self = {0};
    SDLSocket *impl = (SDLSocket *) self.impl_storage;

    if(address && strcmp(address, "0.0.0.0") != 0) {
        log_warn("rhc_socketserver_new SDLNet uses always a public server (0.0.0.0)");
    }
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip, NULL, port) == -1) {
        log_error("rhc_socketserver_new failed to resolve host: %s", SDLNet_GetError());
        rhc_error = "rhc_socketserver_new failed";
        return rhc_socketserver_new_invalid();
    }

    impl->so = SDLNet_TCP_Open(&ip);
    // impl->so will be NULL on error, so _valid check would fail

    if(!rhc_socketserver_valid(self)) {
        log_error("rhc_socketserver_new failed to create the server socket");
        rhc_error = "rhc_socketserver_new failed";
        return rhc_socketserver_new_invalid();
    }

    return self;
}

void rhc_socketserver_kill(SocketServer *self) {
    SDLSocket *impl = (SDLSocket *) self->impl_storage;
    SDLNet_TCP_Close(impl->so);
    *self = rhc_socketserver_new_invalid();
}

Socket *rhc_socketserver_accept_a(SocketServer *self, Allocator_i a) {
    if(!rhc_socketserver_valid(*self))
        return rhc_socket_new_invalid();

    SDLSocket *impl = (SDLSocket *) self->impl_storage;

    Socket *client = a.calloc(a, sizeof *client);
    client->stream = socket_create_stream(client);
    client->allocator = a;
    SDLSocket *client_impl = (SDLSocket *) client->impl_storage;

    for(;;) {
        client_impl->so = SDLNet_TCP_Accept(impl->so);
        if(client_impl->so)
            break;
        SDL_Delay(50); // sleep some millis
    };

    if(!rhc_socket_valid(client)) {
        log_error("rhc_socketserver_accept failed, killing the server");
        rhc_socketserver_kill(self);
        a.free(a, client);
        return rhc_socket_new_invalid();
    }

    IPaddress *client_ip = SDLNet_TCP_GetPeerAddress(client_impl->so);
    if(!client_ip) {
        log_warn("rhc_socketserver_accept failed to get client ip address");
    } else {
        log_info("rhc_socketserver_accept connected with: %s", SDLNet_ResolveIP(client_ip));
    }

    return client;
}

bool rhc_socket_valid(const Socket *self) {
    if(!self)
        return false;
    SDLSocket *impl = (SDLSocket *) self->impl_storage;
    return impl->so != NULL;
}

Socket *rhc_socket_new_invalid() {
    return NULL;
}

Socket *rhc_socket_new_a(const char *address, uint16_t port, Allocator_i a) {
    Socket *self = a.calloc(a, sizeof *self);
    self->stream = socket_create_stream(self);
    self->allocator = a;
    SDLSocket *impl = (SDLSocket *) self->impl_storage;

    IPaddress ip;
    if(SDLNet_ResolveHost(&ip, address, port) == -1) {
        log_error("rhc_socketserver_new failed to resolve host: %s", SDLNet_GetError());
        rhc_error = "rhc_socketserver_new failed";
        return rhc_socket_new_invalid();
    }

    impl->so = SDLNet_TCP_Open(&ip);
    // impl->so will be NULL on error, so _valid check would fail

    if(!rhc_socket_valid(self)) {
        log_error("rhc_socket_new failed to create the connection");
        rhc_error = "rhc_socket_new failed";
        a.free(a, self);
        return rhc_socket_new_invalid();
    }

#ifdef __EMSCRIPTEN__
    if(rhc_socket_valid(self)) {
        emscripten_sleep(100);  // sleep and let the connection be opened (blocks, but runs the event loop)
    }
#endif

    return self;
}

void rhc_socket_kill(Socket **self_ptr) {
    Socket *self = *self_ptr;
    if(!self)
        return;
    SDLSocket *impl = (SDLSocket *) self->impl_storage;
    SDLNet_TCP_Close(impl->so);
    self->allocator.free(self->allocator, self);
    *self_ptr = NULL;
}
#else

//
// UNIX
//
#ifdef unix
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct {
    int so;
} UnixSocket;
_Static_assert(sizeof (UnixSocket) <= RHC_SOCKET_STORAGE_SIZE, "storage not big enough");

static size_t socket_recv(Stream_i stream, void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        return 0;

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    ssize_t n = recv(impl->so, msg, size, MSG_NOSIGNAL);
    if(n <= 0) {
        log_error("rhc_socket_recv failed, killing socket...");
        close(impl->so);
        impl->so = -1;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static size_t socket_send(Stream_i stream, const void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        false;

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    ssize_t n = send(impl->so, msg, size, MSG_NOSIGNAL);
    if(n <= 0) {
        log_error("rhc_socket_send failed, killing socket...");
        close(impl->so);
        impl->so = -1;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static Stream_i socket_create_stream(Socket *self) {
    return (Stream_i) {
        self, socket_recv, socket_send
    };
}
//
// public
//

bool rhc_socketserver_valid(SocketServer self) {
    UnixSocket *impl = (UnixSocket *) self.impl_storage;
    return impl->so >= 0;
}

SocketServer rhc_socketserver_new_invalid() {
    SocketServer self = {0};
    UnixSocket *impl = (UnixSocket *) self.impl_storage;
    impl->so = -1;
    return self;
}

SocketServer rhc_socketserver_new(const char *address, uint16_t port) {
    SocketServer self = {0};
    UnixSocket *impl = (UnixSocket *) self.impl_storage;

    if(!address)
        address = "127.0.0.1";

    char port_str[8];
    snprintf(port_str, 8, "%i", port);

    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
    };
//    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    // find a valid address and create a socket on it
    {
        struct addrinfo *servinfo;
        int status = getaddrinfo(address, port_str, &hints, &servinfo);
        if (status != 0) {
            log_error("rhc_socketserver_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "rhc_socketserver_new failed";
            return rhc_socketserver_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            impl->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!rhc_socketserver_valid(self))
                continue;

            if(bind(impl->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                rhc_socketserver_kill(&self);
                continue;
            }

            // valid socket + bind
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!rhc_socketserver_valid(self)) {
        log_error("rhc_socketserver_new failed to create the server socket");
        rhc_error = "rhc_socketserver_new failed";
        return rhc_socketserver_new_invalid();
    }

    // reuse socket port
    {
        int yes = 1;
        setsockopt(impl->so, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    }

    int backlog = 10;   // queue size of incoming connections
    if(listen(impl->so, backlog) == -1) {
        log_error("rhc_socketserver_new failed to listen");
        rhc_error = "rhc_socketserver_new failed";
        rhc_socketserver_kill(&self);
    }

    return self;
}

void rhc_socketserver_kill(SocketServer *self) {
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    close(impl->so);
    *self = rhc_socketserver_new_invalid();
}

Socket *rhc_socketserver_accept_a(SocketServer *self, Allocator_i a) {
    if(!rhc_socketserver_valid(*self))
        return rhc_socket_new_invalid();

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    Socket *client = a.calloc(a, sizeof *client);
    client->stream = socket_create_stream(client);
    client->allocator = a;
    UnixSocket *client_impl = (UnixSocket *) client->impl_storage;

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof addr;
    client_impl->so = accept(impl->so, (struct sockaddr *) &addr, &addrlen);

    if(!rhc_socket_valid(client)) {
        log_error("rhc_socketserver_accept failed, killing the server");
        rhc_socketserver_kill(self);
        a.free(a, client);
        return rhc_socket_new_invalid();
    }

    char *client_ip = inet_ntoa(((struct sockaddr_in *) &addr)->sin_addr);
    log_info("rhc_socketserver_accept connected with: %s", client_ip);

    return client;
}

bool rhc_socket_valid(const Socket *self) {
    if(!self)
        return false;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    return impl->so >= 0;
}

Socket *rhc_socket_new_invalid() {
    return NULL;
}

Socket *rhc_socket_new_a(const char *address, uint16_t port, Allocator_i a) {
    Socket *self = a.calloc(a, sizeof *self);
    self->stream = socket_create_stream(self);
    self->allocator = a;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    if(!address)
        address = "127.0.0.1";

    char port_str[8];
    snprintf(port_str, 8, "%i", port);

    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
    };

    // find a valid address and connect to it
    {
        struct addrinfo *servinfo;
        int status = getaddrinfo(address, port_str, &hints, &servinfo);
        if (status != 0) {
            log_error("rhc_socket_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "rhc_socket_new failed";
            a.free(a, self);
            return rhc_socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            impl->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!rhc_socket_valid(self))
                continue;

            if(connect(impl->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                rhc_socket_kill(&self);
                continue;
            }

            // valid socket + connect
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!rhc_socket_valid(self)) {
        log_error("rhc_socket_new failed to create the connection");
        rhc_error = "rhc_socket_new failed";
        a.free(a, self);
        return rhc_socket_new_invalid();
    }
    return self;
}

void rhc_socket_kill(Socket **self_ptr) {
    Socket *self = *self_ptr;
    if(!self)
        return;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    close(impl->so);
    self->allocator.free(self->allocator, self);
    *self_ptr = NULL;
}
#endif //unix


//
// mingw - windows
//
#ifdef _WIN32
#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <windows.h>

typedef struct {
    SOCKET so;
} UnixSocket;
_Static_assert(sizeof (UnixSocket) <= RHC_SOCKET_STORAGE_SIZE, "storage not big enough");

static size_t socket_recv(Stream_i stream, void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        return 0;

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    int n = recv(impl->so, msg, (int) size, 0);
    if(n <= 0) {
        log_error("rhc_socket_recv failed, killing socket...");
        closesocket(impl->so);
        impl->so = INVALID_SOCKET;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static size_t socket_send(Stream_i stream, const void *msg, size_t size) {
    Socket *self = stream.user_data;
    if(!rhc_socket_valid(self))
        false;

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    int n = send(impl->so, msg, (int) size, 0);
    if(n <= 0) {
        log_error("rhc_socket_send failed, killing socket...");
        closesocket(impl->so);
        impl->so = INVALID_SOCKET;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static Stream_i socket_create_stream(Socket *self) {
    return (Stream_i) {
        self, socket_recv, socket_send
    };
}
//
// public
//

bool rhc_socketserver_valid(SocketServer self) {
    UnixSocket *impl = (UnixSocket *) self.impl_storage;
    return impl->so != INVALID_SOCKET;
}

SocketServer rhc_socketserver_new_invalid() {
    SocketServer self = {0};
    UnixSocket *impl = (UnixSocket *) self.impl_storage;
    impl->so = INVALID_SOCKET;
    return self;
}

SocketServer rhc_socketserver_new(const char *address, uint16_t port) {
    SocketServer self = {0};
    UnixSocket *impl = (UnixSocket *) self.impl_storage;

    if(!address)
        address = "127.0.0.1";

    char port_str[8];
    snprintf(port_str, 8, "%i", port);

    // winsock startup (can be called multiple times...)
    {
        WORD version = MAKEWORD(2, 2);
        WSADATA wsadata;
        int status = WSAStartup(version, &wsadata);
        if(status != 0) {
            log_error("rhc_socketserver_new failed, WSAStartup failed: &i", status);
            rhc_error = "rhc_socketserver_new failed";
            return rhc_socketserver_new_invalid();
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
        int status = getaddrinfo(address, port_str, &hints, &servinfo);
        if (status != 0) {
            log_error("rhc_socketserver_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "rhc_socketserver_new failed";
            return rhc_socketserver_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            impl->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!rhc_socketserver_valid(self))
                continue;

            if(bind(impl->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                rhc_socketserver_kill(&self);
                continue;
            }

            // valid socket + bind
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!rhc_socketserver_valid(self)) {
        log_error("rhc_socketserver_new failed to create the server socket");
        rhc_error = "rhc_socketserver_new failed";
        return rhc_socketserver_new_invalid();
    }

    // reuse socket port
    {
        BOOL yes = 1;
        setsockopt(impl->so, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof yes);
    }

    int backlog = 10;   // queue size of incoming connections
    if(listen(impl->so, backlog) == -1) {
        log_error("rhc_socketserver_new failed to listen");
        rhc_error = "rhc_socketserver_new failed";
        rhc_socketserver_kill(&self);
    }

    return self;
}

void rhc_socketserver_kill(SocketServer *self) {
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    closesocket(impl->so);
    *self = rhc_socketserver_new_invalid();
}

Socket *rhc_socketserver_accept_a(SocketServer *self, Allocator_i a) {
    if(!rhc_socketserver_valid(*self))
        return rhc_socket_new_invalid();

    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    Socket *client = a.calloc(a, sizeof *client);
    client->stream = socket_create_stream(client);
    client->allocator = a;
    UnixSocket *client_impl = (UnixSocket *) client->impl_storage;

    struct sockaddr_storage addr;
    int addrlen = sizeof addr;
    client_impl->so = accept(impl->so, (struct sockaddr *) &addr, &addrlen);

    if(!rhc_socket_valid(client)) {
        log_error("rhc_socketserver_accept failed, killing the server");
        rhc_socketserver_kill(self);
        a.free(a, client);
        return rhc_socket_new_invalid();
    }

    char *client_ip = inet_ntoa(((struct sockaddr_in *) &addr)->sin_addr);
    log_info("rhc_socketserver_accept connected with: %s", client_ip);

    return client;
}

bool rhc_socket_valid(const Socket *self) {
    if(!self)
        return false;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    return impl->so != INVALID_SOCKET;
}

Socket *rhc_socket_new_invalid() {
    return NULL;
}

Socket *rhc_socket_new_a(const char *address, uint16_t port, Allocator_i a) {
    Socket *self = a.calloc(a, sizeof *self);
    self->stream = socket_create_stream(self);
    self->allocator = a;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;

    if(!address)
        address = "127.0.0.1";

    char port_str[8];
    snprintf(port_str, 8, "%i", port);

    // winsock startup (can be called multiple times...)
    {
        WORD version = MAKEWORD(2, 2);
        WSADATA wsadata;
        int status = WSAStartup(version, &wsadata);
        if(status != 0) {
            log_error("rhc_socket_new_server failed, WSAStartup failed: &i", status);
            rhc_error = "rhc_socket_new_server failed";
            a.free(a, self);
            return rhc_socket_new_invalid();
        }
    }

    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM
    };

    // find a valid address and connect to it
    {
        struct addrinfo *servinfo;
        int status = getaddrinfo(address, port_str, &hints, &servinfo);
        if (status != 0) {
            log_error("rhc_socket_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            rhc_error = "rhc_socket_new failed";
            a.free(a, self);
            return rhc_socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            impl->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!rhc_socket_valid(self))
                continue;

            if(connect(impl->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                rhc_socket_kill(&self);
                continue;
            }

            // valid socket + connect
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!rhc_socket_valid(self)) {
        log_error("rhc_socket_new failed to create the connection");
        rhc_error = "rhc_socket_new failed";
        a.free(a, self);
        return rhc_socket_new_invalid();
    }
    return self;
}

void rhc_socket_kill(Socket **self_ptr) {
    Socket *self = *self_ptr;
    if(!self)
        return;
    UnixSocket *impl = (UnixSocket *) self->impl_storage;
    closesocket(impl->so);
    self->allocator.free(self->allocator, self);
    *self_ptr = NULL;
}
#endif //WIN32

#endif //OPTION_SDL
#endif //OPTION_SOCKET
#endif //RHC_SOCKET_IMPL_H
