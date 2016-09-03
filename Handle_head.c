#include "My_http.h"

void Handle_head(char *recvbuf,char* file_buf,char* versions_buf,char* content_type)
{
    char* p=recvbuf;
    char tmpbuf[5];


    sscanf(p,"%[^ ]",tmpbuf);
    printf("tmpbuf:%s\n",tmpbuf);
    p=p+strlen(tmpbuf)+2;


    sscanf(p,"%[^ ]",file_buf);
    printf("file_buf:%s\n",file_buf);
    p=p+strlen(file_buf)+1;


    sscanf(p,"%[^A]",versions_buf);
  //  printf("hahah\t");
    printf("versions_buf:%s",versions_buf);
 //   printf("hehehh\n");
    p=p+strlen(versions_buf);


    sscanf(p,"%*[^ ]%*c%[^,]",content_type);
    printf("content_type:%s\n",content_type);

}
