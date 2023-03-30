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
            t2 = std::thread(receiveFromClient, &m_ascii_text, &m_dispatcher);
            t1 = std::thread(sendToClient);
            
            t1.join();
            t2.join();

        }else{
            std::thread t1 = std::thread(sendToServer, server_IP_address);
            std::thread t2 = std::thread(receiveFromServer, server_IP_address, &m_ascii_text, &m_dispatcher);

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