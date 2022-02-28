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
    struct can_frame frame;
    struct can_filter rfilter[1];
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字
    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr); //指定 can0 设备
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定
    //定义接收规则，只接收表示符等于 0x11 的报文
    rfilter[0].can_id = 0x22;
    rfilter[0].can_mask = CAN_SFF_MASK;
    //设置过滤规则
     setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
    //禁用过滤规则
    // setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
    while (1)
    {
        // nbytes = read(s, &frame, sizeof(frame)); //接收报文
        socklen_t len = sizeof(addr);
        //接收所有可能的canid的数据
        nbytes = recvfrom(s, &frame, sizeof(frame), 0, (struct sockaddr *)&addr, &len);
        //显示报文
        if (nbytes > 0)
        {
            printf("ID = 0x%X DLC = % d data[0] = 0x % X\n", frame.can_id,
                   frame.can_dlc, frame.data[0]);
            printf("ID = 0x%X DLC = % d data[1] = 0x % X\n", frame.can_id,
                   frame.can_dlc, frame.data[1]);
            printf("ID = 0x%X DLC = % d data[2] = 0x % X\n", frame.can_id,
                   frame.can_dlc, frame.data[2]);
        }
        else
        {
            std::cout << "no data recieved" << std::endl;
        }
    }
    close(s);
    return 0;
}
