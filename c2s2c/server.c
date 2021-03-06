#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_MAX 520 

int main(void)
{
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1314);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serv_sock, (struct sockaddr *)&serv_addr, 
	     sizeof(serv_addr));

	listen(serv_sock, 30);

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_len = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, 
			       (struct sockaddr *)&clnt_addr,
			       &clnt_addr_len);

	char buff[BUFF_MAX];
	read(clnt_sock, buff, sizeof(buff)); 
	write(clnt_sock, buff, sizeof(buff));

	close(serv_sock);
	close(clnt_sock);

	printf("Send success\n");
	
	return 0;
}

