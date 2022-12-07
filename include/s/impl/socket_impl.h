#ifndef S_SOCKET_IMPL_H
#define S_SOCKET_IMPL_H
#ifdef S_IMPL
#ifdef OPTION_SOCKET

#include "../socket.h"


//
// sdl
//
#ifdef OPTION_SDL
#ifdef PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#endif
#include <limits.h>
#include "SDL2/SDL_net.h"

struct sSocket {
    TCPsocket so;
};
struct sSocketServer {
    TCPsocket so;
};

static void s__socket_close(sSocket *self) {
    if(!s_socket_valid(self))
        return;
    SDLNet_TCP_Close(self->so);
    self->so = NULL;
}

static void s__socketserver_close(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return;
    SDLNet_TCP_Close(self->so);
    self->so = NULL;
}


static ssize s__socket_read(struct sStream_i *stream, void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize read = SDLNet_TCP_Recv(self->so, memory, n);
    if(read <= 0) {
        s_log_error("s_socket_recv failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(read <= n);
    return read;
}

static ssize s__socket_write(struct sStream_i *stream, const void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize written = SDLNet_TCP_Send(self->so, memory, n);
    if(written <= 0) {
        s_log_error("s_socket_send failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(written <= n);
    return written;
}

//
// public
//


bool s_socket_valid(const sSocket *self) {
    return self && self->so!=NULL;
}

bool s_socketserver_valid(const sSocketServer *self) {
    return self && self->so!=NULL;
}

sSocketServer *s_socketserver_new(const char *address, su16 port) {
    sSocketServer *self = s_new0(sSocketServer, 1);

    if(address && strcmp(address, "0.0.0.0") != 0) {
        s_log_warn("s_socketserver_new SDLNet uses always a public server (0.0.0.0)");
    }

    IPaddress ip;
    if(SDLNet_ResolveHost(&ip, NULL, port) == -1) {
        s_log_error("s_socketserver_new failed to resolve host: %s", SDLNet_GetError());
        s_error_set("s_socketserver_new failed");
        s_free(self);
        return s_socketserver_new_invalid();
    }

    self->so = SDLNet_TCP_Open(&ip);
    // impl->so will be NULL on error, so _valid check would fail

    if(!s_socketserver_valid(self)) {
        s_log_error("s_socketserver_new failed to create the server socket");
        s_error_set("s_socketserver_new failed");
        s_free(self);
        return s_socketserver_new_invalid();
    }

    return self;
}

sSocket *s_socketserver_accept(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return s_socket_new_invalid();

    sSocket *client = s_new0(sSocket, 1);

    for(;;) {
        client->so = SDLNet_TCP_Accept(self->so);
        if(client->so)
            break;
        SDL_Delay(50); // sleep some millis
    }

    if(!s_socket_valid(client)) {
        s_log_error("s_socketserver_accept failed, killing the server");
        s_socketserver_kill(&self);
        s_free(client);
        return s_socket_new_invalid();
    }

    IPaddress *client_ip = SDLNet_TCP_GetPeerAddress(client->so);
    if(!client_ip) {
        s_log_warn("s_socketserver_accept failed to get client ip address");
    } else {
        s_log_info("s_socketserver_accept connected with: %s", SDLNet_ResolveIP(client_ip));
    }

    return client;
}


sSocket *s_socket_new(const char *address, su16 port) {
    sSocket *self = s_new0(sSocket, 1);

    if(!address)
        address = "127.0.0.1";

    IPaddress ip;
    if(SDLNet_ResolveHost(&ip, address, port) == -1) {
        s_log_error("s_socketserver_new failed to resolve host: %s", SDLNet_GetError());
        s_error_set("s_socketserver_new failed");
        return s_socket_new_invalid();
    }

    self->so = SDLNet_TCP_Open(&ip);
    // impl->so will be NULL on error, so _valid check would fail

    if(!s_socket_valid(self)) {
        s_log_error("s_socket_new failed to create the connection");
        s_error_set("s_socket_new failed");
        s_free(self);
        return s_socket_new_invalid();
    }

#ifdef PLATFORM_EMSCRIPTEN
    if(s_socket_valid(self)) {
        emscripten_sleep(100);  // sleep and let the connection be opened (blocks, but runs the event loop)
    }
#endif

    return self;
}

void s_socket_set_timeout(sSocket *self, int timeout_ms) {
    s_log_warn("s_socket_set_timeout not supported in sdl socket (can be done with SDLNet_SocketReady...)");
}

#else

//
// UNIX
//
#ifdef PLATFORM_UNIX
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

struct sSocket {
    int so;
};
struct sSocketServer {
    int so;
};

static void s__socket_close(sSocket *self) {
    if(!s_socket_valid(self))
        return;
    close(self->so);
    self->so = -1;
}

static void s__socketserver_close(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return;
    close(self->so);
    self->so = -1;
}

static ssize s__socket_read(struct sStream_i *stream, void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize read = recv(self->so, memory, n, MSG_NOSIGNAL);
    if(read <= 0) {
        s_log_error("s_socket_recv failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(read <= n);
    return read;
}

static ssize s__socket_write(struct sStream_i *stream, const void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize written = send(self->so, memory, n, MSG_NOSIGNAL);
    if(written <= 0) {
        s_log_error("s_socket_send failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(written <= n);
    return written;
}

//
// public
//

bool s_socket_valid(const sSocket *self) {
    return self && self->so>=0;
}

bool s_socketserver_valid(const sSocketServer *self) {
    return self && self->so >= 0;
}

sSocketServer *s_socketserver_new(const char *address, su16 port) {
    sSocketServer *self = s_new0(sSocketServer, 1);

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
            s_log_error("s_socketserver_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            s_error_set("s_socketserver_new failed");
            return s_socketserver_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!s_socketserver_valid(self))
                continue;

            if(bind(self->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                s_socketserver_kill(&self);
                continue;
            }

            // valid socket + bind
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!s_socketserver_valid(self)) {
        s_log_error("s_socketserver_new failed to create the server socket");
        s_error_set("s_socketserver_new failed");
        return s_socketserver_new_invalid();
    }

    // reuse socket port
    {
        int yes = 1;
        setsockopt(self->so, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    }

    int backlog = 10;   // queue size of incoming connections
    if(listen(self->so, backlog) == -1) {
        s_log_error("s_socketserver_new failed to listen");
        s_error_set("s_socketserver_new failed");
        s_socketserver_kill(&self);
    }

    return self;
}

sSocket *s_socketserver_accept(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return s_socket_new_invalid();

    sSocket *client = s_new0(sSocket, 1);

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof addr;
    client->so = accept(self->so, (struct sockaddr *) &addr, &addrlen);

    if(!s_socket_valid(client)) {
        s_log_error("s_socketserver_accept failed, killing the server");
        s_socketserver_kill(&self);
        s_free(client);
        return s_socket_new_invalid();
    }

    char *client_ip = inet_ntoa(((struct sockaddr_in *) &addr)->sin_addr);
    s_log_info("s_socketserver_accept connected with: %s", client_ip);

    return client;
}

sSocket *s_socket_new(const char *address, su16 port) {
    sSocket *self = s_new0(sSocket, 1);

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
            s_log_error("s_socket_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            s_error_set("s_socket_new failed");
            s_free(self);
            return s_socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!s_socket_valid(self))
                continue;

            if(connect(self->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                s_socket_kill(&self);
                continue;
            }

            // valid socket + connect
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!s_socket_valid(self)) {
        s_log_error("s_socket_new failed to create the connection");
        s_error_set("s_socket_new failed");
        s_free(self);
        return s_socket_new_invalid();
    }
    return self;
}

void s_socket_set_timeout(sSocket *self, int timeout_ms) {
    if(!s_socket_valid(self))
        return;
    struct timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    setsockopt(self->so, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv,sizeof tv);
    setsockopt(self->so, SOL_SOCKET, SO_SNDTIMEO, (struct timeval *) &tv,sizeof tv);
}


#endif // PLATFORM_UNIX


//
// mingw - windows
//
#if defined(PLATFORM_MINGW) || defined(PLATFORM_MSVC)
#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <windows.h>



struct sSocket {
    SOCKET so;
};
struct sSocketServer {
    SOCKET so;
};

static void s__socket_close(sSocket *self) {
    if(!s_socket_valid(self))
        return;
    closesocket(self->so);
    self->so = INVALID_SOCKET;
}

static void s__socketserver_close(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return;
    closesocket(self->so);
    self->so = INVALID_SOCKET;
}

static ssize s__socket_read(struct sStream_i *stream, void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize read = recv(self->so, memory, (int) n, 0);
    if(read <= 0) {
        s_log_error("s_socket_recv failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(read <= n);
    return read;
}

static ssize s__socket_write(struct sStream_i *stream, const void *memory, ssize n) {
    sSocket *self = stream->impl;
    if(!s_socket_valid(self))
        return 0;

    ssize written = send(self->so, memory, (int) n, 0);
    if(written <= 0) {
        s_log_error("s_socket_send failed, killing socket...");
        s__socket_close(self);
        return 0;
    }
    assert(written <= n);
    return written;
}

//
// public
//

bool s_socket_valid(const sSocket *self) {
    return self && self->so!=INVALID_SOCKET;
}

bool s_socketserver_valid(const sSocketServer *self) {
    return self && self->so!=INVALID_SOCKET;
}


sSocketServer *s_socketserver_new(const char *address, su16 port) {
    sSocketServer *self = s_new0(sSocketServer, 1);

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
            s_log_error("s_socketserver_new failed, WSAStartup failed: &i", status);
            s_error_set("s_socketserver_new failed");
            s_free(self);
            return s_socketserver_new_invalid();
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
            s_log_error("s_socketserver_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            s_error_set("s_socketserver_new failed");
            return s_socketserver_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!s_socketserver_valid(self))
                continue;

            if(bind(self->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                s_socketserver_kill(&self);
                continue;
            }

            // valid socket + bind
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!s_socketserver_valid(self)) {
        s_log_error("s_socketserver_new failed to create the server socket");
        s_error_set("s_socketserver_new failed");
        return s_socketserver_new_invalid();
    }

    // reuse socket port
    {
        BOOL yes = 1;
        setsockopt(self->so, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof yes);
    }

    int backlog = 10;   // queue size of incoming connections
    if(listen(self->so, backlog) == -1) {
        s_log_error("s_socketserver_new failed to listen");
        s_error_set("s_socketserver_new failed");
        s_socketserver_kill(&self);
    }

    return self;
}


sSocket *s_socketserver_accept(sSocketServer *self) {
    if(!s_socketserver_valid(self))
        return s_socket_new_invalid();

    sSocket *client = s_new0(sSocket, 1);

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof addr;
    client->so = accept(self->so, (struct sockaddr *) &addr, &addrlen);

    if(!s_socket_valid(client)) {
        s_log_error("s_socketserver_accept failed, killing the server");
        s_socketserver_kill(&self);
        s_free(client);
        return s_socket_new_invalid();
    }

    char *client_ip = inet_ntoa(((struct sockaddr_in *) &addr)->sin_addr);
    s_log_info("s_socketserver_accept connected with: %s", client_ip);

    return client;
}


sSocket *s_socket_new(const char *address, su16 port) {
    sSocket *self = s_new0(sSocket, 1);

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
            s_log_error("s_socket_new_server failed, WSAStartup failed: &i", status);
            s_error_set("s_socket_new_server failed");
            s_free(self);
            return s_socket_new_invalid();
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
            s_log_error("s_socket_new failed: getaddrinfo error: %s\n", gai_strerror(status));
            s_error_set("s_socket_new failed");
            s_free(self);
            return s_socket_new_invalid();
        }

        for (struct addrinfo *ai = servinfo; ai != NULL; ai = ai->ai_next) {
            self->so = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
            if (!s_socket_valid(self))
                continue;

            if(connect(self->so, ai->ai_addr, (int) ai->ai_addrlen) == -1) {
                s_socket_kill(&self);
                continue;
            }

            // valid socket + connect
            break;
        }
        freeaddrinfo(servinfo); // free the linked-list
    }

    // no valid address found?
    if(!s_socket_valid(self)) {
        s_log_error("s_socket_new failed to create the connection");
        s_error_set("s_socket_new failed");
        s_free(self);
        return s_socket_new_invalid();
    }
    return self;
}

void s_socket_set_timeout(sSocket *self, int timeout_ms) {
    if(!s_socket_valid(self))
        return;
    DWORD time = timeout_ms;
    setsockopt(self->so, SOL_SOCKET, SO_RCVTIMEO, (char*) &time, sizeof time);
    setsockopt(self->so, SOL_SOCKET, SO_SNDTIMEO, (char*) &time, sizeof time);
}

#endif // Windows

#endif //OPTION_SDL



//
// for all:
//

static bool s__socket_valid(struct sStream_i *stream) {
    sSocket *self = stream->impl;
    return s_socket_valid(self);
}

void s_socketserver_kill(sSocketServer **self_ptr) {
    sSocketServer *self = *self_ptr;
    s__socketserver_close(self);
    s_free(self);
    *self_ptr = NULL;
}

void s_socket_kill(sSocket **self_ptr) {
    sSocket *self = *self_ptr;
    s__socket_close(self);
    s_free(self);
    *self_ptr = NULL;
}

sStream_i s_socket_get_stream(sSocket *self) {
    return (sStream_i) {
            .impl = self,
            .opt_read_try = s__socket_read,
            .opt_write_try = s__socket_write,
            .valid = s__socket_valid
    };
}


#endif //OPTION_SOCKET
#endif //S_IMPL
#endif //S_SOCKET_IMPL_H
