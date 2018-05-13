#ifndef MILIB
#define MILIB
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//fork pipe
#include<arpa/inet.h>//net
#include<signal.h>//signal
#include<sys/socket.h>//socket
#include<netdb.h>//gethostbyname
#include<sys/uio.h>//readv iovec
#include<sys/select.h>//select
#include<sys/wait.h>//wait
#include<sys/epoll.h>//epoll
#include<sys/pthread.h>//thread
#include<sys/time.h>//timeval
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<fcntl.h>//fcntl
#include<errno.h>
#define SSIZE 64
#define MSIZE 128
#define XSIZE 256
#define XXSIZE 512
#define XXXSIZE 1024
#define LSIZE 2048
#define EXSIZE 4096

void childexit(int sig);
void msigurg(int sig);
int mepoll();
int threadrecv();
int threadsend();



#endif
