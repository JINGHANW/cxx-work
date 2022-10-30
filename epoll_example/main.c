#define MAXFD 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
int create_socket()//创建一个socket连接
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(-1 != listenfd);

    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(6000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = bind(listenfd, (struct sockaddr *)&ser, sizeof(ser));
    assert(-1 != res);

    listen(listenfd, 5);
    return listenfd;
}

void get_client_link(int fd, int epfd)//获取一个客户端连接
{
    struct sockaddr_in cli;
    int len = sizeof(cli);

    int c = accept(fd,(struct sockaddr_in *)&cli, &len);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = c;

    epoll_ctl(epfd, EPOLL_CTL_ADD, c, &ev);

    printf("one client link\n");
}

void unlink_client(int fd, int epfd)//断开连接
{
    close(fd);
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    printf("one client unlink\n");
}

void deal_client_data(int fd, int epfd)//处理客户端数据
{
    int buff[128] = {0};
    int res = recv(fd, buff, 127, 0);

    if(res == 0)
    {
        unlink_client(fd, epfd);
        return;
    }
    printf("%s\n",buff);
    send(fd, "ok", 2, 0);
}

void deal_finish_fd(int n, struct epoll_event *events, int epfd, int listenfd)//处理就绪的文件描述符
{
    int i = 0;
    for(i = 0;i <= n;i++)
    {
        int fd = events[i].data.fd;
        if(fd == listenfd)
        {
            get_client_link(fd, epfd);
        }
        else if(events[i].events & EPOLLHUP)
        {
            unlink_client(fd, epfd);
        }
        else if(events[i].events & EPOLLIN)
        {
            deal_client_data(fd, epfd);//在后面，如果n = 0，需要断开连接，所以得把epfd传进去
        }
        else
        {
            printf("fd error\n");
        }
    }
}

int main()
{
    int listenfd = create_socket();

    int epfd = epoll_create(5);

    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);//在内核事件中注册listenfd

    while(1)
    {
        struct epoll_event events[MAXFD];

        int n = epoll_wait(epfd, events, MAXFD, -1);

        if(n < 0)
        {
            printf("epoll error\n");
            break;
        }

        deal_finish_fd(n, events, epfd, listenfd);
    }

    exit(0);
}