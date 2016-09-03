#ifndef My_http_H_INCLUDE
#define My_http_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <langinfo.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/tcp.h>



typedef struct FileInformation
{
    int* file_size;
    char* file_cont;
}FileInformation;

int setNonblocking ();
void Service();
void SendToClient();
void Handle_head();
FileInformation* Read_File();
void ErrorHandle();



#endif
