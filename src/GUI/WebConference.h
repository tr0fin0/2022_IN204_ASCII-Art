#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>

#include <uchardet/uchardet.h>

#include <glib.h>
#include <iconv.h>
#include <iostream>
#include <string>
#include <cstring>

#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Network.hpp>

using namespace std;

sf::IpAddress server_sender;
sf::IpAddress client_sender;
class WebConference : public Gtk::Window
{
public:
    //WebConference constructor
    //server -> server_or_client == 1 | otherwise -> client
    //if client, 
    WebConference(int server_or_client, char* server_IP_address)
    {
        this->server_or_client = server_or_client;
        this->server_IP_address = server_IP_address;

        int windowW = 1000;
        int windowH = 1000;

        m_textview = Gtk::manage(new Gtk::TextView());
        m_textview->set_editable(true);
        m_textview->set_cursor_visible(false);
        m_buffer = m_textview->get_buffer();

        m_buffer->set_property("monospace", true);

        m_textview->override_font(Pango::FontDescription("Monospace 12"));
        m_textview->set_justification(Gtk::JUSTIFY_CENTER);

        add(*m_textview);

        set_title("ASCII Conference");
        set_default_size(windowW, windowH);
        set_border_width(10);
        set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
        set_visible(true);
        set_can_focus(false);
        set_resizable(false);

        m_dispatcher.connect([this]()                     {
            m_buffer->set_text(m_ascii_text);
        });


        if(server_or_client == 1){
            t2 = std::thread(receiveFromClient);
            t1 = std::thread(sendToClient);
            
            t1.join();
            t2.join();

        }else{
            std::thread t1 = std::thread(sendToServer, server_IP_address);
            std::thread t2 = std::thread(receiveFromServer, server_IP_address);

            t1.join();
            t2.join();
        }

        show_all_children();
    }

    ~WebConference(){
        t1.join();
        t2.join();
        close();
    }

private:
    std::thread t1, t2;
    Gtk::TextView *m_textview;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer;
    
    int server_or_client;
    const char* server_IP_address;

    void on_button_quit();
    void convertAndDispatch(std::string str);
    //void sendToServer();
    //void sendToClient();
    //void receiveFromServer();
    //void receiveFromClient();
};

void WebConference::on_button_quit()
{
    t1.join();
    t2.join();
    close();
}
/*
void sendToServer(const char* server_IP_address){
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 2).get(), 2500, recipient, server_receive_port) != sf::Socket::Done)
        {
            std::cout<<"Error in sending to " << recipient.toString() <<"\n";;        
        }        
    }

}

void receiveFromServer(const char* server_IP_address){
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
        if (socket.receive(buffer, sizeof(buffer), received, server_sender, server_sender_port) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
        }
    
    }
}

void sendToClient(){
    sf::UdpSocket socket;

    while (client_sender.toString() == "0.0.0.0")
    {
    }
    // UDP socket:    
    sf::IpAddress recipient(client_sender.toString());
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
        if (socket.send((char*)c.parallelConvert(c.getImage(), 1, 2).get(), 2500, recipient, client_receive_port) != sf::Socket::Done)
        {
            std::cout << "Error in sending to client" << std::endl;
        }        
    }

}

void receiveFromClient(){
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
        if (socket.receive(buffer, sizeof(buffer), received, client_sender, client_sender_port) != sf::Socket::Done)
        {
            std::cout<<"Error in rcv" << std::endl;
        }
        if(received == sizeof(buffer)){
        }
        
    }
}

*/
void WebConference::convertAndDispatch(std::string str){

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

    m_ascii_text = utf8_str;
    m_dispatcher.emit();
}