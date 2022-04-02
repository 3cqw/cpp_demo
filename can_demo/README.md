
# 说明
## 安装依赖
sudo apt install can-utils
#
## 设置虚拟CAN
sudo modprobe vcan  
sudo ip link add dev vcan0 type vcan  
sudo ip link set up vcan0
#
cmake ..  
make  
candump vcan0

