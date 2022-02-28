#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAXLINE 4096
#define UDPPORT 8001
#define SERVERIP "192.168.255.129"

using namespace std;

int main()
{
    int serverfd;
    unsigned int server_addr_length, client_addr_length;
    char recvline[MAXLINE];
    char sendline[MAXLINE];
    struct sockaddr_in serveraddr, clientaddr;      //存储套接字地址和端口的结构体

    // 使用函数socket()，生成套接字文件描述符；
    if ((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)  //创建套接字，AF_INET:ipv4, SOCK_DGRAM: UDP
    {
        perror("socket() error");
        exit(1);
    }

    //将地址与端口设置为0；
    bzero(&serveraddr, sizeof(serveraddr));  
    //设置服务器使用的协议，地址与端口
    serveraddr.sin_family = AF_INET;                  //协议：ipv4
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(UDPPORT);

    server_addr_length = sizeof(serveraddr);
    // 使用bind() 函数绑定监听端口，将套接字文件描述符和地址类型变量（struct sockaddr_in ）进行绑定；
    if (bind(serverfd, (struct sockaddr *)&serveraddr, server_addr_length) < 0)
    {
        perror("bind() error");
        exit(1);
    }

    // 接收客户端的数据，使用recvfrom() 函数接收客户端的网络数据；
    client_addr_length = sizeof(sockaddr_in);
    int recv_length = 0;
    recv_length = recvfrom(serverfd, recvline, sizeof(recvline), 0, (struct sockaddr *)&clientaddr, &client_addr_length);
    cout << "recv_length = " << recv_length << endl;
    cout << recvline << endl;

    // 向客户端发送数据，使用sendto() 函数向服务器主机发送数据；
    int send_length = 0;
    sprintf(sendline, "hello client !");
    send_length = sendto(serverfd, sendline, sizeof(sendline), 0, (struct sockaddr *)&clientaddr, client_addr_length);
    if (send_length < 0)
    {
        perror("sendto() error");
        exit(1);
    }
    cout << "send_length = " << send_length << endl;

    //关闭套接字，使用close() 函数释放资源；
    close(serverfd);

    return 0;
}