#ifndef S_SOCKET_H
#define S_SOCKET_H
#ifdef OPTION_SOCKET

//
// TCP sockets
//

#include "stream.h"

typedef struct sSocket sSocket;

typedef struct sSocketServer sSocketServer;


//
// SocketServer
//

// returns true if the SocketServer is valid to use
S_EXPORT
bool s_socketserver_valid(const sSocketServer *self);

// returns a new invalid SocketServer
static sSocketServer *s_socketserver_new_invalid() {
    return NULL;
}

// Creates a new SocketServer
// address may be "localhost" or "127.0.0.1", to only enable local connections
// address may be "0.0.0.0" to enable all incoming connections
// if address is NULL, "127.0.0.1" is used
// SDLs implementation is only able to use "0.0.0.0"
S_EXPORT
sSocketServer *s_socketserver_new(const char *address, su16 port);

// kills the socketserver and sets it invalid
S_EXPORT
void s_socketserver_kill(sSocketServer **self_ptr);

// Accepts a new client for a SocketServer
// If an error occurs, SocketServer will be set invalid and false is returned
S_EXPORT
sSocket *s_socketserver_accept(sSocketServer *self);



//
// Socket
//

// returns true if the Socket is valid to use
S_EXPORT
bool s_socket_valid(const sSocket *self);

// returns a new invalid Socket
static sSocket *s_socket_new_invalid() {
    return NULL;
}

// Creates and connects to a server
// if address is NULL, "127.0.0.1" is used
// not for emscripten users: compile with -s ASYNCIFY=1, because emscripten_sleep(100); will be called
S_EXPORT
sSocket *s_socket_new(const char *address, su16 port);


// kills the socket and sets it invalid
S_EXPORT
void s_socket_kill(sSocket **self_ptr);


// returns the stream for the socket
S_EXPORT
sStream_i s_socket_get_stream(sSocket *self);


#endif //OPTION_SOCKET
#endif //S_SOCKET_H
