#include <stdio.h>

#include <iostream>

#include "zmq.h"
#include "zmq_utils.h"            //Zeromq �����ĵ��������������ʵ����
#pragma comment(lib,"libzmq-v100-mt-gd-4_0_4.lib")

int main( int argc, char** argv )
{
	std::cout << "zmq client, connect: 6666" <<std::endl;

	void* context=zmq_init(1);    //ָ��zmq ����I/0�¼���thread pool Ϊ1
	void* z_socket=zmq_socket(context,ZMQ_REQ);

	int ret = zmq_connect(z_socket,"tcp://localhost:6666");    // accept connections on a socket
	if ( 0 == ret )
	{
		printf("���� zmq server success!\n\n");
	}
	else{
		printf("���� zmq server failed! errcode: %d\n", errno);
	}

	int times = 0;

	int msg_len = 15;

	std::string msg_str = "Z26_PSC_JLB2_2";
	printf("msg_len:%d\n\n", msg_str.length());

	while(true)
	{
		//���Ͳ���
		zmq_msg_t send_msg;
		zmq_msg_init_size(&send_msg, msg_len );
		memcpy(zmq_msg_data(&send_msg), "Z26_PSC_JLB2_2", msg_len );
		zmq_msg_send(&send_msg,z_socket,0);
		printf("client >>> msg:\t");
		std::cout<<(char*)zmq_msg_data(&send_msg)<<std::endl;
		zmq_msg_close(&send_msg);

		//���ܲ���
		zmq_msg_t recv_msg;
		zmq_msg_init(&recv_msg);
		//0��ʾ������
		zmq_msg_recv(&recv_msg,z_socket,0);                    
		printf("client <<< msg:\t");
		std::cout<<(char*)zmq_msg_data(&recv_msg)<<std::endl;
		zmq_msg_close(&recv_msg);

		times++;

		Sleep(300);

		printf("\n");
	}
	zmq_close(z_socket);
	zmq_term(context);

	return 0;
}