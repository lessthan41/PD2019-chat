# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
using namespace std;

const int MAXSTR = 1024;

int main()
{
	// printf("Test\n========\nargs: <%d>\nargv: %s\n=========\n", argc, argv[0]);

	// Part I: connect to server
	printf("Part I: set socket\n");
    // socket declaration
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM , 0);

    if (sockfd == -1)
        printf("\tFail to create a socket.");

    // socket initialization
    printf("\tinitializing connecting to server!\n");
	struct sockaddr_in info;
    bzero(&info, sizeof(info)); // initialize
    info.sin_family = PF_INET;  // ipv4

	// socket IP and port
    printf("\tsetting IP and port!\n");
	/* local 
	info.sin_addr.s_addr = inet_addr("127.0.0.1");     // local IP address
    info.sin_port = htons(8700);                       // local port */

	/* csie server (net0) */
	info.sin_addr.s_addr = inet_addr("140.112.30.40"); // net0 IP address
    info.sin_port = htons(2400);                       // net0 port 

	// socket connection
	printf("\ttry to connect to server, result ==> ");
    int err = connect(sockfd, (struct sockaddr *)& info, sizeof(info));
    if (err == -1)
        printf("ERROR\n");
	else
	{
		printf("SUCCESS\n\n");

		// Part II: I/O
		printf("Part II: starting I/O\n");
		// Send a message to server
		char message[MAXSTR];
		while (cin.getline(message, MAXSTR))
		{
		    char receiveMessage[100];
			send(sockfd, message, sizeof(message), 0);

			// receive message from server
			recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
			printf("%s\n", receiveMessage);
		}

		// close client socket
        close(sockfd);
        printf("Client close Socket\n");
	}
    return 0;
}
