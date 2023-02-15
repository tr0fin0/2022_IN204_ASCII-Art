#include "tcp_c.cpp"
sf::TcpSocket socket_server;

void sendToClient(){
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
        if (socket_server.send((char*)c.parallelConvert(c.getImage(), 1, 3).get(), 2500) != sf::Socket::Done)
        {
            std::cout << "Error in sending to client" << std::endl;
        }        
    }

}

void receiveFromClient(){
    
    char buffer[2500];
    std::size_t received = 0;
    
    while(1){
        // UDP socket:
        if (socket_server.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
            system("clear");
            std::cout<<buffer<<std::endl;
        }
        
    }
    
}


void be_tcp_server(){
    
    sf::TcpListener listener;
    
    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        // error...
        printf("Error trying to listen\n");
        return;
    }
    
    // accept a new connection
    if (listener.accept(socket_server) != sf::Socket::Done)
    {
        // error...
        cout << "Error trying to bind the connection" << endl;
    }

    
    std::thread t2 = std::thread(receiveFromClient);

    std::thread t1 = std::thread(sendToClient);

    t1.join();
    t2.join();
 
}

