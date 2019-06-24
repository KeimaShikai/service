#include "CMain.h"

CMain::CMain()
{
    //creating socket
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("Error! Socket wasn't created!\n");
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
}

CMain::~CMain()
{
    
}

void CMain::initialisation()
{
    sock = accept(listener, NULL, NULL);

    if (sock < 0)
    {
        perror("Accept error!\n");
        exit(3);
    }

    char message_init[] =
        "Greetings, COMRADE!\n"
        "Type HELP to find out what "
        "exectly you can do with "
        "our great application!\n"; 
    
    send(sock, message_init, sizeof(message_init), 0);
}

void CMain::communication()
{
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
                {
                    char message[] = "This is a place for a future help message!\n";
		            send(sock, message, sizeof(message), 0);
                }
		        break;
		    }
        }
        //if (strncmp(buf, "HELP", sizeof("HELP")) == 0)
	    //for (int i = 0; i < bytes_read; ++i) printf("%c", buf[i]);
    }
}

void CMain::disconnection()
{
    close(sock);
}
