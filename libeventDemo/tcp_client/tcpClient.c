#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>

#define SERV_IP		"192.168.128.15"
#define SERV_PORT	9999

void event_cb(struct bufferevent *bev, short events, void * arg);

struct event_base* base = NULL;
struct bufferevent *bev = NULL;

void read_cb(struct bufferevent *bev, void *arg)
{
    char buf[1024] = {0};
    bufferevent_read(bev, buf, sizeof(buf));
    printf("server say:%s\n", buf);
    //bufferevent_write(bev, buf, strlen(buf) +1);
    //sleep(1);
}
 
void write_cb(struct bufferevent *bev, void *arg)
{
    printf("I am client，write done\n");
}

int connect_server(void)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//通信的fd放到bufferevent中
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    
    // init server info
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = PF_INET;
    serv.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &serv.sin_addr.s_addr);
    //连接服务器
    bufferevent_socket_connect(bev, (struct sockaddr*)&serv, sizeof(serv));
	printf("@@@@@@@@ to connect server\n");
	//设置回调
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);
    
    //设置回调生效
    bufferevent_enable(bev, EV_READ);
	printf("@@@@@@@@ set callback and enable ok\n");
	
	return 0;
}

void event_cb(struct bufferevent *bev, short events, void * arg)
{
    if(events & BEV_EVENT_EOF)
    {
        printf("connection closed \n");
		    //释放资源
		bufferevent_free(bev);
		connect_server();
    }
    else if(events & BEV_EVENT_ERROR)
    {
        printf("some other error\n");
		    //释放资源
		bufferevent_free(bev);
    }
    else if(events & BEV_EVENT_CONNECTED)
    {
        printf("已经连接了服务器.....\n");
        return ;
    }
}

//客户端与用户教会，从终端读取数据给服务器
void read_terminal_cb(evutil_socket_t fd, short what, void *arg)
{
    //读数据
    char buf[1024] = {0};
    int len = read(fd, buf, sizeof(buf));
    
    //struct bufferevent* bev = (struct bufferevent*)arg;
    
    //发送数据
    bufferevent_write(bev, buf, len+1);
}

int main()
{
	//创建event_base
    base = event_base_new();
	
    // 连接服务器
	connect_server();
    
    //创建事件
    struct event* ev = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST,
						read_terminal_cb, NULL);
						//read_terminal_cb, bev);
    
    //添加事件
    event_add(ev, NULL);
    event_base_dispatch(base);
    event_free(ev);
    event_base_free(base);
}