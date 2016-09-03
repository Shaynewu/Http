#include "My_http.h"

FileInformation* Read_File(char* filebuf)
{
    FileInformation* file;
    struct stat buf;
    int ret=stat(filebuf,&buf);
    if(ret==-1)
    {
        perror("File not exist");
        return;
    }

    file=(FileInformation*)malloc(sizeof(FileInformation));


    file->file_size=malloc(4);
    file->file_cont=malloc(buf.st_size);
    *(file->file_size)=buf.st_size;


    printf("%d\n",*(file->file_size));


    int fp=open(filebuf,O_RDONLY);
    if(fp==-1)
    {
        perror("open fail");
        return;
    }

    int len=read(fp,file->file_cont,buf.st_size);

    printf("%s\n",file->file_cont);

    close(fp);

  //  printf("img:%s\n",contentbuf);

    return file;
}
