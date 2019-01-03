#include	<time.h>
#include	"unp_cust.h"

#define PORT 50000
#define MAX_WAIT 12

/**
* This is the server program that acts at CBP. It takes client requests and
* handles it according to it's queue capacity
*
**/
int main(int argc, char **argv)
{
	int					master_socket; //master_socket is server socket
	struct sockaddr_in	servaddr;
   int addrlen;
	time_t				ticks;
   int opt = 1;

   /**master socket server section**/
	master_socket = Socket(AF_INET, SOCK_STREAM, 0);
   //set master socket to allow multiple connections ,
   //this is just a good habit, it will work without this
   Setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

   //type of socket created
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // accept client connection on any interface
	servaddr.sin_port        = htons(PORT);	/* daytime server */
   addrlen = sizeof(servaddr);
   //bind the socket to
	Bind(master_socket, (SA *) &servaddr, sizeof(servaddr));

   //try to specify maximum of LISTENQ pending connections for the master socket
	Listen(master_socket, LISTENQ);

   puts("Waiting for connections ...");
   /**master socket server section**/

   //set of socket descriptors
   fd_set readfds;
   int sd;
   int activity, valread;
   int max_sd;
   char sender_buffer[MAXLINE];
   const int MAX_READ_BUFFER = 1024;
   char receiver_buffer[MAX_READ_BUFFER];
   //initialise all client_socket[] to 0 so not checked
   int MAX_CLIENTS = 30;
   int new_socket, client_socket[MAX_CLIENTS];
   for (int i = 0; i < MAX_CLIENTS; i++)
   {
      client_socket[i] = 0;
   }

	while(1) {
      //clear the socket set
      FD_ZERO(&readfds);

      //add master socket to set
      FD_SET(master_socket, &readfds);
      max_sd = master_socket;

      for (int i = 0; i < MAX_CLIENTS; i++) {
         //socket descriptor
         sd = client_socket[i];

         //if valid then add to read listen
         if (sd > 0) {
            FD_SET(sd, &readfds);
         }

         //get highest descriptor for select funcction
         if (sd > max_sd) {
            max_sd = sd;
         }

      }

      //wait for an activity on one of the sockets, set timeout to NULL for
      //indefinite wait
      //TODO: add and handle timeout
      activity = Select(max_sd + 1, & readfds, NULL, NULL, NULL);
      if ((activity < 0) && (errno!=EINTR))
      {
          printf("select error");
      } else {
         printf("%d",errno);
      }

      if (FD_ISSET(master_socket, &readfds)) {
         new_socket = Accept(master_socket,
                           (SA*)&servaddr,
                           (socklen_t*)&addrlen);
         if(new_socket < 0) {
            exit(EXIT_FAILURE);
         }

         //inform user of socket number - used in send and receive commands
         printf("New connection, socket fd is %d , ip is : %s , port : %d\n",
               new_socket,
               inet_ntoa(servaddr.sin_addr),
               ntohs(servaddr.sin_port));

         // send timestamp
         ticks = time(NULL);
         snprintf(sender_buffer,
                  sizeof(sender_buffer),
                  "Client connected at %.24s\r\n",
                  ctime(&ticks));
         Write(new_socket, sender_buffer, strlen(sender_buffer)); //write to message to tcp stream

         puts(sender_buffer); // print time locally as well
         //add new socket to array of sockets
         for (int i = 0; i < MAX_CLIENTS; i++)
         {
            //if position is empty
            if( client_socket[i] == 0 )
            {
                 client_socket[i] = new_socket;
                 printf("Adding to list of sockets as %d\n" , i);
                 break;
            }
         }
      }//endif FD_ISSET

      //else its some IO operation on some other socket
      for (int i = 0; i < MAX_CLIENTS; i++) {
         sd = client_socket[i];

         if (FD_ISSET(sd, &readfds)) {
             //Check if it was for closing , and also read the
             //incoming message
             valread = Read(sd, receiver_buffer, MAX_READ_BUFFER);
             if (valread == 0) {
                  //Somebody disconnected , get details and print
                  getpeername(sd,
                           (struct sockaddr*)&servaddr,
                           (socklen_t*)&addrlen);
                  printf("A host disconnected, IP %s, port %d \n" ,
                       inet_ntoa(servaddr.sin_addr) , ntohs(servaddr.sin_port));

                  //Close the socket and mark as 0 in list for reuse
                  Close(sd);
                  client_socket[i] = 0;
             }
             //Echo back the message that came in
             else {
                  //set the string terminating NULL byte on the end
                  //of the data read
                  receiver_buffer[valread] = '\0';
                  Write(sd, receiver_buffer, strlen(receiver_buffer));
             }
         }
      }
	}
   return 0;
}
