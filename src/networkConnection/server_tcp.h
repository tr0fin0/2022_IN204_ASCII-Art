#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "client_tcp.h"
using namespace std;


void sendToClient(sf::TcpSocket socket){
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
            std::cout << "Error in sending to client" << std::endl;
        }        
    }

}

void receiveFromClient(sf::TcpSocket socket){
    
    char buffer[2500];
    std::size_t received = 0;
    
    while(1){

        if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        system("clear");
        std::cout<<buffer<<std::endl;
    }
    


}


void be_server(){
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(54000) != sf::Socket::Done)
    {
        // error...
        printf("Error trying to listen\n");
        return;
    }

    // accept a new connection
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done)
    {
        // error...
        cout << "Error trying to bind the connection" << endl;
    }

    std::thread t2 = std::thread(receiveFromClient, socket);

    std::thread t1 = std::thread(sendToClient, socket);

    t1.join();
    t2.join();

}

