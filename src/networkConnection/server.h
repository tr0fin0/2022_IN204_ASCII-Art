#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

using namespace std;


sf::IpAddress client_sender_for_server;

void sendToClient(bool *sending){
    sf::UdpSocket socket;

    while (client_sender_for_server.toString() == "0.0.0.0")
    {
        if(!(*sending)){
            std::cout << "server sending saiu\n";
            return;
        } 
    }
    // UDP socket:    
    sf::IpAddress recipient(client_sender_for_server.toString());
    unsigned short client_receive_port = 54001;
    
    std::cout<<"Connectiong to " << recipient.toString() << std::endl;
    
    //camera capture
    cv::VideoCapture cap(0);
    cv::Mat img;

     while(*sending){
        //captando a imagem
        Converter c;
        cap.read(img);
        c.setImage(img);
        c.convertGrayScale();
        c.resize(imageWidth, imageHeight);

        //enviando para server
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 2).get(), bufferSize, recipient, client_receive_port) != sf::Socket::Done)
        {
            std::cout << "Error in sending to client" << std::endl;
        }
    }

    std::cout << "server sending saiu\n";

}

void receiveFromClient(std::string *m_ascii_text, Glib::Dispatcher *m_dispatcher, bool *receiving){
    char buffer[bufferSize];
    std::size_t received = 0;
    unsigned short client_sender_port;

    sf::UdpSocket socket;
    socket.setBlocking(false);
    sf::SocketSelector selector;
    selector.add(socket);
    sf::Time timeout = sf::milliseconds(1000); // timeout de 1 segundo

    if (socket.bind(54000) != sf::Socket::Done)
    {
        printf("error socket\n");
        return;
    }
    std::cout << "Bind sucessfull in " << socket.getLocalPort() << " "<< std::endl;
    while(*receiving){
        // UDP socket:
        if (socket.receive(buffer, sizeof(buffer), received, client_sender_for_server, client_sender_port) != sf::Socket::Done)
        {

        }
        if(received == sizeof(buffer))
        {
            //converting to UTF-8
            *m_ascii_text = convert2UTF8(str);
            m_dispatcher->emit();
        }
    }

    std::cout << "server receiving saiu\n"; 
}

