#include "unp_cust.h"

#define PORT 50000
#define MAX 64

void chat(int sockfd);

int main(int argc, char **argv)
{
   int sockfd, connfd;
   int n;
   struct sockaddr_in servaddr, cli;
   char recvline[MAX];

   if (argc != 2) {
      err_quit("usage: a.out <IPaddress>");
   }
   // socket create and varification
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      err_sys("socket error");
   }

   bzero(&servaddr, sizeof(servaddr));
   // assign IP, PORT
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(PORT);
   if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		err_quit("inet_pton error for %s", argv[1]);
   }

   // connect the client socket to server socket
   if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      err_sys("connect error");
   }
   //recieve first transmission
   else {
      n = Read(sockfd, recvline, MAXLINE);
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF) {
			err_sys("fputs error");
   	}
   }

   // function for chat
   chat(sockfd);

   // close the socket
   Close(sockfd);
}

void chat(int sockfd) {
   char recvline[MAX];
   int n;
   while (1) {
      bzero(recvline, sizeof(recvline));
      printf("Enter the string : ");
      n = 0;
      while ((recvline[n++] = getchar()) != '\n') {
            ;
      }
      write(sockfd, recvline, sizeof(recvline));
      bzero(recvline, sizeof(recvline));
      read(sockfd, recvline, sizeof(recvline));
      printf("From Server : %s", recvline);
      if ((strncmp(recvline, "exit", 4)) == 0) {
         printf("Client Exit...\n");
         break;
      }
   }
}
