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


class WebConference : public Gtk::Window
{
public:
    //WebConference constructor
    //server -> server_or_client == 1 | otherwise -> client
    //if client, 
    WebConference(int server_or_client, char* server_IP_address = NULL)
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
        
        std::string asciiWaiting;
        if(server_or_client == 1)
            asciiWaiting = getWaiting();
        else
            asciiWaiting = getEntering();

        m_buffer->set_text(asciiWaiting);

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

        }else{
            t1 = std::thread(sendToServer, server_IP_address);
            t2 = std::thread(receiveFromServer, server_IP_address, &m_ascii_text, &m_dispatcher);

        }

        show_all_children();
    }

    ~WebConference()
    {
        t1.join();
        t2.join();
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
};

void WebConference::on_button_quit()
{
    t1.join();
    t2.join();
    close();
}
