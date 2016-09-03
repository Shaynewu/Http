#include "My_http.h"

int setNonblocking ( int fd )
{
    int flags;

    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if ( -1 == ( flags = fcntl ( fd, F_GETFL, 0 ) ) )
        flags = 0;
    return fcntl ( fd, F_SETFL, flags | O_NONBLOCK );
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl ( fd, FIOBIO, &flags );
#endif
}

void Service()
{

    int efd=epoll_create(1024);
    while(efd==-1)
    {
        efd=epoll_create(1024);
    }
    ///创建套接字
    int ssock=socket(AF_INET,SOCK_STREAM,0);
    if(ssock==-1)
    {
        perror("socket fail");
        return;
    }

    setNonblocking(ssock);
    ///初始化地址结构
    struct sockaddr_in saddr;
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(1234);
    
    saddr.sin_addr.s_addr=inet_addr("192.168.121.3");
    

    ///设置可以重复绑定
    int optval=1;
	setsockopt(ssock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

    ///绑定套接字
    int ret=bind(ssock,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1)
    {
        perror("bind fail");
        return;
    }

    ret=listen(ssock,5);
    if(ret==-1)
    {
        perror("listen fail");
        return;
    }

    //epoll的设置
    struct epoll_event eventfd;
    eventfd.events=EPOLLIN|EPOLLET;
    eventfd.data.fd=ssock;
    epoll_ctl(efd,EPOLL_CTL_ADD,ssock,&eventfd);
    struct epoll_event fds[1024];

    ///接收客户端请求
    int csock;
    struct sockaddr_in caddr;
    int clen=sizeof(caddr);
    int nfds;
    char recv_buf[1025];


    while(1)
    {
        nfds=epoll_wait(efd,fds,1024,0);
        if(nfds>0)
        {
            int i;
            for(i=0;i<nfds;i++)
            {
                if(fds[i].data.fd==ssock)
                {
                    csock=accept(ssock,(struct sockaddr*)&caddr,&clen);
                    if(csock==-1)
                    {
                        printf("accpet fail");
                        return;
                    }
                    if(csock>0)
                    {
                        setNonblocking(csock);
                        eventfd.events=EPOLLIN|EPOLLET;
                        eventfd.data.fd=csock;
                        epoll_ctl(efd,EPOLL_CTL_ADD,csock,&eventfd);
                    }
                    printf("IP:%s\tport:%d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
                }
                //else if(fds[i].events&EPOLLIN)
                else
                {
                    int cfd=fds[i].data.fd; 
                    if(cfd<0)
                        continue;             
                    bzero(recv_buf,sizeof(recv_buf));
                    int len;
                    if((len=recv(cfd,recv_buf,sizeof(recv_buf)-1,0))<=0)
                    {                        
                        close(cfd);
                        eventfd.data.fd=-1;
                        continue;
                    } 
                    recv_buf[len]='\0';
                    printf("%s\n",recv_buf); 
                      
                    eventfd.events=EPOLLOUT|EPOLLET;
                    eventfd.data.fd=cfd;
                    epoll_ctl(efd,EPOLL_CTL_MOD,cfd,&eventfd);
                    SendToClient(cfd,recv_buf);   
                }
                //待开发，希望加入服务器断点下载
                // else if(fds[i].events&EPOLLOUT)
                // {
                //     int cfd=fds[i].data.fd; 
                //     if(cfd<0)
                //         continue;

                //     eventfd.events=EPOLLIN|EPOLLET;
                //     eventfd.data.fd=cfd;
                //     epoll_ctl(efd,EPOLL_CTL_MOD,cfd,&eventfd);
                // }
            }
        }

    }
    
}
