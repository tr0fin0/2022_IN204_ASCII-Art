#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Network.hpp>

#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>

#include <uchardet/uchardet.h>

#include <glib.h>
#include <iconv.h>
#include <iostream>
#include <string>
#include <cstring>

#include "../converters/VideoConverter.h"

using namespace std;

//tentando com threads
sf::IpAddress server_sender_for_client;

void sendToServer(const char *server_IP_address, bool *sending){
    sf::UdpSocket socket;
    // UDP socket:
    sf::IpAddress recipient(server_IP_address);
    std::cout<<"Trying to connect to " << recipient.toString()<<"\n";;
    unsigned short server_receive_port = 54000;
    
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 2).get(), bufferSize, recipient, server_receive_port) != sf::Socket::Done)
        {
            std::cout<<"Error in sending to " << recipient.toString() <<"\n";;
        }
    }
    // std::cout << "client sending saiu\n";
}

void receiveFromServer(const char* server_IP_address, std::string *m_ascii_text, Glib::Dispatcher *m_dispatcher, bool *receiving){
    char buffer[bufferSize];
    std::size_t received;
    unsigned short server_sender_port;

    sf::UdpSocket socket;
    socket.setBlocking(false);
    if (socket.bind(54001) != sf::Socket::Done)
    {
        printf("Error bro\n");
        return;
    }
    // std::cout<<"Binded to " << socket.getLocalPort()<<"\n";

    while(*receiving){
        received = 0;
        // UDP socket:
        if (socket.receive(buffer, sizeof(buffer), received, server_sender_for_client, server_sender_port) != sf::Socket::Done)
        {
            //std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
            //converting to UTF-8
            std::string str(buffer);

            *m_ascii_text = convert2UTF8(str);
            m_dispatcher->emit();
        }
    
    }
    // std::cout << "client receiving saiu\n";
}