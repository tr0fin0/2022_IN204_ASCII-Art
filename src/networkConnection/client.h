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

void sendToServer(const char *server_IP_address){
    sf::UdpSocket socket;
    // UDP socket:
    sf::IpAddress recipient(server_IP_address);
    std::cout<<"Trying to connect to " << recipient.toString()<<"\n";;
    unsigned short server_receive_port = 54000;
    
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 1).get(), 2500, recipient, server_receive_port) != sf::Socket::Done)
        {
            std::cout<<"Error in sending to " << recipient.toString() <<"\n";;        
        }        
    }

}

void receiveFromServer(const char* server_IP_address, std::string *m_ascii_text){
    char buffer[2500];
    std::size_t received;
    unsigned short server_sender_port;

    sf::UdpSocket socket;
    if (socket.bind(54001) != sf::Socket::Done)
    {
        printf("Error bro\n");
        return;
    }
    std::cout<<"Binded to " << socket.getLocalPort()<<"\n";
    int i = 1;
    while(1){
        i = i * -1;
        // UDP socket:
        if (socket.receive(buffer, sizeof(buffer), received, server_sender_for_client, server_sender_port) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
            system("clear");
            std::cout<<buffer;

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

        }
    
    }
}


void be_client(const char* server_IP_address, std::string m_ascii_text){

    std::thread t1 = std::thread(sendToServer, server_IP_address);

    std::thread t2 = std::thread(receiveFromServer, server_IP_address, &m_ascii_text);

    t1.join();
    t2.join();
}
