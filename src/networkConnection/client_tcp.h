#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Network.hpp>

#include "../converters/VideoConverter.h"

using namespace std;

sf::TcpSocket socket;

void sendToServer(){
    
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 3).get(), 2500) != sf::Socket::Done)
        {
        std::cout<<"Error in sending to " << socket.getRemoteAddress() <<"\n";;        
        }        
    }

}

void receiveFromServer(){
    char buffer[2500];
    std::size_t received = 0;

    while(1){
        // UDP socket:
        if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
            system("clear");
            std::cout<<buffer;
        }
    
    }
}


void be_client(const char* server_IP_address){
    
    sf::Socket::Status status = socket.connect(server_IP_address, 54000);
    if (status != sf::Socket::Done)
    {
        cout << "Error trying to connect" << endl;
    }

    std::thread t1 = std::thread(sendToServer);

    std::thread t2 = std::thread(receiveFromServer);

    t1.join();
    t2.join();
}
