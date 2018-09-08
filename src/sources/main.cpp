#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    //creating socket
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("Error! Socket didn't create!\n");
        exit(1);
    }

    //naming socket
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listener,(struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind error!\n");
        exit(2);
    }

    //listening and queue organization
    listen(listener, 1);

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if (sock < 0)
        {
            perror("Accept error!\n");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if (bytes_read <= 0) break;
            printf(buf);
        }

        //closing socket
        close(sock);
    }
    return 0;
}
