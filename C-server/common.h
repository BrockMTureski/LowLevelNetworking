/*
common header file for web client and server files.
*/

#ifndef _COMMON_H_
#define _COMMON_H_


#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>


#define SERVER_PORT 18000    //port to use in server
#define HTTP_PORT 80

#define MAXLINE 4096        //max buffer length
#define SA struct sockaddr


void err_n_die(const char *fmt, ...); //variadic error handling function
char *bin2hex(const unsigned char *input, size_t len);

#endif