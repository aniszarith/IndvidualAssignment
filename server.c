#include<stdio.h>
#include<string.h>      //strlen
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>      //write
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

void func(int new_socket)
{
   time_t currtime;

   time(&currtime);
   write(new_socket, ctime(&currtime), 35);
   printf("Time details are send to client. %.24s\n",ctime(&currtime) );
}

int main(int argc , char *argv[])
{
        int socket_desc , new_socket , c;
        struct sockaddr_in server , client;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
{
                printf("Could not create socket");
        }

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 13 );
        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("bind failed");
                return 1;
        }
        puts("bind done");

        //Listen
        listen(socket_desc , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(client);

        new_socket = accept(socket_desc, (struct sockaddr *)&client,&c);

        if (new_socket<0)
        {
                perror("accept failed");
                return 1;
        }
        else  puts("RECEIVED");

        func(new_socket);
        close(socket_desc);
        return 0;
}
