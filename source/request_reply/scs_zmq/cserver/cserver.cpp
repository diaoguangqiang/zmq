#include <stdio.h>
#include <iostream>

#include "zmq.h"
#include "zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了

#pragma comment(lib,"libzmq-v100-mt-gd-4_0_4.lib")

int main(int argc, char** argv)
{	
	std::cout << "zmq server, listen: 6666" <<std::endl;
	
	//指定zmq 处理I/0事件的thread pool 为1
	void* context=zmq_init(1);    
	void* z_socket=zmq_socket(context,ZMQ_REP);

	zmq_bind(z_socket,"tcp://*:6666");    // accept connections on a socket

	std::string msg_str = "{\"groupno\":\"451\",\"id\":\"2\",\"name\":\"Z26_PSC_JLB2_2\",\"type\":\"JLB2\",\"lable\":\"lable\",\"loaction\":\"location\",\"timestamp\":\"0\",\"quality\":\"0\",\"point\":[{\"tag\":\"ABDY\",\"offset\":\"790\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"AXDL\",\"offset\":\"791\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BCDY\",\"offset\":\"792\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BXDL\",\"offset\":\"793\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CADY\",\"offset\":\"794\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CXDL\",\"offset\":\"795\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"DYPL\",\"offset\":\"796\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"GLYS\",\"offset\":\"797\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGDD\",\"offset\":\"798\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGGL\",\"offset\":\"799\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGDD\",\"offset\":\"800\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGGL\",\"offset\":\"801\",\"type\":\"1\",\"value\":\"0\"}]}";
	printf("msg_len: %d\n", msg_str.length());
	int msg_len = msg_str.length() + 1;
	
	char msg_buf[1024]={"{\"groupno\":\"451\",\"id\":\"2\",\"name\":\"Z26_PSC_JLB2_2\",\"type\":\"JLB2\",\"lable\":\"lable\",\"loaction\":\"location\",\"timestamp\":\"0\",\"quality\":\"0\",\"point\":[{\"tag\":\"ABDY\",\"offset\":\"790\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"AXDL\",\"offset\":\"791\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BCDY\",\"offset\":\"792\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BXDL\",\"offset\":\"793\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CADY\",\"offset\":\"794\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CXDL\",\"offset\":\"795\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"DYPL\",\"offset\":\"796\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"GLYS\",\"offset\":\"797\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGDD\",\"offset\":\"798\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGGL\",\"offset\":\"799\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGDD\",\"offset\":\"800\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGGL\",\"offset\":\"801\",\"type\":\"1\",\"value\":\"0\"}]}"};
	
	int recvn=1;
	while(true)
	{    
		//接受部分
		zmq_msg_t recv_msg;
		zmq_msg_init(&recv_msg);
		zmq_msg_recv(&recv_msg,z_socket,0);    
		 //0表示非阻塞
		std::cout<<"server <<< msg: "<<recvn++<<" ";
		std::cout<<(char*)zmq_msg_data(&recv_msg)<<std::endl;
		zmq_msg_close(&recv_msg);

		//发送部分
		zmq_msg_t send_msg;
		zmq_msg_init_size(&send_msg,msg_len);
		//memcpy(zmq_msg_data(&send_msg), "{\"groupno\":\"451\",\"id\":\"2\",\"name\":\"Z26_PSC_JLB2_2\",\"type\":\"JLB2\",\"lable\":\"lable\",\"loaction\":\"location\",\"timestamp\":\"0\",\"quality\":\"0\",\"point\":[{\"tag\":\"ABDY\",\"offset\":\"790\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"AXDL\",\"offset\":\"791\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BCDY\",\"offset\":\"792\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"BXDL\",\"offset\":\"793\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CADY\",\"offset\":\"794\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"CXDL\",\"offset\":\"795\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"DYPL\",\"offset\":\"796\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"GLYS\",\"offset\":\"797\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGDD\",\"offset\":\"798\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"WGGL\",\"offset\":\"799\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGDD\",\"offset\":\"800\",\"type\":\"1\",\"value\":\"0\"},{\"tag\":\"YGGL\",\"offset\":\"801\",\"type\":\"1\",\"value\":\"0\"}]}", msg_len);
		memcpy(zmq_msg_data(&send_msg), msg_buf, msg_len);
		zmq_sendmsg(z_socket,&send_msg,0);
		std::cout<<"server >>> msg: success! len "<< msg_len;
		//std::cout<<(char*)zmq_msg_data(&send_msg)<<std::endl;
		zmq_msg_close(&send_msg);

		printf("\n\n");
	}
	zmq_close(z_socket);
	zmq_term(context);

	return 0;
}