/*

*\ 服务器端的源代码

*/

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include <sys/epoll.h>

#define MAXFDS 256
#define EVENTS 100
#define PORT 8888

int epfd;
bool setNonBlock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    if(-1 == fcntl(fd, F_SETFL, flags))
        return false;
    return true;
}

int main(int argc, char *argv[], char *evp[])
{
    int fd, nfds, confd;
    int on = 1;
    char *buffer[512];
    struct sockaddr_in saddr, caddr;
    struct epoll_event ev, events[EVENTS];

    if(-1 == socket(AF_INET, SOCKSTREAM), 0)
    {
        std::cout << "创建套接字出错啦" << std::endl;
        return -1;
    }


    struct sigaction sig;
    sigemptyset(&sig.sa_mask);
    sig_handler = SIG_IGN;
    sigaction(SIGPIPE, &N > sig, NULL);

    epfd = epoll_create(MAXFDS);

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons((short)(PORT));
    saddr.sin_addr.s_addr = INADDR_ANY;
    if(-1 == bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)))
    {
        std::cout << "套接字不能绑定到服务器上" << std::endl;
        return -1;
    }

    if(-1 == listen(fd, 32))
    {
        std::cout << "监听套接字的时候出错了" << std::endl;
        return -1;
    }

    ev.data.fd = fd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    while(true)
    {
        nfds = epoll_wait(epfd, &events, MAXFDS, 0);

        for(int i = 0; i < nfds; ++ i)
        {
            if(fd == events[i].data.fd)
            {
                memset(&caddr, sizeof(caddr));
                cfd = accept(fd, (struct sockaddr *)&caddr, &sizeof(caddr));
                if(-1 == cfd)
                {
                    std::cout << "服务器接收套接字的时候出问题了" << std::endl;
                    break;
                }

                setNonBlock(cfd);

                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
            }
            else if(events[i].data.fd & EPOLLIN)
            {
                bzero(&buffer, sizeof(buffer));
                std::cout << "服务器端要读取客户端发过来的消息" << std::endl;
                ret = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                if(ret < 0)
                {
                    std::cout << "服务器收到的消息出错了" << endl;
                    return -1;
                }
                std::cout << "接收到的消息为：" << (char *) buffer << std::endl;
                ev.data.fd = events[i].data.fd;
                ev.events = EPOLLOUT;
                epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
            }
            else if(events[i].data.fd & EPOLLOUT)
            {
                bzero(&buffer, sizeof(buffer));
                bcopy("The Author@: magicminglee@Hotmail.com", buffer, sizeof("The Author@: magicminglee@Hotmail.com"));
                ret = send(events[i].data.fd, buffer, strlen(buffer));
                if(ret < 0)
                {
                    std::cout << "服务器发送消息给客户端的时候出错啦" << std::endl;
                    return -1;
                }
                ev.data.fd = events[i].data.fd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, ev.data.fd, &ev);
            }
        }
    }
    if(fd > 0)
    {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}
