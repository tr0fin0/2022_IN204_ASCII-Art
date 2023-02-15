#include <SFML/Network.hpp>
#include "../converters/VideoConverter.h"

using namespace std;

sf::TcpSocket socket_client;

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
        if (socket_client.send((char*)c.parallelConvert(c.getImage(), 1, 3).get(), 2500) != sf::Socket::Done)
        {
            std::cout<<"Error in sending"<<"\n";        
        }        
    }

}

void receiveFromServer(){
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
        if (socket_client.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
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

    sf::Socket::Status status = socket_client.connect(server_IP_address, 53000);
    if (status != sf::Socket::Done)
    {
        cout << "Error trying to connect" << endl;
    }

    std::thread t1 = std::thread(sendToServer);

    std::thread t2 = std::thread(receiveFromServer);

    t1.join();
    t2.join();
}
