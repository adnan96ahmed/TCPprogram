#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 4096
 
int main(int argc, char *argv[])
{
    int PORTNUM;
	int len;
	char buffer[MAXRCVLEN + 1]; // +1 so we can add null terminator
    char *endBuffer;
    
    if (argc == 2) {
        PORTNUM = atoi(argv[1]);
    } else {
        printf("Please only provide the port number as the second argument\n");
        return -1;
    }
  
	struct sockaddr_in dest; // socket info about the machine connecting to us
	struct sockaddr_in serv; // socket info about our server
	int mysocket;            // socket used to listen for incoming connections
	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv));           // zero the struct before filling the fields
	
	serv.sin_family = AF_INET;                // Use the IPv4 address family
	serv.sin_addr.s_addr = htonl(INADDR_ANY); // Set our address to any interface 
	serv.sin_port = htons(PORTNUM);           // Set the server port number 

	/* Create a socket.
   	   The arguments indicate that this is an IPv4, TCP socket
	*/
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
	// bind serv information to mysocket
    if ((bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr)) == -1)) {
        fprintf( stderr, "Server could not bind to port number: %d\n", PORTNUM );
        return -1;
    }

	// start listening, allowing a queue of up to 1 pending connection
	listen(mysocket, 1);
	
	// Create a socket to communicate with the client that just connected
	int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  
	while(consocket)
	{
		printf("Incoming connection from %s \n", inet_ntoa(dest.sin_addr));
		
		// Receive data from the client
        len = recv(consocket, buffer, MAXRCVLEN, 0);
        buffer[len] = '\0';
        //loop to continue recieving until end of message
        while (strstr(buffer, "*ended") == NULL) {
            printf("%s", buffer);
            len = recv(consocket, buffer, MAXRCVLEN, 0);
            buffer[len] = '\0';
        }
        
        //printing out the portion before the ended message was received
        if (strcmp(buffer,"*ended")!=0) {
            endBuffer = strtok(buffer, "*");
            printf("%s", endBuffer);
        }
        printf("\n");
        
		//Close current connection
		close(consocket);
		
		//Continue listening for incoming connections
		consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
	}

	close(mysocket);
	return EXIT_SUCCESS;
}
