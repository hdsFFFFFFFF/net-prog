#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_MAX 520

int main(void)
{
	int clnt_sock = socket(AF_INET, SOCK_STREAM, 0);

	char msg[BUFF_MAX];
	fgets(msg, sizeof(msg), stdin);

	struct sockaddr_in clnt_addr;
	memset(&clnt_addr, 0, sizeof(clnt_addr));
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_port = htons(1314);
	clnt_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clnt_sock, (struct sockaddr *)&clnt_addr,
		sizeof(clnt_addr));

	//char msg[BUFF_MAX] = "I love kangchunmei\n";
	char buff[BUFF_MAX];
	write(clnt_sock, msg, sizeof(msg));
	read(clnt_sock, buff, sizeof(buff));

	printf("Message from server:%s\n", buff);

	close(clnt_sock);

	return 0;
}

