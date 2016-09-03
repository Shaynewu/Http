#include "My_http.h"

void ErrorHandle(int csock)
{
    char fail_buf[1025];
    bzero(fail_buf,sizeof(fail_buf));
    sprintf(fail_buf,"HTTP/1.1 404 \r\nServer: ZG_HTTP\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n%s",
            (int)strlen("<html><h1>Not Found 404</h1></html>"), "<html><h1>Not Found 404</h1></html>");

    send(csock,fail_buf,sizeof(fail_buf),0);

    close(csock);
}
