// Костылёк для ревью
#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef CMAIN_H
#define CMAIN_H

class CMain
{
    private:
        char buf[1024];
        int sock, listener;
        struct sockaddr_in addr;
        int bytes_read;
        
    public:
        CMain();
        ~CMain();
        void initialisation();
        void communication();
        void disconnection();
};

#endif
