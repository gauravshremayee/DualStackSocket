#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in6 serv_addr;
	struct sockaddr_in  serv_addr4;
    struct hostent *server_ipv6,*server_ipv4;
    char buffer[256] = "This is a string from client!";

    if (argc < 3) {
        fprintf(stderr, "Usage: %s  \n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);

    printf("\nIPv6 TCP Client Started...\n");
    
    
    //Sockets Layer Call: gethostbyname2()
    server_ipv6 = gethostbyname2(argv[1],AF_INET6);
	server_ipv4 = gethostbyname(argv[1]);
    printf("\nserver1 is % s and server2 is %s\n",server_ipv6, server_ipv4);
     if (server_ipv6 == NULL && server_ipv4 == NULL ) {       
        fprintf(stderr, "ERROR, no such ipv4 host\n");
        exit(0);
        
    }
	
	//Create Socket for ipv6
    if ( server_ipv6 != NULL){
	
	   sockfd = socket(AF_INET6, SOCK_STREAM, 0);
       if (sockfd < 0)
        error("ERROR opening socket");
		
       memset((char *) &serv_addr, 0, sizeof(serv_addr));
       serv_addr.sin6_flowinfo = 0;
       serv_addr.sin6_family = AF_INET6;
       memmove((char *) &serv_addr.sin6_addr.s6_addr, (char *) server_ipv6->h_addr, server_ipv6->h_length);
       serv_addr.sin6_port = htons(portno);
   }
   //Create Socket for ipv4
   else if (server_ipv4 !=NULL) {
   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
       if (sockfd < 0)
           error("ERROR opening socket");
   
    serv_addr4.sin_family = AF_INET;
    memmove((char *) &serv_addr4.sin_addr.s_addr, (char *) server_ipv4->h_addr, server_ipv4->h_length);
    serv_addr4.sin_port = htons(portno);
	
	}
	
	else {
	
	   printf ("Error finding Host");
	   exit(1);
	 }
    //Sockets Layer Call: connect()
	
	// connect  for ipv6 
	 if ( server_ipv6 != NULL) {
          if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
           error("ERROR connecting");
      }
	  // connect  for ipv4
	   if ( server_ipv4 != NULL) {
	        
			if (connect(sockfd, (struct sockaddr *) &serv_addr4, sizeof(serv_addr4)) < 0)
               error("ERROR connecting");
      }
    
    //Sockets Layer Call: send()
    n = send(sockfd,buffer, strlen(buffer)+1, 0);
    if (n < 0)
        error("ERROR writing to socket");

    memset(buffer, 0, 256);
    
    //Sockets Layer Call: recv()
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0)
        error("ERROR reading from socket");
    printf("Message from server: %s\n", buffer);

    //Sockets Layer Call: close()
    close(sockfd);
        
    return 0;
}
