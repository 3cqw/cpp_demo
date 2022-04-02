#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <iostream>
#include <pthread.h>
int s, nbytes;
struct sockaddr_can addr;
void *thread_sender(void *arg);
void *thread_receive(void *arg);
int main()
{
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字
    struct ifreq ifr;
    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr); //指定ifr的name对应的网卡的索引值（唯一）
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    std::cout << "add.can ifindex: " << addr.can_ifindex << std::endl;
    bind(s, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定

    pthread_t id_sender, id_receive;

    pthread_create(&id_receive, NULL, thread_receive, NULL);
    pthread_create(&id_sender, NULL, thread_sender, NULL);

    pthread_join(id_receive, NULL);
    pthread_join(id_sender, NULL);
    // close(s);
    return 0;
}

void *thread_sender(void *arg)
{
    struct can_frame frame[2] = {{0}};
    //禁用过滤规则，本进程不接收报文，只负责发送
    // setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
    frame[0].can_id = 0x22;
    frame[0].data[0] = '0';
    frame[0].data[1] = '1';
    frame[0].data[2] = '2';
    frame[0].data[3] = '3';
    frame[0].data[4] = '4';
    frame[0].data[5] = '5';
    frame[0].data[6] = '6';
    frame[0].can_dlc = 1;
    std::cout << "pyload: " << sizeof(frame[0].data) << std::endl;

    //生成两个报文
    frame[1].can_id = 0x00;
    frame[1].can_dlc = 1;
    frame[1].data[0] = '0';

    //循环发送两个报文
    while (1)
    {
        // nbytes = write(s, &frame[0], sizeof(frame[0])); //发送 frame[0]
        //对于任何被绑定的can设备发送数据
        nbytes = sendto(s, &frame[0], sizeof(frame[0]), MSG_DONTWAIT, (struct sockaddr *)&addr, sizeof(addr));
        if (nbytes != sizeof(frame[0]))
        {
            printf("Send Error frame[0]\n!");
            break; //发送错误，退出
        }
        sleep(1);
        // nbytes = write(s, &frame[1], sizeof(frame[1])); //发送 frame[1],并
        nbytes = sendto(s, &frame[1], sizeof(frame[1]), MSG_DONTWAIT, (struct sockaddr *)&addr, sizeof(addr)); //发送 frame[1]
        if (nbytes != sizeof(frame[1]))
        {
            printf("Send Error frame[1]\n!");
            break;
        }
        else
        {
            std::cout << "send sucess" << std::endl;
        }
        sleep(1);
    }
}

void *thread_receive(void *arg)
{
    int s_receive = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字
    // int s_receive = s;
    bind(s_receive, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定
    std::cout << "bind: " << bind << std::endl;
    struct can_frame received_frame;
    while (1)
    {
        // nbytes = read(s, &frame, sizeof(frame)); //接收报文
        socklen_t len = sizeof(addr);
        //接收所有可能的canid的数据
        std::cout << "before recvfrom" << std::endl;
        nbytes = recvfrom(s_receive, &received_frame, sizeof(received_frame), 0, (struct sockaddr *)&addr, &len);
        std::cout << "received data: " << std::endl;
        //显示报文
        if (nbytes > 0)
        {
            printf("ID = 0x%X DLC = % d data[0] = 0x % X\n", received_frame.can_id,
                   received_frame.can_dlc, received_frame.data[0]);
            printf("ID = 0x%X DLC = % d data[1] = 0x % X\n", received_frame.can_id,
                   received_frame.can_dlc, received_frame.data[1]);
            printf("ID = 0x%X DLC = % d data[2] = 0x % X\n", received_frame.can_id,
                   received_frame.can_dlc, received_frame.data[2]);
        }
        else
        {
            std::cout << "no data recieved" << std::endl;
        }
    }
}