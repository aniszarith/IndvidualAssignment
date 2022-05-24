#include <time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<string.h>
#include<unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

void func(int socket_desc)
{
  char buff[35];

  read(socket_desc, buff, sizeof(buff));
  printf ("Time details from server %s", buff);
}

int main(int argc , char *argv[])
{
        int socket_desc, new_socket;
        struct sockaddr_in server;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        server.sin_addr.s_addr = inet_addr("192.168.56.108"); //Please enter the ip address of your Server VM
        server.sin_family = AF_INET;
        server.sin_port = htons( 13 );

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("connect error");
                return 1;
        }

        puts("Connected \n");

        //chat function
        func(socket_desc);

        close(socket_desc);
        return 0;
}
