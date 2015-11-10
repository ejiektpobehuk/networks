#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
	bzero(message, sizeof message);
	printf("Enter message : ");
        scanf("%s" , message);
		if(strncmp(message,"quit",4) != 0){
		//Send some data
       		if( send(sock , message , strlen(message) , 0) < 0)
        	{
            		puts("Send failed");
            		return 1;
        	}
         
        	//Receive a reply from the server
		bzero(server_reply, sizeof server_reply);
		if( recv(sock , server_reply , 2000 , 0) < 0)
        	{
        	    	puts("recv failed");
	            	break;
        	}
         
        	printf("Server reply : %s\n", server_reply);
    	}
	else{
		break;
		puts("win!!!!!");
	}
    } 
    if(shutdown(sock, SHUT_RDWR) == 0){    
    	if(close(sock) == 0){
		puts("win");
	}
	else{
		puts("you alac");
		return 1;
	}
    }
    else puts("you flac");
    return 0;
}
