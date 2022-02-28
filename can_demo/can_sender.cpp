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

int main()
{
    int s, nbytes;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame[2] = {{0}};
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字
    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr); //指定ifr的name对应的网卡的索引值（唯一）
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    std::cout << "add.can ifindex: " << addr.can_ifindex << std::endl;
    bind(s, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定
    //禁用过滤规则，本进程不接收报文，只负责发送
   //setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
    frame[0].can_id = 0x22;
    frame[0].data[0] = '0';
    frame[0].data[0] = '1';
    frame[0].data[0] = '2';
    frame[0].data[0] = '3';
    frame[0].data[0] = '4';
    frame[0].data[0] = '5';
    frame[0].data[0] = '6';

    std::cout << "pyload: " << sizeof(frame[0].data) << std::endl;
    frame[0].can_dlc = 1;

    //生成两个报文
    frame[1].can_id = 0x00;
    frame[1].can_dlc = 1;
    frame[1].data[0] = '0';

    //循环发送两个报文
    while (1)
    {
        //nbytes = write(s, &frame[0], sizeof(frame[0])); //发送 frame[0]
        //对于任何被绑定的can设备发送数据
         nbytes = sendto(s, &frame[0], sizeof(frame[0]), 0, (struct sockaddr*)&addr, sizeof(addr));
        if (nbytes != sizeof(frame[0]))
        {
            printf("Send Error frame[0]\n!");
            break; //发送错误，退出
        }
        sleep(1);
        //nbytes = write(s, &frame[1], sizeof(frame[1])); //发送 frame[1]
         nbytes = sendto(s, &frame[1], sizeof(frame[1]), 0, (struct sockaddr*)&addr, sizeof(addr)); //发送 frame[1]
        if (nbytes != sizeof(frame[1]))
        {
            printf("Send Error frame[1]\n!");
            break;
        }
        sleep(1);
    }
    close(s);
    return 0;
}