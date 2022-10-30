#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<ctype.h>
#include<event2/event.h>
#include<event2/bufferevent.h> //带缓冲区的事件
#include<event2/listener.h> //连接监听器

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#define PORT 8888

//读回调
void readcb(struct bufferevent* bev,void* arg)
{
    char buf[1024]={0};
    //读缓冲区的数据
    bufferevent_read(bev,buf,sizeof(buf));
    int i=0;
    while(buf[i]!='\0')
    {
        buf[i]=toupper(buf[i]);
        i++;
    }
    //往缓冲区发送数据
    bufferevent_write(bev,buf,sizeof(buf));

}

//写回调
void writecb(struct bufferevent* bev,void* arg)
{
    printf("数据已发送\n");
}

//事件回调
void eventcb(struct bufferevent* bev,short events,void *arg)
{
    if(events&BEV_EVENT_EOF)
    {
        printf("connection cloased");
    }else if(events&BEV_EVENT_ERROR)
    {
        printf("err\n");
    }
    //释放bufferevent资源
    bufferevent_free(bev);
}

//连接完成之后对应的通信操作
void listen_call_back(struct evconnlistener* listener,evutil_socket_t fd,struct sockaddr* addr,int len,void *ptr)
{
    //接收base
    struct event_base *base=(struct event_base*)ptr;
    //接收数据 - 发送数据
    //将fd封装成带缓冲区的事件
    struct bufferevent* bev=bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
    //给bufferevent对应的读写缓冲区设置回调函数
    bufferevent_setcb(bev,readcb,writecb,eventcb,NULL);
    //设置独缓冲区的回调可用
    bufferevent_enable(bev,EV_READ);
}
void getifconfig();
int main()
{
    //创建事件处理框架
    struct event_base* base=event_base_new();
    //设置服务器地址信息
    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family=AF_INET;
    serv.sin_port=htons(PORT);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    //创建监听的套接字

    //绑定
    //监听
    //等待并接收连接
    //有连接时listen_call_back被调用
    struct evconnlistener* listen=evconnlistener_new_bind(base,listen_call_back,base,LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,-1,(struct sockaddr*)&serv,sizeof(serv));
    //开始事件循环

    event_base_dispatch(base);
    //释放资源
    evconnlistener_free(listen);
    event_base_free(base);
}
void getifconfig(){
    char hostname[100]={0};
    char localIpAddress[256]={0};
    struct hostent *h;
    gethostname(hostname,sizeof(hostname));
    printf("host name is %s \n",hostname);
    h=gethostbyname(hostname);

    char mac[30]={0};
    struct ifaddrs * ifhead=NULL;
    struct ifaddrs * ifpoint=NULL;
    struct in_addr * intmpAddrPtr=NULL;
    getifaddrs(&ifhead);
    ifpoint=ifhead;
    while(ifpoint!=NULL)
    {
        if(ifpoint->ifa_addr->sa_family==AF_INET)
        {
            intmpAddrPtr=&((struct sockaddr_in *)ifpoint->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, intmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IPv4: %s\n", ifpoint->ifa_name, addressBuffer);
        }
        else if(ifpoint->ifa_addr->sa_family==AF_INET6)
        {
            intmpAddrPtr=&((struct sockaddr_in *)ifpoint->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, intmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IPv6: %s\n", ifpoint->ifa_name, addressBuffer);
        }
        ifpoint=ifpoint->ifa_next;
    }
    if (ifhead)
    {
        freeifaddrs(ifhead);
        ifhead = NULL;
    }
}
