#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "../converters/VideoConverter.h"

using namespace std;
/*
void be_client(const char* IP_address){
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in s_addr;
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(80);
    inet_aton("127.0.0.0", &s_addr.sin_addr);

    socklen_t s_addr_len = sizeof(s_addr);

    char buffer[2500];
    //camera capture
    cv::VideoCapture cap(0);
    cv::Mat img;

    while(1){

        //captando a imagem
        Converter c;
        cap.read(img);
        //system("cls || clear");

        c.setImage(img);
        c.convertGrayScale();
        c.resize(50, 50);

        cout << strlen((char*)c.parallelConvert(c.getImage(), 1, 3).get()) << endl;

        //enviando para server
        sendto(fd, (char*)c.parallelConvert(c.getImage(), 1, 3).get(), 2500, 0, (const struct sockaddr *) &s_addr, s_addr_len);

        //recebendo imagem do server
        //int n = recvfrom(fd, buffer, 8600, 0, (struct sockaddr *) &s_addr, &s_addr_len);
        //cout << buffer << endl;
    }

}

*/

//tentando com threads

void sendToServer(const char *server_IP_address){
    cout << "Send To server\n";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in s_addr;
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(80);
    inet_aton(server_IP_address, &s_addr.sin_addr);

    socklen_t s_addr_len = sizeof(s_addr);

    char buffer[2500];
    //camera capture
    cv::VideoCapture cap(0);
    cv::Mat img;

     while(1){

        //captando a imagem
        Converter c;
        cap.read(img);
        c.setImage(img);
        c.convertGrayScale();
        c.resize(50, 50);

        //enviando para server
        sendto(fd, (char*)c.parallelConvert(c.getImage(), 1, 3).get(), 2500, 0, (const struct sockaddr *) &s_addr, s_addr_len);
     }

}

void receiveFromServer(const char* server_IP_address){
    cout << "Receive from server\n";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in s_addr;
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(80);
    inet_aton(server_IP_address, &s_addr.sin_addr);

    socklen_t s_addr_len = sizeof(s_addr);

    char buffer[2500];
    sendto(fd, (char*)"Connecting...", 2400, 0, (const struct sockaddr *) &s_addr, s_addr_len);
     while(1){
        //recebendo imagem do server
        int n = recvfrom(fd, buffer, 2400, 0, (struct sockaddr *) &s_addr, &s_addr_len);
                    cout << buffer << endl;

        if(strlen(buffer) == 2400){
            system("clear");
            cout << buffer << endl;
        }
    }

}


void be_client(const char* server_IP_address){
    
    //std::thread t1 = std::thread(sendToServer, server_IP_address);

    std::thread t2 = std::thread(receiveFromServer, server_IP_address);

    //t1.join();
    t2.join();
}

