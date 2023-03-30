#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "client.h"
using namespace std;


sf::IpAddress client_sender_for_server;

void sendToClient(){
    sf::UdpSocket socket;

    while (client_sender_for_server.toString() == "0.0.0.0")
    {
    }
    // UDP socket:    
    sf::IpAddress recipient(client_sender_for_server.toString());
    unsigned short client_receive_port = 54001;
    
    std::cout<<"Connectiong to " << recipient.toString();
    
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 1).get(), 2500, recipient, client_receive_port) != sf::Socket::Done)
        {
            std::cout << "Error in sending to client" << std::endl;
        }        
    }

}

void receiveFromClient(std::string *m_ascii_text, Glib::Dispatcher *m_dispatcher){
    char buffer[2500];
    std::size_t received = 0;
    unsigned short client_sender_port;

    sf::UdpSocket socket;
    
    if (socket.bind(54000) != sf::Socket::Done)
    {
        // error...
        printf("Error bro\n");
        return;
    }
    std::cout << "Bind sucessfull in " << socket.getLocalPort() << " "<< std::endl;

    while(1){
        // UDP socket:
        if (socket.receive(buffer, sizeof(buffer), received, client_sender_for_server, client_sender_port) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
            //system("clear");
            //std::cout<<buffer<<std::endl;

            //CONVERTING TO UTF-8
            std::string str(buffer);

            uchardet_t ud = uchardet_new();
            uchardet_handle_data(ud, str.c_str(), str.size());
            uchardet_data_end(ud);
            const char *encoding = uchardet_get_charset(ud);
            std::string result(encoding);
            // std::cout << "encoding: " << encoding << std::endl;
            uchardet_delete(ud);

            // Create an iconv descriptor for the conversion
            iconv_t cd = iconv_open("UTF-8", "ASCII");

            std::string ascii_str = str;

            // Get the length of the input and output strings
            size_t in_len = ascii_str.length();
            size_t out_len = in_len * 4; // Maximum possible size for UTF-8

            // Allocate memory for the output string
            char *out_buf = new char[out_len + 1];

            // Convert the string
            char *in_ptr = const_cast<char *>(ascii_str.c_str());
            char *out_ptr = out_buf;
            if (iconv(cd, &in_ptr, &in_len, &out_ptr, &out_len) == (size_t)-1)
            {
                perror("iconv");
                exit(EXIT_FAILURE);
            }

            // Null-terminate the output string
            *out_ptr = '\0';

            // Clean up
            iconv_close(cd);
            std::string utf8_str(out_buf);
            delete[] out_buf;

            *m_ascii_text = utf8_str;
            m_dispatcher->emit();
        }
        
    }
    


}

