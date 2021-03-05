#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	/* create socket */
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; /* IPv4地址 */
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234); /* port */

	/* 将套接字与本地端口和IP地址关联起来 */
	bind(serv_sock, (struct sockaddr *)&serv_addr, 
	     		sizeof(serv_addr));

	/* 监听：让套接字接收来自其它套接字的连接请求 */
	listen(serv_sock, 20);

	/* 接收客户端请求 */
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, 
			       (struct sockaddr *)&clnt_addr, 
			       &clnt_addr_size);

	/* 向客户端发送数据 */
	static const char str[] = "http://c.bianceng.net/socket/";
	write(clnt_sock, str, sizeof(str));

	/* close socket */
	close(clnt_sock);
	close(serv_sock);

	return 0;
}

