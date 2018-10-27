#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "messages.h"

int main()
{
    char buf[1024];
    int sock, listener;
    struct sockaddr_in addr;
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

	send(sock, message_1, sizeof(message_1), 0);

        while(1)
        {
            char cur_word[256];
	    bytes_read = recv(sock, buf, 1024, 0);
            if (bytes_read <= 0) break;
            switch (buf[0])
	    {
		case 'H':
		{
		    for (int i = 0; i < 4; ++i) cur_word[i] = buf[i];
		    if (strcmp(cur_word, "HELP") == 0)
			send(sock, message_2, sizeof(message_2), 0);
		    break;
		}
	    }
	    //if (strncmp(buf, "HELP", sizeof("HELP")) == 0)
	    //for (int i = 0; i < bytes_read; ++i) printf("%c", buf[i]);
        }

	//closing socket
        close(sock);
    }
    return 0;
}
