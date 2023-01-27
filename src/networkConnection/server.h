#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "client.h"
using namespace std;


sf::IpAddress client_sender;
    

void sendToClient(){
    sf::UdpSocket socket;

    // UDP socket:
    sf::IpAddress recipient = client_sender;
    unsigned short client_receive_port = 54001;
    
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
        if (socket.send(buffer, 2500, recipient, client_receive_port) != sf::Socket::Done)
        {
            std::cout << buffer;
        }        
    }

}

void receiveFromClient(){
    char buffer[2500];
    std::size_t received;
    unsigned short client_sender_port;

    sf::UdpSocket socket;
    if (socket.bind(54000) != sf::Socket::Done)
    {
        // error...
        printf("Error bro\n");
        return;
    }

    while(1){
        // UDP socket:
        if (socket.receive(buffer, 2500, received, client_sender, client_sender_port) != sf::Socket::Done)
        {
            std::cout << buffer;
        }
    
    }
    


}


void be_server(){
    
    std::thread t2 = std::thread(receiveFromClient);

    std::thread t1 = std::thread(sendToClient);


    t1.join();
    t2.join();

}

