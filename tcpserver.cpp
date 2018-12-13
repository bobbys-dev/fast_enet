#include	<time.h>
#include	"unp_cust.h"

int
main(int argc, char **argv)
{
	int					listenfd, connfd; //listenfd is server socket
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // accept client connection on any interface
	servaddr.sin_port        = htons(3000);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); // Bind server socket to

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);

      ticks = time(NULL);
      snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
      Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}
