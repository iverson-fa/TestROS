#include<sstream> 

// C++引入了 ostringstream、istringstream、stringstream 三个类，要使用他们创建对象就必须包含sstream.h头文件。

#include<ros/ros.h> //包含ros节点所必须的文件

#include<std_msgs/String.h> //包含了我们要使用的消息类型

int main(int argc,char** argv)
{
ros::init(argc,argv,"talker");   //ros节点初始化,输入参数并为节点命名（与CMakeLists.txt中的节点名称相同，名称唯一）

ros::NodeHandle n;//设置节点进程的句柄

ros::Publisher chatter_pub=n.advertise<std_msgs::String>("chatter",1000); //将节点设置成发布者

//**ros::Publisher 对象=n.advertise<std_msgs::消息类型>("话题",缓冲区大小);** 
//在ros master端注册一个publisher，发布名为chatter的topic，消息类型为string，缓冲区可缓冲消息数量为1000）

ros::Rate loop_rate(10); //设置循环的频率，这里是10hz

int count=0;

// 当收到CTRL+C或ROS停止当前节点运行时，ros::ok( )库会执行停止节点运行的命令。

while(ros::ok())//在节点未发生异常的时候循环
{
std_msgs::String msg; //创建一个消息变量，变量的类型必须和节点发布的消息的类型相同

std::stringstream ss; //输入输出流 ss

ss<<"hello world"; //将字符串hello world 输入到ss中

msg.data=ss.str(); //将字符串传递给msg.data

ROS_INFO("%s",msg.data.c_str());  //发布日志消息,类似于c语言中的printf

chatter_pub.publish(msg);//发布封装完毕的消息msg，master会查找订阅该话题的节点，帮助其建立连接，完成消息的传输。

//循环等待回调函数，用来处理节点订阅话题的所有回调函数
//如果有一个订阅者出现，ROS就会更新和读取所有主题

ros::spinOnce();

//按照循环频率（10Hz）延时

loop_rate.sleep();

++count;

}

return 0;

}

