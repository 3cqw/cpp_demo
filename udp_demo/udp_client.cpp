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
    int confd;
    unsigned int addr_length;
    char recvline[MAXLINE];
    char sendline[MAXLINE];
    struct sockaddr_in serveraddr;

    // 使用socket()，生成套接字文件描述符；
    if ((confd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket() error");
        exit(1);
    }

    //通过struct sockaddr_in 结构设置服务器地址和监听端口；
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
    serveraddr.sin_port = htons(UDPPORT);
    addr_length = sizeof(serveraddr);

    // 向服务器发送数据，sendto() ；
    int send_length = 0;
    sprintf(sendline, "hello server!");
    send_length = sendto(confd, sendline, sizeof(sendline), 0, (struct sockaddr *)&serveraddr, addr_length);
    if (send_length < 0)
    {
        perror("sendto() error");
        exit(1);
    }
    cout << "send_length = " << send_length << endl;

    // 接收服务器的数据，recvfrom() ；
    int recv_length = 0;
    recv_length = recvfrom(confd, recvline, sizeof(recvline), 0, (struct sockaddr *)&serveraddr, &addr_length);
    cout << "recv_length = " << recv_length << endl;
    cout << recvline << endl;

    // 关闭套接字，close() ；
    close(confd);

    return 0;
}