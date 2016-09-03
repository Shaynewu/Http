#include "My_http.h"

void SendToClient(int csock,char* recvbuf)
{
    int clisock=csock;
    char head[2048];
    char file_buf[10];
    char versions_buf[20];
    char server_buf[30]={"Server: ZG_Service"};
    char content_type[15];
    char cont_length[20]={"Content-Length:"};
  ///  char *time_buf=NULL;   增加时间！
    FileInformation* fl;


    Handle_head(recvbuf,file_buf,versions_buf,content_type);

 //   printf("1:%d\t%s\n",strlen(file_buf),file_buf);
 //   printf("2:%s\n%s\n",versions_buf,content_type);

    strcpy(file_buf,"./www/index.html");
    
    


    fl=Read_File(file_buf);

    sprintf(head,"HTTP/1.1 200 OK\r\n%s\r\nContent-Type:%s\r\n%s %d\r\n\r\n",server_buf,content_type,cont_length,*(fl->file_size));

    printf("%d\t%s\n",strlen(file_buf),file_buf);
    printf("%s\n",head);

    send(clisock,head,strlen(head),0);
    send(clisock,fl->file_cont,*(fl->file_size),0);

    free(fl->file_cont);
    fl->file_cont=NULL;
    free(fl->file_size);
    fl->file_size=NULL;

    close(clisock);

}
