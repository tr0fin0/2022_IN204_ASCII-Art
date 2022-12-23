#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <random>
#include "client.h"

using namespace std;

//função para esperar tantos milisegundos
void sleep_ms(size_t ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


void be_server(){
    
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in addr;
    
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    if(bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("Listening failed on the socket: ");
        exit(-1);
    }
    
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);

    char buffer[2500];
    //camera capture
    //cv::VideoCapture cap(0);
    //cv::Mat img;

    while(1){

        //captando a imagem
        //Converter c;
        //cap.read(img);


        //c.setImage(img);
        //c.convertGrayScale();
        //c.resize(170, 50);

        recvfrom(fd, buffer, 2500, 0, (struct sockaddr *) &cliaddr, &cliaddr_len);
        if(strlen(buffer) == 2400){
            system("clear");
            cout << strlen(buffer) << endl;
            cout << buffer << endl;    
        }
            
        //enviando para server
        //sendto(fd, (char*)c.parallelConvert(c.getImage(), 1, 3).get(), strlen(buffer), 0, (const struct sockaddr *) &cliaddr, cliaddr_len);
    }

}


//tentando com threads
/*
void sendToClient(){
    cout << "Send To Client\n";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in addr;
    
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    if(bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("Listening failed on the socket: ");
        exit(-1);
    }
    
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);

    char buffer[8600];
    //camera capture
    cv::VideoCapture cap(0);
    cv::Mat img;

    while(1){

        //captando a imagem
        Converter c;
        cap.read(img);

        c.setImage(img);
        c.convertGrayScale();
        c.resize(170, 50);

        //enviando para server
        sendto(fd, (char*)c.parallelConvert(c.getImage(), 1, 3).get(), strlen(buffer), 0, (const struct sockaddr *) &cliaddr, cliaddr_len);
    }

}

void receiveFromClient(){
    cout << "Receive from client\n";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd == -1){
        perror("Socket creation failed :");
        exit(-1);
    }

    struct sockaddr_in addr;
    
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    if(bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) == -1){
        perror("Listening failed on the socket: ");
        exit(-1);
    }
    
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);

    char buffer[8600];
    while(1){
        system("cls || clear");

        recvfrom(fd, buffer, 8600, 0, (struct sockaddr *) &cliaddr, &cliaddr_len);
        cout << buffer << endl;    
    }
}


void be_server(){
    
    std::thread t1 = std::thread(sendToClient);

    std::thread t2 = std::thread(receiveFromClient);

    t1.join();
    t2.join();

}

*/